//this program asks the user if s/he wants to continue the process if user replies with 'y' then the process returns 1(true) to the calling function else it returns 0(false).

#include<stdio.h>

int askforcontinuation()
{

      int flag_2 = 0;                                                                                //flag variable
      char prs_cntu;                                                                                 //variable to store user reply

      do
        {
          flag_2 = 0;

           printf("\n\t\tDo you want to continue this process");                                     //ask the user
           printf("\n\t\tIf yes then press 'y' or 'Y' else press 'n' or 'N'\n\t\t");

           fflush(stdin);                                                                            //flushes the input stream
           scanf("%c",&prs_cntu);                                                                    //accepts the response

            if(prs_cntu != 'N' && prs_cntu != 'n' && prs_cntu != 'Y' && prs_cntu != 'y')             //checks the user reply
             flag_2 = 1;                                                                             //if response is not according to specified instructions then sets
            else if(prs_cntu == 'N' || prs_cntu == 'n')                                              //the flag to 1
            return 1;                                                                                //if response is negative returns 1

       }while(flag_2);
       return 0;                                                                                      //if response is positive returns 0
}
