struct uproc{
  //Christian Gomez Task 4 -> pstat.h file
   int pid;
   enum procstate state;
   uint64 size;
   int ppid;
   char name[16];
   int cputime;
   int arrtime;
   int priority;
};

struct rusage{
   int cputime;
};
