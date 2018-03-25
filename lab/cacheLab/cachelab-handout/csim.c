#include <stdio.h>
#include <stdlib.h>
#include "cachelab.h"

struct CacheLine {
  int valid;
  long tag;
};

int main()
{

    //Assume that s, b, t are bigger than zero
 
    //char *input = "L 04f6b868,8";
    //    // char *address = "04f6b868"
    int m = 64;
    int s = 16;
    //int S = 1;
    //int E = 1;
    int b = 8;
    int t = m - s - b;
    
    //struct CacheLine cache[S][E];

    char *addString = "04f6b868";
    char action = 'S';

    long addNumber = strtol(addString, NULL, 16);
    
    long tagMask = -1UL >> (s + b);
    long tag = (addNumber >> (s + b)) & tagMask;
   
    long setMask = -1UL >> (t + b);
    long set = (addNumber >> b) & setMask;

    long blockMask = -1UL >> (t + s);
    long block = addNumber & blockMask;

            

    printf("addNumber: %lx\ntag: %lx\nset: %lx\nblock: %lx\n", addNumber, tag, set, block);
    
    //Get CacheLine
    

    //printSummary(0, 0, 0);
    return 0;

}
