#ifndef BST_H
#define BST_H

#include <memory>
#include <iostream>

template <class T>
class BST
{
private:
	class Node
	{
	public:
		Node() :Node(nullptr, nullptr, T{}) { }
		Node(const T& val, const std::shared_ptr<Node>& Left = nullptr,
			const std::shared_ptr<Node>& Right = nullptr) :val(val), pLeft{ Left }, pRight{ Right } { }
		void setLeft(const std::shared_ptr<Node>&);
		void setRight(const std::shared_ptr<Node>&);
		const std::shared_ptr<Node>& getLeft() const;
		const std::shared_ptr<Node>& getRight() const;
		std::shared_ptr<Node> &getLeft();  //allow changes
		std::shared_ptr<Node> &getRight();
		const T& getKey() const;
		void setKey(const T& val);
	private:
		std::shared_ptr<Node> pLeft;
		std::shared_ptr<Node> pRight;
		T val;
	};

	std::shared_ptr<Node> root = nullptr;
	static void traverseBST(const std::shared_ptr<Node> &currentR, std::ostream& out);
	static const std::shared_ptr<Node> &findElement(const T& value, const std::shared_ptr<Node> & currentR);
	static const std::shared_ptr<Node> &findParent(const T& value,
		const std::shared_ptr<Node> & keyR, const std::shared_ptr<Node> & parentR);
	void addElement(const T& value, std::shared_ptr<Node> &currentR);
	void removeElement(const T& value, std::shared_ptr<Node> &currentR);

public:
	template <class U>
	friend std::ostream& operator<< (std::ostream&, const BST<U>&);
	std::shared_ptr<Node> findMax(std::shared_ptr<Node> root);
	void addElement(const T& value);
	void removeElement(const T& value);
};

template <class T>
using pNode = typename BST<T>::Node;

template <class T>
const inline std::shared_ptr<pNode<T>>& BST<T>::Node::getLeft() const
{
	return pLeft;
}

template <class T>
inline std::shared_ptr<pNode<T>>& BST<T>::Node::getLeft()
{
	return pLeft;
}

template <class T>
inline const std::shared_ptr<pNode<T>>& BST<T>::Node::getRight() const
{
	return pRight;
}

template <class T>
inline std::shared_ptr<pNode<T>>& BST<T>::Node::getRight()
{
	return pRight;
}

template <class T>
inline void BST<T>::Node::setLeft(const std::shared_ptr<Node> &pLeft)
{
	this->pLeft = pLeft;
}

template <class T>
inline void BST<T>::Node::setRight(const std::shared_ptr<Node> &pRight)
{
	this->pRight = pRight;
}

template <class T>
inline const T& BST<T>::Node::getKey() const
{
	return val;
}

template <class T>
inline void BST<T>::Node::setKey(const T& val)
{
	this->val = val;
}


template <class T>
inline std::ostream& operator<< (std::ostream& out, const BST<T>& tree)
{
	tree.traverseBST(tree.root, out);
	out << std::endl;
	return out;
}

#include "BST.cpp"

#endif