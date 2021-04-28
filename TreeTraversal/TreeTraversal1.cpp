#include <iostream>
#include <stack>
#include <string>

using namespace std;

#define Left_ 0
#define Right_ 1

using BinTree = class TreeNode*;
class TreeNode {
public:
    int Data=-1;
    BinTree Left=nullptr;
    BinTree Right= nullptr;
};

BinTree BuidTree();    //�������������������䣬����ת��Ϊ��
void PostOrderTraversal(BinTree BT);   //��������������
//void PostOrderTraversal_(BinTree BT);  //�Ǳ���

int main() {
    BinTree BT=nullptr;

    BT = BuidTree();    //����
    PostOrderTraversal(BT);   //�����õ�������������
   // PostOrderTraversal_(BT);

    return 0;
}

BinTree BuidTree() {
    stack<BinTree> S;  //��Ž��
    string s;   //�ݴ����
    int x;    //��ʾ��������
    BinTree BT = nullptr;  //��
    BinTree father=nullptr;  //��ʾ���ڵ㣬nullptr��������
    int child = Left_;  //������ʾ���ӽڵ����һ�����
    int N;  //���������������Ӷ����Լ��������

    cin >> N;
    for (int i = 0; i < N*2; i++) {
        cin>>s;
        if (s.length() == 4) {  //�����push x
            cin >> x;
            if (!father) {
                BT = new TreeNode;  //��
                BT->Data = x;  //����Ǹ��ڵ�͸�ֵ
                father = BT;//���浱ǰ���ڵ�
                S.push(father);
            }
            else if (child == Left_) {    //�����������Ӿ�����ڵ��
                BinTree LN = new TreeNode;
                LN->Data = x;
                father->Left = LN;
                father = LN;
                S.push(father);
            }
            else if (child == Right_) {   //���������Һ��Ӿ����ҽڵ��
                BinTree RN = new TreeNode;
                RN->Data = x;
                father->Right = RN;
                father = RN;
                S.push(father);
                child = Left_;   //������һ�������push�ͻ�����ڵ��
            }
        }
        else {  //�����pop
            father = S.top();   //���浱ǰ���ڵ�
            S.pop();
            child = Right_;  //����pop�͸���child
        }
    }
    return BT;  //���ؽ��ָ��
}

void PostOrderTraversal(BinTree BT) {     //��������ĵݹ��㷨
    static int isFirst = 1;  //�����ж��Ƿ��ǵ�һ�����

    if (BT != nullptr) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        if (isFirst) {
            cout << BT->Data;    //�����һ���ո��ҽ�βû�пո�
            isFirst = 0;
        }
        else cout << " " << BT->Data;
    }
}

/*
void PostOrderTraversal_(BinTree BT) {
    BinTree B = BT;
    BinTree temp = nullptr; //��ʱ�����ϴ�����������
    stack<BinTree> S;
    int isFirst = 1;

    while (B || !S.empty()) {
        while (B) {
            S.push(B);
            B = B->Left;
        }
        if (!S.empty()) {
            B = S.top();
            S.pop();
            // ��������Ϊ�գ����ϴ��׳������Ҷ��ӣ�������׳���temp����NULL�����ϴ������������
            if (B->Right == nullptr || B->Right == temp) {
                if (isFirst) {
                    cout << B->Data;
                    isFirst = 0;
                }
                else {
                    cout << " " << B->Data;
                }
                temp = B;    //������һ������������
                B = nullptr; // ���������������ˣ�ָ����ΪNULL,�����������丸���
            }
            //����ǰ����������������򽫵�ǰ�������ѹ��ջ����Tָ����������
            else {
                S.push(B);
                B = B->Right;
            }
        }
    }
}
*/