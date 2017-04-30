#include "types.h"
#include "user.h"
#include "ps.h"


    
int
main(int argc, char* argv[])
{
  int max;
  int i;
  int entries;

  //if(strcmp("MAX", argv[1]) > 0){ //arguments can not be larger than Max size
      //printf(2, "Invalid Argument Size\n");
      //exit();
  //}
  if(argc != 1){ //ps command can not take arguments from user
    printf(2, "Invalid Argument\n");
    exit();
  }
  max = MAX;
  entries = getprocs(max, table);

  if(entries <= 0){ //Not possible to return zero process so put less than
    printf(2, "getprocs_failed\n");
    exit();
  }

  printf(1, "\nPID   ");
  printf(1, "UID   ");
  printf(1, "GID   ");
  printf(1, "PRIORITY   ");
  printf(1, "PPID   ");
  printf(1, "STATE   ");
  printf(1, "SIZE   ");
  printf(1, "NAME   ");

  for(i = 0; i < entries; i++){
    printf(1, "\n");
    printf(1, " %d    ", table[i].pid);
    printf(1, " %d    ", table[i].uid);
    printf(1, " %d      ", table[i].gid);
    printf(1, " %d       ", table[i].priority);
    printf(1, " %d    ", table[i].ppid);
    printf(1, " %s  ", table[i].state);
    printf(1, " %d  ", table[i].size);
    printf(1, " %s    ", table[i].name);
  }
  printf(1, "\n");
  exit();
}
