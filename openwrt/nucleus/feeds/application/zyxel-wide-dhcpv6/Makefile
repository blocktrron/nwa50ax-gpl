include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-wide-dhcpv6
PKG_VERSION:=20080615
PKG_LICENSE:=BSD

PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)
PROWLAN_REPO:=common

define Package/zyxel-wide-dhcpv6
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Zyxel DHCP client application for IPv6
  URL:=https://sourceforge.net/projects/wide-dhcpv6/
  DEPENDS:=+zld-files
endef

TARGET_CFLAGS:=-D_GNU_SOURCE

CONFIGURE_VARS += \
	ac_cv_func_setpgrp_void=yes \

CONFIGURE_ARGS += \
	LEX="flex --noyywrap" \

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/zyxel-wide-dhcpv6/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dhcp6c $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dhcp6c-script $(1)/etc
endef

$(eval $(call BuildPackage,zyxel-wide-dhcpv6))
