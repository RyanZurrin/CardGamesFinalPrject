#pragma once

#ifndef QUEUE_H
#define QUEUE_H
#include <iomanip>
#include <iostream>
#include "deckOfCards.h"



struct cardStruct
{
	card c_;
	cardStruct* next;
};

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
	bool enQueue(card c);

	/// <summary>
	/// Des the queue.
	/// </summary>
	/// <param name="num">The .</param>
	/// <returns></returns>
	bool deQueue(card& c);

	/// <summary>
	/// Gets the front.
	/// </summary>
	/// <returns></returns>
	cardStruct* getFront()const;

	/// <summary>
	/// Gets the back.
	/// </summary>
	/// <returns></returns>
	cardStruct* getBack()const;

	/// <summary>
	/// Peeks the specified .
	/// </summary>
	/// <param name="">The .</param>
	/// <returns>num</returns>
	bool peek(card& c)const;//save next element to a int

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
	cardStruct* back;//pointer to rear of list
	cardStruct* front;;//pointer to start of list
	int qty;//variable to hold number of elements
	int max;//max size of queue
};

#endif


inline Queue::Queue()
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = 20;
}

inline Queue::Queue(int maxSize)
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = maxSize;
}

inline Queue::~Queue()
{
	makeEmpty();
}

inline bool Queue::enQueue(card c)
{
	cardStruct* temp;
	if (isFull())
	{
		return false;
	}
	temp = new cardStruct;
	temp->c_.face = c.face;
	temp->c_.suit = c.face;
	temp->next = NULL;

	if (back == NULL) {
		back = temp;
		back->next = NULL;
		back->c_.face = c.face;
		back->c_.suit = c.suit;
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

inline bool Queue::deQueue(card& c)
{
	cardStruct* temp;
	if (back == front)
	{
		back = front = NULL;
		qty--;
		return true;
	}
	else
	{
		temp = front;
		
		c.face = temp->c_.face;
		c.suit = temp->c_.suit;
		front = front->next;
		delete temp;
		qty--;
		return true;
	}

}


inline cardStruct* Queue::getFront()const
{
	return this->front;
}

inline cardStruct* Queue::getBack() const
{
	return this->back;
}

inline bool Queue::peek(card& c)const
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

inline bool Queue::isEmpty()const
{

	if (qty==0)
	{
		return true;
	}
	return false;

}

inline bool Queue::isFull()const
{

	if (qty >= max)
	{
		return true;
	}
	return false;

}

inline bool Queue::makeEmpty()
{
	cardStruct* temp;
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

inline int Queue::getQty()
{
	return qty;
}

inline void Queue::displayQueue()const
{
	cardStruct* temp;

		temp = front;
		while (temp != NULL)
		{
			std::cout <<temp->c_.face << temp->c_.suit;
			temp = temp->next;
		}
		std::cout << std::endl;

}
