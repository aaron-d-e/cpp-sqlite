#include <stdio.h>
#include <sqlite3.h>
#include <iostream>

using namespace std;

/*
typedef int (*sqlite3_callback)(
   void*,    // Data provided in the 4th argument of sqlite3_exec()
   int,      // The number of columns in row
   char**,   // An array of strings representing fields in the row
   char**    // An array of strings representing column names
);

If the above callback is provided in sqlite_exec() routine as the third
argument, SQLite will call this callback function for each record processed in
each SELECT statement executed within the SQL argument
*/

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
    const char* data = "Callback function called";

    rc = sqlite3_open("test.db", &db);

    if (rc) {
        cout << "Can't open database." << sqlite3_errmsg(db) << endl;
        return 0;
    }
    else {
        cout << "Opened database" << endl;
    }

    sql = "SELECT * from COMPANY";

    rc = sqlite3_exec(db, sql, callback, 0, &zerrmsg);

    if (rc != SQLITE_OK) {
        cout << "SQL error" << " " << zerrmsg << endl;
    }
    else {
        cout << "Operation success" << endl;
    }

    sqlite3_close(db);
}
