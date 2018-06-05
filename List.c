//Nevan Samadhana
//SID:1539153
//pa4
//List.c
//List ADT file
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"

//Structs------------------
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* previous;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
  int length;
  int cursorIndex;
  Node head;
  Node tail;
  Node cursor;
  Node front;
  Node back;
} ListObj;

//Contructors
Node newNode(int data){
  Node current = malloc(sizeof(NodeObj));
  current->data = data;
  current->next = NULL;
  current->previous = NULL;
  return(current);
}

List newList(void){
  List nList = malloc(sizeof(ListObj));
  nList->length=0;
  nList->cursorIndex=0;
  nList->head=NULL;
  nList->tail=NULL;
  nList->front=NULL;
  nList->back=NULL;
  nList->cursor=NULL;
  return(nList);
}

//Destructors
void freeNode(Node* pointer){
  if(pointer!=NULL && *pointer!=NULL){
    free(*pointer);
    *pointer = NULL;
  }
}

void freeList(List* pointer){
  int i;
  int x = length(*pointer);
  for(i=0;i<x;i++){
    deleteBack(*pointer);
  }
  free(*pointer);
}

//length returns the amount of elements in the list
int length(List L){
  if(L==NULL){
    printf("List error: calling length() on NULL list reference\n");
    exit(1);
  }
  return(L->length);
}

//index returns the index of the cursor
int index(List L){
  if(L==NULL){
    printf("List error: calling index() on NULL list reference\n");
    exit(1);
  }else if(L->cursor == NULL){
    return(-1);
  }else{
    return(L->cursorIndex);
  }
}

//front returns the value of the head node
int front(List L){
  if(L==NULL){
    printf("List error: calling front() on NULL list reference\n");
    exit(1);
  }else if(L->length>0){
    return(L->head->data);
  }else{
    printf("List Error: Front() called on empty List");
    exit(1);
  }
}

//back() reutrns value of the tail node
int back(List L){
  if(L==NULL){
    printf("List error: calling back() on NULL list reference\n");
    exit(1);
  }else if(L->length>0){
    return(L->tail->data);
  }else{
    printf("List Error: back() called on empty List");
    exit(1);
  }
}

//get() returns the value of the cursor
int get(List L){ //Fix else
  if(L==NULL){
    printf("List error: calling get() on NULL list reference\n");
    exit(1);
  }else if(L->length>0 && L->cursorIndex >-1){
    return(L->cursor->data);
  }else{
    printf("List error: get() called on List with either insufficient length or undefined cursor");
    exit(1);
  }
}

//equals() checks if both lists are similar
int equals(List A, List B){
  if(A==NULL || B==NULL){
    printf("List error: calling equals() on NULL list reference\n");
    exit(1);
  }
  Node aCurrent = A->head;
  Node bCurrent = B->head;
  int eq = A->length == B->length;
  while( eq && aCurrent!=NULL){
    eq = (aCurrent->data == bCurrent->data);
    aCurrent = aCurrent->next;
    bCurrent = bCurrent->next;
  }
  return(eq);
}

//clear() clears a list
void clear(List L){
  if(L==NULL){
    printf("List error: calling clear() on NULL list reference\n");
    exit(1);
  }
  while(L->front!=NULL){
    deleteFront(L);
  }
  L->head = NULL;
  L->tail = NULL;
  L->front= NULL;
  L->back=NULL;
  L->cursor = NULL;
  L->length = 0;
  L->cursorIndex = -1;
}

//moveFront() places the cursor at the head of the list
void moveFront(List L){
  if(L==NULL){
    printf("List error: calling moveFront() on NULL list reference\n");
    exit(1);
  }
  if(L->length>0){
    L->cursor = L->head;
    L->cursorIndex=0;
  }else{
    return;
  }
}

//moveBack() places the cursor at the tail of the list
void moveBack(List L){
  if(L==NULL){
    printf("List error: calling moveBack() on NULL list reference\n");
    exit(1);
  }
  if(L->length>0){
    L->cursor = L->tail;
    L->cursorIndex=L->length-1;
  }else{
    return;
  }
}

//movePrev() moves the cursor one step towards the front of the list
void movePrev(List L){
  if(L==NULL){
    printf("List error: calling movePrev() on NULL list reference\n");
    exit(1);
  }
  if(L->cursor!=NULL && L->cursor != L->head){
    L->cursor = L->cursor->previous;
    L->cursorIndex-=1;
  }else if(L->cursor == L->head){
    L->cursor = NULL;
    L->cursorIndex = -1;
  }else if(L->cursor == NULL){
    return;
  }
}

//moveNext() moves the cursor one step towards the tail
void moveNext(List L){
  if(L==NULL){
    printf("List error: calling moveNext() on NULL list reference\n");
    exit(1);
  }
  if(L->cursor!=NULL && L->cursor!=L->tail){
    L->cursor = L->cursor->next;
    L->cursorIndex += 1;
  }else if(L->cursor == L->tail){
    L->cursor=NULL;
    L->cursorIndex = -1;
  }else if(L->cursor==NULL){
    return;
  }
}

//prepend() inserts a node at the beginning of the list
void prepend(List L, int data){
  Node latest = newNode(data);
  if(L==NULL){
    printf("List error: calling prepend() on NULL list reference\n");
    exit(1);
  }
  if(L->head == NULL){
    L->head = latest;
    L->tail = latest;
    L->length+=1;
  }else if(L->cursorIndex >=0){
    latest->next = L->head;
    L->head->previous = latest;
    L->head = latest;
    L->length++;
    L->cursorIndex++;
  }else{
    latest->next = L->head;
    L->head->previous = latest;
    L->head = latest;
    L->length++;
  }
}

