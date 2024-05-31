#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "spices.h"
#include "spice_container.h"
#include "iterators.h"
#include "spice_factory.h"

using namespace std;

string spiceColorToString(SpiceColor color) {
    switch (color) {
    case SpiceColor::GREEN:
        return "Green";
    case SpiceColor::BROWN:
        return "Brown";
    case SpiceColor::YELLOW:
        return "Yellow";
    default:
        return "Unknown";
    }
}

void fillContainerWithRandomSpices(VectorSpiceContainer& container, int numSpices) {
    for (int i = 0; i < numSpices; ++i) {
        container.addSpice(SpiceFactory::createRandomSpice());
    }
}

void fillContainerWithRandomSpices(deque<Spice*>& container, int numSpices) {
    for (int i = 0; i < numSpices; ++i) {
        container.push_back(SpiceFactory::createRandomSpice());
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

int main() {
    srand(static_cast<unsigned>(time(0)));

    VectorSpiceContainer vectorContainer;
    deque<Spice*> dequeSpices;

    int numRandomSpices = 10;
    fillContainerWithRandomSpices(vectorContainer, numRandomSpices);
    fillContainerWithRandomSpices(dequeSpices, numRandomSpices); // Используем deque вместо list

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Content of the vector container after filtering by color and sorting by name:" << endl;

    VectorSpiceContainerIterator vectorIterator(vectorContainer.getSpices());
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
    for (Spice* spice : filteredAndSortedVectorSpices) {
        spice->display();
        cout << "Color: " << spiceColorToString(spice->getColor()) << endl;
        cout << endl;
    }

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Not filtered spices from the vector container:" << endl;
    for (Spice* spice : notFilteredSpices) {
        spice->display();
        cout << "Color: " << spiceColorToString(spice->getColor()) << endl;
        cout << endl;
    }

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Sorting spices by taste for not filtered spices:" << endl;

    // Используем deque вместо vector для notFilteredSpices
    sort(notFilteredSpices.begin(), notFilteredSpices.end(), CompareSpicesByTaste);
    DequeSpiceContainerIterator notFilteredIterator(notFilteredSpices);

    // Теперь мы можем использовать notFilteredIterator для перебора отсортированных специй
    for (notFilteredIterator.First(); !notFilteredIterator.IsDone(); notFilteredIterator.Next()) {
        notFilteredIterator.GetCurrent()->display();
        cout << "Color: " << spiceColorToString(notFilteredIterator.GetCurrent()->getColor()) << endl;
        cout << endl;
    }

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Content of the deque container after filtering by color and sorting by name:" << endl;

    // Используем dequeSpices
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
    for (Spice* spice : filteredAndSortedDequeSpices) {
        spice->display();
        cout << "Color: " << spiceColorToString(spice->getColor()) << endl;
        cout << endl;
    }

    cout << "_________________________________________________________________________________________" << endl;

    cout << "Not filtered spices from the deque container:" << endl;

    for (Spice* spice : notFilteredDequeSpices) {
        spice->display();
        cout << "Color: " << spiceColorToString(spice->getColor()) << endl;
        cout << endl;
    }

    return 0;
}

