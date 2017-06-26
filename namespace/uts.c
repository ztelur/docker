#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

char* const child_args[] = {
  "/bin/bash",
  NULL
};

int child_main(void* args) {
  printf("在子进程中\n");
  sethostname("NewNamespace", 12);
  execv(child_args[0], child_args);
  return 1;
}

int main() {
  printf("%s\n", "程序开始");
  int child_pid = clone(child_main, child_stack + STACK_SIZE, SIGCHLD | CLONE_NEWUTS, NULL);
  waitpid(child_pid, NULL, 0);
  printf("%s\n", "已退出");
  return 0;
}
