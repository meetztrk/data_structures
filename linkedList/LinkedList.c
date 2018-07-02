#include<stdlib.h>
#include"LinkedList.h"

LinkedList* new_LinkedList(){
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
    list->size = 0;
    Node *node = (Node*) calloc(1, sizeof(Node));
    list->head = node;
    list->tail = node;
}

void add(LinkedList *list, void *item){
    list->tail->item = item;
    list->tail->next = (Node*) calloc(1, sizeof(Node));
    list->tail = list->tail->next;
    list->size++;
}

void addFirst(LinkedList *list, void *item){
    //insert(list, 0, item);
    Node *node = (Node*) malloc(sizeof(Node));
    node->next = list->head;
    list->head = node;
    node->item = item;
    list->size++;
} 

void insert(LinkedList *list, int index, void* item){
    if(index + 1 > list->size){
        add(list, item);
        //comment
        return;
    }
    Node **iter = &list->head;
    while(index-- > 0){
        iter = &((*iter)->next);
    }
    Node *node = (Node*) malloc(sizeof(Node));
    node->next = *iter;
    *iter = node;
    node->item = item;
    list->size++;
}

void* get(LinkedList *list, int index){
    if(index + 1 > list->size) return NULL;
    Node *iter = list->head;
    while(index-- > 0){
        iter = iter->next;
    }
    return iter->item;
}

void clear(LinkedList *list, Deconstructor(*deconstructor)(void*)){
    Node *iter = list->head;
    list->size = 0;
    Node *node = (Node*) calloc(1, sizeof(Node));
    list->head = node;
    list->tail = node;
    //It is garbage and concurency avaible
    Node *prev;
    if(deconstructor != NULL){
        while(iter->next != NULL){
            prev = iter;
            iter = iter->next;
            deconstructor(prev->item);
            free(prev);
        }
        free(iter);
    }else{
        while(iter != NULL){
            prev = iter;
            iter = iter->next;
            free(prev);
        }
    }
}

LinkedList* copy(LinkedList *list, CopyRule(*copyRule)(void*)){
    LinkedList *copyList = new_LinkedList();
    Node *iter = list->head;
    if(copyRule != NULL){
        while(iter->next != NULL){
            add(copyList, copyRule(iter->item));
            iter = iter->next;
        }
    }else{
        while(iter->next != NULL){
            add(copyList, iter->item);
            iter = iter->next;
        }
    }
    return copyList;
}

int indexOf(LinkedList *list,void *item){
    Node *iter = list->head;
    int index = 0;
    while(iter->next != NULL){
        if(iter->item == item) return index;
        index++;
        iter = iter->next;
    }
    return -1;
}

int lastIndexOf(LinkedList *list, void *item){
    Node *iter = list->head;
    int index = 0;
    int finded = -1;
    while(iter->next != NULL){
        if(iter->item == item) finded = index;
        index++;
        iter = iter->next;
    }
    return finded;
}

int contains(LinkedList *list, void *item){
    int indexof = indexOf(list, item);
    if(indexof == -1) return 0;
    return 1;
}

int size(LinkedList *list){
    return list->size;
}

void remove(LinkedList *list, int index, Deconstructor(*deconstructor)(void*)){
    if(index + 1 > list->size) return;
    Node **iter = &(list->head);
    while(index-- > 0){
        iter = &((*iter)->next);
    }
    if(deconstructor != NULL) deconstructor((*iter)->item);
    Node *temp = (*iter)->next;
    free((*iter));
    *iter = temp;
    list->size--;
}
