
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "declared.h"       //header file for declared structures and other defined values
#include <stdio.h>
#define _WIN32_WINNT 0x0500 //constant for console resizing (redefinition as per mentioned in header file)
#include <windows.h>        //defines number of Windows specific functions that can be used in to improve layout of program

//*******************************************************************************************************************************

void read_books_file(struct book **);
void read_members_file(struct member **);
void read_issue_file(struct issue **);
void add_books_to_record(struct book **);
void close_application(struct book *,struct member *,struct issue *issue_info);
void delete_books_record(struct book **);
void search_book(struct book *);
void displaybookinfo(struct book *);
void edit_books_record(struct book **);
void view_books_list(struct book *);
void displaybooks(struct book *);
void displayoptions();
void mem(struct member **);
void add_member(struct member **);
void remove_member(struct member **);
void view_mem(struct member *);
void search_mem(struct member *);
void memberinfo(struct member *);
void timedisplay();
void issue(struct book **,struct member *,struct issue **);
void issue_book(struct book **,struct member *,struct issue **);
void search_issueed(struct issue *);
void view_issued_list(struct issue *);
void remove_issued_book(struct book **,struct issue **);
void issueinfo(struct issue *);

//*******************************************************************************************************************************

FILE * read_books;                                                       //file pointer to open books related file
FILE * issueb;                                                           //file pointer to open issued info file
FILE * members;                                                          //file pointer to open member file

//*******************************************************************************************************************************

void read_books_file(struct book **book_info)                           //function reads the info about books from the file
{

  struct book *new = NULL, *temp = NULL;

  if( (read_books = fopen("books.txt","r")) == NULL )                   //if file is present then it it opened otherwise the function terminates
    return;
  else
  {

      while(!feof(read_books))
      {

        new = (struct book *) malloc (sizeof(struct book));           //a new pointer is created (read declared.h file to know more about 'struct book' data type)
        new->next = NULL;

        fflush(stdin);
        fscanf(read_books,"%s %s %s %s %d %d %d",new->Category,new->Book_ID,new->Book_Name,new->Author_Name,&new->Quantity,&new->Price,&new->Rack_No); //scans the data from file and stores in new memory

        if(!(*book_info))
          temp = (*book_info) = new;                          //normal linked list operaions using double pointer
        else
        {

          temp->next = new;
          temp = new;

        }

      }

   }
      temp = NULL;
      new = NULL;                                                      //frees the memory
      free(temp);
      free(new);
      fclose(read_books);

}

//*******************************************************************************************************************************

void read_members_file(struct member **member_info)                   //this function reads the data about members from member file
{

    struct member *new = NULL, *temp = NULL;

  if( (members= fopen("members.txt","r")) )
  {

      while(!feof(members))
      {

        new = (struct member *) malloc (sizeof(struct member));
        new->next = NULL;

        fflush(stdin);
        fscanf(members,"%s %s %ld",new->memb_id,new->memb_name,&new->phone);

        if(!(*member_info))
          temp = (*member_info) = new;
        else
        {

          temp->next = new;
          temp = new;

        }

      }

  }
  else
    return;

  temp = NULL;
  new = NULL;
  free(temp);
  free(new);
  fclose(members);


}

//*******************************************************************************************************************************

void read_issue_file(struct issue **issue_info)            //this function reads the about members from members file
{

    struct issue *new = NULL, *temp = NULL;

  if( (issueb = fopen("issue.txt","r")) )
  {

      while(!feof(issueb))
      {

        new = (struct issue *) malloc (sizeof(struct issue));
        new->next = NULL;

        fflush(stdin);
        fscanf(issueb,"%s %s",new->Book_Id,new->memb_id);

        if(!(*issue_info))
          temp = (*issue_info) = new;
        else
        {

          temp->next = new;
          temp = new;

        }

      }

  }
  else
    return;

  temp = NULL;
  new = NULL;
  free(temp);
  free(new);
  fclose(issueb);

}

//*******************************************************************************************************************************

