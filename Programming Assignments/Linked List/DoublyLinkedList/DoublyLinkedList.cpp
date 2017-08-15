#include "DoublyLinkedList.h"
#include <stdexcept>
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
// time complexity O(n)
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll) {
    
	// Initialize the list
	header.next = &trailer; trailer.prev = &header;
  
	// Properly start with the first node of dll
	DListNode* current = dll.getFirst();
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
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll) {
	
	// Delete this list
	delete this; // haHAA
	
	// Initialize the list
	header.next = &trailer; trailer.prev = &header;
  
	// Properly start with the first node of dll
	DListNode* current = dll.getFirst();
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
void DoublyLinkedList::insertFirst(int newobj) { 
  DListNode *newNode = new DListNode(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert the object to the last of the linked list
// time complexity O(1)
void DoublyLinkedList::insertLast(int newobj) {
  DListNode *newNode = new DListNode(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first object of the list
// time complexity O(1)
int DoublyLinkedList::removeFirst() { 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  int obj = node->obj;
  delete node;
  return obj;
}

// remove the last object of the list
// time complexity O(1)
int DoublyLinkedList::removeLast() {
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// destructor
// time complexity O(n)
DoublyLinkedList::~DoublyLinkedList() {
  DListNode *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
// time complexity O(1)
int DoublyLinkedList::first() const { 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}

// return the last object
// time complexity O(n)
int DoublyLinkedList::last() const {
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}

// return the list length
// time complexity O(n)
int DoublyLinkedListLength(DoublyLinkedList& dll) {
  DListNode *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) {
    count++;
    current = current->getNext(); //iterate
  }
  return count;
}

// output operator
// beautiful printing
// time complexity O(n)
ostream& operator<<(ostream& out, const DoublyLinkedList& dll) {
  
	DListNode* current = dll.getFirst();
	cout << " ← " << current->getElem() << " ↔ ";
	
	while (current->getNext() != NULL) {
		cout << current->getElem() << " ↔ ";
		current = current->getNext(); //iterate
	}
	
	cout << current->getElem() << " → ";
	
  return out;
}
