#include"console.h"
#include"print.h"

int kern_entry()
{
	console_clear();
	printk("hello world!\n");
	return 0;
}

