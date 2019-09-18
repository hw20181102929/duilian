#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef enum { push, pop, inject, eject, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode {
    ElementType *Data;      /* 存储元素的数组   */
    Position Front, Rear;   /* 队列的头、尾指针 */
    int MaxSize;            /* 队列最大容量     */
};
typedef PtrToQNode Deque;

Deque CreateDeque( int MaxSize )
{   /* 注意：为区分空队列和满队列，需要多开辟一个空间 */
    Deque D = (Deque)malloc(sizeof(struct QNode));
    MaxSize++;
    D->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    D->Front = D->Rear = 0;
    D->MaxSize = MaxSize;
    return D;
}

bool Push( ElementType X, Deque D );
ElementType Pop( Deque D );
bool Inject( ElementType X, Deque D );
ElementType Eject( Deque D );
int GetOp();          /* 裁判实现，细节不表 */
void PrintDeque( Deque D ); /* 裁判实现，细节不表 */

int main()
{
    ElementType X;
    Deque D;
    int N, done = 0;
    
    scanf("%d", &N);
    D = CreateDeque(N);
    while (!done) {
        switch(GetOp()) {
            case 1:
                scanf("%d", &X);
                if (!Push(X, D)) printf("Deque is Full!\n");
                break;
            case 2:
                X = Pop(D);
                if ( X==ERROR ) printf("Deque is Empty!\n");
                else printf("%d is out\n", X);
                break;
            case 3:
                scanf("%d", &X);
                if (!Inject(X, D)) printf("Deque is Full!\n");
                break;
            case 4:
                X = Eject(D);
                if ( X==ERROR ) printf("Deque is Empty!\n");
                else printf("%d is out\n", X);
                break;
            case 5:
                PrintDeque(D);
                done = 1;
                break;
        }
    }
    return 0;
}
int  GetOp()
{
    int n;
    scanf("%d",&n);
    return n;
}
void PrintDeque( Deque D )
{
    D->Front = D ->Front%(D->MaxSize-1) ;
    D->Rear = D->Rear%(D->MaxSize-1);
    int i;
    for(i=D->Front;i<=D->Rear;i++)
    {
        printf("%d ",D->Data[i]);
    }
}
bool Push( ElementType X, Deque D )
{
    if((D->Rear+1)%(D->MaxSize-1)==D->Front%(D->MaxSize-1))
    {
        return false;
    }
    else
    {
        D->Front=D->Front%(D->MaxSize-1);
        if(D->Front==1)
        {
            D->Data[D->MaxSize-1]=X;
            D->Front = D->MaxSize - 2;
            return true;
        }
        else
        {
            D->Data[D->Front--]=X;
            return true;
        }
    }
}
ElementType Pop( Deque D )
{
    if(D->Front==D->Rear)
    {
        return ERROR;
    }
    else
    {
        D->Front =D->Front%(D->MaxSize-1);
        return D->Data[++D->Front];
    }
}
bool Inject( ElementType X, Deque D )
{
    if((D->Rear+1)%(D->MaxSize-1)==D->Front%(D->MaxSize-1))
    {
        return false;
    }
    else
    {
        D->Rear=D->Rear%(D->MaxSize-1);
        D->Data[(++D->Rear)%(D->MaxSize-1)]=X;
        return  true;
    }
}
ElementType Eject( Deque D )
{
    if(D->Rear==D->Front)
    {
        return ERROR;
    }
    else
    {
        D->Rear=D->Rear%(D->MaxSize-1);
        if(D->Rear==0)
        {
            D->Rear=D->MaxSize-2;
            return D->Data[D->Rear];
        }
        else
        {
            return D->Data[D->Rear--];
        }
    }
}
