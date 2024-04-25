#include <stdio.h>

void buyLicenses(int n, double growth_rates[]) {
    int order[n];
    double total_cost = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (growth_rates[j] < growth_rates[j + 1]) {
                double temp = growth_rates[j];
                growth_rates[j] = growth_rates[j + 1];
                growth_rates[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        total_cost += 100 * growth_rates[i];
        order[i] = i + 1;
    }

    printf("Order of licenses to buy: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", order[i]);
    }
    printf("\nTotal cost: %.2f\n", total_cost);
}

int main() {
    int n;
    printf("Enter the number of licenses: ");
    scanf("%d", &n);

    double growth_rates[n];
    printf("Enter the growth rates of licenses:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &growth_rates[i]);
    }

    buyLicenses(n, growth_rates);

    return 0;
}
