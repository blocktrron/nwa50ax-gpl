static const model_list_t models[] = {
	/* model id, firmware id, product name, slot number, wirless mode, capability */
	/* for band mode, bit 0: support 2.4G, bit 1: support 5G */
	{{0x6B, 0xE1}, {"ABYW"}, "NWA50AX", 2, WHOPMODE_MAX, 0|CAPA_FCC_DFS_SUPPORT|CAPA_80211_AX, {0x01, 0x02}, 1, {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {2, 2},{2, 4, 2500}},
	{{0x6F, 0xE1}, {"ABZL"}, "NWA55AXE", 2, WHOPMODE_MAX, 0|CAPA_FCC_DFS_SUPPORT|CAPA_PLACEMENT_OUTDOOR|CAPA_80211_AX|CAPA_WIRELESS_BRIDGE, {0x01, 0x02}, 1, {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, {2, 2},{2, 4, 2500}},
};
