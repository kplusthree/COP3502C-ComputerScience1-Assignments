// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "LonelyPartyArray.h"
#include <stdio.h>
#include <stdlib.h>

 LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
 {
   int capacity;
   // allocate memory for struct
   LonelyPartyArray *party = (LonelyPartyArray*)malloc(sizeof(LonelyPartyArray));

   if (party == NULL)
   {
     return NULL;
   }

   // return NULL if variables passed to function is less than or equal to zero
   if (num_fragments < 1 || fragment_length < 1)
   {
     return NULL;
   }

   // intitialize values
   party->num_fragments = num_fragments;
   party->fragment_length = fragment_length;
   party->num_active_fragments = 0;
   party->size = 0;
   capacity = num_fragments * fragment_length;

   // allocate memory for array of pointers
   party->fragments = malloc(sizeof(int*) * (num_fragments));
   for (int i = 0; i < num_fragments; i++)
   {
     // intitialize each fragment to NULL
     party->fragments[i] = NULL;
   }

   // allocate memory for the size array
   party->fragment_sizes = malloc(sizeof(int) * (num_fragments));
   for (int i = 0; i < num_fragments; i++)
   {
     // intitialize each size to zero
     party->fragment_sizes[i] = 0;
   }

   printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",
   capacity, num_fragments);

   return party; // return struct
 }

 LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
 {
  if (party == NULL)
  {
    return NULL;
  }

  // free memory for the size array
  free(party->fragment_sizes);
  for (int i = 0; i < party->num_fragments; i++)
  {
    // free memory for each array of cells
    free(party->fragments[i]);
  }
  // free memory for array of pointers
  free(party->fragments);
  // free memory for struct
  free(party);

  printf("-> The LonelyPartyArray has returned to the void.\n");

  return NULL;
 }

int set(LonelyPartyArray *party, int index, int key)
{
  int fragment, offset, high, low;

  // if pointer is NULL, return failure
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in set().\n");
    return LPA_FAILURE;
  }

  // if the index is outside the array, return failure
  if (index < 0 || index >= (party->num_fragments * party->fragment_length))
  {
    // figure out where the key would have gone had it not been outside the arrays
    fragment = index / party->fragment_length;
    offset = index % party->fragment_length;

    printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n",
    index, fragment, offset);
    return LPA_FAILURE;
  }

  // figure out where in the arrays the key goes
  fragment = index / party->fragment_length;
  offset = index % party->fragment_length;

  // if the fragment the key belongs to hasn't been used yet, allocate memory for it
  if (party->fragments[fragment] == NULL)
  {
    party->fragments[fragment] = malloc(sizeof(int) * party->fragment_length);

    // Set each cell to unused
    for (int i = 0; i < party->fragment_length; i++)
    {
      party->fragments[fragment][i] = UNUSED;
    }

    // add this fragment to the number of active fragments
    party->num_active_fragments ++;
    // calculate the indices used in this fragment
    low = party->fragment_length * fragment;
    high = low + party->fragment_length - 1;

    printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",
    fragment, party->fragment_length, low, high);
  }

  // if this cell hasn't been used yet, update the sizes
  if (party->fragments[fragment][offset] == UNUSED)
  {
    // add this cell to the number of overall active cells
    party->size ++;
    // add this cell to the number of active cells in the fragment
    party->fragment_sizes[fragment] ++;
  }

  // put the key in the designated cell
  party->fragments[fragment][offset] = key;

  return LPA_SUCCESS;
}

int get(LonelyPartyArray *party, int index)
{
  int fragment, offset;

  // if pointer is NULL, return failure
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }

  // if the index is outside the array, return failure
  if (index < 0 || index >= (party->num_fragments * party->fragment_length))
  {
    // figure out where the key would have gone had it not been outside the arrays
    fragment = index / party->fragment_length;
    offset = index % party->fragment_length;

    printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n",
    index, fragment, offset);
    return LPA_FAILURE;
  }

  // figure out where in the arrays the the index belongs
  fragment = index / party->fragment_length;
  offset = index % party->fragment_length;

  // if index refers to a cell in an unallocated fragment, return UNUSED
  if (party->fragments[fragment] == NULL)
  {
    return UNUSED;
  }

  // return what's stored in the cell
  return party->fragments[fragment][offset];
}

int empty(LonelyPartyArray *party, int index, int fragment , int offset)
{
  // empty the cell
  party->fragments[fragment][offset] = UNUSED;
  // remove this cell from the number of overall active cells
  party->size --;
  // remove this cell from the number of active cells in the fragment
  party->fragment_sizes[fragment] --;

  // if deleting the cell left the whole fragment empty:
  if (party->fragment_sizes[fragment] == 0)
  {
    // free the memory
    free(party->fragments[fragment]);
    // set it to NULL
    party->fragments[fragment] = NULL;
    // and remove this fragment from the number of active fragments
    party->num_active_fragments --;
    // calculate the indices used in this fragment

    return 1;
  }
  return 0;
}

