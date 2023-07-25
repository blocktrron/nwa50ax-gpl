include $(TOPDIR)/rules.mk

PKG_NAME:=bash
PKG_VERSION:=4.4.18
PKG_LICENSE:=GPL-3.0+

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include ../../prowlan.mk

PROWLAN_PKG_NAME:=$(REAL_PKG_NAME)-$(PKG_VERSION)
PROWLAN_REPO:=common

define Package/bash
  $(eval $(ProWLAN/Package/Default))
  TITLE:=The GNU Bourne Again SHell
  URL:=http://www.gnu.org/software/bash/
  DEPENDS:=+libncurses
endef

# Bash detects and enables certain features by runtest simple piece of code
# which is not viable when doing cross compilation and default to no in many
# cases.  Grep for 'cross.compil' in aclocal.m4 and config-bot.h for details
#
# bash_cv_job_control_missing: Job control is needed for bash to be used as the
# default shell
#
# bash_cv_getcwd_malloc: The replacement by bash does not work well with
# overlayfs.  See "bash getcwd errors when running under OverlayFS"
# http://permalink.gmane.org/gmane.linux.embedded.yocto.general/25204
#
# bash_cv_dev_fd: The test is done on build system but OpenWrt currently does
# not have /dev/fd, it provides /proc/self/fd/ instead
#
# bash_cv_sys_named_pipes: Required for process substituion
CONFIGURE_VARS += \
	ac_cv_rl_prefix="$(STAGING_DIR)/usr" \
	ac_cv_rl_version="7.0" \
	bash_cv_getcwd_malloc=yes \
	bash_cv_job_control_missing=present \
	bash_cv_dev_fd=whacky \
	bash_cv_sys_named_pipes=present \

# The following are some other tests that cannot run when cross-compiling
CONFIGURE_VARS += \
	bash_cv_func_sigsetjmp=present \
	bash_cv_printf_a_format=yes \

CONFIGURE_ARGS+= \
	--with-curses \
	--without-bash-malloc \
	--bindir=/bin \
	--disable-rpath \
	--disable-nls

define Build/Prepare
	$(call ProWLAN/Package/Prepare)
	( cd $(PKG_BUILD_DIR) && touch ./configure )
endef

define Package/bash/preinst
#!/bin/sh
if [ -L $${IPKG_INSTROOT}/bin/sh ]; then
        rm -f $${IPKG_INSTROOT}/bin/sh
fi
exit 0
endef

define Package/bash/postinst
#!/bin/sh
grep -q bash "$${IPKG_INSTROOT}/etc/shells" || {
	echo /bin/bash >> "$${IPKG_INSTROOT}/etc/shells"
	echo /bin/rbash >> "$${IPKG_INSTROOT}/etc/shells"
}
endef

define Package/bash/postrm
#!/bin/sh
rm -f $${IPKG_INSTROOT}/bin/sh
if [ -x $${IPKG_INSTROOT}/bin/ash ] ; then
        ln -s /bin/ash $${IPKG_INSTROOT}/bin/sh;
fi
exit 0
endef

define Package/bash/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/bash $(1)/bin/
	$(LN) bash $(1)/bin/rbash
	$(LN) bash $(1)/bin/sh
endef

$(eval $(call BuildPackage,bash))
