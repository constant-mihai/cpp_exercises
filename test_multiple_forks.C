#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
//#include <PrPegCount.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {

pid_t pids[10];
int i;
int n = 10;

/* Start children. */
for (i = 0; i < n; ++i) {
	printf("Process number [%d] with pid [%d]\n", i, getpid());
  if ((pids[i] = fork()) < 0) {
    perror("fork");
    abort();
  } else if (pids[i] == 0) {
//    while(1) {}
	exit(0);
  }
}

/* Wait for children to exit. */
int status;
pid_t pid;
while (n > 0) {
  pid = wait(&status);
  printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
  --n;  // TODO(pts): Remove pid from the pids array.
}
}
