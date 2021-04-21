#include <iostream>

#define MaxSize 10 //数组最大的存储大小
#define Tree int
#define Null -1

class TreeNode {    //创建树节点
public:
    char element;     //结点储存的字母
    int left;   //左子树，没有则为-1
    int right;  //右子树

    TreeNode() = default;
    TreeNode(char c_, int left_, int right_) {
        this->element = c_;
        this->left = left_;
        this->right = right_;
    }
} T1[MaxSize], T2[MaxSize];


Tree BuildTree(TreeNode* T);      //建树
int Isomorphic(Tree R1, Tree R2);            //判断是否同构

int main() {
    Tree R1, R2;

    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if (Isomorphic(R1, R2))
        std::cout << "Yes\n";
    else
        std::cout << "No\n";
}

Tree BuildTree(TreeNode* T)
{
    int N, i, check[MaxSize]{0}, Root = Null;
    char cl, cr;

    std::cin >> N;
    if (N)
    {
        for (i = 0; i < N; i++) check[i] = 0;
        for (i = 0; i < N; i++)
        {
            std::cin >> T[i].element >> cl >> cr;
            if (cl != '-')                     //判断左孩子是否指向某个结点
            {
                T[i].left = cl - '0';          //输入的结点用数字表示
                check[T[i].left] = 1;         //将被指向的check值设为1，排除是根节点的可能
            }
            else
            {
                T[i].left = Null;
            }

            if (cr != '-')      //右同上
            {
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else
            {
                T[i].right = Null;
            }
        }

        for (i = 0; i < N; i++)            //如果check的值为0则为根节点
            if (!check[i]) break;
        Root = i;                         //将根节点保存在Root上
    }
    return Root;
}

int Isomorphic(Tree R1, Tree R2)
{
    if ((R1 == Null) && (R2 == Null))   //两个空树
        return 1;
    if ((R1 != Null && R2 == Null) || (R1 == Null && R2 != R2))  //一个空一个不空
        return 0;
    if (T1[R1].element != T2[R2].element)//两个不等
        return 0;
    if ((T1[R1].left == Null) && (T2[R2].left == Null))  //左空，则递归右子树
        return Isomorphic(T1[R1].right, T2[R2].right);
    if ((T1[R1].left != Null) && (T2[R2].left != Null) && \
        ((T1[T1[R1].left].element) == (T2[T2[R2].left].element)))         //左都不为空，且相等，比较下一个左和上一个结点的右            
        return (Isomorphic(T1[R1].left, T2[R2].left) && \
            Isomorphic(T1[R1].right, T2[R2].right));
    else return (Isomorphic(T1[R1].left, T2[R2].right) && \
        Isomorphic(T1[R1].right, T2[R2].left));                  //其他的情况只要交换比较就行
}