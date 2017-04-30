#include "types.h"
#include "user.h"
#include "date.h" 



int
main(int argc, char* argv[])
{
   struct rtcdate d1, d2;
   int rc = 0;
   int min = 0;
   int sec = 0;

   if(strcmp("CHtime", argv[1]) == 0) {
       printf(2, "Invalid Argument for CHtime\n");
       exit();
   }
   if(argc == 1){
       printf(2, "Must provide arguments\n");
       exit();
   }
   if(date(&d1)) {
       printf(2, "date_failed\n");
       exit();
   }
   rc = fork();

   if(rc == -1)
       printf(2, "fork_failed");
   if(rc)
       wait();
   else { 
       exec(argv[1], argv + 1);
       printf(2, "exec_failed\n"); //exec should not return back to here
       exit();
   }

   if(date(&d2)) {
       printf(2, "date_failed\n");
       exit();
   }

   if(d1.hour > d2.hour || d1.minute > d2.minute || d1.second > d2.second)
       --min; //decrement min in instance of rollover of time

   if(d1.second <= d2.second) 
       sec = d2.second - d1.second;
   else
       sec = (60 - d1.second) + d2.second;

   if(d1.minute <= d2.minute)
       min += d2.minute - d1.minute;
   else 
       min += ((60 - d1.minute) + d2.minute); //The += allows decrement to affect minutes

   printf(0, "%s ran in %d minutes and %d seconds\n", argv[1], min, sec);

   exit();
}
