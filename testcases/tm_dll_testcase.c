#include<tm_dll.h>
#include<stdio.h>
int main()
{
int *x;
bool succ;
int i,i1,i2,i3,i4,i5,i6;
DoublyLinkedList *list1;
list1=createDoublyLinkedList(&succ);
i1=100;
i2=200;
i3=300;
i4=400;
i5=500;
i6=600;
addToDoublyLinkedList(list1,(void *)&i1,&succ);
addToDoublyLinkedList(list1,(void *)&i2,&succ);
addToDoublyLinkedList(list1,(void *)&i3,&succ);
addToDoublyLinkedList(list1,(void *)&i4,&succ);
addToDoublyLinkedList(list1,(void *)&i5,&succ);
addToDoublyLinkedList(list1,(void *)&i6,&succ);
for(i=0;i<getSizeOfDoublyLinkedList(list1);i++)
{
x=(int *)getFromDoublyLinkedList(list1,i,&succ);
printf("%d\n",*x);
}
destroyDoublyLinkedList(list1);
return 0;
}