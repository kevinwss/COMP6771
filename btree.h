/**
* The btree is a linked structure which operates much like
* a binary search tree, save the fact that multiple client
* elements are stored in a single node.  Whereas a single element
* would partition the tree into two ordered subtrees, a node
* that stores m client elements partition the tree
* into m + 1 sorted subtrees.
*/

//By z5082727 ShaoshenWang
#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <queue>

// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template<typename T> class btree;
template<typename T> std::ostream& operator<<(std::ostream&, const btree<T>&);
//template<typename T> std::stringstream& operator<<(std::stringstream&, const btree<T>&);


template <typename T>
class btree {
public:
	
	friend class btree_iterator<T> ;
	friend class const_btree_iterator<T>;

	typedef btree_iterator<T> iterator;
	typedef const_btree_iterator<T> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	/** Hmm, need some iterator typedefs here... friends? **/

	/**
	* Constructs an empty btree.  Note that
	* the elements stored in your btree must
	* have a well-defined zero-arg constructor,
	* copy constructor, operator=, and destructor.
	* The elements must also know how to order themselves
	* relative to each other by implementing operator<
	* and operator==. (These are already implemented on
	* behalf of all built-ins: ints, doubles, strings, etc.)
	*
	* @param maxNodeElems the maximum number of elements
	*        that can be stored in each B-Tree node
	*/
	btree(size_t maxNodeElems = 40);

	/**
	* The copy constructor and  assignment operator.
	* They allow us to pass around B-Trees by value.
	* Although these operations are likely to be expensive
	* they make for an interesting programming exercise.
	* Implement these operations using value semantics and
	* make sure they do not leak memory.
	*/

	/**
	* Copy constructor
	* Creates a new B-Tree as a copy of original.
	*
	* @param original a const lvalue reference to a B-Tree object
	*/

	

	btree(const btree<T>& original);

	/**
	* Move constructor
	* Creates a new B-Tree by "stealing" from original.
	*
	* @param original an rvalue reference to a B-Tree object
	*/
	btree(btree<T>&& original);


	/**
	* Copy assignment
	* Replaces the contents of this object with a copy of rhs.
	*
	* @param rhs a const lvalue reference to a B-Tree object
	*/
	btree<T>& operator=(const btree<T>& rhs);

	/**
	* Move assignment
	* Replaces the contents of this object with the "stolen"
	* contents of original.
	*
	* @param rhs a const reference to a B-Tree object
	*/
	btree<T>& operator=(btree<T>&& rhs);

	/**
	* Puts a breadth-first traversal of the B-Tree onto the output
	* stream os. Elements must, in turn, support the output operator.
	* Elements are separated by space. Should not output any newlines.
	*
	* @param os a reference to a C++ output stream
	* @param tree a const reference to a B-Tree object
	* @return a reference to os
	*/
	friend std::ostream& operator<<<T>(std::ostream& os, const btree<T>& tree);
	//friend std::stringstream& operator<<<T>(std::stringstream& os, const btree<T>& tree);

	iterator begin() const;
	iterator end() const;
	reverse_iterator rbegin() const;
	reverse_iterator rend() const;

	const_iterator cbegin() const;
	const_iterator cend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	/**
	* Returns an iterator to the matching element, or whatever
	* the non-const end() returns if the element could
	* not be found.
	*
	* @param elem the client element we are trying to match.  The elem,
	*        if an instance of a true class, relies on the operator< and
	*        and operator== methods to compare elem to elements already
	*        in the btree.  You must ensure that your class implements
	*        these things, else code making use of btree<T>::find will
	*        not compile.
	* @return an iterator to the matching element, or whatever the
	*         non-const end() returns if no such match was ever found.
	*/

	iterator find(const T& elem);

	/**
	* Identical in functionality to the non-const version of find,
	* save the fact that what's pointed to by the returned iterator
	* is deemed as const and immutable.
	*
	* @param elem the client element we are trying to match.
	* @return an iterator to the matching element, or whatever the
	*         const end() returns if no such match was ever found.
	*/
	const_iterator find(const T& elem) const;

	/**
	* Operation which inserts the specified element
	* into the btree if a matching element isn't already
	* present.  In the event where the element truly needs
	* to be inserted, the size of the btree is effectively
	* increases by one, and the pair that gets returned contains
	* an iterator to the inserted element and true in its first and
	* second fields.
	*
	* If a matching element already exists in the btree, nothing
	* is added at all, and the size of the btree stays the same.  The
	* returned pair still returns an iterator to the matching element, but
	* the second field of the returned pair will store false.  This
	* second value can be checked to after an insertion to decide whether
	* or not the btree got bigger.
	* 
	* The insert method makes use of T's zero-arg constructor and
	* operator= method, and if these things aren't available,
	* then the call to btree<T>::insert will not compile.  The implementation
	* also makes use of the class's operator== and operator< as well.
	*
	* @param elem the element to be inserted.
	* @return a pair whose first field is an iterator positioned at
	*         the matching element in the btree, and whose second field
	*         stores true if and only if the element needed to be added
	*         because no matching element was there prior to the insert call.
	*/

