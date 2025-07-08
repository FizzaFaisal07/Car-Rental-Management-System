#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <iomanip>
using namespace std;

// Constants to define maximum number of cars and customers in the system
const int MAX_CARS = 100;
const int MAX_CUSTOMERS = 100;
// Constants for max duration limits
const int MAX_DAYS = 10;
const int MAX_HOURS = 24;

// Predefined admin credentials
const string ADMIN_USER = "fizza";
const string ADMIN_PASS = "fizza123";

void clearScreen() 
{
system("cls"); // ANSI escape code to clear screen
}

// Structure for Car to hold details of each car in the system
struct Car {
    int id{};
    string name;
    string color;
    string model;
    float pricePerDay{};
    float pricePerHour{};
    int stock{};
    bool isAvailable{};
};

// Structure for Customer to hold customer details
struct Customer {
    int id{};
    string name;
    string email;
    string phone;
    string address;
};
// Structure for Booking
struct Booking {
    int customerID{};
    string customerName;
    int carID;
    string carsName;
    double quantity;
    string durationType;
    double duration;
    float totalRent;
    float prepayment;
    float remainingRent;
};
// Function Prototypes - Function declarations to manage the system
void displayCars(Car* cars, int numCars);

void addCar(Car* cars, int& numCars);
void updateCar(Car* cars, int numCars);
void removeCar(Car* cars, int& numCars);
void addCustomer(Customer* customers, int& numCustomers);
bool isValidEmail(const string& email);
bool isValidPhoneNumber(const string& phone);
bool isUniqueCustomerID(const Customer* customers, int numCustomers, int id);
void removeCustomer(Customer* customers, int& numCustomers);
void editCustomer(Customer* customers, int numCustomers);
void viewCustomerDetails(Customer* customers, int numCustomers);
void saveCarsToFile(Car* cars, int numCars);
void saveCustomersToFile(Customer* customers, int numCustomers);
void loadCarsFromFile(Car* cars, int& numCars);
void loadCustomersFromFile(Customer* customers, int& numCustomers);
bool isAdminLogin();
bool isCustomerLogin(Customer* customers, int numCustomers);
void saveBookingToFile(Booking& booking);
void rentCar(Car* cars, int numCars, Customer* customers, int numCustomers);
void viewAllBookings();
void ViewBookings();
void saveFeedbackToFile(int customerID, const string& feedback);
void returnCar(Car* cars, int numCars, Customer* customers, int numCustomers);

int main() {
    Car cars[MAX_CARS];
    Customer customers[MAX_CUSTOMERS];
    int numCars = 0, numCustomers = 0;
    loadCarsFromFile(cars, numCars);
    loadCustomersFromFile(customers, numCustomers);

    while (true) {
        cout << "          ===========================================================\n";
        cout << "                   WELCOME TO CAR RENTAL MANAGEMENT SYSTEM          \n";
        cout << "          ===========================================================\n";
        cout << "                     1. Login as Admin\n";
        cout << "                     2. Login as Customer\n";
        cout << "                     3. Exit\n";
        cout << "          =============================================================\n";
        int loginChoice;
        cout << "Enter your choice: ";
        cin >> loginChoice;

        if (loginChoice == 1) {
            // Admin Login
            if (isAdminLogin()) {
                system("cls");
                // Admin Menu
                while (true) {
                    cout << "                 ========================================\n";
                    cout << "                                  ADMIN MENU           \n";
                    cout << "                  =======================================\n";
                    cout << "                     1. View Available Cars\n";
                    cout << "                     2. Add a New Car\n";
                    cout << "                     3. Update Car Information\n";
                    cout << "                     4. Remove a Car\n";
                    cout << "                     5. Add a New Customer\n";
                    cout << "                     6. Remove a Customer\n";
                    cout << "                     7. Edit Customer Information\n";
                    cout << "                     8. View Customer Information\n";
                    cout << "                     9. View All Booking\n";
                    cout << "                     10. Logout\n";
                    cout << "                  ========================================\n";
                    int choice;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        displayCars(cars, numCars);
                        break;
                    case 2:
                        addCar(cars, numCars);
                        break;
                    case 3:
                        updateCar(cars, numCars);
                        break;
                    case 4:
                        removeCar(cars, numCars);
                        break;
                    case 5:
                        addCustomer(customers, numCustomers);
                        break;
                    case 6:
                        removeCustomer(customers, numCustomers);
                        break;
                    case 7:
                        editCustomer(customers, numCustomers);
                        break;
                    case 8:
                        viewCustomerDetails(customers, numCustomers);
                        break;
                    case 9:
                        viewAllBookings();
                        break;
                    case 10:
                        saveCarsToFile(cars, numCars);
                        saveCustomersToFile(customers, numCustomers);
                        cout << "Data saved. Logging out.\n";
                        break;
                    default:
                        cout << "Invalid choice! Please try again.\n";
                    }
                    if (choice == 10) break;
                }
            }
            else {
                cout << "Invalid Admin login. Try again.\n";
            }
        }
        else if (loginChoice == 2) {

            if (isCustomerLogin(customers, numCustomers)) {
                while (true) {
                    cout << "\n            =======================================\n";
                    cout << "                               CUSTOMER MENU          \n";
                    cout << "              ========================================\n";
                    cout << "                    1. View Available Cars\n";
                    cout << "                    2. Rent a Car\n";
                    cout << "                    3. Return a Car\n";
                    cout << "                    4. View Booking Details\n";

                    cout << "                    5. Logout\n";
                    cout << "               ========================================\n";
                    int choice;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        displayCars(cars, numCars);    // Display all available cars
                        break;
                    case 2:
                        rentCar(cars, numCars, customers, numCustomers); // Rent a car function
                        break;
                    case 3:
                        returnCar(cars, numCars, customers, numCustomers);
                        break;
                    case 4:
                        ViewBookings(); // View bookings

                    case 5:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice! Please try again.\n";
                    }
                    if (choice == 5) break;
                }
            }
            else {
                cout << "Invalid Customer login. Try again.\n";
            }
        }
        else if (loginChoice == 3) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}


