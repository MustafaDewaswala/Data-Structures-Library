#ifndef __TM_AVL_TREE__C
#define __TM_AVL_TREE__C 123
#include<stdlib.h>
#include<tm_avl_tree.h>
AVLTree * createAVLTree(bool *success,int (*predicate)(void *,void *))
{
if(success) *success=false;
AVLTree *avlTree;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL || predicate==NULL) return NULL;
avlTree->start=NULL;
avlTree->predicate=predicate;
avlTree->size=0;
if(success) *success=true;
return avlTree;
}
void destroyAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return;
clearAVLTree(avlTree);
free(avlTree);
}
int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}
void clearAVLTree(AVLTree *avlTree)
{
}
void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
Stack *stack;
bool succ;
if(success) *success=false;
AVLTreeNode *j,*t;
int weight;
if(avlTree==NULL) return;
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
if(avlTree->start==NULL)
{
avlTree->start=t;
avlTree->size++;
if(success) *success=true;
return;
}
stack=createStack(&succ);
if(succ==false) return;
else
{
j=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0) return;
pushOnStack(stack,j,&succ);
if(succ==false)
{
destroyStack(stack);
return;
}
if(weight<0)
{
if(j->left==NULL)
{
j->left=t;
avlTree->size++;
balanceAVLTree(avlTree,stack);
destroyStack(stack);
if(success) *success=true;
return;
}
else j=j->left;
}
else
{
if(j->right==NULL) 
{
j->right=t;
avlTree->size++;
balanceAVLTree(avlTree,stack);
destroyStack(stack);
if(success) *success=true;
return;
}
else j=j->right;
}
}
}
}
void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *t,*j,*e,*f;
AVLTreeNode **p2p;
int weight;
void *foundPtr;
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL) return NULL;
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
j=t;
if(weight<0) t=t->left;
else t=t->right;
}
if(t==NULL) return NULL;
foundPtr=t->ptr;
if(t==avlTree->start) p2p=&(avlTree->start);
else if(j->left==t) p2p=&(j->left);
else p2p=&(j->right);
if(t->left==t->right) *p2p=NULL; // both are NULL
else
{
if(t->right!=NULL)
{
for(e=t->right;e->left!=NULL;e=e->left) f=e;
if(e==t->right) e->left=t->left;
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}
}
else
{
for(e=t->left;e->right!=NULL;e=e->right) f=e;
if(e!=t->left)
{
f->right=e->left;
e->left=t->left;
}
}
*p2p=e;
}
free(t);
avlTree->size--;
if(success) *success=true;
return foundPtr;
}
void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
int weight;
AVLTreeNode *t;
if(success) *success=false;
if(avlTree==NULL || avlTree->start==NULL) return NULL;
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)
{
if(success) *success=true;
return t->ptr;
}
if(weight<0) t=t->left;
else t=t->right;
}
return NULL;
}

AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreeInOrderIterator avlTreeInOrderIterator;
avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreeInOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreeInOrderIterator;
}
avlTreeInOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreeInOrderIterator;
t=avlTree->start;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,(void *)t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
t=t->left;
}
avlTreeInOrderIterator.node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator.stack,&succ);
if(success) *success=true;
return avlTreeInOrderIterator;
}
bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}
void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
{
bool succ;
AVLTreeNode *t,*j;
if(success) *success=false;
if(avlTreeInOrderIterator==NULL) return NULL;
if(avlTreeInOrderIterator->node==NULL) return NULL;
j=avlTreeInOrderIterator->node;
t=j->right;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,(void *)t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
t=t->left;
}
if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->node=NULL;
avlTreeInOrderIterator->stack=NULL;
}
else avlTreeInOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator->stack,&succ);
if(success) *success=true;
return j->ptr;
}
int getHeightOfAVLTree(AVLTreeNode *root)
{
if(root==NULL) return 0;
int leftTreeHeight,rightTreeHeight;
leftTreeHeight=getHeightOfAVLTree(root->left);
rightTreeHeight=getHeightOfAVLTree(root->right);
return (leftTreeHeight>rightTreeHeight)?leftTreeHeight+1:rightTreeHeight+1;
}
void balanceAVLTree(AVLTree *avlTree,Stack *stack)
{
AVLTreeNode **p2p;
AVLTreeNode *lc,*rc,*lcrc,*rclc,*parent,*root;
int lh,rh,diff,succ;
if(stack==NULL) return;
if(isStackEmpty(stack)) return;
while(!isStackEmpty(stack))
{
root=popFromStack(stack,&succ);
lh=getHeightOfAVLTree(root->left);
rh=getHeightOfAVLTree(root->right);
diff=lh-rh;
if(diff>=-1 && diff<=1) continue;

if(isStackEmpty(stack))
{
p2p=&(avlTree->start);
}
else
{
parent=elementAtTopOfStack(stack,&succ);
if(parent->left==root) 
{
p2p=&(parent->left);
}
else 
{
p2p=&(parent->right);
}
}
if(rh>lh)
{
rc=root->right;
if(getHeightOfAVLTree(rc->left)>getHeightOfAVLTree(rc->right))
{
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else
{
lc=root->left;
if(getHeightOfAVLTree(lc->right)>getHeightOfAVLTree(lc->left))
{
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
}
}
AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreePreOrderIterator avlTreePreOrderIterator;
avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreePreOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePreOrderIterator;
}
avlTreePreOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePreOrderIterator;
avlTreePreOrderIterator.node=avlTree->start;
if(success) *success=true;
return avlTreePreOrderIterator;
}
bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return false;
return true;
}
void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,bool *success)
{
bool succ;
AVLTreeNode *t,*j;
if(success) *success=false;
if(avlTreePreOrderIterator==NULL) return NULL;
if(avlTreePreOrderIterator->node==NULL) return NULL;
j=avlTreePreOrderIterator->node;
if(j->right!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->right,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}
if(j->left!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->left,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}
if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->node=NULL;
avlTreePreOrderIterator->stack=NULL;
}
else avlTreePreOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreePreOrderIterator->stack,&succ);
if(success) *success=true;
return j->ptr;
}
AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreePostOrderIterator avlTreePostOrderIterator;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return avlTreePostOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePostOrderIterator;
}
avlTreePostOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePostOrderIterator;
t=avlTree->start;
while(1)
{
while(t)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator.stack,t->right,&succ);
// what if succ is false
}
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
// what if succ is false
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator.stack,&succ);
if(!isStackEmpty(avlTreePostOrderIterator.stack) && t->right && t->right==elementAtTopOfStack(avlTreePostOrderIterator.stack,&succ))
{
popFromStack(avlTreePostOrderIterator.stack,&succ);
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
// what if succ is false
t=t->right;
} 
else
{
break;
}
}
avlTreePostOrderIterator.node=t;
if(success) *success=true;
return avlTreePostOrderIterator;
}
bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return false;
return true;
}
void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,bool *success)
{
bool succ;
AVLTreeNode *t,*j;
if(success) *success=false;
if(avlTreePostOrderIterator==NULL) return NULL;
if(avlTreePostOrderIterator->node==NULL) return NULL;
j=avlTreePostOrderIterator->node;
if(isStackEmpty(avlTreePostOrderIterator->stack))
{
avlTreePostOrderIterator->node=NULL;
destroyStack(avlTreePostOrderIterator->stack);
if(success) *success=true;
return j->ptr;
}
t=NULL;
while(1)
{
while(t)
{
if(t->right!=NULL)
{ 
pushOnStack(avlTreePostOrderIterator->stack,t->right,&succ);
}
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator->stack,&succ);
if(!isStackEmpty(avlTreePostOrderIterator->stack) && t->right && t->right==elementAtTopOfStack(avlTreePostOrderIterator->stack,&succ))
{
popFromStack(avlTreePostOrderIterator->stack,&succ);
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
t=t->right;
} 
else
{
break;
}
}
avlTreePostOrderIterator->node=t;
if(success) *success=true;
return j->ptr;
}
#endif















