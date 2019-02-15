To facilitate smaller applications and faster load times, Jolt uses a custom
file format called Jolt Executable and Linkable Format (JELF). JELF can be 
roughly thought of as if an ELF16 format existed.

JELF works by removing unused fields and reducing various larger datatypes
(primarily `uint32_t`) to smaller datatypes that are more appropriate for an
embedded system. The JELF format was made soley to be used by the JELFLoader on
the ESP32. When many of the ESP32's perhipherals are enabled (namely WiFi and Bluetooth), there is very limited RAM available for other tasks. Because of this, JELF relies on bitfields at the cost of CPU cycles. Bitfields are used for convenience, but are notoriously non-portable. However,
this is already optimized for a single plaform, the ESP32, so its fine.

JELF allows the binary to be about 50% smaller and load twice as fast while 
using less RAM.

Examples here are statistics on the Jolt Nano App and are only provided as an 
example on space savings due to these optimizations.

# How to use

See:

```
python3 elf2jelf.py --help
```

# Differences between ELF32 and JELF
Unless otherwise specified, ELF32 and JELF are the same. C Structs are used to
describe changes in the data format.

## Data Types
```
typedef uint16_t   Elf32_Half;
typedef uint32_t   Elf32_Word;
typedef int32_t    Elf32_Sword;
typedef uint64_t   Elf32_Xword;
typedef int64_t    Elf32_Sxword;
typedef uint32_t   Elf32_Addr;
typedef uint32_t   Elf32_Off;
typedef uint16_t   Elf32_Section;
typedef Elf32_Half Elf32_Versym;
#define EI_NIDENT (16)
```

## Program Header
Since the program header is only present once in the file, we are less agressive
to optimize and more inclined for future expandability.
```
typedef struct {
    unsigned char  e_ident[EI_NIDENT];  /* Magic number and other info */
    Elf32_Half     e_type;              /* Object file type */
    Elf32_Half     e_machine;           /* Architecture */
    Elf32_Word     e_version;           /* Object file version */
    Elf32_Addr     e_entry;             /* Entry point virtual address */
    Elf32_Off      e_phoff;             /* Program header table file offset */
    Elf32_Off      e_shoff;             /* Section header table file offset */
    Elf32_Word     e_flags;             /* Processor-specific flags */
    Elf32_Half     e_ehsize;            /* ELF header size in bytes */
    Elf32_Half     e_phentsize;         /* Program header table entry size */
    Elf32_Half     e_phnum;             /* Program header table entry count */
    Elf32_Half     e_shentsize;         /* Section header table entry size */
    Elf32_Half     e_shnum;             /* Section header table entry count */
    Elf32_Half     e_shstrndx;          /* Section header string table index */
} Elf32_Ehdr;
```
52 Bytes

```
#define EI_NIDENT 6
typedef struct {
    unsigned char  e_ident[EI_NIDENT];  /* Magic number and other info */
    uint8_t        e_version_major;
    uint8_t        e_version_minor;
    uint16_t       e_entry_offset;      /* Entry point function offset */
    uint16_t       e_shnum;             /* Section header table entry count */
    uint32_t       e_coin_purpose;
    uint32_t       e_coin_path;
    char           e_bip32key[32];
    uint8_t        e_signature[32];
} Jelf_Ehdr;
```
84 Bytes

`EI_NIDENT` - Reduced from 16 bytes to 6 bytes. The magic value for a JELF file
 is `{0x7F, 'J', 'E', 'L', 'F', '\0'}`.

 `e_type` - Removed; unused
 `e_machine` - Removed; not used since it's always Xtensa
 `e_version` - Reduced to 2 uint8_t for major, minor
 `e_entry_offset` - This needs to be populated to the symtab index referencing `app_main`, currently the ELF32 file doesn't populate this field
 `e_phoff` - Removed; unused
 `e_flags` - Removed; unused
 `e_ehsize` - redundent since the version major specifier indicates compatability
 `e_shentsize` - redundant since the version major specifier indicates compatability.
 `e_phentsize` - Removed; unused
 `e_phnum` - Removed; unused
 `e_shstrndx` - Removed; `.shstrtab` is stripped

 additions:

 `e_signature` - 256-bit signature of the whole file. While computing the signature, replace the `e_signature` field with 256 bits of 0's.

 `e_coin` - 8 bytes specifying the coin derivation. For example, 44'/165'

 `e_bip32key` - 32 byte nul-terminated string for the derivation seed string. For example, `ed25519_seed` or `bitcoin_seed`

 Since these additional fields would have found themselves conventionally as an 
 additional section, they actually represent a net space saving by putting them 
 in the JELF header rather than having the overhead of a Section Header.

