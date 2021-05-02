#pragma once
/**
 * @FileName discardPile.h
 * @Details Template Class DiscardPile interface and in-line implementation currently
 * being used as part of a card game final project. Being used in the War Class
 * as a card pile for each player.
 * @Author Ryan Zurrin
 * @DateBuilt  2/25/2021
 * @lastModified 4/26/2021
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iomanip>
#include <iostream>

template<class T>
struct node
{
	T c_;
	bool faceUp;
	node<T>* next;
	node()
	{
		next = NULL;
		faceUp = false;
	}
};
template<class T>
class PlayPile
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Queue"/> class.
	/// </summary>
	PlayPile();

	/// <summary>
	/// Initializes a new instance of the Queue class.
	/// </summary>
	/// <param name="maxSize">The max number of elements queue can hold</param>
	PlayPile(int);

	/// <summary>
	/// Finalizes an instance of the Queue class.
	/// </summary>
	~PlayPile();

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
	node<T>* getFront()const;

	/// <summary>
	/// Gets the back.
	/// </summary>
	/// <returns></returns>
	node<T>* getBack()const;

	/// <summary>
	/// Peeks the specified .
	/// </summary>
	/// <param name="">The .</param>
	/// <returns>num</returns>
	bool peek(T& c);//save next element to a int

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
	node<T>* back;//pointer to rear of list
	node<T>* front;;//pointer to start of list
	int qty;//variable to hold number of elements
	int max;//max size of queue
};

#endif

template<class T>
inline PlayPile<T>::PlayPile()
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = INT_MAX;
}
template<class T>
inline PlayPile<T>::PlayPile(int maxSize)
{
	back = NULL;
	front = NULL;
	qty = 0;
	max = maxSize;
}
template<class T>
inline PlayPile<T>::~PlayPile()
{
	makeEmpty();
}

template<class T>
inline bool PlayPile<T>::enQueue(T c)
{
	node<T>* temp;
	if (isFull())
	{
		return false;
	}
	temp = new node<T>;
	temp->c_ = c;
	temp->next = NULL;

	if (back == NULL) {
		back = temp;
		back->next = NULL;
		front = back;
		temp = NULL;
		delete temp;
		qty++;
		return true;
	}
	else {
		back->next = temp;
		back = temp;
		qty++;
		temp = NULL;
		delete temp;
		return true;
	}
}
template<class T>
inline bool PlayPile<T>::deQueue(T& c)
{
	node<T>* temp;
	if (back == NULL)
	{
		return false;
	}
	if (back == front)
	{
		c = front->c_;
		back = front = NULL;
		qty--;
		return true;
	}
	else
	{
		c = front->c_;
		temp = front;
		front = front->next;
		delete temp;
		qty--;
		return true;
	}
}

template<class T>
inline node<T>* PlayPile<T>::getFront()const
{
	return this->front;
}
template<class T>
inline node<T>* PlayPile<T>::getBack() const
{
	return this->back;
}
template<class T>
inline bool PlayPile<T>::peek(T& c)
{
	if (isEmpty())
	{
		return false;
	}
	if (this->front != NULL)
	{
		c = front->c_;
		return true;
	}
	return false;

}

template<class T>
inline bool PlayPile<T>::isEmpty()const
{
	if (qty==0)
	{
		return true;
	}
	return false;
}
template<class T>
inline bool PlayPile<T>::isFull()const
{
	if (qty >= max)
	{
		return true;
	}
	return false;

}
template<class T>
inline bool PlayPile<T>::makeEmpty()
{
	node<T>* temp;
	if (isEmpty())
	{
		return false;
	}
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
	back = NULL;
	qty = 0;
	return true;
}
template<class T>
inline int PlayPile<T>::getQty()
{
	return qty;
}
template<class T>
inline void PlayPile<T>::displayQueue()const
{
	node<T>* temp;

		temp = front;
		while (temp != NULL)
		{
			if (temp->faceUp == true)
			{
				std::cout << temp->c_ << " ";
			}
			else
				std::cout << " * ";
			temp = temp->next;
		}
		std::cout << std::endl;

}