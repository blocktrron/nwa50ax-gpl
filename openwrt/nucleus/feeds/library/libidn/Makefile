include $(TOPDIR)/rules.mk

PKG_NAME:=libidn
PKG_VERSION:=1.35
PKG_LICENSE:=GPL-2.0+

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/idn/Default
  $(eval $(ProWLAN/Package/Default))
endef

define Package/idn
  $(call Package/idn/Default)
  SUBMENU:=application
  TITLE:=GNU IDN (Internationalized Domain Name) tool
  URL:=http://www.gnu.org/software/libidn/
  DEPENDS:=+libidn
endef

define Package/libidn
  $(call Package/idn/Default)
  TITLE:=Stringprep, Punycode and IDNA implementation
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--enable-shared=yes \
	--enable-static=no \
	--disable-largefile \
	--disable-tld \
        --disable-rpath \
        --disable-doc \
	--disable-nls

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
	$(Build/Patch)
	(cd $(PKG_BUILD_DIR); \
		find -name 'iconv_*.h' -exec touch {} + ; \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libidn.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libidn.pc $(1)/usr/lib/pkgconfig/
endef

define Package/idn/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
endef

define Package/libidn/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libidn.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libidn))
