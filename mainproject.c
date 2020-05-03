/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 * https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : Theodore Fabian Rudy
 * Student ID : 1155133167
 * Class/Section : ENGG1110/B
 * Date : 18/11/2019
 */

 // Formatting done by using codebeautify.org C formatter beautifier.

#include <stdio.h>

# define MAX_MONEY 99
# define MAX_STOCK 10

void mainMenu(int price[], int stock[], int balance, int bought);
void topMenu();
void displayProductsMenu(char product[][20], int prices[]);
void insertCoinMenu();
void moneySeparator(int money);
void buyProductsMenu();
void returnButton(int balance);
void subMenu();
void inspectMachine(int revenue, int balance, int stock[5], int price[5], char product[5][20]);
void withdrawMoney(int * money);
void restockMenu();
void changeProduct(char product[][20], int price[], int stock[], int choice);

int topMenuChoices();
int insertCoin(int * coinoption);
int buyProducts(int balance, int stock[5], int price[5], int * worth, int * choice);
int serviceMenu();
int subMenuChoices();
int restock(int stock[5], int * stocknumber);
int changeProductMenu();

int main(void) {
    int price[5] = {
        10,
        6,
        5,
        8,
        7
    };
    int stock[5] = {
        5,
        1,
        2,
        1,
        9
    };
    char product[5][20] = {
        "Juice",
        "Cola",
        "Tea",
        "Water",
        "Coffee"
    };
    int balance = 0;
    int bought = 0;
    int revenue = 0;
    int choice; // for menu 1-4
    int second_option; // for submenu of 9
    int coin;
    int coinoption;
    int stockoption;
    int correct_code;
    int product_change;
    int worth, product_choice, button_product_choice;

    mainMenu(price, stock, balance, bought);
    choice = topMenuChoices();
    while (choice > 0) {
        if (choice == 1) {
            displayProductsMenu(product, price);
            choice = topMenuChoices();
        } else if (choice == 2) {
            coin = insertCoin( & coinoption);
            balance = balance + coin;
            if (coinoption != 0) {}
            if (coin != 0 && balance <= MAX_MONEY) {
                mainMenu(price, stock, balance, bought);
            } else if (coin != 0 && balance > MAX_MONEY) {
                balance = MAX_MONEY;
                mainMenu(price, stock, balance, bought);
            } else if (coin == 0) {
                mainMenu(price, stock, balance, bought);
                choice = topMenuChoices();
            }
        } else if (choice == 3) {
            button_product_choice = buyProducts(balance, stock, price, & worth, & product_choice);
            if (button_product_choice != 0) {
                if (stock[product_choice - 1] > 0 && balance >= price[product_choice - 1]) {
                    stock[product_choice - 1]--;
                    balance = balance - worth;
                    revenue = revenue + worth;
                    bought = product_choice;
                    mainMenu(price, stock, balance, bought);
                    bought = 0;
                    choice = topMenuChoices();
                } else if (balance < price[product_choice - 1]) {
                    mainMenu(price, stock, balance, bought);
                    choice = topMenuChoices();
                }
            } else if (button_product_choice == 0) {
                mainMenu(price, stock, balance, bought);
                choice = topMenuChoices();
            }
        } else if (choice == 4) {
            returnButton(balance);
            balance = 0;
            mainMenu(price, stock, balance, bought);
            choice = topMenuChoices();
        } else if (choice == 9) {
            correct_code = serviceMenu();
            int total_money = balance + revenue;
            while (correct_code == 1) {
                second_option = subMenuChoices();
                while (second_option > 0) {
                    if (second_option == 1) {
                        inspectMachine(revenue, balance, stock, price, product);
                        second_option = subMenuChoices();
                    } else if (second_option == 2) {
                        withdrawMoney( & total_money);
                        total_money = 0;
                        balance = 0;
                        revenue = 0;
                        second_option = subMenuChoices();
                    } else if (second_option == 3) {
                        restock(stock, & stockoption);
                        second_option = subMenuChoices();
                    } else if (second_option == 4) {
                        product_change = changeProductMenu();
                        if (product_change == 0) {
                            second_option = subMenuChoices();
                        } else if (product_change > 0 && product_change < 6) {
                            changeProduct(product, price, stock, product_change);
                            second_option = subMenuChoices();
                        } else {
                            printf("\n");
                        }
                    }
                }
                if (second_option == 0) {
                    correct_code = 0;
                }
            }
            mainMenu(price, stock, balance, bought);
            choice = topMenuChoices();
        } else if (choice == 0) {
            return 0;
        }
    }
}

