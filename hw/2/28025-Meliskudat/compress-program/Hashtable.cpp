#include <string>
#include <iostream>
#include <vector>
#include "Hashtable.h"

using namespace std;




template <class HashedObj>
int HashTable<HashedObj> ::hash(const  HashedObj& a, int size) const // it will return ascii number of a char , return 256 for a string
{

    string string_new = a.key_value;
    if (string_new.length() == 1) 
    {
        return (unsigned char)(string_new[0]); // the ascii number of the char
    }
    else
        return 256; // if it has more than one char , its position will start not from 0 but from 256


}



template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const 
{
   

    int index = hash(x, arrayA.size()); // it will return 256 for a string , and char value for a char

    while (arrayA[index].info != EMPTY && arrayA[index].element != x) // if it is not empty to insert and element is not equal to one we search
    {

        index += 1;  // it is linear probbing so we will add one by one
        int size = arrayA.size();
        if (index >= size)             
            index = index - size;          
    }

    return index; 
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
  
    int currentPos = findPos(x); // find an empty location to insert

    if (isActive(currentPos)) // means you cannot insert
        return;

    arrayA[currentPos] = HashEntry(x, ACTIVE); // insert that element as active to that index
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
    int currentPos = findPos(x); // find position of x

    if (isActive(currentPos))
        arrayA[currentPos].info = DELETED;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return arrayA[currentPos].info == ACTIVE;
}


template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const
{
    int currentPos = findPos(x); // finds the location

    if (isActive(currentPos))
        return arrayA[currentPos].element; // returns "part"

    return   ITEM_NOT_FOUND; // if not in the list return not found
}

template <class HashedObj>
const HashedObj& HashTable<HashedObj>::findByCode(int number) const
{
    int currentPos = number; // finds the location

    if (isActive(number))
        return arrayA[number].element; // returns "part"

    return   ITEM_NOT_FOUND; // if not in the list return not found
}