// Admin Login Function
bool isAdminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Only checks against Fizza's credentials
    if (username == ADMIN_USER && password == ADMIN_PASS) {
        return true;
    }
    else {
        cout << "Invalid credentials for Admin\n";
        return false;
    }
}
// Password Validation Function
bool isValidPassword(const string& password) {
    // Check password length
    if (password.length() < 8) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    // Check for at least one uppercase, one lowercase, one digit, and one special character
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (ispunct(ch)) hasSpecial = true;
    }

    // Return true if all conditions are met
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
// Customer Login Function
bool isCustomerLogin(Customer* customers, int numCustomers) {
    int customerID;
    string username, password;

    cout << "Enter Customer ID: ";
    cin >> customerID;

    // Check if the customer exists
    bool customerFound = false;
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerID) {
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        cout << "Customer ID not found.\n";
        return false;
    }
    cout << "Password pattren. Ensure it has at least 8 characters, "
        << "one uppercase letter, one lowercase letter, one digit, and one special character.\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    // Validate the password
    if (!isValidPassword(password)) {
        cout << "Password pattren. Ensure it has at least 8 characters, "
            << "one uppercase letter, one lowercase letter, one digit, and one special character.\n";
        return false;
    }

    cout << "Login successful.\n";
    return true;
}

// Function to display all the cars available in the system
void displayCars(Car* cars, int numCars) {

    if (numCars == 0) {
        cout << "No cars available.\n";
        return;
    }
    cout << "=========================================================================================\n";
    cout << "                             All Available Cars\n";
    cout << "=========================================================================================\n";
    cout << "Car ID | Car Name    | Car Color  | Car Model   | Price per Day |  Stock   | Availability \n";
    cout << "------------------------------------------------------------------------------------------\n";
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Color"
        << setw(15) << "Model" << setw(15) << "Price/Day"
        << setw(10) << "Stock" << setw(15) << "Availability\n";
    cout << "-------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numCars; i++) {
        // Display each car's details, including its availability status
        cout << setw(5) << cars[i].id << setw(15) << cars[i].name
            << setw(10) << cars[i].color << setw(15) << cars[i].model
            << setw(15) << cars[i].pricePerDay << setw(10) << cars[i].stock
            << setw(15) << (cars[i].isAvailable ? "Available" : "Rented") << "\n";
    }

}

// Function to add a new car to the system
void addCar(Car* cars, int& numCars) {
    if (numCars >= MAX_CARS) {
        cout << "Car limit reached. Cannot add more cars.\n";
        return;
    }
    cout << "\nEnter Car Details:\n";
    cout << "ID: ";
    cin >> cars[numCars].id;
    cin.ignore();  // Clear the input buffer
    cout << "Name: ";
    getline(cin, cars[numCars].name);
    cout << "Color: ";
    cin >> cars[numCars].color;
    cout << "Model: ";
    cin >> cars[numCars].model;
    cout << "Price per Day: ";
    cin >> cars[numCars].pricePerDay;
    cout << "Stock: ";
    cin >> cars[numCars].stock;
    cars[numCars].isAvailable = true;  // By default, the car is available for rent
    numCars++;
    cout << "Car added successfully.\n";
}

