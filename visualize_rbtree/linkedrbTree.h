#ifndef linkedrbTree_
#define linkedrbTree_

#include <iostream>
#include <utility>

#include "rbTree.h"
#include "rbTreeNode.h"
#include "myExceptions.h"
#include "Color.h"
#include "arrayQueue.h"

using namespace std;

class linkedrbTree : public rbTree<int,string>
{
public:

	friend class draw;

	linkedrbTree() {
		root = NIL; 
		treeSize = 0; 
		NIL = new rbTreeNode<int, string>(black);
	};
	~linkedrbTree() { dispose(root); root = NULL; treeSize = 0; }
	rbTreeNode<int, string>* getroot() const {
		return root;
	}
	rbTreeNode<int, string>* getNil() const { return NIL; }
	void initialize(const int* theKey, const string* theElement,int n);	//��ʼ���������ò��뷽ʽ���
	void insert(pair<int, string>&);	//�������
	void erase(const int&);	//ɾ������
	int size() const { return treeSize; }
	string find(const int&) const;	//����

	void preOrder() { pre(root); cout << endl; }	//ǰ�����
	void inOrder() { in(root); cout << endl; }	//�������
	void postOrder() { post(root); cout << endl; }	//�������
	void levelOrder() { level(root); cout << endl; };	//��α���
	int treeHight() { return height(root); }
	void clear() { CLEAR(root); root = NIL; }

	void distance_To_root();
	rbTreeNode<int, string>* succ(rbTreeNode<int, string>* t) const;	//������������нڵ����һ���ڵ�
	void calPosition();	//����ڵ������е�λ��

	rbTreeNode<int, string>* findParent(rbTreeNode<int, string> *t) const;

private:

	int treeSize;	//������Ľڵ����
	rbTreeNode<int, string>* root;	//���������
	rbTreeNode<int, string>* NIL;	//�ⲿ�ڵ�

	void dispose(rbTreeNode<int, string>* t) {
		//����������ɾ������
		if (t != NULL) {
			if(t->leftChild != NULL)
				dispose(t->leftChild);
			if(t->rightChild != NULL)
				dispose(t->rightChild);
			delete t;
		}
	}
	void visit(rbTreeNode<int, string>* t) const {
		cout << t->element.first << " " << t->element.second << "\t";
	}
	void pre(rbTreeNode<int, string>* t)const {
		if (t != NIL) {
			visit(t);
			pre(t->leftChild);
			pre(t->rightChild);
		}
	}
	void in(rbTreeNode<int, string>* t) const {
		if (t != NIL) {
			in(t->leftChild);
			visit(t);
			in(t->rightChild);
		}
	}
	void post(rbTreeNode<int, string>* t) const {
		if (t != NIL) {
			post(t->leftChild);
			post(t->rightChild);
			visit(t);
		}
	}
	void level(rbTreeNode<int, string >* t) const;
	void CLEAR(rbTreeNode<int, string>* t) {
		if (t == NIL)
			return;
		if (t->leftChild != NIL)
			CLEAR(t->leftChild);
		if (t->rightChild != NIL)
			CLEAR(t->rightChild);
		t = NIL;
	}
	//�Խڵ�tΪ�������е���������������
	void rotateLeft(rbTreeNode<int, string>* t);
	void rotateRight(rbTreeNode<int, string>* t);

	int calNodes(rbTreeNode<int, string>* t) {
		if (t == NIL)
			return 0;
		return calNodes(t->leftChild) + calNodes(t->rightChild) + 1;
	}

