#include "kernel/param.h"
#include "kernel/types.h"
#include "user/uproc.h"
#include "user/user.h"

struct uproc uproc[NPROC];
int nprocs;

void myPrint(char* name){
   printf(" ");
   printf(" ");
   printf("%s \n",name);
}

// helper function to output the process tree rooted at pid
// calls itself recursively on any children of pid
void mktree(int indent, int pid)
{

  int i = 0;
  for(; i < nprocs; i++){
    if(uproc[i].pid == pid){
       break;
    }
  }

   myPrint(uproc[i].name);

  if(pid<=nprocs){
     pid++;
     indent++;
     mktree(0,pid);
  }
  return;
}

int
main(int argc, char **argv)
{
  int pid = 1;
  if (argc == 2)
    pid = atoi(argv[1]);
  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  // You can remove the following print statement
  printf("%d processes\n", nprocs);

  mktree(0, pid);

  exit(0);
}
