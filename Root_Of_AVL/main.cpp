#include <iostream>

using namespace std;

int Max(int a, int b);

using AVLTree=class AVLNode*;
class AVLNode {
public:
	int Data;  //结点数据
	AVLTree Left;  //左结点
	AVLTree Right;  //右结点
	int Height;   //树高

    AVLNode() {   //无参构造函数
        Left = nullptr;
        Right = nullptr;
        Height = 1;
    }

    int GetHeight() {
        if (!Left && !Right) return 1;  //如果是叶子节点就返回1
        if (!Left && Right) return Right->Height+1;   //左空又不空
        if (Left && !Right) return Left->Height+1;   //右空左不空
        if (Left && Right) return Max(Left->Height, Right->Height)+1;
    }
    int D_Value() {
        if (!Left && !Right) return 0;  //如果是叶子节点就返回1
        if (!Left && Right) return -(Right->Height);   //左空又不空
        if (Left && !Right) return Left->Height;   //右空左不空
        if(Left&&Right) return Left->Height - Right->Height;
    }
};

AVLTree LL_Rotation(AVLTree A);
AVLTree RR_Rotation(AVLTree A);
AVLTree LR_Rotation(AVLTree A);
AVLTree RL_Rotation(AVLTree A);
AVLTree Insert(AVLTree T, int X);

int main() {
    int N;  //结点数
    int X;
    AVLTree T = nullptr;

    cin >> N;
    for (int i = 0; i < N; i++) {   //建树
        cin >> X;
        T = Insert(T, X);
    }
    cout << T->Data;  //输出结果

	return 0;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

AVLTree LL_Rotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */

    AVLTree B = A->Left;   //保存A的左子树
    A->Left = B->Right;    //A的左子树子树B的右子树x
    B->Right = A;    //让A变成B的右子树
    A->Height = A->GetHeight();
    B->Height = B->GetHeight();

    return B;
}

AVLTree RR_Rotation(AVLTree A)
{ /* 注意：A必须有一个右子结点B */

    AVLTree B = A->Right;  
    A->Right = B->Left;    
    B->Left = A;    
    A->Height = A->GetHeight();
    B->Height = B->GetHeight();

    return B;
}

AVLTree LR_Rotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = RR_Rotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return LL_Rotation(A);
}

AVLTree RL_Rotation(AVLTree A)
{ /* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做左单旋，C被返回 */
    A->Right = LL_Rotation(A->Right);
    /* 将A与C做右单旋，C被返回 */
    return RR_Rotation(A);
}

AVLTree Insert(AVLTree T, int X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T) { /* 若插入空树，则新建包含一个结点的树 */
        T = new AVLNode;
        T->Data = X;
    } /* if (插入空树) 结束 */

    else if (X < T->Data) {
        /* 插入T的左子树 */
        T->Left = Insert(T->Left, X);
        /* 如果需要左旋 */
        if (T->D_Value() == 2)
            if (X < T->Left->Data)
                T = LL_Rotation(T);      /* 左单旋 */
            else
                T = LR_Rotation(T); /* 左-右双旋 */
    } /* else if (插入左子树) 结束 */

    else if (X > T->Data) {
        /* 插入T的右子树 */
        T->Right = Insert(T->Right, X);
        /* 如果需要右旋 */
        if (T->D_Value() == -2)
            if (X > T->Right->Data)
                T = RR_Rotation(T);     /* 右单旋 */
            else
                T = RL_Rotation(T); /* 右-左双旋 */
    } /* else if (插入右子树) 结束 */

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = T->GetHeight();

    return T;
}