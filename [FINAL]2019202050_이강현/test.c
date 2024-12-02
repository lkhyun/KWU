#include "includes.h"
#define MAX_PRODUCTS 100
#define MAX_TASKS 5
#define STACK_SIZE 8192
#define MAX_QUEUE_SIZE 10

typedef struct
{
    char name[50];
    int price;
    int inventory;
    char location[100];
} Product;

typedef struct
{
    char name[50];
    int quantity;
    int price;
    int remove; //add or subtract flag
} CartItem;

typedef enum {
    SHOW_PRODUCT_LIST,
    SHOW_CART_CONTENTS,
    ADD_TO_CART,
    REMOVE_FROM_CART,
    PROCESS_PAYMENT
} MsgType;

typedef struct
{
    MsgType type;
    union {
        CartItem cartItem;
        char password[5];
    } data;
} Message; //IPC

Product productList[MAX_PRODUCTS];// total products
CartItem cart[MAX_PRODUCTS]; //individual cart
int productCount = 0;
int cartCount = 0;

OS_STK TaskStk[MAX_TASKS][STACK_SIZE];
OS_EVENT* Sem;//semaphore
OS_EVENT* QueueMsg;//message queue
void* QueueMem[MAX_QUEUE_SIZE];

// Task priorities
enum {
    TASK_LOAD_PRIO = 10,
    TASK_INPUT_PRIO,
    TASK_PAY_PRIO,
    TASK_CART_PRIO,
    TASK_UI_PRIO
};


// task and function
void TaskInput(void* p_arg);
void TaskUI(void* p_arg);
void TaskLoadProducts(void* p_arg);
void TaskCartManagement(void* p_arg);
void TaskPaymentProcessing(void* p_arg);
int CheckPassword(const char* inputPassword);

int main(void) {
    OSInit();

    Sem = OSSemCreate(1);  //create semaphore
    QueueMsg = OSQCreate(QueueMem, MAX_QUEUE_SIZE); //create message queue
    
    OSTaskCreate(TaskInput, NULL, &TaskStk[0][STACK_SIZE - 1], TASK_INPUT_PRIO);
    OSTaskCreate(TaskUI, NULL, &TaskStk[1][STACK_SIZE - 1], TASK_UI_PRIO);
    OSTaskCreate(TaskLoadProducts, NULL, &TaskStk[2][STACK_SIZE - 1], TASK_LOAD_PRIO);
    OSTaskCreate(TaskCartManagement, NULL, &TaskStk[3][STACK_SIZE - 1], TASK_CART_PRIO);
    OSTaskCreate(TaskPaymentProcessing, NULL, &TaskStk[4][STACK_SIZE - 1], TASK_PAY_PRIO);

    OSStart(); //multitasking
    return 0;
}

