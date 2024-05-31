// spice_container.h

#ifndef SPICE_CONTAINER_H
#define SPICE_CONTAINER_H

#include <vector>
#include "spices.h"

using namespace std;

class SpiceContainer {
public:
    virtual ~SpiceContainer() {}
    virtual void addSpice(Spice* spice) = 0;
    virtual vector<Spice*> getSpices() const = 0;
};

class VectorSpiceContainer : public SpiceContainer {
private:
    vector<Spice*> spices;
public:
    VectorSpiceContainer() = default;
    ~VectorSpiceContainer() override {
        for (Spice* spice : spices) {
            delete spice;
        }
    }
    void addSpice(Spice* spice) override {
        spices.push_back(spice);
    }
    vector<Spice*> getSpices() const override {
        return spices;
    }
};



#endif // SPICE_CONTAINER_H
