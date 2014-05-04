#include "linked_list.h"


struct Linked_List* root;
struct Linked_List* current;
int distance_from_end;
int total_elements;

struct Linked_List* create_Linked_List (void){
    struct Linked_List* list;
    list = (struct Linked_List*)malloc(sizeof(struct Linked_List));
    list->parent = NULL;
    list->child = NULL;
    list->value = '\0';
    return list;
}

void init_Linked_List(void){
    current = create_Linked_List();
    root = current;
    distance_from_end = 0;
    total_elements = 0;
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
        total_elements++;
    } else {
        fprintf(stderr, "You did not initialize your linked_list");
        exit(EXIT_FAILURE);
    }
}

void moveCursorToCurrentFromEnd(void){
    for (int i = 0; i < distance_from_end; ++i)
    {
        if(current->parent == NULL){
            fprintf(stderr, "\nYou moved from the end to a point off the end of the list. This means your pointer to current does not match your cursor");
            exit(EXIT_FAILURE);
        }

        current = current->parent;
        printf("\033[D");
        fflush(stdout);
    }
}

void moveBack(void){
    if (current->parent){
        current = current->parent;
        printf("\033[D");
        fflush(stdout);
        distance_from_end++;
    }
}

void moveForword(void){
    if (current->child){
        current = current->child;
        printf("\033[C");
        fflush(stdout);
        distance_from_end--;
    }
}

//You must move the root to start as well.
void moveToStart(void){
    while(current->parent){
        current = current->parent;
        printf("\033[D");
        fflush(stdout);
        distance_from_end++;
    }
}

void moveToEnd(void){
    while(current->child){
        current = current->child;
        printf("\033[D");
        fflush(stdout);
        distance_from_end--;
    }
}

char removeChar(void){
    char deleated = '\0';
    struct Linked_List* toBeRemoved = current->parent;
    if (current->parent != NULL){
        if(current->child == NULL){
            deleated = toBeRemoved->value;
            toBeRemoved->child = NULL;
            toBeRemoved->value = '\0';
            free(current);
            current = toBeRemoved;

        } else if(current->parent->parent){
            deleated = current->parent->value;
            current->parent->parent->child = current;
            current->parent = toBeRemoved->parent;
            free(toBeRemoved);
        } else {
            deleated = current->parent->value;
            current->parent = NULL;
            free(toBeRemoved);
            root = current;
        }
        total_elements--;
    }
    return deleated;
}   

char* flattenList(void){
    char* temp = (char*)malloc(((total_elements)*sizeof(char)));
    for (int i = 0; root->child; ++i)
    {
        temp[i] = root->value;
        struct Linked_List* templist = root;
        root = root->child;
        free(templist);
    }
    return temp;
}

//This was used for debugging code
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

void printCharToTerminal(char c){
    add_char(c);
    printf("\033[K");
    printf("%c", c);
    printFromCurrent();
    moveCursorToCurrentFromEnd();
    fflush(stdout);
}

void removeCharFromTerminal(void){
    if(current->parent){   
        removeChar();
        printf("\033[D");//moves the cursor left 
        printf("\033[K");
        printFromCurrent();
        moveCursorToCurrentFromEnd();
        fflush(stdout);
    }
}

//Fix the fact that there is a new line at root for no reason
bool LineIsEmpty(void){
    if (root->value == '\0' || root->value == '\n'){
        return true;
    } else{
        return false;
    }
}

void whatIsAtRoot(void){
    printf("%c\n", root->value);
    fflush(stdout);
}

void whatIsAtCurrent(void){
    printf("%c\n", current->value);
    fflush(stdout);
}

void RemoveAllText(void){
    while(current->parent != NULL)
    {
        removeCharFromTerminal();
    }
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

