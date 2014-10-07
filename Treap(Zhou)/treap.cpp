#include "treap.h"

int main()
{
	Treap * treap = new Treap();

	for (int i = 0; i < 10; ++i)
		treap->insertNode(i);

	treap->print();

	cout << treap->findMax();
	cout << treap->findMin();
	return 0;
}