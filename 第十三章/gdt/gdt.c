#include "print.h"
#include "gdt.h"

// 全局描述符表个数
#define GDT_LENGTH 5

// 全局描述符表定义
g_descriptor gdt[GDT_LENGTH];

// GDTR
gdtr gdt_ptr;

// 全局描述符表构造函数，根据下标构造
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// 声明内核栈地址
extern uint32_t stack;

// 初始化全局描述符表
void init_gdt()
{
	// 全局描述符表界限 e.g. 从 0 开始，所以总长要 - 1
	gdt_ptr.limit = sizeof(g_descriptor) * GDT_LENGTH - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	// 采用 Intel 平坦模型
	gdt_set_gate(0, 0, 0, 0, 0);             	// 按照 Intel 文档要求，第一个描述符必须全 0
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 	// 指令段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 	// 用户模式数据段

	// 加载全局描述符表地址到 GPTR 寄存器
	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt[num].base_low     = (base & 0xFFFF);
	gdt[num].base_middle  = (base >> 16) & 0xFF;
	gdt[num].base_high    = (base >> 24) & 0xFF;

	gdt[num].limit_low    = (limit & 0xFFFF);
	gdt[num].granularity  = (limit >> 16) & 0x0F;
	gdt[num].granularity |= gran & 0xF0;
	gdt[num].access       = access;
}

