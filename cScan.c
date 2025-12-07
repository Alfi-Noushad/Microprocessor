#include <stdio.h>

#define DISK_SIZE 200

// Simple Bubble Sort (ascending)
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Find head position in sorted array
int findHeadPos(int arr[], int n, int head) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == head)
            return i;
    }
    return -1;
}

// C-SCAN Disk Scheduling
void cscan(int arr[], int n, int headPos) {
    printf("\nC-SCAN Order:\n");

    // Service requests to the right of head
    for (int i = headPos; i < n; i++) {
        printf("%d\t", arr[i]);
    }

    // Move to end of disk if needed
    if (arr[n - 1] != DISK_SIZE)
        printf("%d\t", DISK_SIZE);

    // Jump back to start
    printf("0\t");

    // Service remaining requests on the left side
    for (int i = 0; i < headPos; i++) {
        printf("%d\t", arr[i]);
    }

    printf("\n");
}

// Main Function
int main() {
    int n, head;
    int arr[20];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    arr[0] = head;
    for (int i = 1; i <= n; i++) {
        printf("Enter request %d: ", i);
        scanf("%d", &arr[i]);
    }

    sort(arr, n + 1); // Sort all requests + head
    int headPos = findHeadPos(arr, n + 1, head);

    cscan(arr, n + 1, headPos);

    return 0;
}