## Section Header
```
typedef struct {
    Elf32_Word    sh_name;        /* Section name (string tbl index) */
    Elf32_Word    sh_type;        /* Section type */
    Elf32_Word    sh_flags;       /* Section flags */
    Elf32_Addr    sh_addr;        /* Section virtual addr at execution */
    Elf32_Off     sh_offset;      /* Section file offset */
    Elf32_Word    sh_size;        /* Section size in bytes */
    Elf32_Word    sh_link;        /* Link to another section */
    Elf32_Word    sh_info;        /* Additional section information */
    Elf32_Word    sh_addralign;   /* Section alignment */
    Elf32_Word    sh_entsize;     /* Entry size if section holds table */
} Elf32_Shdr;
```
```
typedef struct {
    uint64_t      sh_type     :2;         /* Section type */
    uint64_t      sh_flags    :2;         /* Section flags */
    uint64_t      sh_size     :16;        /* Section size in bytes */
    uint64_t      sh_info     :14;        /* Additional section information */
    uint64_t      padding     :8;         /* Not actually in JELF file */
} Jelf_Shdr;
```

`sh_name` - section header names are not necessary (so `.shstrtab` can also be removed)

`sh_type` - section's enumerated type. We only treat 2 section types differently:

* `SHT_NOBITS`

* `SHT_RELA`

* All other section types are classified in a third "other" type.

`sh_flags` - section attributes expressed as bitflags; we only care about 2:

* `SHF_EXECINSTR`

* `SHF_ALLOC`

`sh_addr`, `sh_addralign`, `sh_link`, and`sh_entsize` are removed because they are not used.

`sh_offset` - The section file offset from the beginning of the file. Reducing this to 19 bits limits Jolt applications to be a maximum of 512KB in size.

`sh_size` - Section size, needs to be able to (almost) contain the maximum `sh_offset` value.

`sh_info` - Various information depending on section type. We only use it for the `SHT_RELA` type where it contains the section header index for which the relocation applies. 14 bits allows for 16,384 sections. For non RELA sections this is `0`.


These optimizations reduce the 40 byte section header to just 7 bytes. There are 
about 250 sections in the Jolt Nano App, so this translates to 8,250 bytes saved.


## Symbol and Symbol Table
```
typedef struct {
    Elf32_Word       st_name;        /* Symbol name (string tbl index) */
    Elf32_Addr       st_value;       /* Symbol value */
    Elf32_Word       st_size;        /* Symbol size */
    unsigned char    st_info;        /* Symbol type and binding */
    unsigned char    st_other;       /* Symbol visibility */
    Elf32_Section    st_shndx;       /* Section index */
} Elf32_Sym;
```

```
typedef struct {
    uint16_t         st_name;         /* Index, also Name */
    uint16_t         st_shndx;        /* Section index */
    uint32_t         st_value;        /* Unused most the time, but cant think of a good way of removing */
} Jelf_Sym;
```

`st_size` - Contains symbol size; unused

`st_info` - Only used for help finding the entrypoint, which we now include in the program header, so unnecessary.

`st_other` - Unused

`st_shndx` - Indexes into sections; we already limited the number of sections to 14 bits (16,384) in the Section Header, so we reduce this is a `uint16_t`

The Jolt Nano App contains 258 symbols, making the original string table 
take up 4,128 bytes. Now that each symbol has been reduced from 16 bytes to 8 bytes, we can save 2064 bytes.

## RELA Information
`uint32_t` datatypes are excessive for the size of a JELF; a `uint16_t` is
sufficent.

In ELF32, the 8 LSbit of `r_info` are used to specify the type of relocation to
perform. For our applications, only 4 different types are used 
(`NONE`, `ASM_EXPAND`, `32`, `SLOT0_OP`), so this can be reduced to 2 bits.
 The remaining 14 bits (16384) are used to index into the symbol table,
 which is enough for Jolt applications.
```
typedef struct {
    Elf32_Addr    r_offset;        /* Address */
    Elf32_Word    r_info;          /* Relocation type and symbol index */
    Elf32_Sword   r_addend;        /* Addend */
} Elf32_Rela;
```
```
typedef struct {
    uint16_t    r_offset;        /* Address */
    uint16_t    r_info;          /* Relocation type and symbol index */
    int16_t     r_addend;        /* Addend */
} Jelf_Rela;
```
This optimization reduces the Struct size from 12 bytes to 6 bytes. The Nano App
contains 1818 relocations, so this optimization saves a whopping 10,908 bytes.

