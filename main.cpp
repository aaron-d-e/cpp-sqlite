#include <stdio.h>
#include <sqlite3.h>
#include <iostream>

using namespace std;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    cout << endl;

    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    char* zerrmsg = 0;
    int rc;
    char* sql;

    rc = sqlite3_open("test.db", &db);

    if (rc) {
        cout << "Can't open database." << sqlite3_errmsg(db) << endl;
        return 0;
    }
    else {
        cout << "Opened database" << endl;
    }

    sql =
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    rc = sqlite3_exec(db, sql, callback, 0, &zerrmsg);

    if (rc != SQLITE_OK) {
        cout << "SQL error" << " " << zerrmsg << endl;
    }
    else {
        cout << "Record created successfully" << endl;
    }

    sqlite3_close(db);
}
