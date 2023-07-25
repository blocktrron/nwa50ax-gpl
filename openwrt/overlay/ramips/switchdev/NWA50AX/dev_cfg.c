#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#include <linux/module.h>
#include <linux/types.h>
#else
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/ptrace.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/major.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/init.h>
#include <linux/mtd/compatmac.h>
#include <linux/mtd/mtd.h>
#endif

#ifdef CONFIG_PROC_FS
#include <linux/proc_fs.h>
#endif
#include "switchdev.h"

static zld_port_cfg_t zld_port_tbl_mt76xx[] = {
{0, 0, "PORT1", "eth0", ZLD_SWITCH_TYPE_MT76XX, 0, -1, 4, 1, 1, 0, 0, ZLD_PORT_FLG_UPLINK_PORT},
{1, 1, "cpusw0", "eth_base", ZLD_SWITCH_TYPE_MT76XX, 0, -1, 6, 1, -1, 0, 0, ZLD_PORT_FLG_CPU_PORT},
{9999, 0, "", "", 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int port_cnt = 0;
int port_ext_cnt = 0;

int disp_port_table(zld_port_cfg_t *cfg_p, int cnt)
{
	int i = 0;

	printk("%-3s %-16s %3s %4s %4s %4s %4s %3s %3s %5s %-8s %4s\n",
		"No.", "If Name", "typ", "sidx", "ridx", "fidx", "midx", "phy",
		"psw", "psidx", "flag", "base");
	while (i < cnt) {
		printk("%-4.1u%-17.16s%-4.1x%-5.1u%-5.1d%-5.1d%-5.1d%-4.1d%-4.1x%-6.1u%-9.1x%-5.1u\n",
			cfg_p->ext_idx, cfg_p->name, cfg_p->sw_type,
			cfg_p->sw_idx, cfg_p->reg_idx, cfg_p->front_idx,
			cfg_p->mac_idx, cfg_p->phy_addr, cfg_p->phy_cfg_sw,
			cfg_p->phy_sw_idx, cfg_p->flags, cfg_p->base_idx);
		cfg_p++;
		i++;
	}
	return 0;
}

static zld_port_cfg_t *get_switch_table_by_type_idx(int switch_type, int switch_idx)
{
	switch (switch_type) {
	case ZLD_SWITCH_TYPE_MT76XX:
		return zld_port_tbl_mt76xx;
	default:
		printk("<0> This product don't support this switch %d\n", switch_type);
		break;
	}
	return NULL;
}

/* Each switch we should call this function */
int zld_port_table_add(int index, int switch_type, int switch_idx)
{
	zld_port_cfg_t *tbl_p = get_zld_port_cfg_table();
	zld_port_cfg_t *cfg_tbl = get_switch_table_by_type_idx(switch_type, switch_idx);
	zld_port_cfg_t *port_p, *cfg_port_p;
	int cpu_port = -1;
	int eth_base = -1;

	if (cfg_tbl == NULL) return 0;
//	disp_port_table(cfg_tbl, get_zld_port_table_cnt(cfg_tbl));
	/* process the cpu port & eth_base first */
	cfg_port_p = cfg_tbl;
	while (cfg_port_p->ext_idx != ZLD_CFG_TBL_END) {
		if ((cfg_port_p->flags & ZLD_PORT_FLG_CPU_PORT) != 0) {
			cfg_port_p->reg_idx = index;
			cpu_port = cfg_to_ext_cfg_table(cfg_port_p);
		}
		else if ((cfg_port_p->flags & ZLD_PORT_FLG_ETHBASE) != 0) {
			cfg_port_p->reg_idx = index;
			eth_base = cfg_to_ext_cfg_table(cfg_port_p);
		}
		cfg_port_p++;
	}

	/* process other port */
	cfg_port_p = cfg_tbl;
	while (cfg_port_p->ext_idx != ZLD_CFG_TBL_END) {
		port_p = tbl_p + cfg_port_p->ext_idx;

		/* none cpu & eth_base
			if the dest table port->ext_idx == 0 means no one occupy it. Thus, we fill it.
		*/
		if ((cfg_port_p->flags & (ZLD_PORT_FLG_CPU_PORT | ZLD_PORT_FLG_ETHBASE)) == 0) {
			port_cnt++;
			if (port_p->ext_idx == ZLD_CFG_TBL_END) {
				memcpy(port_p, cfg_port_p, sizeof(zld_port_cfg_t));
				port_p->reg_idx = index;
				port_p->cpu_port = cpu_port;
			}
			else {
				printk("<0>%s: Fail. We should not have two switchs in the same port at this product.\n", __FUNCTION__);
			}
		}
		cfg_port_p++;
	}

//	disp_port_table(get_zld_port_cfg_table(), ZLD_MAX_ETHER_PORT_NUM);
//	disp_port_table(get_zld_port_ext_cfg_table(), ZLD_MAX_ETHER_PORT_NUM);

	return 0;
}

/****************************************************************************
* zld_port_table_adjust
*
*	This function adjst real switch ether_base indxe. For those sudo switch
*	The base_idx will be ZLD_CFG_TBL_END.
*
*
****************************************************************************/
int zld_port_table_adjust(void)
{
	int cnt = port_cnt;
	int i;
	zld_port_cfg_t *tbl_p = get_zld_port_cfg_table();
	zld_port_cfg_t *port_p;

//	printk("<0>%s: port_cnt = %d\n", __FUNCTION__, cnt);
	port_p = tbl_p;
	for (i = 0; i < cnt; i++, port_p++) {
		port_p->base_idx = find_ext_cfg_table_idx_by_name(port_p->base_name);
	}
	return 0;
}

EXPORT_SYMBOL(zld_port_table_add);
EXPORT_SYMBOL(zld_port_table_adjust);
