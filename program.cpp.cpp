#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int i, cpuInRep = 8, motherboardInRep = 4, ramInRep = 4, ssdInRep = 4;
double totalPrice;
int discount;

class CPU;
class Motherboard;
class RAM;
class SSD;
class PCConfig;
void title();
void homePage();
void checkoutPage();
void componentPage();
void cpuPage();
void motherboardPage();
void ramPage();
void ssdPage();
double calculateTotalCost(PCConfig);
double calculateDiscountedPrice();

class CPU {
public:
    CPU() {}
    CPU(string name, string socketType, int price)
    : name(name), socketType(socketType), price(price) {}
    string getName() { return name; }
    string getSocketType() { return socketType; }
    int getPrice() { return price; }
    void showInfo() {
        cout << "Model: " << name << "\n";
        cout << "Socket Type: " << socketType << "\n";
        cout << "Price: " << price << " BDT\n";
    }
    void unselect() {
        name = "";
        socketType = "";
        price = 0;
    }
    friend void addCPUFromFile(string);
private:
    string name, socketType;
    int price;
};

class Motherboard {
public:
    Motherboard() {}
    Motherboard(string name, string socketType, int price)
    : name(name), socketType(socketType), price(price) {}
    string getName() { return name; }
    string getSocketType() { return socketType; }
    int getPrice() { return price; }
    void showInfo() {
        cout << "Model: " << name << "\n";
        cout << "Socket Type: " << socketType << "\n";
        cout << "Price: " << price << " BDT\n";
    }
    void unselect() {
        name = "";
        socketType = "";
        price = 0;
    }
    friend void addMotherboardFromFile(string);
private:
    string name, socketType;
    int price;
};

class RAM {
public:
    RAM() {}
    RAM(string name, int capacity, int price)
    : name(name), capacity(capacity), price(price) {}
    string getName() { return name; }
    int getCapacity() { return capacity; }
    int getPrice() { return price; }
    void showInfo() {
        cout << "Model: " << name << "\n";
        cout << "Capacity: " << capacity << "\n";
        cout << "Price: " << price << " BDT\n";
    }
    friend void addRAMFromFile(string fileName);
private:
    string name;
    int capacity, price;
};

class SSD {
public:
    SSD() {}
    SSD(string name, int capacity, int price)
    : name(name), capacity(capacity), price(price) {}
    string getName() { return name; }
    int getCapacity() { return capacity; }
    int getPrice() { return price; }
    void showInfo() {
        cout << "Model: " << name << "\n";
        cout << "Capacity: " << capacity << "\n";
        cout << "Price: " << price << " BDT\n";
    }
    friend void addSSDFromFile(string fileName);
private:
    string name;
    int capacity, price;
};

