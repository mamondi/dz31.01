#include <iostream>
#include <string>

using namespace std;

class Violation {
public:
    string violationDetails;
    Violation* nextViolation;

    Violation(const string& details) : violationDetails(details), nextViolation(nullptr) {}
    ~Violation() {
        delete nextViolation;
    }
};

class Node {
public:
    string carNumber;
    Violation* violationsList;
    Node* left;
    Node* right;

    Node(const string& number, const string& violationDetails)
        : carNumber(number), left(nullptr), right(nullptr) {
        violationsList = new Violation(violationDetails);
    }

    ~Node() {
        delete violationsList;
        delete left;
        delete right;
    }
};

class Database {
private:
    Node* root;

    Node* insert(Node* node, const string& carNumber, const string& violationDetails);
    void printDatabase(Node* node);
    void printDataByNumber(Node* node, const string& carNumber);
    void printDataInRange(Node* node, const string& startNumber, const string& endNumber);

public:
    Database() : root(nullptr) {}
    ~Database();

    void addViolation(const string& carNumber, const string& violationDetails);
    void printFullDatabase();
    void printDataByCarNumber(const string& carNumber);
    void printDataInRange(const string& startNumber, const string& endNumber);
};

Database::~Database() {
    delete root;
}

Node* Database::insert(Node* node, const string& carNumber, const string& violationDetails) {
    if (node == nullptr) {
        return new Node(carNumber, violationDetails);
    }

    if (carNumber < node->carNumber) {
        node->left = insert(node->left, carNumber, violationDetails);
    }
    else if (carNumber > node->carNumber) {
        node->right = insert(node->right, carNumber, violationDetails);
    }
    else {
        // Car number already exists, add violation to the list
        Violation* newViolation = new Violation(violationDetails);
        newViolation->nextViolation = node->violationsList;
        node->violationsList = newViolation;
    }

    return node;
}

void Database::addViolation(const string& carNumber, const string& violationDetails) {
    root = insert(root, carNumber, violationDetails);
}

void Database::printDatabase(Node* node) {
    if (node != nullptr) {
        printDatabase(node->left);
        cout << "Car Number: " << node->carNumber << "\n";
        cout << "Violations:\n";
        Violation* violation = node->violationsList;
        while (violation != nullptr) {
            cout << "  - " << violation->violationDetails << "\n";
            violation = violation->nextViolation;
        }
        cout << "\n";
        printDatabase(node->right);
    }
}

void Database::printFullDatabase() {
    printDatabase(root);
}

void Database::printDataByNumber(Node* node, const string& carNumber) {
    if (node != nullptr) {
        if (carNumber < node->carNumber) {
            printDataByNumber(node->left, carNumber);
        }
        else if (carNumber > node->carNumber) {
            printDataByNumber(node->right, carNumber);
        }
        else {
            cout << "Car Number: " << node->carNumber << "\n";
            cout << "Violations:\n";
            Violation* violation = node->violationsList;
            while (violation != nullptr) {
                cout << "  - " << violation->violationDetails << "\n";
                violation = violation->nextViolation;
            }
            cout << "\n";
        }
    }
    else {
        cout << "Car Number not found.\n";
    }
}

void Database::printDataByCarNumber(const string& carNumber) {
    printDataByNumber(root, carNumber);
}

void Database::printDataInRange(Node* node, const string& startNumber, const string& endNumber) {
    if (node != nullptr) {
        if (node->carNumber >= startNumber) {
            printDataInRange(node->left, startNumber, endNumber);
        }
        if (node->carNumber >= startNumber && node->carNumber <= endNumber) {
            cout << "Car Number: " << node->carNumber << "\n";
            cout << "Violations:\n";
            Violation* violation = node->violationsList;
            while (violation != nullptr) {
                cout << "  - " << violation->violationDetails << "\n";
                violation = violation->nextViolation;
            }
            cout << "\n";
        }
        if (node->carNumber <= endNumber) {
            printDataInRange(node->right, startNumber, endNumber);
        }
    }
}

void Database::printDataInRange(const string& startNumber, const string& endNumber) {
    printDataInRange(root, startNumber, endNumber);
}


