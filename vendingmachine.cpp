#include <iostream>
#include <string>
#include <unordered_map>

class Product {
public:
    int id;
    std::string name;
    double price;
    std::string brand;
};

class Inventory {
public:
    std::unordered_map<int, Product*> products;
    std::unordered_map<int, int> stock;

    void addProduct(Product* product, int stock) {
        products[product->id] = product;
        this->stock[product->id] = stock;
    }

    void removeProduct(int id) {
        products.erase(id);
        stock.erase(id);
    }

    void updateStock(int id, int stock) {
        this->stock[id] = stock;
    }
};

class InventoryController {
public:
    Inventory* inventory;

    InventoryController() {
        inventory = new Inventory();
    }

    ~InventoryController() {
        delete inventory;
    }

    void addProduct(Product* product, int stock) {
        inventory->addProduct(product, stock);
    }

    void removeProduct(int id) {
        inventory->removeProduct(id);
    }

    void updateStock(int id, int stock) {
        inventory->updateStock(id, stock);
    }
};

class VendingMachineStates;

class VendingMachine {
public:
    InventoryController* inventory;
    VendingMachineStates* currentState;
    int currentProductId;
    double amount;

    VendingMachine(InventoryController* inventory);

    void selectProduct(int id);
    void insertCoins(double amount);
    void dispenseProduct();
};

class VendingMachineStates {
public:
    virtual void selectProduct(VendingMachine& vending, int id) = 0;
    virtual void insertCoins(VendingMachine& vending, double amount) = 0;
    virtual void dispenseProduct(VendingMachine& vending) = 0;
};

class IdleState : public VendingMachineStates {
public:
    void selectProduct(VendingMachine& vending, int id) override;
    void insertCoins(VendingMachine& vending, double amount) override;
    void dispenseProduct(VendingMachine& vending) override;
};

class ProductSelectedState : public VendingMachineStates {
public:
    void selectProduct(VendingMachine& vending, int id) override;
    void insertCoins(VendingMachine& vending, double amount) override;
    void dispenseProduct(VendingMachine& vending) override;
};

class ProductDispenseState : public VendingMachineStates {
public:
    void selectProduct(VendingMachine& vending, int id) override;
    void insertCoins(VendingMachine& vending, double amount) override;
    void dispenseProduct(VendingMachine& vending) override;
};

VendingMachine::VendingMachine(InventoryController* inventory) {
    this->inventory = inventory;
    currentState = new IdleState();
    currentProductId = -1;
    amount = 0.0;
}

void VendingMachine::selectProduct(int id) {
    currentState->selectProduct(*this, id);
}

void VendingMachine::insertCoins(double amount) {
    currentState->insertCoins(*this, amount);
}

void VendingMachine::dispenseProduct() {
    currentState->dispenseProduct(*this);
}

void IdleState::selectProduct(VendingMachine& vending, int id) {
    if (vending.inventory->inventory->stock[id] > 0) {
        vending.currentProductId = id;
        vending.currentState = new ProductSelectedState();
    } else {
        std::cout << "Product out of stock" << std::endl;
    }
}

void IdleState::insertCoins(VendingMachine& vending, double amount) {
    std::cout << "Please select a product first" << std::endl;
}

void IdleState::dispenseProduct(VendingMachine& vending) {
    std::cout << "Please select a product first" << std::endl;
}

void ProductSelectedState::selectProduct(VendingMachine& vending, int id) {
    std::cout << "Product already selected" << std::endl;
}

void ProductSelectedState::insertCoins(VendingMachine& vending, double amount) {
    vending.amount += amount;
    if (vending.amount >= vending.inventory->inventory->products[vending.currentProductId]->price) {
        vending.currentState = new ProductDispenseState();
        std::cout << "Return Change: " << vending.amount - vending.inventory->inventory->products[vending.currentProductId]->price << std::endl;
    } else {
        std::cout << "Amount inserted: " << vending.amount << std::endl;
        std::cout << "Amount remaining: " << vending.inventory->inventory->products[vending.currentProductId]->price - vending.amount << std::endl;
    }
}

void ProductSelectedState::dispenseProduct(VendingMachine& vending) {
    std::cout << "Please insert coins first" << std::endl;
}

void ProductDispenseState::selectProduct(VendingMachine& vending, int id) {
    std::cout << "Product already selected" << std::endl;
}

void ProductDispenseState::insertCoins(VendingMachine& vending, double amount) {
    std::cout << "Product already selected" << std::endl;
}

void ProductDispenseState::dispenseProduct(VendingMachine& vending) {
    std::cout << "Product dispensed: " << vending.inventory->inventory->products[vending.currentProductId]->name << std::endl;
    vending.inventory->inventory->stock[vending.currentProductId]--;
    vending.currentState = new IdleState();
}

int main() {
    Product* product1 = new Product();
    product1->id = 1;
    product1->name = "Coke";
    product1->price = 1.5;
    product1->brand = "Coca Cola";

    Product* product2 = new Product();
    product2->id = 2;
    product2->name = "Pepsi";
    product2->price = 2;
    product2->brand = "PepsiCo";

    InventoryController* inventory = new InventoryController();
    inventory->addProduct(product1, 10);
    inventory->addProduct(product2, 10);

    VendingMachine* vendingMachine = new VendingMachine(inventory);
    vendingMachine->selectProduct(1);
    vendingMachine->insertCoins(1.5);
    vendingMachine->dispenseProduct();

    vendingMachine->selectProduct(2);
    vendingMachine->insertCoins(1);
    vendingMachine->insertCoins(0.5);
    vendingMachine->insertCoins(1);
    vendingMachine->dispenseProduct();

    vendingMachine->selectProduct(2);
    vendingMachine->insertCoins(1);
    vendingMachine->dispenseProduct();

    delete vendingMachine;
    delete inventory;
    delete product1;
    delete product2;

    return 0;
}
