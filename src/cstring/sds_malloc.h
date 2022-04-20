//
// Created by yungu on 2022/4/19.
//

#ifndef REDIS_LEARN_SDS_MALLOC_H
#define REDIS_LEARN_SDS_MALLOC_H

#include <malloc/malloc.h>
#include <stdlib.h>

#define  sds_malloc __malloc
#define  sds_free __free
//当你要判断单个宏是否定义时 #ifdef 和 #if defined 效果是一样的，
// 但是当你要判断复杂的条件时，只能用 #if defined
#if defined(__APPLE__)
#define HAVE_MALLOC_SIZE 1
#define PRE_SIZE 0
#else
#define PRE_SIZE 8

#endif

void __free(void *p){
    free(p);
}

void *__malloc(size_t size, size_t *usable) {
    void *p = malloc(size + PRE_SIZE);

#ifdef HAVE_MALLOC_SIZE
    *usable = malloc_size(p);
#elif
    *(size_t*)p=size;
    p=p+size;
#endif
    return p;
}

#endif //REDIS_LEARN_SDS_MALLOC_H
