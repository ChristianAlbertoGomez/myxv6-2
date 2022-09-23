/*
 * Skeleton code for ps.c
 */
#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct uproc uproc[NPROC];
  int nprocs;

  /********************************
   * Add any additional variables or data structures you will need
   ********************************/

  static char *states[] = {
   [UNUSED]    "unused",
   [SLEEPING]  "sleep ",
   [RUNNABLE]  "runble",
   [RUNNING]   "run   ",
   [ZOMBIE]    "zombie"
   };
 // struct proc *p;
  char *state;

  nprocs = getprocs(uproc);

  if (nprocs < 0)
    exit(-1);

  // You can remove the following print statement
  printf("%d processes\n", nprocs);

  for(int i = 0; i < nprocs; i++){

    state = states[uproc[i].state];
    printf("pid:%d state:%s size:%d ppid:%d name:%s cputime:%d\n",uproc[i].pid,state,
            uproc[i].size,uproc[i].ppid,uproc[i].name,uproc[i].cputime);

    //printf("state: %s \n",state);
    //printf("size: %d \n",uproc[i].size);
    //printf("ppid: %d \n",uproc[i].ppid);
  }

  /*********************************
   * Add your code here to output information returned by getprocs()
   * Hint: see procdump() code in kernel/console.c, except that here
   * you will be outputting the first nprocs elements of the uproc array
   * and all will have active states.
   *********************************/


  exit(0);

}
