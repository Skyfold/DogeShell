#ifndef DYNAMIC_CHAR_ARRAY_H
#define DYNAMIC_CHAR_ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

union ArrayOrStruct{
    struct DCharArray* DArray;
    char* CharArray;
    fpos_t* filePosition;
}ArrayOrStruct;

struct DCharArray{
    union ArrayOrStruct* DList;
    int max;
    int current_pos;
    int hist_pos;
} DCharArray;

//struct DCharArray* DCharArray_add(struct DCharArray* list, fpos_t* pos);
struct DCharArray* DCharArray_add(struct DCharArray* list, char* word);
struct DCharArray* DCharArray_add_from_file(struct DCharArray* list);
struct DCharArray* Init_DCharArray(void);
struct DCharArray* DCharArray_upHist(struct DCharArray* list);
struct DCharArray* DCharArray_downHist(struct DCharArray* list);
#endif