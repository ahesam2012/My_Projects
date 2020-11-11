#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define null NULL
#define BiggerThan 2  // If elem 1 > elem 2
#define SmallerThan 3  // if elem 1 < elem 2
#define True 1
#define False 0

typedef int boolean;
typedef char* String;


struct node
{
    void* value;
    struct node* next;
};
typedef struct node Node;

struct ll
{
    String type;
    Node* head;
    int size;
};
typedef struct ll LinkedList;


Node* new_node(void* content){
    Node* node = (Node*)malloc(sizeof(Node));
    node -> value = content;
    node -> next = null;
    return node;
}

LinkedList* new_list(String type){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list -> head = null;
    list -> type = type;
    list -> size = 0;
    return list;
}

//Checks if the two elements in the parameter are equal.
boolean is_equal(void* content1, void* content2, String type){
    if(strcmp(type, "int") == 0){
        if(*(int *)content1 == *(int *)content2){
            return True; // they are equal
        }
        else {
            return False; // not equal
        }
    }
    else if(strcmp(type, "String") == 0){
        if(strcmp(*(String *)content1, *(String *)content2) == 0){
            return True; // they are equal
        }
        else {
            return False; // they arent equal
        }
    }
    if(*(char *)content1 == *(char *)content2){
        return True; // equal
    }
    return False; // not equal
}

// checks if an element is in the list.
boolean is_there(void* element, LinkedList* list){
    Node* current = list -> head;
    if(list -> size == 0 || list -> size == 1){
        if(list -> size == 1){
            return is_equal(element, list -> head -> value, list -> type);
        }
        return False; // list is empty;
    }
    while(current != null){
        if(is_equal(current -> value, element, list -> type) == True){
            return True;
        }
        current = current -> next;
    }
    return False;
}

// returns a value representing which element is greater than the other.
int compare(void* element1, void* element2, String type){
    if(strcmp(type, "int") == 0){
        if(*(int *) element1 > *(int *) element2){
            return SmallerThan; // this is logically wrong, but for the sake of assignment!
        }
        else{
            return BiggerThan;
        }
    }
    else if(strcmp(type, "String") == 0){
        if(strcmp(*(String *) element1, *(String *) element2) < 0){
            return BiggerThan;
        }
        else {
            return SmallerThan;
        }
    }
    if(*(char *) element1 < *(char *) element2){
        return BiggerThan;
    }
    return SmallerThan;
}

void addFront(void* content, LinkedList* list){
    Node* to_be_inserted = new_node(content);
    if(list -> size == 0){
        list -> head = to_be_inserted;
        list -> size += 1;
        return;
    }
    else{
        list -> head -> next = to_be_inserted;
        list -> head = to_be_inserted;
        list -> size += 1;
        return;
    }
}

void addBack(void* content, LinkedList* list){
    Node* to_be_inserted = new_node(content);
    if(list -> size == 0){
        list -> head = to_be_inserted;
        list -> size += 1;
        return;
    }
    Node* current = list -> head;
    while(current != null){
        if(current -> next == null){
            current -> next = to_be_inserted;
            list -> size += 1;
            return;
        }
        current = current -> next;
    }
}


void* get_at_index(int index, LinkedList* list){
    Node* current = list -> head;
    if(index == 0){
        return list -> head -> value;
    }
    else if(index == list -> size - 1){
        while(current != null){
            if(current -> next == null){
                return current -> value;
            }
            current = current -> next;
        }
    }
    int follow = 0;
    while(current != null){
        if(follow + 1 == index){
            return current -> next -> value;
        }
        current = current -> next;
        follow++;
    }
    return null; // index prolly off bounds if we reach here.
}

void addAt(int index, void* content, LinkedList* list){
    if(index == 0){
        addFront(content, list);
        return;
    }
    else if(index == (list -> size)){
        addBack(content, list);
        return;
    }
    int index2 = 0;
    Node* newNode = new_node(content);
    Node* head = list -> head;
    Node* temp = head;
    while(temp != NULL){
        if(index2+1 == index){
            newNode -> next = temp -> next;
            temp -> next = newNode;
        }
        temp = temp -> next;
        index2++;
    }
    list -> size += 1;
    list -> head = head;
    return;
}

void insert_sorted(void* content, LinkedList* list){
    if(list -> size == 0 || compare(content, list -> head -> value, list -> type) == BiggerThan){
        addFront(content, list);
        return;
    }
    int follow = 0;
    Node* current = list -> head;
    while(current != null){
        if(current -> next == null){
            addBack(content, list);
            return;
        }
        else if(compare(content, current -> next -> value, list -> type) == BiggerThan){
            addAt(follow+1, content, list);
        }
        current = current -> next;
        follow++;
    }
}

void reverse(LinkedList* list){
    if(list -> size == 0 || list -> size == 1){
        return;
    }    
    Node* current = list -> head;
    LinkedList* list2 = new_list(list -> type);
    while(current != NULL){
        addFront(current -> value, list2);
        current = current -> next;
    }
    list = list2;
    return;
}
