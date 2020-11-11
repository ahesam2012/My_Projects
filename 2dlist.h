#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "LinkedList.h"



struct list_node
{
    LinkedList* value;
    struct list_node* next;
};
typedef struct list_node ListNode;

struct nested_list
{
    ListNode* head;
    int size;
};
typedef struct nested_list NestedList;

ListNode* new_lnode(LinkedList* content){
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node -> value = content;
    node -> next = null;
    return node;
}

NestedList* new_2dlist(){
    NestedList* list = (NestedList*)malloc(sizeof(NestedList));
    list -> head = null;
    list -> size = 0;
    return list;
}

void addFront2d(LinkedList* content, NestedList* list){
    ListNode* newNode = new_lnode(content);
    if(list -> head == NULL){
        list -> head = newNode;
        list -> size += 1;
        return;
    }
    else {
        newNode -> next = list -> head;
        list -> head = newNode;
        list -> size += 1;
    }
    return;
}

void addBack2d(LinkedList* content, NestedList* list){
    ListNode* newNode = new_lnode(content);
    if(list -> head == NULL){
        list -> head = newNode;
        list -> size += 1;
        return;
    }
    else if(list -> head != NULL && list -> head -> next == NULL){
        list -> head -> next = newNode;
        list -> size += 1;
        return;
    }
    else{
        ListNode* current = list -> head;
        while(1){
            if(current -> next == NULL){
                current -> next = newNode;
                break;
            }
            current = current -> next;
        }
        list -> size += 1;
        return;
    } 
}

void addAt2d(int index, LinkedList* content, NestedList* list){
    if(index == 0){
        addFront2d(content, list);
        return;
    }
    else if(index == list -> size){
        addBack2d(content, list);
        return;
    }
    int index2 = 0;
    ListNode* newNode = new_lnode(content);
    ListNode* temp = list -> head;
    while(temp != NULL){
        if(index2+1 == index){
            newNode -> next = temp -> next;
            temp -> next = newNode;
        }
        temp = temp -> next;
        index2++;
    }
    list -> size += 1;
    return;
}

void insert_sorted2d(LinkedList* content, NestedList* list){
    int index = 0;
    if(list -> size == 0 || compare(content -> head -> value, list -> head -> value -> head -> value, content -> type) == BiggerThan){
        addFront2d(content, list);
        return;
    }
    ListNode* current = list -> head; 
    while(current != NULL){
        if(current -> next == NULL){
            addBack2d(content, list);
            return;
        }
        else if(compare(content -> head -> value, current -> next -> value -> head -> value, content -> type) == BiggerThan){
            addAt2d(index+1, content, list);
            return;
        }
        current = current -> next;
        index++;
    }
    return;
}

void freelist(Node* head){
    Node* temp;
    while(head != null){
        temp = head;
        head = head -> next;
        free(temp -> value);
        free(temp);
    }
}

void free2dlist(ListNode* head){
    ListNode* temp;
    while(head != null){
        temp = head;
        head = head -> next;
        freelist(temp -> value -> head);
        free(temp -> value);
        free(temp);
    }
}