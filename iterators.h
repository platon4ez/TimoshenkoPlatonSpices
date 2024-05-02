#ifndef ITERATORS_H
#define ITERATORS_H

#include "spices.h"
#include <vector>
#include <list>
#include <functional> 

using namespace std;

template<class Type>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Type GetCurrent() const = 0;
};

class VectorSpiceContainerIterator : public Iterator<Spice*>
{
private:
    vector<Spice*>& spices;
    typename vector<Spice*>::iterator it;

public:
    VectorSpiceContainerIterator(vector<Spice*>& spices) : spices(spices), it(spices.begin()) {}

    void First() override { it = spices.begin(); }
    void Next() override { ++it; }
    bool IsDone() const override { return it == spices.end(); }
    Spice* GetCurrent() const override { return *it; }
};

class ListSpiceContainerIterator : public Iterator<Spice*>
{
private:
    list<Spice*>& spices;
    typename list<Spice*>::iterator it;

public:
    ListSpiceContainerIterator(list<Spice*>& spices) : spices(spices), it(spices.begin()) {}

    void First() override { it = spices.begin(); }
    void Next() override { ++it; }
    bool IsDone() const override { return it == spices.end(); }
    Spice* GetCurrent() const override { return *it; }
};

template<class Type>
class SortingIterator : public Iterator<Type>
{
private:
    Iterator<Type>* iterator;
    function<bool(Type, Type)> compareFunc; 

public:
    SortingIterator(Iterator<Type>* iterator, function<bool(Type, Type)> compareFunc)
        : iterator(iterator), compareFunc(compareFunc) {}

    void First() override { iterator->First(); }

    void Next() override { iterator->Next(); }

    bool IsDone() const override { return iterator->IsDone(); }

    Type GetCurrent() const override { return iterator->GetCurrent(); }
};

#endif // ITERATORS_H