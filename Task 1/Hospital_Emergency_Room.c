// Scenario: Hospital Emergency Room
/* Imagine a hospital where:
    1.Three patients arrive and need treatment.
    2.Each patient is handled by a separate thread.
    3.Only one doctor is available, so patients must wait for the doctor (mutex).
    4.The CPU scheduler is simulated using Round Robin to allocate consultation time.
    Without synchronization, two patients could try to use the doctor simultaneously (race condition).
    5.Deadlock is prevented as same rule is followed: acquire and release the doctor's mutex before treatment.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PATIENTS 3

// Shared resource
int patientsTreated = 0;

// Mutex (Doctor)
pthread_mutex_t doctor;

// Process structure for Round Robin
typedef struct
{
    char name[20];
    int treatmentTime;
} Patient;

// Patient Thread
void *patient(void *arg)
{
    char *name = (char *)arg;
    printf("%s arrived at the hospital.\n", name);
    // Patient waits until doctor is free
    pthread_mutex_lock(&doctor);
    printf("%s is being treated by the doctor.\n", name);
    sleep(2);
    patientsTreated++;
    printf("%s finished treatment.\n", name);
    printf("Patients Treated = %d\n\n", patientsTreated);
    pthread_mutex_unlock(&doctor);
    return NULL;
}

// Round Robin Scheduler
void roundRobin(Patient p[], int n, int quantum)
{
    int remaining[n];
    for(int i=0;i<n;i++)
        remaining[i]=p[i].treatmentTime;

    printf("Round Robin Doctor Scheduling\n");
    int finished;
    do
    {
        finished = 1;
        for(int i=0;i<n;i++)
        { if(remaining[i]>0){
                finished = 0;
                if(remaining[i]>quantum)
                {
                    printf("%s receives treatment for %d minutes.\n",
                           p[i].name, quantum);
                    remaining[i]-=quantum;
                }
                else
                {
                    printf("%s receives treatment for %d minutes and leaves.\n",
                           p[i].name, remaining[i]);
                    remaining[i]=0;
                }
            }
        }

    }while(!finished);
}
int main()
{
    pthread_t p1,p2,p3;
    pthread_mutex_init(&doctor,NULL);
    printf("\nHospital Emergency Room\n");
    pthread_create(&p1,NULL,patient,"Patient A");
    pthread_create(&p2,NULL,patient,"Patient B");
    pthread_create(&p3,NULL,patient,"Patient C");
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    printf("Total Patients Treated = %d\n", patientsTreated);
    Patient patients[] =
    {
        {"Patient A",5},
        {"Patient B",3},
        {"Patient C",4}
    };
    roundRobin(patients,3,2);
    pthread_mutex_destroy(&doctor);
    printf("\nDoctor's shift ended successfully.\n");
    return 0;
}