## Remove `.strtab`
The `.strtab` string table gives human-readable names to symbols.

Functions are mapped from JoltOS to the app by matching function names.

The Jolt Nano App's `.strtab` is 2615 Bytes and contains 155 entries, meaning that on average, each string takes up 16.87 bytes. Since the function names don't need to be human readable, we can completely remove the `.strtab` and instead have the `st_name` field of a `Jelf_Sym` index into JoltOS's exported functions. So long as we only append new functions to the exported function table in new versions of JoltOS, this is a valid solution. This solution also reduces necessary caching and
CPU cycles for comparing string names.

`st_name`:

* 0 is unnamed

* 1...N_EXPORTS are exported function names

## Honorable Mentions
Information in this section don't strictly go against ELF32 standards, just
could be considered a little unusual.

### Section Header String Table
The `.shstrtab` is stripped as it is not really necessary.

This saves 4,110 bytes in the Jolt Nano App.

## Saving Summary
Original ELF32 Nano App: 54,604 Bytes

| Optimization                          | Bytes Saved  |
|---------------------------------------|--------------|
| Reduced RELA Info                     | +10,908      |
| Reduced Section Headers               | +8,250       |
| Remove `.shstrtab`                    | +4,208       |
| Remove `.strtab`                      | +2,615       |
| Reduced Symbols (and thus, `.symtab`) | +2,064       |

Grand Total: 28,045 Bytes saved, reducing the binary from 54,604 bytes to 26559 bytes.

todo: additionals/subtractions from program header

# Misc Design Decisions

`.symtab` is 4218 bytes and contains 258 entries.

# Section Reordering
We can reorder the sections so we can take advantage of:

* Locality caching
* Loading from a compressed file (todo)

In the Jelf Loader code, first all sections that take up memory during 
execution are allocated and loaded. By default, these are scattered all over the file, 
so lets put them in the beginning. Whenever we load a section, we put it in a singly-linked-list, 
where the newest sections replaces the head. Later, when we transverse this list,
we are essentially reading it "backwards". This itself isn't a problem, but if we assume the 
relocation sections are ordered in a "forwards" fashion, this means that every single 
rela section read will result in a cache miss. For this reason, we order the ALLOC 
sections "backwards" so that when loaded, the singly-linked-list will be in the "correct"
order.

Because we put all the allocated sections in the beginning, once we hit a non-alloc section,
we can stop reading. This has two nice properties:
* We don't need to read unnecessary data
* Compression like zlib works on a moving window. As it transverses a file from the beginning, it keeps 
  a buffer (typically 32KB, but in Jolt we set it to 4KB to reduce memory consumption at
  the cost of a few percentage worse compression) of the latest uncompressed data as a dictionary to
  decompressed subsequent bytes. This means that naively you cannot efficiently access random 
  decompressed data. Every random access would require decompressing from the beginning of the file to that point.
  One could transverse and decompress the compressed file once, making buffer checkpoints throughout the file
  so that any random access could just be picked up from the previous checkpoint; but this takes too much memory for Jolt. Instead, we just
  smartly organize the jelf sections so that all information can be loaded and processed in a single sequential pass. Compressed data reduces the disk size of the app (typically by ~50%) and the number of SPI Flash reads (which are slow).

## Gotchas

* `literal` sections  *must* go before their corresponding `text` section. See https://stackoverflow.com/a/26610227


# Going Further
Now that everything is a sequential read (with absolutely no random reads, assuming cached section header table and cached symtab), we can get rid of offsets in the section header table. In the Nano app, this saves about 681 bytes of compressed data.

## Modified symtab
The symtab also contains an unnecessary number of zeros in the `uint32_t` `st_value` slot. This value 90% of the time is `0x00000000`. To reduce this overhead, we shrink the `st_value` field to a `uint8_t` and make it's value an index into a small auxilary table. We put this table at the beginning of the `symtab section` as follows:

1. `uint8_t` indicating the number of entries `n` in the table that follows
2. n `uint32_t` non-zero `st_values`; denoted as the auxilary symbol table
3. The actual `symtab`

This only saves about of 100 bytes in the compressed binary, but will cut the amount of RAM required by the symtab cache in half. In the Nano app, this saves about 1KB of RAM.