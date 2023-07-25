include $(TOPDIR)/rules.mk
PKG_NAME:=cert-tool
PKG_VERSION:=1.0
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

define Package/cert-tool
  CATEGORY:=Zyxel Galaxy Nucleus Software Components
  SUBMENU:=proprietary
  TITLE:=Zyxel cert-tool package
  DEPENDS:=+libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread +libopenssl +libxml2 +zld-files
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
    -unzip -d $(1) -o -q $(PKG_BUILD_DIR)/cert-tool.zip
endef

define Build/Compile
	@echo "$(PKG_NAME) is compiled."
endef

define Package/cert-tool/install
	mkdir -p $(1)/tmp
	$(call opkg,$(1)) install $(PKG_BUILD_DIR)/cert-tool.ipk
	rm -fr $(1)/tmp
	rm -fr $(1)/usr/lib/opkg
endef

$(eval $(call BuildPackage,cert-tool))