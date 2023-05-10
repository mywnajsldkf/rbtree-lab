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
  node_t *node = t->root;
  if (node != t->nil)
  {
    delete_node(t, node);
  }  
  
  free(t->nil);
  free(t);
}

void delete_node(rbtree *t, node_t *node) {
  if (node->left != t->nil)
  {
    delete_node(t, node->left);
  }
  if (node->right != t->nil)
  {
    delete_node(t, node->right);
  }  
  free(node);  
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->color = RBTREE_RED;
  new_node->key = key;
  new_node->left = t->nil;
  new_node->right = t->nil;

  node_t *uncle = t->nil;   
  node_t *current = t->root;

  while (current != t->nil)
  {
    uncle = current;
    if (key < current->key)
    {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  new_node->parent = uncle;

  if (uncle == t->nil)
  {
    t->root = new_node;
  }
  else if (key < uncle->key)
  {
    uncle->left = new_node;
  } else {
    uncle->right = new_node;
  }

  rbtree_insert_fixup(t, new_node);

  return new_node;
}

node_t *rbtree_insert_fixup(rbtree *t, node_t *new_node) {
  while (new_node->parent->color == RBTREE_RED)
  {
    if (new_node->parent == new_node->parent->parent->left)
    {
      node_t *temp = new_node->parent->parent->right;
     
      if (temp->color == RBTREE_RED)
      {
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

node_t *rbtree_min(const rbtree *t) {
  node_t *current = t->root;
  
  while (current->left != t->nil)
  {
    current = current->left;
  }
  return current;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *current = t->root;

  while (current->right != t->nil)
  {
    current = current->right;
  }  
  return current;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *temp = p;
  color_t temp_original_color = temp->color;
  node_t *x;

  if (p->left == t->nil)
  {
    x = p->right;
    rb_transplant(t, p, p->right);
  } 
  else if (p->right == t->nil)
  {
    x = p->left;
    rb_transplant(t, p, p->left);
  }
  else
  {
    temp = tree_minimum(t, p->right);
    temp_original_color = temp->color;
    x = temp->right;
    if (temp->parent == p)
    {
      x->parent = temp;
    }
    else
    {
      rb_transplant(t, temp, temp->right);
      temp->right = p->right;
      temp->right->parent = temp;
    }
    rb_transplant(t, p, temp);
    temp->left = p->left;
    temp->left->parent = temp;
    temp->color = p->color;
  }
  if (temp_original_color == RBTREE_BLACK)
  {
    rb_delete_fixup(t, x);
  }
  free(p);

  return 0;
}

node_t *tree_minimum(const rbtree *t, const node_t *p)
{
  while (p->left != t->nil)
  {
    p = p->left;
  }
  return p;
}

int rb_transplant(rbtree *t, node_t *u, node_t *v)
{
  if (u->parent == t->nil)
  {
    t->root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;

  return 0;
}

int rb_delete_fixup(rbtree *t, node_t *x)
{
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    if (x == x->parent->left)
    {
      w = x->parent->right;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->right->color == RBTREE_BLACK)
        {
          w->left->color == RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else
    {
      w = x->parent->left;
      if (w->color == RBTREE_RED)
      {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK)
      {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else
      {
        if (w->left->color == RBTREE_BLACK)
        {
          w->right->color == RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  inorder_array(t, &arr, t->root);
  return 0;
}

int inorder_array(const rbtree *t, key_t **arr, node_t *node) {
  if(node == t->nil)
    return 0;
  
  inorder_array(t, arr, node->left);
  **arr = node->key;
  *arr+=1;
  inorder_array(t, arr, node->right);
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