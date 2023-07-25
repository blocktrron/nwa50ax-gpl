include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-dnsmasq
PKG_VERSION:=2.85
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/zyxel-dnsmasq
  $(eval $(ProWLAN/Package/Default))
  TITLE:=A DNS and DHCP server
  URL:=http://www.thekelleys.org.uk/dnsmasq/doc.html
  DEPENDS:=+ipset +zylog +zld-files +libiface_generic
endef

COPTS:= \
	-DNO_DHCP6 \
	-DNO_AUTH \
	-DNO_ID \
	-DNO_TFTP \
	-DHAVE_BROKEN_RTC

MAKE_FLAGS := \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS) -lzysh_log -liface_generic" \
	COPTS="$(COPTS)" \
	PREFIX="/usr"

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/zyxel-dnsmasq/install
	$(INSTALL_DIR) $(1)/usr/local/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/dnsmasq $(1)/usr/local/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq_start.sh $(1)/usr/local/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/external_portal_url_lookup.sh $(1)/usr/local/bin
	$(call ProWLAN/cprep, $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq_external_portal_init.sh)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq_external_portal_init.sh.cprep $(1)/usr/local/bin/dnsmasq_external_portal_init.sh
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq.conf $(1)/etc
ifeq ($(ZLDCONFIG_SSID_NAT_SUPPORT), 1)
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq_dhcp_prefix_10.conf $(1)/etc
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/0_Zyxel/dnsmasq_dhcp_prefix_172.conf $(1)/etc
endif
	$(INSTALL_DIR) $(1)/var/zyxel/dnsmasq.d
endef

$(eval $(call BuildPackage,zyxel-dnsmasq))
