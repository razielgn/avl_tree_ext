#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "avl_tree.h"

struct avl_tree_node
{
  avl_tree_elem elem;
  avl_tree right;
  avl_tree left;
  long height;
  bool present;
};

#define max(X, Y) ((X) > (Y) ? (X) : (Y))

avl_tree avl_tree_single_rot_left( avl_tree t2 )
{
  avl_tree_pos t1;

  t1 = t2->left;
  t2->left = t1->right;
  t1->right = t2;

  t2->height = max( avl_tree_height( t2->left ), avl_tree_height( t2->right ) ) + 1;
  t1->height = max( avl_tree_height( t1->left ), avl_tree_height( t2 ) ) + 1;

  return t1;
}

avl_tree avl_tree_single_rot_right( avl_tree t1 )
{
  avl_tree_pos t2;

  t2 = t1->right;
  t1->right = t2->left;
  t2->left = t1;

  t1->height = max( avl_tree_height( t1->left ), avl_tree_height( t1->right ) ) + 1;
  t2->height = max( avl_tree_height( t2->left ), avl_tree_height( t1 ) ) + 1;

  return t2;
}

avl_tree avl_tree_double_rot_left( avl_tree t3 )
{
  t3->left = avl_tree_single_rot_right( t3->left );

  return avl_tree_single_rot_left( t3 );
}

avl_tree avl_tree_double_rot_right( avl_tree t3 )
{
  t3->right = avl_tree_single_rot_left( t3->right );

  return avl_tree_single_rot_right( t3 );
}

long avl_tree_height( avl_tree_pos pos )
{
  if( pos )
    return pos->height;

  return -1;
}

avl_tree avl_tree_insert( avl_tree t, avl_tree_elem elem, avl_tree_comparator cmp )
{
  long left_height, right_height;

  if( t == NULL )
  {
    t = malloc( sizeof( struct avl_tree_node ) );
    assert( t );

    t->elem = elem;
    t->right = t->left = NULL;
    t->present = true;
    t->height = 0;
  }
  else
  {
    switch( cmp( elem, t->elem ) )
    {
      case -1:
        t->left = avl_tree_insert( t->left, elem, cmp );

        left_height = avl_tree_height( t->left );
        right_height = avl_tree_height( t->right );

        if( left_height - right_height == 2 )
        {
          if( elem < avl_tree_retrieve( t->left ) )
            t = avl_tree_single_rot_left( t );
          else
            t = avl_tree_double_rot_left( t );
        }
        break;
      case 0: break;
      case 1:
        t->right = avl_tree_insert( t->right, elem, cmp );

        left_height = avl_tree_height( t->left );
        right_height = avl_tree_height( t->right );

        if( right_height - left_height == 2 )
        {
          if( elem > avl_tree_retrieve( t->right ) )
            t = avl_tree_single_rot_right( t );
          else
            t = avl_tree_double_rot_right( t );
        }
        break;
    }
  }

  t->height = max( avl_tree_height( t->left ), avl_tree_height( t->right ) ) + 1;

  return t;
}

avl_tree avl_tree_remove( avl_tree t, avl_tree_elem elem, avl_tree_comparator cmp )
{
  if( t )
  {
    switch( cmp( elem, t->elem ) )
    {
      case -1:
        t->left = avl_tree_remove( t->left, elem, cmp );
        break;
      case 0:
        t->present = false;
        break;
      case 1:
        t->right = avl_tree_remove( t->right, elem, cmp );
        break;
    }
  }

  return t;
}

avl_tree_pos avl_tree_min( avl_tree t )
{
  if( !t ) return NULL;

  if( t->left && t->left->present )
    return avl_tree_min( t->left );
  else if( t->present )
    return t;
  else
    return NULL;
}

avl_tree_pos avl_tree_max( avl_tree t )
{
  if( !t ) return NULL;

  if( t->right && t->right->present )
    return avl_tree_max( t->right );
  else if( t->present )
    return t;
  else
    return NULL;
}

long avl_tree_size( avl_tree t )
{
  long step = 0;

  if( t == NULL ) return 0;

  if( t->present )
    step = 1;

  return step + avl_tree_size( t->left ) + avl_tree_size( t->right );
}

avl_tree_elem avl_tree_retrieve( avl_tree_pos pos )
{
  assert( pos );

  return pos->elem;
}

void avl_tree_free( avl_tree t )
{
  if( !t ) return;

  avl_tree_free( t->left );
  avl_tree_free( t->right );
  free( t );
}

void avl_tree_scan_inorder( avl_tree t, void ( *f )( avl_tree_elem ) )
{
  if( !t ) return;

  avl_tree_scan_inorder( t->left, f );
  if( t->present )
    f( t->elem );
  avl_tree_scan_inorder( t->right, f );
}

void avl_tree_scan_preorder( avl_tree t, void ( *f )( avl_tree_elem ) )
{
  if(!t ) return;

  if( t->present )
    f( t->elem );
  avl_tree_scan_preorder( t->left, f );
  avl_tree_scan_preorder( t->right, f );
}

void avl_tree_scan_postorder( avl_tree t, void ( *f )( avl_tree_elem ) )
{
  if(!t ) return;

  avl_tree_scan_preorder( t->left, f );
  avl_tree_scan_preorder( t->right, f );
  if( t->present )
    f( t->elem );
}

avl_tree_pos avl_tree_find( avl_tree t, avl_tree_elem elem, avl_tree_comparator cmp )
{
  if( t && t->present )
  {
    switch( cmp( elem, t->elem ) )
    {
      case -1:
        return avl_tree_find( t->left, elem, cmp );
      case 0:
        return t;
      case 1:
        return avl_tree_find( t->right, elem, cmp );
    }
  }

  return NULL;
}
