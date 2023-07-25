/* $Id: $ */

/*
 *    $Log: zld_product_spec.h,v $
 */

#ifndef __ZLD_PRODUCT_SPEC_H
#define __ZLD_PRODUCT_SPEC_H
/* Linux Kernel Style */

/*

Example:

#define ZLDCONFIG_XYZ 1
#undef  ZLDCONFIG_SYZ

 *** Please note ZLDCONFIG must be located at col 9 ***
*/

/*****************************************************************************/
/* Product Line Defines                                                      */
/*****************************************************************************/
/* Supported Product Line */
#define ZLD_PRODUCT_LINE_USG              (100)
#define ZLD_PRODUCT_LINE_ENTERPRISE_WLAN  (200)
#define ZLD_PRODUCT_LINE_MSBG             (300)

/* the max length is 32, include '\0' */
#define ZLD_PRODUCT_LINE_NAME_USG "ZyWALL"
#define ZLD_PRODUCT_LINE_NAME_ENTERPRISE_WLAN "EnterpriseWLAN"

/*  The gap between product lines is reserved for sub product lines. (i.e. USG_LITE for USG20)
    Programmer NEVER assume the gap's size (range) or the existence of other product lines.

    for example, the following coding style is illegal

    if (ZLDSYSPARM_PRODUCT_LINE >= ZLD_PRODUCT_LINE_USG && ZLDSYSPARM_PRODUCT_LINE < ZLD_PRODUCT_LINE_ENTERPRISE_WLAN)
           printf("for all security product lines"); // wrong! what if we have new product line between USG and WLAN but have different behavior?

    The right way is to use feature flag, not product line flag
*/

/* Define Product Line */
#define ZLDSYSPARM_PRODUCT_LINE ZLD_PRODUCT_LINE_ENTERPRISE_WLAN
#define ZLDSYSPARM_PRODUCT_LINE_NAME ZLD_PRODUCT_LINE_NAME_ENTERPRISE_WLAN
#define ZLDSYSPARM_PRODUCT_LINE_ZONE_NAME ZLD_PRODUCT_LINE_NAME_ENTERPRISE_WLAN

//Alert user to update firmware; used to produce fake c0 firmware
#undef ZLDCONFIG_GUI_LATEST_FW_NOTIFICATION_SUPPORT

/*****************************************************************************/
/* Feature Support Defines                                                   */
/*****************************************************************************/
/* CAPWAP Client support */
#undef ZLDCONFIG_CAPWAP_WTP_SUPPORT
/* Multi-lingual */
#define ZLDCONFIG_MULTI_LINGUAL 1
/* WLAN Profile Based Setting Support */
#define ZLDCONFIG_WLAN_PROFILE_ENABLE	1
/* Mac Filter Profile enhance Support */
#undef ZLDCONFIG_WLAN_MACFILTER_PROFILE_ENHANCE
/* WLAN Security Profile Radius Accounting Support */
#define ZLDCONFIG_WLAN_SECURITY_PROFILE_ACCOUNTING		1	
/* WLAN Security Profile for EAP External */
#define ZLDCONFIG_WLAN_SECURITY_PROFILE_EAP_AUTH_DEFAULT_EXTERNAL        1
/* WLAN WDS support in RADIO Profile */
#undef ZLDCONFIG_WLAN_RADIO_PROFILE_WDS_SETTING
/* 4-MAC WDS support */
#define ZLDCONFIG_WLAN_4MAC_WDS_SUPPORT	1
/* WLAN Support */
#define ZLDCONFIG_WLAN_ENABLE 1
/* WLAN Support Smart Antenna that implemented by Adant */
#undef ZLDCONFIG_WLAN_SMART_ANTENNA_SUPPORT
/* By pass login session limit rule */
#define ZLDCONFIG_NO_ZYSH_NF_CT_BYPASS_LOGIN_PORT	1
/* Daily Report */
#define ZLDCONFIG_DAILY_REPORT	1
/* Daily Report for CAPWAP */
#define ZLDCONFIG_CAPWAP_DAILY_REPORT	1
/* Customized Login Page */
#undef ZLDCONFIG_CUSTOMIZED_LOGIN_PAGE
/* Disk log */
#define ZLDCONFIG_DISKLOG_MTDOOPS 1
/* PKI */
#define ZLDCONFIG_PKI 1
#define ZLDCONFIG_PKI_UNUSED	1
/* Zysh log send system information */
#define ZLDCONFIG_NO_ZYSH_LOG_SEND_SYS_INFO 1
/* Zysh debug manufacture */
#undef ZLDCONFIG_NO_ZYSH_DEBUG_MANUFACTURE
/* Zysh http support*/
#undef ZLDCONFIG_NO_ZYSH_CISCO_HTTP
/* Zysh https support*/
#undef ZLDCONFIG_NO_ZYSH_CISCO_HTTPS
/* Zysh SNMP support*/
#undef ZLDCONFIG_NO_ZYSH_CISCO_SNMP
/* Zysh GUI automation config*/
#undef ZLDCONFIG_NO_GUI_AUTOMATION
/* define this to hide containment option on the GUI */
#define ZLDCONFIG_NO_ROGUEAP_CONTAINMENT_GUI	1
/* No 5GHz objects on GUI */
#define ZLDCONFIG_NO_5G_OBJECTS 1
/*GUI down size*/
#define ZLDCONFIG_GUI_DOWN_SIZE	1
/*support layer 2 isolation*/
#define ZLDCONFIG_WLAN_L2ISOLATION		1
/*support guest ssid*/
#ifdef ZLDCONFIG_WLAN_L2ISOLATION
#define ZLDCONFIG_GUEST_SSID_SUPPORT 1		
#endif
/* not support bind-9.x.x */
#define ZLDCONFIG_NO_DNS_SERVER 1
/* httpd-2.0.55 support*/
#define  ZLDCONFIG_HTTPD	1
/* httpd-2.0.55 down size*/
#define  ZLDCONFIG_HTTPD_DOWN_SIZE	1
/* libol-0.3.14 support */
#undef  ZLDCONFIG_LIBOL
/* HTTP Redirect support*/
#undef  ZLDCONFIG_HTTP_REDIRECT
/* PCI-DSS requirement 8.4 support */
#define ZLDCONFIG_PCI_DSS_SUPPORT 1
/* Enable IPv6 support */
#define ZLDCONFIG_IPV6 1

#if defined(ZLDCONFIG_IPV6)
/* Enable IPv6 GLOBAL Switch */
#define ZLDCONFIG_IPV6_GLOBAL_SWITCH  1
#endif

#define ZLDCONFIG_GPIO_3_COLOR_LED 1

/* LED suppress support */
#define ZLDCONFIG_LED_SUPPRESS_MODE_SUPPORT 1
/* Hardware Control LED ON OFF*/
#undef ZLDCONFIG_LED_BUTTON_CONTROL

#ifdef ZLDCONFIG_LED_SUPPRESS_MODE_SUPPORT
#undef ZLDCONFIG_LED_SUPPRESS_DEFAULT_ON
#ifdef ZLDCONFIG_LED_BUTTON_CONTROL
#undef ZLDCONFIG_LED_SOFTWARE_CONTROL
#else
/* Software Control LED ON OFF*/
#define ZLDCONFIG_LED_SOFTWARE_CONTROL 1
#endif
#else
#undef ZLDCONFIG_LED_BUTTON_CONTROL
#undef ZLDCONFIG_LED_SOFTWARE_CONTROL
#endif

/* Locator LED Support */
#define ZLDCONFIG_LED_LOCATOR_SUPPORT 1

/* BLE Support */
#undef ZLDCONFIG_BLE_SUPPORT
#ifdef ZLDCONFIG_BLE_SUPPORT
#define ZLDSYSPARM_BEACON_MAX_NUM  5
#define ZLDSYSPARM_BEACON_TXPOWER 202
#endif

/*802.1Q VLAN untag member enhancement*/
#define ZLDCONFIG_8021Q_VLAN_ENHANCE_AP 1
#undef ZLDCONFIG_SWITCH_SW_VLAN
#define ZLDCONFIG_SWITCH_HW_VLAN 1
#undef ZLDCONFIG_SWITCH_IPQ807X_VLAN

/*****************************************************************************/
/* Create NetDevice for REMAP HW SWITCH PORT as SW PORTDEV                   */
/*****************************************************************************/
#undef ZLDCONFIG_SWITCHPORT_REMAP_DEV

/*Enable loop check*/
#undef ZLDCONFIG_WTP_WTP_LOOPGUARD

/* WLAN Monitor mode Enable */
#undef ZLDCONFIG_WLAN_MON_MODE_SERVER_SUPPORT
#undef ZLDCONFIG_WLAN_MON_MODE_CLIENT_SUPPORT

/* WLAN Rogue AP Detection Feature */
#define ZLDCONFIG_WLAN_RAD_AC_SUPPORT 1
#undef ZLDCONFIG_WLAN_RAD_WTP_SUPPORT

/* WLAN Frame Capture Feature*/
#undef ZLDCONFIG_WLAN_FRAME_CAPTURE_SERVER_SUPPORT
#undef ZLDCONFIG_WLAN_FRAME_CAPTURE_CLIENT_SUPPORT

/* WLAN AP-mode detection Feature */
#define ZLDCONFIG_WLAN_APMODE_RAPD_SERVER_SUPPORT 1
#define ZLDCONFIG_WLAN_APMODE_RAPD_CLIENT_SUPPORT 1

