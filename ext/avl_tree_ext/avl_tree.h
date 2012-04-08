#ifndef __avl_tree_H__
#define __avl_tree_H__

struct avl_tree_node;
typedef struct avl_tree_node* avl_tree;
typedef struct avl_tree_node* avl_tree_pos;
typedef void* avl_tree_elem;

typedef int ( *avl_tree_comparator )( avl_tree_elem, avl_tree_elem );

void avl_tree_free( avl_tree t );

avl_tree avl_tree_insert( avl_tree t, avl_tree_elem elem, avl_tree_comparator f );
avl_tree avl_tree_remove( avl_tree t, avl_tree_elem elem, avl_tree_comparator f );
avl_tree_pos avl_tree_find( avl_tree t, avl_tree_elem elem, avl_tree_comparator f );
avl_tree_elem avl_tree_retrieve( avl_tree_pos pos );

avl_tree_pos avl_tree_min( avl_tree t );
avl_tree_pos avl_tree_max( avl_tree t );

long avl_tree_size( avl_tree t );
long avl_tree_height( avl_tree_pos pos );

void avl_tree_scan_inorder( avl_tree t, void ( *f )( avl_tree_elem ) );
void avl_tree_scan_preorder( avl_tree t, void ( *f )( avl_tree_elem ) );
void avl_tree_scan_postorder( avl_tree t, void ( *f )( avl_tree_elem ) );

#endif