// Function to update an existing car's details in the system
void updateCar(Car* cars, int numCars) {
    int id;
    cout << "\nEnter the Car ID to update: ";
    cin >> id;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == id) {
            cout << "Enter New Details for Car ID " << id << ":\n";
            cin.ignore();  // Clear input buffer before accepting new values
            cout << "Name: ";
            getline(cin, cars[i].name);
            cout << "Color: ";
            cin >> cars[i].color;
            cout << "Model: ";
            cin >> cars[i].model;
            cout << "Price per Day: ";
            cin >> cars[i].pricePerDay;
            cout << "Stock: ";
            cin >> cars[i].stock;
            cout << "Is the car available? (1 for Yes, 0 for No): ";
            cin >> cars[i].isAvailable;  // Update the availability of the car
            cout << "Car updated successfully.\n";
            return;
        }
    }
    cout << "Car with ID " << id << " not found.\n";
}

// Function to remove a car from the system by its ID
void removeCar(Car* cars, int& numCars) {
    int id;
    cout << "\nEnter the Car ID to remove: ";
    cin >> id;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == id) {
            // Shift cars in the array to fill the removed car’s position
            for (int j = i; j < numCars - 1; j++) {
                cars[j] = cars[j + 1];
            }
            numCars--;
            cout << "Car removed successfully.\n";
            return;
        }
    }
    cout << "Car with ID " << id << " not found.\n";
}

// Add a new customer with validation
void addCustomer(Customer* customers, int& numCustomers) {
    if (numCustomers >= MAX_CUSTOMERS) {
        cout << "Customer limit reached. Cannot add more customers.\n";
        return;
    }

    int id;
    cout << "\nEnter Customer Details:\n";
    cout << "ID: ";
    cin >> id;

    // Check if ID is unique
    if (!isUniqueCustomerID(customers, numCustomers, id)) {
        cout << "Customer ID already exists. Please enter a unique ID.\n";
        return;
    }

    cin.ignore();  // To ignore the newline character left by cin
    cout << "Name: ";
    getline(cin, customers[numCustomers].name);

    string email;
    cout << "Email: ";
    getline(cin, email);

    // Validate email
    if (!isValidEmail(email)) {
        cout << "Invalid email format. Please enter a valid email.\n";
        return;
    }
    customers[numCustomers].email = email;

    string phone;
    cout << "Phone: ";
    getline(cin, phone);

    // Validate phone number
    if (!isValidPhoneNumber(phone)) {
        cout << "Invalid phone number format. Please enter a valid phone number.\n";
        return;
    }
    customers[numCustomers].phone = phone;

    cout << "Address: ";
    getline(cin, customers[numCustomers].address);

    customers[numCustomers].id = id;
    numCustomers++;
    cout << "Customer added successfully.\n";
}

// Validate email format (simple check for '@' and '.')
bool isValidEmail(const string& email) {
    return email.find('@') != string::npos && email.find('.') != string::npos;
}

// Validate phone number (must be exactly 10 digits)
bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 11) {
        return false;
    }
    for (char c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Check if customer ID is unique
bool isUniqueCustomerID(const Customer* customers, int numCustomers, int id) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            return false; // ID already exists
        }
    }
    return true; // ID is unique
}
// Function to remove a customer from the system by their ID
void removeCustomer(Customer* customers, int& numCustomers) {
    int id;
    cout << "\nEnter the Customer ID to remove: ";
    cin >> id;
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            // Shift customers in the array to fill the removed customer’s position
            for (int j = i; j < numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            numCustomers--;
            cout << "Customer removed successfully.\n";
            return;
        }
    }
    cout << "Customer with ID " << id << " not found.\n";
}

// Function to edit the details of an existing customer
void editCustomer(Customer* customers, int numCustomers) {
    int id;
    cout << "\nEnter the Customer ID to edit: ";
    cin >> id;
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            cout << "Enter New Details for Customer ID " << id << ":\n";
            cin.ignore();  // Clear input buffer
            cout << "Name: ";
            getline(cin, customers[i].name);
            cout << "Email: ";
            cin >> customers[i].email;
            cout << "Phone: ";
            cin >> customers[i].phone;
            cin.ignore();  // Clear input buffer
            cout << "Address: ";
            getline(cin, customers[i].address);
            cout << "Customer updated successfully.\n";
            return;
        }
    }
    cout << "Customer with ID " << id << " not found.\n";
}