/* WLAN Dynamic Channel Selection Feature*/
#undef ZLDCONFIG_WLAN_DCS_AC_SUPPORT
#define ZLDCONFIG_WLAN_DCS_WTP_SUPPORT			1
#define ZLDCONFIG_WLAN_DCS_SCHEDULE_SUPPORT             1

/* WLAN SSID Schedule Feature*/
#define ZLDCONFIG_WLAN_SSID_SCHEDULE_SUPPORT    1

/* WLAN Band Select */
#undef ZLDCONFIG_WLAN_BAND_SELECT_AC_SUPPORT
#define ZLDCONFIG_WLAN_BAND_SELECT_WTP_SUPPORT	1

/* WLAN associate threshold rssi Feature*/
#define ZLDCONFIG_WLAN_RSSI_THRESHOLD			1
#define ZLDCONFIG_WLAN_RSSI_THRESHOLD_SUPPORT_IDLE_CHK 1
/*WLAN auto healing Feature*/
#undef ZLDCONFIG_WLAN_AUTO_HEALING_AC_SUPPORT			
#undef ZLDCONFIG_WLAN_AUTO_HEALING_WTP_SUPPORT

/* AP Load Balancing for AC*/
#define ZLDCONFIG_AP_LOAD_BALANCING_SERVER_SUPPORT		1
/* AP Load Balancing for WTP*/
#define ZLDCONFIG_AP_LOAD_BALANCING_CLIENT_SUPPORT		1

/* Legacy Station Rejection */
#define ZLDCONFIG_LEGACY_STA_REJECTION	1

/* Trap for net-snmp */
#define ZLDCONFIG_SNMP_TRAP		1
/* wireless hal for wireless driver */
#define ZLDCONFIG_WIRELESS_HAL_SUPPORT	1

/* WLAN Client Info Feature */
#define ZLDCONFIG_WLAN_CLIENT_INFO		1

/* WLAN AP proxy ARP */
#define ZLDCONFIG_WLAN_AP_PROXY_ARP  1

/* WLAN Station Info Collection Feature */
#define ZLDCONFIG_WLAN_STATION_INFO_COLLECTION	1

/* WLAN CSA internal optimization */
#define ZLDCONFIG_WLAN_CSA_INTEROP 1

/* WLAN 160MHz support */
#define ZLDCONFIG_WLAN_160MHZ_SUPPORT 1

/*remove OTP from login page*/
#undef ZLDCONFIG_WEBLOGIN_OTP
/*remove Wizard from login page*/
#define ZLDCONFIG_WEBLOGIN_WIZARD	1
/*external user cli and related function, include ext-group-user*/
#undef ZLDCONFIG_USER_EXT_USER_PWLAN_WORKAROUND
/*guest user default setting*/
#undef ZLDCONFIG_USER_GUEST_PWLAN_WORKAROUND
/*user group cli and related function*/
#undef ZLDCONFIG_USER_GROUP_PWLAN_WORKAROUND
/*user lease-time, users reauth-time, user access page and user login related setting. */
#undef ZLDCONFIG_USER_LOGIN_PWLAN_WORKAROUND

/*Workaround: remove aaa object*/
#define ZLDCONFIG_AAA_OBJECT_PWLAN_WORKAROUND	1
#undef ZLDCONFIG_AAA_OBJECT_AD_PWLAN_WORKAROUND
#undef ZLDCONFIG_AAA_OBJECT_LDAP_PWLAN_WORKAROUND

/* freeradius */
#define ZLDCONFIG_AAA_FREERADIUS			1
/*support for auth. server*/
#define ZLDCONFIG_AAA_FREERADIUS_AUTH_SERVER		1
/* FreeRADIUS AAA modified hack */
#define ZLDCONFIG_AAA_FREERADIUS_MODIFY 1
/*support for domain auth*/
#undef ZLDCONFIG_AAA_DOMAIN_AUTH
/* freeradius */
#define ZLDCONFIG_FREERADIUS_HOSTAPD_ATTRIBUTE		1
/*hostapd pmkcache notify to uam*/
#define ZLDCONFIG_AAA_FREERADIUS_UAM			1
/*weblogin without uam*/
#define ZLDCONFIG_LOGIN_WITHOUT_UAM			1
/*mac authentication*/
#define ZLDCONFIG_AAA_MAC_AUTH				1
/*mac authentication accounting support*/
#define ZLDCONFIG_AAA_MAC_AUTH_ACCOUNTING		1
/*mac authentication fallback*/
#undef ZLDCONFIG_MAC_AUTH_FALLBACK
/* NXC FreeRadius proxy with EAP message */
#define ZLDCONFIG_AAA_INTERNAL_EAP_PROXY		1
/* 802.1X accountung */
#define ZLDCONFIG_AAA_8021X_ACCOUNTING	1
/* Enable Dynamic Authorization Server (RFC5176, Included RID and CoA) */
#define ZLDCONFIG_AAA_DYNAMIC_AUTHORIZATION_SERVER		1
/* RADIUS accounting support*/
#define ZLDCONFIG_AAA_RADIUS_ACCT 1
/* RADIUS attr support */
#define ZLDCONFIG_RADIUS_ATTR_SUPPORT			1
/* Server host name FQDN Support */
#define ZLDCONFIG_AAA_HOST_FQDN_SUPPORT                 1
/* Free access support */
#undef ZLDCONFIG_AAA_FREE_ACCESS_SUPPORT
/* workaround method */
#define ZLDCONFIG_PWLAN_SYSTEM_WORKAROUND_SUPPORT	1
/* DTLS Tunnel support*/
#define ZLDCONFIG_TUNNEL_DTLS_SUPPORT		1
/* CAPWAP DATA FORWARD support */
#undef ZLDCONFIG_DATA_FORWARD_CLIENT_SUPPORT
/*Support muti WTP image upgrade methods */
#define ZLDCONFIG_WTP_IMAGE_UPGRADE_MUTI_METHODS	1

#undef ZLDCONFIG_DATA_FORWARD_SERVER_SUPPORT
/* CAPWAP WTP Logs support */
#undef ZLDCONFIG_CAPWAP_WTP_WTP_LOGS_SUPPORT
#undef ZLDCONFIG_CAPWAP_AC_WTP_LOGS_SUPPORT
/* CAPWAP WTP status support */
#define ZLDCONFIG_CAPWAP_WTP_STATUS_NOTIFY_SUPPORT	1
/* CAPWAP Local WLAN Support */
#undef ZLDCONFIG_CAPWAP_LOCAL_WLAN_SUPPORT
/* ZyKit, Common API in userspace */
#define ZLDCONFIG_ZYKIT 1
/* For single F/W multiple product */
#define ZLDCONFIG_MULTIPLE_PRODUCT 1
/* Enterprise WLAN Hybrid device start up operation */
#define ZLDCONFIG_ENTERPRISE_WLAN_HYBRID 1
/* Using Encryption Algorithm V2 for debug account */
#define ZLDCONFIG_DEBUG_ACCOUNT_ENHANCEMENT_V2 1

/* SNMPv3 support */
#define ZLDCONFIG_SNMPV3_SUPPORT	1
/* SNMPv2 support */
#undef ZLDCONFIG_SNMPV2_SUPPORT
/*SNMP down size*/
#define ZLDCONFIG_SNMP_DOWN_SIZE	1

/* Force Auth */
//#undef ZLDCONFIG_FORCE_AUTH_PWLAN_WORKAROUND
#define ZLDCONFIG_WLAN_SECURITY_PROFILE_EAP_AUTH_DEFAULT_EXTERNAL        1
#define ZLDCONFIG_FORCE_AUTH_PWLAN_WORKAROUND 1
/* address object */
#undef ZLDCONFIG_ADDRESS_OBJECT_PWLAN_WORKAROUND
/* service object, depend on ZLDCONFIG_VIRTUAL_SERVER_220 */
#undef ZLDCONFIG_SERVICE_OBJECT_PWLAN_WORKAROUND
/* schedule object, depend on ZLDCONFIG_APP_PATROL */
#undef ZLDCONFIG_SCHEDULE_OBJECT_PWLAN_WORKAROUND
/* No dashboard VD on GUI */
#define ZLDCONFIG_NO_VD_PWLAN_WORKAROUND 1
/* WTP image Post Action*/
#undef ZLDCONFIG_WTP_IMG_POST_ACTION
/* Single Firmware Update function*/
#undef ZLDCONFIG_SINGLE_FW_UPDATE
/* AP Firmware Unify*/
#define ZLDCONFIG_FIRMWARE_UNIFY	1
/*AC discovery in standalone mode*/
#define ZLDCONFIG_STANDALONE_AC_DISCOVERY	1
/* Save Self Image to WTP image*/
#undef ZLDCONFIG_KEEP_SELF_IMG_TO_WTP_IMG
/* Auto WTP image download*/
#undef ZLDCONFIG_AUTO_WTP_IMG_DOWNLOAD
/* Show LOGIN USERS in GUI Page */
#undef ZLDCONFIG_GUI_LOGIN_USERS_PWLAN_WORKAROUND
/* mix interface info for NWA-Serial */
#define ZLDCONFIG_AP_MIX_LAN 1

/*Enhance bridge name change to user define name*/
#define ZLDCONFIG_BRIDGE_USERDEFINE_NAME 1

