#ifndef SPICES_H
#define SPICES_H

#include <string>
#include <iostream>

using namespace std;

enum class SpiceColor { GREEN, BROWN, YELLOW };

string colorToString(SpiceColor color) {
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

class Spice {
protected:
    string name;
    SpiceColor color;
    string taste;
    string smell;
    string use;

public:
    Spice(const string& name, SpiceColor color, const string& taste, const string& smell, const string& use)
        : name(name), color(color), taste(taste), smell(smell), use(use) {}

    virtual ~Spice() {}

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Color: " << colorToString(color) << endl;
        cout << "Taste: " << taste << endl;
        cout << "Smell: " << smell << endl;
        cout << "Use: " << use << endl;
    }

    const string& getName() const {
        return name;
    }

    SpiceColor getColor() const {
        return color;
    }

    const string& getTaste() const {
        return taste;
    }

    const string& getSmell() const {
        return smell;
    }

    const string& getUse() const {
        return use;
    }
};

class Herb : public Spice {
public:
    Herb(const string& name, SpiceColor color, const string& taste, const string& smell, const string& use)
        : Spice(name, color, taste, smell, use) {}

    void display() const override {
        cout << "Herb:" << endl;
        Spice::display();
    }
};

class Powder : public Spice {
public:
    Powder(const string& name, SpiceColor color, const string& taste, const string& smell, const string& use)
        : Spice(name, color, taste, smell, use) {}

    void display() const override {
        cout << "Powder:" << endl;
        Spice::display();
    }
};

class Liquid : public Spice {
public:
    Liquid(const string& name, SpiceColor color, const string& taste, const string& smell, const string& use)
        : Spice(name, color, taste, smell, use) {}

    void display() const override {
        cout << "Liquid:" << endl;
        Spice::display();
    }
};

#endif // SPICES_H
