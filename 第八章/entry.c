#include"console.h"
#include"print.h"
#include"gdt.h"
#include"idt.h"
#include"pmm.h"
#include"timer.h"
#include"types.h"

int kern_entry()
{
	init_gdt();
	init_idt();
	console_clear();
	printk("hello world!\n");
	asm volatile ("int $0x3");
	asm volatile ("int $0xFF");
	asm volatile ("int $0x20");
	init_timer(200);
	
	//asm volatile("sti");
	printk("kernel in memory start: 0x%x\n",kern_start);
	printk("kernel in memory end: 0x%x\n",kern_end);
	printk("kernel in memory used: %d KB\n\n",(kern_end-kern_start+1023)/1024);
	
	show_memory_map();
	return 0;
}