/*hidden ge & vlan interface name*/
#define ZLDCONFIG_GE_INTERFACE_HIDDEN	1
#define ZLDCONFIG_VLAN_INTERFACE_HIDDEN	1

/* ProWLAN IPC support */
#define ZLDCONFIG_PROWLAN_IPC 1

/*ProWLAN Reset Utility Daemon*/
#define ZLDCONFIG_PROWLAN_RESD 1

/* Switch support ieee 802.3az */
#undef ZLDCONFIG_IEEE_8023AZ

/* force ksoftirqd */
#define ZLDCONFIG_FORCE_KSOFTIRQD 1

/* Enable ARP check on DHCP Client */
#define ZLDCONFIG_DHCP_CLIENT_ENABLE_ARP_CHECK	1

/* Real Time Location System */
#define ZLDCONFIG_RTLS_SUPPORT 1
/* RTLS for Ekahau */
#define ZLDCONFIG_RTLS_EKAHAU_SUPPORT 1

/* wireless debug for zysh */
#define ZLDCONFIG_ZYSH_WLAN_OP_DEBUG 1

/* No web console in GUI*/
#define	ZLDCONFIG_NO_WEB_CONSOLE	1
/*Hierachical token bucket Direct Queue*/
/*related code not include in kernek 2.6.31 yet.*/
#undef ZLDCONFIG_NO_HTB_DIRECT_QUEUE

/* Enable new Lirary for BM/MRD/MyZyXEL */
#define ZLDCONFIG_BMM 1
#define ZLDCONFIG_BMM_MTD 1

#if defined(ZLDCONFIG_WLAN_DCS_WTP_SUPPORT) || defined(ZLDCONFIG_WLAN_APMODE_RAPD_CLIENT_SUPPORT)
/* DCS need scan agent supoort */
#define ZLDCONFIG_SCAN_AGENT_WTP_SUPPORT 1
#endif

/* SMART MESH */
#define ZLDCONFIG_SMART_MESH_SUPPORT	1
/* ZyMesh */
#undef ZLDCONFIG_ZYMESH_SUPPORT
/* Wireless Bridge */
#define ZLDCONFIG_WIRELESS_BRIDGE_SUPPORT	1
/* Wireless Bridge Loop Detection */
#ifdef ZLDCONFIG_WLAN_4MAC_WDS_SUPPORT
#define ZLDCONFIG_WLAN_HY_FWD   1
#endif

#undef ZLDCONFIG_COREDUMP_IN_RAM
#undef ZLDCONFIG_COREDUMP_IN_DB

#undef ZLDSYSPARM_COREDUMP_FILE_QUOTA

/* install GDB on board and enable parse function */
#define ZLDCONFIG_WTP_GDB_SUPPORT	1

/* GUI cloud web help support */
#define ZLDCONFIG_GUI_CLOUD_WEB_HELP	1

/* Country Code */
#undef ZLDCONFIG_COUNTRY_CODE_AC
#define ZLDCONFIG_COUNTRY_CODE_AP		1

/* TX Power Debug (Enable the maximum power) */
#undef ZLDCONFIG_TX_POWER_DEBUG_AC
#define ZLDCONFIG_TX_POWER_DEBUG_AP		1

/* 802.11w support */
#define ZLDCONFIG_DOT11W_SUPPORT 1

/* WLAN Absolute Power Configuration */
#define ZLDCONFIG_WLAN_ABS_POWER_SUPPORT 1

/* WAR: clean station information soon upon wlandown */
#define ZLDCONFIG_STA_INFO_CLEAN_WAR 1

/* STA Deauth Disasso Information Enhancement */
#define ZLDCONFIG_STA_INFO_ENHANCEMENT	1

/* 802.11r support */
#define ZLDCONFIG_DOT11R_SUPPORT 1
/* Ratelimit support */
#define	ZLDCONFIG_WLAN_RATELIMIT_SUPPORT	1

/* DHCP option 82*/
#undef ZLDCONFIG_DHCP_OPTION_82_SUPPORT

/* openssl 1.1.1 n*/
#define ZLDCONFIG_OPENSSL_111_SUPPORT 1

/* DB support */
#define ZLDCONFIG_DB_SUPPORT 1

/* RRM support */
#define ZLDCONFIG_RRM_SUPPORT 1
#define ZLDCONFIG_WIRELESS_HAL_RRM_SUPPORT 1

/* DFS channel switch enhancement */
#define ZLDCONFIG_DFS_CHANNEL_SWITCH_ENHANCE 1

/* DFS channel select enhancement */
#define ZLDCONFIG_DFS_CHANNEL_SELECT_ENHANCE 1

/* DFS channel block forever */
#define ZLDCONFIG_DFS_CHANNEL_BLOCK_FOREVER 1
#define ZLDCONFIG_DFS_CHANNEL_BLOCK_WTP_SUPPORT 1

/* DOT11K_SUPPORT */
#define ZLDCONFIG_DOT11K_SUPPORT 1

/* ROAMING GROUP for roaming assistance SUPPORT */
#define ZLDCONFIG_ROAMING_GROUP 1

#define ZLDCONFIG_NEIGHBOR_COLLETOR 1

#define ZLDCONFIG_INITIAL_SETUP_SSID	1

/*Fallback SSID*/
#undef ZLDCONFIG_FALLBACK_SSID_SUPPORT

/*WPA3 support*/
#define ZLDCONFIG_WLAN_WPA3_SUPPORT 1

/* WLAN Thermal Control */
#define ZLDCONFIG_WLAN_THERMAL_CONTROL 1

/* Workaround: mu-mimo & smart antenna can not enable together on broadcom AP.
 * We will disable mu-mimo by default if this product support smart antenna.(ex: wac6303d-s)
 */
#undef ZLDCONFIG_MU_DISABLE_WORKAROUND

/*Wireless Health*/
#define ZLDCONFIG_WIRELESS_HEALTH_SUPPORT 1

/* Channel Utilization */
#define ZLDCONFIG_CHANNEL_INFO 1

/* Dynamic Personal PSK (DPPSK) support */
#undef ZLDCONFIG_WLAN_DPPSK_SUPPORT

#define ZLDCONFIG_IGNORE_COUNTRY_IE_SUPPORT	1

#define ZLDCONFIG_WLAN_RATE_CONTROL_SUPPORT	1

/*****************************************************************************/
/* Down size                                                */
/*****************************************************************************/
#undef ZLDCONFIG_FLASH_DOWN_SIZE
#define ZLDCONFIG_ZYLOG_DOWN_SIZE	1
#define ZLDCONFIG_KISMET_DOWN_SIZE	1
#define ZLDCONFIG_IPROUTE2_DOWN_SIZE	1
#define ZLDCONFIG_LIBPNG_DOWN_SIZE	1
#define ZLDCONFIG_EXPAT_DOWN_SIZE	1
#define ZLDCONFIG_SYSLOG_NG_DOWN_SIZE	1
#define ZLDCONFIG_HOSTAPD_DOWN_SIZE	1
#define ZLDCONFIG_PKI_DOWN_SIZE	1
#define ZLDCONFIG_GD_DOWN_SIZE	1
#define ZLDCONFIG_NTP_DOWN_SIZE	1
#define ZLDCONFIG_UAM_DOWN_SIZE	1
#define ZLDCONFIG_LIBXML_DOWN_SIZE	1
#define ZLDCONFIG_GMP_DOWN_SIZE	1

/* Json format info transfer from AP to AC */
#define ZLDCONFIG_INFO_TRANSFER_WTP_SUPPORT	1

/*****************************************************************************/
/* Multiboot & AP_RECOVERY Function                                                        */
/*****************************************************************************/
/* The MultiBoot and AP_RECOVERY only work with Atheros SoC platform for now */
#define ZLDCONFIG_MULTIBOOT_SUPPORT 1
#define ZLDCONFIG_AP_RECOVERY_SUPPORT 1

/* Reboot by HW Reset after firmware upgrade */
#define ZLDCONFIG_HARDWARE_REBOOT_SUPPORT 1

/*****************************************************************************/
/* ZDP & LLDP Function                                                       */
/*****************************************************************************/
#define ZLDCONFIG_ZDP					1
#define ZLDCONFIG_LLDP					1
#define ZLDCONFIG_LLDP_SUPPORT_RCD		1
#undef ZLDCONFIG_LLDP_POWER_VIA_MDI

/* Power Source Detection */
#undef ZLDCONFIG_POWER_SOURCE_CHANGE_DETECT

/* Force Override PoE full Power */
#undef ZLDCONFIG_OVERRIDE_FULL_POWER_SUPPORT

/*****************************************************************************/
/* ZWO FUNCTION                                                       */
/* at WTP, we only create xml for ZWO windows utility*/
/*****************************************************************************/
#ifdef ZLDCONFIG_SCAN_AGENT_WTP_SUPPORT
#define ZLDCONFIG_ZWO_WTP_SUPPORT 1
#endif
#undef ZLDCONFIG_ZWO_AC_SUPPORT

/*****************************************************************************/
/* System Debug Functions                                                    */
/*****************************************************************************/
#define ZLDCONFIG_DUMP_CONSOLE_MSG_TO_SSH_CLIENT	1

