#include <stdio.h>

void main() {
    int numPages, pageArray[100], numFrames, frameArray[100], i, j;

    printf("ENTER THE NUMBER OF PAGES: ");
    scanf("%d", &numPages);

    printf("ENTER REFERENCE STRING:");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pageArray[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &numFrames);

    for (i = 0; i < numFrames; i++) {
        frameArray[i] = -1;
    }

    int found, pfc = 0, totalHits = 0;
    float missRatio, hitRatio;
    int frameIndex = 0;

    for (i = 0; i < numPages; i++) {
        found = 0;
        printf("\t%d\t\t", pageArray[i]);

        for (j = 0; j < numFrames; j++) {
            if (frameArray[j] == pageArray[i]) {
                found = 1;
                totalHits++;
            }
        }

        if (found == 0) {
            frameArray[frameIndex] = pageArray[i];
            frameIndex = (frameIndex + 1) % numFrames;
            pfc++;
        }

        for (j = 0; j < numFrames; j++) {
            if (frameArray[j] != -1) {
                printf("%d  ", frameArray[j]);
            }
        }
        printf("\n");
        printf("\n");
    }

    int totalPageReferences = numPages;
    int totalPageFaults = pfc;
    missRatio = (float) totalPageFaults / totalPageReferences;
    hitRatio = (float) totalHits / totalPageReferences;

    printf("Total Page Faults: %d\n", totalPageFaults);
    printf("Total Hits: %d\n", totalHits);
    printf("Miss Ratio: %.2f\n", missRatio);
    printf("Hit Ratio: %.2f\n", hitRatio);
}

//7 0 2 1 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1



/*#include<stdio.h>

void main(){
    int numPages,pageArray[100],numFrames,frameArray[100],i,j;

    printf("ENTER THE NUMBER OF PAGES: ");
    scanf("%d", &numPages);
    
    printf("ENTER REFERENCE STRING:");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pageArray[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES: ");
    scanf("%d", &numFrames);

    for (i = 0; i < numFrames; i++) {
        frameArray[i] = -1;
    }
    
    int found,pfc=0,frameIndex=0;
    for(i = 0; i < numPages; i++){
        found=0;
       printf("\t%d\t\t", pageArray[i]);

       for(j = 0; j < numFrames; j++){
          if(frameArray[j] == pageArray[i]){
            found=1;
          }
       }

       if(found==0){
          frameArray[frameIndex]=pageArray[i];
          frameIndex = (frameIndex + 1) % numFrames;
          pfc++;
       }

       for(j=0 ; j<numFrames ; j++){
        if(frameArray[j]!=-1){
            printf("%d  ",frameArray[j]);
        }
       }
       printf("\n");
       printf("\n");
    }

}*/