// Function to view the details of all customers in the system
void viewCustomerDetails(Customer* customers, int numCustomers) {
    if (numCustomers == 0) {
        cout << "=========================================================================================\n";
        cout << "                                All Customers\n";
        cout << "=========================================================================================\n";
        cout << "Customer ID | Customer Name        | Email                     | Phone     | Address     \n";
        cout << "-----------------------------------------------------------------------------------------\n";
        return;
    }
    cout << "\nCustomer Details:\n";
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(25) << "Email"
        << setw(15) << "Phone" << setw(30) << "Address\n";
    cout << "------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numCustomers; i++) {
        // Display each customer's details
        cout << setw(5) << customers[i].id << setw(20) << customers[i].name
            << setw(25) << customers[i].email << setw(15) << customers[i].phone
            << setw(30) << customers[i].address << "\n";
    }
}

// Function to save the car details to a file
void saveCarsToFile(Car* cars, int numCars) {
    ofstream outFile("cars.txt");
    for (int i = 0; i < numCars; i++) {
        outFile << cars[i].id << " " << cars[i].name << " " << cars[i].color << " "
            << cars[i].model << " " << cars[i].pricePerDay << " " << cars[i].stock
            << " " << cars[i].isAvailable << "\n";  // Save the availability status to file
    }
    outFile.close();
}

// Function to save customer details to a file
void saveCustomersToFile(Customer* customers, int numCustomers) {
    ofstream outFile("customers.txt");
    for (int i = 0; i < numCustomers; i++) {
        outFile << customers[i].id << " " << customers[i].name << " " << customers[i].email
            << " " << customers[i].phone << " " << customers[i].address << "\n";
    }
    outFile.close();
}

// Function to load car details from a file
void loadCarsFromFile(Car* cars, int& numCars)
{
    ifstream inFile("cars.txt");
    if (!inFile) {
        // If file doesn't exist, create it (but don't load anything)
        ofstream createFile("cars.txt");
        createFile.close();
        return;
    }

    numCars = 0;
    while (inFile >> cars[numCars].id >> cars[numCars].name >> cars[numCars].color
        >> cars[numCars].model >> cars[numCars].pricePerDay >> cars[numCars].stock
        >> cars[numCars].isAvailable) {
        numCars++;
    }
    inFile.close();
}

// Function to load customer details from a file
void loadCustomersFromFile(Customer* customers, int& numCustomers) 
{
    ifstream inFile("customers.txt");
    if (!inFile) {
        // If file doesn't exist, create it (but don't load anything)
        ofstream createFile("customers.txt");
        createFile.close();
        return;
    }

    numCustomers = 0;
    while (inFile >> customers[numCustomers].id >> customers[numCustomers].name
        >> customers[numCustomers].email >> customers[numCustomers].phone
        >> customers[numCustomers].address) {
        numCustomers++;
    }
    inFile.close();
}

// Function to save booking details to the file
void saveBookingToFile(Booking& booking) {
    ofstream bookingsFile("bookings.txt", ios::app); // Open file in append mode
    if (!bookingsFile) {
        cout << "Error: Unable to open bookings file for saving.\n";
        return;
    }

    // Write booking details to the file
    bookingsFile << booking.customerID << "\t"
        << booking.customerName << "\t"
        << booking.carsName << "\t"
        << booking.durationType << "\t"
        << booking.duration << "\t"
        << booking.quantity << "\t"
        << booking.totalRent << "\t"
        << booking.prepayment << "\t"
        << booking.remainingRent << "\n";

    bookingsFile.close();
    cout << "Booking successfully saved to file.\n";
}
// Function to display all bookings
void viewAllBookings() {
    cout << "\n================================================================================================================\n";
    cout << "                               All Bookings\n";
    cout << "========================================================================================================================\n";
    cout << "Customer ID | Customer Name | Car Name | Rental Type | Duration | Quantity | Total Rent | Prepayment | Remaining Rent\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    ifstream bookingsFile("bookings.txt");

    if (bookingsFile.is_open()) {
        string line;
        while (getline(bookingsFile, line)) {
            cout << line << endl;
        }
        bookingsFile.close();
    }
    else {
        cout << "Error: Unable to open bookings file.\n";
    }
}

