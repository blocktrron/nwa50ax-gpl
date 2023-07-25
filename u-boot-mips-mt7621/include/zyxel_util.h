#ifndef _ZYXEL_UTIL_H_
#define _ZYXEL_UTIL_H__

#include <inttypes.h>
#include <common.h>
#include <mapmem.h>
#include <asm/unaligned.h>

#define NUMOFIMAGE		2
#define BOOTCONFIG_OFFSET	0x7700000
#define BOOTCONFIG_LOAD_ADDR	0x8ff00000
#define BOOTCONFIG_SIZE		0x20000

#define DUALIMAGE_IMGSTATE_MASK 	0xc
#define DUALIMAGE_IMGLOG_MASK 		0x2
#define BOOTIMAGE_IMAGE_MASK 		0x1

#define PART_NAME_BOOTLOADER "u-boot"
#define PART_NAME_MRD "mrd"

#define posOfStartbit(b,n,m) \
({ int def = b; \
int len=0; \
n=0;	\
m=0;	\
while (def) { \
        if(def & 1 ) {break;} \
        n ++; \
        def = def >> 1; \
};  \
while (def) { \
        if((def & 1) ==0) {break;} \
        len ++; \
        def = def >> 1; \
};  \
m = (1 << len) - 1; \
})

typedef enum{
	NONE=0,
	NEW_IMAGE,
	SUCCESS_IMAGE,
	FAIL_IMAGE
}ImageState;

typedef enum{
	NO_LOG = 0,
	LOG
}zyDualImageLog;

/* Manufacturer Related Data */
typedef struct mrd {
	uint8_t BspHeapBlkSize[16];
	uint8_t BspHeapBlkCnt[16];
	uint8_t HardwareVersion[32];
	uint8_t SerialNumber[32];
	uint8_t Reserved0[32];
	uint8_t VendorName[32];
	uint8_t ProductName[32];
	uint32_t Reserved4;
	uint16_t Reserved1;
	uint8_t SystemType;
	uint8_t Reserved2;
	uint8_t FeatureBits[30]; /* Other Feature Bits */
	uint8_t FeatureBit; /* Main Feature Bits */
	uint8_t Reserved3;
	uint8_t EtherAddr[6];
	uint8_t CountryCode;
	uint8_t AreaCode;
} __attribute__((__packed__)) MRD;

struct ImageInfo
{
	ImageState state;
	int log;
	uint32_t age;
};

struct dualImageInfo
{
	int bootImage;
	int upgradeImage;
	struct ImageInfo image[NUMOFIMAGE];
};

void dumpDualImageInfoFromBootconfig(void);
void writeDualImageInfoToBootconfig(void);
int getBootImageNum(void);
int checkHaveNewImage(void);
int flash_part_read(char *part_name, void *buf, size_t offset, size_t size);
int flash_part_write(char *part_name, void *buf, size_t offset, size_t size);
ssize_t mrd_read(MRD *mrd);
ssize_t mrd_write(MRD *mrd);
ssize_t bootloader_write(void);
uint16_t model_get(void);
int zy_init(void);
#endif /* _ZYXEL_UTIL_H_ */
