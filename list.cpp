#include<iostream>
#include<sstream>
#include <string>

using namespace std;
#include"list.h"

//member function implementations for set
template<class type>
Set<type>::Set()
{
	head = nullptr;
	tail = nullptr;
}

template<class type>
Set<type>::Set(const Set & rhs)
{
	head = createClone(rhs);
	primarynode<type>* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	tail = temp;
}

template<class type>
void Set<type>::addSet(type a[], int size) //used in adding complete sets given as arrays
{
	if (head == nullptr)
	{
		head = tail = new primarynode<type>(a, size);
	}
	else
	{
		tail->next = new primarynode<type>(a, size);
		tail = tail->next;
	}
}

template<class type>
primarynode<type>* Set<type>::createClone(const Set<type> & rhs)
{
	Set<type>* clone = new Set; //clone is the new clone created
	
	primarynode<type>* settrail = rhs.head; //settrail will watch over rhs and adds its elements into the new set
	clone->head = new primarynode<type>(settrail->l, settrail->size);
	primarynode<type>* temp = clone->head;
	settrail = settrail->next;
	while (settrail)
	{
		temp->next = new primarynode<type>(settrail->l, settrail->size);
		temp = temp->next;
		settrail = settrail->next;
	}
	
	return clone->head;
}

template<class type>
Set<type> & Set<type>::operator=(const Set<type> & rhs) //assignment
{
	if (this == &rhs) //does nothing if this is self assignment
		return *this;
	deleteSet(); //deletes the original
	head = createClone(rhs); //copies rhs into lhs
	primarynode<type>* temp = head;
	while (temp->next)
	{
		temp = temp->next;
	}
	tail = temp;

	return *this;
}

template<class type>
Set<type> & Set<type>::operator+(const Set & rhs) //union will copy lhs and add the different in rhs into the new set
{
	Set<type>* united = new Set<type>;
	//just as a copy constructor
	united->head = createClone(*this);
	primarynode<type>* temp = united->head;
	while (temp->next)
	{
		temp = temp->next;
	}
	united->tail = temp;
	//we have copied the lhs and now we will add the different lists of rhs
	primarynode<type>* settrail1 = rhs.head; //settrail1 will watch over rhs
	while (settrail1)
	{
		bool exists = false;
		primarynode<type>* settrail2 = this->head; //settrail 2 will watch over "this"
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (!exists) //if an element of rhs doesnt exist in "this"
		{
			united->tail->next = new primarynode<type>(settrail1->l, settrail1->size);
			united->tail = united->tail->next;
		}
		settrail1 = settrail1->next;
	}
	return *united;
}

template<class type>
Set<type> & Set<type>::operator/(const Set<type> & rhs) //difference will add only the different lists into the new set
{
	Set<type>* difference = new Set;

	primarynode<type>* settrail1 = this->head; //settrail1 will watch over "this"
	while (settrail1)
	{
		bool exists = false;
		primarynode<type>* settrail2 = rhs.head; //settrail 2 will watch over rhs
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (!exists) //if an element of "this" doesnt exist in rhs
		{
			if (difference->head == nullptr)
			{
				difference->head = difference->tail = new primarynode<type>(settrail1->l, settrail1->size);
			}
			else
			{
				difference->tail->next = new primarynode<type>(settrail1->l, settrail1->size);
				difference->tail = difference->tail->next;
			}
			
		}
		settrail1 = settrail1->next;
	}

	return *difference;
}

template<class type>
Set<type> & Set<type>::operator%(const Set<type> & rhs) //intersection will add only the same lists into the new set
{
	Set<type>* intersection = new Set;

	primarynode<type>* settrail1 = this->head; //settrail 1 will watch over "this"
	while (settrail1)
	{
		bool exists = false;
		primarynode<type>* settrail2 = rhs.head;
		while (settrail2)
		{
			if (isEqual(settrail1, settrail2))
			{
				exists = true;
				break;
			}
			
			settrail2 = settrail2->next;
		}
		if (exists) //if an element of "this" exists in rhs
		{
			if (intersection->head == nullptr)
			{
				intersection->head = intersection->tail = new primarynode<type>(settrail1->l, settrail1->size);
			}
			else
			{
				intersection->tail->next = new primarynode<type>(settrail1->l, settrail1->size);
				intersection->tail = intersection->tail->next;
			}
		}
		settrail1 = settrail1->next;
	}

	return *intersection;
}

template<class type>
void Set<type>::deleteSet() //deletes all elements of a set
{ //settrail watches primarynodes, listtrail watches secondarynodes
	primarynode<type>* settrail = head;
	primarynode<type>* settemp;
	while (settrail)
	{
		secondarynode<type>* listtrail = settrail->l->getHead();
		secondarynode<type>* listtemp;
		while (listtrail)
		{
			listtemp = listtrail->next;
			delete listtrail;
			listtrail = listtemp;
		}
		settemp = settrail->next;
		delete settrail;
		settrail = settemp;
	}
	head = tail = nullptr;
}

template<class type>
bool Set<type>::isEqual(primarynode<type>* & lhs, primarynode<type>* & rhs) //checks if two lists are same or not
{
	if (lhs->size != rhs->size)
		return false;
	secondarynode<type>* listtrail1 = lhs->l->getHead();
	secondarynode<type>* listtrail2 = rhs->l->getHead();
	while (listtrail1)
	{
		if (listtrail1->value != listtrail2->value)
			return false;
		listtrail1 = listtrail1->next;
		listtrail2 = listtrail2->next;
	}
	return true;
}

template<class type>
primarynode<type>* Set<type>::getHead()
{
	return head;
}

//member function implementations for list

template<class type>
List<type>::List(List<type>* & copy) //used in copying and assigning
{
	head = tail = nullptr;
	secondarynode<type>* listtrail = copy->head;
	while (listtrail)
	{
		if (head == nullptr)
		{
			head = tail = new secondarynode<type>(listtrail->value);
		}
		else
		{
			tail->next = new secondarynode<type>(listtrail->value);
			tail = tail->next;
		}
		listtrail = listtrail->next;
	}
}

template<class type>
List<type>::List(type a[], int size) //used in adding complete lists given as arrays
{
	head = tail = new secondarynode<type>(a[0]);

	for (int i = 1; i < size; i++)
	{
		tail->next = new secondarynode<type>(a[i]);
		tail = tail->next;
	}
}

template<class type>
void List<type>::addToList(type num) //adds standalone numbers into list, used in copying and assigning
{
	if (head == nullptr)
	{
		head = tail = new secondarynode<type>(num);
	}
	else
	{
		tail->next = new secondarynode<type>(num);
		tail = tail->next;
	}
}

template<class type>
secondarynode<type>* List<type>::getHead()
{
	return head;
}
