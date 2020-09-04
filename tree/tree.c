#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node *r_node;
    struct node *l_node;
} node;

node* insert_node(node *tree, int new_value)
{
    if (tree == NULL)
    {
        tree = (node*)malloc(sizeof(node));
        if (!tree)
        {
            fprintf(stderr, "malloc failed during the node creating\n");
            return NULL;
        }
        tree->value = new_value;
        
        tree->r_node = NULL;
        tree->l_node = NULL;
        //printf("tree root_node = %p - %d \n", tree, tree->value);
        return tree;
    }
    if (new_value <= tree->value)
    {
        //printf("rec on the r_node : %d >= %d\n", tree->value, new_value);
        node *n = insert_node(tree->r_node, new_value);
        tree->r_node = n;
    }
    else
    {
        //printf("rec on the l_node : %d < %d\n", tree->value, new_value);
        node *n = insert_node(tree->l_node, new_value);
        tree->l_node = n;
    }

}

int max(int a, int b)
{
    if (a < b)
        return b;
    return a;
}

int process_depth(const node *tree)
{
    if (tree != NULL)
        return max(process_depth(tree->r_node) + 1, process_depth(tree->l_node) + 1);
}



int number_of_node(const node *tree)
{
    if (tree != NULL) {
        //printf("%s %d\n", "processing the node : ", tree->value);
        return number_of_node(tree->r_node) + number_of_node(tree->l_node) + 1;
    }
    return 0;
}

typedef struct point
{
    int has_left_sun;
    int has_right_sun;
    int has_brother;
    char *val;
    int x, y;
} point;

typedef struct array
{
    point **p;
} array;

static int point_index = 0;

void fill_mat(const node *tree, array *mat, int x, int y, int has_left_bro)
{
    if (tree != NULL)
    {
        point *p = malloc(sizeof(point));
        p->x = x;
        p->y = y;
        p->has_brother = has_left_bro;

        char *val = NULL;
        if (tree->l_node != NULL && tree->r_node == NULL)
            asprintf(&val, "%d\\", tree->value);
        else if (tree->r_node != NULL && tree->l_node == NULL)
            asprintf(&val, "/%d", tree->value);
        else if (tree->r_node != NULL && tree->l_node != NULL)
            asprintf(&val, "/%d\\", tree->value);
        else
            asprintf(&val, "|%d|", tree->value);

        p->val = val;

        mat->p[point_index++] = p;

        printf("mat[%d][%d] = %s\n", y, x, p->val);
        fill_mat(tree->r_node, mat, x - x / 8, y + 1, tree->l_node == NULL ? 0 : 1);
        fill_mat(tree->l_node, mat, x + (x / 8), y + 1, 0);
    }
}

//A weird printing
void print(const node *tree)
{
    int depth = process_depth(tree);
    int size = number_of_node(tree);
    int size_row = depth * depth;
    int size_mat = size_row * depth;

    array* mat = (array*)malloc(sizeof(array*));
    mat->p = (point**)malloc(sizeof(point*) * size);
    for (int i = 0; i < size; i++) {
        mat->p[i]= NULL;
    }

    fill_mat(tree, mat, size_row / 2, 0, 0);

    int found = 0;
    int draw_line = 0;
    for (int i = 0; i < depth; i++)
    {
        for (int j = 0; j < size_row; j++)
        {
            for (int k = 0; k < size; k++)
            {
                if (mat->p[k]->y == i && mat->p[k]->x == j)
                {
                    printf("%s", mat->p[k]->val);
                    draw_line = mat->p[k]->has_brother;
                    found = 1;
                    break;
                }
            }
            if (found != 1 && draw_line == 1)
            {
                printf("--");
            }
            else if (found != 1)
            {
                printf("  ");
            }
            found = 0;

        }
        printf("\n\n");
    }
}

int main(int argc, const char *argv[])
{
    node *root_node = (node*)malloc(sizeof(node));
    root_node->value = 20;
    root_node->r_node = NULL;
    root_node->l_node = NULL;

    printf("tree root_node = %p\n", root_node);
    insert_node(root_node, 21);
    insert_node(root_node, 19);
    insert_node(root_node, 41);
    insert_node(root_node, 30);
    insert_node(root_node, 50);
    insert_node(root_node, 18);
    insert_node(root_node, 17);
    insert_node(root_node, 16);
    insert_node(root_node, 35);
    insert_node(root_node, 33);
    insert_node(root_node, 34);
    insert_node(root_node, 10);
    insert_node(root_node, 1);
    insert_node(root_node, 2);
    insert_node(root_node, 14);
    int size = number_of_node(root_node);
    printf("size of the tree : %d\n", size);
    size = process_depth(root_node);
    printf("depth of the tree : %d\n", size);

    print(root_node);

    return 0;
}
