include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-freeradius3
PKG_VERSION:=3.0.20
PKG_FIXUP:=autoreconf
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=aaa
PROWLAN_PKG_NAME:=freeradius-server-$(PKG_VERSION)

define Package/zyxel-freeradius3
  $(eval $(ProWLAN/Package/Default))
  TITLE:=FreeRADIUS Server v3.x
  URL:=https://freeradius.org/
  DEPENDS:=+libopenssl +libtalloc +libatomic +zld-files +kmod-captive_portal
ifeq ($(ZLDCONFIG_CAPWAP_WTP_SUPPORT), 1)
  DEPENDS+=+wtp_module +libbmm
endif
  DEPENDS+=+libcap +libpcap +libncurses +libreadline
endef

CONFIGURE_VARS += \
	ax_cv_cc_builtin_choose_expr=no \
	ax_cv_cc_builtin_types_compatible_p=no \
	ax_cv_cc_builtin_bswap64=no \
	ax_cv_cc_bounded_attribute=no \
	ax_cv_cc_no_date_time_flag=no \
	ac_cv_path_LOCATE=""

CONFIGURE_ARGS += \
	--sysconfdir="/var/zyxel" \
	--localstatedir="/var" \
	--with-vmps="no" \
	--with-dhcp="no" \
	--with-pcre="no" \
	--with-tcp="no" \
	--with-threads="yes" \
	--without-rlm_couchbase \
	--without-rlm_counter \
	--without-rlm_eap_fast \
	--without-rlm_eap_ikev2 \
	--without-rlm_eap_pwd \
	--without-rlm_eap_sim \
	--without-rlm_eap_tnc \
	--without-rlm_example \
	--without-rlm_idn \
	--without-rlm_ippool \
	--without-rlm_krb5 \
	--without-rlm_ldap \
	--without-rlm_opendirectory \
	--without-rlm_pam \
	--without-rlm_perl \
	--without-rlm_python \
	--without-rlm_python3 \
	--without-rlm_redis \
	--without-rlm_rediswho \
	--without-rlm_rest \
	--without-rlm_ruby \
	--without-rlm_securid \
	--without-rlm_smsotp \
	--without-rlm_sql \
	--without-rlm_sqlcounter \
	--without-rlm_sql_db2 \
	--without-rlm_sql_firebird \
	--without-rlm_sql_freetds \
	--without-rlm_sql_iodbc \
	--without-rlm_sql_mongo \
	--without-rlm_sql_mysql \
	--without-rlm_sql_oracle \
	--without-rlm_sql_postgresql \
	--without-rlm_sql_sqlite \
	--without-rlm_sql_unixodbc \
	--without-rlm_sqlhpwippool \
	--without-rlm_sqlippool \
	--without-rlm_unbound \
	--without-rlm_yubikey \
	--with-openssl="yes"

_cprep := common/radiusdebug.sh common/radiusd_start.sh radiusd.conf.ZyXEL default.ZyXEL
ifeq ($(ZLDCONFIG_CLOUD_MODE_SUPPORT), 1)
_cprep += Nebula/default.Nebula Nebula/local.Nebula Nebula/radiusd.conf.Nebula
endif

ifeq ($(ZLDCONFIG_CAPWAP_WTP_SUPPORT), 1)
TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include/capwap_cli
TARGET_LDFLAGS += -lwtpcapwapevent -lbmm
endif

MODS_ENABLED := zylogger
SITES_ENABLED := control-socket status
ifeq ($(ZLDCONFIG_AAA_MAC_AUTH), 1)
MODS_ENABLED += zy_mac_auth
endif
ifeq ($(ZLDCONFIG_NEBULA_PORTAL_ACCOUNTING_SUPPORT), 1)
MODS_ENABLED += zy_rid
SITES_ENABLED += coa
endif
ifeq ($(ZLDCONFIG_CLOUD_MODE_SUPPORT), 1)
MODS_ENABLED += exec.Nebula files.Nebula zychex zycloud zypasswd
SITES_ENABLED += local
endif
DICTS := compat freeradius freeradius.internal rfc2865 rfc2866 rfc2867 rfc2868 rfc2869 rfc3162 rfc3576 rfc3580 rfc4372 rfc4675 rfc4679 rfc5580 microsoft wispr

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	# Compile jlibtool for the host once the configuration is done
	(cd $(PKG_BUILD_DIR); \
		mkdir -p build/make; \
		$(HOSTCC) $(HOST_CFLAGS) scripts/jlibtool.c -o build/make/jlibtool; \
	)
	$(MAKE) -C $(PKG_BUILD_DIR) \
		R="$(PKG_INSTALL_DIR)" \
		INSTALLSTRIP="" \
		all install
endef

