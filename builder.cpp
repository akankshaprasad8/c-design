#include <iostream>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;

    // Output the car's details
    void printDetails() {
        cout << "Car Details:" << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};

class CarBuilder {
private:
    Car car;  // Car object to build

public:
    
    CarBuilder(const Car car){
        this->car = car;
    }
    // Method to set the brand of the car
    CarBuilder& setBrand(const string& brand) {
        car.brand = brand;
        return *this;  // Return a reference to the builder for chaining
    }

    // Method to set the model of the car
    CarBuilder& setModel(const string& model) {
        car.model = model;
        return *this;  // Return a reference to the builder for chaining
    }

    // Method to set the year of the car
    CarBuilder& setYear(int year) {
        car.year = year;
        return *this;  // Return a reference to the builder for chaining
    }

    // Method to build and return the final Car object
    Car build() {
        return car;
    }
};

int main() {
    // Create a CarBuilder object
    CarBuilder carBuilder= CarBuilder(Car());

    // Use the builder to construct a Car object and assign it to 'car'
    Car car = carBuilder
                .setBrand("Ford")
                .setModel("Mustang")
                .setYear(1969)
                .build();

    // Output the car's details
    car.printDetails();

    return 0;
}
