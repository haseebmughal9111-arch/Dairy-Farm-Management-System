#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

bool login() 
{
    string username, password;
    cout << "\n========================== LOGIN =========================="<<endl;
    cout<<"Username: ";
	 cin >> username;
    cout << "Password: "; 
	cin >> password;
	 cin.ignore(10000, '\n');
    if (username == "Pakistan" && password == "1947") { 
	cout << "\nLogin Successful!\n"; return true; }
    cout << "\nInvalid username or password!\n"; return false;
}

struct Animal { int id; string type; string gender; float age; };
struct Milk { int id; int animalId; float quantity; string date; };
struct Feed { int id; int animalId; float quantity; string date; };
struct Health { int id; int animalId; string issue; string status; };
struct Sale { int id; int animalId; float amount; string date; }; 

const int MAX = 100;

Animal animals[MAX]; int totalAnimals = 0;
Milk milkRecords[MAX]; int totalMilk = 0;
Feed feedRecords[MAX]; int totalFeed = 0;
Health healthRecords[MAX]; int totalHealth = 0;
Sale saleRecords[MAX]; int totalSales = 0;

int getIntInput(string prompt, int minVal = -999999, int maxVal = 999999) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            if (val >= minVal && val <= maxVal) { 
                cin.ignore(10000, '\n'); 
                return val; 
            }
            cout << "Error: Value out of range."<<endl;
        } else {
            cout << "Error: Invalid input. Enter a number."<<endl; 
            cin.clear(); 
            cin.ignore(10000, '\n');
        }
    }
}

float getFloatInput(string prompt, float minVal = 0.0f) {
    float val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            if (val >= minVal) { 
                cin.ignore(10000, '\n'); 
                return val; 
            }
            cout << "Error: Value cannot be negative."<<endl;
        } else {
            cout << "Error: Invalid input. Enter a number."<<endl; 
            cin.clear(); 
            cin.ignore(10000, '\n');
        }
    }
}

string getStringInput(string prompt) {
    string val;
    while (true) {
        cout << prompt; 
        getline(cin, val);
        if (val != "") {
            for (size_t i = 0; i < val.length(); i++) {
                if (val[i] == ' ') val[i] = '_'; 
            }
            return val;
        }
        cout << "Error: Input cannot be blank"<<endl;
    }
}

string displayStr(string s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == '_') s[i] = ' '; 
    }
    return s;
}

string getDateInput(string prompt) { 
    string val;
    time_t t = time(0);
    tm* now = localtime(&t);
    int curY = now->tm_year + 1900;
    int curM = now->tm_mon + 1;
    int curD = now->tm_mday;

    while (true) {
        cout << prompt; 
        cin >> val; 
        cin.ignore(10000, '\n');
        
        if (val.length() != 10 || val[2] != '-' || val[5] != '-') {
            cout << "Error: Format must be DD-MM-YYYY (e.g. 05-08-2026)."<<endl;
            continue;
        }
        
        bool isNum = true;
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (val[i] < '0' || val[i] > '9') { isNum = false; break; }
        }
        if (!isNum) { cout << "Error: Only numbers allowed in date."<<endl; continue; }

        int dd = (val[0]-'0')*10 + (val[1]-'0');
        int mm = (val[3]-'0')*10 + (val[4]-'0');
        int yyyy = (val[6]-'0')*1000 + (val[7]-'0')*100 + (val[8]-'0')*10 + (val[9]-'0');
        
        if (yyyy < 2000 || yyyy > curY) { cout << "Error: Year must be between 2000 and " << curY << "."<<endl; continue; }
        if (mm < 1 || mm > 12) { cout << "Error: Month must be 01 to 12."<<endl; continue; }
        if (dd < 1 || dd > 31) { cout << "Error: Day must be 01 to 31."<<endl; continue; }
        
        if (yyyy == curY && (mm > curM || (mm == curM && dd > curD))) {
            cout << "Error: Date cannot be in the future."<<endl; continue;
        }
        
        return val; 
    }
}

