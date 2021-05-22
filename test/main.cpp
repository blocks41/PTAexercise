#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef int ElementType;

typedef struct QNode* Queue;       //������ʽ�洢
typedef struct Node* PNode;
struct Node {
    ElementType Data;
    struct Node* Next;
};
struct QNode {                      //�����еĽṹ��
    struct Node* front;             //һ��ָ���ͷ�ڵ�
    struct Node* rear;              //һ��ָ���β�ڵ�
};

Queue Create();          //�����ն���
void Add(ElementType X, Queue PtrQ);    //����к���
ElementType Delete(Queue PtrQ);      //�����к���

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

ElementType Delete(Queue PtrQ)   //ɾ������һ�㶼����ͷָ��֮��ģ�
                                  //  ����ͷָ�벢��������
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