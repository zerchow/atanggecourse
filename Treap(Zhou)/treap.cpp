#include "treap.h"

int main()
{
	srand((unsigned)time(NULL));

	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(rand() % 100);

	treap->printHorizontal();

	cutline();

	cout << "最大值 ：" << treap->findMax()
		<< "，最小值 ：" << treap->findMin()
		<< "，根前驱 ：" << treap->rootPred()
		<< "，根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	cutline();

	int del;
	cout << "请输入要删除的节点：";
	cin >> del;
	treap->deleteNode(del);

	cutline();

	treap->printHorizontal();

	cutline();

	cout << "最大值 ：" << treap->findMax()
		<< "，最小值 ：" << treap->findMin()
		<< "，根前驱 ：" << treap->rootPred()
		<< "，根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	cutline();

	int fin;
	cout << "请输入要查找的节点：";
	cin >> fin;
	treap->findNode(fin);

	cutline();

	int upd;
	cout << "将查找的节点更新为：";
	cin >> upd;
	if (treap->updateNode(fin, upd))
		cout << "更新成功！" << endl;
	else
		cout << "更新失败！" << endl;

	cutline();

	treap->printHorizontal();

	cutline();

	cout << "最大值 ：" << treap->findMax()
		<< "，最小值 ：" << treap->findMin()
		<< "，根前驱 ：" << treap->rootPred()
		<< "，根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	system("pause");

	return 0;
}