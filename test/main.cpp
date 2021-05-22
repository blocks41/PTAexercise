#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef int ElementType;

typedef struct QNode* Queue;       //队列链式存储
typedef struct Node* PNode;
struct Node {
    ElementType Data;
    struct Node* Next;
};
struct QNode {                      //链队列的结构体
    struct Node* front;             //一个指向队头节点
    struct Node* rear;              //一个指向队尾节点
};

Queue Create();          //创建空队列
void Add(ElementType X, Queue PtrQ);    //入队列函数
ElementType Delete(Queue PtrQ);      //出队列函数

int main()
{
    Queue Q = Create();

    Add(3, Q);
    Add(4, Q);
    Add(5, Q);

    PNode Node=Q->front;
    while (Node != Q->rear) {
        printf("%d ", Node->Data);
        Node = Node->Next;
    }
    printf("%d", Node->Data);

    return 0;
}

Queue Create()
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->front = q->rear = NULL;

    return q;
}

void Add(ElementType X, Queue PtrQ)
{
    PNode N = (PNode)malloc(sizeof(struct Node));
    N->Data = X;
    N->Next = NULL;

    if (PtrQ->front == NULL)
    {
        PtrQ->front = N;
        PtrQ->rear = N;
    }
    else
    {
        PtrQ->rear->Next = N;
        PtrQ->rear = N;
    }
}

ElementType Delete(Queue PtrQ)   //删除操作一般都是在头指针之后的，
                                  //  这里头指针并不存数据
{
    PNode q;
    ElementType X;

    if (PtrQ->front == NULL)
    {
        printf("Queue is Empty!");
        return ERROR;
    }
    q = PtrQ->front->Next;
    X = q->Data;
    PtrQ->front->Next = q->Next;
    free(q);

    return X;
}