	void exchangeColor(rbTreeNode<int, string>* node1, rbTreeNode<int, string>* node2) {
		Color ex = node1->nodeColor;
		node1->nodeColor = node2->nodeColor;
		node2->nodeColor = ex;
	}
	int redsons(rbTreeNode<int, string>* node) {
		if (node == NIL)	return 0;
		else if (node->nodeColor == red)	return 1;
		return redsons(node->leftChild) + redsons(node->rightChild);
	}
	int height(rbTreeNode<int,string>* node) {
		if (node == NIL)	return 0;
		int heightOfLeft = 0;
		int heightOfRight = 0;
		if (node->leftChild != NIL)
			heightOfLeft = height(node->leftChild);
		if (node->rightChild != NIL)
			heightOfRight = height(node->rightChild);
		return (heightOfLeft > heightOfRight) ? (heightOfLeft + 1) : (heightOfRight + 1);
	}
	int insertionType(rbTreeNode<int,string>* iter, rbTreeNode<int,string>* parent, rbTreeNode<int,string>* uncle, rbTreeNode<int,string>* grandParent);

	void fixUp_Delete(rbTreeNode<int, string> *, rbTreeNode<int, string> *);
};

string linkedrbTree::find(const int& theKey) const {//����Ԫ��
	string info;
	if (root == NIL)
		info = "There's no element in the red-black tree.";

	rbTreeNode<int,string>* iter = root;
	while (iter != NIL && iter->element.first != theKey) {
		if (theKey < iter->element.first)	iter = iter->leftChild;	//�ؼ���С�ڵ�ǰ�ڵ�Ԫ�عؼ��֣�������ָ������
		else iter = iter->rightChild;	//������ָ���Һ���
	}
	if (iter == NIL)
		info = "The element doesn't exist!";
	else
		info = iter->element.second;
	return info;
}

void linkedrbTree::initialize(const int* theKey,const string* theElement,int n) {
	pair<int,string> insertion;
	for (int i = 0; i < n; i++) {
		insertion.first = theKey[i];
		insertion.second = theElement[i];
		this->insert(insertion);
	}
}

int linkedrbTree::insertionType(rbTreeNode<int,string>* iter, rbTreeNode<int,string>* parent, rbTreeNode<int,string>* uncle, rbTreeNode<int,string>* grandParent) {
	//ֻ��grandParent��NIL�����ж�
	//XXr
	if (grandParent == NIL)	return 0;
	if (uncle->nodeColor == red) {
		if (iter->nodeColor == red && parent->nodeColor == red && grandParent->nodeColor == black)
			return 1;
		else return 0;
	}
	else {
		//uncle�ڵ�Ϊ��ɫ
		//LLb:���ڵ����游�ڵ�����ӣ�Ҫ����Ľڵ��Ǹ��׵���ڵ�
		if (parent == grandParent->leftChild && iter == parent->leftChild && iter->nodeColor == red && parent->nodeColor == red)
			return 2;
		//LRb:���ڵ����游�ڵ�����ӣ�Ҫ����Ľڵ��Ǹ��׵��ҽڵ�
		else if (parent == grandParent->leftChild && iter == parent->rightChild && iter->nodeColor == red && parent->nodeColor == red)
			return 3;
		//RLb:���ڵ����游�ڵ���Һ��ӣ�Ҫ����Ľڵ��Ǹ��׵���ڵ�
		else if (parent == grandParent->rightChild && iter == parent->leftChild && iter->nodeColor == red && parent->nodeColor == red)
			return 4;
		//RRb:���ڵ����游�ڵ���Һ��ӣ�Ҫ����Ľڵ��Ǹ��׵��ҽڵ�
		else if (parent == grandParent->rightChild && iter == parent->rightChild && iter->nodeColor == red && parent->nodeColor == red)
			return 5;
		else
			return 0;
	}
}

