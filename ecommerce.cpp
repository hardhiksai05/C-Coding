#include<bits/stdc++.h>
using namespace std;

// ENUMS 

enum Category{
    ELECTRONICS,
    CLOTHING,
    GROCERY,
    BOOKS
};

enum OrderStatus{
    PENDING,
    CONFIRMED,
    CANCELLED,
    DELIVERED
};

enum PaymentStatus{
    NOT_PAID,
    PAID,
    FAILED,
    REFUNDED
};

enum PaymentMethod{
    CREDIT_CARD,
    UPI,
    CASH
};


string categoryName(Category c){
    if(c==ELECTRONICS){
        return "ELECTRONICS";
    }
    if(c==CLOTHING){
        return "CLOTHING";
    }
    if(c==GROCERY){
        return "GROCERY";
    }
    else{
        return "BOOKS";
    }
}

string orderStatusName(OrderStatus s){
    if(s==PENDING){
        return "PENDING";
    }
    if(s==CONFIRMED){
        return "CONFIRMED";
    }
    if(s==CANCELLED){
        return "CANCELLED";
    }
    else{
        return "DELIVERED";
    }
}

string paymentStatusName(PaymentStatus p){
    if(p==NOT_PAID){
        return "NOT PAID";
    }
    if(p==PAID){
        return "PAID";
    }
    if(p==FAILED){
        return "FAILED";
    }
    else{
        return "REFUNDED";
    }
}


// CLASS --> PRODUCT

class product{
    private:
        int prodID;
        string name;
        double price;
        int stock;
        Category category;
    
    public:
        product(){
            prodID=0;
            name="";
            price=0.0;
            stock=0;
            category=ELECTRONICS;
        }

        product(int id,string n,double p, int s, Category c){
            prodID=id;
            name=n;
            price=p;
            stock=s;
            category=c;
        }

        //geters
        int getID(){
            return prodID;
        }
        string getname(){
            return name;
        }
        double getPrice(){
            return price;
        }
        int getStock(){
            return stock;
        }

        void displayProduct(){
            cout<<"Product ID: "<<prodID<<endl<<"Name: "<<name<<endl<<"Price: "<<price<<endl<<"Stock: "<<stock<<endl<<"Category: "<<categoryName(category)<<endl;
        }

        // quantity cannot be negative so for that case
        void updateStock(int qty){
            stock+=qty;
            if(stock<0){
                stock=0;
            }
        }

        bool checkAvailability(int qty){
            return stock>=qty;
        }
};


// CLASS --> CUSTOMER CLASS

class Customer{
    private:
        int customerID;
        string name;
        string email;
        long long phone;
        string address;

    public:
        Customer(){
            customerID=phone=0;
            name=email=address="";
        }

        Customer(int id,string n,string e,long long ph,string add){
            customerID=id;
            name=n;
            email=e;
            phone=ph;
            address=add;
        }

        //geters

        int getID(){
            return customerID;
        }
        string getName(){
            return name;
        }

        void displayCustomer(){
            cout<<"Customer ID: "<<customerID<<endl<<"Name: "<<name<<endl<<"Email: "<<email<<endl<<"Phone: "<<phone<<endl<<"Address: "<<address<<endl; 
        }

        void updateDetails(string e, long long ph, string add){
            email=e;
            phone = ph;
            address=add;
        }
};

// union --> Payments
union PaymentInfo{
    int last4digits;
    char upiID[50];
};

// Struct --> Order

struct order{
    int orderID;
    int customerID;
    int productID;
    int quantity;
    double totalAmount;
    OrderStatus status;
    PaymentStatus paymentStatus;
    PaymentMethod method;
    PaymentInfo payInfo;

    void displayOrder(){
        cout<<"OrderID: "<<orderID<<endl<<"Customers ID: "<<customerID<<endl<<"Product ID: "<<productID<<endl<<"Qty: "<<quantity<<endl<<"Total: "<<totalAmount<<endl<<"OrderStatus: "<<orderStatusName(status)<<endl<<"Payment Status: "<<paymentStatusName(paymentStatus)<<endl;
    }

};

