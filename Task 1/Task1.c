#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>

// Shared resource
int counter = 0;

// Mutex for synchronization
pthread_mutex_t mutex;

// Structure for Round Robin processes
typedef struct
{
    char name[10];
    int burstTime;
} Process;

// System Information Thread
void *systemInfo(void *arg)
{
    struct utsname sysInfo;

    uname(&sysInfo);

    printf("[System Info Thread] OS: %s\n", sysInfo.sysname);
    printf("[System Info Thread] Version: %s\n", sysInfo.version);

    return NULL;
}

// Disk I/O Thread
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

// User Process Thread
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

// Round Robin Scheduler
void roundRobin(Process processes[], int n, int quantum)
{
    int remaining[n];

    // Copy burst times
    for (int i = 0; i < n; i++)
    {
        remaining[i] = processes[i].burstTime;
    }

    printf("Round Robin Scheduling\n");
    printf("Time Quantum = %d\n\n", quantum);

    int done;

    do
    {done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                done = 0;

                if (remaining[i] > quantum)
                {
                    printf("%s runs for %d units\n",
                           processes[i].name,
                           quantum);

                    remaining[i] -= quantum;
                }
                else
                {
                    printf("%s runs for %d units and finishes\n",
                           processes[i].name,
                           remaining[i]);

                    remaining[i] = 0;
                }
            }
        }

    } while (!done);
}

// Main Function
int main()
{
    pthread_t thread1, thread2, thread3;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    printf("Main Process ID: %d\n\n", getpid());

    // Create threads
    pthread_create(&thread1, NULL, systemInfo, NULL);
    pthread_create(&thread2, NULL, diskIO, NULL);
    pthread_create(&thread3, NULL, userProcess, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nExpected Counter = 10\n");
    printf("Final Counter = %d\n", counter);

    // Round Robin Simulation
    Process processes[] =
    {
        {"P1", 5},
        {"P2", 3},
        {"P3", 4}
    };

    roundRobin(processes, 3, 2);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("\nAll threads completed.\n");

    return 0;
}