string selectAnimalType() {
    cout << "\n1. Cow\n2. Buffalo\n3. Goat"<<endl;
    int choice = getIntInput("Choice (1-3): ", 1, 3);
    return (choice == 1) ? "Cow" : (choice == 2) ? "Buffalo" : "Goat";
}

string selectGender() {
    cout << "\n1. Female\n2. Male"<<endl;
    return (getIntInput("Choice (1-2): ", 1, 2) == 1) ? "Female" : "Male";
}

string selectHealthStatus() {
    cout << "\n1. Recovered\n2. Sick\n3. Treatment"<<endl;
    int choice = getIntInput("Choice (1-3): ", 1, 3);
    return (choice == 1) ? "Recovered" : (choice == 2) ? "Sick" : "Treatment";
}

bool animalExists(int id) { for (int i = 0; i < totalAnimals; i++) if (animals[i].id == id) return true; return false; }
bool milkRecordExists(int id) { for (int i = 0; i < totalMilk; i++) if (milkRecords[i].id == id) return true; return false; }
bool feedRecordExists(int id) { for (int i = 0; i < totalFeed; i++) if (feedRecords[i].id == id) return true; return false; }
bool healthRecordExists(int id) { for (int i = 0; i < totalHealth; i++) if (healthRecords[i].id == id) return true; return false; }
bool saleRecordExists(int id) { for (int i = 0; i < totalSales; i++) if (saleRecords[i].id == id) return true; return false; }

void saveData() {
    ofstream outFile("dairy_data.txt");
    if (!outFile) return;
    
    outFile << totalAnimals << endl;
    for (int i = 0; i < totalAnimals; i++) outFile << animals[i].id << " " << animals[i].type << " " << animals[i].gender << " " << animals[i].age << endl;
    
    outFile << totalMilk << endl;
    for (int i = 0; i < totalMilk; i++) outFile << milkRecords[i].id << " " << milkRecords[i].animalId << " " << milkRecords[i].quantity << " " << milkRecords[i].date << endl;
    
    outFile << totalFeed << endl;
    for (int i = 0; i < totalFeed; i++) outFile << feedRecords[i].id << " " << feedRecords[i].animalId << " " << feedRecords[i].quantity << " " << feedRecords[i].date << endl;
    
    outFile << totalHealth << endl;
    for (int i = 0; i < totalHealth; i++) outFile << healthRecords[i].id << " " << healthRecords[i].animalId << " " << healthRecords[i].issue << " " << healthRecords[i].status << endl;
    
    outFile << totalSales << endl;
    for (int i = 0; i < totalSales; i++) outFile << saleRecords[i].id << " " << saleRecords[i].animalId << " " << saleRecords[i].amount << " " << saleRecords[i].date << endl;
    
    outFile.close();
}

void loadData() {
    ifstream inFile("dairy_data.txt");
    if (!inFile) return;
    
    if (inFile >> totalAnimals) for (int i = 0; i < totalAnimals; i++) inFile >> animals[i].id >> animals[i].type >> animals[i].gender >> animals[i].age;
    if (inFile >> totalMilk) for (int i = 0; i < totalMilk; i++) inFile >> milkRecords[i].id >> milkRecords[i].animalId >> milkRecords[i].quantity >> milkRecords[i].date;
    if (inFile >> totalFeed) for (int i = 0; i < totalFeed; i++) inFile >> feedRecords[i].id >> feedRecords[i].animalId >> feedRecords[i].quantity >> feedRecords[i].date;
    if (inFile >> totalHealth) for (int i = 0; i < totalHealth; i++) inFile >> healthRecords[i].id >> healthRecords[i].animalId >> healthRecords[i].issue >> healthRecords[i].status;
    if (inFile >> totalSales) for (int i = 0; i < totalSales; i++) inFile >> saleRecords[i].id >> saleRecords[i].animalId >> saleRecords[i].amount >> saleRecords[i].date;
    
    inFile.close();
}

void addAnimal() {
    if (totalAnimals >= MAX) { cout << "Storage Full!"<<endl; return; }
    int id;
    while (true) { id = getIntInput("\nEnter Animal ID: ", 1); if (animalExists(id)) cout << "ID already exists!"<<endl; else break; }
    animals[totalAnimals].id = id;
    animals[totalAnimals].type = selectAnimalType();
    animals[totalAnimals].gender = selectGender();
    animals[totalAnimals].age = getFloatInput("Enter Age (yrs): ", 0.1f);
    totalAnimals++; cout << "Animal Added Successfully!"<<endl;
}

