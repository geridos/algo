#pragma once

typedef struct node node;

node *rot_right(node *tree);
node *rot_left(node *tree);
int get_balance(const node *tree);
node* rot_left_right(node *tree);
