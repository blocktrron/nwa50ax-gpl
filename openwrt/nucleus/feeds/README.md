## How to add a package?

1. Run `build.py` one time. Then change to the `openwrt` directory.
   ```
   cd openwrt
   ```

1. Clean working directory first.
   ```
   make clean
   ```

1. Create a directory under `nucleus/feeds/` with correct category:
   - galaxy-ap/galaxy-ap-application> user applications, daemons
   - galaxy-ap/galaxy-ap-library> developer libraries
   - galaxy-ap/galaxy-ap-kernel> kernel modules, drivers
   - galaxy-ap/galaxy-ap-zld-common> GUI, init scripts, common files from ZLD

1. Create a `Makefile` of your package for Openwrt.
   - Include [prowlan.mk](feeds/prowlan.mk) in your Makefile
   - If your package source is located in `wlan-ap` repository, add the `PROWLAN_REPO`, `PROWLAN_PKG_NAME` of your package.
   - Use `$(call ProWLAN/Package/Prepare)` to copy the package source from `wlan-ap` repository to `$(PKG_BUILD_DIR)`.
   - For more detail information, check [hello_world](feeds/example/hello_world/Makefile) for example.

1. Re-check openwrt feeds and install them.
   ```
   ./scripts/feeds update -a && ./scripts/feeds install -a -f
   ```
   Check the log file if there's error messages.

1. Enable your package in openwrt config.
   ```
   make menuconfig
   ```
   Select your package as 'built-in', exit and save the config.

1. Build your package alone. This make sure your dependency is correct.
   ```
   make prepare; make V=s package/<your_package_dir_name>/compile
   ```
   If there's error when building your package, fix it and rebuild it again.
   ```
   make V=s package/<your_package_dir_name>/{clean,compile}
   ```

1. Copy changed openwrt config to `boards/` as defconfig. For example:
   ```
   cp .config ../boards/mtk11ax/config/mtk11ax.defconfig
   ```

1. Go back to the top directory. Run `build.py` to build all binaries and check the result.
   ```
   cd ../
   ./build.py --clean
   ./build.py
   ```

1. Commit your package files in `openwrt/nucleus/feeds/` and the changed openwrt config in `boards/`.

## How to enable a package by default?

1. Run `build.py` one time. Then change to the `openwrt` directory.
   ```
   cd openwrt
   ```

1. Enable your package in openwrt config.
   ```
   make menuconfig
   ```
   Select your package as 'built-in', exit and save the config.

1. Copy changed openwrt config to `boards/` as defconfig. For example:
   ```
   cp .config ../boards/mtk11ax/config/mtk11ax.defconfig
   ```

1. Go back to the top directory. Run `build.py` to build all binaries again.
   ```
   cd ../
   ./build.py --clean
   ./build.py
   ```

1. Commit the changed openwrt config in `boards/`.

## Package naming rules in general:

1. The package folder name in feed should be the same as `PKG_NAME` defined in each packages.

1. Zyxel proprietary packages:
   - Use the original package's name (without version number) as its `PKG_NAME` in openwrt.

1. Open source packages that is already provided by Openwrt (but with different version):
   - If we **DON'T** care about the package's version
     - Simply use the package from openwrt. There's no need to add it into repo.
   - If we care about the package's version, and it does not contain any modification from Zyxel
     - Use the same package name as openwrt. The package with the same name in this feed will override the one in openwrt. [^1]
   - If it contains modification from Zyxel, or the configuration is different with the one in openwrt
     - If the package is an application, add `PROWLAN_PREFIX` to its `PKG_NAME`.
     - If the package is a library, you should use the package name to override the origin one in order to maintain the dependency of other packages.[^1]

[^1]: Make sure your package won't break the dependency with other openwrt packages. Which means you need to provide the same config options that is provided in original openwrt's package.
