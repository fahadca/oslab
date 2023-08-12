#include <stdio.h>

struct Frame {
    int content;
    int frequency;
    int count;
};

int main() {
    int pages[100], numPages, numFrames, pfc = 0, frameIndex = 0, totalHits = 0;
    int i, j;
    struct Frame frames[100];

    printf("ENTER THE NUMBER OF PAGES: ");
    scanf("%d", &numPages);

    printf("ENTER THE REFERENCE STRING: ");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &numFrames);

    for (i = 0; i < numFrames; i++) {
        frames[i].content = -1;
        frames[i].frequency = 0;
        frames[i].count = 0;
    }

    int next = 1; // Initialize the next order value

    for (i = 0; i < numPages; i++) {
        printf("\t%d\t\t", pages[i]);

        int pageFound = 0;

        for (j = 0; j < numFrames; j++) {
            if (frames[j].content == pages[i]) {
                frames[j].frequency++;
                totalHits++;
                                          //frames[j].count = next++; // Assign and increment next
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            if (frameIndex < numFrames) {
                frames[frameIndex].content = pages[i];
                frames[frameIndex].frequency++;
                frames[frameIndex].count = next++; // Assign and increment next
                frameIndex++;
            } else {
                int minFrequency = 0;

                for (j = 0; j < numFrames; j++) {
                    if (frames[minFrequency].frequency > frames[j].frequency ||
                        (frames[minFrequency].frequency == frames[j].frequency && frames[minFrequency].count > frames[j].count)) {
                        minFrequency = j;
                    }
                }

                frames[minFrequency].content = pages[i];
                frames[minFrequency].frequency = 1;
                frames[minFrequency].count = next++; // Assign and increment next
            }

            pfc++;
        }

        for (j = 0; j < numFrames; j++) {
            if (frames[j].content != -1) {
                printf("%d\t", frames[j].content);
            }
        }

        printf("\n");
    }

    int totalPageReferences = numPages;
    int totalPageFaults = pfc;
    float missRatio = (float) totalPageFaults / totalPageReferences;
    float hitRatio = (float) totalHits / totalPageReferences;

    printf("Total Page Faults: %d\n", totalPageFaults);
    printf("Total Hits: %d\n", totalHits);
    printf("Miss Ratio: %.2f\n", missRatio);
    printf("Hit Ratio: %.2f\n", hitRatio);

    return 0;
}
