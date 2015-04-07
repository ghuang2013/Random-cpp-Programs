#ifndef BST_CPP
#define BST_CPP

#include "BST.h"

template <class T>
void BST<T>::addElement(const T& value)
{
	addElement(value, this->root);
}

template <class T>
void BST<T>::addElement(const T& value, std::shared_ptr<Node>& currentR)
{
	if (currentR == nullptr)
	{
		currentR = std::make_shared<Node>(value);
		return;
	}
	if (value <= currentR->getKey())
	{
		addElement(value, currentR->getLeft());
	}
	else if (value >= currentR->getKey())
	{
		addElement(value, currentR->getRight());
	}
}

template <class T>
void BST<T>::traverseBST(const std::shared_ptr<Node> &currentR, std::ostream& out)
{
	if (currentR == nullptr)
		return;
	traverseBST(currentR->getLeft(), out);
	out << currentR->getKey() << ' ';
	traverseBST(currentR->getRight(), out);
}

template <class T>
const std::shared_ptr<pNode<T>>& BST<T>::findElement(const T& value, const std::shared_ptr<Node> & currentR)
{
	if (currentR == nullptr)
		return currentR;
	if (currentR->getKey() == value)
		return currentR;
	else if (currentR->getKey() < value)
		return findElement(value, currentR->getRight()); //return currentR=keyNode
	else
		return findElement(value, currentR->getLeft());
}

template <class T>
void BST<T>::removeElement(const T& value)
{
	auto keyNode = const_cast<std::shared_ptr<pNode<T>>&>(findElement(value, this->root)); //find the node 
	removeElement(value, keyNode);
}

//this function is only called when there is a parent for sure
template <class T>
const std::shared_ptr<pNode<T>>& BST<T>::findParent(const T& value,
	const std::shared_ptr<Node> & keyR, const std::shared_ptr<Node> & parentR)
{
	if (parentR == nullptr)
		return parentR;
	if (parentR->getLeft() == keyR || parentR->getRight() == keyR)
		return parentR;
	else if (parentR->getKey() < keyR->getKey())
		return findParent(value, keyR, parentR->getRight());
	else
		return findParent(value, keyR, parentR->getLeft());
}

template <class T>
void BST<T>::removeElement(const T& value, std::shared_ptr<Node> &currentR)
{
	auto linking = [](std::shared_ptr<Node>& parentP, const std::shared_ptr<Node>& newNext,
		const T& key)
	{	(key > parentP->getKey()) ? parentP->setRight(newNext) : parentP->setLeft(newNext); };

	if (!currentR)
	{
		std::cerr << "No such node\n";
		return;
	}
	else if (currentR->getLeft() == nullptr && currentR->getRight() == nullptr) //if leaf node
	{
		auto parent = findParent(value, currentR, this->root);
		if (parent == nullptr) root = nullptr;
		else linking(parent, nullptr, currentR->getKey());
		currentR.reset();
	}
	else if (currentR->getLeft() == nullptr) //if it has only right child
	{
		if (currentR == this->root)
		{
			this->root = currentR->getRight();
			currentR.reset();
			return;
		}
		auto parent = findParent(value, currentR, this->root); //find the parent of this node
		linking(parent, currentR->getRight(), currentR->getKey());
		currentR.reset();
	}
	else if (currentR->getRight() == nullptr) //if it has only left child
	{
		if (currentR == this->root)
		{
			this->root = currentR->getLeft();
			currentR.reset();
			return;
		}
		auto parent = findParent(value, currentR, this->root); 
		linking(parent, currentR->getLeft(), currentR->getKey());
		currentR.reset();
	}
	else //most complicated case
	{
		auto max = findMax(currentR->getLeft()); //find max in the left subtree
		currentR->setKey(max->getKey());
		removeElement(max->getKey(), max);
	}
}

template<class T>
std::shared_ptr<pNode<T>> BST<T>::findMax(std::shared_ptr<Node> root)//allow copying
{
	while (root->getRight() != nullptr)
	{
		root = root->getRight();
	}
	return root;
}

#endif