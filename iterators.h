#ifndef ITERATORS_H
#define ITERATORS_H

#include <vector>
#include <list>
#include <algorithm>
#include "spices.h"
#include "spice_container.h"

using namespace std;

template <typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual T GetCurrent() = 0;
};

template <typename T>
class SortingIterator : public Iterator<T> {
private:
    vector<T> elements;
    typename vector<T>::iterator current;
public:
    SortingIterator(Iterator<T>* iterator, bool (*compare)(T, T)) {
        for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
            elements.push_back(iterator->GetCurrent());
        }
        sort(elements.begin(), elements.end(), compare);
        current = elements.begin();
    }
    void First() override {
        current = elements.begin();
    }
    void Next() override {
        ++current;
    }
    bool IsDone() override {
        return current == elements.end();
    }
    T GetCurrent() override {
        return *current;
    }
};

class VectorSpiceContainerIterator : public Iterator<Spice*> {
private:
    vector<Spice*>::const_iterator current;
    vector<Spice*>::const_iterator end;
    vector<Spice*>::const_iterator begin;
public:
    VectorSpiceContainerIterator(const vector<Spice*>& spices)
        : current(spices.begin()), end(spices.end()), begin(spices.begin()) {}
    void First() override {
        current = begin;
    }
    void Next() override {
        ++current;
    }
    bool IsDone() override {
        return current == end;
    }
    Spice* GetCurrent() override {
        return *current;
    }
};

class ListSpiceContainerIterator : public Iterator<Spice*> {
private:
    list<Spice*>::iterator current;
    list<Spice*>::iterator end;
    list<Spice*>::iterator begin;
public:
    ListSpiceContainerIterator(list<Spice*>& spices) : current(spices.begin()), end(spices.end()), begin(spices.begin()) {}
    void First() override {
        current = begin;
    }
    void Next() override {
        ++current;
    }
    bool IsDone() override {
        return current == end;
    }
    Spice* GetCurrent() override {
        return *current;
    }
};

class TasteSortIterator : public SortingIterator<Spice*> {
public:
    TasteSortIterator(Iterator<Spice*>* iterator, bool (*compare)(Spice*, Spice*))
        : SortingIterator<Spice*>(iterator, compare) {}
};

#endif // ITERATORS_H