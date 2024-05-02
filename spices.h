#ifndef SPICES_H
#define SPICES_H

#include <string>
using namespace std;


enum class SpiceColor {
    GREEN, 
    BROWN,
    YELLOW,
    RED,
    DARK,
};

class Spice {
protected:
    string name;
    SpiceColor color;
    string taste;
    string aroma;

public:
    Spice(string _name, SpiceColor _color, string _taste, string _aroma);
    virtual ~Spice() {}
    string getName() const {
        return name;
    }


    virtual void display();
    virtual void cook_recipe() = 0;
    virtual void change_aroma() = 0;
};

class Herb : public Spice {
private:
    string culinary_use;

public:
    Herb(string _name, SpiceColor _color, string _taste, string _aroma, string _culinary_use);
    virtual ~Herb() {}
    string getName() const { return name; }


    void display() override;
    void cook_recipe() override;
    void change_aroma() override;
};

class Powder : public Spice {
private:
    string form;

public:
    Powder(string _name, SpiceColor _color, string _taste, string _aroma, string _form);
    virtual ~Powder() {}
    string getName() const { return name; }


    void display() override;
    void cook_recipe() override;
    void change_aroma() override;
};

class Liquid : public Spice {
private:
    string viscosity;

public:
    Liquid(string _name, SpiceColor _color, string _taste, string _aroma, string _viscosity);
    virtual ~Liquid() {}
    string getName() const { return name; }


    void display() override;
    void cook_recipe() override;
    void change_aroma() override;
};






#endif // SPICES_H