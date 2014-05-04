#include "dynamic_char_array.h"
#include <string.h>
#include "linked_list.h"

/*
union ArrayOrStruct{
    struct DCharArray* DArray;
    char* CharArray;
    fpos_t* filePosition;
}ArrayOrStruct;

struct DCharArray{
    union ArrayOrStruct* DList;
    int max;
    int current_pos;
} DCharArray;
*/

const int INIT_SIZE = 64;
const int INIT_CURRENT = 0;
const int INIT_HIST_POS = 0;

struct DCharArray* Init_DCharArray(void){
    struct DCharArray * list = (struct DCharArray *) malloc(sizeof(struct DCharArray));
    list->max = INIT_SIZE;
    list->current_pos = INIT_CURRENT;
    list->DList = NULL;
    list->hist_pos = INIT_HIST_POS;
    return list;
}

struct DCharArray* DCharArray_add(struct DCharArray* list, char* word){
    union ArrayOrStruct subList;
    subList.CharArray = word;
    if(list->DList == NULL){
        list->DList = (union ArrayOrStruct*)malloc(list->max*sizeof(union ArrayOrStruct));
    }
    if(list->current_pos <= list->max){
        list->DList[list->current_pos] = subList;
        list->current_pos++;
        list->hist_pos = list->current_pos;
    }else{
        list->max = list->max*2;
        list->DList = (union ArrayOrStruct*)realloc(list->DList, list->max*sizeof(union ArrayOrStruct));
        list->DList[list->current_pos] = subList;
        list->current_pos++;
        list->hist_pos = list->current_pos;
    }
    return list;
}

struct DCharArray* DCharArray_add_from_file(struct DCharArray* list){
    char* home = getenv("HOME");
    char homeCopy[64];
    strcpy(homeCopy, home);
    FILE* Hist = fopen(strcat(homeCopy,"/.DogeHistory"), "r");
    if(Hist != NULL){
        char* str = (char*)malloc(1024*sizeof(char));
        fgets(str, 1024, Hist);
        char* pch = strtok(str, "\037");
        while (pch != NULL)
        {
            list = DCharArray_add(list, pch);
            pch = strtok(NULL, "\037");
        }
    }
    fclose(Hist);
    return list;
}

struct DCharArray* DCharArray_upHist(struct DCharArray* list){
    if(list->hist_pos > 0) {
        list->hist_pos--;
        for (int i = 0; list->DList[list->hist_pos].CharArray[i] != '\0'; ++i)
        {
            printCharToTerminal(list->DList[list->hist_pos].CharArray[i]);
        }
    }
    return list;
}

struct DCharArray* DCharArray_downHist(struct DCharArray* list){
    if(list->hist_pos < list->current_pos-1){
        list->hist_pos++;
        for (int i = 0; list->DList[list->hist_pos].CharArray[i] != '\0'; ++i)
        {
            printCharToTerminal(list->DList[list->hist_pos].CharArray[i]);
        }
    }else {
        list->hist_pos = list->current_pos;
    }
    return list;
}


// struct DCharArray* DCharArray_add(struct DCharArray* list, fpos_t* pos){
//     union ArrayOrStruct subList;
//     subList.filePosition = pos;
//     if(list->DList == NULL){
//         list->DList = (union ArrayOrStruct*)malloc(list->max*sizeof(union ArrayOrStruct));
//     }
//     if(list->current_pos <= list->max){
//         list->DList[list->current_pos] = subList;
//         list-> current_pos++;
//     }else{
//         list->max = list->max*2;
//         list->DList = (union ArrayOrStruct*)realloc(list->DList, list->max*sizeof(union ArrayOrStruct));
//         list->DList[list->current_pos] = subList;
//         list->current_pos++;
//     }
//     return list;
// }

