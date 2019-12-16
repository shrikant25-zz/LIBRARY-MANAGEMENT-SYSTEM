#include<stdio.h>

int askforcontinuation()
{

      int flag_2 = 0;
      char prs_cntu;

      do
        {
          flag_2 = 0;

           printf("\n\t\tDo you want to continue this process");
           printf("\n\t\tIf yes then press 'y' or 'Y' else press 'n' or 'N'\n\t\t");

           fflush(stdin);
           scanf("%c",&prs_cntu);

            if(prs_cntu != 'N' && prs_cntu != 'n' && prs_cntu != 'Y' && prs_cntu != 'y')
             flag_2 = 1;
            else if(prs_cntu == 'N' || prs_cntu == 'n')
            return 1;

       }while(flag_2);
       return 0;
}
