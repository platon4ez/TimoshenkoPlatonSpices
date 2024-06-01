#ifndef SPICE_DATABASE_CONTAINER_H
#define SPICE_DATABASE_CONTAINER_H

#include <sqlite3.h>
#include <list>
#include <string>
#include <iostream>
#include "spices.h"
#include "iterators.h"

class SpiceDatabaseContainer {
public:
    SpiceDatabaseContainer(const std::string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    ~SpiceDatabaseContainer() {
        sqlite3_close(db);
    }

    std::list<Spice*> getAllSpices() {
        std::list<Spice*> spices;
        const char* sqlSelectAll = "SELECT Name, Color, Taste, Smell, Use FROM Spices;";
        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(db, sqlSelectAll, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::string color = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string taste = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                std::string smell = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                std::string use = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

                SpiceColor spiceColor;
                if (color == "Green") {
                    spiceColor = SpiceColor::GREEN;
                }
                else if (color == "Brown") {
                    spiceColor = SpiceColor::BROWN;
                }
                else {
                    spiceColor = SpiceColor::YELLOW; 
                }

                spices.push_back(new Spice(name, spiceColor, taste, smell, use));
            }
            sqlite3_finalize(stmt);
        }
        else {
            std::cerr << "Error preparing select statement: " << sqlite3_errmsg(db) << std::endl;
        }
        return spices;
    }

private:
    sqlite3* db;
};

class SpiceDatabaseIterator : public Iterator<Spice*> {
public:
    SpiceDatabaseIterator(std::list<Spice*>& spices) : spices(spices), current(spices.begin()) {}

    void First() override {
        current = spices.begin();
    }

    void Next() override {
        ++current;
    }

    bool IsDone() override {
        return current == spices.end();
    }

    Spice* GetCurrent() override {
        return *current;
    }

private:
    std::list<Spice*>& spices;
    std::list<Spice*>::iterator current;
};

#endif // SPICE_DATABASE_CONTAINER_H
