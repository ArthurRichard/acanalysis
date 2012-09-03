#include "TAList.h"
#include <windows.h>
void memcmp_ta(void * dst,const void * src , unsigned int size)
{
	memcpy_s(dst,size,src,size);
}