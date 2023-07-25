include $(TOPDIR)/rules.mk

PKG_NAME:=libgcgi
PKG_VERSION:=0.9.5
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=LGPL

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=libgcgi.a-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/libgcgi
  $(eval $(ProWLAN/Package/Default))
  TITLE:=GNU CGI Library in C
  URL:=http://catchen.org/gcgi/
endef

TARGET_CFLAGS += $(FPIC) -Wno-unused -std=gnu89

CONFIGURE_ARGS += --enable-shared --disable-static

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
endef

define Package/libgcgi/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(RM) $(1)/usr/lib/*.{a,la}
endef

$(eval $(call BuildPackage,libgcgi))
