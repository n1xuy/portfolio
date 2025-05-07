#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

#define MAX_SIZE 10 // Maximum capacity for stack and queue

// Structure to represent a car in the system
struct Car {
    int id;           // Unique identifier for the car
    string model;     // Model name of the car
    string color;     // Color of the car
    int year;         // Manufacturing year
    float price;      // Daily rental price
    Car* next;        // Pointer for linked list structure (not used in this design)
};

// Structure to represent a rental request (includes rental duration)
struct RentalRequest {
    Car* car;         // Pointer to the car being rented
    int rental_days;  // Number of days for the rental
};

// Structure to represent a processed (booked) rental request
struct ProcessedRequest {
    Car* car;                   // Pointer to the car that was rented
    int rental_days;            // Number of rental days booked
    ProcessedRequest* next;     // Pointer for linked list of processed requests
};

// Stack class to track recently added cars (LIFO)
class RecentStack {
    Car* arr[MAX_SIZE]; // Array to store car pointers
    int top;            // Index of top element

public:
    RecentStack() : top(-1) {} // Initialize empty stack

    // Add car to the top of the stack
    void push(Car* car) {
        if (top < MAX_SIZE - 1) {
            arr[++top] = car;
        }
    }

    // Display cars in stack from most recent to oldest
    void displayRecent() {
        cout << "\n--------------------------------------------------\n";
        cout << "Recent Added Cars (Most Recent First):\n";
        for (int i = top; i >= 0; i--) {
            cout << "ID: " << arr[i]->id 
                 << " | Model: " << arr[i]->model << endl;
        }
        cout << "--------------------------------------------------\n";
    }
};

// Queue class to handle rental requests (FIFO) with ability to process a specific request
class RentalQueue {
    RentalRequest* arr[MAX_SIZE]; // Array to store rental request pointers
    int front, rear;              // Pointers for queue management

public:
    RentalQueue() : front(-1), rear(-1) {} // Initialize empty queue

    // Check if the queue is empty
    bool isEmpty() {
        return (front == -1 || front > rear);
    }

    // Add rental request to the end of the queue
    void enqueue(Car* car, int rental_days) {
        if (rear == MAX_SIZE - 1) {
            cout << "\n[Error] Rental request queue is full!\n";
            return;
        }
        if (front == -1)
            front = 0; // Initialize front if queue was empty
        RentalRequest* req = new RentalRequest();
        req->car = car;
        req->rental_days = rental_days;
        arr[++rear] = req;
        cout << "\n[Info] Rental request submitted for Car ID: " << car->id 
             << " for " << rental_days << " day(s).\n";
        // Calculate and display total rental amount
        float total_amount = car->price * rental_days;
        cout << "[Info] Total Amount: RM" << total_amount << endl;
    }

    // Process a rental request at a specific index and remove it from the queue
    RentalRequest* processRentalAtIndex(int index) {
        if (isEmpty() || index < front || index > rear) {
            cout << "\n[Error] Invalid index! No such rental request.\n";
            return nullptr;
        }
        RentalRequest* req = arr[index];
        cout << "\n--------------------------------------------------\n";
        cout << "[Processing] Rental for Car ID: " << req->car->id << "\n";
        cout << "Rental Duration: " << req->rental_days << " day(s)\n";
        cout << "--------------------------------------------------\n";
        // Shift elements to remove the request from the queue
        for (int i = index; i < rear; i++) {
            arr[i] = arr[i + 1];
        }
        rear--;
        if (rear < front) { // Queue becomes empty
            front = rear = -1;
        }
        return req;
    }

    // Display pending rental requests (those not yet processed)
    void displayPending() {
        if (isEmpty()) {
            cout << "\n[Info] No pending rental requests!\n";
            return;
        }
        cout << "\n--------------------------------------------------\n";
        cout << "Pending Rental Requests:\n";
        for (int i = front; i <= rear; i++) {
            cout << "[" << i << "] Car ID: " << arr[i]->car->id 
                 << " | Duration: " << arr[i]->rental_days << " day(s)" << endl;
        }
        cout << "--------------------------------------------------\n";
    }
};

