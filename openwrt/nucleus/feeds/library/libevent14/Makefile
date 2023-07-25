include $(TOPDIR)/rules.mk

PKG_NAME:=libevent14
PKG_VERSION:=1.4.15
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=libevent-release-$(PKG_VERSION)-stable
PROWLAN_REPO:=common

define Package/libevent14
  $(eval $(ProWLAN/Package/Default))
  TITLE:=libevent (v1.4)
  URL:=http://libevent.org/
endef

TARGET_CFLAGS += $(FPIC) -Wno-unused

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

define Package/libevent14/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(RM) $(1)/usr/lib/*.{a,la}
endef

$(eval $(call BuildPackage,libevent14))
