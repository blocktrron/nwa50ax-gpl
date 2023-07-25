include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-dhcpcd
PKG_VERSION:=1.3.22-pl4
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/zyxel-dhcpcd
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Zyxel dhcpcd
  URL:=http://www.phystech.com/ftp/
  DEPENDS:=+zld-files +zylog
endef


MAKE_FLAGS := \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	CPPFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS) -lzysh_log"


define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef


define Package/zyxel-dhcpcd/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_DIR) $(1)/etc/dhcpc
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/dhcpcd $(1)/sbin
	( cd $(PKG_BUILD_DIR) && \
		sh dhcpcd.exe.tmpl \
	)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dhcpcd.exe $(1)/etc/dhcpc
endef

$(eval $(call BuildPackage,zyxel-dhcpcd))
