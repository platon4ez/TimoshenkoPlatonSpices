#ifndef SPICE_DATABASE_H
#define SPICE_DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

class SpiceDatabase {
public:
    SpiceDatabase(const std::string& dbName) : db(nullptr) {
        int result = sqlite3_open(dbName.c_str(), &db);
        if (result != SQLITE_OK) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            db = nullptr;
        }
        else {
            createTable();
            fillDatabase();
        }
    }

    ~SpiceDatabase() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    std::vector<std::string> getAllSpices() {
        std::vector<std::string> spices;
        if (!db) {
            std::cerr << "Database is not open." << std::endl;
            return spices;
        }

        const char* sqlSelectAll = "SELECT Name FROM Spices";
        sqlite3_stmt* stmt;
        int result = sqlite3_prepare_v2(db, sqlSelectAll, -1, &stmt, nullptr);
        if (result != SQLITE_OK) {
            std::cerr << "Error preparing select statement: " << sqlite3_errmsg(db) << std::endl;
            return spices;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* name = sqlite3_column_text(stmt, 0);
            if (name) {
                spices.push_back(std::string(reinterpret_cast<const char*>(name)));
            }
        }

        sqlite3_finalize(stmt);
        return spices;
    }

private:
    sqlite3* db;

    void createTable() {
        const char* sqlCreateTable = R"(
            CREATE TABLE IF NOT EXISTS Spices (
                Id INTEGER PRIMARY KEY AUTOINCREMENT,
                Name TEXT NOT NULL,
                Color TEXT NOT NULL,
                Taste TEXT NOT NULL,
                Smell TEXT NOT NULL,
                Use TEXT NOT NULL
            )
        )";

        char* errMsg = nullptr;
        int result = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
        if (result != SQLITE_OK) {
            std::cerr << "Error creating table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    void fillDatabase() {
        const char* sqlInsert = R"(
            INSERT INTO Spices (Name, Color, Taste, Smell, Use) VALUES
            ('Pepper', 'Green', 'Spicy', 'Pungent', 'Seasoning'),
            ('Cinnamon', 'Brown', 'Sweet', 'Fragrant', 'Baking'),
            ('Turmeric', 'Yellow', 'Bitter', 'Earthy', 'Cooking'),
            ('Ginger', 'Brown', 'Spicy', 'Aromatic', 'Medicine'),
            ('Saffron', 'Yellow', 'Bitter', 'Aromatic', 'Seasoning'),
            ('Clove', 'Brown', 'Sweet', 'Strong', 'Seasoning'),
            ('Cumin', 'Brown', 'Earthy', 'Nutty', 'Cooking'),
            ('Cardamom', 'Green', 'Sweet', 'Fragrant', 'Cooking'),
            ('Nutmeg', 'Brown', 'Nutty', 'Sweet', 'Baking'),
            ('Paprika', 'Red', 'Sweet', 'Mild', 'Seasoning')
        )";

        char* errMsg = nullptr;
        int result = sqlite3_exec(db, sqlInsert, nullptr, nullptr, &errMsg);
        if (result != SQLITE_OK) {
            std::cerr << "Error inserting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
};

#endif // SPICE_DATABASE_H
