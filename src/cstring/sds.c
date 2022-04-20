
//
// Created by yungu on 2022/4/19.
//
#include "sds.h"
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "sds_malloc.h"
#include <string.h>

size_t sdsHdrSize(char type);

char get_sds_type(size_t initlen) {
    if (initlen < 1 << 8) {
        return SDS_TYPE_8;
    } else if (initlen < 1 << 16) {
        return SDS_TYPE_16;
    }
#if (LONG_MAX == LLONG_MAX)
    if (initlen < 1ll << 32)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
#else
    return SDS_TYPE_32;
#endif
}

static inline size_t sdslen(sds s) {
    char *flag = s - 1;
    size_t size = 0;
    switch (*flag) {
        case SDS_TYPE_8: {
            size = SDS_HDR_PTR(8, s)->len;
            break;
        }
        case SDS_TYPE_16: {
            size = SDS_HDR_PTR(16, s)->len;
            break;
        }
        case SDS_TYPE_32: {
            size = SDS_HDR_PTR(32, s)->len;
            break;
        }
        case SDS_TYPE_64: {
            size = SDS_HDR_PTR(64, s)->len;
            break;
        }
    }
    return size;
}

sds sdsnewlen(const void *init, size_t initlen) {
    sds s;
    char type = get_sds_type(initlen);
    size_t header_size = sdsHdrSize(type);
    assert(header_size + initlen + 1 > initlen);

    size_t usable = initlen;
    void *p = sds_malloc(header_size + initlen + 1, &usable);
    if (!p) {
        return NULL;
    }
    memset(p, 0, header_size + initlen + 1);
    s = p + header_size;

    switch (type) {
        case SDS_TYPE_8: {
            SDS_HDR_VAR(8, s);
            sh->flag = type;
            sh->alloc = usable;
            sh->len = initlen;
            break;
        }
        case SDS_TYPE_16: {
            SDS_HDR_VAR(16, s);
            sh->flag = type;
            sh->alloc = usable;
            sh->len = initlen;
            break;
        }

        case SDS_TYPE_32: {
            SDS_HDR_VAR(32, s);
            sh->flag = type;
            sh->alloc = usable;
            sh->len = initlen;
            break;
        }
        case SDS_TYPE_64: {
            SDS_HDR_VAR(64, s);
            sh->flag = type;
            sh->alloc = usable;
            sh->len = initlen;
            break;
        }
    }
    memcpy(s, init, initlen);
    s[initlen] = 0;
    return s;
}

void print(sds s) {
    size_t size = sdslen(s);
    size_t pos = 0;
    while (size--) {
        printf("%c", *(s + pos++));
    }
    printf("\n");
}

sds sdsdup(sds s) {
    return sdsnewlen(s, sdslen(s));
}

void sdsfree(sds s) {
    sds_free(s - sdsHdrSize(*(s - 1)));
}


size_t sdsHdrSize(char type) {
    if (type == SDS_TYPE_8) {
        return sizeof(struct sds_header8_t);
    }
    if (type == SDS_TYPE_16) {
        return sizeof(struct sds_header16_t);
    }
    if (type == SDS_TYPE_32) {
        return sizeof(struct sds_header32_t);
    }
    if (type == SDS_TYPE_64) {
        return sizeof(struct sds_header64_t);
    }
    return 0;
}

int main() {

    printf("sizeof:%lu\n", sizeof(struct  sds_header8_t));
    printf("sizeof:%lu\n", sizeof(struct  sds_header16_t));
    printf("sizeof:%lu\n", sizeof(struct  sds_header32_t));
    printf("sizeof:%lu\n", sizeof(struct  sds_header64_t));

    char abc[] = {"abcdef\n123"};
    sds s = sdsnewlen(abc, 11);
    SDS_HDR_VAR(8, s);
    //printf("len:%d\n", sh->len);
   // printf("alloc:%d\n", sh->alloc);
   // printf("flag:%d\n", sh->flag);
   // print(s);

    sds s1 = sdsdup(s);
  //  print(s1);

   // sdsfree(s);
    sdsfree(s1);
  //  printf("free-s:%s\n", s);
  //  printf("free-s1:%s\n", s1);
  //  printf("free-s:%s\n", s);
}
