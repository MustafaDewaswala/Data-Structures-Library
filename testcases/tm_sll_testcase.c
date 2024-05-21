#include<tm_sll.h>
#include<stdio.h>
int main()
{
bool succ;
SinglyLinkedList *list1;
list1=createSinglyLinkedList(&succ);
if(succ==false)
{
printf("Unable To Create List");
return 0;
}
printf("List Created\n");
printf("Clearing List\n");
clearSinglyLinkedList(list1);
printf("Destroying List\n");
destroySinglyLinkedList(list1);
return 0;
}