include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-lldpd
PKG_VERSION:=0.7.8
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=ISC

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=management
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)

define Package/zyxel-lldpd
  $(eval $(ProWLAN/Package/Default))
  TITLE:=ProWLAN zyxel-lldpd
  URL:=https://lldpd.github.io/
  DEPENDS:=+zykit +libiface_generic
ifeq ($(ZLDCONFIG_LLDP_POWER_VIA_MDI), 1)
  DEPENDS+=+power_source_detect
endif
endef

TARGET_LDFLAGS += -lzykit -liface_generic
ifeq ($(ZLDCONFIG_LLDP_POWER_VIA_MDI), 1)
TARGET_LDFLAGS += -lpower_util
endif

CONFIGURE_PREFIX:=/usr/local

CONFIGURE_ARGS += \
	--enable-privsep=no \
	--with-privsep-group=root \
	--with-privsep-user=root \
	--with-xml=no \
	--without-readline \
	--enable-cdp=no \
	--enable-fdp=no \
	--enable-edp=no \
	--enable-sonmp=no \

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/local/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/* $(1)/usr/lib
endef

define Package/zyxel-lldpd/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/liblldpctl.so* $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/local/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/local/sbin/* $(1)/usr/local/sbin
endef

$(eval $(call BuildPackage,zyxel-lldpd))