#ifdef ZLDCONFIG_CAPWAP_WTP_SUPPORT
#define ZLDCONFIG_WEB_PORTAL_REDIRECT_FROM_AP           1
#define ZLDCONFIG_MGMT_AP_SHARED_SECRET_SUPPORT		1
#else
#undef ZLDCONFIG_WEB_PORTAL_REDIRECT_FROM_AP
#endif
#ifdef ZLDCONFIG_WEB_PORTAL_REDIRECT_FROM_AP
#define ZLDCONFIG_WEB_PORTAL_LOGOUT_IP			1
#define ZLDSYSPARM_MAX_AP_AUTH_POLICY_RULE_PER_GROUP	8
#endif

/*****************************************************************************/
/* General System parameter                                                  */
/*****************************************************************************/
/* Platform */
#define ZLDCONFIG_PLATFORM_MIPSEL_MEDIATEK_MT7621       1
#define ZLDCONFIG_PLATFORM_MIPSEL_MEDIATEK_MT7621_FIXME       1
#define BOOT_MODULE_CHECKSUM_SUPPORT	1
#define ZLDCONFIG_BM_HTP_DRAM_DISABLE 1
#define ZLDCONFIG_BUSYBOX 1
#define ZLDCONFIG_LIBTIRPC 1

/* This flag used for device only have switch, like WAC6500 */
#define ZLDCONFIG_BOOTUP_NOLOOP 1
/* Manufacture */
#undef ZLDCONFIG_MFGCONFIG_SUPPORT
#define ZLDCONFIG_UBIFS_SUPPORT  1
#define ZLDCONFIG_NAND_SUPPORT  1
/* Board */
#define ZLDCONFIG_BOARD_NWA50AX 1
/* Model */
#define ZLDSYSPARM_PLATFORM_NAME "mt7621"
#define ZLDSYSPARM_PRODUCT_NAME "nwa50ax"
#define ZLDSYSPARM_PRODUCT_NAME1 "NWA50AX"
#define ZLDSYSPARM_PRODUCT_LINE_FAMILY_NAME ZLDSYSPARM_PRODUCT_NAME1
#define ZLDSYSPARM_PRODUCT_CNM "WAX"
#define ZLDSYSPARM_PRODUCT_MODEL "6BE1"
#define ZLDSYSPARM_PRODUCT_MAC_QTY 3
/* Compatible product models  */
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_NUM 5
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_0 "6BE1"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_1 "6FE1"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_2 "FFFF"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_3 "FFFF"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_4 "FFFF"
/* Compatible product models, only for file names as bm, nor */
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_0 "NWA50AX"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_1 "NWA55AXE"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_2 ""
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_3 ""
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_4 ""
/* Compatible product models, Max slot */
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_0 "03"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_1 "03"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_2 "00"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_3 "00"
#define ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_4 "00"
/* Supported hardware componets */
#define ZLDSYSPARM_CPU_CORE_NUM 4 /*$R*/

/* Supported DualImage*/
#define ZLDCONFIG_WTP_DUALIMAGE 1

/* Maximum Firmware Size*/
#define ZLDSYSPARM_MAX_FW_SIZE		(50 * 1024)
#define ZLDSYSPARM_MAX_FW_FTP_QUOTA	60000

/* turn on when use VITESSE VLAN switch */
#define ZLDCONFIG_BUILD_SWITCH_ENABLE 1
#define ZLDCONFIG_BUILD_MINIPCI 1

/* Storm Control for Ethernet */
#define ZLDCONFIG_ETH_STORM_CONTROL 1
#if defined(ZLDCONFIG_ETH_STORM_CONTROL)
/* the minimum settable storm rate (for PPS) */
#define ZLDSYSPARM_ETH_STORM_MIN_PPS_RATE		64
/* 0: no supoort, 1: by port, 2: by frame type */
#define ZLDSYSPARM_ETH_STORM_RATE_SETTING_CAPS		1
/* 0: no supoort, 1: by port, 2: by frame type */
#define ZLDSYSPARM_ETH_STORM_STORMING_GET_CAPS		0
#endif

#ifdef ZLDCONFIG_BOOTUP_NOLOOP
/* port1 = uplink, port2 = lan1 */
#define ZLDSYSPARM_BOOTUP_ENABLED_PORT	1
#endif

/* Extended Slot */
#define ZLDCONFIG_BUILD_MINIPCI_NUM		2
#define ZLDSYSPARM_BUILD_PCMCIA_NUM		0
#define ZLDSYSPARM_BUILD_USB_NUM		0
#define ZLDSYSPARM_PCMCIA_SLOT1_TO_BUSNUM       3
#define ZLDSYSPARM_PCMCIA_SLOT2_TO_BUSNUM       2
#define ZLDSYSPARM_PCMCIA_SLOT_INTERFACE_OFFSET 1

#undef ZLDCONFIG_BUILD_RTC

/* When we re-build zld_fsutils-lite for SoC platform, we will need this flag */
#define ZLDCONFIG_SUPPORT_NOR_STORAGE 1
#define ZLDSYSPARM_BOOT_DRIVE "/dev/mtdblock"
#define ZLD_FIXED_DISK_ID 1
#define ZLD_FIXED_DISK_VENDOR_ID "ZyXEL   "
#define ZLD_FIXED_DISK_PRODUCT_ID "ZyWALL_USG      "
#define ZLD_DISK_LOG_BLOCK_SIZE 2048
/* Sync zysh disk log buf same as kernel_config CONFIG_LOG_BUF_SHIFT */
#define ZLDSYSPARM_DISK_LOG_BUF_SHIFT 17

/* System maximum concurrent session support */
#define ZLDSYSPARM_MAX_CONN_SESSION		10000	/*$R*/
/* Boot Module code size */
#define ZLDSYSPARM_BM_CODE_SIZE (192*(1<<10))
/* GUI_REMOVE_EMAIL_REPORT_SUPPORT */
#define ZLDCONFIG_GUI_REMOVE_EMAIL_REPORT_SUPPORT 1
/* GUI Directory */
#define ZLDSYSPARM_GUI_DIR 	"/usr/local/zyxel-gui"
#define ZLDSYSPARM_GUI_VER	2
/* Softirq restart number */
#define ZLDSYSPARM_MAX_SOFTIRQ_RESTART	2
/* netdev_budget max read number */
#define ZLDSYSPARM_NETDEV_BUDGET_READ_MOSTLY	128
/* ntpdate_agent every N hour set crontab  */
#define ZLDSYSPARM_NTP_SYNC_PERIOD_HOUR 6
/*****************************************************************************/
/* IPv6 related parameter                                               	 */
/*****************************************************************************/
/* The dependency is ZLDCONFIG_IPV6 */
/* Interface parameter */
#define ZLDSYSPARM_MAX_STATIC_IPVVI_ADDRESS 1
#define ZLDSYSPARM_MAX_STATIC_IPVVI_ADDRESS_GATEWAY_LIST 1
#define ZLDSYSPARM_MAX_SLAAC_ADDRESS    16  /*$R*/
#define ZLDSYSPARM_MAX_SLAAC_GW_ADDRESS 16  /*$R*/
#define ZLDSYSPARM_MAX_DHCPVVI_ADDRESS  16  /*$R*/
/* RA daemon parameter */
#define ZLDSYSPARM_MAX_IPVVI_RA_OPTIONS_PREFIX 	4
#define ZLDSYSPARM_MAX_IPVVI_RA_OPTIONS_RDNS 	4
#define ZLDSYSPARM_MAX_IPVVI_RA_OPTIONS_ROUTE 	4
/* DHCP6 parameter */
#define ZLDSYSPARM_MAX_DHCP6_LEASE_OBJECT_NUM	1024
#define ZLDSYSPARM_MAX_DHCP6_REQUEST_OBJECT_NUM	1024
#define ZLDSYSPARM_MAX_DHCP6_PD_ADDRESS_NUM		ZLDSYSPARM_MAX_STATIC_IPVVI_ADDRESS
#define ZLDSYSPARM_MAX_DHCP6_PD_RA_NUM			ZLDSYSPARM_MAX_IPVVI_RA_OPTIONS_PREFIX
/*****************************************************************************/
/* Stream AV System parameter                                                */
/*****************************************************************************/
/* Maximum concurrent ZIP decompress session support */
#define AV_ZIP_MAX_SESSION          50
/* Maximum concurrent RAR-LZSS decompress session support */
#define AV_RAR_LZSS_MAX_SESSION     8
/* Maximum concurrent RAR-PPM decompress session support */
#define AV_RAR_PPM_MAX_SESSION      1
/* Maximum Zone-to-Zone rules */
#define AV_MAX_ZONE_TO_ZONE_RULE        32	/*$R*/
/* Maximum White List Rule */
#define AV_MAX_WHITE_LIST               256	/*$R*/
/* Maximum Black List Rule */
#define AV_MAX_BLACK_LIST               256	/*$R*/
/* Maximum WBL Pattern Length */
#define AV_MAX_WBL_PATTERN_LENGTH       80
/* Maximum Infected Statistics */
#define AV_MAX_STATISTICS               500
/* Maximum Statistics Ranking Results */
#define AV_MAX_STATISTICS_RANKING       10
/* Maximum Inspection Code Size: FULL (MB) */
#define	AV_MAX_FULL_INSPECTION_CODE_SIZE	24
/* Maximum Inspection Code Size: INCR (MB) */
#define	AV_MAX_INCR_INSPECTION_CODE_SIZE	1
/* Resoft enhancement, 0 for HW engine , 1 for SW engine */
#define ZLDSYSPARM_AV_FULL_ENGINE       1
#define ZLDSYSPARM_AV_INCR_ENGINE       1
/* Maximum Port Rule Number*/
#ifdef AV_CONFIGURABLE_PROTOCOL_PORT
#define AV_MAX_PROTOCOL_PORT_RULE               32
#endif

