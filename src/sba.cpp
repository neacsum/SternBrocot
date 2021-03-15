/*
  Rational approximations using Stern-Brocot tree.
  (c) Mircea Neacsu 2016

  Nodes of the Stern-Brocot tree (https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree)
  offer the best possible rational (p/q) approximation for any real number in
  the sense that any other rational approximation p'/q' of the same precission
  has p' >= p and q' >= q.

  Finding small rational approximations can be important for programs designed
  to run on small microprocessors where floating point support may be missing
  or too expensive. For instance floating point value of pi can be replaced
  by the fraction 355/113 that is accurate to 6 decimal places (see
  https://en.wikipedia.org/wiki/Approximations_of_%CF%80)

  The sba utility finds the Stern-Brocot approximation of a number with
  any number of decimal places. 
  
  Usage:
    sba <number> <decimals>


*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

//Uncomment next line to see a printout of the first few levels of the
//Stern-Brocot tree

//#define SHOW_TREE

// A node in the Stern-Brocot tree
struct sbnode {
  int p, q;
  struct sbnode *left, *right, *parent;
  sbnode (sbnode *parent_) 
  {
    p = q = 0; 
    left = right = 0; 
    parent = parent_;
  }
  ~sbnode () 
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

//Tree root
sbnode *root;

//Return node to the left
sbnode *previous (sbnode *node)
{
  assert (node->parent);
  while (node->parent->right && node->parent->right != node)
    node = node->parent;
  return node->parent;
}

//Return node to the right
sbnode *next (sbnode *node)
{
  assert (node->parent);
  while (node->parent->left && node->parent->left != node)
    node = node->parent;
  return node->parent;
}

//Add left and right children to a node
void grow (sbnode *node)
{
#ifdef SHOW_TREE
  printf ("Children of [%d/%d] ", node->p, node->q);
#endif
  //create left child
  sbnode *l = new sbnode (node);

  node->left = l;
  if (node->p == 1)
  {
    //node on left tree boundary = 1/(n+1)
    l->p = 1;
    l->q = node->q + 1;
  }
  else
  {
    //node is mediant of parent and preceding node
    sbnode *prec = previous (node);
    l->p = node->p + prec->p;
    l->q = node->q + prec->q;
  }
#ifdef SHOW_TREE
  printf ("left [%d/%d]", l->p, l->q);
#endif

  //create right child
  sbnode *r = new sbnode (node);

  node->right = r;
  if (node->q == 1)
  {
    //node on right tree boundary = (n+1)/1
    r->q = 1;
    r->p = node->p + 1;
  }
  else
  {
    //node is mediant of parent and succeeding node
    sbnode *succ = next (node);
    r->p = node->p + succ->p;
    r->q = node->q + succ->q;
  }
#ifdef SHOW_TREE
  printf (" right [%d/%d]\n", r->p, r->q);
#endif
}


int main (int argc, char **argv)
{

#ifdef SHOW_TREE
  root = new sbnode (nullptr);
  root->p = root->q = 1;
  grow (root);

  printf ("\n");

  //Grow a few tree levels

  grow (root->left);
  grow (root->right);
  printf ("\n");

  grow (root->left->left);
  grow (root->left->right);
  grow (root->right->left);
  grow (root->right->right);
  printf ("\n");

  grow (root->left->left->left);
  grow (root->left->left->right);
  grow (root->left->right->left);
  grow (root->left->right->right);
  grow (root->right->left->left);
  grow (root->right->left->right);
  grow (root->right->right->left);
  grow (root->right->right->right);
  printf ("\n");
  delete root;
#endif

  if (argc < 3)
  {
    printf ("Usage: sba <number> <decimals>\n");
    exit (1);
  }
  double x = atof (argv[1]);
  int n = atoi (argv[2]);

  double eps = pow (10., -n);

  printf ("Finding approximation of %.10lf with %d decimals\n\n", x, n);

  //Initialize root node and its children
  root = new sbnode (nullptr);
  root->p = root->q = 1;
  grow (root);

  //starting point is tree root
  sbnode *crt = root;
  double approx = 1.;

  while (fabs (x - approx) > eps)
  {
    printf ("Current approximation %d/%d = %.7lf (err=%.2le)\n", crt->p, crt->q, approx, x-approx);
    
    //move left or right
    if (x > approx)
      crt = crt->right;
    else
      crt = crt->left;

    //grow children of current node
    grow (crt);

    //recalculate approximation
    approx = (double)crt->p / (double)crt->q;
  }
  printf ("\nFound fraction %d/%d = %.*lf\n", crt->p, crt->q, n+1, approx);
  printf ("Error= %.2le\n", x - approx);

  //cleanup
  delete root;
  exit (0);
}