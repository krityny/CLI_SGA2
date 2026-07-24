#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid[3];
    int i, status;

    // Create 3 child processes
    for(i = 0; i < 3; i++)
    {
        pid[i] = fork();

        if(pid[i] == 0)
        {
            printf("Child %d started. PID = %d\n", i + 1, getpid());

            // Make Child 2 unresponsive
            if(i == 1)
            {
                printf("Child %d is running for 15 seconds...\n", i + 1);
                sleep(15);
            }
            else
            {
                printf("Child %d is running for 3 seconds...\n", i + 1);
                sleep(3);
            }

            printf("Child %d finished successfully.\n", i + 1);
            exit(0);
        }
    }

    // Parent waits before checking children
    sleep(5);

    printf("\nParent is checking child processes...\n");

    // Monitor each child
    for(i = 0; i < 3; i++)
    {
        if(waitpid(pid[i], &status, WNOHANG) == 0)
        {
            printf("Child %d (PID %d) is unresponsive. Terminating...\n",
                   i + 1, pid[i]);

            kill(pid[i], SIGKILL);

            // Collect terminated child to prevent zombie
            waitpid(pid[i], &status, 0);

            printf("Child %d terminated successfully.\n", i + 1);
        }
        else
        {
            printf("Child %d completed normally.\n", i + 1);
        }
    }

    printf("\nAll child processes have been handled.\n");
    printf("Zombie processes prevented.\n");

    return 0;
}

