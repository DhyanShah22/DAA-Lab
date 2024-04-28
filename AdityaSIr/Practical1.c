#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int id;
    int cost;
    double rate;
    int quantity;
    double ratio;
} Asset;

int compare(const void *A, const void *B)
{
    if(((Asset *) B)->ratio - ((Asset *) A)->ratio < 0)
    {
        return -1;
    }

    else if( ((Asset *) B)->ratio - ((Asset *) A)->ratio == 0 )
    {
        return 0;
    }

    return 1;
}
void maxProfit(Asset assets[], int size, int budget, int time)
{
    qsort(assets, size, sizeof(Asset), compare);
    Asset purchased[time];
    int i = 0;
    int limit = 0;
    int spent = 0;

    while(spent < budget && limit < time)
    {
        if(assets[i].quantity == 0)
        {
            i++;
        }
        
        spent += assets[i].cost;
        assets[i].quantity--;
        purchased[limit] = assets[i];
        printf("\nPurchase Asset %d at Month %d", assets[i].id, limit + 1);
        limit++;
    }

    int month = time;
    int profit = 0;

    for(int i = 0; i < time; i++)
    {
        profit += purchased[i].cost * purchased[i].rate * month;
        month--;
    }

    printf("\nThe total profit after %d months is : %d", time, profit);
}

void main()
{
    int budget, size, time;

    printf("How many assets do you wish to enter?");
    scanf("%d", &size);

    Asset assets[size];

    for(int i = 0; i < size; i++)
    {
        printf("\nEnter the details of asset number %d: ", i+1);
        printf("\nEnter the cost : ");
        scanf("%d", &assets[i].cost);

        printf("Enter the rate per unit : ");
        scanf("%lf", &assets[i].rate);

        printf("Enter the quantity available : ");
        scanf("%d", &assets[i].quantity);

        assets[i].id = i + 1;
        assets[i].ratio = assets[i].cost * assets[i].rate;
    }

    printf("\nWhat is your budget?\n");
    scanf("%d", &budget);

    printf("Time Limit : ");
    scanf("%d", &time);

    maxProfit(assets, size, budget, time);
}