	std::pair<iterator, bool> insert(const T& elem);
	/**
	* Disposes of all internal resources, which includes
	* the disposal of any client objects previously
	* inserted using the insert operation.
	* Check that your implementation does not leak memory!
	*/

	
	~btree() {};

//private:
	// The details of your implementation go here
	struct Node{
		
		Node(int p_pos,int maxElem = 40,Node *p = nullptr) {
			elem = new T[maxElem];
			parent = p;
			desendants = new Node*[maxElem + 1]();
			max_size = maxElem;
			occupied_size = 0;
			parent_pos = p_pos;
			}
		
		~Node(){
			for(int i =0;i<max_size;i++){
			if(desendants[i]!= nullptr)
				delete desendants[i];
		}
			delete [] elem;
			delete [] desendants;
		}

		T *elem;
		Node *parent;
		Node **desendants;
		int max_size;
		int parent_pos;
		int occupied_size;
	};

	Node *root,*head,*tail;
	size_t maxNodeElems;

};



template<typename T>
btree<T>::btree(size_t maxNodeElems) :
	maxNodeElems(maxNodeElems){
	Node* parent = NULL;
	Node* newnode = new Node(0, int(maxNodeElems),parent);

	root = newnode;
	head = newnode;
	tail = newnode;
}

//Copy construction

template<typename T>
btree<T>::btree(const btree<T>& rhs) {

	root = new Node(0, rhs.maxNodeElems,NULL);
	head= root;
	tail = root;

	maxNodeElems = rhs.maxNodeElems;

	std::queue<typename btree<T>::Node*> nodes_queue;
	nodes_queue.push(rhs.root);

	while (nodes_queue.size() != 0) {
	
		typename btree<T>::Node* node = nodes_queue.front();
		nodes_queue.pop();

		for (int i = 0; i < node->occupied_size; i++) 
		{ insert(node->elem[i]); 

			}
		for (int i = 0; i < node->occupied_size + 1; i++) { 
			if (node->desendants[i] != nullptr) { nodes_queue.push(node->desendants[i]); }
		}
	}
}

//Move construction

template<typename T>
btree<T>::btree(btree<T>&& rhs) {

	root = new Node(0, rhs.maxNodeElems,NULL);
	head= root;
	tail = root;

	maxNodeElems = rhs.maxNodeElems;

	std::queue<typename btree<T>::Node*> nodes_queue;
	nodes_queue.push(rhs.root);

	while (nodes_queue.size() != 0) {
	
		typename btree<T>::Node* node = nodes_queue.front();
		nodes_queue.pop();

		for (int i = 0; i < node->occupied_size; i++) 
		{ insert(node->elem[i]); 

			}
		for (int i = 0; i < node->occupied_size + 1; i++) { 
			if (node->desendants[i] != nullptr) { nodes_queue.push(node->desendants[i]); }
		}
	}

	rhs.root = new Node(0,maxNodeElems,NULL);
	rhs.head = rhs.root;
	rhs.tail = rhs.root;
}

//Copy Assignment
template<typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs) {

	root = new Node(0, rhs.maxNodeElems,NULL);
	head= root;
	tail = root;
	maxNodeElems = rhs.maxNodeElems;
	{
		std::queue<typename btree<T>::Node*> nodes_queue;
		nodes_queue.push(rhs.root);
		while (nodes_queue.size() != 0) {
			typename btree<T>::Node* node = nodes_queue.front();
			nodes_queue.pop();
			for (int i = 0; i < node->occupied_size; i++)
			{
				insert(node->elem[i]);
			}
			for (int i = 0; i < node->occupied_size + 1; i++) {
				if (node->desendants[i] != nullptr) { nodes_queue.push(node->desendants[i]); }
			}
		}
	}
	return *this;
}

//Move Assignment
template<typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) {
	root = new Node(0, rhs.maxNodeElems,NULL);
	head= root;
	tail = root;
	maxNodeElems = rhs.maxNodeElems;
	{
		std::queue<typename btree<T>::Node*> nodes_queue;
		nodes_queue.push(rhs.root);
		while (nodes_queue.size() != 0) {
			typename btree<T>::Node* node = nodes_queue.front();
			nodes_queue.pop();
			for (int i = 0; i < node->occupied_size; i++)
			{
				insert(node->elem[i]);
			}
			for (int i = 0; i < node->occupied_size + 1; i++) {
				if (node->desendants[i] != nullptr) { nodes_queue.push(node->desendants[i]); }
			}
		}
	}
	rhs.root = new Node(0,maxNodeElems,NULL);
	rhs.head = rhs.root;
	rhs.tail = rhs.root;
	return *this;
}


