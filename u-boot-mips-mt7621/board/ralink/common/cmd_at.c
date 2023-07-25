/*
 * Copyright (c) 2020 Zyxel Communications, Corp. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <inttypes.h>
#include <linux/sizes.h>
#include <zyxel_util.h>

extern struct dualImageInfo dualIMAGE;
static int do_at(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return CMD_RET_SUCCESS;
}
U_BOOT_USER_CMD(
	at, 1, 1, do_at,
	"print OK",
	""
);

static int do_athe(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return run_command("help", 0);
}
U_BOOT_USER_CMD(
	athe, 1, 1, do_athe,
	"show available commands",
	""
);

static int do_atsr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return run_command("reset", 0);
}
U_BOOT_USER_CMD(
	atsr, 1, 0, do_atsr,
	"reboot",
	""
);

static int do_atna(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[256];

	if (argc != 2)
		return CMD_RET_USAGE;
	snprintf(runcmd, sizeof(runcmd), "setenv ipaddr %s", argv[1]);

	return run_command(runcmd, 0);
}
U_BOOT_USER_CMD(
	atna, 2, 0, do_atna,
	"set board IP for tftp",
	"ip-addr"
);

static int do_atns(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[256];

	if (argc != 2)
		return CMD_RET_USAGE;
	snprintf(runcmd, sizeof(runcmd), "setenv serverip %s", argv[1]);

	return run_command(runcmd, 0);
}
U_BOOT_USER_CMD(
	atns, 2, 0, do_atns,
	"set server IP for tftp",
	"ip-addr"
);

static int do_atnf(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[1280];

	if (argc != 2)
		return CMD_RET_USAGE;
	snprintf(runcmd, sizeof(runcmd), "setenv bootfile %s", argv[1]);

	return run_command(runcmd, 0);
}
U_BOOT_USER_CMD(
		atnf, 2, 0, do_atnf,
		"set filename for tftp",
		"filename"
);

static int do_atnx(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[256];
	uint32_t dfl_load_addr = CONFIG_SYS_LOAD_ADDR;

	if (argc == 2)
		copy_filename(net_boot_file_name, argv[1],
				sizeof(net_boot_file_name));
	else
		copy_filename(net_boot_file_name, env_get("bootfile"),
				sizeof(net_boot_file_name));

	snprintf(runcmd, sizeof(runcmd),
			"setenv normal_update; imgaddr=0x%"PRIx32" && tftpboot $imgaddr && iminfo $imgaddr && source $imgaddr:script",
			dfl_load_addr);

	return run_command(runcmd, 0);
}
U_BOOT_CMD(
		atnx, 2, 0, do_atnx,
		"do full firmware update via tftp",
		"[filename]"
);

static int do_atnz(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[256];
	uint32_t dfl_load_addr = CONFIG_SYS_LOAD_ADDR;

	if (argc == 2)
		copy_filename(net_boot_file_name, argv[1],
				sizeof(net_boot_file_name));
	else
		copy_filename(net_boot_file_name, env_get("bootfile"),
				sizeof(net_boot_file_name));

	snprintf(runcmd, sizeof(runcmd),
			"setenv normal_update 1 && imgaddr=0x%"PRIx32" && tftpboot $imgaddr && iminfo $imgaddr && source $imgaddr:script",
			dfl_load_addr);

	return run_command(runcmd, 0);
}
U_BOOT_USER_CMD(
		atnz, 2, 0, do_atnz,
		"do firmware update via tftp",
		"[filename]"
);

static int do_atsh(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	int width;
	MRD mrd;

	width = 22;
	mrd_read(&mrd);

	printf("%-*s: %s\n", width, "Vendor name", mrd.VendorName);
	printf("%-*s: %s\n", width, "Product model", mrd.ProductName);
	printf("%-*s: %d\n", width, "System type", mrd.SystemType);
	printf("%-*s: %02x%02x%02x%02x%02x%02x\n", width, "MAC address",
			mrd.EtherAddr[0], mrd.EtherAddr[1], mrd.EtherAddr[2],
			mrd.EtherAddr[3], mrd.EtherAddr[4], mrd.EtherAddr[5]);
	printf("%-*s: %x\n", width, "Default country code", mrd.CountryCode);
	printf("%-*s: %x\n", width, "Boot module debug flag", mrd.AreaCode);
	printf("%-*s: %s\n", width, "Hardware version", mrd.HardwareVersion);
	printf("%-*s: %s\n", width, "Serial number", mrd.SerialNumber);

	printf("%-*s: ", width, "SNMP MIB level & OID");
	for (i = 0 + 2; i < 21 + 2; i++) {
		printf("%02x", mrd.Reserved0[i]);
	}
	printf("\n");

	printf("%-*s: %x\n", width, "Main feature bit", mrd.FeatureBit);

	printf("%-*s: ", width, "Other feature bits");
	for (i = 0; i < ARRAY_SIZE(mrd.FeatureBits); i++) {
		printf("%02x", mrd.FeatureBits[i]);
		if (i % 16 == 15)
			printf("\n%-*s", width + 2, " ");
		else
			printf(" ");
	}
	printf("\n");

	/* Use FeatureBits[9] bit 0 as recovery flag */
	printf("%-*s: %d\n", width, "MRD recovery flag",
			(mrd.FeatureBits[9] & 0x01));

	return CMD_RET_SUCCESS;
}
U_BOOT_USER_CMD(
	atsh, 1, 1, do_atsh,
	"dump Manufacturer Related Data (MRD)",
	""
);

