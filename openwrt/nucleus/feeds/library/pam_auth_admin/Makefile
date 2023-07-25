include $(TOPDIR)/rules.mk

PKG_NAME:=pam_auth_admin
PKG_VERSION:=1.0
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=aaa
PROWLAN_PKG_NAME:=pam_modules-1.0/$(REAL_PKG_NAME)-$(PKG_VERSION)

define Package/pam_auth_admin
  $(eval $(ProWLAN/Package/Default))
  TITLE:=PAM module for Admin authentication
  URL:=https://www.zyxel.com/
  DEPENDS:=+libtirpc +zld-files +libfeynman libpam
endef

TARGET_CFLAGS += $(FPIC)
TARGET_CPPFLAGS += -I$(STAGING_DIR)/usr/include/tirpc
TARGET_LDFLAGS += -ltirpc
MAKE_VARS += LDLIBS="$(TARGET_LDFLAGS)"

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/lib/security
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pam_auth_admin.so $(1)/lib/security
endef

define Package/pam_auth_admin/install
	$(INSTALL_DIR) $(1)/lib/security
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pam_auth_admin.so $(1)/lib/security
endef

$(eval $(call BuildPackage,pam_auth_admin))
