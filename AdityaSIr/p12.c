#include <stdio.h>

int main()
{
    int price[] = {5,10,3,8,12,6,15,7,9,11};
    int day[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i <= 9; i++)
    {
        for (int j = i + 1; j <= 9; j++)
        {
            if (price[j] > price[i])
            {
                int temp = price[i];
                price[i] = price[j];
                price[j] = temp;

                int temp2 = day[i];
                day[i] = day[j];
                day[j] = temp2;
            }
        }
    }

    for (int k = 0; k <= 9; k++)
    {
        printf("%d  ", price[k]);
        printf("%d  \n", day[k]);
    }
    int max_profit = 0;

    for (int l = 0; l <= 4; l++)
    {
        max_profit += (price[l] - price[9 - l]);
    }
    printf("max profit: %d", max_profit);
}