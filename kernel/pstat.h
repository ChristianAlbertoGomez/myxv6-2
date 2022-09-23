struct uproc{

   int pid;
   enum procstate state;
   uint64 size;
   int ppid;
   char name[16];
   int cputime;
   int arrtime;
};

struct rusage{
   int cputime;
};
