include $(TOPDIR)/rules.mk

PKG_NAME:=dumpimage-mips-mt7621
PKG_VERSION:=1.0
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=u-boot-mips-mt7621
PROWLAN_REPO:=platform/mt7621

MAKE_FLAGS+=CROSS_COMPILE="$(TARGET_CROSS)"
MAKE_FLAGS+=ARCH=mips

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Package/dumpimage-mips-mt7621
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=dumpimage for MT7621 based platforms
  URL:=http://www.denx.de/wiki/U-Boot
  SUBMENU:=Applications
  DEPENDS:=@TARGET_mt7621||TARGET_ramips +zykit
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)" mt7621_nand_ax_rfb_defconfig
	$(MAKE) -C "$(PKG_BUILD_DIR)" $(MAKE_FLAGS) cross_tools
endef

define Package/dumpimage-mips-mt7621/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/dumpimage $(1)/usr/bin
endef

$(eval $(call BuildPackage,dumpimage-mips-mt7621))
