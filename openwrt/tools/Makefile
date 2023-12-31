#
# Copyright (C) 2006-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# Main makefile for the host tools
#
curdir:=tools

# subdirectories to descend into
tools-y :=

ifeq ($(CONFIG_EXTERNAL_TOOLCHAIN),)
  BUILD_TOOLCHAIN := y
  ifdef CONFIG_GCC_USE_GRAPHITE
    BUILD_ISL = y
  endif
endif
ifneq ($(CONFIG_SDK)$(CONFIG_PACKAGE_kmod-b43)$(CONFIG_PACKAGE_b43legacy-firmware)$(CONFIG_BRCMSMAC_USE_FW_FROM_WL),)
  BUILD_B43_TOOLS = y
endif

tools-$(BUILD_TOOLCHAIN) += gmp mpfr mpc libelf expat
tools-y += m4 libtool autoconf automake flex bison pkg-config mklibs
tools-y += sstrip make-ext4fs e2fsprogs mtd-utils mkimage
tools-y += firmware-utils patch-image quilt padjffs2
tools-y += mm-macros missing-macros cmake scons bc findutils gengetopt patchelf
tools-y += mtools dosfstools libressl
tools-y += ninja meson
tools-$(CONFIG_TARGET_orion_generic) += wrt350nv2-builder upslug2
tools-$(CONFIG_powerpc) += upx
tools-$(CONFIG_TARGET_x86) += qemu
tools-$(CONFIG_TARGET_mxs) += elftosb sdimage
tools-$(CONFIG_TARGET_ar71xx) += lzma-old squashfs
tools-$(CONFIG_USES_MINOR) += kernel2minor
tools-y += lzma squashfs4
tools-$(BUILD_B43_TOOLS) += b43-tools
tools-$(BUILD_ISL) += isl
tools-$(CONFIG_USE_SPARSE) += sparse
tools-$(CONFIG_TARGET_apm821xx) += genext2fs
tools-y += libjson-c libaio lvm2 popt cryptsetup
tools-y += ar-table

# builddir dependencies
$(curdir)/bison/compile := $(curdir)/flex/install
$(curdir)/flex/compile := $(curdir)/libtool/install
$(curdir)/libtool/compile := $(curdir)/m4/install $(curdir)/autoconf/install $(curdir)/automake/install $(curdir)/missing-macros/install
$(curdir)/squashfs/compile := $(curdir)/lzma-old/install
$(curdir)/squashfs4/compile := $(curdir)/xz/install
$(curdir)/quilt/compile := $(curdir)/autoconf/install $(curdir)/findutils/install
$(curdir)/autoconf/compile := $(curdir)/m4/install
$(curdir)/automake/compile := $(curdir)/m4/install $(curdir)/autoconf/install $(curdir)/pkg-config/install $(curdir)/xz/install
$(curdir)/gmp/compile := $(curdir)/libtool/install
$(curdir)/mpc/compile := $(curdir)/mpfr/install $(curdir)/gmp/install
$(curdir)/mpfr/compile := $(curdir)/gmp/install
$(curdir)/mtd-utils/compile := $(curdir)/e2fsprogs/install
$(curdir)/mklibs/compile := $(curdir)/libtool/install
$(curdir)/qemu/compile := $(curdir)/e2fsprogs/install
$(curdir)/upslug2/compile := $(curdir)/libtool/install
$(curdir)/mm-macros/compile := $(curdir)/libtool/install
$(curdir)/missing-macros/compile := $(curdir)/autoconf/install
$(curdir)/e2fsprogs/compile := $(curdir)/libtool/install
$(curdir)/libelf/compile := $(curdir)/libtool/install
$(curdir)/sdcc/compile := $(curdir)/bison/install
$(curdir)/b43-tools/compile := $(curdir)/bison/install
$(curdir)/padjffs2/compile := $(curdir)/findutils/install
$(curdir)/isl/compile := $(curdir)/gmp/install
$(curdir)/bc/compile := $(curdir)/bison/install
$(curdir)/findutils/compile := $(curdir)/bison/install
$(curdir)/gengetopt/compile := $(curdir)/libtool/install
$(curdir)/patchelf/compile := $(curdir)/libtool/install
$(curdir)/dosfstools/compile := $(curdir)/autoconf/install $(curdir)/automake/install
$(curdir)/libressl/compile := $(curdir)/pkg-config/install
$(curdir)/mkimage/compile += $(curdir)/libressl/install
$(curdir)/firmware-utils/compile += $(curdir)/libressl/install
$(curdir)/cmake/compile += $(curdir)/libressl/install
$(curdir)/lvm2/compile := $(curdir)/libaio/install
$(curdir)/libjson-c/compile := $(curdir)/libtool/install
$(curdir)/cryptsetup/compile := $(curdir)/e2fsprogs/install $(curdir)/libjson-c/install $(curdir)/libaio/install $(curdir)/lvm2/install $(curdir)/popt/install

