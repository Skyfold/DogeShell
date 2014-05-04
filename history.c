#include "linked_list.h"
#include "history.h"
#include "dynamic_char_array.h"

//Might want to make this a dynamic array. If you have time

// void printHist(FILE* Hist){
//     char c = '\0';
//     c = fgetc(Hist);
//     while(c != (char)200){
//         printCharToTerminal(c);
//         c = fgetc(Hist);
//     }
// }

char** TokenArray(char* temp){
    char** token = (char**)calloc(256, sizeof(char*));
    char* pch = strtok (temp," ");
    
    for (int i = 0; pch != NULL; ++i)
    {
        token[i] = (char*)malloc(strlen(pch)*sizeof(char));
        token[i] = pch;
        pch = strtok (NULL, " ");
    }
    return token;
}

void SaveHist(char* temp){
    if(temp[0] != '\0'){
        char* home = getenv("HOME");
        char homeCopy[64];
        strcpy(homeCopy, home);
        FILE* Hist = fopen(strcat(homeCopy, "/.DogeHistory"), "a+");

        //list = DCharArray_add(list, temp);
        fputs(temp, Hist);
        fputc(31, Hist);
        fclose(Hist);
    }
}




// void downOneCommand(FILE* Hist){

// }

// void upOneCommand(FILE* Hist){
//      char c = '\0';

//     RemoveAllText();

//     fseek(Hist, -2, SEEK_CUR);
//     c = fgetc(Hist);
//     while(c != (char)200){
//         fseek(Hist, -2, SEEK_CUR);
//         c = fgetc(Hist);
//     }

//     fseek(Hist, -2, SEEK_CUR);
//     c = fgetc(Hist);
//     while(c != (char)200){
//         fseek(Hist, -2, SEEK_CUR);
//         c = fgetc(Hist);
//     }

//     printHist(Hist);
// }

// FILE* previousCommand(void){
//     char c = '\0';
//     FILE* Hist = fopen("DogeHistory", "r");
//         fseek(Hist,-1 ,SEEK_END);
//         c = fgetc(Hist);
//         if(c == (char)200){

//             fseek(Hist, -2, SEEK_CUR);
//             c = fgetc(Hist);
//             while(c != (char)200){
//                 fseek(Hist, -2, SEEK_CUR);
//                 c = fgetc(Hist);
//             }

//             printHist(Hist);
//         }else{
//             fprintf(stderr, "Well you looked at the end of the hist file and it was not a newline, instead %c was there \n",c);
//             exit(1);
//         }
//     return Hist;
// }

