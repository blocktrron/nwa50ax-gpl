include $(TOPDIR)/rules.mk

PKG_NAME:=cron
PKG_VERSION:=3.0pl1-128
PKG_LICENSE:=Paul-Vixie's-license

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=common
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)

define Package/cron
  $(eval $(ProWLAN/Package/Default))
  TITLE:=process scheduling daemon
  URL:=https://salsa.debian.org/debian/cron
endef

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/cron/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cron $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/crontab $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/etc/init.d/cron $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/etc/cron.d
	$(INSTALL_DIR) $(1)/var/zyxel
	$(INSTALL_DATA) ./files/etc/crontab $(1)/var/zyxel/crontab
	$(LN) /var/zyxel/crontab $(1)/etc/crontab
endef

$(eval $(call BuildPackage,cron))
