/*****************************************************************************
*                                                                            *
*  ex-1.c                                                                    *
*  ======                                                                    *
*                                                                            *
*  Description: Illustrates using a binary tree (see Chapter 9).             *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"
#include "traverse.h"

/*****************************************************************************
*                                                                            *
*  ---------------------------- print_preorder ----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_preorder(const BiTreeNode *node) {

/*****************************************************************************
*                                                                            *
*  Display the binary tree rooted at the specified node in preorder.         *
*                                                                            *
*****************************************************************************/

if (!bitree_is_eob(node)) {

   fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));

   if (!bitree_is_eob(bitree_left(node)))
      print_preorder(bitree_left(node));

   if (!bitree_is_eob(bitree_right(node)))
      print_preorder(bitree_right(node));

}

return;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- print_inorder ----------------------------  *
*                                                                            *
*****************************************************************************/

static void print_inorder(const BiTreeNode *node) {

/*****************************************************************************
*                                                                            *
*  Display the binary tree rooted at the specified node in inorder.          *
*                                                                            *
*****************************************************************************/

if (!bitree_is_eob(node)) {

   if (!bitree_is_eob(bitree_left(node)))
      print_inorder(bitree_left(node));

   fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));

   if (!bitree_is_eob(bitree_right(node)))
      print_inorder(bitree_right(node));

}

return;

}

/*****************************************************************************
*                                                                            *
*  ---------------------------- print_postorder ---------------------------  *
*                                                                            *
*****************************************************************************/

static void print_postorder(const BiTreeNode *node) {

/*****************************************************************************
*                                                                            *
*  Display the binary tree rooted at the specified node in postorder.        *
*                                                                            *
*****************************************************************************/

if (!bitree_is_eob(node)) {

   if (!bitree_is_eob(bitree_left(node)))
      print_postorder(bitree_left(node));

   if (!bitree_is_eob(bitree_right(node)))
      print_postorder(bitree_right(node));

   fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));

}

return;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ insert_int ------------------------------  *
*                                                                            *
*****************************************************************************/

static int insert_int(BiTree *tree, int i) {

BiTreeNode         *node,
                   *prev;

int                direction,
                   *data;

/*****************************************************************************
*                                                                            *
*  Insert i assuming a binary tree organized as a binary search tree.        *
*                                                                            *
*****************************************************************************/

node = tree->root;
direction = 0;

while (!bitree_is_eob(node)) {

   prev = node;

   if (i == *(int *)bitree_data(node)) {

      return -1;

      }

   else if (i < *(int *)bitree_data(node)) {

      node = bitree_left(node);
      direction = 1;

      }

   else {

      node = bitree_right(node);
      direction = 2;

   }

}

if ((data = (int *)malloc(sizeof(int))) == NULL)
   return -1;

*data = i;

if (direction == 0)
   return bitree_ins_left(tree, NULL, data);

if (direction == 1)
   return bitree_ins_left(tree, prev, data);

if (direction == 2)
   return bitree_ins_right(tree, prev, data);

return -1;

}

/*****************************************************************************
*                                                                            *
*  ------------------------------ search_int ------------------------------  *
*                                                                            *
*****************************************************************************/

static BiTreeNode *search_int(BiTree *tree, int i) {

BiTreeNode         *node;

/*****************************************************************************
*                                                                            *
*  Look up i assuming a binary tree organized as a binary search tree.       *
*                                                                            *
*****************************************************************************/

node = bitree_root(tree);

while (!bitree_is_eob(node)) {

   if (i == *(int *)bitree_data(node)) {

      return node;

      }

   else if (i < *(int *)bitree_data(node)) {

      node = bitree_left(node);

      }

   else {

      node = bitree_right(node);

   }

}

return NULL;

}

/*****************************************************************************
*                                                                            *
*  --------------------------------- main ---------------------------------  *
*                                                                            *
*****************************************************************************/

