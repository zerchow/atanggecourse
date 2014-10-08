#include "treap.h"

int main()
{
	srand((unsigned)time(NULL));

	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(rand() % 100);

	treap->printHorizontal();

	cutline();

	cout << "最大值 ：" << treap->findMax() << endl;
	cout << "最小值 ：" << treap->findMin() << endl;
	cout << "根前驱 ：" << treap->rootPred() << endl;
	cout << "根后继 ：" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	system("pause");

	return 0;
}