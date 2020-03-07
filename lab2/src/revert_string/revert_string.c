#include "revert_string.h"
#include "string.h"
#include "stdio.h"

void RevertString(char *str)
{
	int len=strlen(str);
    int i=0;
       for( i=len-1;i>=0;i--){
           printf("%c", str[i]);
           
       }
       printf("\n");
}


