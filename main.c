
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "declared.h"
#include <stdio.h>
#define _WIN32_WINNT 0x0500 //constant for console resizing (redefinition as per mentioned in header file)
#include <windows.h> //defines a very large number of Windows specific functions that can be used in C.

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

FILE * read_books;
FILE * issueb;
FILE * members;

//*******************************************************************************************************************************

void read_books_file(struct book **book_info)
{

  struct book *new = NULL, *temp = NULL;

  if( (read_books = fopen("books.txt","r")) == NULL )
    return;
  else
  {

      while(!feof(read_books))
      {

        new = (struct book *) malloc (sizeof(struct book));
        new->next = NULL;

        fflush(stdin);
        fscanf(read_books,"%s %s %s %s %d %d %d",new->Category,new->Book_ID,new->Book_Name,new->Author_Name,&new->Quantity,&new->Price,&new->Rack_No);

        if(!(*book_info))
          temp = (*book_info) = new;
        else
        {

          temp->next = new;
          temp = new;

        }

      }

   }
      temp = NULL;
      new = NULL;
      free(temp);
      free(new);
      fclose(read_books);

}

//*******************************************************************************************************************************

void read_members_file(struct member **member_info)
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

void read_issue_file(struct issue **issue_info)
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

void add_books_to_record(struct book **book_info)
{

 do
  {
      system("cls");
     struct book *new = NULL, *temp = NULL, *temp1 = (*book_info);
     char chk_wht_spc[2] = {' ','\0'};

     new = (struct book *) malloc (sizeof(struct book));
     new->next = NULL;
        int flag = 0;
         do
         {

          do
           {
            flag = 0;
            printf("\n\t\t\t\t\t\tEnter the book ID\n\t\t\t\t\t\t");
            acceptstring(new->Book_ID);

            while(temp1)
             {
                if(!(strcmp(new->Book_ID,temp1->Book_ID)))
                 {
                   flag = 1;
                   printf("\n\t\t\t\t\t\tYou have entered already used ID, please choose another ID\n");
                   break;
                 }
                else
                temp1 = temp1->next;
             }
             if(!(strcmp(new->Book_ID,"\0")) || (new->Book_ID[0] == chk_wht_spc[0]))
             printf("\n\t\t\t\t\t\tBook ID can't be NULL");

            }while(!(strcmp(new->Book_ID,"\0")) || (new->Book_ID[0] == chk_wht_spc[0]));

        }while(flag);

      //-------------------------------------------------------------------------

         do
          {
           printf("\n\t\t\t\t\t\tEnter the book Name\n\t\t\t\t\t\t");
           acceptstring(new->Book_Name);

           if(!(strcmp(new->Book_Name,"\0")) || (new->Book_Name[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tBook Name can't be NULL");
          }while((!strcmp(new->Book_Name,"\0")) || (new->Book_Name[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         do
          {
           printf("\n\t\t\t\t\t\tEnter the book Author Name\n\t\t\t\t\t\t");
           acceptstring(new->Author_Name);

           if(!(strcmp(new->Author_Name,"\0")) || (new->Author_Name[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tAuthor Name can't be NULL");
           }while(!(strcmp(new->Author_Name,"\0")) || (new->Author_Name[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         do
          {
           printf("\n\t\t\t\t\t\tEnter the Category of book\n\t\t\t\t\t\t");
           acceptstring(new->Category);

           if(!(strcmp(new->Category,"\0")) || (new->Category[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tCategory can't be NULL");
          }while(!(strcmp(new->Category,"\0")) || (new->Category[0] == chk_wht_spc[0]));

      //-------------------------------------------------------------------------

         int chk = 0;

         do
          {
           fflush(stdin);

           printf("\n\t\t\t\t\t\tEnter the book Quantity\n\t\t\t\t\t\t");
           chk = scanf("%d",&new->Quantity);

           if(new->Quantity < 1)
           printf("\n\t\t\t\t\t\tQuantity can't be less than zero");
          }while(new->Quantity < 1 || chk == 0);

         chk = 0;

      //-------------------------------------------------------------------------

         do
         {
          fflush(stdin);
          printf("\n\t\t\t\t\t\tEnter the book Price\n\t\t\t\t\t\t");
          chk = scanf("%d",&new->Price);

          if(new->Price < 1)
           printf("\n\t\t\t\t\t\tPrice can't be less than zero");
         }while(new->Price < 1 || chk == 0 );

      //-------------------------------------------------------------------------

         chk = 0;

         do
         {
          fflush(stdin);
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
          temp = (*book_info);
          while(temp->next != NULL)
          temp = temp->next;
          temp->next = new;
          temp = new;

         }

         printf("\n\t\t\t\t\t\tBook added successfully");
         temp = NULL;
         temp1 = NULL;
         new = NULL;
         free(temp);
         free(temp1);
         free(new);

      //-------------------------------------------------------------------------

          int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

  }while(1);
}

//*******************************************************************************************************************************

void close_application(struct book *book_info,struct member *member_info,struct issue *issue_info)
{

    struct book * temp = NULL;
    if(book_info)
    {

       read_books = fopen("books.txt","w");

         book_info = mergesort(book_info,'N');
         temp = book_info;

         while(temp)
         {
           fflush(stdout);
           fprintf(read_books,"%s %s %s %s %d %d %d",temp->Category,temp->Book_ID,temp->Book_Name,temp->Author_Name,temp->Quantity,temp->Price,temp->Rack_No);
           temp = temp->next;

         }

    }
    else
     remove("books.txt");

    temp = NULL;
    free(temp);
    fclose(read_books);

//-------------------------------------------------------------------------

    struct member * temp1 = NULL;
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

   struct issue * temp2 = NULL;
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

void delete_books_record(struct book **book_info)
{

 do
  {
    system("cls");
    char book_id[max_size];
    struct book **temp;
    struct book *free_m;

       printf("\n\t\t\t\t\t\tChoose Book Id\n\t\t\t\t\t\t");
       acceptstring(book_id);

              temp = book_info;

       while(*temp)
        {
         if( !(strcmp (((*temp)->Book_ID),book_id)) )
         {
              free_m = (*temp);
              *temp = (*temp)->next;
              free(free_m);
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
      if((flag_c = askforcontinuation()))
           return;

  }while(1);

}

//*******************************************************************************************************************************

void search_book(struct book *book_info)
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
      printf("\n\t\t\t\t\t\tPress '2' and hit 'Enter' for Book_ID");
      printf("\n\t\t\t\t\t\tPress '3' and hit 'Enter' for Book_Name");
      printf("\n\t\t\t\t\t\tPress '4' and hit 'Enter' for Author_Name");
      printf("\n\n****************************************************************************************************************************\n");

      printf("\n\t\t\t\t\t\t");
      fflush(stdin);
      scanf("%d",&option);
    system("cls");
      switch(option)
       {
         case 1 : printf("\n\t\t\t\t\t\tType the Book Category and hit 'Enter'\n\t\t\t\t\t\t");
                  acceptstring(choice_string);

                  while(temp)
                  {
                    if(!(strcmp(choice_string,temp->Category)))
                    {
                        flag = 1;
                        displaybookinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tCategory not found\n");

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

void displaybookinfo(struct book *temp)
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

void edit_books_record(struct book **book_info)
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
        if(!(strcmp(bk_id,temp->Book_ID)))
        {
            printf("\n****************************************************************************************************************************\n");
            printf("\n\t\t\t\t\t\tBook ID found");
            printf("\n\t\t\t\t\t\tSelect option to edit from following");
            displayoptions();
            printf("\n****************************************************************************************************************************\n");
            printf("\n\t\t\t\t\t\t");
            fflush(stdin);
            scanf("%d",&option);
            system("cls");
            switch(option)
            {

                case 1 : printf("\n\t\t\t\t\t\tCurrent Book Category is %s",temp->Category);
                         printf("\n\t\t\t\t\t\tEnter the new Book Catgeory\n\t\t\t\t\t\t");
                         acceptstring(c_new_data);
                         strcpy(temp->Category,c_new_data);
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
        printf("\n\t\t\t\t\t\t Id not found");

     temp = NULL;
     free(temp);

      int flag_c = 0;
      if((flag_c = askforcontinuation()))
           return;

     }while(1);

}

//*******************************************************************************************************************************

void view_books_list(struct book * book_info)
{
  do
   {

    int option = 0;
    struct book *temp = NULL;;
    printf("\n****************************************************************************************************************************");
    printf("\n\t\t\t\t\t\tChoose the option to sort the data\n");
    displayoptions();
    printf("\n\t\t\t\t\t\tPress '8' and hit 'Enter' for default view\n\t\t\t\t\t\t");
    printf("\n****************************************************************************************************************************");

    printf("\n\t\t\t\t\t\t");
    fflush(stdin);
    scanf("%d",&option);
     system("cls");
           switch(option)
           {
             case 1 : book_info = mergesort(book_info,'C');
                          temp = book_info;
                         displaybooks(temp);
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

void displaybooks(struct book *temp)
{
    while(temp)
     {
      displaybookinfo(temp);
      temp = temp->next;
     }
}

//*******************************************************************************************************************************

void displayoptions()
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

void mem(struct member **member_info)
{
   do
   {
    system("cls");
    int option = 0;

    printf("\n\t\t\t\t\t\tChoose the option from following\n");
    printf("\n\t\t\t\t\t\t Press 1 and hit 'Enter' to add member");
    printf("\n\t\t\t\t\t\t Press 2 and hit 'Enter' to remove member");
    printf("\n\t\t\t\t\t\t Press 3 and hit 'Enter' to view members");
    printf("\n\t\t\t\t\t\t Press 4 and hit 'Enter' to search member\n\t\t\t\t\t\t");

    fflush(stdin);
    scanf("%d",&option);
    system("cls");
    switch(option)
    {
        case 1 : add_member(member_info);
                  break;

        case 2 : if((*member_info))
                   remove_member(member_info);
                 else
                   printf("\n\t\t\t\t\t\tNo members available\n");
                 break;

        case 3 : if((*member_info))
                   view_mem(*member_info);
                 else
                   printf("\n\t\t\t\t\t\tNo members available\n");
                 break;

        case 4 : if((*member_info))
                   search_mem(*member_info);
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

void add_member(struct member **member_info)
{

  struct member *temp =(*member_info);
  struct member *new = NULL;
  int flag = 0;
  char chk_wht_spc[2] = {' ','\0'};

  new = (struct member *)malloc(sizeof(struct member));
  new->next = NULL;
   do
    {
     do
      {
       flag = 0;
       printf("\n\t\t\t\t\t\tEnter the ID of member\n\t\t\t\t\t\t");
       acceptstring(new->memb_id);

       while(temp)
        {
         if(!(strcmp(new->memb_id,temp->memb_id)))
          {
            flag = 1;
            printf("\n\t\t\t\t\t\tYou have entered already used ID, please choose another ID\n");
            break;
          }
        else
            temp = temp->next;
        }
       if(!(strcmp(new->memb_id,"\0")) || (new->memb_id[0] == chk_wht_spc[0]))
       printf("\n\t\t\t\t\t\tMember ID can't be NULL");

      }while(!(strcmp(new->memb_id,"\0")) || (new->memb_id[0] == chk_wht_spc[0]));

     }while(flag);

   //-------------------------------------------------------------------------

    do
      {
        printf("\n\t\t\t\t\t\tEnter the name of member\n\t\t\t\t\t\t");
        acceptstring(new->memb_name);

           if(!(strcmp(new->memb_name,"\0")) || (new->memb_name[0] == chk_wht_spc[0]))
            printf("\n\t\t\t\t\t\tName can't be NULL");
      }while(!(strcmp(new->memb_name,"\0")) || (new->memb_name[0] == chk_wht_spc[0]));

   //-------------------------------------------------------------------------

         int chk = 0;

         do
          {
           fflush(stdin);

           printf("\n\t\t\t\t\t\tEnter the phone of member\n\t\t\t\t\t\t");
           chk = scanf("%ld",&new->phone);

           if(new->phone < 1)
           printf("\n\t\t\t\t\t\tQuantity can't be less than zero");
          }while(new->phone < 1 || chk == 0);

      //-------------------------------------------------------------------------

           if(!(*member_info))
           temp = (*member_info) = new;
         else
         {
          temp = (*member_info);
          while(temp->next != NULL)
          temp = temp->next;
          temp->next = new;
          temp = new;

         }

     //-------------------------------------------------------------------------

         printf("\n\t\t\t\t\t\tMember added successfully");

         temp = NULL;
         new = NULL;
         free(temp);
         free(new);


}

//*******************************************************************************************************************************

void remove_member(struct member **member_info)
{

    char member_id[max_size];
    struct member **temp;
    struct member *free_m;

       printf("\n\t\t\t\t\t\tEnter Member Id\n\t\t\t\t\t\t");
       acceptstring(member_id);
              temp = member_info;

       while(*temp)
        {
         if( !(strcmp((*temp)->memb_id,member_id)  ) )
         {
              free_m = (*temp);
              *temp = (*temp)->next;
              free(free_m);
              free_m = NULL;
              printf("\n\t\t\t\t\t\tMember deleted successfully\n");
              break;
         }
         else
            temp = &(*temp)->next;
            if(temp == NULL)
            printf("\n\t\t\t\t\t\tId not found\n");
        }
      temp = NULL;
      free(temp);

}

//*******************************************************************************************************************************

void view_mem(struct member *member_info)
{
   struct member *temp = member_info;

   while(temp)
   {
       memberinfo(temp);
       temp = temp->next;
   }
}

//*******************************************************************************************************************************

void search_mem(struct member *member_info)
{
  char meminfo[max_size];
  struct member *temp = member_info;
  int option;
  int flag = 0;

  printf("\n\t\t\t\t\t\tPress 1 to search by Member Id");
  printf("\n\t\t\t\t\t\tPress 2 to search by Member Name");
  fflush(stdin);
  printf("\n\t\t\t\t\t\t");
  scanf("%d",&option);
  system("cls");
  switch(option)
  {
      case 1 : printf("\n\t\t\t\t\t\tEnter the ID of Member\n\t\t\t\t\t\t");
               acceptstring(meminfo);
                while(temp)
                  {
                    if(!(strcmp(meminfo,temp->memb_id)))
                    {
                        flag = 1;
                        memberinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tID not found\n");

               break;

    //-------------------------------------------------------------------------

      case 2 : printf("\n\t\t\t\t\t\tEnter the Name of Member\n\t\t\t\t\t\t");
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

void memberinfo(struct member *temp)
{
    printf("\n****************************************************************************************************************************\n");
    printf("\n\t\t\t\t\t\tMember ID = %s",temp->memb_id);
    printf("\n\t\t\t\t\t\tMember Name = %s",temp->memb_name);
    printf("\n\t\t\t\t\t\tPhone Number = %ld",temp->phone);
    printf("\n\n****************************************************************************************************************************\n");
}

//*******************************************************************************************************************************

void timedisplay()
{
    time_t t;
    time(&t);
    printf("\n\t\t\t\t\t\t%s\n\n\n",ctime(&t));
}

//*******************************************************************************************************************************

void issue(struct book **book_info,struct member *member_info,struct issue **issue_info)
{

    do
    {
     system("cls");
     int option;
     printf("\n****************************************************************************************************************************\n");
     printf("\n\t\t\t\t\t\tSelect the option");
     printf("\n\t\t\t\t\t\tPress 1 and hit 'Enter' to Issue a book");
     printf("\n\t\t\t\t\t\tPress 2 and hit 'Enter' to search issued book");
     printf("\n\t\t\t\t\t\tPress 3 and hit 'Enter' to view list of issued books");
     printf("\n\t\t\t\t\t\tPress 4 and hit 'Enter' to remove issued book\n");
     printf("\n****************************************************************************************************************************\n\t\t\t\t\t\t");

     fflush(stdin);
     scanf("%d",&option);
     system("cls");
     //-------------------------------------------------------------------------
        switch(option)
        {
            case 1 :  if(member_info)
                       {
                        if(*book_info)
                         issue_book(book_info,member_info,issue_info);
                        else
                         printf("\n\t\t\t\t\t\tNo Books Available\n");
                       }
                      else
                         printf("\n\t\t\t\t\t\tNo Members Available\n");
                      break;

            case 2 :  if(*issue_info)
                      search_issueed(*issue_info);
                     else
                        printf("\n\t\t\t\t\t\tNo Books are Issued\n");
                     break;

            case 3 :   if(*issue_info)
                      view_issued_list(*issue_info);
                     else
                        printf("\n\t\t\t\t\t\tNo Books are Issued\n");
                     break;

            case 4 :  if(*issue_info)
                      remove_issued_book(book_info,issue_info);
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

void issue_book(struct book **book_info,struct member *member_info,struct issue **issue_info)
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
    acceptstring(bookinfo);

         while(book_temp)
            {
              if(!(strcmp(bookinfo,book_temp->Book_ID)))
                {
                   flag = 1;
                  if((book_temp->Quantity) == 0)
                    flag = 0;
                  break;
                }
                  else
              book_temp = book_temp->next;
            }

              if(!flag)
              {
                printf("\n\t\t\t\t\t\tBook not found\n");
                return;
              }

   //-------------------------------------------------------------------------



     printf("\n\t\t\t\tEnter the Member ID\n\t\t\t\t\t\t");
     acceptstring(membinfo);

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

     --book_temp->Quantity;

     new = (struct issue *)malloc(sizeof(struct issue));
     strcpy(new->Book_Id,book_temp->Book_ID);
     strcpy(new->memb_id,memb_temp->memb_id);
     new ->next = NULL;

     if(!(*issue_info))
           issue_temp = (*issue_info) = new;

         else
         {
          issue_temp = (*issue_info);
          while(issue_temp->next != NULL)
          issue_temp = issue_temp->next;
          issue_temp->next = new;
          issue_temp = new;
         }

     //-------------------------------------------------------------------------

         printf("\n\t\t\t\t\t\tBook issued successfully");

         book_temp = NULL;
         issue_temp = NULL;
         memb_temp = NULL;
         new = NULL;
         free(book_temp);
         free(issue_temp);
         free(memb_temp);
         free(new);

}

//*******************************************************************************************************************************

void search_issueed(struct issue *issue_info)
{

 struct issue *temp = issue_info;
 int option = 0;
 char choice[max_size];
 int flag = 0;

  printf("\n\t\t\t\t\tPress 1 and hit 'Enter' to search by Book ID");
  printf("\n\t\t\t\t\tPress 2 and hit 'Enter' to search by Member ID\n\t\t\t\t\t\t");
  fflush(stdin);
  scanf("%d",&option);
  system("cls");
      //-------------------------------------------------------------------------

  switch(option)
  {
      case 1 : printf("\n\t\t\t\t\tEnter the Book ID\n\t\t\t\t\t\t");
               acceptstring(choice);
               while(temp)
                  {
                    if(!(strcmp(choice,temp->Book_Id)))
                    {
                        flag = 1;
                        issueinfo(temp);
                        break;
                    }
                    else
                    temp = temp->next;
                  }
                    if(!flag)
                        printf("\n\t\t\t\t\t\tBook not found\n");

                break;

      //-------------------------------------------------------------------------

      case 2 : printf("\n\t\t\t\t\tEnter the Member ID\n\t\t\t\t\t\t");
               acceptstring(choice);
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

void view_issued_list(struct issue *issue_info)
{
  struct issue *temp = issue_info;
  while(temp)
  {
     issueinfo(temp);
     temp = temp->next;
  }
}

//*******************************************************************************************************************************

void remove_issued_book(struct book **book_info,struct issue **issue_info)
{

    char book_id[max_size];
    struct issue **temp = issue_info;
    struct issue *free_m;
    struct book **btemp = book_info;
    int flag = 0;

       printf("\n\t\t\t\t\t\tEnter Book Id\n\t\t\t\t\t\t");
       acceptstring(book_id);

       while(*temp)
        {
         if( !(strcmp((*temp)->Book_Id,book_id)  ) )
         {
              free_m = (*temp);
              *temp = (*temp)->next;
              free(free_m);
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
            if(!(strcmp((*btemp)->Book_ID,book_id)))
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

void issueinfo(struct issue *temp)
{

    printf("\n****************************************************************************************************************************\n");
    printf("\n\t\t\t\t\t\tBook ID = %s",temp->Book_Id);
    printf("\n\t\t\t\t\t\tMember ID = %s",temp->memb_id);
    printf("\n\n****************************************************************************************************************************\n");

}

//*******************************************************************************************************************************

int main()
 {

      HWND hwnd = GetConsoleWindow();
	  ShowWindow(hwnd,SW_MAXIMIZE);
	  SetConsoleTitle("LIBRARY MANAGEMENT SYSTEM");

	//-------------------------------------------------------------------------

    int option = 0;
    struct book *book_info = NULL;
    struct member *member_info = NULL;
    struct issue *issue_info = NULL;

    //-------------------------------------------------------------------------

    read_books_file(&book_info);
    read_members_file(&member_info);
    read_issue_file(&issue_info);

    if(book_info)
   book_info = mergesort(book_info,'N');

   //-------------------------------------------------------------------------

   do
   {
       system("color 2");
        system("cls");
      timedisplay();
      printf("\n\t\t\t\t\t\tEnter your option");
      printf("\n\t\t\t\t\t\t1. Issue Books");
      printf("\n\t\t\t\t\t\t2. Search Books");
      printf("\n\t\t\t\t\t\t3. View Book List");
      printf("\n\t\t\t\t\t\t4. Add Books to Record");
      printf("\n\t\t\t\t\t\t5. Edit Books Record");
      printf("\n\t\t\t\t\t\t6. Delete Books from Record");
      printf("\n\t\t\t\t\t\t7. Manage Member");
      printf("\n\t\t\t\t\t\t8. Close Application\n\t\t\t\t\t\t");

      fflush(stdin);
      scanf("%d",&option);
      system("cls");
       switch(option)
       {

         case 1  :  issue(&book_info,member_info,&issue_info);
                   break;

         case 2  : if(book_info)
                     search_book(book_info);
                   else
                     printf("\n\t\t\t\t\t\tNo Books Available");
                   break;

         case 3  : if(book_info)
                    view_books_list(book_info);
                   else
                     printf("\n\t\t\t\t\t\tNo Books Available");
                   break;

         case 4  : add_books_to_record(&book_info);
                   break;

         case 5  : if(book_info)
                     edit_books_record(&book_info);
                   else
                     printf("\n\t\t\t\t\t\tNo Books Available");
                   break;

         case 6  : if(book_info)
                     delete_books_record(&book_info);
                   else
                     printf("\n\t\t\t\t\t\tNo Books Available");
                   break;

         case 7 :  mem(&member_info);
                   break;

         case 8  : close_application(book_info,member_info,issue_info);
                   book_info = NULL;
                   free(book_info);
                   exit(0);
                    break;

         default : printf("\n\t\t\t\t\t\tWrong option selected\n");

       };
   }while(1);
 }
//*******************************************************************************************************************************