//append() interts an element at the back of the list
void append(List L, int data){
  Node latest = newNode(data);
  if(L==NULL){
    printf("List error: calling append() on NULL list reference\n");
    exit(1);
  }
  if(L->head==NULL){
    L->head = latest;
    L->tail = latest;
    L->length++;
  }else{
    L->tail->next = latest;
    latest->previous =L->tail;
    L->tail = latest;
    L->length++;
  }
}

//insertBefore() inserts an elements before the cursor
void insertBefore(List L, int data){
  Node latest = newNode(data);
  if(L==NULL){
    printf("List error: calling insertBefore() on NULL list reference\n");
    exit(1);
  }
  if(L->length==0 && L->cursorIndex<0){
    printf("Calling insertBefore() on either an empty list or a list with an undefined cursor");
  }
  if(L->cursor == L->head){
    L->head->previous = latest;
    latest->next = L->head;
    L->head = latest;
    L->length++;
    L->cursorIndex++;
  }else if(L->cursorIndex>0){//Case where the cursor is not the head
    L->cursor->previous->next = latest;
    latest->previous = L->cursor->previous;
    L->cursor->previous = latest;
    latest->next = L->cursor;
    L->length++;
    L->cursorIndex++;
  }
}

//insertAfter() inserts a node after the cursor
void insertAfter(List L, int data){
  if(L==NULL){
    printf("List error: calling insertAfter() on NULL list reference\n");
    exit(1);
  }
  Node latest = newNode(data);
  if(L->length==0 || L->cursorIndex<0){
    printf("List error: calling insertAfter() either on empty list or list with undefined cursor");
    exit(1);
  }else if(L->cursor == L->tail){
    L->tail->next = latest;
    latest->previous = L->tail;
    L->tail = latest;
    L->length++;
  }else if(L->cursor != L->tail){
    L->cursor->next->previous = latest;
    latest->next = L->cursor->next;
    L->cursor->next = latest;
    latest->previous = L->cursor;
    L->length++;
  }
}

//deleteAfter() deletes the head of the list
void deleteFront(List L){
  if(L==NULL){
    printf("List error: calling deleteFront() on NULL list reference\n");
    exit(1);
  }else if(L->length<1){ //Case of empty list
    printf("List error: calling deleteFront() on an empty list");
    exit(1);
  }else if(L->length>0 && L->head == L->cursor){ //Case where cursor is at the head
    Node temp = L->front;
    L->head = L->head->next;
    L->head->previous = NULL;
    L->cursor = NULL;
    L->cursorIndex=-1;
    L->length --;
    freeNode(&temp);
  }else if(L->length>0 && L->head == L->tail){
    Node temp = L->front;
    L->head = NULL;
    L->cursorIndex =-1;
    L->length =0;
    freeNode(&temp);
  }else if(L->length>0 && L->head != L->cursor){ //Case where cursor is at the head
    Node temp = L->front;
    L->head = L->head->next;
    L->head->previous = NULL;
    L->cursorIndex --;
    L->length --;
    freeNode(&temp);
  }
}

//deleteBack()deletes the tail of the list
void deleteBack(List L){
  if(L==NULL){
    printf("List error: calling deleteBack() on NULL list reference\n");
    exit(1);
  }else if(L->length==1){
    Node temp = L->front;
    clear(L);
    freeNode(&temp);
  }else if(L->length<1){ //Case of empty list
    printf("List error: calling deleteFront() on an empty list");
    exit(1);
  }else if(L->length>0 && L->tail == L->cursor){ //Case where cursor is at the head
    Node temp = L->back;
    L->tail = L->tail->previous;
    L->tail->next = NULL;
    L->cursor = NULL;
    L->length--;
    L->cursorIndex = -1;
    freeNode(&temp);
  }else if(L->length>0 && L->tail!= L->cursor){
    Node temp = L->back;
    L->tail = L->tail->previous;
    L->tail->next = NULL;
    L->length--;
    freeNode(&temp);
  }
}

//delete() deletes the cursor node
void delete(List L){
  if(L==NULL){
    printf("List error: calling copyList() on NULL list reference\n");
    exit(1);
  }else if(L->length==0 || L->cursorIndex<0){
    printf("List error: calling delete either on empty list or list with undefined cursor");
    exit(1);
  }else if(L->cursor == L->head){
    Node temp = L->front;
    L->head = L->head->next;
    L->head->previous = NULL;
    L->length--;
    L->cursorIndex=-1;
    L->cursor = NULL;
    freeNode(&temp);
  }else if(L->cursor == L->tail){
    Node temp = L->tail;
    L->tail = L->tail->previous;
    L->tail->next = NULL;
    L->cursor =NULL;
    L->cursorIndex = -1;
    L->length--;
    freeNode(&temp);
  }else{
    Node temp = L->cursor;
    L->cursor->previous->next = L->cursor->next;
    L->cursor->next->previous = L->cursor->previous;
    L->length--;
    L->cursorIndex = -1;
    freeNode(&temp);
  }
}

//printList()prints to an out file
void printList(FILE* out, List L){
  if(L==NULL){
    printf("List error: calling copyList() on NULL list reference\n");
    exit(1);
  }
  Node current = L->head;
  while(current!=NULL){
    fprintf(out, "%d ", current->data);
    current=current->next;
  }
}

//copyList()return a copy of the List passed in
List copyList(List L){
  if(L==NULL){
    printf("List error: calling copyList() on NULL list reference\n");
    exit(1);
  }
  List copy = newList();
  Node current = L->head;
  while(current!=NULL){
    append(copy, current->data);
    current = current->next;
  }
  return(copy);
}
