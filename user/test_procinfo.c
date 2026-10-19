#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"     // for proc.h
#include "kernel/spinlock.h"  // for proc.h
#include "kernel/riscv.h"     // for proc.h
#include "kernel/proc.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int n = 0, pid = 0;
  if (argc >= 2) n = atoi(argv[1]);

  printf("Say hello to kernel %d\n", n);
  hello(n);

  pid = getpid();

  // procinfo
  struct pinfo in;
  procinfo(&in);
  printf("For the current process: pid=%d ppid=%d syscall_count=%d page_usage=%d\n",
    pid, in.ppid, in.syscall_count, in.page_usage / PGSIZE);

  int memsize_to_add=16384;
  sbrk(memsize_to_add);
  printf("Adding memsize %d byte\n", memsize_to_add);

  procinfo(&in);
  printf("For the current process: pid=%d ppid=%d syscall_count=%d page_usage=%d\n",
    pid, in.ppid, in.syscall_count, in.page_usage / PGSIZE);

  procinfo(&in);
  printf("For the current process: pid=%d ppid=%d syscall_count=%d page_usage=%d\n",
    pid, in.ppid, in.syscall_count, in.page_usage / PGSIZE);

  procinfo(&in);
  printf("For the current process: pid=%d ppid=%d syscall_count=%d page_usage=%d\n",
    pid, in.ppid, in.syscall_count, in.page_usage / PGSIZE);

  exit(0);
}
