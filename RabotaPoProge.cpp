#include "spices.h"
#include <iostream>

using namespace std;


Spice::Spice(string _name, SpiceColor _color, string _taste, string _aroma) : name(_name), color(_color), taste(_taste), aroma(_aroma) {}

void Spice::display() {
    string color_str;
    switch (color) {
        case SpiceColor::GREEN:
            color_str = "Зеленый";
            break;
        case SpiceColor::BROWN:
            color_str = "Коричневый";
            break;
        case SpiceColor::DARK:
            color_str = "Темный";
            break;
    }
    cout << name << ": " << color_str << ", " << taste << " вкус, " << aroma << " запах";
};

Herb::Herb(string _name, SpiceColor _color, string _taste, string _aroma, string _culinary_use) : Spice(_name, _color, _taste, _aroma), culinary_use(_culinary_use) {}

void Herb::display() {
    Spice::display();
    cout << ", используется в " << culinary_use << endl;
};

void Herb::cook_recipe() {
    cout << "Делаем сбор трав из " << name << endl;
};

void  Herb::change_aroma() {
    cout << "Добавляем ароматные травы, чтобы усилить запах " << name << "." << endl;
};

Powder::Powder(string _name, SpiceColor _color, string _taste, string _aroma, string _form) : Spice(_name, _color, _taste, _aroma), form(_form) {}

void Powder::display() {
    Spice::display();
    cout << ", в " << form << " форме" << endl;
};

void Powder::cook_recipe() {
    cout << "Добавляем " << name << " в блюдо" << endl;
};

void Powder::change_aroma() {
    cout << "Растолочь " << name << " в меньшую пыльцу, чтобы усилить аромат." << endl;
};

Liquid::Liquid(string _name, SpiceColor _color, string _taste, string _aroma, string _viscosity) : Spice(_name, _color, _taste, _aroma), viscosity(_viscosity){}

void Liquid::display() {
    Spice::display();
    cout << ", " << viscosity << " вязкость" << endl;
};
void Liquid::cook_recipe() {
    cout << "Добавляем " << name << " в блюдо " << endl;
};

void Liquid::change_aroma() {
    cout << "Добавляем ароматные масла в " << name << "." << endl;
};


int main()
{
    setlocale(LC_ALL, "Russian");
    Herb basil("Базилик", SpiceColor::GREEN, "Сладкий", "Травянистый", "Итальянская кухня");
    Powder cumin("Зира", SpiceColor::BROWN, "Землянистый", "Пряный", "Молотый");
    Liquid soy_sauce("Соевый соус", SpiceColor::DARK, "Соленый", "Многокомпонентен", "Слабая");

    cout << "Информация о специях:" << endl;
    basil.display();
    cumin.display();
    soy_sauce.display();
    cout << endl;
    
    cout << "Рецепт:" << endl;
    basil.cook_recipe();
    cumin.cook_recipe();
    soy_sauce.cook_recipe();
    cout << endl;

    cout << "Смена аромата:" << endl;
    basil.change_aroma();
    cumin.change_aroma();
    soy_sauce.change_aroma();

    return 0;
}
