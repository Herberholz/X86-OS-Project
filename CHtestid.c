#include "types.h"
#include "user.h"


int
testuidgid(void)
{
  int uid, gid, ppid;

  uid = getuid();
  printf(1, "Current UID is: %d\n", uid);
  printf(1, "Setting UID to 100\n\n");

  if(setuid(100)) {
    printf(2, "setuid_failed\n");
    exit();
  }

  uid = getuid();
  printf(1, "Resulting UID is: %d\n\n", uid);

  gid = getgid();
  printf(1, "Current GID is: %d\n", gid);
  printf(1, "Setting GID to 200\n\n");

  if(setgid(200)) {
    printf(2, "setgid_failed");
    exit();
  }

  gid = getgid();
  printf(1, "Resulting GID is: %d\n\n", gid);

  ppid = getppid();
  printf(1, "My parent process is: %d\n", ppid);
  printf(1, "Complete!\n");

  return 0;
}


int
main(int argc, char *argv[])
{
  if(argc != 1){
      printf(2, "This command can't use arguments\n\n");
      exit();
  }
  testuidgid();
  exit();
}
