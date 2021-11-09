/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Config file for Galileo-33x board
 *
 * Copyright (C) 2021, Leuze Electronic -https://www.leuze.com
 *
 * Author: Berrux Nguimeya Kana <bkana@leuze.de>
 */

#ifndef __CONFIG_GALILEO_33XX
#define __CONFIG_GALILEO_33XX

//#define CONFIG_GALILEO_33XX

#include <configs/ti_am335x_common.h>

#undef CONFIG_MAX_RAM_BANK_SIZE
#define CONFIG_MAX_RAM_BANK_SIZE	(512 << 20)	/* 512MB */

#define CONFIG_MACH_TYPE		MACH_TYPE_CM_T335

/* Clock Defines */
#define V_OSCK				25000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

#define CONFIG_ENV_SIZE			(16 << 10)	/* 16 KiB */

#ifndef CONFIG_SPL_BUILD

#define NANDARGS \
	"mtdids=" CONFIG_MTDIDS_DEFAULT "\0" \
	"mtdparts=" CONFIG_MTDPARTS_DEFAULT "\0" \
	"nandargs=setenv bootargs console=${console} " \
		"root=${nandroot} " \
		"rootfstype=${nandrootfstype}\0" \
	"nandroot=ubi0:rootfs rw ubi.mtd=rootfs,2048\0" \
	"nandrootfstype=ubifs rootwait=1\0" \
	"nandboot=echo Booting from nand bkana ...; " \
		"run nandargs; " \
		"nand read ${fdt_addr} dtb; " \
		"nand read ${loadaddr} kernel; " \
		"bootz ${loadaddr} - ${fdt_addr}\0"

/*	"loadenv=echo Importing device tree from Nand ...; " \
		"ubifsload ${fdtaddr} nand0 400000; " \*/

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=82000000\0" \
	"fdt_addr=88000000\0" \
	"console=ttyO0,115200n8\0" \
	"rootfs_name=rootfs\0" \
	"source ${loadaddr}\0" \
	"ethaddr=00:15:7b:00:00:03\0" \
	"serverip=192.168.60.1\0" \
	"ipaddr=192.168.60.22\0" \
	"netmask=255.255.255.0\0" \
	NANDARGS

#define CONFIG_BOOTCOMMAND \
		"run nandboot;"
#endif /* CONFIG_SPL_BUILD */

#define CONFIG_TIMESTAMP
#define CONFIG_SYS_AUTOLOAD		"no"

/* Serial console configuration */

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* UART0 */
#define CONFIG_SYS_NS16550_COM2		0x48022000	/* UART1 */

/* I2C Configuration */
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50	/* Main EEPROM */
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1
#define CONFIG_SYS_I2C_EEPROM_BUS	0

/* SPL */

/* Network. */
#define CONFIG_PHY_ATHEROS

/* NAND support */
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_PAGE_COUNT	(CONFIG_SYS_NAND_BLOCK_SIZE / \
					 CONFIG_SYS_NAND_PAGE_SIZE)
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_OOBSIZE		64
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128 * 1024)
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	NAND_LARGE_BADBLOCK_POS
#define CONFIG_SYS_NAND_ECCPOS		{ 0, }

#define CONFIG_SYS_NAND_ECCSIZE		0
#define CONFIG_SYS_NAND_ECCBYTES	0

/* ??PATCH bkana@leuze.com 2021-02-16 */
#define CONFIG_SYS_NAND_USE_FLASH_BBT

#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE

#undef CONFIG_SYS_NAND_U_BOOT_OFFS
/* ??PATCH bkana@leuze.com 2021-02-16 */
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x200000

#define CONFIG_ENV_OFFSET		0x300000 /* environment starts here */
#define CONFIG_SYS_ENV_SECT_SIZE	(128 << 10)	/* 128 KiB */
#define CONFIG_SYS_NAND_ONFI_DETECTION
#ifdef CONFIG_SPL_OS_BOOT
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x500000
#endif

/* GPIO pin + bank to pin ID mapping */
#define GPIO_PIN(_bank, _pin)		((_bank << 5) + _pin)

/* Status LED */
/* Status LED polarity is inversed, so init it in the "off" state */

/* EEPROM */
#define CONFIG_ENV_EEPROM_IS_ON_I2C
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5
#define CONFIG_SYS_EEPROM_SIZE			256

#ifndef CONFIG_SPL_BUILD
/*
 * Enable PCA9555 at I2C0-0x26.
 * First select the I2C0 bus with "i2c dev 0", then use "pca953x" command.
 */
#define CONFIG_PCA953X
#define CONFIG_SYS_I2C_PCA953X_ADDR	0x26
#define CONFIG_SYS_I2C_PCA953X_WIDTH	{ {0x26, 16} }
#endif /* CONFIG_SPL_BUILD */

#endif	/* __CONFIG_GALILEO_33XX */