void linkedrbTree::insert(pair<int,string>& thePair) {
	int operation = 0;	//Ҫ���в����Ĵ���
	//�������
	if (treeSize == 0)
		root = new rbTreeNode<int,string>(thePair, NIL, NIL, black);
	else {
		rbTreeNode<int,string>* insertNode = new rbTreeNode<int,string>(thePair, NIL, NIL, red);
		//����Ϊ�գ�����Ҫ����ڵ�ĸ��ڵ�
		rbTreeNode<int,string>* parent, *iter;
		iter = root;
		parent = root;
		while (iter != NIL && iter->element.first != thePair.first) {
			parent = iter;
			if (thePair.first < iter->element.first)	iter = iter->leftChild;
			else iter = iter->rightChild;
		}
		//��������ظ�������thePair.second
		if (iter->element.first == thePair.first && iter != NIL) {
			iter->element.second = thePair.second;
			return;
		}
		(thePair.first < parent->element.first) ? (parent->leftChild = insertNode) : (parent->rightChild = insertNode);
		(thePair.first < parent->element.first) ? (iter = parent->leftChild) : (iter = parent->rightChild);
		if (parent->nodeColor == black) { treeSize++; return; }
		else{
			//���ڵ�Ϊ��ɫ
			rbTreeNode<int,string>* uncle, *grandParent;
			grandParent = findParent(parent);
			uncle = (parent == grandParent->leftChild) ? (grandParent->rightChild) : (grandParent->leftChild);
			//���в��������ж�
			if (uncle->nodeColor == red) {
				//XXr��������ɫ����
				while (insertionType(iter,parent,uncle,grandParent) == 1) {
					//��grandParent�Ǹ��ڵ���߲���Ľڵ㲻���ƻ�����ƽ��ʱ����
					if (grandParent != root)
						grandParent->nodeColor = red;
					else {
						parent->nodeColor = black;
						uncle->nodeColor = black;
						break;
					}
					parent->nodeColor = black;
					uncle->nodeColor = black;
					//iterָ��grandParent
					iter = grandParent;
					parent = findParent(iter);
					grandParent = findParent(parent);
					uncle = (parent == grandParent->leftChild) ? (grandParent->rightChild) : (grandParent->leftChild);
				}
				operation = insertionType(iter, parent, uncle, grandParent);
			}
			else
				//uncleΪ��ɫ������LLb,LRb,RRb,RLb
				operation = insertionType(iter, parent, uncle, grandParent);

			switch (operation) {
			case 0://���ƻ�����ƽ��
				break;
			case 1://XXr,�Ѿ�ʵ��
				break;
			case 2://LLb
				//����grandPparent
				rotateRight(grandParent);
				parent->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 3://LRb
				//����parent
				rotateLeft(parent);
				//����grandParent
				rotateRight(grandParent);
				iter->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 4://RLb	�����LRb�Գ�
				//����parent
				rotateRight(parent);
				//����grandParent
				rotateLeft(grandParent);
				iter->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 5://RRb	�����LLb�Գ�
				//����grandParent
				rotateLeft(grandParent);
				parent->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			}
		}
	}
	treeSize = this->calNodes(root);
}

void linkedrbTree::erase(const int& theKey) {
	if (root == NIL || treeSize == 0)
		return;
	if (root->leftChild == NIL && root->rightChild == NIL && root->element.first == theKey) {
		root->leftChild = NULL;
		root->rightChild = NULL;
		delete root;
		root = NIL;
		treeSize--;
		return;
	}
	rbTreeNode<int, string>* node = root;
	rbTreeNode<int, string>*parent = NIL;
	while (node != NIL && node->element.first != theKey) {
		//����Ҫɾ����Ԫ��
		if (theKey < node->element.first)
			node = node->leftChild;
		else
			node = node->rightChild;
	}
	if (node == NIL)
		return;
	//ɾ���ڵ�
	rbTreeNode<int, string>* child;
	Color color;
	if (node->leftChild != NIL && node->rightChild != NIL) {
		rbTreeNode<int, string>*replace = node->rightChild;
		while (replace->leftChild != NIL)
			replace = replace->leftChild;
		//�洢�ڵ���Ϣ
		child = replace->rightChild;
		parent = findParent(replace);
		color = replace->nodeColor;
		if (findParent(node) != NIL) {
			//Ҫɾ���Ľڵ㲻�Ǹ��ڵ�
			if (node == findParent(node)->leftChild)
				findParent(node)->leftChild = replace;
			else
				findParent(node)->rightChild = replace;
		}
		else  //Ҫɾ���Ľڵ��Ǹ��ڵ�
			root = replace;
		if (parent == node)
			parent = replace;
		else {
			parent->leftChild = child;
			replace->rightChild = node->rightChild;
		}
		
		replace->nodeColor = node->nodeColor;
		replace->leftChild = node->leftChild;
		if (color == black)
			fixUp_Delete(child, parent);
		node = NIL;
		treeSize--;
		return;
	}
	if (node->leftChild != NIL)
		child = node->leftChild;
	else
		child = node->rightChild;
	parent = findParent(node);
	color = node->nodeColor;
	if (parent != NIL) {
		if (parent->leftChild == node)
			parent->leftChild = child;
		else
			parent->rightChild = child;
	}
	else
		root = child;
	if (color == black)
		fixUp_Delete(child, parent);
	node = NIL;
	treeSize--;
}

