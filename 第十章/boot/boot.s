MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 
MBOOT_PAGE_ALIGN 	equ 	1 << 0   
MBOOT_MEM_INFO 		equ 	1 << 1    
MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
 
GLOBAL start 		; 内核代码入口
GLOBAL mboot_ptr_tmp	  ;向外部声明的struct multiboot*变量
EXTERN kern_entry       ; 主函数入口

[BITS 32]             ; 内核以32位形式编译

section .init.text         ; 临时代码段

align 4               ; 4字节对齐

Multi_boot_header:           ; 声明变量，只用Multiboot Header必须的那些部分
	dd MBOOT_HEADER_MAGIC 	
	dd MBOOT_HEADER_FLAGS   
	dd MBOOT_CHECKSUM       	

start:			; 汇编的指令开始的地方

	cli  			 ; 此时还没有设置好保护模式的中断处理，所以必须关闭中断
	mov esp, STACK_TOP	; 设置内核栈地址	
	mov ebp, 0 	 		; 帧指针修改为 0
	mov [mboot_ptr_tmp], ebx     ; 将 ebx 中存储的指针存入全局变量
	call kern_entry		; 调用内核入口函数	 

section .init.data

stack: times 1024 db 0
STACK_TOP equ $-stack-1
mboot_ptr_tmp: dd 0


