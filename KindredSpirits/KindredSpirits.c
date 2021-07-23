// Kortney Menefee
// COP 3502, Fall
// ko580767

#include "KindredSpirits.h"
#include <stdio.h>
#include <stdlib.h>

int isReflection(node *a, node *b)
{
  // default is set to true
  int reflection = 1;

  // check for empty tree or node
  if (a == NULL && b == NULL)
  {
    return reflection;
  }
  // check if one of the tree has a NULL node where the other does not
  else if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
  {
    reflection = 0;
    return reflection;
  }
  // if the nodes aren't equal, return 0;
  if (a->data != b->data)
  {
    reflection = 0;
    return reflection;
  }

  // check to see if there is a node to the left
  if (a->left != NULL)
  {
    // cycle through the left of one tree and the right of another
    reflection = isReflection(a->left, b->right);
    // if a difference is found, return 0
    if (reflection == 0)
    {
      return reflection;
    }
  }
  // check to see if there is a node to the right
  if (a->right != NULL)
  {
    // cycle trhough the right of one tree and the left of another
    reflection = isReflection(a->right, b->left);
    // if a difference is found, return 0
    if (reflection == 0)
    {
      return reflection;
    }
  }

  // if no difference is found
  return reflection;
}

// creates a new node for the makeReflection function
node *createNode(int data)
{
  node *n = calloc(1, sizeof(node));
  n->data = data;
  return n;
}

node *makeReflection(node *root)
{
  // if the tree is empty, return an empty tree
  if (root == NULL)
  {
    return root;
  }

  // create a new node, and a potential link for a node
  node *n = createNode(root->data);
  node *link;

  // check to see if there is a node to the left
  if (root->left != NULL)
  {
    // travel down that left node
    link = makeReflection(root->left);
    // link our reflected tree's current node to reflect the original tree's left node
    n->right = link;
  }

  // check to see if there is a node to the right
  if (root->right != NULL)
  {
    // travel down that right node
    link = makeReflection(root->right);
    // link our reflected tree's current node to reflect the original tree's right node
    n->left = link;
  }

  // return the new reflected node
  return n;
}

// count how many nodes there are
int preorderCount(node *n, int counter)
{
  // check to see if there is a node to the left
  if (n->left != NULL)
  {
    // travel down that left node
    counter = preorderCount(n->left, counter);
  }
  // check to see if there is a node to the right
  if (n->right != NULL)
  {
    // travel down that right node
    counter = preorderCount(n->right, counter);
  }

  // increment each time we return so we know how many nodes there are
  counter ++;

  return counter;
}

void preorderArray(node *n, int numOfNodes, int *counter, int *arrayPtr)
{
  // fill our pointer with the data of each node, moving along the pointer as necessary
  *(arrayPtr + *counter) = n->data;

  // increment counter
  *counter = *counter + 1;

  // check to see if there is a node to the left
  if (n->left != NULL)
  {
    // travel down that left node
    preorderArray(n->left, numOfNodes, counter, arrayPtr);
  }
  // check to see if there is a node to the right
  if (n->right != NULL)
  {
    // travel down that right node
    preorderArray(n->right, numOfNodes, counter, arrayPtr);
  }
}

int compare(node *a, node *b, int *arrayPtr, int *counter)
{
  // default is set to true
  int comparison = 1;

  // check to see if there is a node to the left
  if (b->left != NULL)
  {
    // travel down that left node
    comparison = compare(a, b->left, arrayPtr, counter);
    // if the comparison was false, return 0
    if (comparison == 0)
    {
      return comparison;
    }
  }
  // check to see if there is a node to the right
  if (b->right != NULL)
  {
    // travel down that right node
    comparison = compare(a, b->right, arrayPtr, counter);
    // if the comparison was false, return 0
    if (comparison == 0)
    {
      return comparison;
    }
  }

  // if the nodes don't match return 0
  if (b->data != *(arrayPtr + *counter))
  {
    comparison = 0;
    return comparison;
  }

  // increment our counter so we'll be using the correct integers in our comparisons
  *counter = *counter + 1;

  return comparison;
}

int kindredSpirits(node *a, node *b)
{
  // muber of nodes in our preorder functions
  int numOfNodes;
  // a pointer we'll need to compare trees
  int *arrayPtr = malloc(sizeof(int) * numOfNodes);
  // counters for helper functions
  int zero = 0;
  int *counter = &zero;
  int zero2 = 0;
  int *counter2 = &zero2;

  // check for empty tree
  if (a == NULL && b == NULL)
  {
    return 1;
  }
  // check to see if one of the trees is empty
  if (a == NULL || b == NULL)
  {
    return 0;
  }

  // find number of nodes in first preorder
  numOfNodes = preorderCount(a, 0);

  preorderArray(a, numOfNodes, counter, arrayPtr);

  // see if a's preorder = b's postorder
  if (compare(a, b, arrayPtr, counter2) == 1)
  {
    return 1;
  }

  // reset counters and arrayPtr
  zero = 0;
  zero2 = 0;

  preorderArray(b, numOfNodes, counter, arrayPtr);

  // find number of nodes in second preorder
  numOfNodes = preorderCount(b, 0);

  // see if b's preorder = a's postorder
  if (compare(b, a, arrayPtr, counter2) == 1)
  {
    return 1;
  }

  // if neither are true, return 0
  return 0;
}

double difficultyRating(void)
{
  return 2.0;
}

double hoursSpent(void)
{
  return 10.0;
}
