#include "treap.h"

int main()
{
	srand((unsigned)time(NULL));

	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(rand() % 100);

	treap->printHorizontal();

	cutline();

	cout<< "���ֵ ��" << treap->findMax() 
		<< "����Сֵ ��" << treap->findMin() 
		<< "����ǰ�� ��" << treap->rootPred() 
		<< "������� ��" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	cutline();

	int del;
	cout<<"������Ҫɾ���Ľڵ㣺";
	cin>>del;
	treap->deleteNode(del);

	cutline();

	treap->printHorizontal();

	cutline();

	cout<< "���ֵ ��" << treap->findMax() 
		<< "����Сֵ ��" << treap->findMin() 
		<< "����ǰ�� ��" << treap->rootPred() 
		<< "������� ��" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	system("pause");

	return 0;//test
}