void linkedrbTree::fixUp_Delete(rbTreeNode<int, string>* node,rbTreeNode<int,string>* parent) {
	rbTreeNode<int, string>* other;
	while ((node == NIL || node->nodeColor == black) && node != root) {
		if (parent->leftChild == node) {
			other = parent->rightChild;
			if (other->nodeColor == red) {
				other->nodeColor = black;
				parent->nodeColor = red;
				rotateLeft(parent);
				other = parent->rightChild;
			}
			if ((other->leftChild == NIL || other->leftChild->nodeColor == black) &&
				(other->rightChild == NIL || other->rightChild->nodeColor == black)) {
				other->nodeColor = red;
				node = parent;
				parent = findParent(node);
			}
			else {
				if (other->rightChild == NIL || other->rightChild->nodeColor == black) {
					other->leftChild->nodeColor = black;
					other->nodeColor = red;
					rotateRight(other);
					other = parent->rightChild;
				}
				other->nodeColor = parent->nodeColor;
				parent->nodeColor = black;
				other->rightChild->nodeColor = black;
				rotateLeft(parent);
				node = root;
				break;
			}
		}
		else {//�Գ������node��parent ���Һ���
			other = parent->leftChild;
			if (other->nodeColor == red) {
				other->nodeColor = black;
				parent->nodeColor = red;
				rotateRight(parent);
				other = parent->leftChild;
			}
			if ((other->leftChild == NIL || other->leftChild->nodeColor == black) &&
				(other->rightChild == NIL || other->rightChild->nodeColor == black)) {
				other->nodeColor = red;
				node = parent;
				parent = findParent(node);
			}
			else {
				if (other->leftChild == NIL || other->leftChild->nodeColor == black) {
					other->rightChild->nodeColor = black;
					other->nodeColor = red;
					rotateLeft(other);
					other = parent->leftChild;
				}
				other->nodeColor = parent->nodeColor;
				parent->nodeColor = black;
				other->leftChild->nodeColor = black;
				rotateRight(parent);
				node = root;
				break;
			}
		}
	}
	if (node != NIL)
		node->nodeColor = black;
}

rbTreeNode<int,string>* linkedrbTree::findParent(rbTreeNode<int, string>* t) const {
	//���ҵ�ǰ�ڵ�ĸ��ڵ�
	if (t == this->root || t == NIL)	return NIL;
	rbTreeNode<int, string>* iter = root;
	rbTreeNode<int, string>* parent = root;
	while (iter != NIL && iter != t) {
		parent = iter;
		if (t->element.first < iter->element.first)	iter = iter->leftChild;
		else iter = iter->rightChild;
	}
	return parent;
}

void linkedrbTree::rotateLeft(rbTreeNode<int,string> *t) {
	//�ڵ�����
	if (t == NIL || t->rightChild == NIL)	//���ڵ�Ϊ�ջ����Һ���Ϊ��ʱ���ڵ㲻��Ҫ����
		return;
	rbTreeNode<int,string>* parent = findParent(t);
	rbTreeNode<int,string>* right = t->rightChild;
	rbTreeNode<int,string>* exchange = right->leftChild;
	if (t == root)
		root = right;
	//�ж�t��parent����һ�����ӣ�������Ӧ��ָ��ָ��t���Һ���
	else
		(t == parent->leftChild) ? (parent->leftChild = right) : (parent->rightChild = right);
	t->rightChild = exchange;	//�ڵ���Һ���ָ��ڵ��Һ��ӵ�����
	right->leftChild = t;	//t�ڵ�֮ǰ���Һ���ָ��t
}

