#include<stdio.h>
#include<tm_queue.h>
int main()
{
int succ;
int x1,x2,x3,x4;
int *x;
x1=10;
x2=20;
x3=30;
x4=40;
Queue *queue;
queue=createQueue(&succ);
if(queue==false)
{
printf("UNABLE TO CREATE QUEUE\n");
return 0;
}
addToQueue(queue,&x1,&succ);
if(succ) printf("%d added to queue\n",x1);
else printf("UNABLE TO PUSH %d ON QUEUE\n",x1);
addToQueue(queue,&x2,&succ);
if(succ) printf("%d added to queue\n",x2);
else printf("UNABLE TO PUSH %d ON QUEUE\n",x2);
addToQueue(queue,&x3,&succ);
if(succ) printf("%d added to queue\n",x3);
else printf("UNABLE TO PUSH %d ON QUEUE\n",x3);
addToQueue(queue,&x4,&succ);
if(succ) printf("%d added to queue\n",x4);
else printf("UNABLE TO PUSH %d ON QUEUE\n",x4);
printf("Size Of Queue %d\n",getSizeOfQueue(queue));
if(isQueueEmpty(queue)) printf("QUEUE IS EMPTY\n");
else printf("QUEUE IS NOT EMPTY\n");
x=(int *)elementAtFrontOfQueue(queue,&succ);
printf("ELEMENT AT TOP OF QUEUE IS %d\n",*x);
printf("NOW POPPING ALL THE ELEMENTS FROM QUEUE\n");
while(!isQueueEmpty(queue))
{
x=(int *)removeFromQueue(queue,&succ);
printf("%d removed from queue\n",*x);
}
destroyQueue(queue);
return 0;
}