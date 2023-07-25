# About project.yaml

## models

- Define `ZYXEL_REF` means that it would base on zyxel style to prepare image (boot loader / rootfs / logs / mrd / sysupgeade)
- Define `MTK11AX_REF` means that do nothing currently

## builds

- Define `zyxel_dts` means that it would base on config/zyxel-partition.xml to update related device tree

## image

- Define `default` means that it would base on zyxel style (fit image format) to pack firmware
- Define `squashfs-mtk` means that it would base on openwrt style (sysupgrade.bin) to pack firmware
- Define `qsdk` means that it would base on qualcomm style (run update_common_info.py) to pack firmware

## release

- Define `default` means that it would base on zyxel style to pack release image (rename and pack related image)
- Define `archive` means that it would use tar to pack release image
- Define `openwrt` means that it would just copy specific image as release image
