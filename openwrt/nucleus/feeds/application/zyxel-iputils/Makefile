include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-iputils
PKG_VERSION:=20180629
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=nebula-apps

TARGET_CFLAGS += -D_GNU_SOURCE

define Package/zyxel-iputils
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Zyxel iputils package
  URL:=http://www.skbuff.net/iputils/
endef

MAKE_FLAGS += CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS) $(TARGET_LDFLAGS)"

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/zyxel-iputils/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_SUID) $(PKG_BUILD_DIR)/ping $(1)/usr/sbin/
	$(INSTALL_SUID) $(PKG_BUILD_DIR)/tracepath $(1)/usr/sbin/
ifeq ($(ZLDCONFIG_IPV6),1)
	$(INSTALL_SUID) $(PKG_BUILD_DIR)/traceroute6 $(1)/usr/sbin/
endif
endef

$(eval $(call BuildPackage,zyxel-iputils))
