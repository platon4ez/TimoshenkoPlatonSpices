﻿#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sqlite3.h>
#include "spices.h"
#include "spice_container.h"
#include "iterators.h"
#include "spice_factory.h"
#include "spices_database.h"
#include "SpiceDatabaseContainer.h"

using namespace std;

template <typename Container>
void fillContainerWithRandomSpices(Container& container, int numSpices) {
    for (int i = 0; i < numSpices; ++i) {
        container.push_back(SpiceFactory::createRandomSpice());
    }
}

void fillContainerWithRandomSpices(VectorSpiceContainer& container, int numSpices) {
    for (int i = 0; i < numSpices; ++i) {
        container.addSpice(SpiceFactory::createRandomSpice());
    }
}

bool CompareSpicesByName(Spice* spice1, Spice* spice2) {
    return spice1->getName() < spice2->getName();
}

bool CompareSpicesByTaste(Spice* spice1, Spice* spice2) {
    return spice1->getTaste() < spice2->getTaste();
}

class DequeSpiceContainerIterator : public Iterator<Spice*> {
private:
    deque<Spice*>::iterator iterator;
    deque<Spice*>& spices;

public:
    DequeSpiceContainerIterator(deque<Spice*>& spices) : iterator(spices.begin()), spices(spices) {}

    void First() override {
        iterator = spices.begin();
    }

    void Next() override {
        ++iterator;
    }

    bool IsDone() override {
        return iterator == spices.end();
    }

    Spice* GetCurrent() override {
        return *iterator;
    }
};

template <typename Container>
void displayContainer(const Container& container) {
    for (const auto& spice : container) {
        spice->display();
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    SpiceDatabaseContainer dbContainer("D:\\TimoshenkoPlatonSpices\\x64\\Debug\\spices.db");

    std::list<Spice*> dbSpices = dbContainer.getAllSpices();

    if (dbSpices.empty()) {
        cerr << "No spices found in the database." << endl;
        return 1;
    }

    cout << "Spices from the database without sorting" << endl;
    displayContainer(dbSpices);

    dbSpices.sort([](const Spice* a, const Spice* b) { return a->getName() < b->getName(); });
    cout << "_________________________________________________________________________________________" << endl;

    cout << "Spices from the database by alphabetical order:" << endl;
    displayContainer(dbSpices);

    VectorSpiceContainer vectorContainer;
    deque<Spice*> dequeSpices;

    int numRandomSpices = 10;
    fillContainerWithRandomSpices(vectorContainer, numRandomSpices);
    fillContainerWithRandomSpices(dequeSpices, numRandomSpices);

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Content of the vector container after filtering by color and sorting by name:" << endl;
    vector<Spice*> filteredAndSortedVectorSpices;
    deque<Spice*> notFilteredSpices;
    for (size_t i = 0; i < vectorContainer.getSpices().size(); ++i) {
        Spice* spice = vectorContainer.getSpices()[i];
        if (spice->getColor() == SpiceColor::GREEN) {
            filteredAndSortedVectorSpices.push_back(spice);
        }
        else {
            notFilteredSpices.push_back(spice);
        }
    }
    sort(filteredAndSortedVectorSpices.begin(), filteredAndSortedVectorSpices.end(), CompareSpicesByName);
    displayContainer(filteredAndSortedVectorSpices);

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Not filtered spices from the vector container:" << endl;
    displayContainer(notFilteredSpices);

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Sorting spices by taste for not filtered spices:" << endl;

    sort(notFilteredSpices.begin(), notFilteredSpices.end(), CompareSpicesByTaste);
    DequeSpiceContainerIterator notFilteredIterator(notFilteredSpices);

    for (notFilteredIterator.First(); !notFilteredIterator.IsDone(); notFilteredIterator.Next()) {
        notFilteredIterator.GetCurrent()->display();
        cout << endl;
    }

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Content of the deque container after filtering by color and sorting by name:" << endl;

    sort(dequeSpices.begin(), dequeSpices.end(), CompareSpicesByName);
    deque<Spice*> filteredAndSortedDequeSpices;
    deque<Spice*> notFilteredDequeSpices;
    for (size_t i = 0; i < dequeSpices.size(); ++i) {
        Spice* spice = dequeSpices[i];
        if (spice->getColor() == SpiceColor::GREEN) {
            filteredAndSortedDequeSpices.push_back(spice);
        }
        else {
            notFilteredDequeSpices.push_back(spice);
        }
    }
    displayContainer(filteredAndSortedDequeSpices);

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Not filtered spices from the deque container:" << endl;

    displayContainer(notFilteredDequeSpices);

    return 0;
}