void TaskInput(void* p_arg)
{
    char buffer[100];
    while (1)
    {
        if (_kbhit()) //input or not
        {
            char c = _getch(); //user input
            printf("input : %c\n", c);
            if (c == 'l') {
                // print products list
                Message* msg = (Message*)malloc(sizeof(Message)); //create new message
                msg->type = SHOW_PRODUCT_LIST;
                if (OSQPost(QueueMsg, (void*)msg) != 0) {
                    printf("message queue is full.\n");
                    free(msg);
                }
                MyKernelFunc(TASK_UI_PRIO,NULL);//save request UI
            }
            else if (c == 'c') {
                // all cart list
                Message* msg = (Message*)malloc(sizeof(Message));
                msg->type = SHOW_CART_CONTENTS;
                if (OSQPost(QueueMsg, (void*)msg) != 0) {
                    printf("message queue is full.\n");
                    free(msg);
                }
                MyKernelFunc(TASK_UI_PRIO,NULL);//save request UI
            }
            else if (c == 'a') {
                // add to cart
                INT8U err;
                printf("Enter product name and quantity(ex: Apple 3)\n");
                fgets(buffer, 100, stdin);
                buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character

                Message* msg = (Message*)malloc(sizeof(Message));//create new message
                msg->type = ADD_TO_CART;
                sscanf(buffer, "%s %d", msg->data.cartItem.name, &msg->data.cartItem.quantity);//Separate product name and quantity

                //Find and add items to the list of items
                OSSemPend(Sem, 0, &err);//enter critical section
                int found = 0;
                for (int i = 0; i < productCount; i++) {
                    if (strcmp(productList[i].name, msg->data.cartItem.name) == 0) {
                        if (productList[i].inventory >= msg->data.cartItem.quantity) {
                            msg->data.cartItem.price = productList[i].price;
                            msg->data.cartItem.remove = 0; //add flag
                            found = 1;//item exists
                        }
                        else {
                            printf("Out of stock.\n");
                            found = -1;
                        }
                        break;
                    }
                }
                OSSemPost(Sem);//escape critical section

                if (found == 0) {
                    printf("Product not found.\n");
                    free(msg);
                }
                else if (found == 1) {
                    if (OSQPost(QueueMsg, (void*)msg) != 0) {
                        printf("message queue is full.\n");
                        free(msg);
                    }
                }
                else {
                    free(msg);
                }
                strcat(buffer, " +");
                MyKernelFunc(TASK_CART_PRIO,buffer);//save request CART and detail
            }
            else if (c == 'r') {
                // remove
                printf("Enter product name and quantity(ex: Apple 3)\n");
                fgets(buffer, 100, stdin);
                buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character

                Message* msg = (Message*)malloc(sizeof(Message));//create new message
                msg->type = REMOVE_FROM_CART;
                sscanf(buffer, "%s %d", msg->data.cartItem.name, &msg->data.cartItem.quantity);//Separate product name and quantity
                msg->data.cartItem.remove = 1; //subtract flag

                if (OSQPost(QueueMsg, (void*)msg) != 0) {
                    printf("message queue is full.\n");
                    free(msg);
                }
                strcat(buffer, " -");
                MyKernelFunc(TASK_CART_PRIO,buffer);//save request CART and detail
            }
            else if (c == 'p') {
                // purchase
                printf("Please enter your 4-digit password:\n");
                fgets(buffer, 100, stdin);
                buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character

                Message* msg = (Message*)malloc(sizeof(Message));
                msg->type = PROCESS_PAYMENT;
                strncpy(msg->data.password, buffer, 4);
                msg->data.password[4] = '\0'; // Ensure null-terminated

                if (OSQPost(QueueMsg, (void*)msg) != 0) {
                    printf("message queue is full.\n");
                    free(msg);
                }
                MyKernelFunc(TASK_PAY_PRIO,NULL);//save request PAY and detail
            }
            else if (c == 'e') {//exit
                MyKernelPrintFunc();// record output
                exit(0);
            }
        }
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

void TaskUI(void* p_arg) {
    while (1) {
        INT8U err;
        OSTaskSuspend(OS_PRIO_SELF);//waiting for request on its own
        void* msg;
        if ((msg = OSQAccept(QueueMsg)) != NULL) {//Receive message
            Message* message = (Message*)msg;
            if (message->type == SHOW_PRODUCT_LIST) {
                OSSemPend(Sem, 0, &err);  // Enter critical section
                printf("Current product list:\n");
                for (int i = 0; i < productCount; i++) {
                    printf("Product Name: %s, Price: %d, Stock: %d, Location: %s\n", productList[i].name, productList[i].price, productList[i].inventory, productList[i].location);
                }
                OSSemPost(Sem);  // Escape critical section
            }
            else if (message->type == SHOW_CART_CONTENTS) {
                printf("Current cart list:\n");
                for (int i = 0; i < cartCount; i++) {
                    printf("Product Name: %s, Count: %d, Price: %d\n", cart[i].name, cart[i].quantity, cart[i].price * cart[i].quantity);
                }
            }
            free(message);
        }
        MyKernelResponseFunc(2);//No need save detail
    }
}

void TaskLoadProducts(void* p_arg) {
    INT8U err;
    OSSemPend(Sem, 0, &err);  // Enter critical section
    FILE* file = fopen("products.txt", "r");//load product list from txt
    if (file == NULL) {
        printf("Failed to open file\n");
    }
    else {
        while (fscanf(file, "%49[^,],%d,%d,%99[^\n]\n", productList[productCount].name, &productList[productCount].price, &productList[productCount].inventory, productList[productCount].location) == 4) {
            productCount++;
        }//Separate and save with , as a delimiter
        fclose(file);
        printf("Product list is initialized.\n");
    }
    OSSemPost(Sem);  //Escape critical section
    printf("Loaded products:\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product Name: %s, Price: %d, Stock: %d, Location: %s\n", productList[i].name, productList[i].price, productList[i].inventory, productList[i].location);
    }
    printf("<Command List>\n");
    printf("l: print list\na: add to cart\nr: remove from cart\np: purchase cart item\n");
    OSTaskDel(OS_PRIO_SELF);//Run only once
}

void TaskCartManagement(void* p_arg) {
    while (1) {
        OSTaskSuspend(OS_PRIO_SELF); //waiting for request on its own
        INT8U err;
        void* msg;
        if ((msg = OSQPend(QueueMsg, 0, &err)) != NULL) {
            Message* message = (Message*)msg;
            if (message->type == ADD_TO_CART || message->type == REMOVE_FROM_CART) {
                CartItem* item = &message->data.cartItem;
                int found = 0;
                OSSemPend(Sem, 0, &err);// Enter critical section
                for (int i = 0; i < cartCount; i++) {
                    if (strcmp(cart[i].name, item->name) == 0) {
                        if (message->type == ADD_TO_CART) {
                            cart[i].quantity += item->quantity;
                            MyKernelResponseFunc(1);//Add to Cart Success
                        }
                        else {
                            if (cart[i].quantity >= item->quantity) {
                                cart[i].quantity -= item->quantity;
                                MyKernelResponseFunc(1);//Remove from Cart Success
                            }
                            else {
                                printf("There are fewer %s than your request.\n", item->name);
                                MyKernelResponseFunc(0);////Remove from Cart Success
                            }
                        }
                        found = 1;
                        break;
                    }
                }
                OSSemPost(Sem);//Escape critical section
                if (!found && message->type == ADD_TO_CART) {//If it already exists in your cart
                    strcpy(cart[cartCount].name, item->name);
                    cart[cartCount].quantity = item->quantity;
                    cart[cartCount].price = item->price;
                    cartCount++;
                    MyKernelResponseFunc(1);////Add to Cart Success
                }
                else if (!found && message->type == REMOVE_FROM_CART) {
                    printf("No %s found..\n", item->name);
                    MyKernelResponseFunc(0);//Remove from Cart Success
                }
            }
            free(message);
        }
    }
}

void TaskPaymentProcessing(void* p_arg) {
    while (1) {
        OSTaskSuspend(OS_PRIO_SELF);//waiting for request on its own
        int lateflag = 0;
        INT8U err;
        void* msg;
        if ((msg = OSQPend(QueueMsg, 0, &err)) != NULL) {
            Message* message = (Message*)msg;
            if (message->type == PROCESS_PAYMENT) {
                if (CheckPassword(message->data.password)) {
                    OSSemPend(Sem, 0, &err);// Enter critical section
                    for (int i = 0; i < cartCount; i++) {
                        for (int j = 0; j < productCount; j++) {
                            if (strcmp(cart[i].name, productList[j].name) == 0)
                            {
                                if (productList[j].inventory < cart[i].quantity)
                                {
                                    lateflag = 1;//someone was already bought
                                    cart[i].quantity = 0;
                                    printf("%s Out of stock\n", cart[i].name);
                                    break;
                                }
                            }//Remove cart contents from product list
                        }
                        if (lateflag == 1) { break; }
                    }
                    if (lateflag == 1)//out of stock
                    {
                        printf("Payment Failure.\n");
                        MyKernelResponseFunc(0);
                    }
                    else
                    {
                        for (int i = 0; i < cartCount; i++) {
                            for (int j = 0; j < productCount; j++) {
                                if (strcmp(cart[i].name, productList[j].name) == 0)
                                {
                                    productList[j].inventory -= cart[i].quantity;
                                    break;
                                }//Remove cart contents from product list
                            }
                        }
                        cartCount = 0;
                        printf("Payment Successful.\n");
                        MyKernelResponseFunc(1);
                    }
                    OSSemPost(Sem);//Escape critical section
                }
                else {
                    printf("Passwords do not match..\n");
                    MyKernelResponseFunc(0);
                }
            }
            free(message);
        }
    }
}
int CheckPassword(const char* inputPassword) {
    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("File open fail.\n");
        return 0;
    }

    char storedPassword[5];
    if (fgets(storedPassword, 5, file) == NULL) {
        fclose(file);
        return 0;
    }

    fclose(file);
    return strcmp(inputPassword, storedPassword) == 0;
}
