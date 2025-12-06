#include <stdio.h>
#include <stdlib.h>

void main()  
{  
    int track[20], n, head, i, s = 0;  
    float avg;  

    printf("\nEnter number of tracks: ");  
    scanf("%d", &n);  

    printf("Enter track positions:\n");  
    for(i = 0; i < n; i++)  
    {  
        scanf("%d", &track[i]);  
    }  

    printf("Enter the initial head position: ");  
    scanf("%d", &head);  

    printf("\nTrack\tHead Movement\n");  

    for(i = 0; i < n; i++)  
    {  
        int diff = abs(track[i] - head);  
        printf("%d\t\t%d\n", track[i], diff);  
        s += diff;  
        head = track[i];  
    }  

    printf("\nTotal head movement: %d", s);  
    avg = s / (float)n;  
    printf("\nAverage head movement: %.2f\n", avg);  
}
