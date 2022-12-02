#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char* path){
  char *p;
  static char buf[DIRSIZ+1];

  for(p=path+strlen(path); p>=path && *p != '/'; p--)
   ;
  p++;

  if(strlen(p)>=DIRSIZ)
    return p;

  memmove(buf,p,strlen(p));
  memset(buf+strlen(p),' ',DIRSIZ-strlen(p));
  return buf;
}


int main(int argc, char *argv[]){

   struct stat st;
   int fd;

   if((fd=open(argv[1],0))<0){
      fprintf(2,"fstat: This cannot be open %s\n",argv[1]);
      exit(0);
   }
   if(fstat(fd,&st)<0){
     close(fd);
   }

   printf("File name:%s \n",fmtname(argv[1]));

   if(st.type==1)
     printf("File type: Directory\n");
   if(st.type==2)
     printf("File type: Regular File\n");

   printf("Inode number:%d\tSize:%l bytes\tLinks:%d\n",st.ino,st.size,st.nlink);

   close(fd);
   exit(0);
}
