#include "treap.h"

int main()
{
	srand((unsigned)time(NULL));

	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(rand() % 100);

	treap->printHorizontal();

	cutline();

	cout<< "最大值 ：" << treap->findMax() 
		<< "，最小值 ：" << treap->findMin() 
		<< "，根前驱 ：" << treap->rootPred() 
		<< "，根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	cutline();

	int del;
	cout<<"请输入要删除的节点：";
	cin>>del;
	treap->deleteNode(del);

	cutline();

	treap->printHorizontal();

	cutline();

	cout<< "最大值 ：" << treap->findMax() 
		<< "，最小值 ：" << treap->findMin() 
		<< "，根前驱 ：" << treap->rootPred() 
		<< "，根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	system("pause");

	return 0;//test
}