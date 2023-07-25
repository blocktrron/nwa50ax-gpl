Hooks/Prepare/Pre += zyxel_add_patches
define zyxel_add_patches

	if [ ! -d patches ]; then \
		mkdir patches; \
	fi
	if [ -d $(TOPDIR)/overlay/$(BOARD)/wireless-tools/patches/ ]; then \
		$(CP) $(TOPDIR)/overlay/$(BOARD)/wireless-tools/patches/* patches/; \
	fi \

endef
