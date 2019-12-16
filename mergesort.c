

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declared.h"



struct book* sortedmerge(struct book *, struct book*, char);
void split(struct book *, struct book **, struct book **);
struct book* mergesort(struct book*,char);
int compare_strings(char *a,char *b);
int compare_int(int a,int b);
int compare_int(int a,int b);


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

struct book* sortedmerge(struct book* a, struct book* b, char n)
{
	struct book* result = NULL;
    int comparision_flag = 0;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

    switch(n)
    {
      case 'C'    :  comparision_flag = compare_strings(a->Category, b->Category);break;
      case 'I'    :  comparision_flag = compare_strings(a->Book_ID, b->Book_ID);break;
      case 'N'    :  comparision_flag = compare_strings(a->Book_Name, b->Book_Name);break;
      case 'A'    :  comparision_flag = compare_strings(a->Author_Name, b->Author_Name);break;
      case 'Q'    :  comparision_flag = compare_int(a->Quantity, b->Quantity);break;
      case 'P'    :  comparision_flag = compare_int(a->Price, b->Price);break;
      case 'R'    :  comparision_flag = compare_int(a->Rack_No, b->Rack_No);break;
    };


	if (comparision_flag)
    {
		result = a;
		result->next = sortedmerge(a->next, b, n);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next, n);
	}
	return (result);
}

void split(struct book* source,struct book** front, struct book** back)
{
	struct book* fast;
	struct book* slow;
	slow = source;
	fast = source->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	(*front) = source;
	(*back) = slow->next;
	slow->next = NULL;
}


int compare_int(int a,int b)
{
  if(a < b)
    return 1;
    return 0;
}


int compare_strings(char *a,char *b)
{
  int c;
  c = strcmp(a,b);
  if(c < 0)
  return 1;
  return 0;
}