class PCConfig {
public:
    void addCPU(CPU cpu) {
        char yn;
        if (motherboardIsSelected == false) {
            selectedCPU = cpu;
            CPUIsSelected = true;
            cout << "CPU selected successfully." << endl;
        }
        else {
            if (cpu.getSocketType() == selectedMotherboard.getSocketType()) {
                selectedCPU = cpu;
                CPUIsSelected = true;
                cout << "CPU selected successfully." << endl;
            }
            else {
                cout << "This CPU isn't compatible with selected Motherboard!"
                "CPU & Motherboard need to be of same socket type." << endl;
                cout << "Do you want to unselect the selected motherboard and select this cpu?(Y/y for yes): ";
                std::cin >> yn;
                if (yn == 'y' || yn == 'Y') {
                    selectedMotherboard.unselect();
                    motherboardIsSelected = false;
                    selectedCPU = cpu;
                    CPUIsSelected = true;

                }
            }
        }
    }
    bool getCPUIsSelected() { return CPUIsSelected; }
    void addMotherboard(Motherboard motherboard) {
        char yn;
        if (CPUIsSelected == false) {
            selectedMotherboard = motherboard;
            motherboardIsSelected = true;
            cout << "Motherboard selected successfully." << endl;
        }
        else {
            if (selectedCPU.getSocketType() == motherboard.getSocketType()) {
                selectedMotherboard = motherboard;
                motherboardIsSelected = true;
                cout << "Motherboard selected successfully." << endl;
            }
            else {
                cout << "Selected CPU isn't compatible with this Motherboard!"
                "CPU & Motherboard need to be of same socket type." << endl;
                cout << "Do you want to unselect the selected cpu and select this moyherboard?(Y/y for yes): ";
                std::cin >> yn;
                if (yn == 'y' || yn == 'Y') {
                    selectedCPU.unselect();
                    CPUIsSelected = false;
                    selectedMotherboard = motherboard;
                    motherboardIsSelected = true;
                }
            }
        }
    }
    bool getMotherbardIsSelected() { return motherboardIsSelected; }
    void addRAM(RAM ram, int quantity) {
        for (i = 0; i < quantity; i++) {
            selectedRAM[numRAMs] = ram;
            numRAMs++;
        }
    }
    int getNumRAMs() { return numRAMs; }
    void addSSD(SSD ssd, int quantity) {
        for (i = 0; i < quantity; i++) {
            selectedSSD[numSSDs] = ssd;
            numSSDs++;
        }
    }
    int getNumSSDs() { return numSSDs; }
    void display() {
        if (CPUIsSelected == true) {
            cout << "CPU: " << selectedCPU.getName() << "\tPrice: " << selectedCPU.getPrice() << " BDT" << endl;
        }
        if (motherboardIsSelected == true) {
            cout << "Motherboard: " << selectedMotherboard.getName() << "\tPrice: " << selectedMotherboard.getPrice() << " BDT" << endl;
        }
        if (numRAMs > 0) {
            for (i = 0; i < numRAMs; ++i) {
                cout << "RAM: " << selectedRAM[i].getName() << "\tPrice: " << selectedRAM[i].getPrice() << " BDT" << endl;
            }
        }
        if (numSSDs > 0) {
            for (i = 0; i < numSSDs; ++i) {
                cout << "SSD: " << selectedSSD[i].getName() << "\tPrice: " << selectedSSD[i].getPrice() << " BDT" << endl;
            }
        }
    }
    void shortDisplay() {
        if (CPUIsSelected == true) {
            cout << "CPU: " << selectedCPU.getName() << endl;
        }
        if (motherboardIsSelected == true) {
            cout << "Motherboard: " << selectedMotherboard.getName() << endl;
        }
        if (numRAMs > 0) {
            for (i = 0; i < numRAMs; ++i) {
                cout << "RAM: " << selectedRAM[i].getName() << endl;
            }
        }
        if (numSSDs > 0) {
            for (i = 0; i < numSSDs; ++i) {
                cout << "SSD: " << selectedSSD[i].getName() << endl;
            }
        }
    }
    friend double calculateTotalCost(PCConfig);
private:
    CPU selectedCPU;
    bool CPUIsSelected = false;
    Motherboard selectedMotherboard;
    bool motherboardIsSelected = false;
    RAM selectedRAM[100];
    SSD selectedSSD[100];
    int numRAMs = 0;
    int numSSDs = 0;
};

CPU cpuRepository[100];
Motherboard motherboardRepository[100];
RAM ramRepository[100];
SSD ssdRepository[100];
PCConfig customerConfig;

int main() {
    cpuRepository[0] = CPU("Core i3-12100", "LGA1700", 13300);
    cpuRepository[1] = CPU("Core i3-13100", "LGA1700", 16500);
    cpuRepository[2] = CPU("Core i5-12400", "LGA1700", 20000);
    cpuRepository[3] = CPU("Core i5-13400", "LGA1700", 26500);
    cpuRepository[4] = CPU("Core i5-13600K", "LGA1700", 36000);
    cpuRepository[5] = CPU("Core i7-12700", "LGA1700", 32500);
    cpuRepository[6] = CPU("Core i7-12700K", "LGA1700", 43500);
    cpuRepository[7] = CPU("Core i7-13700", "LGA1700", 44000);
    cpuRepository[8] = CPU("Core i7-13700K", "LGA1700", 47000);

    motherboardRepository[0] = Motherboard(" PRO H510M-B", "LGA1200", 8900);
    motherboardRepository[1] = Motherboard("Gigabyte B560M DS3H AC", "LGA1200", 13800);
    motherboardRepository[2] = Motherboard("Gigabyte H610M H", "LGA1700", 9900);
    motherboardRepository[3] = Motherboard("ASRock B660M PHANTOM GAMING 4", "LGA1700", 15000);

    ramRepository[0] = RAM("Adata Premier 4GB", 4, 1475);
    ramRepository[1] = RAM("Kingston 4GB", 4, 2000);
    ramRepository[2] = RAM("G.Skill 8GB", 8, 2400);
    ramRepository[3] = RAM("Corsair Vengeance LPX", 8, 2500);

    ssdRepository[0] = SSD(" N600S 128GB", 128, 1625);
    ssdRepository[1] = SSD("Western Digital Green", 240, 1900);
    ssdRepository[2] = SSD("Western Digital Blue SN550", 250, 3950);
    ssdRepository[3] = SSD("Biwintech NX500", 512, 4100);

    homePage();
    return 0;
}

