#ifndef declared_h
#define declared_h

#ifndef max_size
#define max_size 21
#endif // max_size

#ifndef struct_book
#define struct_book
struct book
{
  char Category[max_size];
  char Book_ID[max_size];
  char Book_Name[max_size];
  char Author_Name[max_size];
  int Quantity;
  int Rack_No;
  int Price;
  struct book *next;
};
#endif // struct_book

#ifndef struct_issue
#define struct_issue
struct issue
{
  char memb_id[max_size];
  char Book_Id[max_size];
  struct issue *next;
};
#endif // struct_issue

#ifndef struct_member
#define struct_member
struct member
{
  char memb_name[max_size];
  char memb_id[max_size];
  unsigned long int phone;
  struct member *next;
};
#endif // struct_member

#ifndef merge_sort
#define merge_sort
struct book * mergesort(struct book*,char);
#endif // merge_sort

#ifndef accep_string
#define accept_string
void acceptstring(char *);
#endif // accep_string

#ifndef ask_continuation
#define ask_continuation
int askforcontinuation();
#endif // ask_continuation

#endif // declared

