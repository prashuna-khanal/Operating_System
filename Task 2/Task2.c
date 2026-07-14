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
void FIFO(int frameSize)
{
    int frame[10];
    int i,j;
    int index=0;
    for(i=0;i<frameSize;i++)
        frame[i]=-1;

    printf("\nFIFO Simulation\n");

    for(i=0;i<size;i++){
      int found=0;
      for(j=0;j<frameSize;j++){
            if(frame[j]==pages[i]){
                found=1;
                break;}}
      if(found){printf("Page %d -> HIT\n",pages[i]);}
      else{printf("Page %d -> FAULT\n",pages[i]);
          frame[index]=pages[i];
          index=(index+1)%frameSize;}
      printFrames(frame,frameSize);
    }
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
    return 0;
}
