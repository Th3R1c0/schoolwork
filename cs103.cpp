#include <iostream>
#include <sqlite_modern_cpp.h>

using namespace sqlite;
using namespace std;

int main() {
    try {
        // creates a database file 'dbfile.db' if it does not exist.
        database db("dbfile.db");

        // executes the query and creates a 'users' table
        db <<
            "CREATE TABLE IF NOT EXISTS users ("
            "   id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "   username TEXT,"
            "   password TEXT,"
            "   role TEXT"
            ");";

        // takes user input for username, password, and role
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        // roles admin, teacher or student
        cout << "Enter role: ";
        cin >> role;

        // inserts the user information into the 'users' table
        db << "INSERT INTO users (username, password, role) VALUES (?, ?, ?);"
           << username
           << password
           << role;

        cout << "User information stored successfully.\n";

        // displays all users in the 'users' table
        cout << "Users in the database:\n";
        db << "SELECT * FROM users;" >> [&](int id, string username, string password, string role) {
            cout << "ID: " << id << ", Username: " << username << ", Role: " << role << "\n";
        };

    } catch (const exception &e) {
        cout << "SQLite error: " << e.what() << endl;
    }

    return 0;
}
