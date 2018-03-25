#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */

const char *byte_to_binary(short x);
void arg_int(int a, int b);

int main()
{

   //int a = 1;
   //int *pa = &a;
  
   //char ca = '1';
   //int m = (int)ca; 
  
   //long int result;
   //char *szNumber = "f";
   //result = strtol(szNumber, NULL, 0);
   //printf("f-0 result: %d \n", (unsigned char)result);
   //result = strtol(szNumber, NULL, 16);
   //printf("f-16 result: %d \n", (unsigned char)result);
   
   //short tag = ((short)-1) >> 1;
   //printf("tag: %d\n", tag);
   //printf("%s\n", byte_to_binary((((unsigned short)-1) >> 1)));
   //printf("%d\n", (unsigned int)(-1) >> 1);
   
   //short a = 0xffff;
   //unsigned short ua = 0xffff;
   //printf("a: %hd ua: %hu \n", a, ua);

   //long a = 0xffffffffffffffff;
   //unsigned long ua = 0xffffffffffffffff;
   //printf("a: %ld ua: %ld \n", a, ua);

   //long a = 0xffff;
   //unsigned long ua = 0xffff;
   //arg_int(a, ua);  

   //int a = 0xffffffff;
   //unsigned int ua = 0xffffffff;
   //int moved_a = a >> 1;
   //unsigned int moved_ua = ua >> 1;
   //printf("a: %x \nua: %x \n", a >> 1, ua >> 1);
   //printf("moved_a: %x \nmoved_ua: %x \n", moved_a, moved_ua);

   int a = 0xffffffff;
   long mask = -1UL >> 64;
   printf("%lx", mask);

   return 0;

}

const char *byte_to_binary(short x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void arg_int(int a, int b) {}
