// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "Orcheeseo.h"
#include <stdio.h>
#include <string.h>

void inorder_recursive(node *root)
{
  if (root == NULL)
  return;
  inorder_recursive(root->left);
  printf("%d ", root->data);
  inorder_recursive(root->right);
}


  int ready_for_market(pumpkin *patch, double min_size)
{
   int numRipe;

   if (patch == NULL)
   return;

   if (ripeness == 0 && size >= min_size)
   {
     numRipe++;
   }

   ready_for_market(patch->left, double min_size);
   ready_for_market(patch->right, double min_size);

   return numRipe;
}
