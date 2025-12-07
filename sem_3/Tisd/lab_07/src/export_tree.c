#include "export_tree.h"

#define DOT_DEPENDENS_FMT "%s -> %s;\n"
#define NULL_DOT_DEPENDENS_FMT "%s -> null%d;\n"

void export_tree_to_dot(void *tree, FILE *dot_file)
{
    tree_node *node = (tree_node*)tree;
    fprintf(dot_file, "digraph {\n");
    tree_apple_pre(node, print_node, dot_file);
    fprintf(dot_file, "}\n");
}

void print_node(tree_node *node, FILE *dot_file)
{
    tree_node *left = tree_left_child(node), *right = tree_right_child(node);
    
    // Левый потомок
    if (left)
        fprintf(dot_file, DOT_DEPENDENS_FMT, tree_value(node), tree_value(left));
    else
        print_null_node(node, dot_file);

    // Правый потомок
    if (right)
        fprintf(dot_file, DOT_DEPENDENS_FMT, tree_value(node), tree_value(right));
    else
        print_null_node(node, dot_file);   
}

void print_null_node(tree_node *node, FILE *dot_file)
{
    static null_count = 0;

    fprintf(dot_file, "null%d [label=\"\", shape=none, width=0, height=0 ];\n", null_count);
    fprintf(dot_file, NULL_DOT_DEPENDENS_FMT, tree_value(node), null_count);
    
    null_count += 1;
}
