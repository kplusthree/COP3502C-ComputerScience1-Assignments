// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "ListyFib.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListyInt *listyAdd(ListyInt *p, ListyInt *q)
{
  int longestLength, shortestLength, difference, addition, wasGreater;
  // temporary node to cycle through lists
  Node *temp, *temp2, *temp3;
  // allocate memory for a struct with the sum
  ListyInt *sum = (ListyInt*)malloc(sizeof(ListyInt));

  // checks for NULL pointers and failed memory allocation
  if (p == NULL || q == NULL)
  {
    free(sum);
    return NULL;
  }
  if (sum == NULL)
  {
    return NULL;
  }

  // find the larger of the two lists
  if (p->length >= q->length)
  {
    longestLength = p->length;
    shortestLength = q->length;
    temp2 = p->head;
    temp3 = q->head;
  }
  else
  {
    longestLength = q->length;
    shortestLength = p->length;
    temp2 = q->head;
    temp3 = p->head;
  }

  // find how many nodes the two lists have that aren't empty
  difference = longestLength - shortestLength;

  // allocate temp
  temp = (Node*)malloc(sizeof(Node));

  // create the head of the new list
  sum->head = (Node*)malloc(sizeof(Node));
  temp = sum->head;

  if (temp == NULL)
  {
    free(sum);
    return NULL;
  }

  temp->next = NULL;
  wasGreater = 0;
  sum->length = 0;

  for (int i = 0; i < shortestLength; i++)
  {
    // checks for failed memory allocation
    if (temp == NULL)
    {
      destroyListyInt(sum);
      return NULL;
    }

    // add the two numbers, and any carry over.
    addition = temp2->digit + temp3->digit + wasGreater;
    if (addition > 9)
    {
      addition = addition % 10;
      wasGreater = 1;
    }
    else
    {
      wasGreater = 0;
    }

    sum->length++;

    temp->digit = addition;
    //printf("digit: %d and i %d\n", temp->digit, i);
    temp->next = (Node*)malloc(sizeof(Node));
    temp = temp->next;
    // move through the two lists
    temp2 = temp2->next;
    temp3 = temp3->next;
  }

  // while one list is only contributing 0
  for (int i = 0; i < difference; i++)
  {
    // checks for failed memory allocation
    if (temp == NULL)
    {
      destroyListyInt(sum);
      return NULL;
    }

    addition = temp2->digit + wasGreater;
    // if there will be a number carried over
    if (addition > 9)
    {
      addition = addition % 10;
      wasGreater = 1;
    }
    else
    {
      wasGreater = 0;
    }

    sum->length++;

    temp->digit = addition;
    temp->next = NULL;
    //printf("digit: %d and i %d\n", temp->digit, i);
    if (i < difference - 1)
    {
      temp->next = (Node*)malloc(sizeof(Node));
      temp = temp->next;
      // move through longer list
      temp2 = temp2->next;
    }
  }

  // if there is a new column being created by the addition
  // being over 10 in the final column
  if (wasGreater == 1)
  {
    // checks for failed memory allocation
    if (temp->next == NULL)
    {
      destroyListyInt(sum);
      return NULL;
    }

    sum->length++;

    temp->digit = 1;
    temp->next = NULL;
  }
  else
  {
    temp = NULL;
  }

  // returns struct with the sum of p and q
  //printf("length: %d\n", sum->length);
  return sum;
}

ListyInt *destroyListyInt(ListyInt *listy)
{
  // temporary node to cycle through list
  Node *temp;

  // if listy is NULL, end function
  if (listy == NULL)
  {
    return NULL;
  }

  temp = listy->head;

  // while there is another node
  while (temp->next != NULL)
  {
    // set temp to the next node
    temp = temp->next;
    // free the current node
    free(listy->head);
    // make head also equal the next node
    listy->head = temp;
  }
  // free the last node
  free(listy->head);
  // free the struct
  free(listy);

  return NULL;
}

