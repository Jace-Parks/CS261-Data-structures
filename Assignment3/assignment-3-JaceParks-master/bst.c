/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Jace Parks
 * Email: parkjace@oregonstate.edu
 */

#include <stdlib.h>
#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* new_bst = malloc(sizeof(struct bst*));
  new_bst->root = NULL;
  return new_bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should free up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST. This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  freenodes(bst->root);
  return;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  return nodesize(bst->root);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  if(bst->root == NULL){
    bst->root = malloc(sizeof(struct bst_node));
    bst->root->key = key;
    bst->root->value = value;
    bst->root->left = NULL;
    bst->root->right = NULL;
  }else{
    struct bst_node* tmp = bst->root;
    while(1){
      if(tmp->key < key){
        if(tmp->right == NULL){
          tmp->right = malloc(sizeof(struct bst_node));
          tmp->right->key = key;
          tmp->right->value = value;
          return;
        }else{
          tmp = tmp->right;
        }
      }else if(tmp->key > key){
        if(tmp->left == NULL){
          tmp->left = malloc(sizeof(struct bst_node));
          tmp->left->key = key;
          tmp->left->value = value;
          return;
        }else{
          tmp = tmp->left;
        }
      }else{
        return;
      }
    }
  }
  return;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  return noderemove(bst->root,key);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  return getnode(bst->root,key);

}


// new functions


int nodesize(struct bst_node* node){
  int count = 1;
    if(node == NULL){
      return 0;
    }
    if(node->left != NULL){
      count = nodesize(node->left) + count;
    }
    if(node->right != NULL){
      count = nodesize(node->right) + count;
    }
    return count;
}

void nodeinsert(struct bst_node* bst,int key,void* value){
  if(bst == NULL){
    struct bst_node* new = malloc(sizeof(struct bst_node*));
    new->key = key;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    bst = new;
    return;
  }else if(bst != NULL){
  if(bst->left != NULL && key < bst->key){
    nodeinsert(bst->left,key,value);
  }else if(bst->right != NULL && key > bst->key){
    nodeinsert(bst->right,key,value);
  }

  if(bst->left == NULL && key < bst->key){
    struct bst_node* new = malloc(sizeof(struct bst_node*));
    new->key = key;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    bst->left = new;
    return;
  }else if(bst->right == NULL && key > bst->key){
    struct bst_node* new = malloc(sizeof(struct bst_node*));
    new->key = key;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    bst->left = new;
    return;
  }
}
  return;
}

void freenodes(struct bst_node* node){
  if(node == NULL){
    return;
  }
  if(node->left != NULL){
    freenodes(node->left);
  }
  if(node->right != NULL){
    freenodes(node->right);
  }
  if(node->left == NULL && node->right == NULL){
    free(node);
  }
  return;
}

void noderemove(struct bst_node* bst,int key){
  if(bst == NULL){
    return NULL;
  }else if(bst->key == key) {
    struct bst_node* buffer;
    struct bst_node* previous;
    struct bst_node* children;
    buffer = bst->right;
    if(buffer->left == NULL){
      children = bst->right->right;
      bst->right->left = NULL;
      bst->right->right = NULL;
      freenodes(bst->right);
      buffer->left = children;
      bst->right = buffer;
    }else{
    while(buffer->left != NULL){
      previous = buffer;
      buffer = buffer->left;
    }
    bst->key = buffer->key;
    bst->value = buffer->value;
    children = buffer->right;
    previous->left = children;
    buffer->left = NULL;
    buffer->right = NULL;
    freenodes(buffer);
    }
  }else{
  if(bst->right->key == key && bst->right != NULL){
    //remove case right
    if(bst->right->right == NULL && bst->right->left == NULL){
      freenodes(bst->right);
      bst->right == NULL;
    }else if(bst->right->right == NULL && bst->right->left != NULL ){
      struct bst_node* buffer = bst->right->left;
      bst->right->left = NULL;
      freenodes(bst->right);
      bst->right = buffer;
    }else if(bst->right->left == NULL && bst->right->right != NULL ){
      struct bst_node* buffer = bst->right->right;
      bst->right->right = NULL;
      freenodes(bst->right);
      bst->right = buffer;
    }else if(bst->right->right != NULL && bst->right->right != NULL){
      struct bst_node* buffer;
      struct bst_node* previous;
      struct bst_node* children;
      buffer = bst->right->right;
      if(buffer->left == NULL){
        children = bst->right->left;
        bst->right->left = NULL;
        bst->right->right = NULL;
        freenodes(bst->left);
        buffer->left = children;
        bst->left = buffer;
      }else{
      while(buffer->left != NULL){
        previous = buffer;
        buffer = buffer->left;
      }
      bst->right->key = buffer->key;
      bst->right->value = buffer->value;
      children = buffer->right;
      previous->left = children;
      buffer->left = NULL;
      buffer->right = NULL;
      freenodes(buffer);
      }
    }
  }else if(bst->left->key == key && bst->left != NULL){
    //remove case left
    if(bst->left->right == NULL && bst->left->left == NULL){
      freenodes(bst->left);
      bst->left == NULL;
    }else if(bst->left->right == NULL && bst->left->left != NULL ){
      struct bst_node* buffer = bst->left->left;
      bst->left->left = NULL;
      freenodes(bst->left);
      bst->left = buffer;
    }else if(bst->left->right != NULL && bst->left->left == NULL ){
      struct bst_node* buffer = bst->left->right;
      bst->left->right = NULL;
      freenodes(bst->left);
      bst->left = buffer;
    }else if(bst->left->right != NULL && bst->left->left != NULL){
      struct bst_node* buffer;
      struct bst_node* previous;
      struct bst_node* children;
      buffer = bst->left->right;
      if(buffer->left == NULL){
        children = bst->left->left;
        bst->left->left = NULL;
        bst->left->right = NULL;
        freenodes(bst->left);
        buffer->left = children;
        bst->left = buffer;
      }else{
      while(buffer->left != NULL){
        previous = buffer;
        buffer = buffer->left;
      }
      bst->left->key = buffer->key;
      bst->left->value = buffer->value;
      children = buffer->right;
      previous->left = children;
      buffer->left = NULL;
      buffer->right = NULL;
      freenodes(buffer);
      }
    }
  }else{
    if(bst->left != NULL && key < bst->key){
      noderemove(bst->left,key);
    }else if(bst->right != NULL && key > bst->key){
      noderemove(bst->right,key);
    }else{
      return NULL;
    }
  }
  }
}

void* getnode(struct bst_node* bst,int key){
  if(bst == NULL){
    return NULL;
  }
  if(bst->key == key){
    return bst->value;
  }else{
    if(bst->left != NULL && key < bst->key){
      getnode(bst->left,key);
    }else if(bst->right != NULL && key > bst->key){
      getnode(bst->right,key);
    }else{
      return NULL;
    }
  }
}
