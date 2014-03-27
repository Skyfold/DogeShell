struct Linked_List{
    struct Linked_List *parent;
    struct Linked_List *child;
    char value;
};

void init_Linked_List(void);
void add_char (char value);
void moveBack(int times);
void moveForword(int times);
void moveToStart(void);
void moveToEnd(void);
void removeChar(void);

void printCurrentValue(void);
void printFromRoot(void);
void printFromCurrent(void);