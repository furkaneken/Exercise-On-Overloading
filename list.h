#ifndef _SET_H
#define _SET_H
#include <sstream>
#include <iostream>

template<class type>
struct secondarynode //holds the value of an element of a set
{
	type value;
	secondarynode* next;

	secondarynode(type v) : value(v), next(nullptr) {}
};

template<class type>
class List
{
private:
	secondarynode<type>* head;
	secondarynode<type>* tail;
public:
	List(List* & copy);
	List(type a[], int size);
	void addToList(type num);
	secondarynode<type>* getHead();
};

template<class type>
struct primarynode //holds a list and the size of that integer list
{
	List<type>* l;
	int size;
	primarynode<type>* next;

	primarynode (type a[], int s, primarynode<type>* n = nullptr) : size(s), next(n) 
	{
		l = new List<type>(a, s);
	}

	primarynode (List<type>* copy, int s, primarynode<type>* n = nullptr) : size(s), next(n) 
	{
		l = new List<type>(copy);
	}
};

template<class type>
class Set
{
private:
	primarynode<type>* head;
	primarynode<type>* tail;
public:
	Set(); //constructor
	Set(const Set<type> & set); //copy constructor
	void addSet(type a[], int size); //adds element to the set
	primarynode<type>* createClone(const Set<type> & set); //creates clone and returns the head of the clone
	Set<type> & operator=(const Set<type> & rhs); //assignment operator
	Set<type> & operator+(const Set<type> & rhs); //union operator
	Set<type> & operator/(const Set<type> & rhs); //difference operator
	Set<type> & operator%(const Set<type> & rhs); //intersection operator
	bool isEqual(primarynode<type>* & lhs, primarynode<type>* & rhs);
	primarynode<type>* getHead();
	void deleteSet();
};
#endif