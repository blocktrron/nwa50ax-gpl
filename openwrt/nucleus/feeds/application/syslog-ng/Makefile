include $(TOPDIR)/rules.mk
PKG_NAME:=syslog-ng
PKG_VERSION:=1.6.12
PKG_RELEASE:=6
PKG_MD5SUM:=a3cbfdb6e1e5beea181a7349749719f3

PKG_SOURCE_URL:= \
	http://www.balabit.com/downloads/files/syslog-ng/sources/1.6/src \
	http://www.balabit.com/downloads/files/syslog-ng/stable/src
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_LICENSE:=GPL-2.0

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

define Package/syslog-ng
  $(eval $(ProWLAN/Package/Default))
  TITLE:=A powerful syslog daemon
  URL:=http://www.balabit.hu/products/syslog-ng/
  DEPENDS:=+libol +librt
endef

define Package/syslog-ng/description
	syslog-ng reads and logs messages to the system console, log
	files, other machines and/or users as specified by its
	configuration file.
endef

define Package/syslog-ng/conffiles
/etc/syslog-ng/syslog-ng.conf
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--disable-dependency-tracking \
		--disable-full-static \
		--enable-tcp-wrapper \
		--with-libol="$(STAGING_DIR)/host/bin" \
		, \
		CPPFLAGS="-I$(STAGING_DIR)/usr/include/libol $(TARGET_CPPFLAGS)" \
		LDFLAGS="-L$(STAGING_DIR)/usr/lib/libol $(TARGET_LDFLAGS)" \
	)
endef

define Package/syslog-ng/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/syslog-ng $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/syslog-ng
	$(INSTALL_DATA) ./files/syslog-ng.conf $(1)/etc/syslog-ng/syslog-ng.conf
	$(INSTALL_DIR) $(1)/var/zyxel
	$(LN) /etc/syslog-ng $(1)/var/zyxel/syslog-ng
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/syslog-ng.initd $(1)/etc/init.d/syslog-ng
endef

$(eval $(call BuildPackage,syslog-ng))