void viewAnimals() {
    if (totalAnimals == 0) { cout << "\nNo Records Found!\n"; return; }
    cout << "\n===================== ANIMAL RECORDS ======================\n";
    for (int i = 0; i < totalAnimals; i++) cout << "ID: " << animals[i].id << " | Type: " << animals[i].type << " | Gender: " << animals[i].gender << " | Age: " << animals[i].age << " yrs\n";
}

void searchAnimal() {
    if (totalAnimals == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Animal ID: ", 1);
    for (int i = 0; i < totalAnimals; i++) if (animals[i].id == id) { cout << "Found: " << animals[i].type << ", " << animals[i].gender << ", " << animals[i].age << " yrs\n"; return; }
    cout << "Animal Not Found!\n";
}

void updateAnimal() {
    if (totalAnimals == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Animal ID to Update: ", 1);
    for (int i = 0; i < totalAnimals; i++) if (animals[i].id == id) {
        animals[i].type = selectAnimalType(); animals[i].gender = selectGender(); animals[i].age = getFloatInput("Enter New Age: ", 0.1f);
        cout << "Updated Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void deleteAnimal() {
    if (totalAnimals == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Animal ID to Delete: ", 1);
    int idx = -1;
    for (int i = 0; i < totalAnimals; i++) { if (animals[i].id == id) { idx = i; break; } }
    
    if (idx != -1) {
    
        for (int i = 0; i < totalMilk; ) { if (milkRecords[i].animalId == id) { for (int j = i; j < totalMilk - 1; j++) milkRecords[j] = milkRecords[j+1]; totalMilk--; } else i++; }
        for (int i = 0; i < totalHealth; ) { if (healthRecords[i].animalId == id) { for (int j = i; j < totalHealth - 1; j++) healthRecords[j] = healthRecords[j+1]; totalHealth--; } else i++; }
        for (int i = 0; i < totalFeed; ) { if (feedRecords[i].animalId == id) { for (int j = i; j < totalFeed - 1; j++) feedRecords[j] = feedRecords[j+1]; totalFeed--; } else i++; }
        for (int i = 0; i < totalSales; ) { if (saleRecords[i].animalId == id) { for (int j = i; j < totalSales - 1; j++) saleRecords[j] = saleRecords[j+1]; totalSales--; } else i++; }
        
        for (int j = idx; j < totalAnimals - 1; j++) animals[j] = animals[j+1];
        totalAnimals--;
        cout << "Animal and ALL its related records deleted successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void animalMenu() {
    int c; do {
        cout << "\n==================== ANIMAL MANAGEMENT ====================\n1. Add\n2. View\n3. Search\n4. Update\n5. Delete\n6. Back"<<endl;
        c = getIntInput("Choice (1-6): ", 1, 6);
        if (c == 1) addAnimal(); else if (c == 2) viewAnimals(); else if (c == 3) searchAnimal(); else if (c == 4) updateAnimal(); else if (c == 5) deleteAnimal();
    } while (c != 6);
}

void addMilk() {
    if (totalMilk >= MAX || totalAnimals == 0) { cout << "Cannot add milk record!"<<endl; return; }
    int id, aId;
    while (true) { id = getIntInput("\nEnter Record ID: ", 1); if (milkRecordExists(id)) cout << "ID exists!"<<endl; else break; }
    
    bool isFemale = false;
    while (true) { 
        aId = getIntInput("Enter Animal ID: ", 1); 
        bool found = false;
        for (int i = 0; i < totalAnimals; i++) {
            if (animals[i].id == aId) { found = true; if (animals[i].gender == "Female") isFemale = true; break; }
        }
        if (!found) cout << "Animal ID doesn't exist!"<<endl;
        else if (!isFemale) cout << "Error: You cannot add a milk record for a Male animal!"<<endl; 
        else break;
    }
    
    milkRecords[totalMilk].id = id; milkRecords[totalMilk].animalId = aId;
    milkRecords[totalMilk].quantity = getFloatInput("Enter Liters: ", 0.1f);
    milkRecords[totalMilk].date = getDateInput("Enter Date (DD-MM-YYYY): ");
    totalMilk++; cout << "Milk Record Added!"<<endl;
}

void viewMilk() {
    if (totalMilk == 0) { cout << "\nNo Records Found!\n"; return; }
    cout << "\n====================== MILK RECORDS =======================\n";
    for (int i = 0; i < totalMilk; i++) cout << "ID: " << milkRecords[i].id << " | Animal ID: " << milkRecords[i].animalId << " | Qty: " << milkRecords[i].quantity << "L | Date: " << milkRecords[i].date << endl;
}

void searchMilk() {
    if (totalMilk == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Record ID: ", 1);
    for (int i = 0; i < totalMilk; i++) if (milkRecords[i].id == id) { cout << "Found! Animal ID: " << milkRecords[i].animalId << ", Qty: " << milkRecords[i].quantity << "L, Date: " << milkRecords[i].date << endl; return; }
    cout << "Record Not Found!"<<endl;
}

void updateMilk() {
    if (totalMilk == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Milk Record ID to Update: ", 1);
    for (int i = 0; i < totalMilk; i++) if (milkRecords[i].id == id) {
        milkRecords[i].quantity = getFloatInput("Enter New Liters: ", 0.1f); milkRecords[i].date = getDateInput("Enter New Date: ");
        cout << "Updated Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void deleteMilk() {
    if (totalMilk == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Milk Record ID to Delete: ", 1);
    for (int i = 0; i < totalMilk; i++) if (milkRecords[i].id == id) {
        for (int j = i; j < totalMilk - 1; j++) milkRecords[j] = milkRecords[j+1];
        totalMilk--; cout << "Deleted Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void milkMenu() {
    int c; do {
        cout << "\n===================== MILK MANAGEMENT =====================\n1. Add\n2. View\n3. Search\n4. Update\n5. Delete\n6. Back"<<endl;
        c = getIntInput("Choice (1-6): ", 1, 6);
        if (c == 1) addMilk(); else if (c == 2) viewMilk(); else if (c == 3) searchMilk(); else if (c == 4) updateMilk(); else if (c == 5) deleteMilk();
    } while (c != 6);
}

void addFeed() {
    if (totalFeed >= MAX || totalAnimals == 0) { cout << "Cannot add feed record! No animals exist."<<endl; return; }
    int id, aId;
    while (true) { id = getIntInput("\nEnter Feed Record ID: ", 1); if (feedRecordExists(id)) cout << "ID exists!"<<endl; else break; }
    while (true) { aId = getIntInput("Enter Animal ID: ", 1); if (!animalExists(aId)) cout << "Animal ID doesn't exist!"<<endl; else break; }
    
    feedRecords[totalFeed].id = id; feedRecords[totalFeed].animalId = aId;
    feedRecords[totalFeed].quantity = getFloatInput("Enter Quantity (Kg): ", 0.1f);
    feedRecords[totalFeed].date = getDateInput("Enter Date (DD-MM-YYYY): ");
    totalFeed++; cout << "Feed Record Added!"<<endl;
}

void viewFeed() {
    if (totalFeed == 0) { cout << "\nNo Records Found!\n"; return; }
    cout << "\n====================== FEED RECORDS =======================\n";
    for (int i = 0; i < totalFeed; i++) cout << "ID: " << feedRecords[i].id << " | Animal ID: " << feedRecords[i].animalId << " | Qty: " << feedRecords[i].quantity << "kg | Date: " << feedRecords[i].date << endl;
}

void searchFeed() {
    if (totalFeed == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Record ID: ", 1);
    for (int i = 0; i < totalFeed; i++) if (feedRecords[i].id == id) { cout << "Found! Animal ID: " << feedRecords[i].animalId << ", Qty: " << feedRecords[i].quantity << "kg, Date: " << feedRecords[i].date << endl; return; }
    cout << "Record Not Found!"<<endl;
}

void updateFeed() {
    if (totalFeed == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Feed Record ID: ", 1);
    for (int i = 0; i < totalFeed; i++) if (feedRecords[i].id == id) {
        feedRecords[i].quantity = getFloatInput("Enter New Qty: ", 0.1f); feedRecords[i].date = getDateInput("Enter New Date: ");
        cout << "Updated Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void deleteFeed() {
    if (totalFeed == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Feed Record ID to Delete: ", 1);
    for (int i = 0; i < totalFeed; i++) if (feedRecords[i].id == id) {
        for (int j = i; j < totalFeed - 1; j++) feedRecords[j] = feedRecords[j+1];
        totalFeed--; cout << "Deleted Successfully!"<<endl; return;
    }
    cout << "ID Not Found!\n";
}

void feedMenu() {
    int c; do {
        cout << "\n===================== FEED MANAGEMENT =====================\n1. Add\n2. View\n3. Search\n4. Update\n5. Delete\n6. Back"<<endl;
        c = getIntInput("Choice (1-6): ", 1, 6);
        if (c == 1) addFeed(); else if (c == 2) viewFeed(); else if (c == 3) searchFeed(); else if (c == 4) updateFeed(); else if (c == 5) deleteFeed();
    } while (c != 6);
}

void addHealth() {
    if (totalHealth >= MAX || totalAnimals == 0) { cout << "Cannot add health record!"<<endl; return; }
    int id, aId;
    while (true) { id = getIntInput("\nEnter Record ID: ", 1); if (healthRecordExists(id)) cout << "ID exists!"<<endl; else break; }
    while (true) { aId = getIntInput("Enter Animal ID: ", 1); if (!animalExists(aId)) cout << "Animal ID doesn't exist!"<<endl; else break; }
    
    string issue = getStringInput("Enter Health Issue (Type 'No' if animal is healthy): ");
    if (issue == "No" || issue == "no" || issue == "NO") {
        cout << "\nNo health issue reported. Returning to Menu...\n"; return; 
    }

    healthRecords[totalHealth].id = id; healthRecords[totalHealth].animalId = aId;
    healthRecords[totalHealth].issue = issue; healthRecords[totalHealth].status = selectHealthStatus();
    totalHealth++; cout << "Health Record Added!"<<endl;
}

void viewHealth() {
    if (totalHealth == 0) { cout << "\nNo Records Found!\n"; return; }
    cout << "\n===================== HEALTH RECORDS ======================\n";
    for (int i = 0; i < totalHealth; i++) cout << "ID: " << healthRecords[i].id << " | Animal ID: " << healthRecords[i].animalId << " | Issue: " << displayStr(healthRecords[i].issue) << " | Status: " << healthRecords[i].status << endl;
}

void searchHealth() {
    if (totalHealth == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Record ID: ", 1);
    for (int i = 0; i < totalHealth; i++) if (healthRecords[i].id == id) { cout << "Found! Animal ID: " << healthRecords[i].animalId << ", Issue: " << displayStr(healthRecords[i].issue) << ", Status: " << healthRecords[i].status << endl; return; }
    cout << "Record Not Found!"<<endl;
}

void updateHealth() {
    if (totalHealth == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Health Record ID: ", 1);
    for (int i = 0; i < totalHealth; i++) if (healthRecords[i].id == id) {
        string issue = getStringInput("Enter New Issue (Type 'No' to cancel update): ");
        if (issue == "No" || issue == "no" || issue == "NO") { cout << "\nUpdate Cancelled.\n"; return; }
        healthRecords[i].issue = issue; healthRecords[i].status = selectHealthStatus();
        cout << "Updated Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void deleteHealth() {
    if (totalHealth == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Health Record ID to Delete: ", 1);
    for (int i = 0; i < totalHealth; i++) if (healthRecords[i].id == id) {
        for (int j = i; j < totalHealth - 1; j++) healthRecords[j] = healthRecords[j+1];
        totalHealth--; cout << "Deleted Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void healthMenu() {
    int c; do {
        cout << "\n==================== HEALTH MANAGEMENT ====================\n1. Add\n2. View\n3. Search\n4. Update\n5. Delete\n6. Back"<<endl;
        c = getIntInput("Choice (1-6): ", 1, 6);
        if (c == 1) addHealth(); else if (c == 2) viewHealth(); else if (c == 3) searchHealth(); else if (c == 4) updateHealth(); else if (c == 5) deleteHealth();
    } while (c != 6);
}

void addSale() {
    if (totalSales >= MAX || totalAnimals == 0) { cout << "Cannot add sale record! No animals exist."<<endl; return; }
    int id, aId;
    while (true) { id = getIntInput("\nEnter Sale ID: ", 1); if (saleRecordExists(id)) cout << "ID exists!"<<endl; else break; }
    while (true) { aId = getIntInput("Enter Animal ID: ", 1); if (!animalExists(aId)) cout << "Animal ID doesn't exist!"<<endl; else break; }
    
    saleRecords[totalSales].id = id; saleRecords[totalSales].animalId = aId;
    saleRecords[totalSales].amount = getFloatInput("Enter Total Amount: ", 0.0f);
    saleRecords[totalSales].date = getDateInput("Enter Date (DD-MM-YYYY): ");
    totalSales++; cout << "Sale Record Added!"<<endl;
}

void viewSales() {
    if (totalSales == 0) { cout << "\nNo Records Found!\n"; return; }
    cout << "\n====================== SALES RECORDS ======================\n";
    for (int i = 0; i < totalSales; i++) cout << "ID: " << saleRecords[i].id << " | Animal ID: " << saleRecords[i].animalId << " | Amount: " << saleRecords[i].amount << " | Date: " << saleRecords[i].date << endl;
}

void searchSale() {
    if (totalSales == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Sale ID: ", 1);
    for (int i = 0; i < totalSales; i++) if (saleRecords[i].id == id) { cout << "Found! Animal ID: " << saleRecords[i].animalId << ", Amount: " << saleRecords[i].amount << ", Date: " << saleRecords[i].date << endl; return; }
    cout << "Record Not Found!"<<endl;
}

void updateSale() {
    if (totalSales == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Sale ID to Update: ", 1);
    for (int i = 0; i < totalSales; i++) if (saleRecords[i].id == id) {
        saleRecords[i].amount = getFloatInput("Enter New Amount: ", 0.0f); saleRecords[i].date = getDateInput("Enter New Date: ");
        cout << "Updated Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void deleteSale() {
    if (totalSales == 0) { cout << "\nNo Records Found!\n"; return; }
    int id = getIntInput("\nEnter Sale ID to Delete: ", 1);
    for (int i = 0; i < totalSales; i++) if (saleRecords[i].id == id) {
        for (int j = i; j < totalSales - 1; j++) saleRecords[j] = saleRecords[j+1];
        totalSales--; cout << "Deleted Successfully!"<<endl; return;
    }
    cout << "ID Not Found!"<<endl;
}

void salesMenu() {
    int c; do {
        cout << "\n==================== SALES MANAGEMENT =====================\n1. Add\n2. View\n3. Search\n4. Update\n5. Delete\n6. Back"<<endl;
        c = getIntInput("Choice (1-6): ", 1, 6);
        if (c == 1) addSale(); else if (c == 2) viewSales(); else if (c == 3) searchSale(); else if (c == 4) updateSale(); else if (c == 5) deleteSale();
    } while (c != 6);
}

int main() {
    loadData();
    cout << "===========================================================\n";
    cout << "              DAIRY FARM MANAGEMENT SYSTEM     \n";
    cout << "===========================================================\n";
    while (!login());
    
    int choice;
    do {
        cout << "\n======================== MAIN MENU ========================\n1. Animal Management\n2. Milk Management\n3. Feed Management\n4. Health Management\n5. Sales Management\n6. Exit"<<endl;
        choice = getIntInput("Choice (1-6): ", 1, 6);
        if (choice == 1) animalMenu();
        else if (choice == 2) milkMenu();
        else if (choice == 3) feedMenu();
        else if (choice == 4) healthMenu();
        else if (choice == 5) salesMenu();
        else if (choice == 6) { saveData(); cout << "\nData Saved. Exiting...\n"; }
    } while (choice != 6);
    
    return 0;
}
