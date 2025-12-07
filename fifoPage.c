#include <stdio.h>

int main() {
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;

    printf("\nEnter the number of pages: ");
    scanf("%d", &n);

    printf("\nEnter the page numbers:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    printf("\nEnter the number of frames: ");
    scanf("%d", &no);

    for (i = 0; i < no; i++) {
        frame[i] = -1;
    }

    j = 0;

    printf("\nRefString\tPage Frames\n");

    for (i = 1; i <= n; i++) {
        printf("%d\t\t", a[i]);
        avail = 0;

        // Check if page is already in frame
        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }

        // If not available → page fault occurs
        if (avail == 0) {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;

            for (k = 0; k < no; k++) {
                if (frame[k] != -1)
                    printf("%d\t", frame[k]);
                else
                    printf("-\t");
            }
        }

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", count);

    return 0;
}
