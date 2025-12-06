#include <stdio.h>

int main() {
    int pages[25], frames[10], freq[25], time[25];
    int total_pages, total_frames;
    int i, j, k, min_freq, min_time, pos;
    int page_faults = 0, page_hits = 0, counter = 0, avail;

    printf("Enter total number of pages: ");
    scanf("%d", &total_pages);

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);

    // Input the reference string
    printf("Enter the reference string:\n");
    for (i = 0; i < total_pages; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize all frames as empty
    for (i = 0; i < total_frames; i++) {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }
    
     printf("\nReference\t Frames\n");
     

    // Process each page
    for (i = 0; i < total_pages; i++) {
        avail = 0;
        counter++; // To keep track of usage time
        printf("%d\t\t",pages[i]);

        // Check if page already exists (HIT)
        for (j = 0; j < total_frames; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;          // Increase frequency
                time[j] = counter;  // Update recent use
                avail = 1;
                page_hits++;
                break;
            }
        }

        // If page not avail (FAULT)
        if (!avail) {
            // Find empty frame
            for (j = 0; j < total_frames; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    freq[j] = 1;
                    time[j] = counter;
                    page_faults++;
                    avail = 1;
                    break;
                }
            }
        }

        // If no empty frame — replace LFU (tie → LRU)
        if (!avail) {
            min_freq = freq[0];
            pos = 0;

            // Find page with least frequency
            for (j = 1; j < total_frames; j++) {
                if (freq[j] < min_freq) {
                    min_freq = freq[j];
                    pos = j;
                }
                // If same frequency, replace least recently used
                else if (freq[j] == min_freq && time[j] < time[pos]) {
                    pos = j;
                }
            }

            // Replace the selected page
            frames[pos] = pages[i];
            freq[pos] = 1;
            time[pos] = counter;
            page_faults++;
        }

        // Print frame status
        //printf("\nReference\t Frames\n");
        //printf("%d\n",pages[i]);
        for (k = 0; k < total_frames; k++) {
            if (frames[k] != -1)
                printf("%d\t", frames[k]);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("\n\nTotal Page Faults: %d", page_faults);
    printf("\nTotal Page Hits: %d\n", page_hits);

    return 0;
}
