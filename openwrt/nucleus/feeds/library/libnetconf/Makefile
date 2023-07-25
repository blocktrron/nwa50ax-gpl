include $(TOPDIR)/rules.mk

PKG_NAME:=libnetconf
PKG_VERSION:=0.10.0
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=nebula-apps
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)

define Package/libnetconf
  $(eval $(ProWLAN/Package/Default))
  TITLE:=ProWLAN nebula library
  URL:=https://github.com/CESNET/libnetconf
  DEPENDS:=+zykit +libcurl +libxml2 +libxslt +zld-files
endef

CONFIGURE_ARGS += \
	--disable-libssh \
	--enable-tls

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(INSTALL_DIR) $(2)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/lnctool $(2)/usr/bin/lnctool
endef

define Build/Install
	$(call Build/Install/Default,install-bin)
	$(call Build/Install/Default,install-devel)
endef

define Package/libnetconf/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libnetconf.so* $(1)/usr/lib
	$(INSTALL_DIR) $(1)/var/libnetconf/libnetconf
	$(CP) $(PKG_INSTALL_DIR)/usr/share/libnetconf/{rnglib,xslt} $(1)/var/libnetconf/libnetconf
	$(INSTALL_DIR) $(1)/var/lib
	$(CP) $(PKG_INSTALL_DIR)/var/lib/libnetconf $(1)/var/lib
endef

$(eval $(call BuildPackage,libnetconf))
