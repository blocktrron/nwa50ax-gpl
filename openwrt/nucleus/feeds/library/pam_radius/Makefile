include $(TOPDIR)/rules.mk

PKG_NAME:=pam_radius
PKG_VERSION:=1.3.16
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=aaa
PROWLAN_PKG_NAME:=pam_modules-1.0/$(REAL_PKG_NAME)-$(PKG_VERSION)

define Package/pam_radius
  $(eval $(ProWLAN/Package/Default))
  TITLE:=PAM module for RADIUS authentication
  URL:= http://www.freeradius.org/
  DEPENDS:=+zld-files +libuam libpam
endef

TARGET_CFLAGS += $(FPIC)

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/lib/security
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pam_radius_auth.so $(1)/lib/security
endef

define Package/pam_radius/install
	$(INSTALL_DIR) $(1)/lib/security
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pam_radius_auth.so $(1)/lib/security
endef

$(eval $(call BuildPackage,pam_radius))
