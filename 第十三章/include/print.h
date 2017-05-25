#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

#include "types.h"

//进制转换
char *convert(uint32_t num, int32_t base);

// 内核的打印函数
void printk(char *str, ...);

#endif
