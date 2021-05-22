#include <iostream>

#define MaxSize 100

using namespace std;

using ElementType = int;     //默认元素为整型
using SetName = int;       //根节点下标为集合名称
using SetType = int[MaxSize];      

void Init(SetType S, int n);     //将所有节点变为-1，且可以用负的数字表示元素数字或这树高
SetName Find(SetType S, ElementType X);      //找到元素所在集合
void Union(SetType S, SetName Root1, SetName Root2);   //按秩归并
void Input_connection(SetType S);
void Check_connection(SetType S);
void Check_network(SetType S, int n);

int main() {
	SetType S;
	int n;
	char in;

	cin >> n;
	Init(S, n);
	do {
		cin >> in;
		switch (in) {
			case 'I':Input_connection(S);break;
			case 'C':Check_connection(S);break;
			case 'S':Check_network(S, n);break;
		}
	} while (in != 'S');

	return 0;
}

void Init(SetType S, int n) {
	for (int i = 0; i < n; i++) {
		S[i] = -1;
	}
}

SetName Find(SetType S, ElementType X) {
	if (S[X] < 0) return X;
	else {  //压缩路径
		S[X] = Find(S, S[X]);
		return S[X];
	}
}

void Union(SetType S, SetName Root1, SetName Root2) {
	if (S[Root2] < S[Root1]) {
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else {
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}

void Input_connection(SetType S) {
	ElementType u, v;
	SetName Root1, Root2;
	cin >> u >> v;
	Root1 = Find(S, u - 1);
	Root2 = Find(S, v - 1);
	if (Root1 != Root2) Union(S, Root1, Root2);
}

void Check_connection(SetType S) {
	ElementType u, v;
	SetName Root1, Root2;
	cin >> u >> v;
	Root1 = Find(S, u - 1);
	Root2 = Find(S, v - 1);
	if (Root1 == Root2) cout << "yes\n";
	else cout << "no\n";
}

void Check_network(SetType S, int n) {
	int i, counter = 0;
	for (i = 0; i < n; i++) {
		if (S[i] < 0) counter++;
	}
	if (counter == 1) cout << "The network is connected.";
	else cout << "There are " << counter << " components.";
}