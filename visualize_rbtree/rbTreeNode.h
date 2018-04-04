#pragma once
#ifndef rbTreeNode_
#define rbTreeNode_

#include "Color.h"

using namespace std;

template <class K,class E>
struct rbTreeNode {
public:
	pair<K, E> element;	//查找元素
	Color nodeColor;	//节点颜色

	pair<int, int> position;

	rbTreeNode<K, E>* leftChild, *rightChild;

	rbTreeNode() { leftChild = rightChild = NULL; nodeColor = red; }
	rbTreeNode(pair<K, E> & thePair) { leftChild = rightChild = NULL; element = thePair; }
	rbTreeNode(rbTreeNode<K, E>& theNode) {
		element = theNode.element;
		nodeColor = theNode.nodeColor;
	}
	rbTreeNode(Color theColor) { 
		leftChild = rightChild = NULL;
		nodeColor = theColor;
	}
	rbTreeNode(pair<K,E> & thePair,rbTreeNode<K, E> *leftChild, rbTreeNode<K, E> *rightChild, Color theColor) {
		element = thePair;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
		nodeColor = theColor;
	}
};

#endif