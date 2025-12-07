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
int findheadPos(int arr[], int n, int head) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == head)
            return i;
    }
    return -1;
}

// SCAN Disk Scheduling
void scan(int arr[], int n, int headPos) {
    printf("\n SCAN Order:\n");
        int diff1;
        int diff2;
        if(headPos>0)
            diff1 = arr[headPos]-arr[headPos-1];
        if(headPos < n-1)
        diff2 = arr[headPos+1]-arr[headPos];
       
    if(diff2 > diff1)
    {
        // Service requests to the right of head
    for (int i = headPos; i < n; i++) {
        printf("%d\t", arr[i]);
    }

    // Move to end of disk if needed
    if (arr[n - 1] != DISK_SIZE)
        printf("%d\t", DISK_SIZE);
    
     // Service remaining requests on the left side
    for (int i = headPos-1; i >= 0; i--) {
        printf("%d\t", arr[i]);
        }
    }
    else
    {
       // Service remaining requests on the left side
    for (int i = headPos-1; i >= 0; i--) {
            printf("%d\t", arr[i]);
            
        }
        printf("0\t");
        
        // Service requests to the right of head
    for (int i = headPos; i < n; i++) {
        printf("%d\t", arr[i]);
    }
        
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
    int headPos = findheadPos(arr, n + 1, head);

    scan(arr, n + 1, headPos);

    return 0;
}

