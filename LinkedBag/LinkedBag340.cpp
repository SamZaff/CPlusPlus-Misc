#include <cstddef>
#include "Node.h"
#include "LinkedBag.h"
#include <time.h>
#include <string>
#include <stdlib.h>

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
	Node<ItemType>* secondNodePtr = headPtr->getNext();
	bool canRemoveItem = !isEmpty() && (secondNodePtr != nullptr);

	if (canRemoveItem) {
		secondNodePtr->setItem(headPtr->getItem());
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	}

	return canRemoveItem;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& anEntry) {
	Node<ItemType>* entryNodePtr = new Node<ItemType>();
	entryNodePtr->setItem(anEntry);
	Node<ItemType>* curPtr = headPtr;
	int counter = 1;

	// traverse to the end of the linked list
	while ((curPtr != nullptr) && (counter < itemCount)) {
		curPtr = curPtr->getNext();
		counter++;
	}

	curPtr->setNext(entryNodePtr);
	itemCount++;

	return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;

	// traverse to the end of the linked list
	while (curPtr != nullptr) {
		curPtr = curPtr->getNext();
		counter++;
	}

	return counter;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* curPtr) const {
	if (curPtr == nullptr) {
		return 0;
	}
	else {
		curPtr = curPtr->getNext();
		return 1 + getCurrentSize340RecursiveHelper(curPtr);
	}
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
	Node<ItemType>* curPtr = headPtr;
	return getCurrentSize340RecursiveHelper(curPtr);

}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* curPtr, const ItemType& anEntry) const {
	if (curPtr == nullptr) {
		return 0;
	}
	if (anEntry == curPtr->getItem()) {
		curPtr = curPtr->getNext();
		return 1 + getFrequencyOf340RecursiveHelper(curPtr, anEntry);
	}
	else {
		curPtr = curPtr->getNext();
		return getFrequencyOf340RecursiveHelper(curPtr, anEntry);
	}
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& anEntry) const {
	Node<ItemType>* curPtr = headPtr;
	return getFrequencyOf340RecursiveHelper(curPtr, anEntry);
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
	std::string randomItem = headPtr->getItem();
	Node<ItemType>* curPtr = headPtr;

	// allows for new random values on each run
	srand(time(NULL));

	// reservoir sampling
	int n;
	for (n = 2; curPtr != nullptr; n++) {
		if (rand() % n == 0) {
			randomItem = curPtr->getItem();
		}
		curPtr = curPtr->getNext();
	}

	Node<ItemType>* randomNodePtr = getPointerTo(randomItem);
	bool canRemoveItem = !isEmpty() && (randomNodePtr != nullptr);

	if (canRemoveItem) {
		randomNodePtr->setItem(headPtr->getItem());
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	}

	return randomItem;
}