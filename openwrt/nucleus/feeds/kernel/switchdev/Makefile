include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=switchdev
PKG_VERSION:=1.0
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=ethernet
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)

define KernelPackage/switchdev
  $(ProWLAN/Package/Default)
  URL:=https://www.zyxel.com/
  FILES:=\
	$(PKG_BUILD_DIR)/switchdev.ko \
	$(PKG_BUILD_DIR)/switchdev_char.ko
  AUTOLOAD:=$(call AutoLoad,07,switchdev switchdev_char,1)
  DEPENDS:=+zld-files
endef

define KernelPackage/switchdev/description
	A middleware between switch driver and Zysh configuration
endef

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		modules
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/switchdev.h $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/switchdev-abi.h $(1)/usr/include
endef

$(eval $(call KernelPackage,switchdev))
