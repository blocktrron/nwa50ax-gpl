Hooks/Prepare/Pre += zyxel_add_patches
define zyxel_add_patches
	
	if [ ! -f .files-patches ]; then \
		if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files-patches/ ]; then \
			$(foreach patch,$(shell ls $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files-patches/),$(PATCH) -i $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files-patches/$(patch) -p1;) \
			touch .files-patches;\
		fi \
	fi \

endef

define procd_overlay_patch
	if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/patches/ ]; then \
		$(INSTALL_DIR) patches ; \
		$(CP) $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/patches/* patches/ ; \
	fi ;
	if [ -d $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files/ ]; then \
		$(INSTALL_DIR) files ; \
		$(CP) $(TOPDIR)/overlay/$(BOARD)/$(PKG_NAME)/files/* files/ ; \
	fi ;
endef

Build/Prepare = $(procd_overlay_patch)
Build/Prepare += $(Build/Prepare/Default)

define procd_install_scripts

	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) ./files/mtd_links $(1)/sbin
ifeq ($(CONFIG_TARGET_ramips),y)
	$(INSTALL_BIN) ./files/procd_start_instance.sh $(1)/sbin
endif
endef

Package/procd/install += $(procd_install_scripts)
