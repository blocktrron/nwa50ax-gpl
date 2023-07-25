define install_busybox_suid

ifneq ($(CONFIG_BUSYBOX_$(BUSYBOX_SYM)_FEATURE_SUID),)
	chmod u+s $(1)/bin/busybox
endif
	
endef

Package/busybox/install += $(install_busybox_suid)
