# Memory Management Simulation
#include <stdio.h>
#define size 10

int pages[size] = {1,2,3,2,4,1,5,2,1,2};
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
    return 0;
}
