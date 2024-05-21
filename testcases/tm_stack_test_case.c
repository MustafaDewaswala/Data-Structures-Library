#include<stdio.h>
#include<tm_stack.h>
int main()
{
int succ;
int x1,x2,x3,x4;
int *x;
x1=10;
x2=20;
x3=30;
x4=40;
Stack *stack;
stack=createStack(&succ);
if(stack==false)
{
printf("UNABLE TO CREATE STACK\n");
return 0;
}
pushOnStack(stack,&x1,&succ);
if(succ) printf("%d pushed on stack\n",x1);
else printf("UNABLE TO PUSH %d ON STACK\n",x1);
pushOnStack(stack,&x2,&succ);
if(succ) printf("%d pushed on stack\n",x2);
else printf("UNABLE TO PUSH %d ON STACK\n",x2);
pushOnStack(stack,&x3,&succ);
if(succ) printf("%d pushed on stack\n",x3);
else printf("UNABLE TO PUSH %d ON STACK\n",x3);
pushOnStack(stack,&x4,&succ);
if(succ) printf("%d pushed on stack\n",x4);
else printf("UNABLE TO PUSH %d ON STACK\n",x4);
printf("Size Of Stack %d\n",getSizeOfStack(stack));
if(isStackEmpty(stack)) printf("STACK IS EMPTY\n");
else printf("STACK IS NOT EMPTY\n");
x=(int *)elementAtTopOfStack(stack,&succ);
printf("ELEMENT AT TOP OF STACK IS %d\n",*x);
printf("NOW POPPING ALL THE ELEMENTS FROM STACK\n");
while(!isStackEmpty(stack))
{
x=(int *)popFromStack(stack,&succ);
printf("%d popped from stack\n",*x);
}
destroyStack(stack);
return 0;
}