void title() {
    system("cls");
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "|    PC Builder - Build your Computer    |" << endl;
    cout << "------------------------------------------" << endl;
    cout << endl;
}

void homePage() {
    int option, errorCheck;
    string userInput;
    title();
    cout << "Home Page" << endl;
    cout << endl;
    cout << "1. Select Components" << endl;
    cout << "2. Checkout" << endl;
    cout << endl;
    cout << "Press only Enter to exit." << endl;
    cout << endl;
    cout << "Input: ";
    fflush(stdin);
UserInputHome:
    std::getline(std::cin, userInput);
    if (userInput.empty()) {
        exit(0);
    }
    else {
        if (userInput.length() > 1) {
            cout << "Invalid response! Input again: ";
            goto UserInputHome;
        }
        else {
            option = userInput[0];
            switch (option) {
            case '1':
                componentPage();
                break;
            case '2':
                checkoutPage();
                break;
            default:
                cout << "Invalid response! Input again: ";
                goto UserInputHome;
            }
        }
    }
}

void componentPage() {
    char option;
    string userInput;
    title();
    cout << endl;
    cout << "Select your components (Chronologically recommended)" << endl;
    cout << endl;
    cout << "Core components:" << endl;
    cout << "1. CPU" << endl;
    cout << "2. Motherboard" << endl;
    cout << "3. Ram" << endl;
    cout << "4. SSD" << endl;
    cout << endl;
    customerConfig.shortDisplay();
    cout << endl;
    cout << "Input: ";
    fflush(stdin);
UserInputComp:
    std::getline(std::cin, userInput);
    if (userInput.empty()) {
        homePage();
    }
    else {
        if (userInput.length() > 1) {
            cout << "Invalid response! Input again: ";
            goto UserInputComp;
        }
        else {
            option = userInput[0];
            switch (option) {
            case '1':
                cpuPage();
                break;
            case '2':
                motherboardPage();
                break;
            case '3':
                ramPage();
                break;
            case '4':
                ssdPage();
                break;
            default:
                cout << "Invalid response! Input again: ";
                goto UserInputComp;
            }
        }
    }
}

void checkoutPage() {
    char yn;
    string userInput, coupon;
    totalPrice = calculateTotalCost(customerConfig);
    title();
    if (customerConfig.getCPUIsSelected() == false && customerConfig.getMotherbardIsSelected() == false
    && customerConfig.getNumRAMs() == 0 && customerConfig.getNumSSDs() == 0) {
        cout << "No Component Selected!" << endl;
        cout << "Press Enter to  go back." << endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty() || !userInput.empty()) {
            homePage();
        }
    }
    else {
        cout << "Your Cart:" << endl;
        customerConfig.display();
        cout << endl;
        cout << "Total Cost: " << totalPrice << " BDT" << endl;
        cout << endl;
        cout << "Do you want to confirm your purchase order?(Y/y for yes and you can't go back): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            char yn;
            cout << "Do you have any coupon code(Y/y for yes): ";
            std::cin >> yn;
            if (yn == 'y' || yn == 'Y') {
            enterCoupon:
                cout << "Enter code: ";
                std::cin >> coupon;
                if (coupon == "Dc2005") {
                    discount = 5;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2010") {
                    discount = 10;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2020") {
                    discount = 20;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2030") {
                    discount = 40;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else {
                    cout << "Invalid code! Want to try again?(Y/y for yes): ";
                    std::cin >> yn;
                    if (yn == 'y' || yn == 'Y') {
                        goto enterCoupon;
                    }
                    else {
                        cout << "Completing purchase without discount." << endl;
                        goto purchaseComplete;
                    }
                }
            }
            else {
            purchaseComplete:
                cout << "Purchase complete. Press Enter to exit." << endl;
                fflush(stdin);
                std::getline(std::cin, userInput);
                if (userInput.empty() || !userInput.empty()) {
                    exit(0);
                }
            }
        }
        else {
            homePage();
        }
    }
}

