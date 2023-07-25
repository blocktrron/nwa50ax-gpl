mkfile_path = $(shell readlink $(MAKEFILE_LIST))
current_dir = $(abspath $(patsubst %/,%,$(dir $(mkfile_path))))

define prepare_zyxel_rootfs
	$(current_dir)/../script/zyxel-usr-merge.sh $(1)
	$(current_dir)/../../gen-image/script/prepare-conf-img.sh $(1)
endef
