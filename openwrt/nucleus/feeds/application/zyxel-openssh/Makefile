include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-openssh
PKG_VERSION:=8.6p1
PKG_LICENSE:=BSD

PKG_FIXUP:=autoreconf
PKG_BUILD_DEPENDS:=libopenssl

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=nebula-apps

define Package/zyxel-openssh
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Zyxel OpenSSH Package
  URL:=http://www.openssh.com/
  DEPENDS:=+libopenssl +zlib +libpthread +libpam
endef


TARGET_CFLAGS += $(FPIC) \
        -I$(STAGING_DIR)/usr/include

CONFIGURE_ARGS+= \
	$(DISABLE_NLS) \
	--enable-shared \
	--disable-static \
	--disable-debug \
	--disable-strip \
	--disable-etc-default-login \
	--disable-lastlog \
	--disable-utmp \
	--disable-utmpx \
	--disable-wtmp \
	--disable-wtmpx \
	--without-bsd-auth \
	--without-kerberos5 \
	--without-x \
	--with-pam

ifeq ($(CONFIG_OPENSSL_ENGINE),y)
CONFIGURE_ARGS+= \
	--with-ssl-engine
endif

CONFIGURE_VARS += LD="$(TARGET_CC)"

TARGET_LDFLAGS += -lpthread -lssl -lcrypto -L$(STAGING_DIR)/lib

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		LIBS="" \
		sftp-server
	$(MAKE) -C $(PKG_BUILD_DIR) \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		STRIP_OPT="" \
		all install
	(cd $(PKG_BUILD_DIR) ; \
                $(TARGET_CC) cert2ssh.c ssh-sk.o -o cert2ssh -I. $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) -L. -Lopenbsd-compat $(TARGET_LDFLAGS) -lzykit -lzysh_log -luam -pie -lssh -lopenbsd-compat -lcrypto -lutil -lz -lcrypt\
        )
endef

ifeq ($(ZLDCONFIG_NEBULA_REMOTE_SUPPORT), 1)
define Package/zyxel-openssh/preinst
#!/bin/sh
if [ -L $${IPKG_INSTROOT}/usr/bin/ssh ] && [ -L $${IPKG_INSTROOT}/usr/bin/scp ]; then
        rm -f $${IPKG_INSTROOT}/usr/bin/ssh
fi
exit 0
endef

define Package/zyxel-openssh/postrm
#!/bin/sh
rm -f $${IPKG_INSTROOT}/usr/bin/ssh $${IPKG_INSTROOT}/usr/bin/scp;
if [ -x $${IPKG_INSTROOT}/usr/sbin/dropbear ] ; then
        ln -s /usr/sbin/dropbear $${IPKG_INSTROOT}/usr/bin/ssh;
fi
exit 0
endef
endif

define Package/zyxel-openssh/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ssh-keygen $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cert2ssh $(1)/usr/bin/
ifeq ($(ZLDCONFIG_NEBULA_REMOTE_SUPPORT), 1)
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/ssh $(1)/usr/bin/
endif
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/sshd $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/pam.d
	ln -sf ssh $(1)/etc/pam.d/sshd
	$(INSTALL_DIR) $(1)/etc/ssh
	ln -sf /var/zyxel/sshd_config $(1)/etc/ssh/sshd_config
endef

$(eval $(call BuildPackage,zyxel-openssh))