/*****************************************************************************/
/* Object System parameter                                                   */
/*****************************************************************************/
/* Maximum number of address object support */
#define ZLDSYSPARM_ADDRESS_OBJECT_MAX_NUM      100
/* Maximum number of address group support */
#define ZLDSYSPARM_ADDRESS_GROUP_MAX_NUM       25 
/* Maximum number of address object in one group.*/
#define ZLDSYSPARM_OBJECT_GROUP_MEMBER_MAX     64
/* Maximum number of service object support */
#define ZLDSYSPARM_SERVICE_OBJECT_MAX_NUM      200
/* Maximum number of service group support */
#define ZLDSYSPARM_SERVICE_GROUP_MAX_NUM       50
/* Maximum number of service object in one group.*/
#define ZLDSYSPARM_SERVICE_OBJECT_GROUP_MEMBER_MAX  64
/* Maximum number of schedule object support */
#define ZLDSYSPARM_SCHEDULE_OBJECT_MAX_NUM    16 
/* Maximum number of system built-in zone object support */
#define ZLDSYSPARM_SYSTEM_BUILTIN_ZONE_OBJECT_MAX_NUM     7 
/* Maximum number of user-define zone object support */
#define ZLDSYSPARM_USER_DEFINE_ZONE_OBJECT_MAX_NUM     8
/* Maximum number of zone object support */
#define ZLDSYSPARM_ZONE_OBJECT_MAX_NUM	ZLDSYSPARM_USER_DEFINE_ZONE_OBJECT_MAX_NUM

/*****************************************************************************/
/* Interface System parameter                                                */
/*****************************************************************************/
/* Maximum Physical Port support number */
#define ZLDSYSPARM_PHY_PORT_MAX_NUM       1
/* Maximum Ethernet Interface support number */
#define ZLDSYSPARM_ETH_IFACE_MAX_NUM      1
/* Maximum Virtual interface support number */
#define ZLDSYSPARM_VIR_IFACE_MAX_NUM      4
/* Maximum VLAN Interface support number */
#define ZLDSYSPARM_VLAN_IFACE_MAX_NUM     1
/* Maximum Bridge Interface support number */
#define ZLDSYSPARM_BRIDGE_IFACE_MAX_NUM   1
/* Maximum User Configurable PPP Interface support number */
#define ZLDSYSPARM_USER_PPP_IFACE_MAX_NUM  0
/* Maximum System PPP interface number */
#define ZLDSYSPARM_SYSTEM_PPP_IFACE_MAX_NUM  0
/* define First System PPP interface unit */
#define ZLDSYSPARM_SYSTEM_PPP_IFACE_START_NUM  1
/* Maximum PPP Interface support number (include user-define ppp and system-default ppp) */
#define ZLDSYSPARM_PPP_IFACE_MAX_NUM     	(ZLDSYSPARM_SYSTEM_PPP_IFACE_START_NUM + ZLDSYSPARM_SYSTEM_PPP_IFACE_MAX_NUM)
/* Maximum layer2 vlan support number*/
#if defined(ZLDCONFIG_SWITCH_SW_VLAN) || defined(ZLDCONFIG_SWITCH_HW_VLAN) || defined(ZLDCONFIG_SWITCH_IPQ807X_VLAN)
#define ZLDSYSPARM_LAYER2VLAN_MAX_NUM 4094
#endif

#if defined(ZLDSYSPARM_PHY_PORT_MAX_NUM) && (ZLDSYSPARM_PHY_PORT_MAX_NUM > 1)
#define ZLDCONFIG_AP_LAN_PROVISION 1
#else
#undef ZLDCONFIG_AP_LAN_PROVISION
#endif
/*****************************************************************************/
/* WLAN parameter                                                            */
/*****************************************************************************/
/* Madwifi driver support, depends on ZLDCONFIG_WLAN_ENABLE */
#undef ZLDCONFIG_WLAN_BUILD_MADWIFI_DRIVER
/* Atheros Fusion driver support, depends on ZLDCONFIG_WLAN_ENABLE */
#undef ZLDCONFIG_WLAN_BUILD_ATHEROS_DRIVER
#ifdef ZLDCONFIG_WLAN_BUILD_ATHEROS_DRIVER
/* Atheros driver version: 110 => 11.0, 102 => 10.2, 92 => 9.2, 73 => 7.3 */
#define ZLDSYSPARM_ATHEROS_DRIVER_VERSION	110
#endif
#define ZLDCONFIG_WLAN_BUILD_MTK_DRIVER 1
#define ZLDCONFIG_UBUS_SUPPORT 1

/* station mode support */
#undef ZLDSYSPARM_WLAN_STATION_SUPPORT
/* WDS mode support */
#undef ZLDSYSPARM_WLAN_WDS_SUPPORT
/* define available slots */
#define ZLDSYSPARM_WLAN_MAX_SLOT                (ZLDSYSPARM_BUILD_PCMCIA_NUM + ZLDCONFIG_BUILD_MINIPCI_NUM)
/* define max ap support on each slot */
#define ZLDSYSPARM_WLAN_MAX_AP                  8
/* define max mac filter table entry */
#define ZLDSYSPARM_WLAN_MAX_MAC_FILTER_ADDR     128
/* define US without DFS */
/* #define ZLDCONFIG_WLAN_USA_NODFS 1 */
/* define 802.11ac support */
#define ZLDCONFIG_WLAN_11AC_SUPPORT 1
/* define 802.11ax suport */
#define ZLDCONFIG_WLAN_11AX_SUPPORT 1
/* defone wpa3 enhanced-open transition mode max num*/
#define ZLDSYSPARM_WLAN_MAX_OWE 3
#define ZLDSYSPARM_MESH_MAX_AP 5
#define ZLDSYSPARM_WLAN_START_OWE (ZLDSYSPARM_WLAN_MAX_AP+ZLDSYSPARM_MESH_MAX_AP+1)
/* define max clients number */
#define ZLDSYSPARM_WLAN_MAX_CLIENT 		512
/*****************************************************************************/
/* WLAN Profile Based Setting                                                */
/*****************************************************************************/
/**/
#ifdef ZLDCONFIG_WLAN_PROFILE_ENABLE
#define ZLDSYSPARM_WLAN_RADIO_PROFILE_SUPPORT		64
#define ZLDSYSPARM_WLAN_MONITOR_PROFILE_SUPPORT		64
#define ZLDSYSPARM_WLAN_SSID_PROFILE_SUPPORT		64  /*$R*/
#define ZLDSYSPARM_WLAN_SECURITY_PROFILE_SUPPORT	64
#define ZLDSYSPARM_WLAN_MACFILTER_PROFILE_SUPPORT	64
#define ZLDSYSPARM_WLAN_MACFILTER_MAX_ENTRY		512
#ifdef ZLDCONFIG_WLAN_L2ISOLATION
#define ZLDSYSPARM_WLAN_L2ISOLATION_PROFILE_SUPPORT	16
#define ZLDSYSPARM_WLAN_L2ISOLATION_MAX_ENTRY		32
#endif
#ifdef ZLDCONFIG_GUEST_SSID_SUPPORT
#define ZLDSYSPARM_GUEST_SSID_PROFILE_SUPPORT        16
#define ZLDSYSPARM_GUEST_SSID_MAX_ENTRY                      32
#endif
#ifdef ZLDCONFIG_WLAN_4MAC_WDS_SUPPORT
#define ZLDSYSPARM_WLAN_WDS_PROFILE_SUPPORT		32
#endif
#endif

/*****************************************************************************/
/* WLAN WDS parameter                                                            						*/
/*****************************************************************************/
#ifdef ZLDCONFIG_WLAN_RADIO_PROFILE_WDS_SETTING
#define NUM_OF_WDS_LINK	5
#endif

/*******************************************************************************/
/* define maximum member in a bridge include all ethernet port , one vlan port(we only support one vlan in one bridge), all wlan interface.*/
#define ZLDSYSPARM_BRIDGE_MEMBER_MAX_NUM	(ZLDSYSPARM_ETH_IFACE_MAX_NUM + 1 +(ZLDSYSPARM_WLAN_MAX_SLOT*ZLDSYSPARM_WLAN_MAX_AP))

/*****************************************************************************/
/* DHCP Relay System parameter                                               */
/*****************************************************************************/
/* Maximum number of DHCP Relay per interface */
#define ZLDSYSPARM_DHCP_RELAY_NUM_PER_IFACE    2


/*****************************************************************************/
/* NAT System parameter                                                      */
/*****************************************************************************/
/* Maximum number of virtual server */
#define ZLDSYSPARM_VIRTUAL_SERVER_MAX_NUM      128 
/* Maximum number of trigger port */
#define ZLDSYSPARM_TRIGGER_PORT_PER_RULE       8	/*$R*/

/*****************************************************************************/
/* Route System parameter                                                    */
/*****************************************************************************/
/* Maximum number of policy route rule support */
#define ZLDSYSPARM_POLICY_ROUTE_MAX_NUM        100	/*$R*/