void linkedrbTree::rotateRight(rbTreeNode<int,string> *t) {
	//�ڵ�����
	if (t == NIL || t->leftChild == NIL)	//���ڵ�Ϊ�ջ�������Ϊ��ʱ���ڵ㲻��Ҫ����
		return;
	rbTreeNode<int,string>* parent = findParent(t);
	rbTreeNode<int,string>* left = t->leftChild;
	rbTreeNode<int,string>* exchange = left->rightChild;
	if (t == root)
		root = left;
	//�ж�t��parent����һ�����ӣ�������Ӧ��ָ��ָ��t������
	else
		(t == parent->leftChild) ? (parent->leftChild = left) : (parent->rightChild = left);
	t->leftChild = exchange;	//t�ڵ������ָ��t���ӵ��Һ���
	left->rightChild = t;	//t�ڵ�ԭ�ȵ�����ָ��t
}

void linkedrbTree::level(rbTreeNode<int, string> *t) const {
	//��α���
	arrayQueue<rbTreeNode<int, string>*> q;
	while (t != NULL) {
		visit(t);
		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);
		try {
			t = q.front();
		}
		catch (queueEmpty) {
			return;
			}
		q.pop();
	}
}

void linkedrbTree::distance_To_root() {
	//��α�����ÿһ���ڵ㵽���ڵ�ľ���
	if (treeSize == 0)
		return;
	else if (treeSize == 1) {
		root->position.second = 1;
		return;
	}
	int levelOfNode = 1;
	arrayQueue<rbTreeNode<int,string>*> queue;
	rbTreeNode<int, string>* iter = root;
	queue.push(root);
	root->position.second = levelOfNode;
	queue.push(NIL);
	while (iter != NIL) {
		if (iter->leftChild != NIL)
			queue.push(iter->leftChild);
		if (iter->rightChild != NIL)
			queue.push(iter->rightChild);
		try {
			queue.pop();
			iter = queue.front();
		}
		catch (queueEmpty) {
			break;
		}
		if (iter == NIL) {
			levelOfNode++;
			queue.push(NIL);
			queue.pop();
			iter = queue.front();
			iter->position.second = levelOfNode;
		}
		else
			iter->position.second = levelOfNode;
	}
}

rbTreeNode<int,string>* linkedrbTree::succ(rbTreeNode<int,string> *t) const {
	rbTreeNode<int,string> *nextNode = NIL;
	//t����������������������������ߵĽڵ�
	if (t->rightChild != NIL) {
		nextNode = t->rightChild;
		while (nextNode->leftChild != NIL)
			nextNode = nextNode->leftChild;
	}
	else if (t->rightChild == NIL) {
		//tû���������������ҵ����ڵ㣬ʹ��t�Ǹ��ڵ����ڵ�
		//�����ǣ��ͼ�������Ѱ��
		nextNode = findParent(t);
		while (nextNode != NIL && t == nextNode->rightChild) {
			t = nextNode;
			nextNode = findParent(nextNode);
		}
	}
	return nextNode;
}

void linkedrbTree::calPosition() {
	//����succ()��������ڵ�t����������е�λ��
	//���㴹ֱλ��
	this->distance_To_root();
	//����ˮƽ����
	int xpos = 0;
	rbTreeNode<int,string>* iter = root;
	//�ҵ���������ĵ�һ���ڵ�
	while (iter->leftChild != NIL)
		iter = iter->leftChild;
	//����succ()���������
	while (iter != NIL) {
		iter->position.first = xpos++;
		iter = succ(iter);
	}
}

#endif