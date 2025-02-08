#include <stdio.h>
#include <stdlib.h>

struct Item {
    int enjoyment;
    int weight;
    float ratio;
};

// Function to compare items based on the ratio in descending order
int compareItems(const void *a, const void *b) {
    return (((struct Item *)b)->ratio - ((struct Item *)a)->ratio);
}

// Function to solve the fractional knapsack problem
float knapsackFractional(struct Item items[], int n, int maxWeight) {
    // Calculate value-to-weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].enjoyment / items[i].weight;
    }

    // Sort items based on ratio in descending order
    qsort(items, n, sizeof(struct Item), compareItems);

    float totalEnjoyment = 0;
    int totalWeight = 0;

    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= maxWeight) {
            // Add the entire item to the backpack
            totalEnjoyment += items[i].enjoyment;
            totalWeight += items[i].weight;
        } else {
            // Add a fraction of the item to fill the remaining capacity
            float fraction = (float)(maxWeight - totalWeight) / items[i].weight;
            totalEnjoyment += fraction * items[i].enjoyment;
            break;  // Backpack is full
        }
    }

    return totalEnjoyment;
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item *items = (struct Item *)malloc(n * sizeof(struct Item));

    printf("Enter the enjoyment and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &items[i].enjoyment, &items[i].weight);
    }

    int maxWeight;
    printf("Enter the maximum weight of the backpack: ");
    scanf("%d", &maxWeight);

    float maxEnjoyment = knapsackFractional(items, n, maxWeight);

    printf("Maximum enjoyment: %.2f\n", maxEnjoyment);

    free(items);

    return 0;
}
