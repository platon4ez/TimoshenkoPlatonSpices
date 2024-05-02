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


    template<typename T>
    class TasteSortIterator : public Iterator<T> {
    private:
        Iterator<T>* iterator;
        bool(*compareFunction)(T, T);

    public:
        TasteSortIterator(Iterator<T>* iterator, bool(*compareFunction)(T, T)) : iterator(iterator), compareFunction(compareFunction) {}

        ~TasteSortIterator() {
            delete iterator;
        }

        void Reset() override {
            iterator->Reset();
        }

        void Next() override {
            iterator->Next();
        }

        bool IsDone() override {
            return iterator->IsDone();
        }

        T GetCurrent() override {
            return iterator->GetCurrent();
        }

        void Sort() {
            std::vector<T> items;
            while (!iterator->IsDone()) {
                items.push_back(iterator->GetCurrent());
                iterator->Next();
            }
            std::sort(items.begin(), items.end(), compareFunction);
            for (const auto& item : items) {
                iterator->Reset();
                while (iterator->GetCurrent() != item && !iterator->IsDone()) {
                    iterator->Next();
                }
                if (!iterator->IsDone()) {
                    iterator->Next();
                }
            }
            iterator->Reset();
        }
    };
};

#endif // ITERATORS_H