ifneq ($(HOST_OS),Linux)
  tools-y += coreutils
endif

ifneq ($(CONFIG_CCACHE)$(CONFIG_SDK),)
$(foreach tool, $(filter-out xz patch,$(tools-y)), $(eval $(curdir)/$(tool)/compile += $(curdir)/ccache/install))
tools-y += ccache
endif

# in case there is no patch tool on the host we need to make patch tool a
# dependency for tools which have patches directory
$(foreach tool, $(tools-y), $(if $(wildcard $(curdir)/$(tool)/patches),$(eval $(curdir)/$(tool)/compile += $(curdir)/patch/install)))

$(foreach tool, $(filter-out xz,$(tools-y)), $(eval $(curdir)/$(tool)/compile += $(curdir)/xz/install))

# make any tool depend on tar, xz and patch to ensure that archives can be unpacked and patched properly
tools-core := tar xz patch

$(foreach tool, $(tools-y), $(eval $(curdir)/$(tool)/compile += $(patsubst %,$(curdir)/%/install,$(tools-core))))
tools-y += $(tools-core)

# make core tools depend on sed and flock
$(foreach tool, $(tools-core), $(eval $(curdir)/$(tool)/compile += $(curdir)/sed/install))

$(curdir)/sed/compile := $(curdir)/flock/install
tools-y += flock sed

$(curdir)/builddirs := $(tools-y) $(tools-dep) $(tools-)
$(curdir)/builddirs-default := $(tools-y)

ifdef CHECK_ALL
$(curdir)/builddirs-check:=$($(curdir)/builddirs)
$(curdir)/builddirs-download:=$($(curdir)/builddirs)
endif

ifndef DUMP_TARGET_DB
define PrepareStaging
	@for dir in $(1); do ( \
		$(if $(QUIET),,set -x;) \
		mkdir -p "$$dir"; \
		cd "$$dir"; \
		mkdir -p bin lib include stamp; \
	); done
endef

# preparatory work
$(STAGING_DIR)/.prepared: $(TMP_DIR)/.build
	$(call PrepareStaging,$(STAGING_DIR))
	mkdir -p $(BUILD_DIR)/stamp
	touch $@

$(STAGING_DIR_HOST)/.prepared: $(TMP_DIR)/.build
	$(call PrepareStaging,$(STAGING_DIR_HOST))
	mkdir -p $(BUILD_DIR_HOST)/stamp $(STAGING_DIR_HOST)/include/sys
	$(INSTALL_DATA) $(TOPDIR)/tools/include/*.h $(STAGING_DIR_HOST)/include/
	$(INSTALL_DATA) $(TOPDIR)/tools/include/sys/*.h $(STAGING_DIR_HOST)/include/sys/
	ln -sf lib $(STAGING_DIR_HOST)/lib64
	touch $@

endif

$(curdir)//prepare = $(STAGING_DIR)/.prepared $(STAGING_DIR_HOST)/.prepared
$(curdir)//compile = $(STAGING_DIR)/.prepared $(STAGING_DIR_HOST)/.prepared

# prerequisites for the individual targets
$(curdir)/ := .config prereq
$(curdir)//install = $(1)/compile

tools_enabled = $(foreach tool,$(sort $(tools-y) $(tools-)),$(if $(filter $(tool),$(tools-y)),y,n))
$(eval $(call stampfile,$(curdir),tools,install,,_$(subst $(space),,$(tools_enabled))))
$(eval $(call stampfile,$(curdir),tools,check,$(TMP_DIR)/.build))
$(eval $(call subdir,$(curdir)))
