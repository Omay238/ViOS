#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define VIOS_TOTAL_INTERRUPTS 512

#define VIOS_HEAP_SIZE_BYTES 104857600
#define VIOS_HEAP_BLOCK_SIZE 4096
#define VIOS_HEAP_ADDRESS 0x01000000
#define VIOS_HEAP_TABLE_ADDRESS 0x000007E00

#define VIOS_SECTOR_SIZE 512

#define VIOS_MAX_FILESYSTEMS 12
#define VIOS_MAX_FILE_DESCRIPTORS 512

#endif