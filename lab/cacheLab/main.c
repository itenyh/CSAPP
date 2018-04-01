//
//  main.c
//  TestConmandLine
//
//  Created by Iten on 2018/1/5.
//  Copyright © 2018年 Iten. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include <unistd.h>

#define ADD_LENGTH 64

typedef struct {
    int valid;
    long tag;
    unsigned long counter;
} cache_line;

typedef struct {
    cache_line *lines;
} cache_set;

typedef struct {
    cache_set *sets;
    
    int hit;
    int miss;
    int miss_eviction;
    
    long E;
    long b;
    long s;
    
} cache;

void main_work(long addNumber, char action, cache *c);
void print_cache(cache c, long E, long S);
cache init_cache(long E, long S, long b);
int is_hitted(cache *c, long tag, long set);
int store_cache_inset_new(cache *c, long tag, long set);
void store_cache_inset_replace(cache *c, long tag, long set);
void manipulate_cache(cache *c, long set, long tag);
void get_parameter(int argc, const char * argv[], unsigned long *s, unsigned long *E, unsigned long *b, char **tracefile);

int main(int argc, const char * argv[]) {

    unsigned long E = 0;
    unsigned long b = 0;
    unsigned long s = 0;
    char *tracefile;
    
    get_parameter(argc, argv, &s, &E, &b, &tracefile);
    cache c = init_cache(E, s, b);

    FILE * pFile;
    pFile = fopen (tracefile, "r");
    char action;
    unsigned address;
    int size;
    
    while(fscanf(pFile , "\n%c %x,%d\n", &action, &address, &size) > 0) {
        main_work(address, action, &c);
    }
    fclose(pFile);
    
    printf("hit: %d miss: %d miss_eviction: %d \n", c.hit, c.miss, c.miss_eviction);
//    printSummary(c.hit, c.miss, c.miss_eviction);
    
    return 0;
    
}

void get_parameter(int argc, const char * argv[], unsigned long *s, unsigned long *E, unsigned long *b, char **tracefile) {
    
    char ch;
    while ((ch = getopt(argc, (char *const *)argv, "s:E:b:t:")) != -1) {
        
        switch (ch) {
            case 's':
                *s = strtol(optarg, NULL, 10);
                break;
            case 'E':
                *E = strtol(optarg, NULL, 10);
                break;
            case 'b':
                *b = strtol(optarg, NULL, 10);
                break;
            case 't':
                *tracefile = optarg;
                break;
            default:
                break;
        }
    }
    
}

void main_work(long addNumber, char action, cache *c) {
    
    long s = c->s;
    long b = c->b;
    long t = ADD_LENGTH - s - b;
    
    long tagMask = -1UL >> (s + b);
    long tag = (addNumber >> (s + b)) & tagMask;
    
    long setMask = -1UL >> (t + b);
    long set = (addNumber >> b) & setMask;
    
    if (action == 'L' || action == 'S') {
        
        manipulate_cache(c, set, tag);
        
    }
    
    else {
        
        manipulate_cache(c, set, tag);
        manipulate_cache(c, set, tag);
        
    }
    
}

cache init_cache(long E, long s, long b) {
    
    cache c;
    cache_set *sets = malloc(sizeof(cache_set) * (1 << s));
    c.sets = sets;
    for (int set_index = 0; set_index < (1 << s); set_index++) {
        cache_line *lines = malloc(sizeof(cache_line) * E);
        for (int line_index = 0; line_index < E; line_index++) {
            cache_line *line = lines + line_index;
            line->counter = 0;
            line->tag = 0;
            line->valid = 0;
        }
        c.sets[set_index].lines = lines;
    }
    
    c.hit = 0;
    c.miss = 0;
    c.miss_eviction = 0;
    c.b = b;
    c.E = E;
    c.s = s;
    
    return c;
    
}