int delete(LonelyPartyArray *party, int index)
{
  int fragment, offset, high, low, didDeallocate;

  // if pointer is NULL, return failure
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }

  // if the index is outside the array, return failure
  if (index < 0 || index >= (party->num_fragments * party->fragment_length))
  {
    // figure out where the key would have gone had it not been outside the arrays
    fragment = index / party->fragment_length;
    offset = index % party->fragment_length;

    printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n",
    index, fragment, offset);
    return LPA_FAILURE;
  }

  // figure out where the key would have gone had it not been outside the arrays
  fragment = index / party->fragment_length;
  offset = index % party->fragment_length;

  // if index refers to a cell in an unallocated fragment, return failure
  if (party->fragments[fragment] == NULL || party->fragments[fragment][offset] == UNUSED)
  {
    return LPA_FAILURE;
  }

  didDeallocate = empty(party, index, fragment, offset);

  // if the fragment got deallocated, print
  if (didDeallocate == 1)
  {
    low = party->fragment_length * fragment;
    high = low + party->fragment_length - 1;

    printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n",
    fragment, party->fragment_length, low, high);
  }
  return LPA_SUCCESS;
}

int containsKey(LonelyPartyArray *party, int key)
{
  // if party is NULL or the struct is empty, return 0
  if (party == NULL || party->size == 0)
  {
    return 0;
  }

  for (int i = 0; i < party->num_fragments; i++)
  {
    // check if there's anything in the current fragment
    if (party->fragment_sizes[i] == 0)
    {
      continue;
    }
    for (int j = 0; j < party->fragment_length; j++)
    {
      // if the cell's contents matches the key, return 1
      if (party->fragments[i][j] == key)
      {
        return 1;
      }
    }
  }
  // if no match is found, return 0
  return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
  int fragment, offset;

  // if party is NULL or the struct is empty, return 0
  if (party == NULL || party->size == 0)
  {
    return 0;
  }
  // if the index is outside the array, return 0
  if (index < 0 || index >= (party->num_fragments * party->fragment_length))
  {
    return 0;
  }

  // figure out what cell to check
  fragment = index / party->fragment_length;
  offset = index % party->fragment_length;

  // if the fragment is uninitiated or the cell has no value, return 0
  if (party->fragments[fragment] == NULL || party->fragments[fragment][offset] == UNUSED)
  {
    return 0;
  }
  // if the cell has a value, return 1
  return 1;
}

int printIfValid(LonelyPartyArray *party, int index)
{
  // check if the cell has anything in it
  int hasBeenSet = isSet(party, index);
  int value;

  if (hasBeenSet == 0)
  {
    return LPA_FAILURE;
  }

  value = get(party, index);

  // print value stored at index
  printf("%d\n", value);

  return LPA_SUCCESS;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int capacity, index, fragment, offset;

  // if party is NULL, return
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
    return party;
  }

  for (int i = 0; i < party->num_fragments; i++)
  {
    // check if there's anything in the current fragment
    if (party->fragment_sizes[i] == 0)
    {
      continue;
    }
    for (int j = 0; j < party->fragment_length; j++)
    {
      // if the fragment becomes empty from deletion or if the cell is UNUSED, continue
      if (party->fragments[i] == NULL || party->fragments[i][j] == UNUSED)
      {
        continue;
      }

      // if the cell's contents are not UNUSED, delete that cell
      index = party->fragment_length * i + j;
      // figure out where the key would have gone had it not been outside the arrays
      fragment = index / party->fragment_length;
      offset = index % party->fragment_length;
      empty(party, index, fragment, offset);
    }
  }

  capacity = getCapacity(party);
  // print the successful reset and return party
  printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n",
  capacity, party->num_fragments);
  return party;
}

int getSize(LonelyPartyArray *party)
{
  // if party is NULL, return -1
  if (party == NULL)
  {
    return -1;
  }
  // return the size
  return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
  // if party is NULL, return -1
  if (party == NULL)
  {
    return -1;
  }
  // return the capacity
  return party->num_fragments * party->fragment_length;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
  // if party is NULL, return -1
  if (party == NULL)
  {
    return -1;
  }
  // return the possible number of cells with current fragments
  return party->num_active_fragments * party->fragment_length;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  int capacity = getCapacity(party);

  // if party is NULL, return 0
  if (party == NULL)
  {
    return 0;
  }
  // return a typecasted total of bytes
  return ((long long unsigned int)capacity * sizeof(int));
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  // initilize variables
  long long unsigned int lpaPointer, lpaStruct, fragArray, fragSizeArray, activeFrags, total;
  int allocatedCells = getAllocatedCellCount(party);

  // if party is NULL, return 0
  if (party == NULL)
  {
    return 0;
  }

  // number of bytes taken up by the LPA pointer itself
  lpaPointer = (long long unsigned int)sizeof(LonelyPartyArray*);
  // number of bytes taken up by the LPA struct
  lpaStruct = (long long unsigned int)sizeof(LonelyPartyArray);
  // number of bytes taken up by the fragments array
  fragArray = (long long unsigned int)sizeof(int*) * party->num_fragments;
  // number of bytes taken up by the fragments_sizes array
  fragSizeArray = (long long unsigned int)sizeof(int) * party->num_fragments;
  // number of bytes taken up by the active fragments
  activeFrags = (long long unsigned int)sizeof(int) * allocatedCells;

  // calculate total
  total = lpaPointer + lpaStruct + fragArray + fragSizeArray + activeFrags;

  return total;
}

double difficultyRating(void)
{
  return 3.0;
}

double hoursSpent(void)
{
  return 20.0;
}