void cpuPage() {
    int CPUIndex;
    string userInput;
    title();
    cout << "Select your desired CPU" << endl;
    cout << endl;
    for (i = 0; i < cpuInRep; i++) {
        cout << i + 1 << ".\n";
        cpuRepository[i].showInfo();
    }
    cout << endl;
    if (!(std::cin >> CPUIndex) || CPUIndex < 1 || CPUIndex > cpuInRep) {
        cout << "Invalid response!" << endl;
    }
    else {
        customerConfig.addCPU(cpuRepository[CPUIndex - 1]);
        cout << "Press Enter to continue." << endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty()) {
            componentPage();
        }
    }
}

void motherboardPage() {
    int motherboardIndex;
    string userInput;
    title();
    cout << "Select your desired Motherboard" << endl;
    cout << endl;
    for (i = 0; i < motherboardInRep; i++) {
        cout << i + 1 << ".\n";
        motherboardRepository[i].showInfo();
    }
    cout << endl;
    if (!(std::cin >> motherboardIndex) || motherboardIndex < 1 || motherboardIndex > motherboardInRep) {
        cout << "Invalid response!" << endl;
    }
    else {
        customerConfig.addMotherboard(motherboardRepository[motherboardIndex - 1]);
        cout << "Press Enter to continue." << endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty()) {
            componentPage();
        }
    }
}

void ramPage() {
    int ramIndex, quantity;
    char yn;
    title();
    cout << "Select your desired RAM" << endl;
    cout << endl;
    for (i = 0; i < ramInRep; i++) {
        cout << i + 1 << ".\n";
        ramRepository[i].showInfo();
    }
    cout << endl;
selectRAM:
    cout << "Select: ";
    if (!(std::cin >> ramIndex) || ramIndex < 1 || ramIndex > ramInRep) {
        cout << "Invalid response!" << endl;
    }
    else {
        cout << "Quantity: ";
        std::cin >> quantity;
        customerConfig.addRAM(ramRepository[ramIndex - 1], quantity);
        cout << "Do you want to select more (Y/y for yes): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            goto selectRAM;
        }
        else {
            componentPage();
        }
    }
}

void ssdPage() {
    int ssdIndex, quantity;
    char yn;
    title();
    cout << "Select your desired SSD" << endl;
    cout << endl;
    for (i = 0; i < ssdInRep; i++) {
        cout << i + 1 << ".\n";
        ssdRepository[i].showInfo();
    }
    cout << endl;
selectSSD:
    cout << "Select: ";
    if (!(std::cin >> ssdIndex) || ssdIndex < 1 || ssdIndex > ssdInRep) {
        cout << "Invalid response!" << endl;
    }
    else {
        cout << "Quantity: ";
        std::cin >> quantity;
        customerConfig.addSSD(ssdRepository[ssdIndex - 1], quantity);
        cout << "Do you want to select more (Y/y for yes): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            goto selectSSD;
        }
        else {
            componentPage();
        }
    }
}

double calculateTotalCost(PCConfig config) {
    double totalCost = 0.0;
    totalCost = config.selectedCPU.getPrice() + config.selectedMotherboard.getPrice();
    for (int i = 0; i < config.numRAMs; ++i) {
        totalCost += config.selectedRAM[i].getPrice();
    }
    for (i = 0; i < config.numSSDs; ++i) {
        totalCost += config.selectedSSD[i].getPrice();
    }
    return totalCost;
}

double calculateDiscountedPrice() {
    double discountedPrice;
    discountedPrice = totalPrice - totalPrice * discount / 100;
    return discountedPrice;
}
