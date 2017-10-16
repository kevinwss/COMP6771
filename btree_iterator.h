#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <vector>
//By z5082727 ShaoshenWang

/**
* You MUST implement the btree iterators as (an) external class(es) in this file.
* Failure to do so will result in a total mark of 0 for this deliverable.
**/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

template<typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template <typename T>
class btree_iterator {
public:
	typedef std::ptrdiff_t                   difference_type;
	typedef std::bidirectional_iterator_tag  iterator_category;
	typedef T                                value_type;
	typedef T* 								 pointer;
	typedef T&								 reference;

	friend class const_btree_iterator<T>;

	btree_iterator(typename btree<T>::Node* n,  const btree<T>* t,int idx);
	btree_iterator():
	index(0),
	node(NULL),
	tree(NULL){};

	reference operator * () const;
	pointer operator->() const{return &(operator*());}

	btree_iterator<T>& operator++();
    btree_iterator<T> operator++(int);
	btree_iterator<T>& operator--();
	btree_iterator<T> operator--(int);

	btree_iterator<T>& operator=(const btree_iterator& orinigal);
	btree_iterator<T>& operator=(const const_btree_iterator<T>& orinigal);

	bool operator==(const btree_iterator& orinigal) const;
	bool operator==(const const_btree_iterator<T>& orinigal) const;

	bool operator!=(const btree_iterator& original) const {return !operator ==(original);};
	bool operator!=(const const_btree_iterator<T>& original) const {return !operator ==(original);};



    //private:
	int index; //index of a node in tree
	typename btree<T>::Node* node;

 	const btree<T> *tree;


};



template <typename T>
btree_iterator<T>::btree_iterator(typename btree<T>::Node* n,const btree<T> *t,int idx) :
	index(idx),
	node(n),
	tree(t)
	{

}


template <typename T> typename btree_iterator<T>::reference
btree_iterator<T>::operator*() const {
	return node->elem[index];

}


template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++() {

	if (node->desendants[index+1] ==nullptr){ //No desendant node
		if (index+1<node->occupied_size || node == tree->tail){ // If in the last node or this node still have position
			index ++; //Same node	

		}else{ //ascend up
			while (node->parent!=nullptr && node->parent_pos == node->parent->max_size){ // next exceeds parent's end

				node = node->parent;
				index = node->parent_pos;// next elem
			}

			if (node->parent != nullptr) {
				index = node->parent_pos;
				node = node->parent;
			}
			else {
				index++;
			}
			//Consider end iterator
		}
		
	}else {
		//Find the next node des_down
		node = node->desendants[index+1];
		while(node->desendants[0]!=nullptr){node = node->desendants[0];}
		index = 0;
	}
	
	return *this;
}


template <typename T>
btree_iterator<T>& btree_iterator<T>::operator--() {

	if (node->desendants[index] == nullptr) {   // No desendant node
		if (index - 1>=0 || node == tree->head) { // If in the last node or this node still have position
			index--; //Same node
		}
		else { //ascend up
			while (node->parent != nullptr && node->parent_pos == 0) { // prev exceeds parent's start
																							
				node = node->parent;
				index = node->parent_pos - 1;// prev elem
			}
			// next not exceeds parent's node ,ascend once
			if (node->parent != nullptr) {
				index = node->parent_pos - 1;
				node = node->parent;
			}
			else {//root
				index--;
			}
			//Consider end iterator
		}
	}
	else {
		//Find the next node des_down
		node = node->desendants[index];
		while (node->desendants[tree->maxNodeElems] != nullptr) 
		{ node = node->desendants[tree->maxNodeElems]; }
		index = node->occupied_size-1;
	}
	return *this;
}

template <typename T>
btree_iterator<T> btree_iterator<T>::operator ++(int) {
	btree_iterator res = *this;
	operator ++();
	return res;

}

template <typename T>
btree_iterator<T> btree_iterator<T>::operator --(int) {
	btree_iterator res = *this;
	operator --();
	return res;

}



template <typename T>
btree_iterator<T>& btree_iterator<T>::operator=(const btree_iterator& original){
	index = original.index;
	node = original.node;
	tree = original.tree;
	return *this;
}

template <typename T>
btree_iterator<T>& btree_iterator<T>::operator=(const const_btree_iterator<T>& original){
	index = original.index;
	node = original.node;
	tree = original.tree;
	return *this;
}



template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator& original) const{

	return (tree == original.tree && node == original.node && index == original.index);

}


template <typename T>
bool btree_iterator<T>::operator==(const const_btree_iterator<T>& original) const{

	return (tree == original.tree && node == original.node && index == original.index);

}