void manipulate_cache(cache *c, long set, long tag) {
    
    int hitted = is_hitted(c, tag, set);
    int missed = 0;
    
    if (!hitted) {
        missed = store_cache_inset_new(c, tag, set);
        if (!missed) {
            store_cache_inset_replace(c, tag, set);
        }
    }
    
    if (hitted) {
        printf("hit \n");
        c->hit++;
    }
    else {
        if (missed) {
            printf("miss \n");
            c->miss++;
        }
        else {
            printf("miss eviction \n");
            c->miss++;
            c->miss_eviction++;
        }
    }
    
}

int is_hitted(cache *c, long tag, long set) {
    
    int is = 0;
    cache_line *lines = c->sets[set].lines;
    for (int i = 0; i < c->E; i++) {
        cache_line *line = lines + i;
        if (line->valid == 1 && line->tag == tag) {
            line->counter++;
            is = 1;
            break;
        }
    }
    
    return is;
    
}

int store_cache_inset_new(cache *c, long tag, long set) {
    
    int success = 0;
    cache_line *lines = (c->sets + set)->lines;
    for (int i = 0; i < c->E; i++) {
        cache_line *line = (lines + i);
        if (line->valid == 0) {
            line->tag = tag;
            line->counter = 1;
            line->valid = 1;
            success = 1;
            break;
        }
    }
    return success;
    
}

void store_cache_inset_replace(cache *c, long tag, long set) {
    
    cache_line *lines = (c->sets + set)->lines;
    
    int lru_index = 0;
    long lru = ULONG_MAX;
    for (int i = 0; i < c->E; i++) {
        cache_line line = lines[i];
        if (line.counter < lru) {
            lru = line.counter;
            lru_index = i;
        }
    }
    
    cache_line *target_c = (lines + lru_index);
    target_c->tag = tag;
    target_c->counter = 1;
    
}

void print_cache(cache c, long E, long S) {
    
    for (long set_index = 0; set_index < S; set_index++) {
        cache_set cs = c.sets[set_index];
        for (int line_index = 0; line_index < E; line_index++) {
            cache_line cl = cs.lines[line_index];
            printf("cache in set: %ld | line_index: %d | tag: %ld | valid: %d | counter: %lu \n", set_index, line_index, cl.tag, cl.valid, cl.counter);
        }
    }
    
    
}

//cache *c = malloc(sizeof(cache));
//cache_set *sets = malloc(sizeof(cache_set) * S);
//c->sets = sets;
//for (int set_index = 0; set_index < S; set_index++) {
//    cache_line *lines = malloc(sizeof(cache_line) * E);
//    for (int line_index = 0; line_index < E; line_index++) {
//        cache_line *line = lines + line_index;
//        line->counter = 10;
//        line->tag = 0;
//        line->valid = 0;
//    }
//    c->sets[set_index].lines = lines;
//}

//    long blockMask = -1UL >> (t + s);
//    long block = addNumber & blockMask;

//    printf("addNumber: %lx tag: %lx set: %lx block: %lx\n", addNumber, tag, set, block);


//│0x40052d <main>                 push   %rbp
//│0x40052e <main+1>               mov    %rsp,%rbp
//│0x400531 <main+4>               sub    $0x10,%rsp
//B+ │0x400535 <main+8>               mov    $0x190,%edi
//>  │0x40053a <main+13>              callq  0x400430 <malloc@plt>
//│0x40053f <main+18>              mov    %rax,-0x8(%rbp)
//│0x400543 <main+22>              mov    -0x8(%rbp),%rax
//│0x400547 <main+26>              add    $0xc,%rax
//>│0x40054b <main+30>              movl   $0x1,(%rax)
//│0x400551 <main+36>              mov    $0x0,%eax
//│0x400556 <main+41>              leaveq
//│0x400557 <main+42>              retq

//0x4004ed <main>                 push   %rbp
//│0x4004ee <main+1>               mov    %rsp,%rbp
//│0x4004f1 <main+4>               sub    $0x118,%rsp
//B+>│0x4004f8 <main+11>              movl   $0x1,-0x184(%rbp)
//│0x400502 <main+21>              mov    $0x0,%eax
//│0x400507 <main+26>              leaveq
//│0x400508 <main+27>              retq

