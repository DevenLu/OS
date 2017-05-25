#include"console.h"

int kern_entry()
{
	console_clear();
	console_write_color("hello, kernel!\n",rc_white,rc_red);
	return 0;
}