void add_books_to_record(struct book **book_info)                                                                 //this function is used to add new book to record
{

 do
  {
      system("cls");
     struct book *new = NULL, *temp = NULL, *temp1 = (*book_info);
     char chk_wht_spc[2] = {' ','\0'};                                                                            //this varibale is used as comparison to check white space

     new = (struct book *) malloc (sizeof(struct book));
     new->next = NULL;
        int flag = 0;
         do
         {

          do
           {
            flag = 0;
            printf("\n\t\t\t\t\t\tEnter the book ID\n\t\t\t\t\t\t");                                             //accepts the book id
            acceptstring(new->Book_ID);

            while(temp1)
             {
                if(!(strcmp(new->Book_ID,temp1->Book_ID)))                                                       //compares the book with the books in revord
                 {                                                                                               //if a match is found it means the book is already present the record
                   flag = 1;                                                                                     //then the flag is set to 1 and appropriate message is displayed
                   printf("\n\t\t\t\t\t\tYou have entered already used ID, please choose another ID\n");
                   break;
                 }
                else
                temp1 = temp1->next;
             }
             if(!(strcmp(new->Book_ID,"\0")) || (new->Book_ID[0] == chk_wht_spc[0]))                             //checks if the user input is proper, checking for NULL strings
             printf("\n\t\t\t\t\t\tBook ID can't be NULL");

            }while(!(strcmp(new->Book_ID,"\0")) || (new->Book_ID[0] == chk_wht_spc[0]));                         //if the input is not proper the loop continues

        }while(flag);                                                                                            //outer loop continues if the flag is set to 1

      //-------------------------------------------------------------------------

         do
          {                                                                                                      //accepts the book name
           printf("\n\t\t\t\t\t\tEnter the book Name\n\t\t\t\t\t\t");
           acceptstring(new->Book_Name);

           if(!(strcmp(new->Book_Name,"\0")) || (new->Book_Name[0] == chk_wht_spc[0]))                           //user input is checked
            printf("\n\t\t\t\t\t\tBook Name can't be NULL");
          }while((!strcmp(new->Book_Name,"\0")) || (new->Book_Name[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         do
          {
           printf("\n\t\t\t\t\t\tEnter the book Author Name\n\t\t\t\t\t\t");
           acceptstring(new->Author_Name);                                                                       //accepts the author name

           if(!(strcmp(new->Author_Name,"\0")) || (new->Author_Name[0] == chk_wht_spc[0]))                       //user input checked
            printf("\n\t\t\t\t\t\tAuthor Name can't be NULL");
           }while(!(strcmp(new->Author_Name,"\0")) || (new->Author_Name[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         do
          {
           printf("\n\t\t\t\t\t\tEnter the Category of book\n\t\t\t\t\t\t");                                     //accepts the category of book
           acceptstring(new->Category);

           if(!(strcmp(new->Category,"\0")) || (new->Category[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tCategory can't be NULL");                                                      //user input is checked
          }while(!(strcmp(new->Category,"\0")) || (new->Category[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         int chk = 0;

         do
          {
           fflush(stdin);

           printf("\n\t\t\t\t\t\tEnter the book Quantity\n\t\t\t\t\t\t");                                       //accepts the book quantitiy
           chk = scanf("%d",&new->Quantity);                                                                    //if the user enters a character instead of an integer then the scanf fucniton returns 0 else 1
                                                                                                                //if scanf returns 0 then the chk flag is set to 0
           if(new->Quantity < 1)                                                                                //checks the user input
           printf("\n\t\t\t\t\t\tQuantity can't be less than zero");
          }while(new->Quantity < 1 || chk == 0);                                                                //the loop continues if the quantity is less than 1 or if the chk flag is 0

         chk = 0;

      //-------------------------------------------------------------------------

         do
         {
          fflush(stdin);                                                                                       //accepts the book price
          printf("\n\t\t\t\t\t\tEnter the book Price\n\t\t\t\t\t\t");
          chk = scanf("%d",&new->Price);

          if(new->Price < 1)
           printf("\n\t\t\t\t\t\tPrice can't be less than zero");
         }while(new->Price < 1 || chk == 0 );

      //-------------------------------------------------------------------------

         chk = 0;

         do
         {
          fflush(stdin);                                                                                       //accepts the rack number
          printf("\n\t\t\t\t\t\tEnter the Rack_no of book\n\t\t\t\t\t\t");
          chk = scanf("%d",&new->Rack_No);

          if(new->Rack_No < 1)
           printf("\n\t\t\t\t\t\tRack Number can't be less than zero");
         }while(new->Rack_No < 1 || chk == 0);

      //-------------------------------------------------------------------------

         if(!(*book_info))
           temp = (*book_info) = new;
         else
         {
          temp = (*book_info);                                                                                 //nomral fucntioning of linked list using double pointer
          while(temp->next != NULL)
          temp = temp->next;
          temp->next = new;
          temp = new;

         }

         printf("\n\t\t\t\t\t\tBook added successfully");
         temp = NULL;
         temp1 = NULL;
         new = NULL;
         free(temp);                                                                                           //frees the memory
         free(temp1);
         free(new);

      //-------------------------------------------------------------------------

          int flag_c = 0;
      if((flag_c = askforcontinuation()))                                        //gives call to continuation funciton, the fucntion asks the user if the process is to be continued or terminated
           return;

  }while(1);
}

//*******************************************************************************************************************************

void close_application(struct book *book_info,struct member *member_info,struct issue *issue_info)          //this funciton writes the data to external files before closing the program
{

    struct book * temp = NULL;
    if(book_info)                                                                                           //if the pointer is present the concerned file is opened
    {                                                                                                       //writes the data of books to the concerned file

       read_books = fopen("books.txt","w");

         book_info = mergesort(book_info,'N');                                                              //sort function is called to sort the data before it is stored in file
         temp = book_info;

         while(temp)
         {
           fflush(stdout);
           fprintf(read_books,"%s %s %s %s %d %d %d",temp->Category,temp->Book_ID,temp->Book_Name,temp->Author_Name,temp->Quantity,temp->Price,temp->Rack_No);    //data is written to the file
           temp = temp->next;

         }

    }
    else
     remove("books.txt");                                                                                  //if the pointer is empty, then it means there is no data present so the concerned file is deleted

    temp = NULL;
    free(temp);                                                                                            //frees the memory
    fclose(read_books);                                                                                    //closes the file

//-------------------------------------------------------------------------

    struct member * temp1 = NULL;                                                                          //writes data of members to the member file
    if(member_info)
     {

       members = fopen("members.txt","w");

         temp1 = member_info;

         while(temp1)
         {
           fflush(stdout);
           fprintf(members,"%s %s %ld",temp1->memb_id,temp1->memb_name,temp1->phone);
           temp1 = temp1->next;

         }

     }
    else
     remove("members.txt");

   temp1 = NULL;
   free(temp1);
   fclose(members);

//-------------------------------------------------------------------------

   struct issue * temp2 = NULL;                                                                         //writes the data of issued books to the concernd file
   if(issue_info)
    {

      issueb = fopen("issue.txt","w");

         temp2 = issue_info;

         while(temp2)
         {
           fflush(stdout);
           fprintf(issueb,"%s %s",temp2->Book_Id,temp2->memb_id);
           temp2 = temp2->next;
         }

    }
   else
    remove("issue.txt");

   temp2 = NULL;
   free(temp2);
   fclose(issueb);

}

//*******************************************************************************************************************************

void delete_books_record(struct book **book_info)                                                      //this is funciton is used to delete books record
{

 do
  {
    system("cls");                                                                                     //function to clear the screen present in stdlib.h
    char book_id[max_size];
    struct book **temp;
    struct book *free_m;

       printf("\n\t\t\t\t\t\tChoose Book Id\n\t\t\t\t\t\t");                                           //accepts the book ID
       acceptstring(book_id);

              temp = book_info;

       while(*temp)
        {
         if( !(strcmp (((*temp)->Book_ID),book_id)) )                                                  //checks the user entered string with books record
         {
              free_m = (*temp);                                                                        //if books ID is found then the deletion takes place
              *temp = (*temp)->next;
              free(free_m);                                                                            //normal deletion of linked list using double pointer
              free_m = NULL;
              printf("\n\t\t\t\t\t\tBook deleted successfully\n");
              break;
         }
         else
            temp = &(*temp)->next;
            if(temp == NULL)
            printf("\n\t\t\t\t\t\tId not found\n");
      }
      temp = NULL;
      free(temp);


          int flag_c = 0;
      if((flag_c = askforcontinuation()))                                                               //give call to continuation function
           return;

  }while(1);

}

//*******************************************************************************************************************************

void search_book(struct book *book_info)                                                               //funciton to search a book in record
{
    do
     {
      system("cls");
      int flag = 0;
      char choice_string[max_size] = {"\0"};
      int choice_int = 0;
      struct book *temp = book_info;
      int option = 0;

      printf("\n\n****************************************************************************************************************************\n");
      printf("\n\t\t\t\t\t\tChoose the option to search the book");
      printf("\n\t\t\t\t\t\tPress '1' and hit 'Enter' for Book Category");
      printf("\n\t\t\t\t\t\tPress '2' and hit 'Enter' for Book_ID");                                    //dislays the choices
      printf("\n\t\t\t\t\t\tPress '3' and hit 'Enter' for Book_Name");
      printf("\n\t\t\t\t\t\tPress '4' and hit 'Enter' for Author_Name");
      printf("\n\n****************************************************************************************************************************\n");

      printf("\n\t\t\t\t\t\t");
      fflush(stdin);
      scanf("%d",&option);
    system("cls");
      switch(option)
       {
         case 1 : printf("\n\t\t\t\t\t\tType the Book Category and hit 'Enter'\n\t\t\t\t\t\t");        //switch case is used to match various conditions
                  acceptstring(choice_string);

                  while(temp)
                  {
                    if(!(strcmp(choice_string,temp->Category)))                                        //matches the user input with the record
                    {
                        flag = 1;
                        displaybookinfo(temp);                                                         //if value is found in record then the flag is set to 1
                        break;                                                                         //the display funcion prints the book info on screen
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tCategory not found\n");                                  //if record is not found then appropriate message is displayed

                  break;

       //-------------------------------------------------------------------------

         case 2 : printf("\n\t\t\t\t\t\tType the Book ID and hit 'Enter'\n\t\t\t\t\t\t");
                  acceptstring(choice_string);
                  while(temp)
                   {
                    if(!(strcmp(choice_string,temp->Book_ID)))
                     {
                       flag = 1;
                       displaybookinfo(temp);
                       break;
                     }
                    else
                     temp = temp->next;
                   }
                    if(!flag)
                    {
                        printf("\n\t\t\t\t\t\t Book_ID not found\n");
                        break;
                    }

                  break;

        //-------------------------------------------------------------------------

         case 3 : printf("\n\t\t\t\t\t\tType the Book Name and hit 'Enter'\n\t\t\t\t\t\t");
                  acceptstring(choice_string);
                  while(temp)
                   {
                     if(!(strcmp(choice_string,temp->Book_Name)))
                      {
                        flag = 1;
                        displaybookinfo(temp);
                        break;
                      }
                    else
                     temp = temp->next;
                   }
                    if(!flag)
                    {
                        printf("\n\t\t\t\t\t\t Book_Name not found\n");
                        break;
                    }

                  break;

        //-------------------------------------------------------------------------

         case 4 : printf("\n\t\t\t\t\t\tType the Author Name and hit 'Enter'\n\t\t\t\t\t\t");
                  acceptstring(choice_string);
                  while(temp)
                  {
                    if(!(strcmp(choice_string,temp->Author_Name)))
                    {
                        flag = 1;
                        displaybookinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                    {
                        printf("\n\t\t\t\t\t\t Author_Name not found\n");
                        break;
                    }

                  break;

         //-------------------------------------------------------------------------

         case 5 : printf("\n\t\t\t\t\t\tType the Rack No and hit 'Enter'\n\t\t\t\t\t\t");
                  fflush(stdin);
                  scanf("%d",&choice_int);
                  while(temp)
                   {
                    if(choice_int == temp->Rack_No)
                    {
                        flag = 1;
                        displaybookinfo(temp);
                        break;
                    }
                    else
                     temp = temp->next;
                   }
                    if(!flag)
                    {
                        printf("\n\t\t\t\t\t\t Rack Number not found\n");
                        break;
                    }
                  break;
        default : printf("\n\t\t\t\t\t\tWrong Option\n");
      };

      //-------------------------------------------------------------------------

      temp = NULL;
      free(temp);

      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

     }while(1);

}

//*******************************************************************************************************************************

void displaybookinfo(struct book *temp)                                                           //this function prints the book info on screen
{
     printf("\n\n****************************************************************************************************************************\n");
     printf("\n\t\t\t\t\t\tBook Found\n");
     printf("\n\t\t\t\t\t\tBook_ID = %s",temp->Book_ID);
     printf("\n\t\t\t\t\t\tBook_Name = %s",temp->Book_Name);
     printf("\n\t\t\t\t\t\tAuthor_Name = %s",temp->Author_Name);
     printf("\n\t\t\t\t\t\tCategory = %s",temp->Category);
     printf("\n\t\t\t\t\t\tQuantity = %d",temp->Quantity);
     printf("\n\t\t\t\t\t\tPrice = %d",temp->Price);
     printf("\n\t\t\t\t\t\tRack_Number = %d",temp->Rack_No);
     printf("\n\n****************************************************************************************************************************\n");
}

//*******************************************************************************************************************************

void edit_books_record(struct book **book_info)                                                  //this function is used to edit the book record
{

   do
   {
    system("cls");
    char bk_id[max_size];
    struct book *temp = (*book_info);
    int option = 0;
    char c_new_data[max_size] = {'\0'};
    int i_new_data = 0;

    printf("\n\t\t\t\t\t\tEnter the ID of Book to be Edited\n\t\t\t\t\t\t");
    acceptstring(bk_id);

    while(temp)
    {
        if(!(strcmp(bk_id,temp->Book_ID)))                                                         //matches the user input
        {
            printf("\n****************************************************************************************************************************\n");
            printf("\n\t\t\t\t\t\tBook ID found");
            printf("\n\t\t\t\t\t\tSelect option to edit from following");
            displayoptions();                                                                      //display function prints the book info on screen
            printf("\n****************************************************************************************************************************\n");
            printf("\n\t\t\t\t\t\t");
            fflush(stdin);
            scanf("%d",&option);                                                                   //accepts the user input
            system("cls");
            switch(option)                                                                         //switch case is use to compare various conditions
            {

                case 1 : printf("\n\t\t\t\t\t\tCurrent Book Category is %s",temp->Category);
                         printf("\n\t\t\t\t\t\tEnter the new Book Catgeory\n\t\t\t\t\t\t");
                         acceptstring(c_new_data);
                         strcpy(temp->Category,c_new_data);                                        //copies newly added data in the record
                         break;

                case 2 : printf("\n\t\t\t\t\t\tCurrent Book Name is %s",temp->Book_Name);
                         printf("\n\t\t\t\t\t\tEnter the new Book Name\n\t\t\t\t\t\t");
                         acceptstring(c_new_data);
                         strcpy(temp->Book_Name,c_new_data);
                         break;

                case 3 : printf("\n\t\t\t\t\t\tCurrent Book Id is %s",temp->Book_ID);
                         printf("\n\t\t\t\t\t\tEnter the new Book ID\n\t\t\t\t\t\t");
                         acceptstring(c_new_data);
                         strcpy(temp->Book_ID,c_new_data);
                         break;

                case 4 : printf("\n\t\t\t\t\t\tCurrent Author Name is %s",temp->Author_Name);
                         printf("\n\t\t\t\t\t\tEnter the new Author Name\n\t\t\t\t\t\t");
                         acceptstring(c_new_data);
                         strcpy(temp->Author_Name,c_new_data);
                         break;

                case 5 : printf("\n\t\t\t\t\t\tCurrent Quantity is %d",temp->Quantity);
                         printf("\n\t\t\t\t\t\tEnter the new Quantity\n\t\t\t\t\t\t");
                         fflush(stdin);
                         scanf("%d",&i_new_data);
                         temp->Quantity = i_new_data;
                         break;

                case 6 : printf("\n\t\t\t\t\t\tCurrent Price is %d",temp->Price);
                         printf("\n\t\t\t\t\t\tEnter the new Price\n\t\t\t\t\t\t");
                         fflush(stdin);
                         scanf("%d",&i_new_data);
                         temp->Price = i_new_data;
                         break;

                case 7 : printf("\n\t\t\t\t\t\tCurrent Rack Number is %d",temp->Rack_No);
                         printf("\n\t\t\t\t\t\tEnter the new Rack Number\n\t\t\t\t\t\t");
                         fflush(stdin);
                         scanf("%d",&i_new_data);
                         temp->Rack_No = i_new_data;
                         break;



            };
            printf("\n\t\t\t\t\t\tBook edited Successfully");
            break;
        }
        else
            temp = temp->next;
    }
     if(temp == NULL)
        printf("\n\t\t\t\t\t\t Id not found");                                                       //if the temp variable reaches the end of list and then it means that the id entered by the user
                                                                                                     //is not present in the record and hence the appropriate message is displayed
     temp = NULL;
     free(temp);

      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

     }while(1);

}

//*******************************************************************************************************************************

void view_books_list(struct book * book_info)                                                        //this function is used to view the book list
{
  do
   {

    int option = 0;
    struct book *temp = NULL;;
    printf("\n****************************************************************************************************************************");
    printf("\n\t\t\t\t\t\tChoose the option to sort the data\n");
    displayoptions();                                                                                //displays the option
    printf("\n\t\t\t\t\t\tPress '8' and hit 'Enter' for default view\n\t\t\t\t\t\t");
    printf("\n****************************************************************************************************************************");

    printf("\n\t\t\t\t\t\t");
    fflush(stdin);
    scanf("%d",&option);
     system("cls");
           switch(option)                                                                            //switch condition matches the user input various conditons
           {
             case 1 : book_info = mergesort(book_info,'C');                                          //the matched condition calls the sort function, along withthe head pointer it also sends the first character
                          temp = book_info;                                                          //of the mathced condition, the sort function takes appropriate comparison call based on the character
                         displaybooks(temp);                                                         //merge sort funciton is included in header file mergesort.h
                         break;

                case 2 : book_info = mergesort(book_info,'N');
                          temp = book_info;
                         displaybooks(temp);
                         break;

                case 3 : book_info = mergesort(book_info,'I');
                          temp = book_info;
                         displaybooks(temp);
                         break;

               case 4 : book_info = mergesort(book_info,'A');
                          temp = book_info;
                         displaybooks(temp);
                         break;

               case 5 : book_info = mergesort(book_info,'Q');
                          temp = book_info;
                         displaybooks(temp);
                         break;


                case 6 : book_info = mergesort(book_info,'P');
                          temp = book_info;
                         displaybooks(temp);
                         break;


                case 7 : book_info = mergesort(book_info,'R');
                          temp = book_info;
                         displaybooks(temp);
                         break;

                case 8 : temp = book_info;
                         displaybooks(temp);
                         break;


                default : printf("\n\t\t\t\t\t\tYou have entered invalid option");
           };

      temp = NULL;
      free(temp);

      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

   }while(1);
}

//*******************************************************************************************************************************

void displaybooks(struct book *temp)                                                       //this is a small function consists of a loop which continously calls the another function to display books info
{
    while(temp)
     {
      displaybookinfo(temp);
      temp = temp->next;
     }
}

//*******************************************************************************************************************************

void displayoptions()                                                                     //function used to display options before switch case statements in various funcitons(book related functions)
{
    printf("\n\t\t\t\t\t\tPress '1' and hit 'Enter' for Book Category");
    printf("\n\t\t\t\t\t\tPress '2' and hit 'Enter' for Book Name");
    printf("\n\t\t\t\t\t\tPress '3' and hit 'Enter' for Book Id");
    printf("\n\t\t\t\t\t\tPress '4' and hit 'Enter' for Author Name");
    printf("\n\t\t\t\t\t\tPress '5' and hit 'Enter' for Quantity");
    printf("\n\t\t\t\t\t\tPress '6' and hit 'Enter' for Price");
    printf("\n\t\t\t\t\t\tPress '7' and hit 'Enter' for Rack Number");
}

//*******************************************************************************************************************************

void mem(struct member **member_info)                                                     //this function is use to manipulate member related information
{
   do
   {
    system("cls");
    int option = 0;

    printf("\n\t\t\t\t\t\tChoose the option from following\n");
    printf("\n\t\t\t\t\t\t Press 1 and hit 'Enter' to add member");                       //displays various options
    printf("\n\t\t\t\t\t\t Press 2 and hit 'Enter' to remove member");
    printf("\n\t\t\t\t\t\t Press 3 and hit 'Enter' to view members");
    printf("\n\t\t\t\t\t\t Press 4 and hit 'Enter' to search member\n\t\t\t\t\t\t");

    fflush(stdin);
    scanf("%d",&option);
    system("cls");
    switch(option)
    {
        case 1 : add_member(member_info);                                                 //this function is used to add new members
                  break;

        case 2 : if((*member_info))                                                       //this function is used to remove the members
                   remove_member(member_info);
                 else
                   printf("\n\t\t\t\t\t\tNo members available\n");
                 break;

        case 3 : if((*member_info))                                                      //this function is used to view members
                   view_mem(*member_info);
                 else
                   printf("\n\t\t\t\t\t\tNo members available\n");
                 break;

        case 4 : if((*member_info))
                   search_mem(*member_info);                                             //this function is used to search members
                 else
                   printf("\n\t\t\t\t\t\tNo members available\n");
                 break;

        default : printf("\n\t\t\t\t\t\tWrong Option\n");
    };


      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

   }while(1);
}

//*******************************************************************************************************************************

void add_member(struct member **member_info)                                                         //this is function is used to add members
{

  struct member *temp =(*member_info);
  struct member *new = NULL;
  int flag = 0;
  char chk_wht_spc[2] = {' ','\0'};

  new = (struct member *)malloc(sizeof(struct member));                                             //new memory is allocated
  new->next = NULL;
   do
    {
     do
      {
       flag = 0;
       printf("\n\t\t\t\t\t\tEnter the ID of member\n\t\t\t\t\t\t");                                //accepts the ID of member
       acceptstring(new->memb_id);

       while(temp)
        {
         if(!(strcmp(new->memb_id,temp->memb_id)))                                                  //matches the user input with the record
          {
            flag = 1;
            printf("\n\t\t\t\t\t\tYou have entered already used ID, please choose another ID\n");   //if record is not foudn then appropriate message is displayed and flag is set to 1
            break;
          }
        else
            temp = temp->next;
        }
       if(!(strcmp(new->memb_id,"\0")) || (new->memb_id[0] == chk_wht_spc[0]))
       printf("\n\t\t\t\t\t\tMember ID can't be NULL");                                             //user input is checked for NULL strings

      }while(!(strcmp(new->memb_id,"\0")) || (new->memb_id[0] == chk_wht_spc[0]));

     }while(flag);

     //-------------------------------------------------------------------------

    do
      {
        printf("\n\t\t\t\t\t\tEnter the name of member\n\t\t\t\t\t\t");                             //accepts the name of member
        acceptstring(new->memb_name);

           if(!(strcmp(new->memb_name,"\0")) || (new->memb_name[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tName can't be NULL");                                             //user input is checked
      }while(!(strcmp(new->memb_name,"\0")) || (new->memb_name[0] == chk_wht_spc[0]));

     //-------------------------------------------------------------------------

         int chk = 0;

         do
          {
           fflush(stdin);

           printf("\n\t\t\t\t\t\tEnter the phone of member\n\t\t\t\t\t\t");                          //phone number is accepted
           chk = scanf("%ld",&new->phone);

           if(new->phone < 1)
           printf("\n\t\t\t\t\t\tQuantity can't be less than zero");
          }while(new->phone < 1 || chk == 0);

      //-------------------------------------------------------------------------

           if(!(*member_info))
           temp = (*member_info) = new;
         else
         {
          temp = (*member_info);                                                                    //linked list function to add new member using the double pointer
          while(temp->next != NULL)
          temp = temp->next;
          temp->next = new;
          temp = new;

         }

     //-------------------------------------------------------------------------

         printf("\n\t\t\t\t\t\tMember added successfully");

         temp = NULL;
         new = NULL;
         free(temp);                                                                                //memory is freed
         free(new);


}

//*******************************************************************************************************************************

void remove_member(struct member **member_info)                                                    //this function is used to remove a member
{

    char member_id[max_size];
    struct member **temp;
    struct member *free_m;

       printf("\n\t\t\t\t\t\tEnter Member Id\n\t\t\t\t\t\t");
       acceptstring(member_id);
              temp = member_info;                                                                   //accepts member id

       while(*temp)
        {
         if( !(strcmp((*temp)->memb_id,member_id)  ) )                                              //compares member id in record with the user input
         {
              free_m = (*temp);
              *temp = (*temp)->next;                                                                //if found then reomves the record, it follows the linked list function to remove a node
              free(free_m);                                                                         //using double pointer
              free_m = NULL;
              printf("\n\t\t\t\t\t\tMember deleted successfully\n");
              break;
         }
         else
            temp = &(*temp)->next;
            if(temp == NULL)                                                                        //if not found then appropriate message is displayed
            printf("\n\t\t\t\t\t\tId not found\n");
        }
      temp = NULL;
      free(temp);

}

//*******************************************************************************************************************************

void view_mem(struct member *member_info)                                                            //this is funciton is used to veiw a member
{
   struct member *temp = member_info;

   while(temp)                                                                                       //loops iterates through the list
   {
       memberinfo(temp);                                                                             //succesively the display function is called
       temp = temp->next;
   }
}

//*******************************************************************************************************************************

void search_mem(struct member *member_info)                                                            //this fucntion is used to search a member
{
  char meminfo[max_size];
  struct member *temp = member_info;
  int option;
  int flag = 0;

  printf("\n\t\t\t\t\t\tPress 1 to search by Member Id");
  printf("\n\t\t\t\t\t\tPress 2 to search by Member Name");                                            //asks for searching method
  fflush(stdin);
  printf("\n\t\t\t\t\t\t");
  scanf("%d",&option);
  system("cls");
  switch(option)                                                                                       //switch operates according to user input
  {
      case 1 : printf("\n\t\t\t\t\t\tEnter the ID of Member\n\t\t\t\t\t\t");
               acceptstring(meminfo);                                                                  //this function accepts the member id from user
                while(temp)
                  {
                    if(!(strcmp(meminfo,temp->memb_id)))                                               //compares user input with data in list
                    {
                        flag = 1;                                                                      //if found falg is set to '1'
                        memberinfo(temp);                                                              //display function is called
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)                                                                          //if not found then appropriate message will be displayed
                        printf("\n\t\t\t\t\t\tID not found\n");

               break;

    //-------------------------------------------------------------------------

      case 2 : printf("\n\t\t\t\t\t\tEnter the Name of Member\n\t\t\t\t\t\t");                         //accepts the member name, rest of the functioning is same as case 1
               acceptstring(meminfo);
                while(temp)
                  {
                    if(!(strcmp(meminfo,temp->memb_name)))
                    {
                        flag = 1;
                        memberinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tName not found\n");

                break;

     default : printf("\n\t\t\t\t\t\tWrong Option");
  };
}

//*******************************************************************************************************************************

void memberinfo(struct member *temp)                                                                  // it acts as supporting function for other member info function which need to display member info
{
    printf("\n****************************************************************************************************************************\n");
    printf("\n\t\t\t\t\t\tMember ID = %s",temp->memb_id);
    printf("\n\t\t\t\t\t\tMember Name = %s",temp->memb_name);
    printf("\n\t\t\t\t\t\tPhone Number = %ld",temp->phone);
    printf("\n\n****************************************************************************************************************************\n");
}

//*******************************************************************************************************************************

void timedisplay()                                                                                    //this function is used to display time
{
    time_t t;                                                                                         //declared a variable 't' with data type time_t(available in time.h header file)
    time(&t);                                                                                         //address of variable 't' is passed as parameter to time function which stores current time stamp in 't'
    printf("\n\t\t\t\t\t\t%s\n\n\n",ctime(&t));                                                       //ctime function converts the time into a c lang string and into a human readable format
}

//*******************************************************************************************************************************

void issue(struct book **book_info,struct member *member_info,struct issue **issue_info)              //this fucntion handles varies options related to issuing the book
{

    do
    {
     system("cls");
     int option;
     printf("\n****************************************************************************************************************************\n");
     printf("\n\t\t\t\t\t\tSelect the option");
     printf("\n\t\t\t\t\t\tPress 1 and hit 'Enter' to Issue a book");
     printf("\n\t\t\t\t\t\tPress 2 and hit 'Enter' to search issued book");
     printf("\n\t\t\t\t\t\tPress 3 and hit 'Enter' to view list of issued books");                    //displays vaious options
     printf("\n\t\t\t\t\t\tPress 4 and hit 'Enter' to remove issued book\n");
     printf("\n****************************************************************************************************************************\n\t\t\t\t\t\t");

     fflush(stdin);
     scanf("%d",&option);
     system("cls");
     //-------------------------------------------------------------------------
        switch(option)
        {
            case 1 :  if(member_info)                                                                 //checks if the linked list for member info exists
                       {
                        if(*book_info)                                                                //checks if the linked list for book info exists
                         issue_book(book_info,member_info,issue_info);                                //calls the issue book fucntion
                        else
                         printf("\n\t\t\t\t\t\tNo Books Available\n");
                       }
                      else
                         printf("\n\t\t\t\t\t\tNo Members Available\n");
                      break;

            case 2 :  if(*issue_info)
                      search_issueed(*issue_info);                                                    //calls the search_issued function to search a issued book
                     else
                        printf("\n\t\t\t\t\t\tNo Books are Issued\n");
                     break;

            case 3 :   if(*issue_info)
                      view_issued_list(*issue_info);                                                  //calls the view_list function to view the list of issued books
                     else
                        printf("\n\t\t\t\t\t\tNo Books are Issued\n");
                     break;

            case 4 :  if(*issue_info)
                      remove_issued_book(book_info,issue_info);                                       //calls the remove the function remove a issued book
                     else
                        printf("\n\t\t\t\t\t\tNo Books are Issued\n");
                     break;

            default : printf("\n\t\t\t\t\t\tWrong Option\n");

        };

   //-------------------------------------------------------------------------

      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

   }while(1);
}

//*******************************************************************************************************************************

void issue_book(struct book **book_info,struct member *member_info,struct issue **issue_info)         //this fucntion is used to issue books
{

  struct member *memb_temp = member_info;
  struct book *book_temp = (*book_info);
  struct issue *issue_temp = (*issue_info);
  struct issue *new = NULL;
  char bookinfo[max_size];
  char membinfo[max_size];
  int flag = 0;

   //-------------------------------------------------------------------------


    printf("\n\t\t\t\tEnter the Book ID\n\t\t\t\t\t\t");
    acceptstring(bookinfo);                                                                           //accspts the book id from user

         while(book_temp)
            {
              if(!(strcmp(bookinfo,book_temp->Book_ID)))                                              //checks the user input in record
                {
                    flag = 1;                                                                         //if found sets the flag to 1
                  if((book_temp->Quantity) == 0)                                                      //if book quantity is null then sets teh flag to 0
                    flag = 0;
                  break;
                }
                  else
              book_temp = book_temp->next;
            }

              if(!flag)                                                                               //if book is not available in library then displays the appropraite message
              {
                printf("\n\t\t\t\t\t\tBook not found\n");
                return;
              }

   //-------------------------------------------------------------------------



     printf("\n\t\t\t\tEnter the Member ID\n\t\t\t\t\t\t");
     acceptstring(membinfo);                                                                           //accepts the member id

         while(memb_temp)
            {
              if(!(strcmp(membinfo,memb_temp->memb_id)))
                {
                  flag = 1;
                  break;
                }
                  else
              memb_temp = memb_temp->next;
            }
              if(!flag)
              {
                printf("\n\t\t\t\t\t\tMember not found\n");
                return;
              }



   //-------------------------------------------------------------------------

     --book_temp->Quantity;                                                                            //if meber_id as well as book id both are valid, then the book is issued and its quantity is reduced by 1
                                                                                                       //from books record
     new = (struct issue *)malloc(sizeof(struct issue));
     strcpy(new->Book_Id,book_temp->Book_ID);                                                          //new memory is allocated and issued_books record is updated
     strcpy(new->memb_id,memb_temp->memb_id);
     new ->next = NULL;

     if(!(*issue_info))
           issue_temp = (*issue_info) = new;

         else
         {
          issue_temp = (*issue_info);
          while(issue_temp->next != NULL)
          issue_temp = issue_temp->next;                                                               //linked function to add new node using a double pointer
          issue_temp->next = new;
          issue_temp = new;
         }

     //-------------------------------------------------------------------------

         printf("\n\t\t\t\t\t\tBook issued successfully");

         book_temp = NULL;
         issue_temp = NULL;
         memb_temp = NULL;
         new = NULL;
         free(book_temp);                                                                               //frees the issued memory
         free(issue_temp);
         free(memb_temp);
         free(new);

}

//*******************************************************************************************************************************

void search_issueed(struct issue *issue_info)                                                           //the function is used to search info in issued books record
{

 struct issue *temp = issue_info;
 int option = 0;
 char choice[max_size];
 int flag = 0;

  printf("\n\t\t\t\t\tPress 1 and hit 'Enter' to search by Book ID");
  printf("\n\t\t\t\t\tPress 2 and hit 'Enter' to search by Member ID\n\t\t\t\t\t\t");                   //asks for choice
  fflush(stdin);
  scanf("%d",&option);
  system("cls");
      //-------------------------------------------------------------------------

  switch(option)
  {
      case 1 : printf("\n\t\t\t\t\tEnter the Book ID\n\t\t\t\t\t\t");
               acceptstring(choice);                                                                    //accepts the book id from the user
               while(temp)
                  {
                    if(!(strcmp(choice,temp->Book_Id)))
                    {
                        flag = 1;
                        issueinfo(temp);                                                                //if found the display function is called and flag is set to 1
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tBook not found\n");                                       //if not found then appropriate message is displayed

                break;

      //-------------------------------------------------------------------------

      case 2 : printf("\n\t\t\t\t\tEnter the Member ID\n\t\t\t\t\t\t");
               acceptstring(choice);                                                                    //accepts the member id
               while(temp)
                  {
                    if(!(strcmp(choice,temp->memb_id)))
                    {
                        flag = 1;
                        issueinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tMember not found\n");

                break;

      default : printf("\n\t\t\t\t\t\tWrong Option");

  }

}

//*******************************************************************************************************************************

void view_issued_list(struct issue *issue_info)                                                           //the function is used to view the list of all issued book and their details
{
  struct issue *temp = issue_info;
  while(temp)
  {
     issueinfo(temp);                                                                                     //calls the display info function
     temp = temp->next;
  }
}

//*******************************************************************************************************************************

void remove_issued_book(struct book **book_info,struct issue **issue_info)                                //this function is used to remove a record from issued books
{

    char book_id[max_size];
    struct issue **temp = issue_info;
    struct issue *free_m;
    struct book **btemp = book_info;
    int flag = 0;

       printf("\n\t\t\t\t\t\tEnter Book Id\n\t\t\t\t\t\t");                                                //accepts book id
       acceptstring(book_id);

       while(*temp)
        {
         if( !(strcmp((*temp)->Book_Id,book_id)  ) )                                                       //compares the user input with records
         {
              free_m = (*temp);
              *temp = (*temp)->next;                                                                       //if record is found then it is removed from the list
              free(free_m);                                                                                //linked likst function to remove a node using double pointer
              free_m = NULL;
              printf("\n\t\t\t\t\t\tBook unissued successfully\n");
              flag = 1;
              break;
         }
         else
            temp = &(*temp)->next;
            if(temp == NULL)
            printf("\n\t\t\t\t\t\tId not found\n");
        }

        temp = NULL;
        free(temp);

        if(flag)
        {
         while(*btemp)
           {
            if(!(strcmp((*btemp)->Book_ID,book_id)))                                                      //the book id is searched in books record and its quantity is increased by 1
              {
                ++(*btemp)->Quantity;
                break;
              }
             else
                    btemp = &(*btemp)->next;
            }
        }

        btemp = NULL;
        free(btemp);


}

//*******************************************************************************************************************************

void issueinfo(struct issue *temp)                                                                        //this function acts as display info function for other function working on issued books
{

    printf("\n****************************************************************************************************************************\n");
    printf("\n\t\t\t\t\t\tBook ID = %s",temp->Book_Id);
    printf("\n\t\t\t\t\t\tMember ID = %s",temp->memb_id);
    printf("\n\n****************************************************************************************************************************\n");

}

//*******************************************************************************************************************************

int main()                                                                                                 //main :)
 {

      HWND hwnd = GetConsoleWindow();                                                                      //windows api function to get console in handle(declared in windows.h)
	  ShowWindow(hwnd,SW_MAXIMIZE);                                                                    //windows api function to set console to full screen mode
	  SetConsoleTitle("LIBRARY MANAGEMENT SYSTEM");                                                    //windows api function to set the title to console

     //-------------------------------------------------------------------------

    int option = 0;
    struct book *book_info = NULL;                                                                         //book_info pointer acts as head for the linked list which stores book info
    struct member *member_info = NULL;                                                                     //member_info pointer acts as head for the linked list which stores member info
    struct issue *issue_info = NULL;                                                                       //issue_info pointer acts as head for the linked list which stores issued info

    //-------------------------------------------------------------------------

    read_books_file(&book_info);                                                                           //reads data from books file
    read_members_file(&member_info);                                                                       //reads data from members file
    read_issue_file(&issue_info);                                                                          //reads data from issued file

    if(book_info)
   book_info = mergesort(book_info,'N');                                                                   //if book_info linked contains any node then it is sorted using merge sort.
                                                                                                           //Here 'N' parameter tells the merge sort to sort the data using 'N'ames of book
   //-------------------------------------------------------------------------

   do
   {
       system("color 2");                                                                                  //windows api function to set a specified color to text
        system("cls");
      timedisplay();                                                                                       //function to display time
      printf("\n\t\t\t\t\t\tEnter your option");
      printf("\n\t\t\t\t\t\t1. Issue Books");
      printf("\n\t\t\t\t\t\t2. Search Books");
      printf("\n\t\t\t\t\t\t3. View Book List");
      printf("\n\t\t\t\t\t\t4. Add Books to Record");
      printf("\n\t\t\t\t\t\t5. Edit Books Record");                                                         //various options to perform a task
      printf("\n\t\t\t\t\t\t6. Delete Books from Record");
      printf("\n\t\t\t\t\t\t7. Manage Member");
      printf("\n\t\t\t\t\t\t8. Close Application\n\t\t\t\t\t\t");

      fflush(stdin);                                                                                        //flushes the input stream
      scanf("%d",&option);                                                                                  //accepts the option from user
      system("cls");                                                                                        //clears the screen, available in stdlib.h
       switch(option)
       {

         case 1  :  issue(&book_info,member_info,&issue_info);                                              //function to perform various tasks related to book issuing
                   break;

         case 2  : if(book_info)
                     search_book(book_info);                                                                //function to search a record in book info
                   else
		   {
                     printf("\n\t\t\t\t\t\tNo Books Available");
		     Sleep(3000);                                                                           //Sleep function is defined in windows.h header filed, it stops all functioning for given miliseconds.
		   }
                   break;

         case 3  : if(book_info)
                    view_books_list(book_info);                                                             //function to view books list
                   else
	           {
                     printf("\n\t\t\t\t\t\tNo Books Available");
		     Sleep(3000);
		   }
                   break;

         case 4  : add_books_to_record(&book_info);                                                         //function to add new books in the list
                   break;

         case 5  : if(book_info)
                     edit_books_record(&book_info);                                                         //function to edit books record
                   else
		   {
                     printf("\n\t\t\t\t\t\tNo Books Available");
		     Sleep(3000);
		   }
                   break;

         case 6  : if(book_info)
                     delete_books_record(&book_info);                                                       //function to delete a node from books record
                   else
		   {
                     printf("\n\t\t\t\t\t\tNo Books Available");
		     Sleep(3000);
		   }
                   break;

         case 7 :  mem(&member_info);                                                                       //function to perform various tasks related to members
                   break;

         case 8  : close_application(book_info,member_info,issue_info);                                     //calls the close application function, the function saves all the data in .txt files
                   book_info = NULL;
		   member_info = NULL;                                                                      //sets the pointer to NULL
		   issue_info = NULL;
                   free(book_info);
		   free(member_info);                                                                       //free the allocated memory
		   free(issue_info);
                   exit(0);
                    break;

         default : printf("\n\t\t\t\t\t\tWrong option selected\n");

       };
   }while(1);
 }
//*******************************************************************************************************************************
