//Code from christian gomez

#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int time_to_sleep;

    if(argc <= 1){
      fprintf(2, "Sleeping Time!. \n");
      exit(1);
    }
    time_to_sleep = atoi(argv[1]);
    sleep(time_to_sleep);
    exit(0);

}
