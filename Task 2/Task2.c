//Memory Management Simulation
#include <stdio.h>
#define size 10

int pages[size] = {1,2,3,2,4,1,5,2,1,2};

void printFrames(int frame[], int frameSize)
{
    int i;
    printf("Frames: ");
    for(i = 0; i < frameSize; i++)
    {
        if(frame[i] == -1)
            printf("- ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}
// FIFO implemented
void FIFO(int frameSize){
    int frame[10], i, j, index = 0, hits = 0, faults = 0;
    for(i=0;i<frameSize;i++) frame[i]=-1;
    printf("\n FIFO\n");
    for(i=0;i<size;i++){
        int found=0;
        for(j=0;j<frameSize;j++)
            if(frame[j]==pages[i]) { found=1; break; }
        if(found){
            hits++;
            printf("Page %d -> HIT\n",pages[i]);}
        else{
            faults++;
            printf("Page %d -> FAULT\n",pages[i]);
            frame[index]=pages[i];
            index=(index+1)%frameSize;}
        printFrames(frame,frameSize);
    }
    printf("\nHits: %d",hits);
    printf("\nFaults: %d",faults);
    printf("\nHit Ratio: %.2f",(float)hits/size);
    printf("\nMiss Ratio: %.2f\n",(float)faults/size);
}
// LRU implementation
void LRU(int frameSize){
    int frame[10], recent[10], i, j, hits=0, faults=0;
    for(i=0;i<frameSize;i++)
        frame[i]=recent[i]=-1;
    printf("\n LRU \n");
    for(i=0;i<size;i++){
        int found=0;
        for(j=0;j<frameSize;j++)
            if(frame[j]==pages[i]) { found=1; hits++; recent[j]=i; break; }
        if(!found){
            faults++;
            int empty=-1;
            for(j=0;j<frameSize;j++)
                if(frame[j]==-1){ empty=j; break; }
            if(empty!=-1){
                frame[empty]=pages[i];
                recent[empty]=i;
            }
            else{
                int least=0;
                for(j=1;j<frameSize;j++)
                    if(recent[j]<recent[least]) least=j;
                frame[least]=pages[i];
                recent[least]=i;}
            printf("Page %d -> FAULT\n",pages[i]);
        }
        else
            printf("Page %d -> HIT\n",pages[i]);
        printFrames(frame,frameSize);
    }
    printf("\nHits: %d",hits);
    printf("\nFaults: %d",faults);
    printf("\nHit Ratio: %.2f",(float)hits/size);
    printf("\nMiss Ratio: %.2f\n",(float)faults/size);
}

int main()
{   int pageSize;
    int frameSize;
    int i;
    printf("Memory Management Simulator\n");
    printf("Enter Page Size (KB): ");
    scanf("%d",&pageSize);
    
    printf("Enter Number of Frames: ");
    scanf("%d",&frameSize);

    printf("\nPage Size = %d KB\n",pageSize);
    printf("Reference String:\n");

    for(i=0;i<size;i++)
        printf("%d ",pages[i]);
    printf("\n");
    FIFO(frameSize);
    LRU(frameSize);
    return 0;
}