define Build/Install
	$(foreach f, $(_cprep), $(call ProWLAN/cprep, $(PKG_BUILD_DIR)/0_Zyxel/$(f)))
	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/usr/local/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/common/radiusdebug.sh.cprep $(PKG_INSTALL_DIR)/usr/local/bin/radiusdebug.sh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/common/radiusd_start.sh.cprep $(PKG_INSTALL_DIR)/usr/local/bin/radiusd_start.sh
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/common/dictionary.ZyXEL $(PKG_INSTALL_DIR)/var/zyxel/raddb/dictionary
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/common/policy.ZyXEL $(PKG_INSTALL_DIR)/var/zyxel/raddb/policy.d/policy.ZyXEL
ifeq ($(ZLDCONFIG_NEBULA_PORTAL_ACCOUNTING_SUPPORT), 1)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/0_Zyxel/common/coa.sh $(PKG_INSTALL_DIR)/usr/local/bin/coa.sh
endif
	find $(PKG_INSTALL_DIR)/var/zyxel/raddb/certs/ -type f ! -name dh -delete
	cd $(PKG_INSTALL_DIR)/var/zyxel/raddb/certs/ && ln -sf /dev/urandom random
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/proxy.conf.ZyXEL $(PKG_INSTALL_DIR)/var/zyxel/raddb/proxy.conf.ZyXEL
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/radiusd.conf.ZyXEL.cprep $(PKG_INSTALL_DIR)/var/zyxel/raddb/radiusd.conf.ZyXEL
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/default.ZyXEL.cprep $(PKG_INSTALL_DIR)/var/zyxel/raddb/sites-available/default.ZyXEL
ifeq ($(ZLDCONFIG_AAA_MAC_AUTH), 1)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/proxy_zy_mac_auth.conf $(PKG_INSTALL_DIR)/var/zyxel/raddb/proxy_zy_mac_auth.conf
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/proxy_zy_mac_auth_realm.conf $(PKG_INSTALL_DIR)/var/zyxel/raddb/proxy_zy_mac_auth_realm.conf
endif
ifeq ($(ZLDCONFIG_CLOUD_MODE_SUPPORT), 1)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/default.Nebula.cprep $(PKG_INSTALL_DIR)/var/zyxel/raddb/sites-available/default.Nebula
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/inner-tunnel.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/sites-available/inner-tunnel
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/radiusd.conf.Nebula.cprep $(PKG_INSTALL_DIR)/var/zyxel/raddb/radiusd.conf.Nebula
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/proxy.conf.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/proxy.conf.Nebula
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/local.Nebula.cprep $(PKG_INSTALL_DIR)/var/zyxel/raddb/sites-available/local
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/exec.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/mods-available/exec.Nebula
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/files.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/mods-available/files.Nebula
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/zypasswd.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/mods-available/zypasswd
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/zycloud.Nebula $(PKG_INSTALL_DIR)/var/zyxel/raddb/mods-available/zycloud
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/mac_role $(PKG_INSTALL_DIR)/var/zyxel/raddb/mac_role
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/authorized_macs $(PKG_INSTALL_DIR)/var/zyxel/raddb/authorized_macs
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/0_Zyxel/Nebula/mac_auth_file $(PKG_INSTALL_DIR)/var/zyxel/raddb/mac_auth_file
endif
	for f in $(MODS_ENABLED) ; do \
		cd $(PKG_INSTALL_DIR)/var/zyxel/raddb/mods-enabled/ && ln -sf ../mods-available/$$$$f ./$$$$f; \
	done
	for f in $(SITES_ENABLED) ; do \
		cd $(PKG_INSTALL_DIR)/var/zyxel/raddb/sites-enabled/ && ln -sf ../sites-available/$$$$f ./$$$$f ; \
	done
	$(RM) -r $(PKG_INSTALL_DIR)/usr/man/
	$(RM) -r $(PKG_INSTALL_DIR)/usr/share/doc/
	$(RM) $(PKG_INSTALL_DIR)/usr/share/freeradius/*
	touch $(PKG_INSTALL_DIR)/usr/share/freeradius/dictionary
	for f in $(DICTS) ; do \
		echo "\$$$$INCLUDE dictionary.$$$$f" >> $(PKG_INSTALL_DIR)/usr/share/freeradius/dictionary; \
		$(INSTALL_DATA) $(PKG_BUILD_DIR)/share/dictionary.$$$$f $(PKG_INSTALL_DIR)/usr/share/freeradius/dictionary.$$$$f ; \
	done
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
endef

define Package/zyxel-freeradius3/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(RM) $(1)/usr/lib/*.{a,la}
	$(INSTALL_DIR) $(1)/usr/share/freeradius
	$(CP) $(PKG_INSTALL_DIR)/usr/share/freeradius/* $(1)/usr/share/freeradius
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/usr/local/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/local/bin/* $(1)/usr/local/bin
	$(INSTALL_DIR) $(1)/var
	$(CP) $(PKG_INSTALL_DIR)/var/* $(1)/var
endef

$(eval $(call BuildPackage,zyxel-freeradius3))
