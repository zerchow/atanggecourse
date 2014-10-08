#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;//

//节点结构;
struct TreapNode
{
	int data;              //数据项;
	int priority;          //优先权;
	TreapNode * leftChild; //左孩子;
	TreapNode * rightChild;//右孩子;
};

//华丽的分割线;
void cutline()
{
	cout << "-------------------------------------------------------" << endl;
}

//树堆类;
class Treap
{
private:
	TreapNode * root;                //指向根节点的指针;
	vector<int> priorityGenerator;   //随机优先级的数组;
	static const int MAX_NODE = 1000;//最多的节点数;
	int currentNodeNum;              //当前节点数量;
	vector<TreapNode*> nodes;

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
	//横向打印树堆;
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
	//利用BFS纵向打印树堆;
	void treapBFS()
	{
		if (this->root == NULL)
			return;
		queue<TreapNode*> temp;       //临时队列，用于BFS;
		TreapNode * node = this->root;//根节点;
		temp.push(node);              //保存根节点;
		int notnullnum = 1;           //记录非空节点的个数;
		while (!temp.empty())
		{
			TreapNode * tempNode = temp.front();
			temp.pop();

			//如果没有非空节点，不继续处理，避免无限循环;
			if (notnullnum > 0)
			{
				this->nodes.push_back(tempNode);

				//为了打印格式的整齐，增加空节点;
				if (tempNode == NULL)
				{
					temp.push(NULL);
					temp.push(NULL);
				}
				else
				{
					--notnullnum;
					if (tempNode->leftChild != NULL)
						++notnullnum;
					if (tempNode->rightChild != NULL)
						++notnullnum;
					temp.push(tempNode->leftChild);
					temp.push(tempNode->rightChild);
				}
			}
		}

		//增加一定个数的空节点，使树堆成为完全二叉树;
		int size = this->nodes.size();
		int index = 1;
		while (index < size)
			index *= 2;
		while (size < index - 1)
		{
			this->nodes.push_back(NULL);
			++ size;
		}
	}
	
	//以一个节点为起点，找最小值;
	int findMin(TreapNode * node)
	{
		if (node == NULL)
			return -1;
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node->data;
	}
	//以一个节点为起点，找最大值;
	int findMax(TreapNode * node)
	{
		if (node == NULL)
			return -1;
		while (node->rightChild != NULL)
			node = node->rightChild;
		return node->data;
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
	//横向打印树堆;
	void printHorizontal()
	{
		print(this->root, 0);
	}
	//返回最小值;
	int findMin()
	{
		return findMin(this->root);
	}
	//返回最大值;
	int findMax()
	{
		return findMax(this->root);
	}
	//返回根节点的前驱节点;
	int rootPred()
	{
		if (this->root == NULL)
			return -1;
		return findMax(this->root->leftChild);
	}
	//返回根节点的后继节点;
	int rootSucc()
	{
		if (this->root == NULL)
			return -1;
		return findMin(this->root->rightChild);
	}
	//纵向打印树堆;
	void printVertical()
	{
		this->treapBFS();
		int size = this->nodes.size();
		if (size == 0)
			return;
		int index = 1;
		int begin = 0;
		int end = begin + 1;
		do
		{
			int spacenum = (size - index - index + 1) / 2;
			for (int i = 0; i < spacenum; ++i)
				cout << " ";
			for (int i = begin; i < end; ++ i)
			{
				TreapNode * node = this->nodes[i];
				if (node == NULL)
					cout << "*";
				else
					cout << node->data;
				cout << " ";
			}
			cout << endl; 
			begin = end;
			index *= 2;
			end += index;
		} while (end <= size);
	}
};