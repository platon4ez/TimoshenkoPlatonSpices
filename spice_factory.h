#ifndef SPICE_FACTORY_H
#define SPICE_FACTORY_H

#include "spices.h"
#include <vector>
#include <cstdlib>

class SpiceFactory {
public:
    static Spice* createRandomSpice() {
        int type = rand() % 3;
        switch (type) {
        case 0: return createRandomHerb();
        case 1: return createRandomPowder();
        case 2: return createRandomLiquid();
        default: return nullptr;
        }
    }

private:
    static Herb* createRandomHerb() {
        static const vector<string> herbNames = { "Mint", "Basil", "Thyme", "Rosemary", "Oregano", "Dill" };
        static const vector<string> herbTastes = { "Refreshing", "Sweet", "Earthy", "Woody", "Bitter", "Fresh" };
        static const vector<string> herbSmells = { "Minty", "Herbaceous", "Pungent", "Woody" };
        static const vector<string> herbUses = { "Cocktails", "Italian Cuisine", "Mediterranean Cuisine", "Scandinavian Cuisine" };

        string name = herbNames[rand() % herbNames.size()];
        string taste = herbTastes[rand() % herbTastes.size()];
        string smell = herbSmells[rand() % herbSmells.size()];
        string use = herbUses[rand() % herbUses.size()];

        return new Herb(name, SpiceColor::GREEN, taste, smell, use);
    }

    static Powder* createRandomPowder() {
        static const vector<string> powderNames = { "Cumin", "Paprika", "Curry", "Chili" };
        static const vector<string> powderTastes = { "Earthy", "Sweet", "Spicy" };
        static const vector<string> powderSmells = { "Spicy", "Smoky", "Aromatic" };
        static const vector<string> powderUses = { "Ground", "Cooking" };

        string name = powderNames[rand() % powderNames.size()];
        string taste = powderTastes[rand() % powderTastes.size()];
        string smell = powderSmells[rand() % powderSmells.size()];
        string use = powderUses[rand() % powderUses.size()];

        return new Powder(name, SpiceColor::BROWN, taste, smell, use);
    }

    static Liquid* createRandomLiquid() {
        static const vector<string> liquidNames = { "Olive Oil", "Soy Sauce", "Balsamic Vinegar", "Worcestershire Sauce" };
        static const vector<string> liquidTastes = { "Fruity", "Salty", "Sour" };
        static const vector<string> liquidSmells = { "Delicate", "Umami", "Sweet", "Complex" };
        static const vector<string> liquidUses = { "Thick", "Liquid" };

        string name = liquidNames[rand() % liquidNames.size()];
        string taste = liquidTastes[rand() % liquidTastes.size()];
        string smell = liquidSmells[rand() % liquidSmells.size()];
        string use = liquidUses[rand() % liquidUses.size()];

        return new Liquid(name, SpiceColor::YELLOW, taste, smell, use);
    }
};

#endif // SPICE_FACTORY_H
