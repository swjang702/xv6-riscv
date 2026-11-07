
#include "kernel/types.h"
#include "user/user.h"

// Lab2 Part1: Test scheduling statistics
int
main(void)
{
  printf("=== Scheduling Statistics Test ===\n");

  sched_statistics();

  printf("=== Test Completed ===\n");

  exit(0);
}
