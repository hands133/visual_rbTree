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
	void initialize(const int* theKey, const string* theElement,int n);	//初始化操作，用插入方式完成
	void insert(pair<int, string>&);	//插入操作
	void erase(const int&);	//删除操作
	int size() const { return treeSize; }
	string find(const int&) const;	//查找

	void preOrder() { pre(root); cout << endl; }	//前序遍历
	void inOrder() { in(root); cout << endl; }	//中序遍历
	void postOrder() { post(root); cout << endl; }	//后序遍历
	void levelOrder() { level(root); cout << endl; };	//层次遍历
	int treeHight() { return height(root); }
	void clear() { CLEAR(root); root = NIL; }

	void distance_To_root();
	rbTreeNode<int, string>* succ(rbTreeNode<int, string>* t) const;	//查找中序遍历中节点的下一个节点
	void calPosition();	//计算节点在树中的位置

	rbTreeNode<int, string>* findParent(rbTreeNode<int, string> *t) const;

private:

	int treeSize;	//红黑树的节点个数
	rbTreeNode<int, string>* root;	//红黑树树根
	rbTreeNode<int, string>* NIL;	//外部节点

	void dispose(rbTreeNode<int, string>* t) {
		//析构函数的删除函数
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
	//以节点t为树根进行的左旋、右旋操作
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

string linkedrbTree::find(const int& theKey) const {//查找元素
	string info;
	if (root == NIL)
		info = "There's no element in the red-black tree.";

	rbTreeNode<int,string>* iter = root;
	while (iter != NIL && iter->element.first != theKey) {
		if (theKey < iter->element.first)	iter = iter->leftChild;	//关键字小于当前节点元素关键字，迭代器指向左孩子
		else iter = iter->rightChild;	//迭代器指向右孩子
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
	//只对grandParent非NIL进行判断
	//XXr
	if (grandParent == NIL)	return 0;
	if (uncle->nodeColor == red) {
		if (iter->nodeColor == red && parent->nodeColor == red && grandParent->nodeColor == black)
			return 1;
		else return 0;
	}
	else {
		//uncle节点为黑色
		//LLb:父节点是祖父节点的左孩子，要插入的节点是父亲的左节点
		if (parent == grandParent->leftChild && iter == parent->leftChild && iter->nodeColor == red && parent->nodeColor == red)
			return 2;
		//LRb:父节点是祖父节点的左孩子，要插入的节点是父亲的右节点
		else if (parent == grandParent->leftChild && iter == parent->rightChild && iter->nodeColor == red && parent->nodeColor == red)
			return 3;
		//RLb:父节点是祖父节点的右孩子，要插入的节点是父亲的左节点
		else if (parent == grandParent->rightChild && iter == parent->leftChild && iter->nodeColor == red && parent->nodeColor == red)
			return 4;
		//RRb:父节点是祖父节点的右孩子，要插入的节点是父亲的右节点
		else if (parent == grandParent->rightChild && iter == parent->rightChild && iter->nodeColor == red && parent->nodeColor == red)
			return 5;
		else
			return 0;
	}
}

void linkedrbTree::insert(pair<int,string>& thePair) {
	int operation = 0;	//要进行操作的代号
	//插入操作
	if (treeSize == 0)
		root = new rbTreeNode<int,string>(thePair, NIL, NIL, black);
	else {
		rbTreeNode<int,string>* insertNode = new rbTreeNode<int,string>(thePair, NIL, NIL, red);
		//树不为空，查找要插入节点的父节点
		rbTreeNode<int,string>* parent, *iter;
		iter = root;
		parent = root;
		while (iter != NIL && iter->element.first != thePair.first) {
			parent = iter;
			if (thePair.first < iter->element.first)	iter = iter->leftChild;
			else iter = iter->rightChild;
		}
		//如果发现重复，覆盖thePair.second
		if (iter->element.first == thePair.first && iter != NIL) {
			iter->element.second = thePair.second;
			return;
		}
		(thePair.first < parent->element.first) ? (parent->leftChild = insertNode) : (parent->rightChild = insertNode);
		(thePair.first < parent->element.first) ? (iter = parent->leftChild) : (iter = parent->rightChild);
		if (parent->nodeColor == black) { treeSize++; return; }
		else{
			//父节点为红色
			rbTreeNode<int,string>* uncle, *grandParent;
			grandParent = findParent(parent);
			uncle = (parent == grandParent->leftChild) ? (grandParent->rightChild) : (grandParent->leftChild);
			//进行插入类型判断
			if (uncle->nodeColor == red) {
				//XXr，进行颜色交换
				while (insertionType(iter,parent,uncle,grandParent) == 1) {
					//当grandParent是根节点或者插入的节点不会破坏树的平衡时结束
					if (grandParent != root)
						grandParent->nodeColor = red;
					else {
						parent->nodeColor = black;
						uncle->nodeColor = black;
						break;
					}
					parent->nodeColor = black;
					uncle->nodeColor = black;
					//iter指向grandParent
					iter = grandParent;
					parent = findParent(iter);
					grandParent = findParent(parent);
					uncle = (parent == grandParent->leftChild) ? (grandParent->rightChild) : (grandParent->leftChild);
				}
				operation = insertionType(iter, parent, uncle, grandParent);
			}
			else
				//uncle为黑色，考虑LLb,LRb,RRb,RLb
				operation = insertionType(iter, parent, uncle, grandParent);

			switch (operation) {
			case 0://不破坏树的平衡
				break;
			case 1://XXr,已经实现
				break;
			case 2://LLb
				//右旋grandPparent
				rotateRight(grandParent);
				parent->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 3://LRb
				//左旋parent
				rotateLeft(parent);
				//右旋grandParent
				rotateRight(grandParent);
				iter->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 4://RLb	情况与LRb对称
				//右旋parent
				rotateRight(parent);
				//左旋grandParent
				rotateLeft(grandParent);
				iter->nodeColor = black;
				grandParent->nodeColor = red;
				break;
			case 5://RRb	情况与LLb对称
				//左旋grandParent
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
		//查找要删除的元素
		if (theKey < node->element.first)
			node = node->leftChild;
		else
			node = node->rightChild;
	}
	if (node == NIL)
		return;
	//删除节点
	rbTreeNode<int, string>* child;
	Color color;
	if (node->leftChild != NIL && node->rightChild != NIL) {
		rbTreeNode<int, string>*replace = node->rightChild;
		while (replace->leftChild != NIL)
			replace = replace->leftChild;
		//存储节点信息
		child = replace->rightChild;
		parent = findParent(replace);
		color = replace->nodeColor;
		if (findParent(node) != NIL) {
			//要删除的节点不是根节点
			if (node == findParent(node)->leftChild)
				findParent(node)->leftChild = replace;
			else
				findParent(node)->rightChild = replace;
		}
		else  //要删除的节点是根节点
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
		else {//对称情况，node是parent 的右孩子
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
	//查找当前节点的父节点
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
	//节点左旋
	if (t == NIL || t->rightChild == NIL)	//当节点为空或者右孩子为空时，节点不需要左旋
		return;
	rbTreeNode<int,string>* parent = findParent(t);
	rbTreeNode<int,string>* right = t->rightChild;
	rbTreeNode<int,string>* exchange = right->leftChild;
	if (t == root)
		root = right;
	//判断t是parent的哪一个孩子，并将对应的指针指向t的右孩子
	else
		(t == parent->leftChild) ? (parent->leftChild = right) : (parent->rightChild = right);
	t->rightChild = exchange;	//节点的右孩子指向节点右孩子的左孩子
	right->leftChild = t;	//t节点之前的右孩子指向t
}

void linkedrbTree::rotateRight(rbTreeNode<int,string> *t) {
	//节点右旋
	if (t == NIL || t->leftChild == NIL)	//当节点为空或者左孩子为空时，节点不需要右旋
		return;
	rbTreeNode<int,string>* parent = findParent(t);
	rbTreeNode<int,string>* left = t->leftChild;
	rbTreeNode<int,string>* exchange = left->rightChild;
	if (t == root)
		root = left;
	//判断t是parent的哪一个孩子，并将对应的指针指向t的左孩子
	else
		(t == parent->leftChild) ? (parent->leftChild = left) : (parent->rightChild = left);
	t->leftChild = exchange;	//t节点的左孩子指向t左孩子的右孩子
	left->rightChild = t;	//t节点原先的左孩子指向t
}

void linkedrbTree::level(rbTreeNode<int, string> *t) const {
	//层次遍历
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
	//层次遍历求每一个节点到根节点的距离
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
	//t存在右子树，返回右子树中最左边的节点
	if (t->rightChild != NIL) {
		nextNode = t->rightChild;
		while (nextNode->leftChild != NIL)
			nextNode = nextNode->leftChild;
	}
	else if (t->rightChild == NIL) {
		//t没有右子树，向上找到父节点，使得t是父节点的左节点
		//若不是，就继续向上寻找
		nextNode = findParent(t);
		while (nextNode != NIL && t == nextNode->rightChild) {
			t = nextNode;
			nextNode = findParent(nextNode);
		}
	}
	return nextNode;
}

void linkedrbTree::calPosition() {
	//调用succ()函数计算节点t在中序遍历中的位置
	//计算垂直位置
	this->distance_To_root();
	//计算水平距离
	int xpos = 0;
	rbTreeNode<int,string>* iter = root;
	//找到中序遍历的第一个节点
	while (iter->leftChild != NIL)
		iter = iter->leftChild;
	//调用succ()计算横坐标
	while (iter != NIL) {
		iter->position.first = xpos++;
		iter = succ(iter);
	}
}

#endif