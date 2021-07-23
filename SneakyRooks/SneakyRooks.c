// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "SneakyRooks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
 {
   // create 2 arrays to compare rook positions
   int *checkRows = calloc(boardSize + 1, sizeof(int));
   int *checkCols = calloc(boardSize + 1, sizeof(int));

   // temp rook to access row and column
   Coordinate rook;
   // a pointer to our rook so we can pass it to parseCoordinateString
   Coordinate *rookPtr;
   // initilize ro 0
   rook.col = 0;
 	 rook.row = 0;
   // Pointer pointing to rook
   rookPtr = &rook;

   for (int i = 0; i < numRooks; i ++)
   {
     // find row and column values
     parseCoordinateString(rookStrings[i], rookPtr);
     // add one to the corresponding row and column that the current rook is associated with
     checkRows[rook.row] ++;
     checkCols[rook.col] ++;

     // if the index is ever greater than 1, than we know there is another rook in that row or column
     if (checkRows[rook.row] > 1 || checkCols[rook.col] > 1)
     {
       // if there's a rook that can attack a rook, we free our arrays and return 0
       free(checkRows);
       free(checkCols);
       return 0;
     }
   }
   // free arrays
   free(checkRows);
   free(checkCols);
   // if no rooks share a row or column, they are all safe, return 1
   return 1;
 }

 int toDigit(char c)
 {
   // subtract by the beginning value and add 1 since this set has no 0 value
   return c - 'a' + 1;
 }

 // this function was based on Szumlanski's Base Conversion (Part 2 of 2) lecture notes
 // it has been modified to fit this assignment
 int toBase10(char *str, int length, int base)
 {
   int i, result = 0;

   // loop through the string
   for (i = 0; i < length; i++)
   {
     // multiply by base, in this case 26
     result *= base;
     // convert alphabet values into standard base 10 values
     result += toDigit(str[i]);
   }

   // return converted value
   return result;
 }

 void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
 {
   // declare variables
   int totalLength = strlen(rookString);
   int stringLength = 0;
   int rowValue, colValue;
   int base = 26;
   // so we can get the numbers for the row all by themselves
   char *rowCopy = malloc(sizeof(char) * totalLength);

   // loop through the whole string
   for (int i = 0; i < totalLength; i ++)
   {
     // if we're still looking at characters for the columns,
     if (isalpha(rookString[i]) != 0)
     {
       // increase stringLength and move to next character
       stringLength ++;
       continue;
     }

     // if we've gone passed the letters into numbers, copy the rest of the string
     strcpy(rowCopy, &rookString[i]);

     // turn that part of the string into an integer
     rowValue = atoi(rowCopy);
     // store that integer
     rookCoordinate->row = rowValue;
     // end loop
     break;
   }

   // give the string full of letters to a helper function to convert it into base 10
   colValue = toBase10(rookString, stringLength, base);
   // store the converted value
   rookCoordinate->col = colValue;

   free(rowCopy);
 }

double difficultyRating(void)
{
  return 2.0;
}

double hoursSpent(void)
{
  return 5.0;
}
