#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>

int simple_init(void) {
	printk(KERN_INFO "Loading module\nHola :D");
	return 0;
}

void simple_exit(void) {
	printk(KERN_INFO "Removing module\nAdios :D");
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Esta es mi descripcion personalizada");
MODULE_AUTHOR("Josue Sagastume");