// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "Orcheeseo.h"
#include <stdio.h>
#include <string.h>

int returnThirtyTwo(void)
{
  return 32;
}

void printThirtyTwo(void)
{
  printf("32\n");
}

// print the art for the layer given
void printLayer(char first, char second, int layerLength)
{
  for(int i = 0; i < layerLength; i++)
  {
    printf("%c%c", first, second);
  }
  printf("\n");
}

void printSpaces(int numOfSpaces)
{
  if(numOfSpaces == 2)
  {
    printf(" ");
  }
  printf(" ");
}

// prints goldfish layers to screen and returns tallness of said layers
double printGoldfish(int numGoldfish)
{
  int numOfLayers = (numGoldfish / 3);

  // print a layer of crumbs if there's only one goldfish
  if(numGoldfish == 1)
  {
    // print two extra spaces for the crumb layer
    printSpaces(2);
    printLayer('.', ',', 3);
    return 0.1;
  }

  // if divisible by 3, print the standard layers of goldfish
  else if(numGoldfish % 3 == 0)
  {
    for(int i = 0; i < numOfLayers; i++)
    {
      // print an extra space for the standard layers
      printSpaces(1);
      printLayer('x', 'o', 4);
    }
    return numOfLayers * 0.25;
  }

  // if there's 2 goldfish left over, print one impoverished layer of goldfish
  // and then the standard layers of goldfish
  else if(numGoldfish % 3 == 2)
  {
    // print two extra spaces for the impoverished layer
    printSpaces(2);
    printLayer('x', 'o', 3);

    for(int i = 0; i < numOfLayers; i++)
    {
      // print an extra space for the standard layers
      printSpaces(1);
      printLayer('x', 'o', 4);
    }
    return (numOfLayers + 1) * 0.25;
  }

  // if there's 1 goldfish left over, print all the standard layers - 1,
  // and then print one extended layer of goldfish
  else
  {
    for(int i = 0; i < numOfLayers - 1; i++)
    {
      // print an extra space for the standard layers
      printSpaces(1);
      printLayer('x', 'o', 4);
    }

    printLayer('x', 'o', 5);

    return numOfLayers * 0.25;
  }
}

// prints whole orcheeseo to screen, determines edibility of snack
void printOrcheeseo(char *str)
{
  int length, counter = 0;
  int hasGoldfish = 0;
  double howTall = 0;
  char currentChar;

  // get length of string
  length = strlen(str);

  // check for an empty string
  if(length == 0)
  {
    printf("No cookie. :(\n");
    return;
  }

  for(int i = 0; i < length; i++)
  {
    // get current character
    currentChar = str[i];

    // print cookie layer
    if(currentChar == 'o')
    {
      // if this char ended a streak of goldfish, print th goldfigh first
      if(counter > 0)
      {
        howTall += printGoldfish(counter);
        counter = 0;
      }
      printLayer('=', '=', 5);
      howTall += 0.4;
    }

    // print creme layer
    else if(currentChar == 'c')
    {
      // if this char ended a streak of goldfish, print th goldfigh first
      if(counter > 0)
      {
        howTall += printGoldfish(counter);
        counter = 0;
      }
      // print an extra space for the creme layer
      printSpaces(1);
      printLayer('~', '~', 4);
      howTall += 0.25;
    }

    // count how many goldfish there are
    else if (currentChar == 'g')
    {
      hasGoldfish = 1;
      counter++;
    }

    // if the orcheeseo ends in goldfish
    else if(counter > 0)
    {
      howTall += printGoldfish(counter);
      counter = 0;
    }
  }

  // checks if the orcheeseo is messy
  if(str[0] != 'o' || str[length-1] != 'o')
  {
    printf("Too messy. :(\n");
  }

  // if bigger than 4.0 mm, the orcheeseo can't be comfortably eaten
  else if(howTall > 4.0)
  {
    printf("Oh nooooo! Too tall. :(\n");
  }

  // checks if there's been any goldfish
  else if(hasGoldfish == 0)
  {
    printf("Om nom nom! Oreo!\n");
  }

  else
  {
    printf("Om nom nom! Orcheeseo!\n");
  }
}

int main(int argc, char **argv)
{
  printOrcheeseo(argv[1]);

  return 0;
}

double difficultyRating(void)
{
  return 1.0;
}

double hoursSpent(void)
{
  return 6.0;
}