/* Maximum number of user configurable interface trunk support */
#define ZLDSYSPARM_USER_INTERFACE_TRUNK_MAX_NUM     2

/* Maximum number of system interface trunk support */
#define ZLDSYSPARM_SYSTEM_INTERFACE_TRUNK_MAX_NUM     1

/* Maximum number of interface trunk support */
#define ZLDSYSPARM_INTERFACE_TRUNK_MAX_NUM     (ZLDSYSPARM_USER_INTERFACE_TRUNK_MAX_NUM + ZLDSYSPARM_SYSTEM_INTERFACE_TRUNK_MAX_NUM)

/* Maximum number of static route rule support */
#define ZLDSYSPARM_STATIC_ROUTE_MAX_NUM        64 


/*****************************************************************************/
/* Firewall System parameter                                                 */
/*****************************************************************************/
/* Maximum number of firewall rule support */
#define ZLDSYSPARM_FIREWALL_RULE_MAX_NUM       500	/*$R*/

/*****************************************************************************/
/* Session Limit System parameter                                                 */
/*****************************************************************************/
/* Maximum number of firewall rule support */
#define ZLDSYSPARM_SESSION_LIMIT_RULE_MAX_NUM       500	/*$R*/

/*****************************************************************************/
/* VPN System parameter                                                      */
/*****************************************************************************/
/* Maximum number of VPN connection support after license upgrade */
#define ZLDSYSPARM_IPSEC_VPN_MAX_CONN          15	/*$R*/
/* Maximum number of VPN connection support without license upgrade */
#define ZLDSYSPARM_IPSEC_VPN_MAX_CONN_BASIC    ZLDSYSPARM_IPSEC_VPN_MAX_CONN
/* Maximum number of VPN concentrator */
#define ZLDSYSPARM_IPSEC_VPN_CONCENTRATOR_MAX_NUM  2
/* QuickSec version, 30 = QS 3.0, 44 = QS 4.4 */
#define ZLDSYSPARM_IPSEC_VPN_QS_VER		44

/*****************************************************************************/
/* Multi-login/UAM System parameter                                          */
/*****************************************************************************/
/* Max concurrent users */
#define ZLDSYSPARM_CON_USER_MAX_NUM            1034	/*$R*/
/* Max number of same username from different ip address */
/* Due to no matched definition symbol to ZLDSYSPARM_SAME_USER_MAX_NUM in current programs, comment out ZLDSYSPARM_SAME_USER_MAX_NUM temporarily. */
/* #define ZLDSYSPARM_SAME_USER_MAX_NUM           256 */
/* Max user name length */
#define ZLDSYSPARM_UAM_USER_NAME_LEN				64
#define ZLDSYSPARM_UAM_PASSWORD_LEN					64
/* Max cookie value length */
#define ZLDSYSPARM_UAM_UNIQUE_LEN					64
/* Max num of user roles for each user */
#define ZLDSYSPARM_UAM_USER_ROLES_PER_EXT_GROUP_USER 32

#undef	SSL_HW_ACCELERATOR

/* Support SSL VPN reverse proxy , current for GUI, code not used.*/
#undef ZLDCONFIG_SSLVPN_REVERSE_PROXY_SUPPORT
/* Support SSL VPN file sharing. , current for GUI, code not used.*/
#undef ZLDCONFIG_SSLVPN_FILE_SHARING_SUPPORT
#define ZLDSYSPARM_SSL_VPN_DEFAULT_ACTIVE_USERS		1
#define ZLDSYSPARM_SSL_VPN_MAX_ACTIVE_USERS		5
/* ZLDSYSPARM_SSL_VPN_MAX_SESSIONS = ZLDSYSPARM_SSL_VPN_MAX_ACTIVE_USERS * factor(3), the factor depends on product*/
#define ZLDSYSPARM_SSL_VPN_MAX_SESSIONS			15
#define ZLDSYSPARM_SSL_VPN_USER_NAME_LEN		(ZLDSYSPARM_UAM_USER_NAME_LEN)
#define ZLDSYSPARM_SSL_VPN_MAX_POLICY              16 /*$R*/
#define ZLDSYSPARM_SSL_VPN_MAX_POLICY_APPLICATION  8
#define ZLDSYSPARM_SSL_VPN_MAX_POLICY_NETWORK      4
#define ZLDSYSPARM_SSL_VPN_MAX_POLICY_USER         16
#define ZLDSYSPARM_SSL_VPN_MAX_APP                 64
#define ZLDSYSPARM_SSL_VPN_MAX_OWA_APP             1
#define ZLDSYSPARM_SSL_VPN_MAX_THREAD_NUMBER    3
#define ZLDSYSPARM_SSL_VPN_MIN_THREAD_NUMBER    1

/*****************************************************************************/
/* NAC System parameter                                       */
/*****************************************************************************/
#undef ZLDCONFIG_NAC
#define ZLDSYSPARM_NAC_MAX_POLICY              1024 /*$R*/

/*****************************************************************************/
/* PKI System parameter                                                      */
/*****************************************************************************/
/* Maximum size of certificate storage support */
#define ZLDSYSPARM_CERT_STORAGE_SIZE_LIMIT     64000
/* Max certificate name length */
#define ZLDSYSPARM_CERT_NAME_LEN				32


/*****************************************************************************/
/* The cacert.pem parameter                                                  */
/*****************************************************************************/
/* Build-in cacert.pem */
#define ZLDSYSPARM_BUILDIN_CACERT_PATH "/etc/zyxel/cert/cacert.buildin.pem"
/* Deployed cacert.pem */
#define ZLDSYSPARM_CACERT_PATH "/etc/zyxel/pikachu/cacert.pem"


/*****************************************************************************/
/* App Patrol System parameter                                               */
/*****************************************************************************/
/* Maximum allow port number */
#define ZLDSYSPARM_APP_PATROL_ALLOW_PORT_MAX   8
/* Maximum address pool number */
#define ZLDSYSPARM_APP_PATROL_MAX_ADDR_POOL    5000
/* Maximum default port number */
#define ZLDSYSPARM_APP_PATROL_DEFAULT_PORT_MAX 8
/* Maximum exception rule number */
#define ZLDSYSPARM_APP_PATROL_MAX_EXCEP_RULE   24	/*$R*/
/* Maximum other rule number */
#define ZLDSYSPARM_APP_PATROL_MAX_OTHER_RULE   24	/*$R*/
/* Maximum number of protocol support */
#define ZLDSYSPARM_APP_PATROL_MAX_PROTO_NUM    32
/* The deflaut value of classify packet check number*/
#define SYSTEM_DEFAULT_PACKET_CHECK 8

/*****************************************************************************/
/* AAA System parameter                                                      */
/*****************************************************************************/
/* Maximum LDAP group support */
#define ZLDSYSPARM_AAA_LDAP_GROUP_MAX_NUM      2 
/* Maximum LDAP server per group support */
#define ZLDSYSPARM_AAA_LDAP_SERVER_MAX_NUM     2
/* Maximum Radius group support */
#define ZLDSYSPARM_AAA_RADIUS_GROUP_MAX_NUM    2
/* Maximum radius server per group support */
#define ZLDSYSPARM_AAA_RADIUS_SERVER_MAX_NUM   2
/* Maximum AD group support */
#define ZLDSYSPARM_AAA_AD_GROUP_MAX_NUM        4
/* Maximum AD server per group support */
#define ZLDSYSPARM_AAA_AD_SERVER_MAX_NUM       2
/* Maximum authentication method support */
#define ZLDSYSPARM_AAA_AUTH_METHOD_MAX_NUM     4
/* RADIUS accounting interim update interval */
#define ZLDSYSPARM_AAA_DEF_ACCT_INTERIM_INT	600
#define ZLDSYSPARM_AAA_DEF_ACCT_INTERIM_STR	"600"
/* RADIUS accounting interim update interval in minutes */
#define ZLDSYSPARM_AAA_DEF_ACCT_INTERIM_MINUTE_STR	"10"

/*****************************************************************************/
/* Auth. Server parameter                                                     */
/*****************************************************************************/
/* Maximum Trusted Client */
#define ZLDSYSPARM_AUTH_SERVER_TRUSTED_CLIENT_MAX_NUM	32

/*****************************************************************************/
/* User Profile System parameter                                             */
/*****************************************************************************/
/* Maximum local user */
#define ZLDSYSPARM_LOCAL_USER_MAX_NUM          64
/* Maximum admin user */
#define ZLDSYSPARM_ADMIN_USER_MAX_NUM          5 
/* Maximum user group */
#define ZLDSYSPARM_USER_GROUP_MAX_NUM          16
/* Maximum user in one user group */
/* The current ZySH program use ZLDSYSPARM_LOCAL_USER_MAX_NUM to check this limitation, so comment out ZLDSYSPARM_MAX_USER_PER_GROUP temporarily. */
/* #define ZLDSYSPARM_MAX_USER_PER_GROUP          256 */

/*****************************************************************************/
/* Built-in service System parameter                                         */
/*****************************************************************************/
/* maximum dns address record */
#define ZLDSYSPARM_DNS_ADDR_RECORD_MAX_NUM      32
/* maximum dns domain zone forwarder */
#define ZLDSYSPARM_DNS_DOMAIN_ZONE_FORWARD_MAX_NUM 4 
/* maximum dns mx record */
#define ZLDSYSPARM_DNS_MX_RECORD_MAX_NUM       4 
/* maximum httpd processes */
#define ZLDSYSPARM_HTTP_PROCESS_MAX_NUM		62
/*****************************************************************************/
/* ZLD Web Server parameter                                                  */
/*****************************************************************************/

