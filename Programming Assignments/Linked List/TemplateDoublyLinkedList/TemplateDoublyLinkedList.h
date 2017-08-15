#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T> class DoublyLinkedList;

template <typename T> class DListNode {
    private:
		T obj;
		DListNode<T> *prev, *next;
		friend class DoublyLinkedList<T>;
		public:
		DListNode ( DListNode<T> *p = NULL, DListNode<T> *n = NULL)
			: prev(p), next(n) {}
			DListNode ( T e, DListNode<T> *p = NULL, DListNode<T> *n = NULL)
			: obj(e), prev(p), next(n) {}
		T getElem() const { return obj; }
		DListNode<T>* getNext() const { return next;} 
		DListNode<T>* getPrev() const { return prev;}
};

// doubly linked list
template <typename T> class DoublyLinkedList {
    protected:
		DListNode<T> header, trailer;
    public:
		// constructor
		DoublyLinkedList() : header(0), trailer(0) {header.next = &trailer; trailer.prev = &header;}
		DoublyLinkedList(DoublyLinkedList<T>& dll); // copy constructor
		~DoublyLinkedList(); // destructor
		DoublyLinkedList& operator=(DoublyLinkedList<T>& dll); //copy assignment operator
		// return the pointer to the first node
		DListNode<T> *getFirst() const { return header.next;}
		// return the pointer to the trailer
		DListNode<T> *getAfterLast() { return &trailer;}
		// return if the list is empty
		bool isEmpty() const { return header.next == &trailer; }
		T first() const; // return the first object 
		T last() const; // return the last object 
		void insertFirst(T newobj); // insert to the first of the list
		T removeFirst(); // remove the first node
		void insertLast(T newobj); // insert to the last of the list
		T removeLast(); // remove the last node
};

// output operator
template <typename T> ostream& operator<<(ostream& out,DoublyLinkedList<T>& dll);

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
    explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

//-----------------------------------------------------------------------------

// copy constructor 
// time complexity O(n)
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>& dll) {
    // Initialize the list
	header.next = &trailer; trailer.prev = &header;
  
	// Properly start with the first node of dll
	DListNode<T>* current = dll.getFirst();
	header = *current;
	
	// Copy from dll
	while(current->getNext() != NULL) {
		insertLast(current->getElem());
		current = current->getNext(); //iterate
	}
	
	// Properly terminate with the final node of dll
	trailer = *current;
	trailer.prev = current->getPrev();
}

// assignment operator
// time complexity O(n)
template <typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>& dll) {

    // Delete this list
	delete this; // haHAA
	
	// Initialize the list
	header.next = &trailer; trailer.prev = &header;
  
	// Properly start with the first node of dll
	DListNode<T>* current = dll.getFirst();
	header = *current;
	
	// Copy from dll
	while(current->getNext() != NULL) {
		insertLast(current->getElem());
		current = current->getNext(); //iterate
	}
	
	// Properly terminate with the final node of dll
	trailer = *current;
	trailer.prev = current->getPrev();
}

// insert the object to the first of the linked list
// time complexity O(1)
template <typename T> void DoublyLinkedList<T>::insertFirst(T newobj) {
    DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert the object to the last of the linked list
// time complexity O(1)
template <typename T> void DoublyLinkedList<T>::insertLast(T newobj) {
    DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first object of the list
// time complexity O(1)
template <typename T> T DoublyLinkedList<T>::removeFirst() {
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    DListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
}

// remove the last object of the list
// time complexity O(1)
template <typename T> T DoublyLinkedList<T>::removeLast() {
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    DListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T obj = node->obj;
    delete node;
    return obj;
}

// destructor
// time complexity O(n)
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() {
    DListNode<T> *prev_node, *node = header.next;
    while (node != &trailer)
    {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// return the first object
// time complexity O(1)
template <typename T> T DoublyLinkedList<T>::first() const {
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return header.next->obj;
}

// return the last object
// time complexity O(1)
template <typename T> T DoublyLinkedList<T>::last() const {
    if (isEmpty())
        throw EmptyDLinkedListException("Empty Doubly Linked List");
    return trailer.prev->obj;
}

// return the list length
// time complexity O(n)
template <typename T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll) {
    DListNode<T> *current = dll.getFirst();
    int count = 0;
    while(current != dll.getAfterLast())
    {
        count++;
        current = current->getNext(); //iterate
    }
    return count;
}

// output operator
// time complexity O(n) but it looks BEAUTIFUL
template <typename T> ostream& operator<<(ostream& out, DoublyLinkedList<T>& dll) {
    DListNode<T>* current = dll.getFirst();
	cout << " ← " << current->getElem() << " ↔ ";
	
	while (current->getNext() != NULL) {
		cout << current->getElem() << " ↔ ";
		current = current->getNext(); //iterate
	}
	
	cout << current->getElem() << " → ";
	
  return out;
}