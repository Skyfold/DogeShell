struct Linked_List{
    struct Linked_List *parent;
    struct Linked_List *child;
    char value;
};

void init_Linked_List(void);
void printCharToTerminal(char c);
void removeCharFromTerminal(void);

void moveBack(void);
void moveForword(void);
void moveToStart(void);
void moveToEnd(void);