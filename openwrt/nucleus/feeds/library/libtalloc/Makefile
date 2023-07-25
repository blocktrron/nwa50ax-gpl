include $(TOPDIR)/rules.mk

PKG_NAME:=libtalloc
PKG_VERSION:=2.1.14
MAJOR_VERSION:=2
PKG_BUILD_PARALLEL:=0
PKG_LICENSE:=LGPL-3.0+

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=aaa
PROWLAN_PKG_NAME:=talloc-$(PKG_VERSION)

define Package/libtalloc
  $(eval $(ProWLAN/Package/Default))
  TITLE:=talloc Library
  URL:=https://talloc.samba.org/talloc/doc/html/index.html
endef

TARGET_CFLAGS += $(FPIC)

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); \
		$(CONFIGURE_VARS) \
		./buildtools/bin/waf configure \
		--prefix=/usr \
		--sysconfdir=/etc \
		--localstatedir=/var \
		--cross-compile \
		--cross-answers=$(PKG_BUILD_DIR)/answers.txt \
		--disable-python \
		--disable-rpath \
		--disable-rpath-install \
		--without-gettext \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/bin/default/libtalloc.so $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_BUILD_DIR)/bin/default/talloc.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libtalloc/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/bin/default/libtalloc.so $(1)/usr/lib/libtalloc.so.$(MAJOR_VERSION)
	(cd $(1)/usr/lib; ln -sf libtalloc.so.$(MAJOR_VERSION) libtalloc.so)
endef

$(eval $(call BuildPackage,libtalloc))
