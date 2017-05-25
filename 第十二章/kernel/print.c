#include "print.h"
#include "console.h"
#include "types.h"
#include "vargs.h"

//进制转换，在一个长度为50的栈里转换，所以这里有问题隐患，不是吗。
char *convert(unsigned int num, int base)
{
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);

	return(ptr);
}

//printk的实现
void printk(char *str, ...)
{
	va_list arg;		//声明一个va_list类型的变量，在宏定义里有说明
	va_start(arg, str);   //把printk()第一个参数取出到str中
	char *temp;         //用一个字符指针来作为我们的字符输出
	int i;
	for(temp=str;*temp;temp++)   //对我们的字符进行遍历
	{
	    if(*temp!='%')
            	putchar(*temp);  //如果字符是正常字符，则输出
		else{					 //当字符不是正常字符，而是用%标记的特定输出
			temp++;              //加一，取到%的下一个字符
			switch(*temp){       //对%标记做讨论
				case 'd':			
					i=va_arg(arg,int);  //将取到的参数按照int型赋值给i
					if(i<0)				//对i转换为10进制，讨论正负，输出
					{
						putchar('-');
						console_write(convert(-i,10));
					}
					else
						console_write(convert(i,10));
					break;
				case 'c':			
					i=va_arg(arg,int);  //将取到的参数按照int型赋值给i
					putchar(i);			//对i对于的ASCII码输出
					break;
                case 'o':
                   	i=va_arg(arg,unsigned int); //将取到的参数按照unsigned int型赋值给i
                   	console_write(convert(i,8));  //把i转换为8进制输出
					break;
                case 's':
               		i=(int)va_arg(arg, char*); //将取到的参数按照char*型赋值给i
                   	console_write((char*)i);
           			break;
              	case 'x':
               		i=va_arg(arg,unsigned int); //将取到的参数按照unsigned int型赋值给i
           			console_write(convert(i,16));              			break;
				case 'b':
					i=va_arg(arg,int); //将取到的参数按照int型赋值给i
					console_write(convert(i,2));
					break;	
				}
		}

	}
	va_end(arg);    //结束我们的arg，防止后序误调用引发错误
}

