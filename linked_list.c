#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "linked_list.h"

struct Linked_List* root;
struct Linked_List* current;

struct Linked_List* create_Linked_List (void){
    struct Linked_List* list;
    list = (struct Linked_List*)malloc(sizeof(struct Linked_List));
    list->parent = NULL;
    list->child = NULL;
    return list;
}

void init_Linked_List(void){
    current = create_Linked_List();
    root = current;
}

void add_char (char value){
    if (&current){
        if (current->child == NULL){
            current->value = value;
            current->child = create_Linked_List();
            current->child->parent = current;
            current = current->child;
        } else if (current->parent == NULL){
            current->parent = create_Linked_List();
            current->parent->value = value;
            current->parent->child = current;
            root = current->parent;
        } else {
            struct Linked_List* Insert_List = create_Linked_List();
            current->parent->child = Insert_List;
            Insert_List->parent = current->parent;
            current->parent = Insert_List;
            Insert_List->child = current;
            Insert_List->value = value;
        }
    } else {
        fprintf(stderr, "You did not initialize your linked_list");
        exit(EXIT_FAILURE);
    }
}

void moveBack(int times){
    for (int i = 0; i < times; ++i)
    {
        if (current->parent){
            current = current->parent;
        }
        printf("\033[D");
        fflush(stdout);
    }
}

void moveForword(int times){
    for (int i = 0; i < times; ++i)
    {
        if (current->child){
            current = current->child;
        }
        printf("\033[C");
        fflush(stdout);
    }

}

//You must move the root to start as well.
void moveToStart(void){
    while(current->parent){
        current = current->parent;
    }
}

void moveToEnd(void){
    while(current->child){
        current = current->child;
    }
}

void removeChar(void){
    struct Linked_List* toBeRemoved = current->parent;
    if (current->parent != NULL){
        if(current->child == NULL){
            toBeRemoved->child = NULL;
            toBeRemoved->value = '\0';
            free(current);
            current = toBeRemoved;

        } else if(current->parent->parent){
            current->parent->parent->child = current;
            current->parent = toBeRemoved->parent;
            free(toBeRemoved);
        } else {
            current->parent = NULL;
            free(toBeRemoved);
            root = current;
        }
    }
}   

void printCurrentValue(void){
    printf("     %c", current->value);
    fflush(stdout);
}

void printFromRoot(void){
    struct Linked_List* temp;
    temp  = root;
    while (root->child){
    printf("%c", root->value);
    root = root->child;
    }
    root = temp;
    fflush(stdout);
}

void printFromCurrent(void){
    while (current->child){
    printf("%c", current->value);
    current = current->child;
    }
    fflush(stdout);
}

// int main(){
//     init_Linked_List();
//     add_char('a');
//     add_char('b');
//     add_char('c');
//     moveToStart();
//     add_char('t');

//     moveForword();
//     add_char('g');
//     add_char('p');
//     moveToEnd();
//     add_char('z');
//     moveBack();
//     add_char('o');
//     removeChar();
//     removeChar();
//     moveForword();
//     removeChar();
//     moveToStart();
//     removeChar();
//     moveToEnd();
//     removeChar();
//     removeChar();
//     removeChar();
//     printf("%c\n", current->value);

//     while (root->child){
//         printf("%c", root->value);
//         root = root->child;
//     }
//     return 0;
// }

