include $(TOPDIR)/rules.mk

PKG_NAME:=sp-oops-extract
PKG_VERSION:=0.0.7
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/sp-oops-extract
  $(eval $(ProWLAN/Package/Default))
  URL:=http://maemo.org/packages/view/sp-oops-extract/
endef

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/sp-oops-extract/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/sp-oops-extract $(1)/bin
endef

$(eval $(call BuildPackage,sp-oops-extract))