//*******************const_btree_iterator**************



template <typename T>
class const_btree_iterator {
public:

	typedef std::ptrdiff_t                   difference_type;
	typedef std::bidirectional_iterator_tag  iterator_category;
	typedef T                                value_type;
	typedef const T* 						 pointer;
	typedef const T&						 reference;

	friend class btree_iterator<T>;

	const_btree_iterator(typename btree<T>::Node* n, const btree<T>* t, int idx);

	const_btree_iterator():
	index(0),
	node(NULL),
	tree(NULL){};
    
    const_btree_iterator(const btree_iterator<T>& rhs):
		index(rhs.index),node(rhs.node),tree(rhs.tree){}

	reference operator * () const;
	pointer operator->() const{return &(operator*());}

	const_btree_iterator<T>& operator++();
	const_btree_iterator<T> operator++(int);
	const_btree_iterator<T>& operator--();
	const_btree_iterator<T> operator--(int);

	const_btree_iterator<T>& operator=(const const_btree_iterator& original);
	const_btree_iterator<T>& operator=(const btree_iterator<T>& original);

	bool operator==(const const_btree_iterator& original) const;
	bool operator==(const btree_iterator<T>& original) const;

	bool operator!=(const const_btree_iterator& original) const{ return !operator == (original);}
	bool operator!=(const btree_iterator<T>& original) const{return !operator == (original);};



//private:
	int index; //index of a node in tree
	typename btree<T>::Node* node;

	const btree<T> *tree;
	

};



template <typename T>
const_btree_iterator<T>::const_btree_iterator(typename btree<T>::Node* n, const btree<T> *t,int idx) :
	index( idx ),
	node( n ),
	tree( t )
{
}



template <typename T> typename const_btree_iterator<T>::reference
const_btree_iterator<T>::operator*() const {
	return node->elem[index];

}


template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator++() {

	if (node->desendants[index + 1] == nullptr) { //No desendant node
		if (index + 1<node->occupied_size || node == tree->tail) { // If in the last node or this node still have position
			index++; //Same node
		}
		else { //ascend up
			while (node->parent != nullptr && node->parent_pos == node->parent->max_size) { // next exceeds parent's end
				node = node->parent;
				index = node->parent_pos;// next elem
			}
			// next not exceeds parent's node ,ascend once
			if (node->parent != nullptr) {
				index = node->parent_pos;
				node = node->parent;
			}
			else {
				index++;
			}
			//Consider end iterator
		}
	}
	else {
		//Find the next node des_down
		node = node->desendants[index + 1];

		while (node->desendants[0] != nullptr) { node = node->desendants[0]; }
		index = 0;
	}

	return *this;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator--() {
	
	if (node->desendants[index] == nullptr) {   // No desendant node
		if (index - 1 >= 0 || node == tree->head) { // If in the last node or this node still have position
			index--; //Same node
		}
		else { //ascend up
			while (node->parent != nullptr && node->parent_pos == 0) { // prev exceeds parent's start

				node = node->parent;
				index = node->parent_pos - 1;// prev elem
			}
			// next not exceeds parent's node ,ascend once
			if (node->parent != nullptr) {
				index = node->parent_pos - 1;
				node = node->parent;
			}
			else {//root
				index--;
			}
			//Consider end iterator
		}
	}
	else {
		//Find the next node des_down
		node = node->desendants[index];

		while (node->desendants[tree->maxNodeElems] != nullptr)
		{
			node = node->desendants[tree->maxNodeElems];
		}
		index = node->occupied_size - 1;
	}
	return *this;
}



template <typename T>
const_btree_iterator<T> const_btree_iterator<T>::operator ++(int) {
	const_btree_iterator res = *this;
	operator ++();
	return res;

}

template <typename T>
const_btree_iterator<T> const_btree_iterator<T>::operator --(int) {
	const_btree_iterator res = *this;
	operator --();
	return res;

}





template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator=(const const_btree_iterator& original) {
	index = original.index;
	node = original.node;
	tree = original.tree;
	return *this; 
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator=(const btree_iterator<T>& original) {
	index = original.index;
	node = original.node;
	tree = original.tree;
	return *this; 
}



template <typename T>
bool const_btree_iterator<T>::operator==(const const_btree_iterator& original) const{

	return (tree == original.tree && node == original.node && index == original.index);

}

template <typename T>
bool const_btree_iterator<T>::operator==(const btree_iterator<T>& original) const{

	return (tree == original.tree && node == original.node && index == original.index);

}




#endif
#pragma once