ListyInt *stringToListyInt(char *str)
{
  // temporary node to cycle through list
  Node *temp;
  ListyInt *list;
  int len;

  // check for NULL pointers and failed memory allocation
  if (str == NULL)
  {
    return NULL;
  }

  // allocate memory for a struct
  list = (ListyInt*)malloc(sizeof(ListyInt));
  if (list == NULL)
  {
    return NULL;
  }

  // if the char array is empty
  if (str[0] == '\0')
  {
    // allocate memory for the node
    list->head = (Node*)malloc(sizeof(Node));
    // checks for failed memory allocation
    if (list->head == NULL)
    {
      free(list);
      return NULL;
    }
    // set the digit to 0
    list->head->digit = 0;
    // increase length of list
    list->length = 1;
    list->head->next = NULL;
    return list;
  }

  len = strlen(str);

  list->head = (Node*)malloc(sizeof(Node));
  temp = list->head;
  temp->next = NULL;

  // reverse the string
  char *dummy = (char*)malloc(len * sizeof(char));
  for (int i = 0; i < len; i++)
  {
    dummy[i] = str[len-1-i];
  }

  str = dummy;
  free(dummy);

  for (int i = 0; i < len; i++)
  {
    // checks for failed memory allocation
    if (temp == NULL)
    {
      list = destroyListyInt(list);
      return list;
    }
    // set digits in list
    temp->digit = (int)str[i] - 48;
    list->length++;
    // link next node
    temp->next = (Node*)malloc(sizeof(Node));
    if (i < len - 1)
    {
      temp = temp->next;
    }
  }
  temp->next = NULL;
  return list;
}

char *listyIntToString(ListyInt *listy)
{
  char *str;
  // temporary node to cycle through list
  Node *temp;

  // check for NULL struct
  if (listy == NULL)
  {
    return NULL;
  }

  // allocate memory for the length of the list plue room for a null sentinel
  str = (char*)malloc(sizeof(char) * (listy->length + 1));
  // checks for failed memory allocation
  if (str == NULL)
  {
    return NULL;
  }

  temp = listy->head;

  // loop through the list and put each integer into the char array
  for (int i = 1; i < listy->length; i++)
  {
    str[i] = (char)temp->digit;
    temp = temp->next;
  }

  // end with null sentinel
  str[listy->length] = '\0';

  return str;
}

ListyInt *uintToListyInt(unsigned int n)
{
  char str[11];
  // allocate memory for a struct
  ListyInt *list = (ListyInt*)malloc(sizeof(ListyInt));

  // convert unsigned int to string
  sprintf(str, "%u", n);

  // convert string to listyInt
  list = stringToListyInt(str);

  if (list == NULL)
  {
    return NULL;
  }

  return list;
}

unsigned int *listyIntToUint(ListyInt *listy)
{
  unsigned int *pointUint;
  char *str;

  // check for NULL struct
  if (listy == NULL)
  {
    return NULL;
  }

  pointUint = (unsigned int*)malloc(sizeof(unsigned int));

  // checks for failed memory allocation
  if (pointUint == NULL)
  {
    return NULL;
  }

  // the list is too big to be an unsigned int
  if (listy->length > 10)
  {
    return NULL;
  }
  else if (listy->length == 10)
  {
    return NULL;
  }

  // convert list to string
  strcpy(str, listyIntToString(listy));

  // convert string to unsigned int
  *pointUint = strtoul (str, NULL, 10);

  return pointUint;
}

void plusPlus(ListyInt *listy)
{
  // create a listyInt that just contains a one
  ListyInt *addOne;
  addOne->head->digit = 1;
  addOne->head->next = NULL;
  addOne->length = 1;
  // add one to the given list
  listyAdd(listy, addOne);
}

ListyInt *fib(unsigned int n)
{
  ListyInt *list;
  ListyInt *list2;
  ListyInt *tempList;
  unsigned int *pointUint;

  // set for 0
  list->head->digit = 1;
  list->head->next = NULL;
  list->length = 1;

  // set for 1
  list2->head->digit = 1;
  list2->head->next = NULL;
  list2->length = 1;

  // base cases
  if (n == 0 || n == 1)
  {
    return list;
  }

  for (int i = 2; i < n; i++)
  {
    tempList = list;
    list = listyAdd(list, list2);
    destroyListyInt(list2);
    list2 = list;
  }

  return list;
}

double difficultyRating(void)
{
  return 4.0;
}

double hoursSpent(void)
{
  return 17.0;
}