#define APACHE		1
#define LIGHTTPD	2

#define ZLDSYSPARM_HTTP_WEB_SERVER_PACKAGE	LIGHTTPD

/* WWW/SSH/TELNET/FTP/SNMP maximum service control entries */
/* ZLDSYSPARM_SERVICE_MAX_CONTROL_ENTRY has the same meaning as the ZLDSYSPARM_ACCESS_CONTROL_RULE_MAX_NUM, comment out ZLDSYSPARM_SERVICE_MAX_CONTROL_ENTRY temporarily. */
/* #define ZLDSYSPARM_SERVICE_MAX_CONTROL_ENTRY   16 */
#define ZLDSYSPARM_SNMP_INTERFACE_CACHE_TIMEOUT		300

/* maximum access control rule */
#define ZLDSYSPARM_ACCESS_CONTROL_RULE_MAX_NUM 8	/*$R*/
/* maximum number of DDNS profile */
#define ZLDSYSPARM_DDNS_PROFILE_MAX_NUM        5
/* Maximum dhcp network pool, vlan+brg+ethernet number */
#define ZLDSYSPARM_DHCP_NETWORK_POOL_MAX_NUM   ZLDSYSPARM_ETH_IFACE_MAX_NUM+ZLDSYSPARM_VLAN_IFACE_MAX_NUM+ZLDSYSPARM_BRIDGE_IFACE_MAX_NUM
/* Maximum dhcp host pool */
#define ZLDSYSPARM_DHCP_HOST_POOL_MAX_NUM     64 

/* available string values: rc4, aes, des, 3des */
/* If you want to define rc4 or aes or 3des as default cipher, you have to write down "rc4 aes 3des" */
#define ZLDSYSPARM_SSL_DEFAULT_CIPHER_SUITE		"aes des 3des"

#if defined(ZLDCONFIG_SNMPV3_SUPPORT)
#define ZLDSYSPARM_SNMP_V3USER_MAX_NUM		8
#define ZLDSYSPARM_SNMP_V3USER_PASSWD_MIN_LENGTH      8
#endif

/*****************************************************************************/
/* Centralize log  System parameter                                          */
/*****************************************************************************/
/* Maximum event log entry */
#define ZLDSYSPARM_EVENT_LOG_ENTRY_MAX_NUM     512
/* Maximum debug log entry */
#define ZLDSYSPARM_DEBUG_LOG_ENTRY_MAX_NUM     1
/* Maximum email server support */
#define ZLDSYSPARM_LOG_EMAIL_SERVER_SUPPORT    2	/*$R*/
/* Maximum syslog server support */
#define ZLDSYSPARM_LOG_SYSLOG_SERVER_SUPPORT   4	/*$R*/


/*****************************************************************************/
/* Traffic statistics System parameter                                       */
/*****************************************************************************/
/* Maximum number of report entry support */
#define ZLDSYSPARM_TRAFFIC_REPORT_MAX_ENTRY    20


/*****************************************************************************/
/* OSPF System parameter                                                     */
/*****************************************************************************/
/* Maximum OSPF area support */
#define ZLDSYSPARM_OSPF_AREA_MAX_NUM           16 

/*****************************************************************************/
/* Inbound Load Balancing parameter                                                     */
/*****************************************************************************/
/* Maximum service size */
#define ZLDSYSPARM_ILB_DNS_SVC_MAX_NUM        32	/*$R*/
/* Maximum destination size */
#define ZLDSYSPARM_ILB_DNS_DEST_MAX_NUM        8	/*$R*/

/*****************************************************************************/
/* ZLD watchdog parameter                                                     */
/*****************************************************************************/
#define ZLDCONFIG_WATCHDOG_SUPPORT 		1

#define ZLDCONFIG_LAST_BOOT_REASON_SUPPORT	1

/*****************************************************************************/
/* Auto recover daemon. Implement in app watch dog                           */
/*****************************************************************************/
#define ZLDCONFIG_APP_AUTO_RECOVER 1

/*****************************************************************************
 * Define White-Brand parameter for ODM
 ******************************************************************************/
/* 0 (default) : deactivate, 1 : activate */
#define ODM_CONFIG_ACTIVATE 0
/* Original Company Name : ZyXEL */
#define ODM_SYSPARM_COMPANY_NAME ""
/* Original Company Website : http://www.zyxel.com.tw */
#define ODM_SYSPARM_COMPANY_WEBSITE ""
/* Original Product Name : zw1050 */
#define ODM_SYSPARM_PRODUCT_NAME ""
/* Original Product Name1 : ZyWALL 1050 */
#define ODM_SYSPARM_PRODUCT_NAME1 ""
/* Original Product Series Name : ZyWALL */
#define ODM_SYSPARM_PRODUCT_SERIES_NAME "Device"
/* Original Product zone name : ZyWALL */
#define ODM_SYSPARM_PRODUCT_ZONE_NAME "Device"

/*
 *Original Register : myZyXEL.com
 *Since ODM_SYSPARM_REGIST_NAME may be with simplified chinese font, thus we remove
 *this item to apps/white-brand-1.0.0
 *#define ODM_SYSPARM_REGIST_NAME "TiGateway regist"
 */

/* Original Regist Server website : http://www.myZyXEL.com */
#define ODM_SYSPARM_REGIST_SERVER_WEBSITE ""
#define ODM_SYSPARM_REGIST_UPDATE_SERVER_WEBSITE ""

/*****************************************************************************/
/* ZLD CAPWAP parameter                                                     */
/*****************************************************************************/
/* 1 (default) : DTLS Tunnel , 0 : UDP Socket */
#define ZLDSYSPARM_CAPWAP_DTLS_SOCKET                   1
/* 0 (default) : AutoPSK , 1 : PSK , 2:CA*/
#define ZLDSYSPARM_CAPWAP_DTLS_SECURITY                 1
/* define max preferred controller number , used for failover feature*/
#define ZLDSYSPARM_CAPWAP_AC_PREFER_MAX_NUM             2

/* define max wtp number supported on the controller*/
#define ZLDSYSPARM_CAPWAP_WTP_MAX_NUM			24
/* define max unmanaged wtp number supported on the controller*/
#define ZLDSYSPARM_CAPWAP_WAIT_WTP_MAX_NUM		(ZLDSYSPARM_CAPWAP_WTP_MAX_NUM * 2)

/* define capwap client task event max number*/
#define ZLDSYSPARM_CAPWAP_TASKEVT_WM           100

/* define AC support model list */
#define ZLDSYSPARM_CAPWAP_AC_SUPPORT_MODEL_NAME_LIST	"(NWA3160-N|NWA3550-N|NWA3560-N)"
#define ZLDSYSPARM_CAPWAP_AC_SUPPORT_MODEL_NAME_HELP    "<NWA3160-N,NWA3550-N,NWA3560-N>"

/*****************************************************************************/
/* WLAN Monitor Mode parameter                                                            */
/*****************************************************************************/
#if defined(ZLDCONFIG_WLAN_RAD_AC_SUPPORT)||defined(ZLDCONFIG_WLAN_RAD_WTP_SUPPORT)
/* rogue ap detection support*/
#define ZLDCONFIG_WLAN_ROGUEAP_DETECTION_SUPPORT			1
/* rogue ap containment support */
#define ZLDCONFIG_WLAN_ROGUEAP_CONTAINMENT_SUPPORT		1
/* max devices for detected device list */
#define ZLDSYSPARM_WLAN_ROGUEAP_DETECTED_DEVICE_NUM		512
#define ZLDSYSPARM_WLAN_ROGUE_AP_NUM					64
#define ZLDSYSPARM_WLAN_FRIENDLY_AP_NUM					64

/* max ap for contained list*/
#define ZLDSYSPARM_WLAN_CONTAINED_MAC_NUM					256

/* max number of ssid keyword */
#define ZLDSYSPARM_WLAN_ROGUE_RULE_SSID_KEYWORD_NUM             10
#endif
#define ZLDSYSPARM_WLAN_FRAME_CAPTURE_MAX_SOURCE_NUM    240
#if defined(ZLDCONFIG_WLAN_FRAME_CAPTURE_SERVER_SUPPORT)
#define ZLDSYSPARM_WLAN_FRAME_CAPTURE_MAX_DIR_SIZE		50000	/* kilobytes */
#endif

/*****************************************************************************/
/* ZLD File Manage parameter                                                 */
/*****************************************************************************/

/*
 * Added by Router Hsieh(Router.Hsieh@zyxel.com.tw)
 * Date: 20120309
 * Comment:
 * Because now we have two packages for ftp daemon,
 * so I add new compile flag for product line leader 
 * to chose which package should be used on their product.
 * Besides, I also add new compile flag for all ZyXEL hacking part
 * on pure-ftpd
 * 
 * Known issue:
 * 1. pure-ftpd`s tls may not work properly for device HA(20120412)
 */
  
#define ZLDCONFIG_FILEMANAGE_SUPPORT 1

#define ZLDCONFIG_SUPPORT_SHOW_SYS_FILE			1

/* Decide whether AC transfers configuration of SNMP*/
#define ZLDCONFIG_WTP_SUPPORT_SNMP_PROVISION 1

