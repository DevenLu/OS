#include"console.h"
#include"print.h"
#include"gdt.h"
#include"idt.h"
#include"timer.h"

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
	
	//开启中断，这样我们设定好的timer就会按照时间给出中断
	asm volatile("sti");
	
	return 0;
}

