include $(TOPDIR)/rules.mk

PKG_NAME:=paping
PKG_VERSION:=1.5.5
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)_$(PKG_VERSION)
PROWLAN_REPO:=nebula-apps

define Package/paping
  $(eval $(ProWLAN/Package/Default))
  URL:=https://code.google.com/archive/p/paping/
  DEPENDS:=+libstdcpp
endef

BUILD_SRC := print.cpp stats.cpp timer.cpp arguments.cpp i18n.cpp host.cpp socket.cpp main.cpp
BUILD_OBJ := paping

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	(cd $(PKG_BUILD_DIR); \
		$(TARGET_CXX) $(addprefix src/,$(BUILD_SRC)) -o $(BUILD_OBJ) \
	)
endef

define Package/paping/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/paping $(1)/usr/bin
endef

$(eval $(call BuildPackage,paping))