int main(int argc, char **argv) {

BiTree             tree;
BiTreeNode         *node;

int                i;

/*****************************************************************************
*                                                                            *
*  Initialize the binary tree.                                               *
*                                                                            *
*****************************************************************************/

bitree_init(&tree, free);

/*****************************************************************************
*                                                                            *
*  Perform some binary tree operations.                                      *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Inserting some nodes\n");

if (insert_int(&tree, 20) != 0)
   return 1;

if (insert_int(&tree, 10) != 0)
   return 1;

if (insert_int(&tree, 30) != 0)
   return 1;

if (insert_int(&tree, 15) != 0)
   return 1;

if (insert_int(&tree, 25) != 0)
   return 1;

if (insert_int(&tree, 70) != 0)
   return 1;

if (insert_int(&tree, 80) != 0)
   return 1;

if (insert_int(&tree, 23) != 0)
   return 1;

if (insert_int(&tree, 26) != 0)
   return 1;

if (insert_int(&tree, 5) != 0)
   return 1;

fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
fprintf(stdout, "(Preorder traversal)\n");
print_preorder(bitree_root(&tree));

i = 30;

if ((node = search_int(&tree, i)) == NULL) {

   fprintf(stdout, "Could not find %03d\n", i);

   }

else {

   fprintf(stdout, "Found %03d...Removing the left tree below it\n", i);
   bitree_rem_left(&tree, node);
   fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
   fprintf(stdout, "(Preorder traversal)\n");
   print_preorder(bitree_root(&tree));

}

i = 99;

if ((node = search_int(&tree, i)) == NULL) {

   fprintf(stdout, "Could not find %03d\n", i);

   }

else {

   fprintf(stdout, "Found %03d...Removing the right tree below it\n", i);
   bitree_rem_right(&tree, node);
   fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
   fprintf(stdout, "(Preorder traversal)\n");
   print_preorder(bitree_root(&tree));

}

i = 20;

if ((node = search_int(&tree, i)) == NULL) {

   fprintf(stdout, "Could not find %03d\n", i);

   }

else {

   fprintf(stdout, "Found %03d...Removing the right tree below it\n", i);
   bitree_rem_right(&tree, node);
   fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
   fprintf(stdout, "(Preorder traversal)\n");
   print_preorder(bitree_root(&tree));

}

i = bitree_is_leaf(bitree_root(&tree));
fprintf(stdout, "Testing bitree_is_leaf...Value=%d (0=OK)\n", i);
i = bitree_is_leaf(bitree_left((bitree_root(&tree))));
fprintf(stdout, "Testing bitree_is_leaf...Value=%d (0=OK)\n", i);
i = bitree_is_leaf(bitree_left(bitree_left((bitree_root(&tree)))));
fprintf(stdout, "Testing bitree_is_leaf...Value=%d (1=OK)\n", i);
i = bitree_is_leaf(bitree_right(bitree_left((bitree_root(&tree)))));
fprintf(stdout, "Testing bitree_is_leaf...Value=%d (1=OK)\n", i);

fprintf(stdout, "Inserting some nodes\n");

if (insert_int(&tree, 55) != 0)
   return 1;

if (insert_int(&tree, 44) != 0)
   return 1;

if (insert_int(&tree, 77) != 0)
   return 1;

if (insert_int(&tree, 11) != 0)
   return 1;

fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
fprintf(stdout, "(Preorder traversal)\n");
print_preorder(bitree_root(&tree));
fprintf(stdout, "(Inorder traversal)\n");
print_inorder(bitree_root(&tree));
fprintf(stdout, "(Postorder traversal)\n");
print_postorder(bitree_root(&tree));

/*****************************************************************************
*                                                                            *
*  Destroy the binary tree.                                                  *
*                                                                            *
*****************************************************************************/

fprintf(stdout, "Destroying the tree\n");
bitree_destroy(&tree);

return 0;

}
