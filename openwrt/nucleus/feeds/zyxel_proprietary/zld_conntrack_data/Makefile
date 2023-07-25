include $(TOPDIR)/rules.mk
PKG_NAME:=zld_conntrack_data
PKG_VERSION:=4.4.198+1.0-
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

define Package/kmod-zld_conntrack_data
  CATEGORY:=Zyxel Galaxy Nucleus Software Components
  SUBMENU:=proprietary
  TITLE:=Zyxel kmod-zld_conntrack_data package
  DEPENDS:=+kmod-zyklog +kmod-nf-conntrack
  DEFAULT:=y
endef

opkg = \
  IPKG_NO_SCRIPT=1 \
  IPKG_INSTROOT=$(1) \
  TMPDIR=$(1)/tmp \
  $(STAGING_DIR_HOST)/bin/opkg \
	--offline-root $(1) \
	--force-postinstall \
	--add-dest root:/ \
	--add-arch all:100 \
	--add-arch $(if $(ARCH_PACKAGES),$(ARCH_PACKAGES),$(BOARD)):200 \
	--nodeps

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/InstallDev
    -unzip -d $(1) -o -q $(PKG_BUILD_DIR)/zld_conntrack_data.zip
endef

define Build/Compile
	@echo "$(PKG_NAME) is compiled."
endef

define Package/kmod-zld_conntrack_data/install
	mkdir -p $(1)/tmp
	$(call opkg,$(1)) install $(PKG_BUILD_DIR)/kmod-zld_conntrack_data.ipk
	rm -fr $(1)/tmp
	rm -fr $(1)/usr/lib/opkg
endef

$(eval $(call BuildPackage,kmod-zld_conntrack_data))