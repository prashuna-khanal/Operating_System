#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

// System information thread
void *systemInfo(void *arg)
{
    struct utsname sysInfo;

    uname(&sysInfo);

    printf("[System Info Thread] OS: %s\n", sysInfo.sysname);
    printf("[System Info Thread] Version: %s\n", sysInfo.version);

    return NULL;
}

int counter = 0;
// Simulates a disk read operation
void *diskIO(void *arg)
{
    for(int i = 0; i < 5; i++)
    {
        int temp = counter;
        sleep(1);  
        temp++;       
        counter = temp;   //counter is accessed as a shared variable simultaneously by two threads

        printf("[Disk Thread] Counter = %d\n", counter);
    }

    return NULL;
}

// Simulates a user process
void *userProcess(void *arg)
{
    for(int i = 0; i < 5; i++)
    {
        int temp = counter;
        sleep(1);          
        temp++;
        counter = temp;

        printf("[User Thread] Counter = %d\n", counter);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;

    printf("Main Process ID: %d\n\n", getpid());

    pthread_create(&thread1, NULL, systemInfo, NULL);
    pthread_create(&thread2, NULL, diskIO, NULL);
    pthread_create(&thread3, NULL, userProcess, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nAll threads completed.\n");

    return 0;
}
