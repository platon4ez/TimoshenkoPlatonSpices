#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "spices.h" // Включите ваш файл заголовка, содержащий определение Spice и других классов

using namespace std;

class SpiceDatabase {
public:
    SpiceDatabase(const string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        }
        else {
            createTable();
            insertSampleData();
        }
    }

    ~SpiceDatabase() {
        sqlite3_close(db);
    }

private:
    sqlite3* db;

    void createTable() {
        const char* sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS Spices (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Name TEXT NOT NULL,
            Color TEXT NOT NULL,
            Taste TEXT NOT NULL,
            Smell TEXT NOT NULL,
            Use TEXT NOT NULL
        );
        )";

        char* errMsg = nullptr;
        if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            cerr << "Error creating table: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }

    void insertSampleData() {
        vector<vector<string>> sampleData = {
            {"Mint", "Green", "Refreshing", "Minty", "Cocktails"},
            {"Basil", "Green", "Sweet", "Herbaceous", "Italian Cuisine"},
            {"Thyme", "Green", "Earthy", "Pungent", "Mediterranean Cuisine"},
            {"Rosemary", "Green", "Pine", "Woody", "Mediterranean Cuisine"},
            {"Oregano", "Green", "Bitter", "Herbaceous", "Mediterranean Cuisine"},
            {"Dill", "Green", "Fresh", "Herbaceous", "Scandinavian Cuisine"},
            {"Cumin", "Brown", "Earthy", "Spicy", "Ground"},
            {"Paprika", "Brown", "Sweet", "Smoky", "Culinary"},
            {"Curry", "Brown", "Spicy", "Aromatic", "Culinary"},
            {"Chili", "Brown", "Spicy", "Smoky", "Culinary"}
        };

        for (const auto& spice : sampleData) {
            insertSpice(spice[0], spice[1], spice[2], spice[3], spice[4]);
        }
    }

    void insertSpice(const string& name, const string& color, const string& taste, const string& smell, const string& use) {
        const char* sqlInsert = R"(
        INSERT INTO Spices (Name, Color, Taste, Smell, Use)
        VALUES (?, ?, ?, ?, ?);
        )";

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, color.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, taste.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, smell.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, use.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
            }

            sqlite3_finalize(stmt);
        }
        else {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        }
    }
};

int main() {
    SpiceDatabase db("spices.db");

    return 0;
}
