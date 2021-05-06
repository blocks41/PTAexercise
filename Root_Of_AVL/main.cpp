#include <iostream>

using namespace std;

int Max(int a, int b);

using AVLTree=class AVLNode*;
class AVLNode {
public:
	int Data;  //�������
	AVLTree Left;  //����
	AVLTree Right;  //�ҽ��
	int Height;   //����

    AVLNode() {   //�޲ι��캯��
        Left = nullptr;
        Right = nullptr;
        Height = 1;
    }

    int GetHeight() {
        if (!Left && !Right) return 1;  //�����Ҷ�ӽڵ�ͷ���1
        if (!Left && Right) return Right->Height+1;   //����ֲ���
        if (Left && !Right) return Left->Height+1;   //�ҿ��󲻿�
        if (Left && Right) return Max(Left->Height, Right->Height)+1;
    }
    int D_Value() {
        if (!Left && !Right) return 0;  //�����Ҷ�ӽڵ�ͷ���1
        if (!Left && Right) return -(Right->Height);   //����ֲ���
        if (Left && !Right) return Left->Height;   //�ҿ��󲻿�
        if(Left&&Right) return Left->Height - Right->Height;
    }
};

AVLTree LL_Rotation(AVLTree A);
AVLTree RR_Rotation(AVLTree A);
AVLTree LR_Rotation(AVLTree A);
AVLTree RL_Rotation(AVLTree A);
AVLTree Insert(AVLTree T, int X);

int main() {
    int N;  //�����
    int X;
    AVLTree T = nullptr;

    cin >> N;
    for (int i = 0; i < N; i++) {   //����
        cin >> X;
        T = Insert(T, X);
    }
    cout << T->Data;  //������

	return 0;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

AVLTree LL_Rotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B */

    AVLTree B = A->Left;   //����A��������
    A->Left = B->Right;    //A������������B��������x
    B->Right = A;    //��A���B��������
    A->Height = A->GetHeight();
    B->Height = B->GetHeight();

    return B;
}

AVLTree RR_Rotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B */

    AVLTree B = A->Right;  
    A->Right = B->Left;    
    B->Left = A;    
    A->Height = A->GetHeight();
    B->Height = B->GetHeight();

    return B;
}

AVLTree LR_Rotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

    /* ��B��C���ҵ�����C������ */
    A->Left = RR_Rotation(A->Left);
    /* ��A��C��������C������ */
    return LL_Rotation(A);
}

AVLTree RL_Rotation(AVLTree A)
{ /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

    /* ��B��C��������C������ */
    A->Right = LL_Rotation(A->Right);
    /* ��A��C���ҵ�����C������ */
    return RR_Rotation(A);
}

AVLTree Insert(AVLTree T, int X)
{ /* ��X����AVL��T�У����ҷ��ص������AVL�� */
    if (!T) { /* ��������������½�����һ�������� */
        T = new AVLNode;
        T->Data = X;
    } /* if (�������) ���� */

    else if (X < T->Data) {
        /* ����T�������� */
        T->Left = Insert(T->Left, X);
        /* �����Ҫ���� */
        if (T->D_Value() == 2)
            if (X < T->Left->Data)
                T = LL_Rotation(T);      /* ���� */
            else
                T = LR_Rotation(T); /* ��-��˫�� */
    } /* else if (����������) ���� */

    else if (X > T->Data) {
        /* ����T�������� */
        T->Right = Insert(T->Right, X);
        /* �����Ҫ���� */
        if (T->D_Value() == -2)
            if (X > T->Right->Data)
                T = RR_Rotation(T);     /* �ҵ��� */
            else
                T = RL_Rotation(T); /* ��-��˫�� */
    } /* else if (����������) ���� */

    /* else X == T->Data��������� */

    /* �����˸������� */
    T->Height = T->GetHeight();

    return T;
}