#include "Employee.h"													// Defines class Employee
#include "Map.h"// Defines template Map<Key, Value>
#include "BookData.h"
#include <iostream>

typedef unsigned int ID; 												// Identification number of employee
typedef Map<ID, Employee> Database; 									// Database of employees
typedef std::string name;                                                      // 
typedef Map<name, BookData> Lib;
using namespace std;

void addEmployees(Database& database);
void modifyEmployees(Database& database);
void DatabaseTest(){
  Database database;
	addEmployees(database);

	Database newDatabase = database;									// Make a copy of database
	newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));	// Add fourth employee
	modifyEmployees(newDatabase);

	cout << "Original database:" << endl << database << endl;
	cout << "Modified database:" << endl << newDatabase << endl;

	database = newDatabase;												// Update original database

	cout << "Database after the assignment:" << endl << database << endl;

}
void BooksTest(){
  Lib libr;
  libr.add("new book", BookData("author", "cat", 42));
  libr.add("another new book", BookData("another author", "another cat", 42, true));
  cout << "Before: " << endl;
  cout << libr << endl;
  BookData *bd = libr.find("new book");
  bd->pages = 52;
  bd->taken = true;
  bd->category="found category";
  cout << "After: " << endl;
  cout << libr << endl;
}
int main() {
  cout << "----------------db---------------" << endl;
  DatabaseTest();
  cout << "-------------books---------------" << endl;
  BooksTest();
  return 0;
};

void addEmployees(Database& database) {
	database.add(761028073, Employee("Jan Kowalski", "salesman", 28)); 	// Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));	// Add second employee
	database.add(730505129, Employee("Anna Zaradna", "secretary", 32));	// Add third employee
}

void modifyEmployees(Database& database) {
	Employee* employeePtr;

	employeePtr = database.find(510212881);								// Find employee using its ID
	employeePtr->position = "salesman";									// Modify the position of employee
	
	employeePtr = database.find(761028073);								// Find employee using its ID
	employeePtr->age = 29;												// Modify the age of employee
}
