#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "rotation.h"

node* rot_right(node *tree)
{
    if (tree != NULL && tree->r_node != NULL && tree->r_node->r_node != NULL)
    {
        node *tmp = tree;
        tree = tree->r_node;
        tree->l_node = tmp;
        tmp->r_node = NULL;
    }
    return tree;
}
 
node* rot_left(node *tree)
{
    if (tree != NULL && tree->l_node != NULL && tree->l_node->l_node != NULL)
    {
        printf("rot_left\n");
        node *tmp = tree;
        tree = tree->l_node;
        tree->r_node = tmp;
        tmp->l_node = NULL;
    }
    return tree;
}

node* rot_left_right(node *tree)
{
    if (tree != NULL && tree->l_node != NULL && tree->l_node->r_node != NULL)
    {
        node *old_root = tree;

        node *branch_left = tree->l_node->r_node->l_node;
        node *branch_right = tree->l_node->r_node->r_node;
        //1.
        printf("%d -> %d\n", tree->l_node->r_node->value, tree->value);
        tree = tree->l_node->r_node;

        printf("%d -> %d\n", old_root->l_node->value, tree->l_node->value);
        tree->l_node = old_root->l_node;

        printf("%d -> %d\n", old_root->value, tree->r_node->value);
        tree->r_node = old_root;

        //2.
        tree->l_node->r_node = branch_left;

        //3. 
        old_root->l_node = branch_right;
    }
    return tree;
}

int get_balance(const node *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    int balance = abs(get_balance(tree->r_node) - get_balance(tree->l_node));
    printf("%d -> %d\n", tree->value, balance);
    return balance + 1;
}
/*
void make_balance(node *tree, node* par)
{
    if (tree == NULL)
        return tree;
    make_balance(tree->r_node, tree);
    if (get_balance(tree) <= 1)
    {
        return tree;
    }
    else if (get_depth(tree) == 2) {
        par->r_node = rot_right(tree);
        return tree;
    }
    make_balance(tree->l_node, tree);
    if (get_balance(tree) <= 1)
    {
        return tree;
    }
    else if (get_depth(tree) == 2) {
        par->l_node = rot_left(tree);
        return tree;
    }
    if (get_balance(tree) <= 1)
        return tree;

}
*/