static int do_atwe(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	char addr[3];
	MRD mrd;

	if (argc != 2)
		return CMD_RET_USAGE;

	/* Make sure the MAC address has exactly 12 chars */
	if (strlen(argv[1]) != 12)
		return CMD_RET_USAGE;

	mrd_read(&mrd);

	for (i = 0; i < 6; i++) {
		strncpy(addr, argv[1] + (i * 2), 2);
		addr[2] = '\0';
		mrd.EtherAddr[i] = simple_strtoul(addr, NULL, 16);
	}

	if (mrd_write(&mrd) < 0)
		return CMD_RET_FAILURE;

	run_command("reset", 0);

	return CMD_RET_SUCCESS;
}
U_BOOT_CMD(
	atwe, 2, 0, do_atwe,
	"write MAC address",
	"mac-addr"
);

static int do_atgo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char runcmd[256];
	int imageNum=0;
	int desired_boot_image;
	const char *ep;

	ep = env_get("autostart");
	if (ep)
		ep = strdup(ep);

	env_set("autostart", "yes");

	if(argc == 2){
		desired_boot_image = simple_strtoul(argv[1], NULL, 10);
		if (desired_boot_image != 0 && desired_boot_image != 1)
			return CMD_RET_USAGE;
		else {
			imageNum = desired_boot_image;
		}
	}
	else
		imageNum = checkHaveNewImage();

	snprintf(runcmd, sizeof(runcmd), "setenv bootargs ${bootargs} bootImage=%d bootVer=%s", imageNum, CONFIG_ZYXEL_VERSION);
	run_command(runcmd, 0);

	if (imageNum == 1)
		run_command("nmbm nmbm0 boot firmware_1", 0);
	else
		run_command("nmbm nmbm0 boot firmware", 0);
	return CMD_RET_SUCCESS;
}
U_BOOT_USER_CMD(
	atgo, 2, 0, do_atgo,
	"boot",
	"[image]\n"
	"    - 0 = image0\n"
	"    - 1 = image1"
);

static int do_atds(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

	int imageNum = 0;
	const char imageStatus[][10]={"none","new","success","fail"};

	while(imageNum < NUMOFIMAGE){
		printf("Image%d status		:%s\r\n", imageNum ,imageStatus[dualIMAGE.image[imageNum].state]);
		imageNum++;
	}
	printf("Boot Image		:Image%d\r\n", dualIMAGE.bootImage);
	return CMD_RET_SUCCESS;
}
U_BOOT_USER_CMD(
	atds, 1, 1, do_atds,
	"show dual image info",
	""
);

static int do_atnb(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc == 2)
		copy_filename(net_boot_file_name, argv[1],
				sizeof(net_boot_file_name));
	else
		return CMD_RET_USAGE;

	if(bootloader_write())
		return CMD_RET_FAILURE;

	return CMD_RET_SUCCESS;
}
U_BOOT_CMD(
	atnb, 2, 0, do_atnb,
	"Upload and program bootloader via tftp.",
	"[filename]"
);
