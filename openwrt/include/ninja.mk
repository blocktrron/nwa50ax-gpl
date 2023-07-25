ifneq ($(__ninja_mk_inc),1)
__ninja_mk_inc=1

NINJA_ARGS:=$(filter -j%,$(filter-out -j,$(MAKEFLAGS)))
ifneq ($(findstring c,$(OPENWRT_VERBOSE)),)
  NINJA_ARGS+=-v
endif

define Ninja
	$(2) $(STAGING_DIR_HOST)/usr/bin/ninja $(NINJA_ARGS) $(1)
endef

endif
