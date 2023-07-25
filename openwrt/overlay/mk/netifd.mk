Hooks/Prepare/Pre += zyxel_add_patches
define zyxel_add_patches

	if [ ! -f .init-patches ]; then \
		if [ -d $(TOPDIR)/overlay/$(BOARD)/netifd/init-patches/ ]; then \
			$(foreach patch,$(shell ls $(TOPDIR)/overlay/$(BOARD)/netifd/init-patches/),$(PATCH) -i $(TOPDIR)/overlay/$(BOARD)/netifd/init-patches/$(patch) -p1;) \
			touch .init-patches;\
		fi \
	fi \

endef
