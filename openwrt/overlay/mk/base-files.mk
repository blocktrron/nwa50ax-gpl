# patch for base-files
Hooks/Prepare/Pre += zyxel_add_patches
define zyxel_add_patches
	# patch for openwrt/package/base-files/
	if [ ! -f .package-files-patches ]; then \
		if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/package-files-patches/ ]; then \
			$(foreach patch,$(shell ls $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/package-files-patches/),$(PATCH) --verbose -i $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/package-files-patches/$(patch) -d $(TOPDIR)/package/base-files/ -p1;) \
			touch .package-files-patches; \
		fi \
	fi

	# patch for openwrt/target/linux/ramips/base-files/
	if [ ! -f .target-files-patches ]; then \
		if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/target-files-patches/ ]; then \
			$(foreach patch,$(shell ls $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/target-files-patches/),$(PATCH) --verbose -i $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/target-files-patches/$(patch) -d $(TOPDIR)/target/linux/ramips/base-files/ -p1;) \
			touch .target-files-patches; \
		fi \
	fi
endef

define base-files_overlay_install
	;\
	echo "Install Galaxy base-files"
ifneq ($(CONFIG_ZYUMAC_MODEL_NAME),)
	echo "DEVICE_GALAXY_MODEL_NAME='$(CONFIG_ZYUMAC_MODEL_NAME)'" >>$(1)/etc/device_info
endif

ifneq ($(CONFIG_ZYUMAC_BOARD_NAME),)
	echo "DEVICE_GALAXY_BOARD_NAME='$(CONFIG_ZYUMAC_BOARD_NAME)'" >>$(1)/etc/device_info
endif
	# Copy files for generic
	if [ -d $(TOPDIR)/overlay/generic/$(PKG_NAME)/files/. ]; then \
		$(CP) $(TOPDIR)/overlay/generic/$(PKG_NAME)/files/* $(1)/; \
	fi

	# Copy files for product line overwriting
	if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME) ]; then \
                $(CP) -a $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files/* $(1)/; \
	fi

	# Copy files for board profile
	if [ -d $(PLATFORM_DIR)/base-files-$(PROFILE)/. ]; then \
		$(CP) $(PLATFORM_DIR)/base-files-$(PROFILE)/* $(1)/; \
	fi

	mkdir -p $(1)/etc/zyxel/pikachu
	mkdir -p $(1)/etc/zyxel/ftp/.tmp
	mkdir -p $(1)/etc/zyxel/ftp/coredump
	mkdir -p $(1)/etc/zyxel/ftp/diaglog
	mkdir -p $(1)/etc/zyxel/ftp/keep
	mkdir -p $(1)/etc/zyxel/ftp/nebula
	mkdir -p $(1)/etc/zyxel/ftp/netopeer
	mkdir -p $(1)/etc/zyxel/ftp/smart_mesh
	mkdir -p $(1)/etc/zyxel/ftp/tmp

	touch $(1)/etc/zyxel/ftp/keep/firmware-upgraded
	touch $(1)/etc/zyxel/ftp/keep/firmware-upgraded-cli-change
endef

Package/base-files/install += $(base-files_overlay_install)
