#include <iostream>
#include <array>

#define MaxSize 10 //�������Ĵ洢��С
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
};

class Tree : public TreeNode {
public:
    std::array <TreeNode, MaxSize> T;
    int Root;    //���ڵ��±�
    int Num_of_Node;   //�ڵ���

    Tree() {
        Root = -1;
        Num_of_Node = 0;
    }

    void Buildtree();     //����
}T1, T2;

int Isomorphic(int R1, int R2);

int main() {
    T1.Buildtree();
    T2.Buildtree();

    if (Isomorphic(T1.Root, T2.Root))
        std::cout << "Yes\n";
    else
        std::cout << "No\n";
}

void Tree::Buildtree(){
    int i, check[MaxSize]{ 0 };
    char cl, cr;

    std::cin >> Num_of_Node;
    if (Num_of_Node){
        for (i = 0; i < Num_of_Node; i++){
            std::cin >> T[i].element >> cl >> cr;
            if (cl != '-') {                    //�ж������Ƿ�ָ��ĳ�����
                T[i].left = cl - '0';          //����Ľ�������ֱ�ʾ
                check[T[i].left] = 1;         //����ָ���checkֵ��Ϊ1���ų��Ǹ��ڵ�Ŀ���
            }
            else{
                T[i].left = Null;
            }

            if (cr != '-'){      //��ͬ��
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else{
                T[i].right = Null;
            }
        }

        for (i = 0; i < Num_of_Node; i++)            //���check��ֵΪ0��Ϊ���ڵ�
            if (!check[i]) break;
        Root= i;                         //�����ڵ㱣����Root��
    }
}

int Isomorphic(int R1, int R2)
{
    if ((R1 == Null) && (R2 == Null))   //��������
        return 1;
    if ((R1 != Null && R2 == Null) || (R1 == Null && R2 != Null))  //һ����һ������
        return 0;
    if (T1.T[R1].element != T2.T[R2].element)//��������
        return 0;
    if ((T1.T[R1].left == Null) && (T2.T[R2].left == Null))  //��գ���ݹ�������
        return Isomorphic(T1.T[R1].right, T2.T[R2].right);
    if ((T1.T[R1].left != Null) && (T2.T[R2].left != Null) && \
        ((T1.T[T1.T[R1].left].element) == (T2.T[T2.T[R2].left].element)))         //�󶼲�Ϊ�գ�����ȣ��Ƚ���һ�������һ��������            
        return (Isomorphic(T1.T[R1].left, T2.T[R2].left) && \
            Isomorphic(T1.T[R1].right, T2.T[R2].right));
    else return (Isomorphic(T1.T[R1].left, T2.T[R2].right) && \
        Isomorphic(T1.T[R1].right, T2.T[R2].left));                  //���������ֻҪ�����ȽϾ���
}