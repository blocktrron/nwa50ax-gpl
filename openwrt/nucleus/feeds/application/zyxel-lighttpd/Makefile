include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-lighttpd
PKG_VERSION:=1.4.45
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/zyxel-lighttpd
  $(eval $(ProWLAN/Package/Default))
  TITLE:=A flexible and lightweight web server
  URL:=https://www.lighttpd.net/
  DEPENDS:=+libuser_profile +libopenssl +libpcre +zlib +libpthread +libuam
endef

TARGET_CFLAGS += $(FPIC)

TARGET_LDFLAGS += -luam

CONFIGURE_PREFIX:=/usr/local/lighttpd

CONFIGURE_VARS += \
	PCRE_LIB="-lpcre" \

CONFIGURE_ARGS += \
		--enable-shared \
		--disable-static \
		--disable-lfs \
		--without-attr \
		--without-bzip2 \
		--without-dbi \
		--without-fam \
		--without-gdbm \
		--without-geoip \
		--without-krb5 \
		--without-ldap \
		--without-libev \
		--without-libxml \
		--without-lua \
		--without-maxminddb \
		--without-memcached \
		--without-mysql \
		--without-pam \
		--without-pgsql \
		--without-sqlite \
		--without-sasl \
		--without-valgrind \
		--with-zlib \
		--with-pcre \
		--with-openssl="$(STAGING_DIR)/usr"

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/zyxel-lighttpd/install
	$(INSTALL_DIR) $(1)/$(CONFIGURE_PREFIX)
	$(CP) $(PKG_INSTALL_DIR)/$(CONFIGURE_PREFIX)/* $(1)/$(CONFIGURE_PREFIX)
	$(RM) $(1)/$(CONFIGURE_PREFIX)/lib/*.{a,la}
	$(RM) -r $(1)/$(CONFIGURE_PREFIX)/man
	$(INSTALL_DIR) $(1)/$(CONFIGURE_PREFIX)/conf
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/config/lighttpd.conf.ZyXEL $(1)/$(CONFIGURE_PREFIX)/conf/lighttpd.conf
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/config/modules.conf.ZyXEL $(1)/$(CONFIGURE_PREFIX)/conf/modules.conf
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/config/dh2048.pem $(1)/$(CONFIGURE_PREFIX)/conf
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/doc/config/gen_portal_include.sh $(1)/$(CONFIGURE_PREFIX)/conf
	$(INSTALL_DIR) $(1)/$(CONFIGURE_PREFIX)/conf/conf.d
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/config/conf.ZyXEL/*.conf $(1)/$(CONFIGURE_PREFIX)/conf/conf.d
endef

$(eval $(call BuildPackage,zyxel-lighttpd))
