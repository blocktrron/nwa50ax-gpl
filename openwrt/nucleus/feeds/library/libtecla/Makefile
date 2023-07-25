include $(TOPDIR)/rules.mk

PKG_NAME:=libtecla
PKG_VERSION:=1.6.1
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1
PKG_LICENSE:=X11

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/libtecla
  $(eval $(ProWLAN/Package/Default))
  TITLE:=The Tecla command-line editing library
  URL:=https://sites.astro.caltech.edu/~mcs/tecla/
  DEPENDS:=+libncurses
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--without-file-actions \
	--without-file-system \
	--without-man-pages

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/libtecla.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
endef

define Package/libtecla/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(RM) $(1)/usr/lib/*.{a,la}
endef

$(eval $(call BuildPackage,libtecla))
