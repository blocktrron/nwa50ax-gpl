ifndef DUMP
  ifndef __package_mk
    $(warning prowlan.mk should be included after package.mk)
  endif
endif

__prowlan_mk:=1

PROWLAN_DIR:=$(DL_DIR)/wlan-ap
PROWLAN_FEED:=$(TOPDIR)/nucleus/feeds

PROWLAN_PREFIX:=zyxel-
REAL_PKG_NAME:=$(strip $(patsubst $(PROWLAN_PREFIX)%,%,$(PKG_NAME)))
PROWLAN_PKG_NAME:=$(strip $(REAL_PKG_NAME)-$(PKG_VERSION))
PROWLAN_REPO:=

OBJ_DIR:=
STAGING_OBJ_DIR:=$(STAGING_DIR)/obj/$(PKG_NAME)

ifndef INSTALL_SUID
  INSTALL_SUID:=install -m4755
endif

include $(PROWLAN_FEED)/zld-spec.mk

define ProWLAN/cprep
	$(PROWLAN_FEED)/cprep.sh \
		$(1) \
		$(STAGING_DIR)/usr/include/zld-spec.h \
		$(if $(2), $(2), 1);
endef

define ProWLAN/Package/Default
  CATEGORY:=Zyxel Galaxy Nucleus Software Components
  SUBMENU:=$(firstword $(subst /,$(space),$(subst $(PROWLAN_FEED)/,,$(subst /$(PKG_DIR_NAME),,$(CURDIR)))))
  TITLE:=Zyxel $(REAL_PKG_NAME) package
endef

define ProWLAN/Package/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	-unzip -d $(PKG_BUILD_DIR) -o -q $(PROWLAN_DIR)/$(PKG_NAME).zip
ifneq ($(OBJ_DIR),)
	$(INSTALL_DIR) $(OBJ_DIR)
	$(if $(wildcard $(STAGING_OBJ_DIR)/*.o),\
		$(CP) $(STAGING_OBJ_DIR)/*.o $(OBJ_DIR))
endif
endef

# Make sure PKG_NAME and PKG_DIR_NAME are the same
$(if $(and $(findstring $(PKG_DIR_NAME),$(PKG_NAME)),$(findstring $(PKG_NAME),$(PKG_DIR_NAME))),,$(error PKG_NAME and PKG_DIR_NAME is different!!))
