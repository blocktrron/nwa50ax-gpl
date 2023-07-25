include $(TOPDIR)/rules.mk

PKG_NAME:=net-tools
PKG_VERSION:=2.10-alpha
PKG_LICENSE:=GPL-2.0

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/net-tools
  $(eval $(ProWLAN/Package/Default))
  TITLE:=The net-tools package
  URL:=https://sourceforge.net/projects/net-tools/
endef

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Configure
	# Failed configure.sh leaves stub config.h around.
	rm -f $(PKG_BUILD_DIR)/config.h
	( cd $(PKG_BUILD_DIR); \
		yes $$$$'\n' | ./configure.sh config.in \
	)
endef

define Package/bash/preinst
#!/bin/sh
if [ -L $${IPKG_INSTROOT}/sbin/ifconfig ]; then
        rm -f $${IPKG_INSTROOT}/sbin/ifconfig
fi
exit 0
endef

define Package/net-tools/install
	$(INSTALL_DIR) $(1)/sbin $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ifconfig $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netstat $(1)/bin
endef

$(eval $(call BuildPackage,net-tools))
