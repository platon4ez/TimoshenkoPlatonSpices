#ifndef SPICE_DATABASE_H
#define SPICE_DATABASE_H

#include <sqlite3.h>
#include "spices.h"

class SpiceDatabase {
private:
    sqlite3* db;

    static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

public:
    SpiceDatabase(const char* filename) {
        int rc = sqlite3_open(filename, &db);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else {
            fprintf(stdout, "Opened database successfully\n");
        }
    }

    ~SpiceDatabase() {
        sqlite3_close(db);
    }

    void createTable() {
        char* errorMessage;
        const char* sql = "CREATE TABLE SPICES(" \
            "ID INT PRIMARY KEY     NOT NULL," \
            "NAME           TEXT    NOT NULL," \
            "COLOR          TEXT    NOT NULL," \
            "TASTE          TEXT    NOT NULL," \
            "SMELL          TEXT    NOT NULL," \
            "USE            TEXT    NOT NULL);";

        int rc = sqlite3_exec(db, sql, callback, 0, &errorMessage);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errorMessage);
            sqlite3_free(errorMessage);
        }
        else {
            fprintf(stdout, "Table created successfully\n");
        }
    }

    void insertSpice(int id, const char* name, const char* color, const char* taste, const char* smell, const char* use) {
        char sql[512];
        sprintf(sql, "INSERT INTO SPICES (ID, NAME, COLOR, TASTE, SMELL, USE) " \
            "VALUES (%d, '%s', '%s', '%s', '%s', '%s');", id, name, color, taste, smell, use);

        char* errorMessage;
        int rc = sqlite3_exec(db, sql, callback, 0, &errorMessage);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errorMessage);
            sqlite3_free(errorMessage);
        }
        else {
            fprintf(stdout, "Records created successfully\n");
        }
    }
};

#endif // SPICE_DATABASE_H
