#include "/projects/os_lab_2019/lab2/src/swap/swap.h"
#include "string.h"

void Swap(char *left, char *right)
{
	char t=*left;
    *left=*right;
    *right=t;
   
}