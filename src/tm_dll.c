#ifndef __TM_DLL_C
#define __TM_DLL_C 
#include<stdlib.h>
#include<tm_dll.h>
DoublyLinkedList * createDoublyLinkedList(bool *success)
{
if(success) *success=false;
DoublyLinkedList *doublyLinkedList;
doublyLinkedList=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
if(doublyLinkedList==NULL) return NULL;
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
if(success) *success=true;
return doublyLinkedList;
}
void destroyDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return;
clearDoublyLinkedList(doublyLinkedList);
free(doublyLinkedList);
}
int getSizeOfDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return 0;
return doublyLinkedList->size;
}
void clearDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
DoublyLinkedListNode *node;
if(doublyLinkedList==NULL) return;
node=doublyLinkedList->start;
while(doublyLinkedList->start!=NULL)
{
node=doublyLinkedList->start;
doublyLinkedList->start=doublyLinkedList->start->next;
free(node);
}
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
}
void addToDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,bool *success)
{
DoublyLinkedListNode *node;
if(success) *success=false;
if(doublyLinkedList==NULL) return;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;
if(doublyLinkedList->start==NULL) doublyLinkedList->start=doublyLinkedList->end=node;
else
{
doublyLinkedList->end->next=node;
node->previous=doublyLinkedList->end;
doublyLinkedList->end=node;
}
doublyLinkedList->size++;
if(success) *success=true;
}
void * getFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success)
{
DoublyLinkedListNode *node;
int x;
if(success) *success=false;
if(doublyLinkedList==NULL) return NULL;
if(index<0 || index>=doublyLinkedList->size) return NULL;
x=0;
node=doublyLinkedList->start;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}
#endif
