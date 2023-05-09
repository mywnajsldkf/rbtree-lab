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
node_t *rbtree_insert_fixup(rbtree *t, node_t *new_node) {
  while (new_node->parent->color == RBTREE_RED)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      // new_node의 삼촌노드 색상을 확인한다.
      node_t *temp = new_node->parent->parent->right;
      // case1) recoloring case
      if (temp->color == RBTREE_RED)
      {
        // recoloring
        new_node->parent->color = RBTREE_BLACK;
        temp->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else {
      if (new_node == new_node->parent->right)
      {
        new_node = new_node->parent;
        left_rotate(t, new_node);
      }
      new_node->parent->color = RBTREE_BLACK;
      new_node->parent->parent->color = RBTREE_RED;
      right_rotate(t, new_node->parent->parent);  
      }
    }
    // 반대쪽에 있는 경우
    else
    {
      node_t *temp = new_node->parent->parent->left;
      if (temp->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        temp->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      else {
      if (new_node == new_node->parent->left)
      {
        new_node = new_node->parent;
        right_rotate(t, new_node);
      }
      new_node->parent->color = RBTREE_BLACK;
      new_node->parent->parent->color = RBTREE_RED;
      left_rotate(t, new_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return new_node;
}

// 왼쪽으로 회전하는 경우
void *left_rotate(rbtree *t, node_t *new_node) {
  node_t *temp = new_node->right;
  new_node->right = temp->left;

  if (temp->left != t->nil)
  {
    temp->left->parent = new_node;
  }
  temp->parent = new_node->parent;

  if (new_node->parent == t->nil)
  {
    t->root = temp;
  }
  else if (new_node == new_node->parent->left)
  {
    new_node->parent->left = temp;
  }
  else
  {
    new_node->parent->right = temp;
  }
    temp->left = new_node;
  new_node->parent = temp;
  }

// 오른쪽으로 회전하는 경우
void *right_rotate(rbtree *t, node_t *new_node) {
  node_t *temp = new_node->left;
  new_node->left = temp->right;

  if (temp->right != t->nil)
  {
    temp->right->parent = new_node;
  }
  temp->parent = new_node->parent;
  
  if (new_node->parent == t->nil)
  {
    t->root = temp;
  }
  else if (new_node == new_node->parent->right)
  {
    new_node->parent->right = temp;
  }
  else
  {
    new_node->parent->left = temp;
  }
  temp->right = new_node;
  new_node->parent = temp;  
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *current = t ->root;

  // 현재 노드가 nil노드가 아닐 때까지
  while (current != t->nil)
  {
    if (key == current->key)
    {
      return current;
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

// 가장 왼쪽으로 이동한다.
node_t *rbtree_min(const rbtree *t) {
  node_t *current = t->root;
  
  while (current->left != t->nil)
  {
    current = current->left;
    // printf("now: %d\n", current->key);
  }
  return current;
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