//Array Points

const int MAX = 100;
product products[MAX];
int productcount=0;

Customer customers[MAX];
int customercount=0;

order orders[MAX];
int orderCount=0;
int nextOrderID=1001;


//Helpers lookups

int findProductIndex(int id){
    for(int i=0;i<productcount;i++){
        if(products[i].getID()==id){
            return i;
        }
    }
    return -1;
}

int findCustomerIndex(int id){
    for(int i=0;i<customercount;i++){
        if(customers[i].getID()==id){
            return i;
        }
        return -1;
    }
}

int findOrderIndex(int id){
    for(int i=0;i<orderCount;i++){
        if(orders[i].orderID==id){
            return i;
        }
    }
    return -1;
}


//adding products
void addProduct(){
    string name;
    double price;
    int stock;
    int choice;
    int id=productcount+1;

    cout<<"Enter the product name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter the price: ";
    cin>>price;
    cout<<"Enter Stock: ";
    cin>>stock;
    cout<<"Choose category (0-Electronics, 1-Clothing, 2-Grocery, 3-Books): ";
    cin>>choice;

    products[productcount]=product(id,name,price,stock,(Category)choice);
    productcount++;
    cout<<"Poduct added and ID is : "<<id<<endl;
}

//Adding Customers

void addCustomer(){
    string name;
    string email;
    long long phone;
    string address;
    int id=customercount+1;

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone: ";
    cin>>phone;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, address);

    customers[customercount]=Customer(id,name,email,phone,address);
    customercount++;
    cout<<"Customer added and ID is: "<<id<<endl;
}

void createOrder(){
    int custID;
    int prodID;
    int qty;

    cout << "Enter Customer ID: ";
    cin >> custID;
    int ci = findCustomerIndex(custID);
    if (ci == -1) {
        cout << "ERROR: Invalid Customer ID!" << endl;
        return;
    }

    cout << "Enter Product ID: ";
    cin >> prodID;
    int pi = findProductIndex(prodID);
    if (pi == -1) {
        cout << "ERROR: Invalid Product ID!" << endl;
        return;
    }

    cout << "Enter quantity: ";
    cin >> qty;
    if (!products[pi].checkAvailability(qty)) {
        cout << "ERROR: Product out of stock! Available: "
             << products[pi].getStock() << endl;
        return;
    }

    order o;
    o.orderID = nextOrderID++;
    o.customerID = custID;
    o.productID = prodID;
    o.quantity = qty;
    o.totalAmount = products[pi].getPrice() * qty;
    o.status = PENDING;
    o.paymentStatus = NOT_PAID;
 
    products[pi].updateStock(-qty); // reduce stock
 
    orders[orderCount++] = o;
 
    cout << "Order created successfully! OrderID: " << o.orderID<<endl<< "Total Amount: " << o.totalAmount << endl;
}

void makePayment(){
    int orderID;
    int methodChoice;

    cout << "Enter Order ID: ";
    cin >> orderID;
    int oi = findOrderIndex(orderID);
    if (oi == -1) {
        cout << "ERROR: Invalid Order ID!" << endl;
        return;
    }

    if (orders[oi].status == CANCELLED) {
        cout << "ERROR: Cannot pay for a cancelled order!" << endl;
        return;
    }

    cout << "Choose Payment Method (0-CreditCard 1-UPI 2-Cash): ";
    cin >> methodChoice;
    orders[oi].method = (PaymentMethod)methodChoice;
 
    if (orders[oi].method == CREDIT_CARD) {
        int last4;
        cout << "Enter last 4 digits of card: ";
        cin >> last4;
        orders[oi].payInfo.last4digits = last4;
    } else if (orders[oi].method == UPI) {
        string upi;
        cout << "Enter UPI ID: ";
        cin >> upi;
        strncpy(orders[oi].payInfo.upiID, upi.c_str(), 49);
        orders[oi].payInfo.upiID[49] = '\0';
    }


    char choice;
    cout << "Did payment succeed? (y/n): ";
    cin >> choice;
 
    if (choice == 'y' || choice == 'Y') {
        orders[oi].paymentStatus = PAID;
        cout << "Payment successful!" << endl;
    } else {
        orders[oi].paymentStatus = FAILED;
        cout << "Payment failed!" << endl;
    }
}

