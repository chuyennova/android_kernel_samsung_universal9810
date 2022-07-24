/*
 */

#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mman.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/raw.h>
#include <linux/tty.h>
#include <linux/capability.h>
#include <linux/ptrace.h>
#include <linux/device.h>
#include <linux/highmem.h>
#include <linux/crash_dump.h>
#include <linux/backing-dev.h>
#include <linux/bootmem.h>
#include <linux/splice.h>
#include <linux/pfn.h>
#include <linux/export.h>
#include <linux/seq_file.h>

#include <linux/uaccess.h>
#include <linux/io.h>

#define KAP_RET_SIZE	5
static int knox_kap_read(struct seq_file *m, void *v)
{
	unsigned char ret_buffer[KAP_RET_SIZE];

	memset(ret_buffer, 0, KAP_RET_SIZE);
	snprintf(ret_buffer, sizeof(ret_buffer), "%02x\n", 0x11); //KAP is ON and will stay ON
	seq_write(m, ret_buffer, sizeof(ret_buffer));

	return 0;
}
static int knox_kap_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, knox_kap_read, NULL);
}

long knox_kap_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

const struct file_operations knox_kap_fops = {
	.open	= knox_kap_open,
	.release	= single_release,
	.read	= seq_read,
	.unlocked_ioctl  = knox_kap_ioctl,
};
