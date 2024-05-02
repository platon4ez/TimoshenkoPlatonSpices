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
    string getName() const { return name; }
    SpiceColor getColor() const { return color; }
    string getTaste() const { return taste; }
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
    string getTaste() const { return taste; }

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
    string getTaste() const { return taste; }

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
    string getTaste() const { return taste; }

    void display() override;
    void cook_recipe() override;
    void change_aroma() override;
};

Spice::Spice(string _name, SpiceColor _color, string _taste, string _aroma) : name(_name), color(_color), taste(_taste), aroma(_aroma) {}

void Spice::display() {
    string color_str;
    switch (color) {
    case SpiceColor::GREEN:
        color_str = "�������";
        break;
    case SpiceColor::BROWN:
        color_str = "����������";
        break;
    case SpiceColor::DARK:
        color_str = "������";
        break;
    case SpiceColor::YELLOW:
        color_str = "������";
        break;
    case SpiceColor::RED:
        color_str = "������";
        break;
    }
    cout << name << ": " << color_str << ", " << taste << " ����, " << aroma << " �����";
}

Herb::Herb(string _name, SpiceColor _color, string _taste, string _aroma, string _culinary_use) : Spice(_name, _color, _taste, _aroma), culinary_use(_culinary_use) {}

void Herb::display() {
    Spice::display();
    cout << ", ������������ � " << culinary_use << endl;
}

void Herb::cook_recipe() {
    cout << "������ ���� ���� �� " << name << endl;
}

void  Herb::change_aroma() {
    cout << "��������� ��������� �����, ����� ������� ����� " << name << "." << endl;
}

Powder::Powder(string _name, SpiceColor _color, string _taste, string _aroma, string _form) : Spice(_name, _color, _taste, _aroma), form(_form) {}

void Powder::display() {
    Spice::display();
    cout << ", � " << form << " �����" << endl;
}

void Powder::cook_recipe() {
    cout << "��������� " << name << " � �����" << endl;
}

void Powder::change_aroma() {
    cout << "��������� " << name << " � ������� ������, ����� ������� ������." << endl;
}

Liquid::Liquid(string _name, SpiceColor _color, string _taste, string _aroma, string _viscosity) : Spice(_name, _color, _taste, _aroma), viscosity(_viscosity) {}

void Liquid::display() {
    Spice::display();
    cout << ", " << viscosity << " ��������" << endl;
}

void Liquid::cook_recipe() {
    cout << "��������� " << name << " � ����� " << endl;
}

void Liquid::change_aroma() {
    cout << "��������� ��������� ����� � " << name << "." << endl;
}




#endif // SPICES_H