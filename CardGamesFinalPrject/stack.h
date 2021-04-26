#pragma once
/**
 * @FileName stack.h
 * @Details Template Stack class interface and inline implementation currently
 * being used as part of a card game final project. Being used in the War Class
 * as a discard pile for each player.
 * @Author Ryan Zurrin
 * @DateBuilt  2/12/2021
 * @lastModified 4/26/2021
 */

#ifndef STACK_H
#define STACK_H

template<class T>
struct s_node
{
	T c_;
	bool faceUp;
	s_node<T>* next;
	s_node()
	{
		next = NULL;
		faceUp = false;
	}
};

template<class T>
class Stack
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Stack"/> class.
	/// </summary>
	Stack();
	/// <summary>
	/// Initializes a new instance of the <see cref="Stack"/> class.
	/// </summary>
	/// <param name="maxSize">The maximum size.</param>
	Stack(int);
	/// <summary>
	/// Finalizes an instance of the <see cref="Stack"/> class.
	/// </summary>
	~Stack();
	/// <summary>
	/// Pushes the specified value on to the top of stack.
	/// </summary>
	/// <param name="c">The c.</param>
	/// <returns></returns>
	bool push(T);
	/// <summary>
	/// Pops the specified c off the top.
	/// </summary>
	/// <param name="c">The c.</param>
	/// <returns></returns>
	bool pop(T&);
	/// <summary>
	/// Peeks at the specified top value of the stack.
	/// </summary>
	/// <param name="c">The c.</param>
	/// <returns></returns>
	bool peek(T&)const;
	/// <summary>
	/// Gets the top Pointer address
	/// </summary>
	/// <returns>pointer to top of stack</returns>
	s_node<T>* getTop();
	/// <summary>
	/// Determines whether this instance is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty()const;
	/// <summary>
	/// Determines whether this instance is full.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is full; otherwise, <c>false</c>.
	/// </returns>
	bool isFull()const;
	/// <summary>
	/// Makes the stack empty.
	/// </summary>
	/// <returns></returns>
	bool makeEmpty();
	/// <summary>
	/// Gets the qty.
	/// </summary>
	/// <returns>
	///  <c>true</c> if this instance is made empty; otherwise, <c>false</c>.
	/// </returns>
	int getQty()const;
	/// <summary>
	/// Displays the stack.
	/// </summary>
	void displayStack()const;

private:
	s_node<T>* topPtr;
	int qty;
	int max;
};

#endif
template<class T>
inline Stack<T>::Stack()
{
	qty = 0;
	max = 1024;
	topPtr = NULL;
}
template<class T>
inline Stack<T>::Stack(int maxSize)
{
	qty = 0;
	max = maxSize;
	topPtr = NULL;
}
template<class T>
inline Stack<T>::~Stack()
{
	makeEmpty();
}
template<class T>
inline bool Stack<T>::push(T c)
{
	s_node<T>* temp;
	if (isFull())
	{
		return false;
	}
	temp = new s_node<T>;
	temp->c_ = c;
	temp->next = topPtr;
	topPtr = temp;
	qty++;
	return true;
}
template<class T>
inline bool Stack<T>::pop(T& c)
{
	s_node<T>* temp;
	if (isEmpty())
	{
		return false;
	}
	temp = topPtr;
	topPtr = topPtr->next;
	c = temp->c_;
	delete temp;
	qty--;
	return true;
}
template<class T>
inline bool Stack<T>::peek(T& c)const
{
	if (isEmpty())
	{
		return false;
	}
	c = topPtr->c_;
	return true;
}
template<class T>
inline s_node<T>* Stack<T>::getTop()
{
	return this->topPtr;
}
template<class T>
inline bool Stack<T>::isEmpty()const
{
	if (topPtr == NULL)
	{
		return true;
	}
	return false;
}
template<class T>
inline bool Stack<T>::isFull()const
{
	if (qty >= max)
	{
		return true;
	}
	return false;
}
template<class T>
inline bool Stack<T>::makeEmpty()
{
	s_node<T>* temp;
	if (isEmpty())
	{
		return false;
	}
	while (topPtr != NULL)
	{
		temp = topPtr;
		topPtr = topPtr->next;
		delete temp;
	}
	qty = 0;
	return true;
}
template<class T>
inline int Stack<T>::getQty()const
{
	return qty;
}

template<class T>
inline void Stack<T>::displayStack() const
{
		s_node<T>* temp;
		temp = topPtr;
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
