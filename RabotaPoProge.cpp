#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "spices.h"
#include "spice_container.h"
#include "iterators.h"

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
        case SpiceColor::YELLOW:
            color_str = "Желтый";
            break;
        case SpiceColor::RED:
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

bool CompareSpicesByName(Spice* spice1, Spice* spice2) {
    return spice1->getName() < spice2->getName();
};

int main()
{
    setlocale(LC_ALL, "Russian");

    VectorSpiceContainer vectorContainer;
    ListSpiceContainer listContainer;
    SortingIterator<Spice*> sortedVectorIterator(new VectorSpiceContainerIterator(vectorContainer.getSpices()), CompareSpicesByName);
    SortingIterator<Spice*> sortedListIterator(new ListSpiceContainerIterator(listContainer.getSpicesList()), CompareSpicesByName);


    
    vectorContainer.addSpice(new Herb("Мята", SpiceColor::GREEN, "Освежающий", "Мятный", "Коктейли"));
    vectorContainer.addSpice(new Herb("Базилик", SpiceColor::GREEN, "Сладкий", "Травянистый", "Итальянская кухня"));
    vectorContainer.addSpice(new Herb("Тимьян", SpiceColor::GREEN, "Землянистый", "Травянистый", "Средиземноморская кухня"));
    vectorContainer.addSpice(new Powder("Кумин", SpiceColor::BROWN, "Землянистый", "Пряный", "Молотый"));
    vectorContainer.addSpice(new Powder("Паприка", SpiceColor::RED, "Сладкий", "Дымный", "Молотый"));
    vectorContainer.addSpice(new Liquid("Оливковое масло", SpiceColor::YELLOW, "Фруктовый", "Нежный", "Густой"));
    vectorContainer.addSpice(new Liquid("Соевый соус", SpiceColor::DARK, "Соленый", "Умами", "Жидкий"));

    listContainer.addSpice(new Herb("Розмарин", SpiceColor::GREEN, "Хвойный", "Древесный", "Средиземноморская кухня"));
    listContainer.addSpice(new Herb("Орегано", SpiceColor::GREEN, "Горький", "Пронзающий", "Средиземноморская кухня"));
    listContainer.addSpice(new Herb("Укроп", SpiceColor::GREEN, "Свежий", "Травянистый", "Скандинавская кухня"));
    listContainer.addSpice(new Powder("Карри", SpiceColor::YELLOW, "Пряный", "Ароматный", "Молотый"));
    listContainer.addSpice(new Powder("Чили", SpiceColor::RED, "Пряный", "Дымный", "Молотый"));
    listContainer.addSpice(new Liquid("Бальзамический уксус", SpiceColor::DARK, "Кислый", "Сладкий", "Густой"));
    listContainer.addSpice(new Liquid("Соус Ворчестер", SpiceColor::DARK, "Кислый", "Сложный", "Жидкий"));


    cout << "_________________________________________________________________________________" << endl;
    
    cout << "Содержимое векторного контейнера:" << endl;
    VectorSpiceContainerIterator vectorIterator(vectorContainer.getSpices());
    for (vectorIterator.First(); !vectorIterator.IsDone(); vectorIterator.Next()) {
        vectorIterator.GetCurrent()->display();
        cout << endl;
    };
    
    cout << "__________________________________________________________________________________" << endl;
    
    cout << "Содержимое списочного контейнера : " << endl;
    ListSpiceContainerIterator listIterator(listContainer.getSpices());
    for (listIterator.First(); !listIterator.IsDone(); listIterator.Next()) {
        listIterator.GetCurrent()->display();
        cout << endl;
    };
    
    cout << "___________________________________________________________________________________" << endl;

    cout << "Содержимое векторного контейнера после сортировки:" << endl;
    for (sortedVectorIterator.First(); !sortedVectorIterator.IsDone(); sortedVectorIterator.Next()) {
        sortedVectorIterator.GetCurrent()->display();
        cout << endl;
    };
    
    cout << "___________________________________________________________________________________" << endl;


    cout << "Содержимое списочного контейнера после сортировки:" << endl;
    for (sortedListIterator.First(); !sortedListIterator.IsDone(); sortedListIterator.Next()) {
        sortedListIterator.GetCurrent()->display();
        cout << endl;
    };


    return 0;
}

