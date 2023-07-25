include $(TOPDIR)/rules.mk

PKG_NAME:=libpam
PKG_VERSION:=1.3.1
PKG_FIXUP:=autoreconf
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=aaa
PROWLAN_PKG_NAME:=Linux-PAM-$(PKG_VERSION)

define Package/libpam
  $(eval $(ProWLAN/Package/Default))
  TITLE:=Linux PAM Library and Modules
  URL:=http://www.linux-pam.org/
  DEPENDS:=+zylog +libuser_profile +libuam +libfeynman +zld-files
endef

TARGET_CFLAGS += $(FPIC) -Wno-unused

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-audit \
	--disable-cracklib \
	--enable-db=no \
	--disable-prelude \
	--disable-largefile \
	--disable-nis \
	--disable-selinux \
	--disable-nls \
	--disable-regenerate-docu \
	--disable-rpath \
	--without-mailspool \
	--without-xauth

TARGET_LDFLAGS += -lzysh_log -luam -luser_profile -lfeynman

NEEDED_PAM_MODULES := ! -name pam_auth_admin.so
NEEDED_PAM_MODULES += ! -name pam_debugauth.so
NEEDED_PAM_MODULES += ! -name pam_radius_auth.so
NEEDED_PAM_MODULES += ! -name pam_uam.so
NEEDED_PAM_MODULES += ! -name pam_webaccess.so
NEEDED_PAM_MODULES += ! -name pam_deny.so
NEEDED_PAM_MODULES += ! -name pam_env.so
NEEDED_PAM_MODULES += ! -name pam_nologin.so
NEEDED_PAM_MODULES += ! -name pam_permit.so
NEEDED_PAM_MODULES += ! -name pam_unix.so

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Install
	$(call Build/Install/Default)
	find $(PKG_INSTALL_DIR)/lib/security -type f $(NEEDED_PAM_MODULES) -delete
	find $(PKG_INSTALL_DIR)/lib/security -type d -empty -delete
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/* $(1)/lib
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
endef

define Package/libpam/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/* $(1)/lib
	$(RM) $(1)/lib/*.{a,la}
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/pam.d
	$(CP) ./files/pam.d/* $(1)/etc/pam.d/
	$(INSTALL_DIR) $(1)/var/zyxel
	$(LN) /etc/pam.d $(1)/var/zyxel/pam.d
endef

$(eval $(call BuildPackage,libpam))
