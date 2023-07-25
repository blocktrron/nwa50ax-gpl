include $(TOPDIR)/rules.mk
PKG_NAME:=zysh
PKG_VERSION:=1.0.0
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

define Package/zysh
  CATEGORY:=Zyxel Galaxy Nucleus Software Components
  SUBMENU:=proprietary
  TITLE:=Zyxel zysh package
  DEPENDS:=+libc +SSP_SUPPORT:libssp +USE_GLIBC:librt +USE_GLIBC:libpthread +libxml2 +libidn +libpam +libtecla +libopenssl +app_wd +link_updown +wlan_dcs_3 +accounting-daemon +kmod-zyklog +kmod-captive_portal +fauthd +nebula-led-ctrl +pki +email-daily-report +zld-files +wireless-hal +zylog +libbmm +libfirmware +wtp_module +libuam +walled_garden +wpa3lib +libiface_generic +libuser_profile +zykit +zylog_wrapper +zyio_library +libzld-sysinfo +generic_timer +kmod-switchdev +libzyDualImage +wlan_apmode_rapd +scan_agent +radio_resource_measurement +ssid_manager +neighbor_collector +info_transfer +libgpio_control +diag_info +pcap_monitor +smart_mesh +kmod-hy_fwd
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
    -unzip -d $(1) -o -q $(PKG_BUILD_DIR)/zysh.zip
endef

define Build/Compile
	@echo "$(PKG_NAME) is compiled."
endef

define Package/zysh/install
	mkdir -p $(1)/tmp
	$(call opkg,$(1)) install $(PKG_BUILD_DIR)/zysh.ipk
	rm -fr $(1)/tmp
	rm -fr $(1)/usr/lib/opkg
endef

$(eval $(call BuildPackage,zysh))