template<typename T> std::ostream&
operator<<(std::ostream& os, const btree<T>& tree) {
	std::vector<typename btree<T>::Node*> current_layer;
	std::vector<typename btree<T>::Node*> next_layer;
	if (tree.root==nullptr){return os;} 
	current_layer.push_back(tree.root);
	bool first = true;

	while (!current_layer.empty()) {
		for (auto node : current_layer) {
			for (int i = 0; i < node->occupied_size; i++) {
				if (first){os << node->elem[i];} //Add space after first one
				else{
				os <<" "<<node->elem[i];
					}
				first = false;

				if (node->desendants[i] != nullptr) {
					next_layer.push_back(node->desendants[i]);
				}
			}
			if (node->desendants[node->occupied_size] != nullptr) { next_layer.push_back(node->desendants[node->occupied_size]); }//boundary case
		}
		
		current_layer = next_layer;
		next_layer.clear();
		
	}
	return os;
}


//custom iterators


template<typename T> typename btree<T>::iterator
btree<T>::begin() const{

	return iterator(head, this, 0);
}


template<typename T> typename btree<T>::iterator
btree<T>::end() const{

	return iterator(tail, this, tail->occupied_size);
}

template<typename T> typename btree<T>::const_iterator
btree<T>::cbegin() const {
	return const_iterator(head, this, 0);
}


template<typename T> typename btree<T>::const_iterator
btree<T>::cend()  const{
	return const_iterator(tail, this, tail->occupied_size);
}


template<typename T> typename btree<T>::reverse_iterator
btree<T>::rbegin() const {
	return reverse_iterator(end());
}

template<typename T> typename btree<T>::reverse_iterator
btree<T>::rend() const {
	return reverse_iterator(begin());
}


template<typename T> typename btree<T>::const_reverse_iterator
btree<T>::crbegin() const {
	return const_reverse_iterator(end());
}

template<typename T> typename btree<T>::const_reverse_iterator
btree<T>::crend() const {
	return const_reverse_iterator(begin());
}


//**********insert**********

template<typename T>
std::pair<btree_iterator<T>, bool> btree<T>::insert(const T& elem) {
	
	unsigned max_size = maxNodeElems;
	auto node = root;

	while (true){
		if (node->occupied_size == 0) {  //add at first
			node->elem[0] = elem;
			node->occupied_size++;
			return std::make_pair(iterator(node, this,0), true);
		}
		if (node->occupied_size < node->max_size) { //current node is not full yet
			for (int i = 0; i < node->occupied_size; i++) {//find position

				if (elem == node->elem[i]) { //value already exists
					return std::make_pair(iterator(node, this, i), false);
				}
				if (elem < node->elem[i]) {// less than current value, add in the middle
					for (int j = node->occupied_size; j > i; j--) { node->elem[j] = node->elem[j - 1]; }
					node->elem[i] = elem;
					node->occupied_size++;
					return std::make_pair(iterator(node, this, i), true);
				}
				if (elem > node->elem[i] && i == node->occupied_size - 1) { //add at the end
					node->elem[i + 1] = elem;
					node->occupied_size++;
					return std::make_pair(iterator(node, this, i+1), true);
				}
			}
		}
		else { //current node is already full
			for (int i = 0; i < node->occupied_size; i++) {
				if (elem == node->elem[i]) { //value already exists
					return std::make_pair(iterator(node, this, i), false);
				}
				if (elem < node->elem[i] || (elem > node->elem[i] && i == node->occupied_size - 1)) { // insert in middle or at last
					if (elem > node->elem[i] && i == node->occupied_size - 1) { 
						i = i + 1; //position at last
					}
					if (node->desendants[i] == nullptr) { // i = insert position
						Node* newnode = new Node(i, max_size, node);
						//Perserve two pointers
						if (i == 0 && head == node) { head = newnode;}
						if (i == node->max_size && tail == node) { tail = newnode; }

						node->desendants[i] = newnode;
						node = node->desendants[i]; //descend down
					}
					else { node = node->desendants[i]; }
					break;
				}
			}
		}

	}

}


//***********find*************

template<typename T>
btree_iterator<T> btree<T>::find(const T& elem) {
	auto node = root;

	while (true) {
		for (int i = 0; i < node->occupied_size; i++) {
			if (elem == node->elem[i]) { //found in this node

				return iterator(node, this, i);
			}
			if (elem < node->elem[i]) { //find in desendants
				if (node->desendants[i] == nullptr) { return end(); }
				else {
					node = node->desendants[i];
					break;
				}
			}

			if (i == node->occupied_size - 1 && elem > node->elem[i]) {//desendants always have one more
				i++;
				if (node->desendants[i] == nullptr) { return end(); }
				else {
					node = node->desendants[i];
					break;

				}
			}

		}
	}
}



template<typename T>
const_btree_iterator<T> btree<T>::find(const T& elem) const {
	auto node = root;
	while (true) {
		for (int i = 0; i < node->occupied_size; i++) {
			if (elem == node->elem[i]) { //found

				return const_iterator(node, this, i);
			}
			if (elem < node->elem[i]) { //find in desendants
				if (node->desendants[i] == nullptr) { return cend(); }
				else {
					node = node->desendants[i];
					break;
				}
			}

			if (i == node->occupied_size - 1 && elem > node->elem[i]) {//last
				i++;
				if (node->desendants[i] == nullptr) { return cend(); }
				else {
					node = node->desendants[i];
					break;
				}
			}
		}
	}
}

#endif
#pragma once
