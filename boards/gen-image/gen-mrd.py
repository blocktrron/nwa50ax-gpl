#!/usr/bin/env python3

import json
import os
import struct
import xml.etree.ElementTree as ET
from optparse import OptionParser
from pathlib import Path

part_xml_root = ET.parse('config/zyxel-partition.xml')

class PartInfo:
    def __init__(self, name, size):
        self.name = name
        self.size = size

def get_part_info(part_name):
    name = part_name
    flash = part_xml_root.find(f"./partition/[name='{part_name}']/flash").text
    # If NOR, the MRD size is the overall partition size.
    # If NAND, the MRD size is the block size to handle bad block.
    if flash == "nand":
        size = int(part_xml_root.find(f"./partition/[name='{part_name}']/block_size").text)
    else:
        size = int(part_xml_root.find(f"./partition/[name='{part_name}']/size").text)

    return PartInfo(name, size)

class Product:
    def __init__(self, name, model_id, mac_qty):
        self.name = name
        self.model_id = model_id
        self.mac_qty = mac_qty

    def __str__(self):
        return "name: %s, model_id: %s, mac_qty: %s" % (self.name, self.model_id, self.mac_qty)

def parse_args():
    parser = OptionParser(usage="usage: %prog <mrd.json> -d <output_dir>")
    parser.add_option("-d",
                      action="store",
                      dest="output_dir",
                      help="specify the output directory")
    (options, args) = parser.parse_args()

    if len(args) != 1:
        parser.error("no input file specified")

    if options.output_dir is None:
        parser.error('no output directory specified')

    return options, args

if __name__ == '__main__':
    options, args = parse_args()

    products = []
    names = sorted([x for x in os.environ if 'ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME_' in x])
    model_ids = sorted([x for x in os.environ if 'ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL_' in x])
    mac_qtys = sorted([x for x in os.environ if 'ZLDSYSPARM_COMPATIBLE_PRODUCT_MAC_QTY_' in x])
    for name, model_id, mac_qty in zip(names, model_ids, mac_qtys):
        name = os.getenv(name).strip('\"')
        model_id = os.getenv(model_id).strip('\"')
        mac_qty = os.getenv(mac_qty).strip('\"')
        if name:
            products.append(Product(name, model_id, mac_qty))

    with open(args[0]) as f:
        mrd = f.read()
    mrd = mrd.replace('@ZLDSYSPARM_PLATFORM_NAME@', os.environ['ZLDSYSPARM_PLATFORM_NAME'].upper().replace('"', ''))
    os.makedirs(options.output_dir, exist_ok=True)

    mrd_format = '3s16B16B32s32s32B32s32s4B2BBBHB13BB13BBB6BBB'
    mrd_padding = get_part_info('mrd').size * 1024 \
                  - struct.calcsize('=%s' % mrd_format)
    mrd_format = '<%dx%s' % (mrd_padding, mrd_format)

    for product in products:
        output_file = os.path.join(options.output_dir,
                                   'mrd-%s.bin' % product.name)
        default_file = os.path.join(options.output_dir, 'mrd.bin')

        fp = open(output_file, 'wb')

        product_mrd = mrd
        product_mrd = product_mrd.replace('@ZLDSYSPARM_COMPATIBLE_PRODUCT_NAME@',
                                          product.name)
        product_mrd = product_mrd.replace('@ZLDSYSPARM_COMPATIBLE_PRODUCT_MODEL@',
                                          product.model_id)
        product_mrd = product_mrd.replace('@ZLDSYSPARM_PRODUCT_MAC_QTY@',
                                          product.mac_qty)
        mrd_json = json.loads(product_mrd)

        output = struct.pack(mrd_format,
                            str.encode(mrd_json['magic']),
                            *([int(x, 16) for x in mrd_json['bsp_heap_blk_size']]),
                            *([int(x, 16) for x in mrd_json['bsp_heap_blk_cnt']]),
                            str.encode(mrd_json['hardware_version']),
                            str.encode(mrd_json['serial_number']),
                            *([int(x, 16) for x in mrd_json['reserved_0']]),
                            str.encode(mrd_json['verdor_name']),
                            str.encode(mrd_json['product_name']),
                            *([int(x, 16) for x in mrd_json['reserved_4']]),
                            *([int(x, 16) for x in mrd_json['reserved_1']]),
                            int(mrd_json['system_type'], 16),
                            int(mrd_json['reserved_2'], 16),
                            int(mrd_json['model_id'], 16),
                            int(mrd_json['mfg'], 16),
                            *([int(x, 16) for x in mrd_json['feature_bits_0']]),
                            int(mrd_json['macqty'], 16),
                            *([int(x, 16) for x in mrd_json['feature_bits_1']]),
                            int(mrd_json['feature_bit'], 16),
                            int(mrd_json['reserved_3'], 16),
                            *([int(x, 16) for x in mrd_json['ether_addr']]),
                            int(mrd_json['country_code'], 16),
                            int(mrd_json['area_code'], 16))
        fp.write(output)
        fp.close()

        if not os.path.isfile(default_file):
            fp = open(default_file, 'wb')
            fp.write(output)
            fp.close()
