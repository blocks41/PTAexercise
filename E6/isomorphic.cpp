#include <iostream>

#define MaxSize 10 //�������Ĵ洢��С
#define Tree int
#define Null -1

class TreeNode {    //�������ڵ�
public:
    char element;     //��㴢�����ĸ
    int left;   //��������û����Ϊ-1
    int right;  //������

    TreeNode() = default;
    TreeNode(char c_, int left_, int right_) {
        this->element = c_;
        this->left = left_;
        this->right = right_;
    }
} T1[MaxSize], T2[MaxSize];


Tree BuildTree(TreeNode* T);      //����
int Isomorphic(Tree R1, Tree R2);            //�ж��Ƿ�ͬ��

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
            if (cl != '-')                     //�ж������Ƿ�ָ��ĳ�����
            {
                T[i].left = cl - '0';          //����Ľ�������ֱ�ʾ
                check[T[i].left] = 1;         //����ָ���checkֵ��Ϊ1���ų��Ǹ��ڵ�Ŀ���
            }
            else
            {
                T[i].left = Null;
            }

            if (cr != '-')      //��ͬ��
            {
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else
            {
                T[i].right = Null;
            }
        }

        for (i = 0; i < N; i++)            //���check��ֵΪ0��Ϊ���ڵ�
            if (!check[i]) break;
        Root = i;                         //�����ڵ㱣����Root��
    }
    return Root;
}

int Isomorphic(Tree R1, Tree R2)
{
    if ((R1 == Null) && (R2 == Null))   //��������
        return 1;
    if ((R1 != Null && R2 == Null) || (R1 == Null && R2 != R2))  //һ����һ������
        return 0;
    if (T1[R1].element != T2[R2].element)//��������
        return 0;
    if ((T1[R1].left == Null) && (T2[R2].left == Null))  //��գ���ݹ�������
        return Isomorphic(T1[R1].right, T2[R2].right);
    if ((T1[R1].left != Null) && (T2[R2].left != Null) && \
        ((T1[T1[R1].left].element) == (T2[T2[R2].left].element)))         //�󶼲�Ϊ�գ�����ȣ��Ƚ���һ�������һ��������            
        return (Isomorphic(T1[R1].left, T2[R2].left) && \
            Isomorphic(T1[R1].right, T2[R2].right));
    else return (Isomorphic(T1[R1].left, T2[R2].right) && \
        Isomorphic(T1[R1].right, T2[R2].left));                  //���������ֻҪ�����ȽϾ���
}