void mainMenu(int price[5], int stock[5], int balance, int bought) {
    int item_bought = 64 + bought;
    printf("*---------------------------*\n");
    printf("|      Vending Machine      |\n");
    printf("*---------------------------*\n");
    printf("|   A    B    C    D    E   |\n");
    printf("|  ");
    moneySeparator(price[0]);
    printf("  ");
    moneySeparator(price[1]);
    printf("  ");
    moneySeparator(price[2]);
    printf("  ");
    moneySeparator(price[3]);
    printf("  ");
    moneySeparator(price[4]);
    printf("  |\n");
    printf("|");
    for (int i = 0; i < 5; i++) {
        if (stock[i] > 0 && balance < price[i]) {
            printf("  [ ]");
        } else if (stock[i] > 0 && balance >= price[i]) {
            printf("  [O]");
        } else if (stock[i] == 0) {
            printf("  [X]");
        }
    }
    printf("  |\n");
    // printf("|  [ ]  [ ]  [ ]  [ ]  [ ]  |\n");
    printf("*---------------------------*\n");
    printf("|                    [");
    moneySeparator(balance);
    printf("]  |\n");
    printf("|                           |\n");
    printf("|           [=");
    if (item_bought == 64) {
        printf("=");
    } else {
        printf("%c", item_bought);
    }
    printf("=]           |\n");
    printf("*---------------------------*\n");
    printf("\n");
}

void moneySeparator(int money) {
    if (money < 10) {
        printf("$ %d", money);
    } else if (money >= 10) {
        printf("$%d", money);
    }
}

// 0
void topMenu() {
    printf("What would you like to do?\n");
    printf("1. Read product information\n");
    printf("2. Insert coin\n");
    printf("3. Press product button\n");
    printf("4. Press return button\n");
    printf("9. Open service menu (code required)\n");
    printf("0. Quit\n");
    printf("Your choice:");
}

// 0
int topMenuChoices() {
    int choice = 0;
    int loop = 1;
    while (loop) {
        topMenu();
        scanf("%d", & choice);
        if ((choice >= 0 && choice <= 4) || choice == 9) {
            loop = 0;
            printf("\n");
        } else {
            printf("Invalid choice!\n\n");
        }
    }
    return choice;
}

// 1
void displayProductsMenu(char product[5][20], int price[5]) {
    int ascii = 65;
    printf("(1) The displayed products are:\n");
    for (int i = 0; i < 5; i++) {
        printf("%c. %s ($%d)\n", ascii + i, product[i], price[i]);
    }
    printf("\n");
}

// 2
void insertCoinMenu() {
    printf("(2) Which coin would you like to insert?\n");
    printf("1. $1\n");
    printf("2. $2\n");
    printf("3. $5\n");
    printf("4. $10\n");
    printf("0. Go back\n");
    printf("Your choice:");
}

// 2
int insertCoin(int * coinoption) {
    int loop = 1;
    int coinAdded;
    while (loop) {
        insertCoinMenu();
        scanf("%d", coinoption);
        if (( * coinoption >= 0 && * coinoption <= 4)) {
            loop = 0;
            if ( * coinoption == 1) {
                coinAdded = 1;
                printf("You have inserted $%d.\n\n", coinAdded);
            } else if ( * coinoption == 2) {
                coinAdded = 2;
                printf("You have inserted $%d.\n\n", coinAdded);
            } else if ( * coinoption == 3) {
                coinAdded = 5;
                printf("You have inserted $%d.\n\n", coinAdded);
            } else if ( * coinoption == 4) {
                coinAdded = 10;
                printf("You have inserted $%d.\n\n", coinAdded);
            } else if ( * coinoption == 0) {
                coinAdded = 0;
                printf("Going back!\n\n");
            }
        } else {
            printf("Invalid choice!\n\n");
        }
    }
    return coinAdded;
}

// 3
void buyProductsMenu() {
    int characters = 65;
    printf("(3) Which product button would you like to press?\n");
    for (int i = 1; i < 6; i++) {
        printf("%d. %c\n", i, characters++);
    }
    printf("0. Go back\n");
    printf("Your choice:");
}

