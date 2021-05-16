#include <iostream>

#define MinData -10001

using namespace std;

class MinHeap {
public:
    int* Elements;       //�洢��Ԫ�ص�����
    int Size;           //�ѵĵ�ǰԪ�ظ���
    int Capacity;      //�ѵ��������

public:
    MinHeap(int MaxSize) {
        Elements = new int[MaxSize + 1];     //���ڱ���λ��
        Size = 0;
        Capacity = MaxSize;
        Elements[0] = MinData;             //�����ڱ�Ϊ��������Ԫ�ص���Сֵ
    }

    void Insert(int item) {     //����Ԫ�� 
        int i;

        i = ++Size;    //ָ������һ��Ԫ�ص�λ��
        for (; Elements[i / 2] > item; i /= 2)      //�ڱ�����˲���Ľ�������н���������
            Elements[i] = Elements[i / 2];
        Elements[i] = item;
    }
    int Delete() {         //ɾ��Ԫ��
        int Parent, child;
        int MinItem, temp;

        MinItem = Elements[1];
        temp = Elements[Size--];
        for (Parent = 1; Parent * 2 <= Size; Parent = child)
        {
            child = Parent * 2;
            if ((child < Size) && \
                (Elements[child] > Elements[child + 1]))
                child++;
            if (temp <= Elements[child]) break;
            else
                Elements[Parent] = Elements[child];
        }
        Elements[Parent] = temp;
        return MinItem;
    }
    void Out_path(int index) { //���·��
        while (index != 1) {
            cout << Elements[index] << ' ';
            index /= 2;
        }
        cout << Elements[1];
    }
};

int main() {
    int node, path;
    int item, index;
    int i;
    MinHeap H{ 1000 };

    cin >> node >> path;
    for (i = 0; i < node; i++) {
        cin >> item;
        H.Insert(item);
    }

    for (i = 0; i < path; i++) {
        cin >> index;
        H.Out_path(index);
        if (i != path - 1) cout << "\n";
    }

    return 0;
}