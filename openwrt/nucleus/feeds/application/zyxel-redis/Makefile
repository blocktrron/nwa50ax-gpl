include $(TOPDIR)/rules.mk

PKG_NAME:=zyxel-redis
PKG_VERSION:=3.0.3
PKG_INSTALL:=1
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/zyxel-redis
  $(eval $(ProWLAN/Package/Default))
  TITLE:=The redis for database
  URL:=https://redis.io
  DEPENDS:=+zld-files
endef

MAKE_FLAGS+= \
	MALLOC="libc" \
	USE_JEMALLOC="no" \
	PREFIX="$(PKG_INSTALL_DIR)/usr" \
	ARCH=""

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
endef

define Build/Compile
	$(MAKE) -C "$(PKG_BUILD_DIR)/deps/hiredis" static $(MAKE_FLAGS)  $(MAKE_VARS)
	$(call Build/Compile/Default)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/include/hiredis
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/deps/hiredis/*.h $(1)/include/hiredis/
	$(INSTALL_DIR) $(1)/include/hiredis/adapters
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/deps/hiredis/adapters/*.h $(1)/include/hiredis/adapters/
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_BUILD_DIR)/deps/hiredis/libhiredis.a $(1)/lib	
endef

define Package/zyxel-redis/install
	$(INSTALL_DIR) $(1)/usr/local/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/redis-* $(1)/usr/local/bin
	$(INSTALL_DIR) $(1)/var
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/redis.conf $(1)/var
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/zyxel-redis.initd $(1)/etc/init.d/redis-server
endef

$(eval $(call BuildPackage,zyxel-redis))
