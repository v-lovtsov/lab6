#ifndef _TREE_H_
#define _TREE_H_

#include "utils.h"
#define NODE struct Node

NODE
{
    int key;
    NODE *left;
    NODE *right;
    int height;
};

int getHeight(NODE *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(NODE *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

NODE *newNode(int key)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

NODE *rightRotate(NODE *node)
{
    NODE *pivot = node->left;
    NODE *pivotr = pivot->right;

    pivot->right = node;
    node->left = pivotr;

    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    pivot->height = getMax(getHeight(pivot->left), getHeight(pivot->right)) + 1;

    return pivot;
}

NODE *leftRotate(NODE *node)
{
    NODE *pivot = node->right;
    NODE *pivotl = pivot->left;

    pivot->left = node;
    node->right = pivotl;

    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    pivot->height = getMax(getHeight(pivot->left), getHeight(pivot->right)) + 1;

    return pivot;
}

NODE *insert(NODE *node, int key, int *rotations, char **rotation_types, int *rotation_count)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key, rotations, rotation_types, rotation_count);
    else if (key > node->key)
        node->right = insert(node->right, key, rotations, rotation_types, rotation_count);
    else
        return node;

    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
    {
        if (*rotation_count < 100)
        {
            rotation_types[*rotation_count] = "SR";
            (*rotation_count)++;
        }
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key)
    {
        if (*rotation_count < 100)
        {
            rotation_types[*rotation_count] = "SL";
            (*rotation_count)++;
        }
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        if (*rotation_count < 100)
        {
            rotation_types[*rotation_count] = "BR";
            (*rotation_count)++;
        }
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        if (*rotation_count < 100)
        {
            rotation_types[*rotation_count] = "BL";
            (*rotation_count)++;
        }
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void freeTree(NODE *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

#endif
