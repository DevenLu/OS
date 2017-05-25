#include"console.h"
#include"print.h"
#include"gdt.h"

int kern_entry()
{
	init_gdt();
	console_clear();
	printk("hello world!\n");
	return 0;
}

