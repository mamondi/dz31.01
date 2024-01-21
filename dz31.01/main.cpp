#include "tree.h"

int main() {
    Database database;

    while (true) {
        cout << "Choose an action:\n";
        cout << "1. Add Violation\n";
        cout << "2. Print Full Database\n";
        cout << "3. Print Data by Car Number\n";
        cout << "4. Print Data in Range\n";
        cout << "5. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string carNumber, violationDetails;
            cout << "Enter Car Number: ";
            cin >> carNumber;
            cout << "Enter Violation Details: ";
            cin.ignore();
            getline(cin, violationDetails);
            database.addViolation(carNumber, violationDetails);
            break;
        }
        case 2:
            database.printFullDatabase();
            break;
        case 3: {
            string carNumber;
            cout << "Enter Car Number: ";
            cin >> carNumber;
            database.printDataByCarNumber(carNumber);
            break;
        }
        case 4: {
            string startNumber, endNumber;
            cout << "Enter Start Car Number: ";
            cin >> startNumber;
            cout << "Enter End Car Number: ";
            cin >> endNumber;
            database.printDataInRange(startNumber, endNumber);
            break;
        }
        case 5:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}