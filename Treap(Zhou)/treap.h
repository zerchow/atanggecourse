#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;//

//节点结构;
struct TreapNode
{
	int data;              //数据项;
	int priority;          //优先权;
	TreapNode * leftChild; //左孩子;
	TreapNode * rightChild;//右孩子;
};

//树堆类;
class Treap
{
private:
	TreapNode * root;             //指向根节点的指针;
	vector<int> priorityGenerator;  //随机优先级的数组;
	static const int MAX_NODE = 1000;    //最多的节点数;
	int currentNodeNum;           //当前节点数量;
	queue<TreapNode*> nodes;

	//销毁方法;
	void destroy(TreapNode *& node)
	{
		if (node == NULL)
			return;
		destroy(node->leftChild); //递归销毁左子树;
		destroy(node->rightChild);//递归销毁右子树;
		delete node;              //最后销毁父节点;
		node = NULL;
	}

	//产生一个待插入节点;
	TreapNode * generateDefaultNode(int data)
	{
		TreapNode * node = new TreapNode();                               //创建一个新的节点;
		node->data = data;                                                //设置节点数据值;
		node->priority = this->priorityGenerator[this->currentNodeNum ++];//设置节点优先级;
		node->leftChild = NULL;                                           //设置节点左子树;
		node->rightChild = NULL;                                          //设置节点右子树;
		return node;
	}

	//左旋;
	void leftRotate(TreapNode *& node)
	{
		if (node == NULL || node->rightChild == NULL)
			return;
		TreapNode * rightChild = node->rightChild;
		node->rightChild = rightChild->leftChild;
		rightChild->leftChild = node;
		node = rightChild;
	}
	//右旋;
	void rightRotate(TreapNode *& node)
	{
		if (node == NULL || node->leftChild == NULL)
			return;
		TreapNode * leftChild = node->leftChild;
		node->leftChild = leftChild->rightChild;
		leftChild->rightChild = node;
		node = leftChild;
	}
	//插入一个节点;
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
	//删除一个节点;
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
	//打印树堆;
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

	//构造函数;
	Treap()
	{
		this->root = NULL;
		this->currentNodeNum = 0;

		//随机优先级的处理;
		for (int i = 1; i <= MAX_NODE; ++i)
			this->priorityGenerator.push_back(i);
		random_shuffle(this->priorityGenerator.begin(), this->priorityGenerator.end());
	}
	//析构函数;
	~Treap()
	{
		this->destroy(this->root);
		this->currentNodeNum = 0;
	}
	//插入一个节点;
	void insertNode(int data)
	{
		this->insertNode(this->root, data);
	}
	//删除一个节点;
	void deleteNode(int data)
	{
		this->deleteNode(this->root, data);
	}
	//打印树堆;
	void print()
	{
		print(this->root, 0);
	}
	//返回最小值;
	int findMin()
	{
		if (this->root == NULL)
			return -1;
		TreapNode * node = this->root;
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node->data;
	}
	//返回最大值;
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