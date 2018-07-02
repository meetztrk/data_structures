#ifndef LinkedList_h
#define LinkedList_h

#define remove l_remove

typedef void Deconstructor;
typedef void* CopyRule;

typedef struct Node{
    struct Node *next;
    void *item;
}Node;

typedef struct LinkedList{
    Node *head;
    Node *tail;
    int size;
}LinkedList;


LinkedList* new_LinkedList();

void add(LinkedList *list, void *item);

void addFirst(LinkedList *list, void *item);

void insert(LinkedList *list, int index, void* item);

void* get(LinkedList *list, int index);

void clear(LinkedList *list, Deconstructor(*deconstructor)(void*));

LinkedList* copy(LinkedList *list, CopyRule(*copyRule)(void*));

int indexOf(LinkedList *list,void *item);

int lastIndexOf(LinkedList *list, void *item);

int contains(LinkedList *list, void *item);

int size(LinkedList *list);

void remove(LinkedList *list, int index, Deconstructor(*deconstructor)(void*));

#endif  