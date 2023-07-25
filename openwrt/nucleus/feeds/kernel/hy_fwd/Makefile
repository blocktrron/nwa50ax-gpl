include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=hy_fwd
PKG_VERSION:=1.0
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_REPO:=kernel-modules
PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-module

define KernelPackage/hy_fwd
  $(ProWLAN/Package/Default)
  TITLE:=hybrid forwarding module
  URL:=https://www.zyxel.com/
  FILES:=$(PKG_BUILD_DIR)/hy_fwd.ko
  DEPENDS:=+zld-files
  AUTOLOAD:=$(call AutoLoad,09,hy_fwd)
endef

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)/" \
		modules
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/hy_fwd.h $(1)/usr/include/
endef

$(eval $(call KernelPackage,hy_fwd))
