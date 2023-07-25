include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-net-snmp
PKG_VERSION:=5.4.3
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=management

define Package/zyxel-net-snmp
   $(eval $(ProWLAN/Package/Default))
   URL:=http://net-snmp.sourceforge.net/
   DEPENDS:=+zld-files +zyio_library +zykit +libxml2 +libopenssl +wireless-hal
endef

CONFIGURE_MIB_MODULES:=mibII/at agentx target agent_mibs notification notification-log-mib ucd_snmp
ifneq ($(ZLDCONFIG_SNMP_DOWN_SIZE),1)
CONFIGURE_MIB_MODULES+=examples/ucdDemoPublic examples/example mibII/mta_sendmail ucd-snmp/lmSensors 
endif

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include/libxml2 $(FPIC) -DINTERFACE_CACHE_TIMEOUT="$(ZLDSYSPARM_SNMP_INTERFACE_CACHE_TIMEOUT)"

TARGET_LDFLAGS += -lzysh_io -lzykit -lxml2

TARGET_CONFIGURE_OPTS += RANLIB=":"

CONFIGURE_ARGS += \
	--with-endianness=$(if $(CONFIG_BIG_ENDIAN),big,little) \
	--with-out-mib-modules="$(CONFIGURE_MIB_MODULES)" \
	--with-default-snmp-version="3" \
	--with-sys-contact="support@zyxel.com.tw" \
	--with-sys-location=" " \
	--with-logfile="/var/log/snmpd.log" \
	--with-persistent-directory="/etc/net-snmp" \
	--disable-manuals \
	--with-mib-modules="utilities/execute disman/event-mib zld" \
	--with-enterprise-oid=890 \
	--with-enterprise-sysoid=.1.3.6.1.4.1.890.1.15 \
	--with-enterprise-notification-oid=.1.3.6.1.4.1.890 \
	--without-perl-modules \
	--disable-embedded-perl \
	--disable-perl-cc-checks \
	--without-rpm \

ifeq ($(ZLDCONFIG_SNMP_DOWN_SIZE),1)
CONFIGURE_ARGS += \
	--with-out-security-modules="ksm" \
	--disable-debugging \
	--without-kmem-usage \
	--disable-scripts \
	--disable-perl \
	--with-out-transports="UDPIPv6 TCPIPv6 Unix AAL5PVC IPX" \
	--disable-ipv6
endif

ifneq ($(ZLDCONFIG_CLOUD_MODE_SUPPORT),1)
CONFIGURE_ARGS += --disable-snmpv1
endif

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Configure
	$(call ProWLAN/cprep,$(PKG_BUILD_DIR)/zld_mib)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/zld_mib.cprep $(PKG_BUILD_DIR)/agent/mibgroup/zld.h
	$(call Build/Configure/Default)
endef

define Build/Install-dev
	$(INSTALL_DIR) $(1)/usr/local/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libnetsnmp*.so* $(1)/usr/local/lib
endef

define Package/zyxel-net-snmp/install
	$(INSTALL_DIR) $(1)/usr/local/bin
	$(INSTALL_DIR) $(1)/usr/local/sbin
	$(INSTALL_DIR) $(1)/usr/local/lib
	$(INSTALL_DIR) $(1)/usr/local/share/snmp/mibs
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/snmpd $(1)/usr/local/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/snmptrap $(1)/usr/local/bin
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libnetsnmp*.so* $(1)/usr/local/lib
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/mibs/*.txt $(1)/usr/local/share/snmp/mibs
ifneq ($(ZLDCONFIG_IPV6), 1)
	rm -rf $(1)/usr/local/share/snmp/mibs/IPV6*
endif
	$(INSTALL_DIR) $(1)/etc
	$(LN) -v /var/zyxel/net-snmp $(1)/etc/net-snmp
	$(LN) -v /var/zyxel/snmpd.conf $(1)/etc/snmpd.conf
endef

$(eval $(call BuildPackage,zyxel-net-snmp))