// 3
int buyProducts(int balance, int stock[5], int price[5], int * worth, int * choice) {
    int loop = 1;
    int characters = 64;
    while (loop) {
        buyProductsMenu();
        scanf("%d", choice);
        if ( * choice >= 0 && * choice <= 5) {
            loop = 0;
            if ( * choice != 0) {
                * worth = price[ * choice - 1];
                printf("You have pressed button %c.\n\n", characters + * choice);
            } else if ( * choice == 0) {
                worth = 0;
                printf("Going back!\n\n");
            }
        } else {
            printf("Invalid choice!\n\n");
        }
    }
    return *choice;
}

// 4
void returnButton(int balance) {
    printf("(4) Return button is pressed.\n");
    printf("$%d has been returned.\n\n", balance);
}

// 9
int serviceMenu() {
    int
    const password = 1110;
    int access_code;
    int correct_code = 1;
    printf("(9) Opening service menu. Access code is required.\n");
    printf("Enter access code:");
    scanf("%d", & access_code);
    if (access_code != password) {
        printf("Incorrect code!\n\n");
        correct_code = 0;
    } else if (access_code == password) {
        printf("Correct code!\n");
    }
    return correct_code;
}

// 9
void subMenu() {
    printf("(9) What would you like to do?\n");
    printf("1. Inspect machine status\n");
    printf("2. Withdraw all money\n");
    printf("3. Refill product\n");
    printf("4. Change product\n");
    printf("0. Go back\n");
    printf("Your choice:");
}

int subMenuChoices() {
    int second_option;
    printf("\n");
    int loop = 1;
    while (loop) {
        subMenu();
        scanf("%d", & second_option);
        if ((second_option >= 0 && second_option <= 4)) {
            loop = 0;
            if (second_option != 0) {
                printf("\n");
            } else if (second_option == 0) {
                printf("Going back!\n\n");
            }
        } else {
            printf("Invalid choice!\n\n");
        }
    }
    return second_option;
}

// 9-1
void inspectMachine(int revenue, int balance, int stock[5], int price[5], char product[5][20]) {
    int characters = 65;
    printf("(9-1) Machine status\n");
    printf("Amount of revenue: $%d\n", revenue);
    printf("Amount of inserted coins: $%d\n", balance);
    printf("Product information:\n");
    for (int i = 0; i < 5; i++) {
        if (stock[i] > 0) {
            printf("%c. %s ($%d) (%d left)\n", characters + i, product[i], price[i], stock[i]);
        } else if (stock[i] == 0) {
            printf("%c. %s ($%d) (sold out)\n", characters + i, product[i], price[i]);
        }
    }
}

// 9-2
void withdrawMoney(int * money) {
    printf("(9-2) All money is being withdrawn.\n");
    printf("$%d is withdrawn.\n", * money);
}

// 9-3
void restockMenu() {
    int characters = 64;
    printf("(9-3) Which product would you like to refill?\n");
    for (int i = 1; i < 6; i++) {
        printf("%d. %c\n", i, characters + i);
    }
    printf("0. Go back\n");
    printf("Your choice:");
}

// 9-3
int restock(int stock[5], int * stocknumber) {
    int loop = 1;
    int characters = 64;
    while (loop) {
        restockMenu();
        scanf("%d", stocknumber);
        if ( * stocknumber >= 0 && * stocknumber < 6) {
            loop = 0;
            if ( * stocknumber != 0) {
                stock[ * stocknumber - 1] = MAX_STOCK;
                printf("You have refilled product %c to full.\n", characters + * stocknumber);
            } else if ( * stocknumber == 0) {
                printf("Going back!\n");
            }
        } else {
            printf("Invalid choice!\n\n");
        }
    }
    return *stocknumber;
}

// 9-4
int changeProductMenu() {
    int characters = 64;
    printf("(9-4) Which product would you like to change\n");
    for (int i = 1; i < 6; i++) {
        printf("%d. %c\n", i, characters + i);
    }
    printf("0. Go back\n");
    printf("Your choice:");
    int choice;
    scanf("%d", & choice);
    if (choice > 0 && choice < 6) {
        printf("You are changing product %c.\n\n", characters + choice);
    } else if (choice == 0) {
        printf("Going back!\n");
    } else {
        printf("Invalid choice!\n");
    }
    return choice;
}

// 9-4-1
void changeProduct(char product[][20], int price[], int stock[], int choice) {
    int characters = 64;
    printf("Enter new product name:");
    scanf("%s", product[choice - 1]);
    printf("Enter new product price:");
    scanf("%d", & price[choice - 1]);
    stock[choice - 1] = MAX_STOCK;
    printf("The new product %c has been filled to full.\n", characters + choice);
}
