#include "kernel/param.h"
#include "kernel/types.h"
#include "user/uproc.h"
#include "user/user.h"

struct uproc uproc[NPROC];
int nprocs;


void myPrint(char* name, int indent, int pid){
     for(int x = 0; x < indent; x++){
         printf(" ");
      }
     printf("%s [%d] \n",name,pid);
}


// helper function to output the process tree rooted at pid
// calls itself recursively on any children of pid
void mktree(int indent, int pid)
{

  int i = 0;
  int j = 0;
  for(; i < nprocs; i++){
    if(uproc[i].pid == pid){
       break;
    }
  }

   myPrint(uproc[i].name,indent,uproc[i].pid);

   for(;j < nprocs; j++){
     if(uproc[i].pid == uproc[j].ppid){
       mktree(indent+1,uproc[j].pid);
     }
   }

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
