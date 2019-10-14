#include "ecdsa_secp256k1.h"
#include <mbedtls/ecdsa.h>
#include "assert.h"
#include "jolt_helpers.h"
#include "string.h"

/**
 * @brief Populate a keypair object.
 * @param[out] keypair Populated keypair object. Must be previously initialized.
 */
static jolt_crypto_status_t jolt_crypto_ecdsa_secp256k1_keypair( mbedtls_ecp_keypair *keypair,
                                                                 const uint8_t *private_key )
{
    int res;
    jolt_crypto_status_t status = JOLT_CRYPTO_STATUS_FAIL;

    res = mbedtls_mpi_read_binary( &keypair->d, private_key, 32 );

    /* Populate secret */
    res = mbedtls_mpi_read_binary( &keypair->d, private_key, 32 );
    if( 0 != res ) goto exit;

    res = mbedtls_ecp_group_load( &keypair->grp, MBEDTLS_ECP_DP_SECP256K1 );
    if( 0 != res ) goto exit;

    /* check valid private key range */
    {
        mbedtls_mpi upper;

        mbedtls_mpi_init( &upper );
        assert( 0 == mbedtls_mpi_read_string( &upper, 16,
                                              "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364140" ) );

        if( 1 == mbedtls_mpi_cmp_mpi( &keypair->d, &upper ) || 1 != mbedtls_mpi_cmp_int( &keypair->d, 0 ) ) {
            /* Private Key wasn't in valid range */
            status = JOLT_CRYPTO_STATUS_INVALID_PRIV;
            goto exit;
        }
    }

    /* Derive Public Key */
    res = mbedtls_ecp_mul( &keypair->grp, &keypair->Q, &keypair->d, &keypair->grp.G, NULL, NULL );
    if( 0 != res ) goto exit;

    status = JOLT_CRYPTO_STATUS_SUCCESS;

exit:

    return status;
}

jolt_crypto_status_t jolt_crypto_ecdsa_secp256k1_derive( uint8_t *public_key, uint16_t *public_key_len,
                                                         const uint8_t *private_key, uint16_t private_key_len )
{
    int res;
    jolt_crypto_status_t status = JOLT_CRYPTO_STATUS_FAIL;
    mbedtls_ecp_keypair keypair;
    mbedtls_ecp_keypair_init( &keypair );

    /* Confirm input/output buffer sizes */
    if( 64 != *public_key_len || 32 != private_key_len ) {
        status = JOLT_CRYPTO_STATUS_PARAM;
        goto exit;
    }

    status = jolt_crypto_ecdsa_secp256k1_keypair( &keypair, private_key );
    if( JOLT_CRYPTO_STATUS_SUCCESS != status ) goto exit;
    status = JOLT_CRYPTO_STATUS_FAIL;

    /* Export Q to public key */
    memzero( public_key, 64 );
    res = mbedtls_mpi_write_binary( &keypair.Q.X, public_key, 32 );
    if( 0 != res ) goto exit;
    res = mbedtls_mpi_write_binary( &keypair.Q.Y, public_key + 32, 32 );
    if( 0 != res ) goto exit;

    status = JOLT_CRYPTO_STATUS_SUCCESS;

exit:
    mbedtls_ecp_keypair_free( &keypair );

    return status;
}

jolt_crypto_status_t jolt_crypto_ecdsa_secp256k1_sign( uint8_t *sig, uint16_t *sig_len, const uint8_t *msg,
                                                       size_t msg_len, const uint8_t *public_key,
                                                       uint16_t public_key_len, const uint8_t *private_key,
                                                       uint16_t private_key_len )
{
    int res;
    jolt_crypto_status_t status = JOLT_CRYPTO_STATUS_FAIL;
    mbedtls_ecdsa_context ctx;
    mbedtls_ecp_keypair keypair;

    mbedtls_ecdsa_init( &ctx );
    mbedtls_ecp_keypair_init( &keypair );

    /* Confirm input/output buffer sizes */
    if( 64 != public_key_len || 32 != private_key_len ) {
        status = JOLT_CRYPTO_STATUS_PARAM;
        goto exit;
    }
    else if( *sig_len < ( 2 * 32 + 9 ) ) {
        /* Must support maximum signature length size */
        return JOLT_CRYPTO_STATUS_PARAM;
    }
    else if( 32 != msg_len ) {
        /* This is for signing a message hash, not the message itself */
        return JOLT_CRYPTO_STATUS_PARAM;
    }

    /* Populate the keypair */
    status = jolt_crypto_ecdsa_secp256k1_keypair( &keypair, private_key );
    if( JOLT_CRYPTO_STATUS_SUCCESS != status ) goto exit;
    status = JOLT_CRYPTO_STATUS_FAIL;

    // TODO: compare derived public key with provided one for safety.

    /* Instantiate the signing context */
    res = mbedtls_ecdsa_from_keypair( &ctx, &keypair );
    if( 0 != res ) goto exit;

    /* Sign */
    size_t slen;
    res = mbedtls_ecdsa_write_signature( &ctx, MBEDTLS_MD_SHA256, msg, sizeof( msg ), sig, &slen, NULL, NULL );
    if( 0 != res ) goto exit;
    *sig_len = slen;

    status = JOLT_CRYPTO_STATUS_SUCCESS;

exit:
    mbedtls_ecdsa_free( &ctx );
    mbedtls_ecp_keypair_free( &keypair );

    return status;
}

jolt_crypto_status_t jolt_crypto_ecdsa_secp256k1_verify( const uint8_t *sig, uint16_t sig_len, const uint8_t *msg,
                                                         size_t msg_len, const uint8_t *public_key,
                                                         uint16_t public_key_len )
{
    return JOLT_CRYPTO_STATUS_NOT_IMPL;
}
