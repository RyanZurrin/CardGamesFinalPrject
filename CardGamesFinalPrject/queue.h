#pragma once

#ifndef QUEUE_H
#define QUEUE_H
#include <iomanip>
#include <iostream>
#include "deckOfCards.h"
template<class T>
struct Node
{
	T c_;
	Node<T>* next;
};
template<class T>
class Queue
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Queue"/> class.
	/// </summary>
	Queue();

	/// <summary>
	/// Initializes a new instance of the Queue class.
	/// </summary>
	/// <param name="maxSize">The max number of elements queue can hold</param>
	Queue(int);

	/// <summary>
	/// Finalizes an instance of the Queue class.
	/// </summary>
	~Queue();

	/// <summary>
	/// Enqueues the specified number.
	/// </summary>
	/// <param name="num">The number.</param>
	/// <returns>true if successfully enqueues: false if else</returns>
	bool enQueue(T c);

	/// <summary>
	/// Des the queue.
	/// </summary>
	/// <param name="num">The .</param>
	/// <returns></returns>
	bool deQueue(T& c);

	/// <summary>
	/// Gets the front.
	/// </summary>
	/// <returns></returns>
	Node<T>* getFront()const;

	/// <summary>
	/// Gets the back.
	/// </summary>
	/// <returns></returns>
	Node<T>* getBack()const;

	/// <summary>
	/// Peeks the specified .
	/// </summary>
	/// <param name="">The .</param>
	/// <returns>num</returns>
	bool peek(T& c)const;//save next element to a int

	/// <summary>
	/// Determines whether this instance is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty()const;//return true if empty:false if else

	/// <summary>
	/// Determines whether this instance is full.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is full; otherwise, <c>false</c>.
	/// </returns>
	bool isFull()const;//return true if full: false if else

	/// <summary>
	/// Makes the empty.
	/// </summary>
	/// <returns></returns>
	bool makeEmpty();//empties the queue

	/// <summary>
	/// Gets the qty.
	/// </summary>
	/// <returns>qty of stack</returns>
	int getQty();//return the qty of items in the queue

	/// <summary>
	/// Displays the queue.
	/// </summary>
	void displayQueue()const;
	//::Queue& operator=(Queue* queue);

private:
	Node<T>* back;//pointer to rear of list
	Node<T>* front;;//pointer to start of list
	int qty;//variable to hold number of elements
	int max;//max size of queue
};

#endif

template<class T>
inline Queue<T>::Queue()
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = 20;
}
template<class T>
inline Queue<T>::Queue(int maxSize)
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = maxSize;
}
template<class T>
inline Queue<T>::~Queue()
{
	makeEmpty();
}

template<class T>
inline bool Queue<T>::enQueue(T c)
{
	Node<T>* temp;
	if (isFull())
	{
		return false;
	}
	temp = new Node<T>;
	temp->c_ = c;
	//temp->c_.face = c.face;
	//temp->c_.suit = c.face;
	temp->next = NULL;

	if (back == NULL) {
		back = temp;
		back->next = NULL;
		//back->c_.face = c.face;
		//back->c_.suit = c.suit;
		front = back;
		qty++;
		return true;
	}
	else {
		back->next = temp;
		back = temp;
		qty++;
		return true;
	}

}
template<class T>
inline bool Queue<T>::deQueue(T& c)
{
	Node<T>* temp;
	if (back == front)
	{
		back = front = NULL;
		qty--;
		return true;
	}
	else
	{
		temp = front;
		//c.face = temp->c_.face;
		//c.suit = temp->c_.suit;
		front = front->next;
		delete temp;
		qty--;
		return true;
	}

}

template<class T>
inline Node<T>* Queue<T>::getFront()const
{
	return this->front;
}
template<class T>
inline Node<T>* Queue<T>::getBack() const
{
	return this->back;
}
template<class T>
inline bool Queue<T>::peek(T& c)const
{
	if (isEmpty())
	{
		//c = NULL;
		return false;
	}
	if (this->front != NULL)
	{
		c = front->c_;
		return true;
	}
//	c = NULL;
	return false;

}

template<class T>
inline bool Queue<T>::isEmpty()const
{

	if (qty==0)
	{
		return true;
	}
	return false;

}
template<class T>
inline bool Queue<T>::isFull()const
{

	if (qty >= max)
	{
		return true;
	}
	return false;

}
template<class T>
inline bool Queue<T>::makeEmpty()
{
	Node<T>* temp;
	if (isEmpty())
	{
		std::cout << " Queue is empty" << std::endl;
		return false;
	}
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
	back = NULL;
	return true;
}
template<class T>
inline int Queue<T>::getQty()
{
	return qty;
}
template<class T>
inline void Queue<T>::displayQueue()const
{
	Node<T>* temp;

		temp = front;
		while (temp != NULL)
		{
			std::cout << temp->c_;
			temp = temp->next;
		}
		std::cout << std::endl;

}
