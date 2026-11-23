#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Item
{
    int id;
    char name[30];
    float rate;
};

struct Order
{
    int id;
    int qty;
    float amount;
};

float calculateAmount(float rate, int qty)
{
    return rate * qty;
}

void addToTotal(float *total, float amount)
{
    *total = *total + amount;
}

int main()
{
    struct Item menu[6] = {
        {1, "TEA", 18.00},
        {2, "COFFEE", 20.00},
        {3, "BOOST", 25.00},
        {4, "MILK", 15.00},
        {5, "SAMOSA", 10.00},
        {6, "VADAI", 10.00}
    };

    struct Order *order;
    order = (struct Order *)malloc(50 * sizeof(struct Order));

    if (order == NULL)
    {
        printf("Memory allocation failed!\n");
        return 0;
    }

    int choice, qty, n, i;
    int token = 1;
    int orderStatus;
    float total;

    char customer[50];
    char shopName[50];
    char continueShop;

    strcpy(shopName, "RIO TEA SHOP");

    do
    {
        n = 0;
        total = 0;
        orderStatus = 0;

        time_t now;
        struct tm *t;

        now = time(NULL);
        t = localtime(&now);

        printf("\n\n====================================\n");
        printf("          %s\n", shopName);
        printf("====================================\n");

        printf("TOKEN NO: %04d\n", token);

        printf("Enter customer name: ");
        scanf(" %49[^\n]", customer);

        printf("\n-------------- MENU --------------\n");

        for (i = 0; i < 6; i++)
        {
            printf("%d. %-12s Rs. %.2f\n",
                   menu[i].id,
                   menu[i].name,
                   menu[i].rate);
        }

        printf("---------------------------------\n");
        printf("Enter 0 to finish order.\n");

        while (1)
        {
            printf("\nEnter item number: ");
            scanf("%d", &choice);

            if (choice == 0)
            {
                break;
            }

            if (choice < 1 || choice > 6)
            {
                printf("Invalid item number!\n");
                continue;
            }

            printf("Enter quantity: ");
            scanf("%d", &qty);

            if (qty <= 0)
            {
                printf("Invalid quantity!\n");
                continue;
            }

            if (n >= 50)
            {
                printf("Order limit reached!\n");
                break;
            }

            order[n].id = choice;
            order[n].qty = qty;

            order[n].amount =
                calculateAmount(menu[choice - 1].rate, qty);

            addToTotal(&total, order[n].amount);

            n++;

            orderStatus |= 1;

            printf("Item added successfully!\n");
        }

        printf("\n\n");
        printf("====================================\n");
        printf("          %s\n", shopName);
        printf("====================================\n");

        printf("TOKEN NO: %04d\n", token);

        printf("DATE: %02d-%02d-%02d\n",
               t->tm_mday,
               t->tm_mon + 1,
               (t->tm_year + 1900) % 100);

        printf("TIME: %02d:%02d\n",
               t->tm_hour,
               t->tm_min);

        printf("------------------------------------\n");

        printf("%-12s %3s %6s %8s\n",
               "DESCRIPTION", "QTY", "RATE", "AMOUNT");

        printf("------------------------------------\n");

        for (i = 0; i < n; i++)
        {
            printf("%-12s %3d %6.2f %8.2f\n",
                   menu[order[i].id - 1].name,
                   order[i].qty,
                   menu[order[i].id - 1].rate,
                   order[i].amount);
        }

        printf("------------------------------------\n");
        printf("CUSTOMER: %s\n", customer);
        printf("CASH             : Rs. %.2f\n", total);
        printf("------------------------------------\n");

        if (orderStatus & 1)
        {
            printf("ORDER STATUS: COMPLETED\n");
        }
        else
        {
            printf("ORDER STATUS: NO ITEMS\n");
        }

        printf("------------------------------------\n");
        printf("      THANK YOU! VISIT AGAIN\n");
        printf("         HAVE A NICE DAY!\n");
        printf("------------------------------------\n");

        FILE *fp = fopen("receipt.txt", "a");

        if (fp != NULL)
        {
            fprintf(fp, "\n====================================\n");
            fprintf(fp, "          %s\n", shopName);
            fprintf(fp, "TOKEN NO: %04d\n", token);

            fprintf(fp, "DATE: %02d-%02d-%02d\n",
                    t->tm_mday,
                    t->tm_mon + 1,
                    (t->tm_year + 1900) % 100);

            fprintf(fp, "TIME: %02d:%02d\n",
                    t->tm_hour,
                    t->tm_min);

            fprintf(fp, "CUSTOMER: %s\n", customer);

            fprintf(fp, "------------------------------------\n");

            fprintf(fp, "%-12s %3s %6s %8s\n",
                    "DESCRIPTION", "QTY", "RATE", "AMOUNT");

            for (i = 0; i < n; i++)
            {
                fprintf(fp, "%-12s %3d %6.2f %8.2f\n",
                        menu[order[i].id - 1].name,
                        order[i].qty,
                        menu[order[i].id - 1].rate,
                        order[i].amount);
            }

            fprintf(fp, "------------------------------------\n");
            fprintf(fp, "TOTAL: Rs. %.2f\n", total);
            fprintf(fp, "THANK YOU! VISIT AGAIN!\n");
            fprintf(fp, "====================================\n");

            fclose(fp);

            printf("\nReceipt saved successfully!\n");
        }
        else
        {
            printf("\nFile could not be opened!\n");
        }

        token++;

        printf("\nDo you want to take the next order? (Y/N): ");
        scanf(" %c", &continueShop);

    } while (continueShop == 'Y' || continueShop == 'y');

    free(order);

    printf("\nShop billing system closed.\n");

    return 0;
}