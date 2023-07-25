include $(TOPDIR)/rules.mk
PKG_NAME:=zyxel-bind
PKG_VERSION:=9.2.3
PKG_LICENSE:=ISC

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=common
PROWLAN_PKG_NAME:=_bind-9.2.3_no_change

define Package/zyxel-bind
  $(eval $(ProWLAN/Package/Default))
  TITLE:=ProWLAN zyxel-bind no change
  URL:=https://www.isc.org/bind/
endef

PKG_INSTALL:=1

CONFIGURE_ARGS += \
	--with-randomdev=/dev/random \
	CFLAGS="-Os -I$(STAGING_DIR)/usr/include" \
	LDFLAGS="-L$(STAGING_DIR)/usr/lib"


define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/zyxel-bind/install
	$(INSTALL_DIR) $(1)/usr/local/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/dig/nslookup $(1)/usr/local/bin
endef

$(eval $(call BuildPackage,zyxel-bind))
