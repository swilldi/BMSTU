#include "export_data.h"
#include "avl_tree.h"

#define DOT_DEPENDENS_FMT "%s -> %s;\n"
#define NULL_DOT_DEPENDENS_FMT "%s -> null%d;\n"

#define DOT_DEPENDENS_FMT_AVL "\"%s (%d)\" -> \"%s (%d)\";\n"
#define NULL_DOT_DEPENDENS_FMT_AVL "\"%s (%d)\" -> null%d;\n"

void print_null_node(tree_node *node, FILE *dot_file);
void print_node(tree_node *node, void *dot_file);

void print_null_avl_node(avl_tree_node *node, FILE *dot_file);
void export_avl_tree_to_dot(void *tree, FILE *dot_file);

void export_tree_to_dot(void *tree, FILE *dot_file)
{
    tree_node *node = (tree_node*)tree;
    fprintf(dot_file, "digraph {\n");
    tree_apple_pre(node, print_node, dot_file);
    fprintf(dot_file, "}\n");
}

void print_node(tree_node *node, void *dot_file)
{
    tree_node *left = tree_left_child(node), *right = tree_right_child(node);
    
    // Левый потомок
    if (left)
        fprintf(dot_file, "  "DOT_DEPENDENS_FMT, (char *)tree_value(node), (char *)tree_value(left));
    else
        print_null_node(node, dot_file);

    // Правый потомок
    if (right)
        fprintf(dot_file, "  "DOT_DEPENDENS_FMT, (char *)tree_value(node), (char *)tree_value(right));
    else
        print_null_node(node, dot_file);   
}

void print_null_node(tree_node *node, FILE *dot_file)
{
    static int null_count = 0;

    fprintf(dot_file, "  null%d [label=\"\", shape=none, width=0, height=0 ];\n", null_count);
    fprintf(dot_file, "  "NULL_DOT_DEPENDENS_FMT, (char *)tree_value(node), null_count);
    
    null_count += 1;
}

void print_avl_node(avl_tree_node *node, void *dot_file)
{
    avl_tree_node *left = avl_tree_left_child(node), *right = avl_tree_right_child(node);
    
    // Левый потомок
    if (left)
        fprintf(dot_file, "  "DOT_DEPENDENS_FMT_AVL, (char *)avl_tree_value(node), (int)avl_tree_height(node), (char *)avl_tree_value(left), (int)avl_tree_height(left));
    else
        print_null_avl_node(node, dot_file);

    // Правый потомок
    if (right)
        fprintf(dot_file, "  "DOT_DEPENDENS_FMT_AVL, (char *)avl_tree_value(node), (int)avl_tree_height(node), (char *)avl_tree_value(right), (int)avl_tree_height(right));
    else
        print_null_avl_node(node, dot_file);
}

void print_null_avl_node(avl_tree_node *node, FILE *dot_file)
{
    static int null_count = 0;

    fprintf(dot_file, "  null%d [label=\"\", shape=none, width=0, height=0 ];\n", null_count);
    fprintf(dot_file, "  "NULL_DOT_DEPENDENS_FMT_AVL, (char *)avl_tree_value(node), (int)avl_tree_height(node), null_count);
    
    null_count += 1;
}

void export_avl_tree_to_dot(void *tree, FILE *dot_file)
{
    avl_tree_node *node = (avl_tree_node*)tree;
    fprintf(dot_file, "digraph {\n");
    avl_tree_apple_pre(node, print_avl_node, dot_file);
    fprintf(dot_file, "}\n");
}
