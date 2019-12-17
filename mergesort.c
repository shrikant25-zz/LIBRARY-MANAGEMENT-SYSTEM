//this program accepts a linked list and sorts the lsit with merge sort
//the merge sort is modified according to the requirements of the program
//along with the list the sort function accepts a character whhich the first word of the optin choosen by user, options include the members of book structure(for more chech declared.h)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declared.h"



struct book* sortedmerge(struct book *, struct book*, char);   //the basic function to accept a list
void split(struct book *, struct book **, struct book **);     //this function splits the list
struct book* mergesort(struct book*,char);                     //this function merges the two lists
int compare_strings(char *a,char *b);                          //function to compare two strings
int compare_int(int a,int b);                                  //function to compare two integers


struct book* mergesort(struct book* h,char n)                   
{
	struct book* head = h;
	struct book* a = NULL;
	struct book* b = NULL;


	if ((head == NULL) || (head->next == NULL))
       return head;

	split(head,&a,&b);                                          

	a = mergesort(a,n);
	b = mergesort(b,n);

	head = sortedmerge(a, b,n);
	return head;
}

struct book* sortedmerge(struct book* a, struct book* b, char n)    //accepts two string and a character
{
	struct book* result = NULL;
    int comparision_flag = 0;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

    switch(n)                                                        //checks the character and calls the compare function and sets the comparison_flag accordingly
    {
      case 'C'    :  comparision_flag = compare_strings(a->Category, b->Category);break;
      case 'I'    :  comparision_flag = compare_strings(a->Book_ID, b->Book_ID);break;
      case 'N'    :  comparision_flag = compare_strings(a->Book_Name, b->Book_Name);break;
      case 'A'    :  comparision_flag = compare_strings(a->Author_Name, b->Author_Name);break;
      case 'Q'    :  comparision_flag = compare_int(a->Quantity, b->Quantity);break;
      case 'P'    :  comparision_flag = compare_int(a->Price, b->Price);break;
      case 'R'    :  comparision_flag = compare_int(a->Rack_No, b->Rack_No);break;
    };


	if (comparision_flag)                                       //if comparision_flag is true it means the first string is smaller
         {                                                          //hence it will be added first in the list
		result = a;                                            
		result->next = sortedmerge(a->next, b, n);         //recursivley calls itself untill an exit condition is encountered
	}
	else
	{
		result = b;                                        //if compariosion_flag is false it means the second string is smaller
		result->next = sortedmerge(a, b->next, n);          //hence it will be added first in the list
	}
	return (result);
}

void split(struct book* source,struct book** front, struct book** back)  //this function splits the given string in two parts, it accepts the pointer to the head of the string and address of other two pointers 
{                                                                        //the other two pointers are used two store the two parts of the string after splitting.
	struct book* fast;                                               //[ source->1->2->3->4->NULL ]
	struct book* slow;
	slow = source;                                                      //pointer 'slow' is assigned the address of first element of the string 
	fast = source->next;                                                //pointer  'fast' is assigned the address of the element next to first element(i.e second element)

	while (fast != NULL) 
	{                                                          //untill the fast pointer reaches NULL the loop continues
		fast = fast->next;                                 //the 'fast' pointer is incremented twice while the 'slow' pointer is incremented only once per iterarion
		if (fast != NULL) {
			slow = slow->next;                         //both the pointer are incremented
			fast = fast->next;
		}
	}                                                          //because of such incrementation the 'fast' pointer reaches the end of the string and at the same time 
                                                                   //th slow pointer reaches at the the center of string
	(*front) = source;                                         //'front' pointer is assigned the address of head os the string
	(*back) = slow->next;                                      //while the 'back' pointer is assigned the address of the element next to the element at center
	slow->next = NULL;                                         //the 'slow' is set to store NULL in its address storing ('next') place, resulting in the split of string.
}                                                                  // [ source->1->2->3->4->NULL ]  ....  after split [ front->1->2->NULL and back->3->4->NULL ]    


int compare_int(int a,int b)
{
  if(a < b)                                                        //compares the integers and returns the value accordingly
    return 1;
    return 0;
}


int compare_strings(char *a,char *b)                                //compares the string and returns the value accordingly
{
  int c;
  c = strcmp(a,b);
  if(c < 0)
  return 1;
  return 0;
}

