#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MinData -1
#define MAXSIZE 1001

using namespace std;

using HuffmanTree =class TreeNode*;
class TreeNode {
private:
    int Weight=0;   //Ȩ��
    HuffmanTree Left=nullptr;
    HuffmanTree Right=nullptr;

public:
    friend class MinHeap;

    int WPL(int Depth);   //�����������ű��볤��,H�����
    bool is_suc_BuildHT(string Code, vector<int> Weight_,int index);    //����������ı���ת������,�ж��Ƿ�ɹ�
};

class MinHeap {
private:
    HuffmanTree Elements[MAXSIZE];       //�洢��Ԫ�ص�����
    int Size;           //�ѵĵ�ǰԪ�ظ���
    int Capacity;      //�ѵ��������,������ָ����Ľ����

public:
    MinHeap(int MaxSize);

    HuffmanTree Huffman();       //�����������
    void AddData(vector<int> Weight_);  //�Ȱ���ȫ��������������
    HuffmanTree Delete();   //ȡ���Ѷ�
    void PercDown(int Root);         //���˺���
    void BuildMinHeap();               //��Ȩ�ص�������
    void Insert(HuffmanTree item);     //����Ԫ�� 
};

int main()
{
    HuffmanTree T;           //Ϊ������СWPL��������
    int Num_of_Node, Num_of_test;    //����������ĸ���
    vector<int> Weight;  //���Ȩ��ֵ
    int CodeLen;    //����WPL
    queue<int> Q;  //��������жϵĽ��  
    int count = 0;  //Ϊ�˽�β���û�л��з�

    cin >> Num_of_Node;       //��������
    MinHeap H{ Num_of_Node };   //������H

    char c_;
    int weight_;
    for (int i = 0; i < Num_of_Node; i++) {    //��Ȩ��ֵ���뵽������
        cin >> c_ >> weight_;
        Weight.push_back(weight_);
    }

    H.AddData(Weight);   //�������ݣ�������ȫ������
    H.BuildMinHeap();    //��Ȩֵ���ѵ���Ϊ��С��
    T=H.Huffman();  //���ɹ�������

    CodeLen = T->WPL(0);  //����СWPL

    cin >> Num_of_test;   //����Ҫ���Ե�����
    for (int i = 0; i < Num_of_test; i++) {
        int flag = 1;
        char C;
        string Code;
        HuffmanTree HT=new TreeNode;   //���ݱ��빹������

        for (int j = 0; j < Num_of_Node; j++) {     //���Ա���
            cin >> C >> Code;
            if (Code.length() > Num_of_Node - 1) flag = 0;   //���Ȳ�����
            if (flag && !HT->is_suc_BuildHT(Code, Weight, j)) flag = 0;    //���ȷ����˾ͽ���
        }
        if (flag&& (HT->WPL(0) == CodeLen)) Q.push(true);  //�ж����Ƿ񽨳ɣ������Ƿ����ǰ׺��淶�������˾����ж�WPL
        else  Q.push(false); //����ֱ���жϲ���

        delete HT;
    }

    while (!Q.empty()) {
        if (Q.front()) cout << "Yes";
        else cout << "No";

        Q.pop();
        count++;
        if (count != Num_of_test) cout << endl;
    }

    return 0;
}

bool TreeNode::is_suc_BuildHT(string Code, vector<int> Weight_, int index) {
    int i = 0;

    if (i < Code.length()) {
        if (Code[i] == '0') {
            if (Left == nullptr) {
                HuffmanTree T = new TreeNode;
                T->Weight = Weight_[index];
                Left = T;
                if (Code.length() == 1) return true; 
            }
            if (Code.length() == 1) return false;
            else return Left->is_suc_BuildHT(Code.substr(i + 1), Weight_, index);
        }
        else if (Code[i] == '1') {
            if (Right == nullptr) {
                HuffmanTree T = new TreeNode;
                T->Weight = Weight_[index];
                Right = T;
                if (Code.length() == 1) return true;
            }
            if (Code.length() == 1) return false;
            else return Right->is_suc_BuildHT(Code.substr(i + 1), Weight_, index);
        }
    }  
}

int TreeNode::WPL(int Depth) {
    if (Left == nullptr && Right == nullptr)
        return Depth * Weight;
    else if (Left && Right) return Left->WPL(Depth + 1) + Right->WPL(Depth + 1);
    else return -1000;  //����һ��������ʱ�򣬿��ܻ����������Ϲ����������ص�3
}

HuffmanTree MinHeap::Huffman(){    //����H->Capacity��Ȩ��ֵ�Ѿ������H->Element[]->Weight
    HuffmanTree T;

    for (int i = 1; i < Capacity; i++)
    {
        T = new TreeNode;
        T->Left = Delete();
        T->Right = Delete();
        T->Weight = T->Left->Weight + T->Right->Weight;

        Insert(T);     //��T������С��
    }
    T = Delete();

    return T;
}

MinHeap::MinHeap(int MaxSize) {
    Size = MaxSize;
    Capacity = MaxSize;
    HuffmanTree Node = new TreeNode;
    Node->Weight = MinData;             //�����ڱ�Ϊ��������Ԫ�ص���Сֵ
    Elements[0] = Node;
}

void MinHeap::AddData(vector<int> Weight_) {
    for (int i = 0; i < Capacity; i++) {
        HuffmanTree Node = new TreeNode;
        Node->Weight = Weight_[i];
        Elements[i + 1] = Node;
    }
}

HuffmanTree MinHeap::Delete(){
    int Parent, child;
    HuffmanTree MinItem, temp;
    /*����Ҫ���Բ����ж϶��Ƿ�Ϊ��*/
    MinItem = Elements[1];
    temp = Elements[Size--];
    for (Parent = 1; Parent * 2 <= Size; Parent = child)
    {
        child = Parent * 2;
        if ((child < Size) && \
            (Elements[child]->Weight > Elements[child + 1]->Weight))
            child++;
        if (temp->Weight <= Elements[child]->Weight) break;
        else
            Elements[Parent] = Elements[child];
    }
    Elements[Parent] = temp;

    return MinItem;
}

void MinHeap::PercDown(int Root){ /* ���ˣ���H����Elements[p]Ϊ�����Ӷѵ���Ϊ��С�� */
    int Parent, Child;
    HuffmanTree X;

    X = Elements[Root]; /* ȡ��������ŵ�ֵ */
    for (Parent = Root; Parent * 2 <= Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != Size) && (Elements[Child]->Weight > Elements[Child + 1]->Weight))
            Child++;  /* Childָ�������ӽ��Ľ�С�� */
        if (X->Weight <= Elements[Child]->Weight) break; /* �ҵ��˺���λ�� */
        else  /* ����X */
            Elements[Parent] = Elements[Child];
    }
    Elements[Parent] = X;
}

void MinHeap::BuildMinHeap(){ /* ����Elements[]�е�Ԫ�أ�ʹ������С�ѵ�������  */
  /* �����������H->Size��Ԫ���Ѿ�����Elements[]�� */

    int i;

    /* �����һ�����ĸ��ڵ㿪ʼ���������1 */
    for (i = Size / 2; i > 0; i--)
        PercDown(i);
}

void MinHeap::Insert(HuffmanTree item){
    int i;
    /*����Ҫ�����ж϶��Ƿ�����*/
    i = ++Size;    //ָ������һ��Ԫ�ص�λ��
    for (; Elements[i / 2]->Weight > item->Weight; i /= 2) {      //�ڱ�����˲���Ľ�������н����С�����
        Elements[i] = Elements[i / 2];
    }
    Elements[i] = item;
}