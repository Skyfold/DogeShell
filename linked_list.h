#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

struct Linked_List{
    struct Linked_List *parent;
    struct Linked_List *child;
    char value;
};

char* flattenList(void);
void init_Linked_List(void);
void printCharToTerminal(char c);
void removeCharFromTerminal(void);

void moveBack(void);
void moveForword(void);
void moveToStart(void);
void moveToEnd(void);

bool LineIsEmpty(void);

void RemoveAllText(void);

void whatIsAtRoot(void);
void whatIsAtCurrent(void);

#endif