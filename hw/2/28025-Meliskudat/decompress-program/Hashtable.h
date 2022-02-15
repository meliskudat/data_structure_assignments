#pragma once
#ifndef Hashtable_H_
#define Hashtable_H_
#include <string>
#include <iostream>
#include <vector>
#include <string> 
using namespace std;


template <class HashedObj>
class HashTable
{
public:
    explicit HashTable(const HashedObj& notFound, int size = 4096) :
        arrayA(size), currentSize(0)
    {};
    
    HashTable(const HashTable& rhs) // copy constructor
        : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
        array(rhs.array), currentSize(rhs.currentSize) { }

    const HashedObj& find(const HashedObj& x) const;

    int hash(const  HashedObj& k, int size) const;
    void insert(const HashedObj& x);
    void remove(const HashedObj& x);
    const HashedObj& findByCode(int number) const;

    enum EntryType { ACTIVE, EMPTY, DELETED };
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) { }
    };

    vector<HashEntry> arrayA;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;

    bool isActive(int currentPos) const;
    int findPos(const HashedObj& x) const;
    
};


struct Part // struct to be used as HashedObj 
{
public:
    Part() { // constructor for part class that store key and the code
        key_value = "";
        code = 0;
    }
    Part(string key1, int code1) {//constructor with parameters for part class that initialize key_value and code
        key_value= key1;
        code = code1;
    }
    bool operator ==(const Part& r) const { //checking if lhs is the same as rhs, if so return true , else return false
        if ((*this).key_value == r.key_value)
            return true;
        return false;
    }
    bool operator !=(const Part& r)const { //also checking if lhs is the same as rhs, it returns false if not equal and returns true if equal
        if ((*this).key_value == r.key_value)
            return false;
        return true;
    }
  
    string key_value;
    int code;

};








































#endif
#include "Hashtable.cpp" 