// Main system class integrating all components
class CarRentalSystem {
    // Node structure for linked list and hash table chaining
    struct Node {
        Car* data;   // Pointer to car data
        Node* next;  // Pointer to next node
    };

    Node* head;                   // Head of linked list for all cars
    RecentStack stack;            // Recent cars stack
    RentalQueue queue;            // Rental requests queue
    Node* hashTable[MAX_SIZE];    // Hash table for quick lookups
    ProcessedRequest* processedHead; // Head of processed (booked) requests list

public:
    CarRentalSystem() {
        head = NULL;  // head is of type Node*
        processedHead = NULL;
        for (int i = 0; i < MAX_SIZE; i++)
            hashTable[i] = NULL;
    }

    // Simple hash function using modulo operation
    int hashFunction(int id) {
        return id % MAX_SIZE;
    }

    // Find car by ID using linear search through the linked list
    Car* findCarById(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->data->id == id) {
                return temp->data;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Add new car to all data structures
    void addCar() {
        Car* newCar = new Car();
        cout << "\n--------------------------------------------------\n";
        cout << "Enter Car Details:\n";
        cout << "ID: ";
        cin >> newCar->id;
        cout << "Model: "; 
        cin >> newCar->model;
        cout << "Color: "; 
        cin >> newCar->color;
        cout << "Year: ";
        cin >> newCar->year;
        cout << "Price per day: "; 
        cin >> newCar->price;
        cout << "--------------------------------------------------\n";

        // Create a new node for the linked list
        Node* newNode = new Node();
        newNode->data = newCar;
        newNode->next = head;
        head = newNode;

        // Push to recent stack
        stack.push(newCar);

        // Add to hash table
        int index = hashFunction(newCar->id);
        Node* hashNode = new Node();
        hashNode->data = newCar;
        hashNode->next = hashTable[index];
        hashTable[index] = hashNode;

        cout << "[Success] Car added successfully!\n";
    }

    // Display all cars sorted by ID using bubble sort on the linked list
    void displayCars(bool isAdmin = true) {
        if (!head) {
            cout << "\n--------------------------------------------------\n";
            cout << "[Info] No cars in system!\n";
            cout << "--------------------------------------------------\n";
            return;
        }

        // Bubble sort implementation for the linked list based on car ID
        bool swapped;
        Node* ptr1;
        Node* lptr = NULL;
        do {
            swapped = false;
            ptr1 = head;
            while (ptr1->next != lptr) {
                if (ptr1->data->id > ptr1->next->data->id) {
                    swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        // Display the sorted list of available cars
        cout << "\n--------------------------------------------------\n";
        cout << "Available Cars (Sorted by ID):\n";
        Node* temp = head;
        while (temp) {
            Car* car = temp->data;
            cout << "ID: " << car->id
                 << " | Model: " << car->model
                 << " | Color: " << car->color
                 << " | Year: " << car->year
                 << " | Price per day: RM" << car->price << endl;
            temp = temp->next;
        }
        cout << "--------------------------------------------------\n";

        // Show recent cars for admin users
        if (isAdmin)
            stack.displayRecent();
    }

    // Search for a car by ID using the hash table, with fallback to linear search
    void searchCar() {
        if (!head) {
            cout << "\n--------------------------------------------------\n";
            cout << "[Info] No cars in system!\n";
            cout << "--------------------------------------------------\n";
            return;
        }

        int searchId;
        cout << "\n--------------------------------------------------\n";
        cout << "Enter Car ID to search: ";
        cin >> searchId;
        cout << "--------------------------------------------------\n";

        // Attempt hash table lookup
        int index = hashFunction(searchId);
        Node* hashEntry = hashTable[index];
        while (hashEntry) {
            if (hashEntry->data->id == searchId) {
                cout << "[Success] Car Found (via Hash Table):\n";
                printCarDetails(hashEntry->data);
                cout << "--------------------------------------------------\n";
                return;
            }
            hashEntry = hashEntry->next;
        }

        // Fallback to linear search if not found in hash table
        Node* temp = head;
        while (temp) {
            if (temp->data->id == searchId) {
                cout << "[Success] Car Found (via Linear Search):\n";
                printCarDetails(temp->data);
                cout << "--------------------------------------------------\n";
                return;
            }
            temp = temp->next;
        }
        cout << "[Error] Car not found!\n";
    }

    // Edit existing car details
    void editCar() {
        int editId;
        cout << "\n--------------------------------------------------\n";
        cout << "Enter Car ID to edit: ";
        cin >> editId;
        cout << "--------------------------------------------------\n";

        Node* temp = head;
        while (temp) {
            if (temp->data->id == editId) {
                cout << "Enter new details (enter current value to keep unchanged):\n";
                cout << "Model (" << temp->data->model << "): "; 
                cin >> temp->data->model;
                cout << "Color (" << temp->data->color << "): "; 
                cin >> temp->data->color;
                cout << "Year (" << temp->data->year << "): "; 
                cin >> temp->data->year;
                cout << "Price (" << temp->data->price << "): "; 
                cin >> temp->data->price;
                cout << "--------------------------------------------------\n";
                cout << "[Success] Car updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "[Error] Car not found!\n";
    }

    // Delete a car from all data structures
    void deleteCar() {
        int deleteId;
        cout << "\n--------------------------------------------------\n";
        cout << "Enter Car ID to delete: ";
        cin >> deleteId;
        cout << "--------------------------------------------------\n";
        if (removeCarFromSystem(deleteId))
            cout << "[Success] Car deleted successfully!\n";
        else
            cout << "[Error] Car not found!\n";
    }

    // Helper function to remove a car from the linked list and hash table
    bool removeCarFromSystem(int deleteId) {
        // Remove from linked list
        Node *prev = NULL, *curr = head;
        while (curr) {
            if (curr->data->id == deleteId) {
                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;
                // Remove from hash table
                int index = hashFunction(deleteId);
                Node *hPrev = NULL, *hCurr = hashTable[index];
                while (hCurr) {
                    if (hCurr->data->id == deleteId) {
                        if (hPrev)
                            hPrev->next = hCurr->next;
                        else
                            hashTable[index] = hCurr->next;
                        delete hCurr;
                        break;
                    }
                    hPrev = hCurr;
                    hCurr = hCurr->next;
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // Helper function to display the details of a car
    void printCarDetails(Car* car) {
        cout << "ID: " << car->id << endl
             << "Model: " << car->model << endl
             << "Color: " << car->color << endl
             << "Year: " << car->year << endl
             << "Price per day: RM" << car->price << endl;
    }

    // Add a processed (booked) rental request to the processed requests list
    void addProcessedRequest(RentalRequest* req) {
        ProcessedRequest* newProcessed = new ProcessedRequest();
        newProcessed->car = req->car;
        newProcessed->rental_days = req->rental_days;
        newProcessed->next = processedHead;
        processedHead = newProcessed;
        // Free the RentalRequest object after processing
        delete req;
    }

    // Display all processed (booked) rental requests
    void viewProcessedRequests() {
        if (!processedHead) {
            cout << "\n--------------------------------------------------\n";
            cout << "[Info] No processed rental requests!\n";
            cout << "--------------------------------------------------\n";
            return;
        }
        cout << "\n--------------------------------------------------\n";
        cout << "Processed (Booked) Rental Requests:\n";
        ProcessedRequest* temp = processedHead;
        while (temp) {
            cout << "Car ID: " << temp->car->id
                 << " | Model: " << temp->car->model
                 << " | Rental Duration: " << temp->rental_days << " day(s)" << endl;
            temp = temp->next;
        }
        cout << "--------------------------------------------------\n";
    }

    // Admin function to process a specific rental request chosen by index.
    // If there are no pending requests, do not prompt for an index.
    void adminProcessRental() {
        // Check if there are pending rental requests
        if (queue.isEmpty()) {
            cout << "\n[Info] No pending rental requests!\n";
            return;
        }
        // Display pending rental requests with their indices
        queue.displayPending();
        cout << "\nEnter the index of the rental request to process: ";
        int index;
        cin >> index;
        RentalRequest* req = queue.processRentalAtIndex(index);
        if (req) {
            // Remove the car from the system after processing the rental
            if (removeCarFromSystem(req->car->id)) {
                addProcessedRequest(req);
                cout << "[Success] Rental processed and car removed from system.\n";
            } else {
                cout << "[Error] Car removal failed.\n";
                delete req; // Free the request to avoid memory leak
            }
        }
    }

    // Admin interface with management options
    void showAdminMenu() {
        while (true) {
            cout << "\n******************** ADMIN MENU ********************\n";
            cout << "1. Add New Car\n";
            cout << "2. Display All Cars\n";
            cout << "3. Search Car\n";
            cout << "4. Edit Car Details\n";
            cout << "5. Delete Car\n";
            cout << "6. Process Specific Rental Request\n";
            cout << "7. View Processed Rental Requests\n";
            cout << "8. Return to Main Menu\n";
            cout << "****************************************************\n";
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            switch (choice) {
                case 1: addCar(); break;
                case 2: displayCars(); break;
                case 3: searchCar(); break;
                case 4: editCar(); break;
                case 5: deleteCar(); break;
                case 6: adminProcessRental(); break;
                case 7: viewProcessedRequests(); break;
                case 8: return;
                default: cout << "[Error] Invalid choice!\n";
            }
        }
    }

    // Renter interface with rental options
    void showRenterMenu() {
        while (true) {
            cout << "\n******************* RENTER MENU *******************\n";
            cout << "1. View Available Cars\n";
            cout << "2. Search Car\n";
            cout << "3. Request Rental\n";
            cout << "4. View Pending Rental Requests\n";
            cout << "5. View Processed Rental Requests\n";
            cout << "6. Return to Main Menu\n";
            cout << "****************************************************\n";
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            switch (choice) {
                case 1: displayCars(false); break;
                case 2: searchCar(); break;
                case 3: {
                    int carId, days;
                    cout << "\nEnter Car ID to rent: ";
                    cin >> carId;
                    Car* car = findCarById(carId);
                    if (car) {
                        cout << "Enter number of rental days: ";
                        cin >> days;
                        // Enqueue the rental request and display total amount info
                        queue.enqueue(car, days);
                    } else {
                        cout << "[Error] Car not found!\n";
                    }
                    break;
                }
                case 4:
                    // Display pending rental requests (rental requests not yet processed)
                    queue.displayPending();
                    break;
                case 5: viewProcessedRequests(); break;
                case 6: return;
                default: cout << "[Error] Invalid choice!\n";
            }
        }
    }

    // Main menu with role selection
    void showMainMenu() {
        int selection;
        do {
            cout << "\n#################### WELCOME TO ####################\n";
            cout << "                CAR RENTAL SYSTEM\n";
            cout << "####################################################\n";
            cout << "1. Admin\n";
            cout << "2. Renter\n";
            cout << "3. Exit\n";
            cout << "----------------------------------------------------\n";
            cout << "Enter your selection: ";
            cin >> selection;
            switch (selection) {
                case 1:
                    showAdminMenu();
                    break;
                case 2:
                    showRenterMenu();
                    break;
                case 3:
                    cout << "\n[Info] Thank you for using Car Rental System. Goodbye!\n";
                    exit(0);
                default:
                    cout << "[Error] Invalid selection!\n";
            }
        } while (selection != 0);
    }
};

int main() {
    CarRentalSystem system;
    system.showMainMenu();
    return 0;
}
