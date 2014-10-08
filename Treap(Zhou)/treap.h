#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;//

//�ڵ�ṹ;
struct TreapNode
{
	int data;              //������;
	int priority;          //����Ȩ;
	TreapNode * leftChild; //����;
	TreapNode * rightChild;//�Һ���;
};

//������;
class Treap
{
private:
	TreapNode * root;             //ָ����ڵ��ָ��;
	vector<int> priorityGenerator;  //������ȼ�������;
	static const int MAX_NODE = 1000;    //���Ľڵ���;
	int currentNodeNum;           //��ǰ�ڵ�����;
	queue<TreapNode*> nodes;

	//���ٷ���;
	void destroy(TreapNode *& node)
	{
		if (node == NULL)
			return;
		destroy(node->leftChild); //�ݹ�����������;
		destroy(node->rightChild);//�ݹ�����������;
		delete node;              //������ٸ��ڵ�;
		node = NULL;
	}

	//����һ��������ڵ�;
	TreapNode * generateDefaultNode(int data)
	{
		TreapNode * node = new TreapNode();                               //����һ���µĽڵ�;
		node->data = data;                                                //���ýڵ�����ֵ;
		node->priority = this->priorityGenerator[this->currentNodeNum ++];//���ýڵ����ȼ�;
		node->leftChild = NULL;                                           //���ýڵ�������;
		node->rightChild = NULL;                                          //���ýڵ�������;
		return node;
	}

	//����;
	void leftRotate(TreapNode *& node)
	{
		if (node == NULL || node->rightChild == NULL)
			return;
		TreapNode * rightChild = node->rightChild;
		node->rightChild = rightChild->leftChild;
		rightChild->leftChild = node;
		node = rightChild;
	}
	//����;
	void rightRotate(TreapNode *& node)
	{
		if (node == NULL || node->leftChild == NULL)
			return;
		TreapNode * leftChild = node->leftChild;
		node->leftChild = leftChild->rightChild;
		leftChild->rightChild = node;
		node = leftChild;
	}
	//����һ���ڵ�;
	void insertNode(TreapNode *& node, const int data)
	{
		if (node == NULL)
		{
			node = this->generateDefaultNode(data);
		}
		else if (node->data >= data)
		{
			this->insertNode(node->leftChild, data);
			if (node->priority > node->leftChild->priority)
				this->rightRotate(node);
		}
		else
		{
			this->insertNode(node->rightChild, data);
			if (node->priority > node->rightChild->priority)
				this->leftRotate(node);
		}
	}
	//ɾ��һ���ڵ�;
	void deleteNode(TreapNode *& node, const int data)
	{
		if (node == NULL)
			return;
		if (node->data == data)
		{
			if (node->leftChild == NULL || node->rightChild == NULL)
			{
				TreapNode * tempNode = node;
				if (node->leftChild != NULL)
					node = node->leftChild;
				else
					node = node->rightChild;
				delete node;
			}
			else
			{
				if (node->leftChild->priority < node->rightChild->priority)
				{
					this->rightRotate(node);
					deleteNode(node->rightChild, data);
				}
				else
				{
					this->leftRotate(node);
					deleteNode(node->leftChild, data);
				}
			}
		}
		else if (node->data > data)
		{
			deleteNode(node->leftChild, data);
		}
		else
		{
			deleteNode(node->rightChild, data);
		}
	}
	//��ӡ����;
	void print(TreapNode *& node, int spaceNum) const
	{
		if (node == NULL)
		{
			for (int i = 0; i < spaceNum; i++)
				cout << "\t";
			cout << "NULL" << endl;
			return;
		}
		if (node->leftChild != NULL)
		{
			print(node->leftChild, spaceNum + 1);
		}
		for (int i = 0; i < spaceNum; i++)
			cout << "\t";
		cout << node->data << "/" << node->priority << endl;
		if (node->rightChild != NULL)
		{
			print(node->rightChild, spaceNum + 1);
		}
	}
	//BFS
	void treapBFS()
	{
		if (this->root == NULL)
			return;
		queue<TreapNode*> temp;
		TreapNode * node = this->root;
		temp.push(node);
		while (!temp.empty())
		{
			
		}
	}
	
public:

	//���캯��;
	Treap()
	{
		this->root = NULL;
		this->currentNodeNum = 0;

		//������ȼ��Ĵ���;
		for (int i = 1; i <= MAX_NODE; ++i)
			this->priorityGenerator.push_back(i);
		random_shuffle(this->priorityGenerator.begin(), this->priorityGenerator.end());
	}
	//��������;
	~Treap()
	{
		this->destroy(this->root);
		this->currentNodeNum = 0;
	}
	//����һ���ڵ�;
	void insertNode(int data)
	{
		this->insertNode(this->root, data);
	}
	//ɾ��һ���ڵ�;
	void deleteNode(int data)
	{
		this->deleteNode(this->root, data);
	}
	//��ӡ����;
	void print()
	{
		print(this->root, 0);
	}
	//������Сֵ;
	int findMin()
	{
		if (this->root == NULL)
			return -1;
		TreapNode * node = this->root;
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node->data;
	}
	//�������ֵ;
	int findMax()
	{
		if (this->root == NULL)
			return -1;
		TreapNode * node = this->root;
		while (node->rightChild != NULL)
			node = node->rightChild;
		return node->data;
	}
};