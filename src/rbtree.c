#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *tree = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));

  nil->color = RBTREE_BLACK;

  tree->root = nil;
  tree->nil = nil;

  return tree;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

  new_node->color = RBTREE_RED;
  new_node->key = key;
  new_node->left = new_node->right = t->nil;

  node_t *current = t->root;
  node_t *temp = t->nil;

  while (current != t->nil)
  {
    temp = current;
    if (new_node->key < current->key)
    {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  new_node->parent = temp;

  if (temp == t->nil)
  {
    t->root = new_node;
  }
  else if (key < temp->key)
  {
    temp->left = new_node;
  } else {
    temp->right = new_node;
  }
  
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *current = t ->root;

  while (current != t->nil)
  {
    if (key == current->key)
    {
  return t->root;
}
    else if (key > current->key)
    {
      current = current -> right;
    }
    else 
    {
      current = current -> left;
    }
  }
  
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  t->root = t->nil;

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void print_rbtree(const rbtree *t, const node_t *node) {
  if (node == t->nil)
  {
    printf("%s", "nil\n");
  }
  else{
    printf("%d \n", node->key);
    printf("%s", "left: ");
    print_rbtree(t, node->left);
    printf("%s", "right: ");
    print_rbtree(t ,node->right);
  }
}