#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROC 10
#define NUM_TICK 5
#define NUM_ITER 10

int main(int argc, char *argv[])
{
  int ret, proc_pid[MAX_PROC];
  int sleep_ticks[NUM_TICK] = {20, 40, 60, 80, 100};

  // The first test: four processes with 8, 4, 2, 1 tickets for each.
  printf("The first test: four processes with 8, 4, 2, 1 tickets for each.\n");

  int n_tickets1[4] = {8, 4, 2, 1};

  for (int k = 0; k < NUM_ITER; k++) {
    printf("ITERATION: %d\n", k);
    for (int j = 0; j < NUM_TICK; j++) {
      printf("TICKS: %d\n", sleep_ticks[j]);
      for (int i = 0; i < 4; i++) {
        ret = fork();
        if (ret == 0) { // child process
          sched_tickets(n_tickets1[i]);
          while(1);
        }
        else { // parent
          proc_pid[i] = ret;
          continue;
        }
      }
      sleep(sleep_ticks[j]);
      sched_statistics();
      for (int i = 0; i < 4; i++) {
        kill(proc_pid[i]);
        wait(0);
      }
    }
  }

  // The second test: four processes with all 1 ticket.
  printf("The second test: four processes with all 1 ticket.\n");

  int n_tickets2[4] = {1, 1, 1, 1};

  for (int k = 0; k < NUM_ITER; k++) {
    printf("ITERATION: %d\n", k);
    for (int j = 0; j < NUM_TICK; j++) {
      printf("TICKS: %d\n", sleep_ticks[j]);
      for (int i = 0; i < 4; i++) {
        ret = fork();
        if (ret == 0) { // child process
          sched_tickets(n_tickets2[i]);
          while(1);
        }
        else { // parent
          proc_pid[i] = ret;
          continue;
        }
      }
      sleep(sleep_ticks[j]);
      sched_statistics();
      for (int i = 0; i < 4; i++) {
        kill(proc_pid[i]);
        wait(0);
      }
    }
  }

  exit(0);
}
