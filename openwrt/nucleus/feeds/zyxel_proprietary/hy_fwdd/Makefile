include $(TOPDIR)/rules.mk
PKG_NAME:=hy_fwdd
PKG_VERSION:=1.0
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

define Package/hy_fwdd
  CATEGORY:=Zyxel Galaxy Nucleus Software Components
  SUBMENU:=proprietary
  TITLE:=Zyxel hy_fwdd package
  DEPENDS:=+libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread +kmod-hy_fwd +zylog +libiface_generic
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
    -unzip -d $(1) -o -q $(PKG_BUILD_DIR)/hy_fwdd.zip
endef

define Build/Compile
	@echo "$(PKG_NAME) is compiled."
endef

define Package/hy_fwdd/install
	mkdir -p $(1)/tmp
	$(call opkg,$(1)) install $(PKG_BUILD_DIR)/hy_fwdd.ipk
	rm -fr $(1)/tmp
	rm -fr $(1)/usr/lib/opkg
endef

$(eval $(call BuildPackage,hy_fwdd))