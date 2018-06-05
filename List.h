//Nevan Samadhana
//SID:1539153
//pa4
//List.h
//Header file for List

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//newList() creates a reference to an empty list object
List newList(void);

//freeList() frees memory
void freeList(List* lp);

//length() returns length of the list
int length(List lp);

//index() returns index of the cursor
int index(List lp);

//front() returns the front of the list
int front(List lp);

//back() returns the end of the list
int back(List lp);

//get() returns the value of the cursor
int get(List lp);

//equals() returns 1 if Lists are equal, 0 if not equal
int equals(List A, List B);

//clear() clears a list
void clear(List lp);

//moveFront() places the cursor at the head of the list
void moveFront(List lp);

//moveBack() places the cursor at the back of the list
void moveBack(List lp);

//movePrev() Moves the cursor towards the head by one step
void movePrev(List lp);

//moveNext() moves the cursor one towards the tail
void moveNext(List lp);

//prepend() Inserts a node at the beginning of the list
void prepend(List lp, int data);

//append() Places a node at the end of the list
void append(List lp, int data);

//insertBefoe() inserts a node before the cursor
void insertBefore(List lp, int data);

//insertAfter() inserts a node after the cursor
void insertAfter(List lp, int data);

//copyList()return a copy of the List passed in
List copyList(List lp);

//deleteFront()deletes the head of the list
void deleteFront(List lp);

//deleteBack()deletes the tail of the list
void deleteBack(List lp);

//delete() deletes the cursor
void delete(List lp);

//printList()prints to an out file
void printList(FILE* out, List L);


#endif
