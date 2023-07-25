include $(TOPDIR)/rules.mk

PKG_NAME:=pure-ftpd
PKG_VERSION:=1.0.49
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/pure-ftpd
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Pure-FTPd
  URL:=https://www.pureftpd.org/project/pure-ftpd/
  DEPENDS:=+libopenssl +zylog +zykit +libuam +libpam +file_manage
endef

TARGET_LDFLAGS += -lzysh_log -lzykit -luam

CONFIGURE_ARGS += \
	--with-tls \
	--with-certfile="/tmp/tls_default" \
	--with-pam \
	--with-quotas \
	--without-inetd \
	--without-capabilities \
	--without-globbing

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/pure-ftpd/install
	$(INSTALL_DIR) $(1)/usr/local/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/pure-ftpd $(1)/usr/local/sbin
	$(INSTALL_DIR) $(1)/etc
	$(LN) /var/zyxel/ftp.conf $(1)/etc/ftp.conf
	$(LN) /var/zyxel/ftpusers $(1)/etc/ftpuser
endef

$(eval $(call BuildPackage,pure-ftpd))
