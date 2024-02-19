#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_SALES 100

typedef struct {
    char name[50];
    double price;
    int quantity;
} Product;

typedef struct {
    Product products[MAX_PRODUCTS];
    int productCount;
    int salesCount;
} DepartmentalStore;

void addProduct(DepartmentalStore* store, const char* name, double price, int quantity) {
    if (store->productCount < MAX_PRODUCTS) {
        Product newProduct;
        strcpy(newProduct.name, name);
        newProduct.price = price;
        newProduct.quantity = quantity;
        store->products[store->productCount++] = newProduct;
        printf("|----------------------------------|\n");
        printf("Product added successfully!\n");
        printf("|----------------------------------|\n\n");
    } else {
        printf("Product limit reached. Cannot add more products.\n");
    }
}

void displayProducts(DepartmentalStore* store) {
    if (store->productCount == 0) {
        printf("No products available.\n");
    } else {
        printf("Products:\n");
        for (int i = 0; i < store->productCount; i++) {
            printf("%d. %s - $%.2f, Quantity: %d\n", i + 1, store->products[i].name, store->products[i].price, store->products[i].quantity);
        }
    }
}

void processSale(DepartmentalStore* store, int productIndex, int quantity) {
    if (productIndex >= 0 && productIndex < store->productCount) {
        if (store->products[productIndex].quantity >= quantity) {
            printf("|----------------------------------|\n");
            printf("Sale processed successfully!\n");
            printf("|----------------------------------|\n\n");
            store->products[productIndex].quantity -= quantity;
            store->salesCount++;

        } else {
            printf("Insufficient stock. Cannot process the sale.\n");
        }
    } else {
        printf("Invalid product index.\n");
    }
}

void restockProduct(DepartmentalStore* store, int productIndex, int quantity) {
    if (productIndex >= 0 && productIndex < store->productCount) {
        store->products[productIndex].quantity += quantity;
        printf("Restock successful!\n");
    } else {
        printf("Invalid product index.\n");
    }
}

void generateSalesReport(DepartmentalStore* store) {
    if (store->salesCount == 0) {
        printf("No sales recorded.\n");
    } else {
        printf("Sales Report:\n");
        printf("================================================\n");
        printf("%-20s %-10s %-10s\n", "Product Name", "Quantity", "Revenue\n");

        for (int i = 0; i < store->productCount; i++) {
            // Calculate revenue for each product (quantity * price)
            double revenue = store->products[i].price * (double)(store->salesCount);

            printf("%-20s %-10d $%-10.2f\n", store->products[i].name, store->salesCount, revenue);
        
        }
    }
}

void exitSystem() {
    printf("Exiting the program. Goodbye!\n");
    exit(0);
}

int main() {
    DepartmentalStore departmentalStore;
    departmentalStore.productCount = 0;
    departmentalStore.salesCount = 0;

    int choice;

    do {
        printf("\n========================================");
        printf("\nDepartmental Store Management\n");
        printf("========================================\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Process Sale\n");
        printf("4. Restock Product\n");
        printf("5. Generate Sales Report\n");
        printf("6. Exit\n");
        printf("X----------------------------X\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar(); // Consume newline character

        switch (choice) {
            case 1: {
                char name[50];
                double price;
                int quantity;

                printf("Enter product name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 

                printf("Enter product price: $");
                scanf("%lf", &price);

                printf("Enter product quantity: ");
                scanf("%d", &quantity);

                addProduct(&departmentalStore, name, price, quantity);
                break;
            }
            case 2:
                displayProducts(&departmentalStore);
                break;
            case 3: {
                int productIndex;
                int saleQuantity;

                displayProducts(&departmentalStore);

                printf("Enter product index to process sale: ");
                scanf("%d", &productIndex);

                printf("Enter quantity for sale: ");
                scanf("%d", &saleQuantity);

                processSale(&departmentalStore, productIndex - 1, saleQuantity);
                break;
            }
            case 4: {
                int productIndex;
                int restockQuantity;

                displayProducts(&departmentalStore);

                printf("Enter product index to restock: ");
                scanf("%d", &productIndex);

                printf("Enter quantity for restock: ");
                scanf("%d", &restockQuantity);

                restockProduct(&departmentalStore, productIndex - 1, restockQuantity);
                break;
            }
            case 5:
                generateSalesReport(&departmentalStore);
                break;
            case 6:
                exitSystem();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
