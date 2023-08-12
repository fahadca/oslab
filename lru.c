#include <stdio.h>

struct Frame {
    int content;
    int usageCount;
};

void main() {
    int i, j, k, numPages, numFrames, referencingPages[100], pageFaultCount = 0, frameIndex = 0;
    int currentCount = 1, minCount = 0, totalHits = 0;

    printf("ENTER THE NUMBER OF PAGES: ");
    scanf("%d", &numPages);

    printf("ENTER THE REFERENCING STRING: ");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &referencingPages[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &numFrames);

    struct Frame frames[100];

    for (i = 0; i < numFrames; i++) {
        frames[i].content = -1;
        frames[i].usageCount = 0;
    }

    printf("\nREFERENCING PAGE\tSTATUS\t\tFRAME CONTENT\n\n");

    for (i = 0; i < numPages; i++) {
        printf("\t%d\t\t", referencingPages[i]);

        int pageFound = 0;

        for (j = 0; j < numFrames; j++) {
            if (frames[j].content == referencingPages[i]) {
                printf("HIT\t\t");
                frames[j].usageCount = currentCount++;
                pageFound = 1;
                totalHits++;
                break;
            }
        }

        if (!pageFound) {
            printf("MISS\t\t");

            if (frameIndex < numFrames) {
                frames[frameIndex].content = referencingPages[i];
                frames[frameIndex].usageCount = currentCount++;
                frameIndex++;
            } else {
                minCount = 0;
                for (k = 0; k < numFrames; k++) {
                    if (frames[k].usageCount < frames[minCount].usageCount) {
                        minCount = k;
                    }
                }
                frames[minCount].content = referencingPages[i];
                frames[minCount].usageCount = currentCount++;
            }

            pageFaultCount++;
        }

        for (j = 0; j < numFrames; j++) {
            if (frames[j].content != -1) {
                printf("%d\t", frames[j].content);
            }
        }
        printf("\n");
    }

    int totalPageReferences = numPages;
    int totalPageFaults = pageFaultCount;
    float missRatio = (float) totalPageFaults / totalPageReferences;
    float hitRatio = (float) totalHits / totalPageReferences;

    printf("\nPAGE FAULT: %d\n", pageFaultCount);
    printf("Total Hits: %d\n", totalHits);
    printf("Miss Ratio: %.2f\n", missRatio);
    printf("Hit Ratio: %.2f\n", hitRatio);
}
