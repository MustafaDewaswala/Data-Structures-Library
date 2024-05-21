#include<tm_avl_tree.h>
#include<stdio.h>
#include<stdlib.h>
int myComparator(void *left,void *right)
{
int *leftInt,*rightInt;
leftInt=(int *)left;
rightInt=(int *)right;
return (*leftInt)-(*rightInt);
}
int main()
{
AVLTreeInOrderIterator iterator;
AVLTreePreOrderIterator iterator2;
AVLTreePostOrderIterator iterator3;
char more;
int *x;
int num,ch;
AVLTree *tree;
int success;
tree=createAVLTree(&success,myComparator);
if(success==false)
{
printf("Unable to create tree, low on memory\n");
return 0;
}
while(1)
{
printf("1. Insert\n");
printf("2. In Order Traversal\n");
printf("3. Remove\n");
printf("4. Search\n");
printf("5. Pre Order Traversal\n");
printf("6. Post Order Traversal\n");
printf("7. Exit\n");
printf("Enter Your Choice : ");
scanf("%d",&ch);
if(ch==1)
{
printf("Enter number to be inserted in tree : ");
scanf("%d",&num);
fflush(stdin);
x=(int *)malloc(sizeof(int));
*x=num;
insertIntoAVLTree(tree,(void *)x,&success);
if(success) printf("Address of item that contains %d inserted in tree\n",*x);
else printf("Unable to insert in tree\n"); 
}
else if(ch==2)
{
printf("In Order Iteration starts\n");
iterator=getAVLTreeInOrderIterator(tree,&success);
if(success)
{
while(hasNextInOrderElementInAVLTree(&iterator))
{
x=(int *)getNextInOrderElementFromAVLTree(&iterator,&success);
printf("%d\n",*x);
}
}
}
else if(ch==3)
{
printf("Enter number to remove : ");
scanf("%d",&num);
fflush(stdin);
x=removeFromAVLTree(tree,&num,&success);
if(success) printf("%d found and removed\n",*x);
else printf("%d not found\n",num);
}
else if(ch==4)
{
printf("Enter number to search : ");
scanf("%d",&num);
fflush(stdin);
x=getFromAVLTree(tree,&num,&success);
if(success) printf("%d found\n",*x);
else printf("%d not found\n",num);
}
else if(ch==5)
{
printf("Pre Order Iteration starts\n");
iterator2=getAVLTreePreOrderIterator(tree,&success);
if(success)
{
while(hasNextPreOrderElementInAVLTree(&iterator2))
{
x=(int *)getNextPreOrderElementFromAVLTree(&iterator2,&success);
printf("%d\n",*x);
}
}
}

else if(ch==6)
{
printf("Post Order Iteration starts\n");
iterator3=getAVLTreePostOrderIterator(tree,&success);
if(success)
{
while(hasNextPostOrderElementInAVLTree(&iterator3))
{
x=(int *)getNextPostOrderElementFromAVLTree(&iterator3,&success);
printf("%d\n",*x);
}
}
}
else if(ch==7) break;
else continue;
}
destroyAVLTree(tree);
return 0;
}


