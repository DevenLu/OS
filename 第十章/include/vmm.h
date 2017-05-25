#ifndef INCLUDE_VMM_H
#define INCLUDE_VMM_H

#include "types.h"

// 内核的偏移地址
#define PAGE_OFFSET 	0xC0000000

//页表项的第1位，存在位
#define PAGE_PRESENT 	0x1

//页表项的第2位，读写位
#define PAGE_WRITE 	0x2

//页表项的第3位，权限位
#define PAGE_USER 	0x4

// 虚拟分页大小
#define PAGE_SIZE 	4096

// 页掩码，用于 4KB 对齐
#define PAGE_MASK      0xFFFFF000

// 获取一个地址的页目录项
#define PGD_INDEX(x) (((x) >> 22) & 0x3FF)

// 获取一个地址的页表项
#define PTE_INDEX(x) (((x) >> 12) & 0x3FF)

// 获取一个地址的页內偏移
#define OFFSET_INDEX(x) ((x) & 0xFFF)

// 页目录数据类型
typedef uint32_t pgd_t;

// 页表数据类型
typedef uint32_t pte_t;

// 页目录成员数
#define PGD_SIZE (PAGE_SIZE/sizeof(pte_t))

// 页表成员数
#define PTE_SIZE (PAGE_SIZE/sizeof(uint32_t))

// 映射 512MB 内存所需要的页表数
#define PTE_COUNT 128

// 内核页目录区域
extern pgd_t pgd_kern[PGD_SIZE];

#endif 	// INCLUDE_VMM_H
