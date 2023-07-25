include $(TOPDIR)/rules.mk

PKG_NAME:=libxml2
PKG_VERSION:=2.9.8
PKG_LICENSE:=MIT

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=0

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk

include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common


define Package/libxml2
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Gnome XML library
  URL:=http://xmlsoft.org/
  DEPENDS:=+libpthread +zlib
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-static \
	--without-debug \
	--without-python \
	--without-iconv \
	--without-docbook \
	--without-catalog \
	--without-ftp \
	--enable-ipv6=no \
	--without-lzma \
	--without-http \
	--without-icu \
	--with-zlib=$(STAGING_DIR)/usr \
	--without-lzma

HOST_CONFIGURE_ARGS += \
	--enable-shared \
	--disable-static \
	--with-c14n \
	--without-catalog \
	--with-debug \
	--without-docbook \
	--with-html \
	--without-ftp \
	--without-http \
	--without-iconv \
	--without-iso8859x \
	--without-legacy \
	--with-output \
	--without-pattern \
	--without-push \
	--without-python \
	--with-reader \
	--without-readline \
	--without-regexps \
	--with-sax1 \
	--with-schemas \
	--with-threads \
	--with-tree \
	--with-valid \
	--with-writer \
	--with-xinclude \
	--with-xpath \
	--with-xptr \
	--with-zlib \
	--without-lzma

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
	$(Build/Patch)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(2)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/xml2-config $(2)/bin/
	$(SED) 's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/usr,g' $(2)/bin/xml2-config

	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/libxml2 $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxml2.so* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/cmake/libxml2
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/cmake/libxml2/libxml2-config.cmake \
		$(1)/usr/lib/cmake/libxml2

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libxml-2.0.pc $(1)/usr/lib/pkgconfig/

	$(INSTALL_DIR) $(2)/share/aclocal/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/aclocal/* $(2)/share/aclocal
endef

define Package/libxml2/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libxml2.so* $(1)/usr/lib/
endef

define Host/Install
	$(SED) 's,^\(prefix\|exec_prefix\)=.*,\1=$(STAGING_DIR)/usr,g' $(HOST_BUILD_DIR)/xml2-config
	$(call Host/Install/Default)
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libxml2))
