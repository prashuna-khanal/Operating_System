#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

// Shared resource
int counter = 0;

// Mutex for synchronization
pthread_mutex_t mutex;

// System information thread
void *systemInfo(void *arg)
{
    struct utsname sysInfo;

    uname(&sysInfo);

    printf("[System Info Thread] OS: %s\n", sysInfo.sysname);
    printf("[System Info Thread] Version: %s\n", sysInfo.version);

    return NULL;
}

// Simulates a disk read operation
void *diskIO(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex);

        int temp = counter;
        sleep(1);
        temp++;
        counter = temp;

        printf("[Disk Thread] Counter = %d\n", counter);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Simulates a user process
void *userProcess(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex);

        int temp = counter;
        sleep(1);
        temp++;
        counter = temp;

        printf("[User Thread] Counter = %d\n", counter);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    printf("Main Process ID: %d\n\n", getpid());

    pthread_create(&thread1, NULL, systemInfo, NULL);
    pthread_create(&thread2, NULL, diskIO, NULL);
    pthread_create(&thread3, NULL, userProcess, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nExpected Counter = 10\n");
    printf("Final Counter = %d\n", counter);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("\nAll threads completed.\n");

    return 0;
}
