include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-ntp
PKG_VERSION:=4.2.8p12
PKG_LICENSE:=NTP License

PKG_FIXUP:=autoreconf
PKG_LIBTOOL_PATHS:=. sntp
PKG_CHECK_FORMAT_SECURITY:=0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/zyxel-ntp
  $(eval $(ProWLAN/Package/Default))
  TITLE:=The ntpdate utility from ISC NTP & ProWLAN ntpdate agent
  URL:=http://www.ntp.org/
  DEPENDS:=+libcap +zld-files +libuam +zylog +zykit
endef

CONFIGURE_VARS += \
	ac_cv_header_md5_h=no \
	ac_cv_lib_rt_sched_setscheduler=no \
	ac_cv_header_dns_sd_h=no \
	hw_cv_func_snprintf_c99=yes \
	hw_cv_func_vsnprintf_c99=yes \

CONFIGURE_ARGS += \
	--disable-nls \
	--disable-all-clocks \
	--disable-parse-clocks \
	--disable-threads-support \
	--without-threads \
	--without-crypto \
	--without-rpath \
	--without-ntpsnmpd \
	--without-lineeditlibs \
	--enable-local-libevent \
	--with-yielding-select=yes

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR) ; \
		./bootstrap ; \
		touch COPYRIGHT \
	)
	$(call Build/Configure/Default)
endef

define Build/Compile
	$(call Build/Compile/Default)
	$(call Package/ntp_agent/compile)
endef

define Package/ntp_agent/compile
	(cd $(PKG_BUILD_DIR)/ntpdate ; \
		$(TARGET_CC) $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) ntpdate_agent.c -o ntpdate_agent -luam -lzysh_log -lzykit \
	)
endef

define Package/zyxel-ntp/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ntpdate/ntpdate $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ntpdate/ntpdate_agent $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,zyxel-ntp))
