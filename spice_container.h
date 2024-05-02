#ifndef SPICE_CONTAINER_H
#define SPICE_CONTAINER_H

#include "spices.h"
#include <vector>
#include <list>
#include "iterators.h"

using namespace std;

class SpiceContainer {
public:
    virtual void addSpice(Spice* spice) = 0;
    virtual void removeSpice(Spice* spice) = 0;
    virtual void display() = 0;
    virtual ~SpiceContainer() {}
    virtual vector<Spice*>& getSpices() = 0;
};

class VectorSpiceContainer : public SpiceContainer {
private:
    vector<Spice*> spices;

public:
    VectorSpiceContainer() = default;
    ~VectorSpiceContainer() {
        for (Spice* spice : spices) {
            delete spice;
        }
    }

    void addSpice(Spice* spice) override {
        spices.push_back(spice);
    }

    void removeSpice(Spice* spice) override {
        spices.erase(remove(spices.begin(), spices.end(), spice), spices.end());
        delete spice;
    }

    void display() override {
        for (Spice* spice : spices) {
            spice->display();
            cout << endl;
        }
    }

    vector<Spice*>& getSpices() override {
        return spices;
    }
};

class ListSpiceContainer : public SpiceContainer {
private:
    list<Spice*> spices;

public:
    ListSpiceContainer() = default;
    ~ListSpiceContainer() {
        for (Spice* spice : spices) {
            delete spice;
        }
    }

    void addSpice(Spice* spice) override {
        spices.push_back(spice);
    }

    void removeSpice(Spice* spice) override {
        spices.remove(spice);
        delete spice;
    }

    void display() override {
        for (Spice* spice : spices) {
            spice->display();
            cout << endl;
        }
    }

    vector<Spice*>& getSpices() override {
        static vector<Spice*> spicesVec(spices.begin(), spices.end());
        return spicesVec;
    }
};

#endif // SPICE_CONTAINER_H
