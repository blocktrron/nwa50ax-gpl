GPL Software Readme

1. Download & install Ubuntu 18.04 Desktop image for 64-bit PC (only this version is guranteed)

2. Install the following packages
   $ sudo apt install build-essential autoconf autoconf-archive automake gcc-multilib libtool pkgconf gawk flex bison python python-dev python-libxml2 python-setuptools xsltproc u-boot-tools mtd-utils ccache libncurses5-dev git-core zlib1g-dev swig libxml2-utils

3. Change /bin/sh to use bash instead of dash
   $ sudo sh -c 'printf "dash dash/sh boolean false" | debconf-set-selections'
   $ sudo DEBIAN_FRONTEND=noninteractive dpkg-reconfigure dash

4. Extract the GPL file.
   $ mkdir /path/to/gpl && cd /path/to/gpl
   $ tar xvf /path/to/gpl_filename.tar.xz

5. Install Zyxel packages
   $ tar xvf packages.tar
   $ sudo apt install ./*.deb

6. Build the runtime image from the source code.
   $ ./build.py --target=nwa50ax

   The firmware image will locate at ./bin/nwa50ax-fullimage.*.bin
   You can use it update by using the firmware update procedure.
