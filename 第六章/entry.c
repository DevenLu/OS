#include"console.h"
#include"print.h"
#include"gdt.h"
#include"idt.h"

int kern_entry()
{
	init_gdt();
	init_idt();
	console_clear();
	printk("hello world!\n");
	asm volatile ("int $0x3");
	asm volatile ("int $0xFF");
	return 0;
}

