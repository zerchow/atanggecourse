#include "treap.h"

int main()
{
	srand((unsigned)time(NULL));

	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(rand() % 100);

	treap->printHorizontal();

	cutline();

	cout << "���ֵ ��" << treap->findMax() << endl;
	cout << "��Сֵ ��" << treap->findMin() << endl;
	cout << "��ǰ�� ��" << treap->rootPred() << endl;
	cout << "����� ��" << treap->rootSucc() << endl;

	cutline();

	treap->printVertical();

	system("pause");

	return 0;
}