void ViewBookings() {
    int customerID;

    // Prompt the user for their Customer ID
    cout << "Enter your Customer ID to view your booking details: ";
    cin >> customerID;

    cout << "\n==================================================================================================================\n";
    cout << "                               Your Booking Details\n";
    cout << "=====================================================================================================================\n";
    cout << "Customer ID | Customer Name | Car Name | Rental Type | Duration | Quantity | Total Rent | Prepayment | Remaining Rent\n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";

    ifstream bookingsFile("bookings.txt", ios::in); // Open file in read mode
    if (!bookingsFile) {
        cout << "Error opening the bookings file.\n";
        return;
    }

    string line;
    bool foundBooking = false;

    // Read through each line in the bookings file
    while (getline(bookingsFile, line)) {
        if (line.empty()) continue; // Skip empty lines

        // Use a stringstream to extract data from each line
        stringstream ss(line);
        int fileCustomerID;
        string customerName, carsName, durationType;
        int quantity, duration;
        float totalRent, prepayment, remainingRent;

        // Read each field from the line
        ss >> fileCustomerID >> customerName >> carsName >> durationType >> duration >> quantity >> totalRent >> prepayment >> remainingRent;

        // Check if the current line belongs to the customer
        if (fileCustomerID == customerID) {
            foundBooking = true;
            // Display the booking details for the customer
            cout << setw(12) << fileCustomerID << " | "
                << setw(15) << customerName << " | "
                << setw(10) << carsName << " | "
                << setw(12) << durationType << " | "
                << setw(10) << duration << " | "
                << setw(8) << quantity << " | "
                << setw(10) << totalRent << " | "
                << setw(10) << prepayment << " | "
                << setw(10) << remainingRent << endl;
            cout << "---------------------------------------------------------------------------------\n";
        }
    }

    if (!foundBooking) {
        cout << "No bookings found for Customer ID " << customerID << ".\n";
    }

    bookingsFile.close();
}


void rentCar(Car* cars, int numCars, Customer* customers, int numCustomers) {
    int customerID, carID, quantity;

    // Get Customer ID
    cout << "Enter your Customer ID: ";
    cin >> customerID;

    // Validate Customer ID
    int customerIndex = -1;
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerID) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Customer ID not found.\n";
        return;
    }

    // Get Car ID
    cout << "Enter Car ID you want to rent: ";
    cin >> carID;

    // Validate Car ID and Availability
    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carID && cars[i].isAvailable && cars[i].stock > 0) {
            carIndex = i;
            break;
        }
    }

    if (carIndex == -1) {
        cout << "Car not available for rent.\n";
        return;
    }

    // Get Quantity
    cout << "Enter the quantity of cars you want to rent: ";
    cin >> quantity;

    if (quantity > cars[carIndex].stock) {
        cout << "Not enough cars in stock. Available stock: " << cars[carIndex].stock << "\n";
        return;
    }

    // Asking for rental duration type (days or hours)
    string durationType;
    int duration;
    cout << "Do you want to rent the car for days or hours? (Enter 'days' or 'hours'): ";
    cin >> durationType;

    if (durationType == "days") {
        cout << "Enter rental duration (max 10 days): ";
        cin >> duration;
        if (duration > MAX_DAYS) {
            cout << "Invalid duration! Maximum allowed is " << MAX_DAYS << " days.\n";
            return;
        }
    }
    else if (durationType == "hours") {
        cout << "Enter rental duration (max 24 hours): ";
        cin >> duration;
        if (duration > MAX_HOURS) {
            cout << "Invalid duration! Maximum allowed is " << MAX_HOURS << " hours.\n";
            return;
        }
    }
    else {
        cout << "Invalid input! Please enter either 'days' or 'hours'.\n";
        return;
    }

    // Calculate Total Rent
    float totalRent = 0;
    if (durationType == "days") {
        totalRent = cars[carIndex].pricePerDay * duration * quantity;
    }
    else if (durationType == "hours") {
        totalRent = (cars[carIndex].pricePerDay / 24) * duration * quantity;
    }

    cout << "Total rent for " << duration << " " << durationType << "(s): $" << totalRent << "\n";

    // Calculate Prepayment
    float prepayment = totalRent / 2;
    cout << "Prepayment (50%): $" << prepayment << "\n";

    // Ask for Payment Confirmation
    string paymentDecision;
    cout << "Do you want to pay the prepayment of $" << prepayment << "? (yes/no): ";
    cin >> paymentDecision;

    if (paymentDecision == "yes") {
        cout << "Booking confirmed! You have paid the prepayment of $" << prepayment << ".\n";

        // Deduct stock and mark car as unavailable if necessary
        cars[carIndex].stock -= quantity;
        if (cars[carIndex].stock == 0) {
            cars[carIndex].isAvailable = false;
        }

        float remainingRent = totalRent - prepayment;

        // Save the booking information to a file
        Booking booking = {
           customerID,
           customers[customerIndex].name,  // Corrected array index
           carID,
           cars[carIndex].name,
           quantity,
           durationType,
           duration,
           totalRent,
           prepayment,
           remainingRent
        };
        saveBookingToFile(booking); // Ensure this function is implemented correctly

        cout << "Remaining rent to be paid: $" << remainingRent << "\n";
    }
    else {
        cout << "Booking canceled.\n";
    }
}

