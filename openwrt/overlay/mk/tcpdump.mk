define install_tcpdump_suid

	chmod u+s $(1)/usr/sbin/tcpdump
	
endef

Package/tcpdump/install += $(install_tcpdump_suid)
