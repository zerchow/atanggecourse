#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

//�ڵ�ṹ;
struct TreapNode
{
	int data;              //������;
	int priority;          //����Ȩ;
	TreapNode * leftChild; //����;
	TreapNode * rightChild;//�Һ���;
};

//�����ķָ���;
void cutline()
{
	cout << "-------------------------------------------------------" << endl;
}

//������;
class Treap
{
private:
	TreapNode * root;                //ָ����ڵ��ָ��;
	vector<int> priorityGenerator;   //������ȼ�������;
	static const int MAX_NODE = 1000;//���Ľڵ���;
	int currentNodeNum;              //��ǰ�ڵ�����;
	vector<TreapNode*> nodes;

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

	//����һ��������ڵ㣨�������Ȩ��;
	TreapNode * generateDefaultNode(int data)
	{
		TreapNode * node = new TreapNode();                               //����һ���µĽڵ�;
		node->data = data;                                                //���ýڵ�����ֵ;
		node->priority = this->priorityGenerator[this->currentNodeNum ++];//���ýڵ����ȼ�;
		node->leftChild = NULL;                                           //���ýڵ�������;
		node->rightChild = NULL;                                          //���ýڵ�������;
		return node;
	}

	//����һ��������ڵ㣨�趨����Ȩ��;
	TreapNode * generateSpecialNode(int data, int priority)
	{
		TreapNode * node = new TreapNode();//����һ���µĽڵ�;
		node->data = data;                 //���ýڵ�����ֵ;
		node->priority = priority;         //���ýڵ����ȼ�;
		node->leftChild = NULL;            //���ýڵ�������;
		node->rightChild = NULL;           //���ýڵ�������;
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
	//����һ���ڵ㣨�������Ȩ��;
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
	//����һ���ڵ㣨�趨����Ȩ��;
	void insertNode(TreapNode *& node, const int data, const int priority)
	{
		if (node == NULL)
		{
			node = this->generateSpecialNode(data, priority);
		}
		else if (node->data >= data)
		{
			this->insertNode(node->leftChild, data, priority);
			if (node->priority > node->leftChild->priority)
				this->rightRotate(node);
		}
		else
		{
			this->insertNode(node->rightChild, data, priority);
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
				delete tempNode;
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
	//�����ӡ����;
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
	//����BFS�����ӡ����;
	void treapBFS()
	{
		if (this->root == NULL)
			return;
		this->nodes.clear();          //���;
		queue<TreapNode*> temp;       //��ʱ���У�����BFS;
		TreapNode * node = this->root;//���ڵ�;
		temp.push(node);              //������ڵ�;
		int notnullnum = 1;           //��¼�ǿսڵ�ĸ���;
		while (!temp.empty())
		{
			TreapNode * tempNode = temp.front();
			temp.pop();

			//���û�зǿսڵ㣬������������������ѭ��;
			if (notnullnum > 0)
			{
				this->nodes.push_back(tempNode);

				//Ϊ�˴�ӡ��ʽ�����룬���ӿսڵ�;
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

		//����һ�������Ŀսڵ㣬ʹ���ѳ�Ϊ��ȫ������;
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
	
	//��һ���ڵ�Ϊ��㣬����Сֵ;
	int findMin(TreapNode * node) const
	{
		if (node == NULL)
			return -1;
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node->data;
	}
	//��һ���ڵ�Ϊ��㣬�����ֵ;
	int findMax(TreapNode * node) const
	{
		if (node == NULL)
			return -1;
		while (node->rightChild != NULL)
			node = node->rightChild;
		return node->data;
	}
	//��һ���ڵ�Ϊ��㣬����ĳ��ֵ;
	TreapNode * findNode(TreapNode * node, const int data)
	{
		TreapNode * result = NULL;
		while (node != NULL)
		{
			if (node->data < data)
				node = node->rightChild;
			else if (node->data > data)
				node = node->leftChild;
			else
			{
				result = node;
				break;
			}
		}
		return result;
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
	//�����ӡ����;
	void printHorizontal()
	{
		cout<<"�����ӡ����ʽΪ���ڵ�ֵ/����Ȩ������"<<endl;
		print(this->root, 0);
	}
	//������Сֵ;
	int findMin()
	{
		return findMin(this->root);
	}
	//�������ֵ;
	int findMax()
	{
		return findMax(this->root);
	}
	//���ظ��ڵ��ǰ���ڵ�;
	int rootPred()
	{
		if (this->root == NULL)
			return -1;
		return findMax(this->root->leftChild);
	}
	//���ظ��ڵ�ĺ�̽ڵ�;
	int rootSucc()
	{
		if (this->root == NULL)
			return -1;
		return findMin(this->root->rightChild);
	}
	//����ĳ���ڵ�;
	void findNode(const int data)
	{
		TreapNode * node = this->findNode(this->root, data);
		if (node == NULL)
			cout << "�Ҳ����ڵ㣡" << endl;
		else
			cout << "�ڵ�ֵ��" << node->data << "���ڵ�����Ȩ��" << node->priority << endl;
	}
	//����ĳ���ڵ�;
	bool updateNode(const int oldData, const int newData)
	{
		TreapNode * node = this->findNode(this->root, oldData);
		if (node == NULL)
		{
			cout << "�Ҳ����ڵ㣡" << endl;
			return false;
		}
		else
		{
			int priority = node->priority;
			this->deleteNode(oldData);
			this->insertNode(this->root, newData, priority);
			return true;
		}
	}
	//�����ӡ����;
	void printVertical()
	{
		cout<<"�����ӡ��ֻ��ӡ�ڵ�ֵ������Ȩ���պ����ӡ����"<<endl;
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