#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#define MAX_CHILDREN 20
#define SHM_KEY 1234
#define MSG_KEY 5678

struct PCB {
    int occupied;
    pid_t pid;
    int startSeconds;
    int startNano;
};

struct PCB processTable[MAX_CHILDREN];

int shmid;
int msqid;
int totalChildren = 0;
int remainingChildren = 0;

void incrementClock() {
    // Increment clock by 250ms divided by the number of current children
}

void cleanup() {
    // Cleanup shared memory and message queue
    // Terminate all child processes
}

void timeoutHandler(int signum) {
    // Handle timeout signal
    // Cleanup and exit
    exit(EXIT_SUCCESS);
}

void sigintHandler(int signum) {
   if (signum == SIGINT) {
        printf("Received SIGINT signal. Cleaning up...\n");
    // Handle Ctrl+C signal
    // Cleanup and exit
    exit(EXIT_SUCCESS);
}

void launchWorker(int intervalSeconds, int intervalNano) {
    // Fork and exec worker process
    // Update process table
}

void updateProcessTable(int pid) {
    // Update process table when a child process terminates
}

void sendMsgToChild(pid_t childPid) {
    // Construct message
    struct msgbuf {
        long mtype;
        // Your message structure here
    } message;

    message.mtype = 1; // Message type
    // Fill in your message structure

    // Send message to child process
    if (msgsnd(msqid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to child process with PID %d.\n", childPid);
}

void receiveMsgFromChild() {
    // Define message buffer
    struct msgbuf {
        long mtype;
        // Your message structure here
    } message;

    // Receive message from any child process
    if (msgrcv(msqid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
  printf("Message received from child process.\n");
}

void checkChildTermination() {
    int status;
    pid_t childPid;

    // Check if any child process has terminated
    while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Update process table or perform other actions based on child termination
        printf("Child process with PID %d has terminated.\n", childPid);
        updateProcessTable(childPid);
        remainingChildren--;
    }
}

void outputProcessTable() {
    // Implement logic to output the process table
    printf("Process Table:\n");
    printf("Entry  Occupied  PID  StartS  StartN\n");
    for (int i = 0; i < MAX_CHILDREN; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i, processTable[i].occupied, processTable[i].pid, processTable[i].startSeconds, processTable[i].startNano);
    }
    printf("\n");
}
int main(int argc, char *argv[]) {
    int opt;
    int proc_count = 0;
    int simul_count = 0;
    int time_limit = 0;
    int launch_interval = 0;
    char *logfile = NULL;
  

    // Parse command line options
  int opt;
    while ((opt = getopt(argc, argv, "hn:s:t:i:f:")) != -1) {
        switch (opt) {
            case 'h':
                // Display help message
                printf("Usage: %s [-n proc] [-s simul] [-t timelimitForChildren] [-i intervalInMsToLaunchChildren] [-f logfile]\n", argv[0]);
                exit(EXIT_SUCCESS);
            case 'n':
                // Set number of processes to launch
                proc_count = atoi(optarg);
                break;
            case 's':
                // Set number of simultaneous processes
                simul_count = atoi(optarg);
                break;
            case 't':
                // Set time limit for children
                time_limit = atoi(optarg);
                break;
            case 'i':
                // Set interval to launch children
                launch_interval = atoi(optarg);
                break;
            case 'f':
                // Set logfile name
                logfile = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n proc] [-s simul] [-t timelimitForChildren] [-i intervalInMsToLaunchChildren] [-f logfile]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Print parsed command-line options
    printf("Number of child processes: %d\n", proc);
    printf("Number of child processes to launch initially: %d\n", simul);
    printf("Time limit for child processes: %d\n", timelimitForChildren);
    printf("Interval in milliseconds to launch children: %d\n", intervalInMsToLaunchChildren);
    printf("Log file name: %s\n", logfile ? logfile : "None");

  int shmid;
    key_t shm_key = SHM_KEY;

    // Create shared memory segment
    if ((shmid = shmget(shm_key, sizeof(struct PCB) * 20, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Initialize message queue
    int msqid;
    key_t msg_key = MSG_KEY;

    // Create message queue
    if ((msqid = msgget(msg_key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return 0;
}
    

    // Main loop
    while (remainingChildren > 0) {
        incrementClock();
        // Check if it's time to launch a new child
      struct timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);
        int currentSeconds = currentTime.tv_sec;
        int currentNano = currentTime.tv_nsec;

        if (currentSeconds > nextLaunchSeconds || (currentSeconds == nextLaunchSeconds && currentNano >= nextLaunchNano)) {
            // It's time to launch a new child process
            if (totalChildren < MAX_CHILDREN) {
                launchWorker(intervalSeconds, intervalNano);
                totalChildren++;
                remainingChildren++;
                printf("Launched a new child process.\n");
            } else {
                printf("Maximum number of children reached.\n");
            }

            // Calculate next launch time
            nextLaunchSeconds = currentSeconds + intervalSeconds;
            nextLaunchNano = currentNano + intervalNano;
            if (nextLaunchNano >= 1000000000) {
                nextLaunchSeconds++;
                nextLaunchNano -= 1000000000;
            }
        }

        // Send message to child process
      pid_t childPid = /* get child process PID from process table */;
sendMsgToChild(childPid);
        // Receive message from child process
      receiveMsgFromChild();
        // Check if child process has terminated
      checkChildTermination();
        // Launch new child if conditions are met
      if (shouldLaunchNewChild()) {
        // Launch a new child process if conditions are met
        launchNewChild();
        totalChildren++;
        remainingChildren++;
        printf("Launched a new child process.\n");
    } else {
        printf("Maximum number of children reached.\n");
    }

        // Output process table every half second
      outputProcessTable();
    }

    // Cleanup and exit
    cleanup();
    return 0;
}

