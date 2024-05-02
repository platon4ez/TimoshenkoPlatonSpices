#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "spices.h"
#include "spice_container.h"
#include "iterators.h"

using namespace std;



bool CompareSpicesByName(Spice* spice1, Spice* spice2) {
    return spice1->getName() < spice2->getName();
}

bool CompareSpicesByColor(Spice* spice1, Spice* spice2) {
    return spice1->getColor() < spice2->getColor();
}

bool CompareSpicesByTaste(Spice* spice1, Spice* spice2) {
    return spice1->getTaste() < spice2->getTaste();
}

class TasteSortIterator : public SortingIterator<Spice*> {
public:
    TasteSortIterator(Iterator<Spice*>* iterator) : SortingIterator<Spice*>(iterator, CompareSpicesByTaste) {}
};

int main() {
    setlocale(LC_ALL, "Russian");

    VectorSpiceContainer vectorContainer;
    list<Spice*> listSpices;

    vectorContainer.addSpice(new Herb("Мята", SpiceColor::GREEN, "Освежающий", "Мятный", "Коктейли"));
    vectorContainer.addSpice(new Herb("Базилик", SpiceColor::GREEN, "Сладкий", "Травянистый", "Итальянская кухня"));
    vectorContainer.addSpice(new Herb("Тимьян", SpiceColor::GREEN, "Землянистый", "Травянистый", "Средиземноморская кухня"));
    vectorContainer.addSpice(new Powder("Зира", SpiceColor::BROWN, "Землянистый", "Пряный", "Молотый"));
    vectorContainer.addSpice(new Powder("Паприка", SpiceColor::RED, "Сладкий", "Дымный", "Молотый"));
    vectorContainer.addSpice(new Liquid("Оливковое масло", SpiceColor::YELLOW, "Фруктовый", "Нежный", "Густой"));
    vectorContainer.addSpice(new Liquid("Соевый соус", SpiceColor::DARK, "Соленый", "Умами", "Жидкий"));

    listSpices.push_back(new Herb("Розмарин", SpiceColor::GREEN, "Хвойный", "Древесный", "Средиземноморская кухня"));
    listSpices.push_back(new Herb("Орегано", SpiceColor::GREEN, "Горький", "Пронзающий", "Средиземноморская кухня"));
    listSpices.push_back(new Herb("Укроп", SpiceColor::GREEN, "Свежий", "Травянистый", "Скандинавская кухня"));
    listSpices.push_back(new Powder("Карри", SpiceColor::YELLOW, "Пряный", "Ароматный", "Молотый"));
    listSpices.push_back(new Powder("Чили", SpiceColor::RED, "Пряный", "Дымный", "Молотый"));
    listSpices.push_back(new Liquid("Бальзамический уксус", SpiceColor::DARK, "Кислый", "Сладкий", "Густой"));
    listSpices.push_back(new Liquid("Вустерский соус", SpiceColor::DARK, "Кислый", "Сложный", "Жидкий"));

    cout << "Содержимое векторного контейнера после фильтрации по цвету и сортировки по имени:" << endl;
    VectorSpiceContainerIterator vectorIterator(vectorContainer.getSpices());
    vector<Spice*> filteredAndSortedVectorSpices;
    vector<Spice*> notFilteredSpices;
    for (vectorIterator.First(); !vectorIterator.IsDone(); vectorIterator.Next()) {
        Spice* spice = vectorIterator.GetCurrent();
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
        cout << endl;
    }

    cout << "Не прошедшие отбор из векторного контейнера:" << endl;
    for (Spice* spice : notFilteredSpices) {
        spice->display();
        cout << endl;
    }

    cout << "Сортировка специй по вкусу для не отфильтрованных специй:" << endl;
    vector<Spice*> notFilteredAndNotSortedSpices;
    for (Spice* spice : notFilteredSpices) {
        notFilteredAndNotSortedSpices.push_back(spice);
    }
    
    TasteSortIterator tasteSortedIterator(new VectorSpiceContainerIterator(notFilteredAndNotSortedSpices));
    for (tasteSortedIterator.First(); !tasteSortedIterator.IsDone(); tasteSortedIterator.Next()) {
        tasteSortedIterator.GetCurrent()->display();
        cout << endl;
    }

    cout << "Содержимое лист контейнера после фильтрации по цвету и сортировки по имени:" << endl;
    ListSpiceContainerIterator listIterator(listSpices);
    list<Spice*> filteredAndSortedlistSpices;
    list<Spice*> notFilteredlistSpices;
    for (listIterator.First(); !listIterator.IsDone(); listIterator.Next()) {
        Spice* spice = listIterator.GetCurrent();
        if (spice->getColor() == SpiceColor::GREEN) {
            filteredAndSortedlistSpices.push_back(spice);
        }
        else {
            notFilteredlistSpices.push_back(spice);
        }
    }
    filteredAndSortedlistSpices.sort(CompareSpicesByName);
    for (Spice* spice : filteredAndSortedlistSpices) {
        spice->display();
        cout << endl;
    }

    cout << "Не прошедшие отбор из лист контейнера" << endl;
    for (Spice* spice : notFilteredlistSpices) {
        spice->display();
        cout << endl;
    }

    return 0;
}
