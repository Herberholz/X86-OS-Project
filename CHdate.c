#include "types.h"
#include "user.h"
#include "date.h"



int
main(int argc, char* argv[])
{
  struct rtcdate r;

  if(date(&r)){
    printf(2, "date_failed\n"); 
    exit();
  }

  printf(0, "Date: %d:%d:%d\n", r.year, r.month, r.day);
  printf(0, "Time: %d:%d:%d\n", r.hour, r.minute, r.second);
  exit();
}
