//
// Created by yungu on 2022/4/19.
//
#ifndef REDIS_LEARN_SDS_H
#define REDIS_LEARN_SDS_H

#include <stdint.h>
#include <sys/types.h>

/**
 * 为了优化内容，redis 通过设置不同的sdshrd 来减少sds字符头部占用字节，并编译时不对其字节
 */
typedef char *sds;

#define SDS_TYPE_8  1
#define SDS_TYPE_16 2
#define SDS_TYPE_32 3
#define SDS_TYPE_64 4

#define SDS_HDR_VAR(T, s)  struct sds_header##T##_t *sh=(void*)((s)-sizeof(struct sds_header##T##_t));
#define SDS_HDR_PTR(T, s) ((struct sds_header##T##_t*)((s)-sizeof(struct sds_header##T##_t)))

struct __attribute__((packed)) sds_header8_t {
    uint8_t len;
    uint8_t alloc;
    unsigned char flag;
    char buf[];
};

struct __attribute__((packed)) sds_header16_t {
    uint16_t len;
    uint16_t alloc;
    unsigned char flag;
    char buf[];

};

struct __attribute__((packed)) sds_header32_t {
    uint32_t len;
    uint32_t alloc;
    unsigned char flag;
    char buf[];

};

struct __attribute__((packed)) sds_header64_t {
    uint64_t len;
    uint64_t alloc;
    unsigned char flag;
    char buf[];
};

sds sdsnewlen(const void *init, size_t initlen);

sds sdsdup(const sds s);

void sdsfree(sds s);

sds sdsMakeRoomFor(sds s, size_t addlen);

#endif //REDIS_LEARN_SDS_H
