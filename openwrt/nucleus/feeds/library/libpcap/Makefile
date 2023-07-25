include $(TOPDIR)/rules.mk

PKG_NAME:=libpcap
PKG_VERSION:=1.9.0
PKG_LICENSE:=BSD

PKG_FIXUP:=patch-libtool

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/libpcap
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Low-level packet capture library
  URL:=http://www.tcpdump.org/
endef

TARGET_CFLAGS += \
	-ffunction-sections \
	-fdata-sections

CONFIGURE_VARS += \
	ac_cv_linux_vers=$(LINUX_VERSION) \
	ac_cv_header_libusb_1_0_libusb_h=no \
	ac_cv_netfilter_can_compile=no

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-yydebug \
	--with-pcap=linux \
	--without-septel \
	--without-dag \
	--without-libnl \
	--without-snf \
	--disable-can \
	--disable-canusb \
	--disable-dbus \
	--disable-bluetooth \
	--enable-remote=yes

ifeq ($(CONFIG_IPV6),y)
CONFIGURE_ARGS += \
	--enable-ipv6
endif

MAKE_FLAGS += \
	CCOPT="$(TARGET_CFLAGS) -I$(BUILD_DIR)/linux/include"

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
	$(Build/Patch)
endef

define Build/Configure
	$(call Build/Configure/Default)
	$(if $(CONFIG_PCAP_HAS_USB),,$(SED) '/^#define PCAP_SUPPORT_USB/D' $(PKG_BUILD_DIR)/config.h)
	$(if $(CONFIG_PCAP_HAS_USB),,$(SED) 's/pcap-usb-linux.c *//' $(PKG_BUILD_DIR)/Makefile)
	$(if $(CONFIG_PCAP_HAS_BT),,$(SED) '/^#define PCAP_SUPPORT_BT/D' $(PKG_BUILD_DIR)/config.h)
	$(if $(CONFIG_PCAP_HAS_BT),,$(SED) 's/pcap-bt-linux.c *//' $(PKG_BUILD_DIR)/Makefile)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/pcap* $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpcap.{a,so*} $(1)/usr/lib/
endef

define Package/libpcap/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpcap.so.* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/rpcapd $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,libpcap))
