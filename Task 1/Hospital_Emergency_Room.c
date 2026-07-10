// Scenario: Hospital Emergency Room
/* Imagine a hospital where:
    1.Three patients arrive and need treatment.
    2.Each patient is handled by a separate thread.
    3.Only one doctor is available, so patients must wait for the doctor (mutex).
    4.The CPU scheduler is simulated using Round Robin to allocate consultation time.
    Without synchronization, two patients could try to use the doctor simultaneously (race condition).
    5.Deadlock is prevented as same rule is followed: acquire and release the doctor's mutex before treatment.
*/
