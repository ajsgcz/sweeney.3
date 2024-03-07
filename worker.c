#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>

#define SHM_KEY 1234
#define MSG_KEY 5678
#define TERMINATION_SECONDS 10
#define TERMINATION_NANOSECONDS 0

struct Message {
    long mtype;
    // Define your message structure
};

int shmid;
int msqid;

void handleTermination() {
    // Cleanup shared memory and message queue
    // Terminate
}

void handleMessage(struct Message msg) {
    // Handle incoming message from oss
}
void detachFromSharedMemory(void *shmaddr) {
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
}
void signal_handler(int signum) {
    // Handle termination signals here
    if (signum == SIGINT) {
        printf("Received SIGINT signal. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}


void startWorker(int seconds, int nanoseconds) {
    // Attach to shared memory
    // Main loop
    do {
        // Receive message from oss
       struct message msg;
    while (1) {
        // Receive message from oss
        if (msgrcv(msqid, &msg, sizeof(struct message), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        // Process received message
        printf("Received message from oss: %ld\n", msg.mtype);
        // Process other fields of the message as needed
    }

        // Check clock and determine if it's time to terminate
      int shouldTerminate(struct timespec *terminationTime) {
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    // Compare current time with termination time
    if (currentTime.tv_sec > terminationTime->tv_sec ||
        (currentTime.tv_sec == terminationTime->tv_sec && currentTime.tv_nsec >= terminationTime->tv_nsec)) {
        return 1; // It's time to terminate
    } else {
        return 0; // It's not time to terminate yet
    }
}

        // Send message to oss
      struct message msg;
    msg.mtype = 1; // Message type for messages sent to oss
    // Set other fields of the message as needed

    while (1) {
        // Send message to oss
        if (msgsnd(msqid, &msg, sizeof(struct message), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

    } while (!done);

    // Detach from shared memory and exit
      
}

int main(int argc, char *argv[]) {
  struct timespec terminationTime;
    terminationTime.tv_sec = TERMINATION_SECONDS;
    terminationTime.tv_nsec = TERMINATION_NANOSECONDS;

    // Main loop to check the clock and determine if it's time to terminate
    while (1) {
        // Check if it's time to terminate
        if (shouldTerminate(&terminationTime)) {
            printf("Termination time reached. Exiting...\n");
            break;
        }

        // Other operations of the worker process

        // Sleep for a short interval before checking the clock again
        usleep(100000); // Sleep for 100 milliseconds
    }

    // Parse command line arguments
   int seconds = 5;
    int nanoseconds = 0;

    // Parse command line options
    if (argc >= 3) {
        seconds = atoi(argv[1]);
        nanoseconds = atoi(argv[2]);
    } else if (argc == 2) {
        printf("Error: Nanoseconds argument missing\n");
        exit(EXIT_FAILURE);
    }

    // Print parsed command-line options
    printf("Seconds: %d\n", seconds);
    printf("Nanoseconds: %d\n", nanoseconds);

    // Initialize shared memory and message queue
   int msqid;
    key_t msg_key = MSG_KEY;
int shmid;
    key_t shm_key = SHM_KEY;
    void *shmaddr;
if ((shmid = shmget(shm_key, sizeof(struct PCB) * 20, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment
    if ((shmaddr = shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);

    // Get the message queue

    if ((msqid = msgget(msg_key, 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Register termination signal handler
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    // Output initial information
printf("Worker process started.\n");
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    // Start worker process
    startWorker(seconds, nanoseconds);

    return 0;
}
