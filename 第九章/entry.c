#include"console.h"
#include"print.h"
#include"gdt.h"
#include"idt.h"
#include"timer.h"
#include"pmm.h"

int kern_entry()
{
	init_gdt();
	init_idt();
	console_clear();
	printk("hello world!\n");

	init_timer(200);
	
	//asm volatile("sti");
	printk("kernel in memory start: 0x%x\n",kern_start);
	printk("kernel in memory end: 0x%x\n",kern_end);
	printk("kernel in memory used: %d KB\n\n",(kern_end-kern_start+1023)/1024);
	
	show_memory_map();
	init_pmm();
		
	printk("\nThe Count of Physical Memory Page is: %d\n\n", phy_page_count);

	uint32_t allc_addr = NULL;
	printk("Test Physical Memory Alloc :\n");
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: 0x%x\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: 0x%x\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: 0x%x\n", allc_addr);
	allc_addr = pmm_alloc_page();
	printk("Alloc Physical Addr: 0x%x\n", allc_addr);
	return 0;
}