void confirmOrder() {
    int orderID;
    cout << "Enter Order ID: ";
    cin >> orderID;
    int oi = findOrderIndex(orderID);
    if (oi == -1) {
        cout << "ERROR: Invalid Order ID!" << endl;
        return;
    }
 
    if (orders[oi].status == CANCELLED) {
        cout << "ERROR: Cannot confirm a cancelled order!" << endl;
        return;
    }

    if (orders[oi].paymentStatus != PAID) {
        cout << "ERROR: Cannot confirm order. Payment not completed (status: "<< paymentStatusName(orders[oi].paymentStatus) << ")" << endl;
        return;
    }
 
    orders[oi].status = CONFIRMED;
    cout << "Order confirmed successfully!" << endl;
}

void cancelOrder() {
    int orderID;
    cout << "Enter Order ID: ";
    cin >> orderID;
    int oi = findOrderIndex(orderID);
    if (oi == -1) {
        cout << "ERROR: Invalid Order ID!" << endl;
        return;
    }
 
    if (orders[oi].status == DELIVERED) {
        cout << "ERROR: Cannot cancel a delivered order!" << endl;
        return;
    }
 
    if (orders[oi].status == CANCELLED) {
        cout << "ERROR: Order is already cancelled!" << endl;
        return;
    }
 
    orders[oi].status = CANCELLED;
 
    // restore stock since order is cancelled
    int pi = findProductIndex(orders[oi].productID);
    if (pi != -1) {
        products[pi].updateStock(orders[oi].quantity);
    }
 
    cout << "Order cancelled successfully!" << endl;
}

void markDelivered() {
    int orderID;
    cout << "Enter Order ID: ";
    cin >> orderID;
    int oi = findOrderIndex(orderID);
    if (oi == -1) {
        cout << "ERROR: Invalid Order ID!" << endl;
        return;
    }
    if (orders[oi].status != CONFIRMED) {
        cout << "ERROR: Only confirmed orders can be marked delivered!" << endl;
        return;
    }
    orders[oi].status = DELIVERED;
    cout << "Order marked as delivered!" << endl;
}
 
void displayAllProducts() {
    if (productcount == 0){ 
        cout << "No products available.\n";
        return;
    }
    for (int i = 0; i < productcount; i++){
        products[i].displayProduct();
    }
}

void displayAllCustomers() {
    if (customercount == 0){
        cout << "No customers available.\n"; 
        return; 
    }
    for (int i = 0; i < customercount; i++){
        customers[i].displayCustomer();
    }
}
 
void displayAllOrders() {
    if (orderCount == 0){
        cout << "No orders available.\n"; 
        return; 
    }
    for (int i = 0; i < orderCount; i++){
        orders[i].displayOrder();
    }
}

// Main Function

int main(){
    int choice;
    do{
        cout << "\n========== E-COMMERCE ORDER MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Product\n";
        cout << "2. Add Customer\n";
        cout << "3. Create Order\n";
        cout << "4. Make Payment\n";
        cout << "5. Confirm Order\n";
        cout << "6. Cancel Order\n";
        cout << "7. Mark Order Delivered\n";
        cout << "8. Display All Products\n";
        cout << "9. Display All Customers\n";
        cout << "10. Display All Orders\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: addCustomer(); break;
            case 3: createOrder(); break;
            case 4: makePayment(); break;
            case 5: confirmOrder(); break;
            case 6: cancelOrder(); break;
            case 7: markDelivered(); break;
            case 8: displayAllProducts(); break;
            case 9: displayAllCustomers(); break;
            case 10: displayAllOrders(); break;
            case 0: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    }while(choice!=0);

    return 0;
}