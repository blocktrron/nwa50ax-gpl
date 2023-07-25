include $(TOPDIR)/rules.mk

PKG_NAME:=netopeer
PKG_VERSION:=0.8.0
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_UNSTRIP:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=nebula-ap-apps
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)

define Package/netopeer
  $(eval $(ProWLAN/Package/Default))
  TITLE:=ProWLAN nebula netopeer
  URL:=https://github.com/cesnet/netopeer
  DEPENDS:=+libopenssl +wtp_module +zylog +zykit +zlib +libnetconf +libfeynman +netopeer-watchdog +@OPENSSL_WITH_COMPRESSION +zld-files
endef

CONFIGURE_ARGS += \
	LIBS="-lparser -lsta -lrrm_common -levent -lzykit -lfeynman -lzysh_log" \
	--with-lnctool="$(STAGING_DIR)/host/usr/bin/lnctool" \
	--sysconfdir="/var/netopeer" \
	--disable-ssh \
	--disable-configurator \
	--enable-tls \
	--enable-debug \

MAKE_FLAGS += MANPAGES= MANHTMLS=

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Install
 	sed -i -r "s,$(BUILD_DIR)/.+?/ipkg-install/usr/share,/var/libnetconf,g" $(PKG_BUILD_DIR)/config/*.rng
	$(call Build/Install/Default)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/var/netopeer/netopeer
	$(CP) $(PKG_INSTALL_DIR)/var/netopeer/netopeer/* $(1)/var/netopeer/netopeer
	$(INSTALL_DIR) $(2)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/netopeer-manager $(2)/usr/bin
endef

define Package/netopeer/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nc_conn_dbg_tool/* $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netopeer-server $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nc_conn_dbg_keeper.initd $(1)/etc/init.d/nc_conn_dbg_keeper
endef

$(eval $(call BuildPackage,netopeer))