/*****************************************************************************/
/* ZOD & LLDP parameter                                                      */
/*****************************************************************************/
#if defined(ZLDCONFIG_LLDP)
/* RCD Parameters:Wait(W) */
#define ZLDSYSPARM_LLDP_RCD_WAIT            23
/* RCD Parameters:Retransmit(X) */
#define ZLDSYSPARM_LLDP_RCD_RETRANSMIT      20
#define ZLDSYSPARM_LLDP_TX_INTERVAL         30
#define ZLDSYSPARM_LLDP_TX_HOLD             4
#define ZLDSYSPARM_LLDP_TOLERANCE_TIME      16

#if defined(ZLDCONFIG_LLDP_POWER_VIA_MDI)
#define ZLDSYSPARM_LLDP_POE_PORT            "eth0"
#endif

#endif

#define ZLDCONFIG_WTP_SAVE_CONFIG	1

/* Periodic Memory check support */
#define ZLDCONFIG_MEMCHECK_SUPPORT          1

#ifdef ZLDCONFIG_WLAN_STATION_INFO_COLLECTION
#define ZLDSYSPARM_WLAN_SIC_INTERVAL    1
#define ZLDSYSPARM_WLAN_SIC_NUMBER      1
#define ZLDSYSPARM_WLAN_SIC_TYPE        1
#endif

#define ZLDCONFIG_ROAMING_LOG_SUPPORT 1

#ifdef ZLDCONFIG_ROAMING_GROUP
#define ZLDSYSPARM_ROAMING_GROUP_LEN    15
#endif

#define ZLDCONFIG_CLOUD_MODE_SUPPORT 1

#if defined(ZLDCONFIG_CLOUD_MODE_SUPPORT)
#define ZLDSYSPARM_CERT_DEV "/etc/zyxel/pikachu/nebula.cert"
#define ZLDSYSPARM_ETC_WRITABLE_ZYXEL_CFG_DIR "/etc/zyxel/ftp/nebula"
#define ZLDSYSPARM_NEBULA_NC_RUNNING_CFG_BACKUP_DIR "/etc/zyxel/ftp/netopeer"
#define ZLDSYSPARM_NEBULA_NC_RUNNING_CFG_DIR "/var/netopeer/netopeer"
#define FORIEGN_AUTHENTICATED_STA_PATH "/tmp/sta_lists/foreign-auth-sta.txt"
/* NTP UPDATE RETRY */
#define ZLDCONFIG_NEBULA_NTP_UPDATE_RETRY 1
/* NTP PROTECT */
#define ZLDCONFIG_NEBULA_NTP_PROTECT 1
/* DROPPED LOG */
#define ZLDCONFIG_ZYLOG_DROPPED_COUNT 1
/* DHCP SNIFFER */
#define ZLDCONFIG_DHCP_SNIFFER_SUPPORT 1
/* ZYLOG MAX MESSAGE LENGTH */
#define ZLDCONFIG_ZYLOG_MAX_MESSAGE_LEN 512
/* Get User Info from UAM and Sent it to NCC */
#define ZLDCONFIG_SEND_USER_INFO_TO_NCC 1
/* Nebula_remote_debug */
#define ZLDCONFIG_NEBULA_REMOTE_SUPPORT 1
#endif /* ZLDCONFIG_CLOUD_MODE_SUPPORT */

#undef ZLDCONFIG_AAA_IPV6_SUPPORT
#define AAA_WEB_PORTAL  1
#define AAA_8021X_CLOUD_AUTHENTICATION  1
#ifdef AAA_WEB_PORTAL
#define ZLDSYSPARM_AAA_WEB_PORTAL_SLOT_BASE_OFFSET  10000
#define ZLDSYSPARM_AAA_WEB_PORTAL_HTTP_OFFSET              80
#define ZLDSYSPARM_AAA_WEB_PORTAL_HTTPS_OFFSET           443
#define ZLDSYSPARM_AAA_WEB_PORTAL_MARK_NUMBER       4100
#define ZLDSYSPARM_AAA_WEB_PORTAL_MARK_SLOT_INDEX_OFFSET	50
#define WHITELIST_STA_PATH_SLOT1 "/tmp/sta_lists/whitelist-sta-slot1.txt"
#define WHITELIST_STA_PATH_SLOT2 "/tmp/sta_lists/whitelist-sta-slot2.txt"
#define ZLDCONFIG_AAA_WALLED_GARDEN_SUPPORT 1
#endif

#ifdef ZLDCONFIG_AAA_WALLED_GARDEN_SUPPORT
#define ZLDSYSPARM_WALLED_GARDEN_PROFILE_SUPPORT        16
#define ZLDSYSPARM_WALLED_GARDEN_MAX_ENTRY                      32
#endif

#ifdef AAA_WEB_PORTAL
#define ZLDCONFIG_SOCIAL_LOGIN_SUPPORT          1
#define ZLDCONFIG_NEBULA_PORTAL_ACCOUNTING_SUPPORT	1
#define ZLDCONFIG_WEB_PORTAL_LIMIT_SUPPORT	1
#define ZLDCONFIG_FB_WIFI			1
#define ZLDCONFIG_ORIGINAL_URL		1
#define ZLDCONFIG_MULTI_FACTOR_AUTHENTICATION_SUPPORT	1
#undef ZLDCONFIG_FINDME_URL
#define ZLDCONFIG_FINDME_URL_MARK_NUMBER	4200
#define ZLDCONFIG_LOGOUT_IP_MARK_NUMBER		4400
#endif

#ifdef AAA_WEB_PORTAL
#define ZLDSYSPARM_WLAN_CAPTIVE_PROFILE_SUPPORT 64
#define ZLDSYSPARM_WLAN_WHITELIST_PROFILE_SUPPORT       64
#define ZLDSYSPARM_WLAN_CAPTIVE_PARAMETER_PROFILE_SUPPORT	32
/*whitelist mac entry*/
#define ZLDSYSPARM_WLAN_WHITELIST_MAX_ENTRY             256
#endif

#define ZLDCONFIG_AP_FACTORY_DEFAULT_SUPPORT   1

#ifdef ZLDCONFIG_CAPWAP_WTP_SUPPORT
/* Use CAPWAP timer to implement this fearute */
#define ZLDCONFIG_DEBUG_SYS_CMD 1
#endif

/* UTF-8 SSID support */
#define ZLDCONFIG_UTF8_SSID_SUPPORT		1

/* NAT&DHCP sever support */
#define ZLDCONFIG_SSID_NAT_SUPPORT		1

/* Zyxel hacks in Linux-PAM */
#define ZLDCONFIG_LINUX_PAM_MODIFICATION	1

/* Third radio support */
/* scan on third radio, no-beaconap */
#undef ZLDCONFIG_THIRD_RADIO_SUPPORT
/* zero-wait dfs support */
#undef ZLDCONFIG_ZERO_WAIT_DFS_SUPPORT

#define ZLDCONFIG_AP_LOAD_BALANCING_GROUP_SUPPORT 1
#ifdef ZLDCONFIG_AP_LOAD_BALANCING_GROUP_SUPPORT
#define LOADBALANCING_GROUP_NUM 2
#define LOADBALANCING_GROUP_LEN 32
#endif

#undef ZLDCONFIG_INIT_OPENRC

/*****************************************************************************/
/* AAA Table parameter                                                       */
/*****************************************************************************/
/* Max VAP number */
#define ZLDSYSPARM_WLAN_AAA_MAX_VAP (ZLDSYSPARM_WLAN_MAX_AP+ZLDSYSPARM_MESH_MAX_AP+ZLDSYSPARM_WLAN_MAX_OWE)

#undef ZLDCONFIG_ENCRYPTED_WPA_PSK

#define ZLDCONFIG_WAR_NCC_MISCONFIGURED 1
#ifdef ZLDCONFIG_WAR_NCC_MISCONFIGURED
#define DISABLE_WAR_NCC_MISCONFIGURED "/tmp/disable_war_ncc_misconfigured"
#endif

#define ZLDCONFIG_GUI_BASIC_FEATURE_SUPPORT 1

#define ZLDCONFIG_PACKET_CAPTURE_SUPPORT                1
#ifdef ZLDCONFIG_PACKET_CAPTURE_SUPPORT
/* Packet capture on GUI */
#undef ZLDCONFIG_PCAP_MONITOR
/* WTP Packet capture on GUI*/
#undef ZLDCONFIG_PCAP_MONITOR_WTP
/* Remote Packet capture support */
#define ZLDCONFIG_REMOTE_CAPTURE_SUPPORT                1
/* Wireless Packet capture support */
#undef ZLDCONFIG_WIRELESS_CAPTURE_SUPPORT
#ifdef ZLDCONFIG_WIRELESS_CAPTURE_SUPPORT
/* The interface is used to capture 24G wireless packet. */
#define ZLDSYSPARM_WIRELESS_CAPTURE_INTERFACE_1         "radiotap0"
/* The interface is used to capture 5G wireless packet. */
#define ZLDSYSPARM_WIRELESS_CAPTURE_INTERFACE_2         "radiotap2"
#endif
#endif

#define ZLDCONFIG_MD5_SUPPORT 1

#define ZLDCONFIG_NEBULA_AP_SUPPORT 1

/* Iperf */
#define ZLDCONFIG_IPERF_SUPPORT 1

#endif /* end of __ZLD_PRODUCT_SPEC_H */