void saveFeedbackToFile(int customerID, const string& feedback) {
    ofstream bookingsFile("bookings.txt", ios::app);
    if (bookingsFile.is_open()) {
        bookingsFile << customerID << feedback << "\n";
        bookingsFile.close();
    }
    else {
        cout << "Failed to save feedback to the file.\n";
    }
}
void returnCar(Car* cars, int numCars, Customer* customers, int numCustomers) {
    int customerID, carID, rentedCars;

    // Get Customer ID
    cout << "Enter your Customer ID: ";
    cin >> customerID;

    // Validate Customer ID
    int customerIndex = -1;
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == customerID) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Customer ID not found.\n";
        return;
    }

    // Get Car ID
    cout << "Enter the Car ID you are returning: ";
    cin >> carID;

    // Validate Car ID
    int carIndex = -1;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carID) {
            carIndex = i;
            break;
        }
    }

    if (carIndex == -1) {
        cout << "Car ID not found.\n";
        return;
    }

    // Get Rental Duration
    string durationType;
    int actualDuration;
    cout << "Did you rent the car for days or hours? (Enter 'days' or 'hours'): ";
    cin >> durationType;

    if (durationType != "days" && durationType != "hours") {
        cout << "Invalid input! Please enter either 'days' or 'hours'.\n";
        return;
    }

    cout << "Enter the actual duration you rented the car for: ";
    cin >> actualDuration;

    int originalDuration = 0; // Assume we retrieve this from the booking system
    if (actualDuration <= originalDuration) {
        cout << "Has the car been returned within the agreed duration? (yes/no): ";
        string returnedOnTime;
        cin >> returnedOnTime;
        if (returnedOnTime == "yes") {
            cout << "Thank you for returning the car on time!\n";
        }
        else {
            cout << "Car returned late.\n";
        }
    }
    else {
        cout << "Car was returned after more than the agreed duration. Did you pay the fine for extra days/hours? (yes/no): ";
        string finePaid;
        cin >> finePaid;
        if (finePaid != "yes") {
            cout << "Return process canceled. Please pay the fine first.\n";
            return;
        }
    }

    // Get Quantity
    cout << "Enter the quantity of cars you rented: ";
    cin >> rentedCars;

    // Check for Damage
    string isDamaged;
    cout << "Was the car damaged? (yes/no): ";
    cin >> isDamaged;
    if (isDamaged == "yes") {
        cout << "Did you pay the damage charges? (yes/no): ";
        string damagePaid;
        cin >> damagePaid;
        if (damagePaid != "yes") {
            cout << "Return process canceled. Please pay the damage charges first.\n";
            return;
        }
    }

    // Update Car Stock
    cars[carIndex].stock += rentedCars;
    cars[carIndex].isAvailable = true;

    // Update Car Details in File
    ofstream outFile("cars.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < numCars; i++) {
            outFile << cars[i].id << " " << cars[i].name << " " << cars[i].color << " "
                << cars[i].model << " " << cars[i].pricePerDay << " " << cars[i].stock
                << " " << cars[i].isAvailable << "\n";  // Save the availability status to file
        }
        outFile.close();
    }
    else {
        cout << "Failed to update car details in the file.\n";
        return;
    }

    cout << "Car returned successfully. Thank you!\n";

    // Ask for Feedback
    cout << "Would you like to provide feedback for this car rental? (yes/no): ";
    string provideFeedback;
    cin >> provideFeedback;

    if (provideFeedback == "yes") {
        string feedback;
        cout << "Please enter your feedback: ";
        cin.ignore();  // To clear any leftover newline
        getline(cin, feedback);

        // Save the feedback to the file
        saveFeedbackToFile(customerID, feedback);



        cout << "Thank you for your feedback!\n";
    }
}