#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// 全局描述符类型
typedef
struct g_descriptor {
	uint16_t limit_low;     // 段界限   0~15
	uint16_t base_low;      // 段基地址 16~31
	uint8_t  base_middle;   // 段基地址 32~39
	uint8_t  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别
	uint8_t  granularity; 	// 其他标志、段界限 19～16
	uint8_t  base_high;     // 段基地址 56~63
} __attribute__((packed)) g_descriptor;

// GDTR
typedef
struct gdtr{
	uint16_t limit; 	// 全局描述符表限长
	uint32_t base; 		// 全局描述符表 32位 基地址
} __attribute__((packed)) gdtr;

// 初始化全局描述符表
void init_gdt();

// GDT 加载到 GDTR 的函数[汇编实现]
extern void gdt_flush(uint32_t);

#endif 	// INCLUDE_GDT_H_
