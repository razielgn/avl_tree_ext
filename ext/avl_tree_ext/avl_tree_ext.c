#include "ruby.h"
#include "avl_tree.h"

typedef struct {
  avl_tree root;
} avl_tree_r;

static int cmp( avl_tree_elem elem1, avl_tree_elem elem2 )
{
  VALUE hesit, value1, value2;
  ID method_id;

  value1 = ( VALUE )elem1;
  value2 = ( VALUE )elem2;

  method_id = rb_intern( "<=>" );

  hesit = rb_funcall( value1, method_id, 1, value2 );

  if( NIL_P( hesit ) )
  {
    rb_raise( rb_eTypeError, "can't compare object of class %s with object of class %s.", rb_obj_classname( value1 ), rb_obj_classname( value2 ) );
  }
  else
    return FIX2INT( hesit );
}

static void avl_tree_rdealloc( avl_tree_r* avl_tree )
{
  avl_tree_free( avl_tree->root );
  free( avl_tree );
}

static VALUE avl_tree_ralloc( VALUE klass )
{
  avl_tree_r *t = malloc( sizeof( avl_tree_r ) );
  t->root = NULL;

  return Data_Wrap_Struct( klass, NULL, avl_tree_rdealloc, t );
}

static VALUE avl_tree_rinsert( VALUE self, VALUE obj )
{
  avl_tree_r *t;
  avl_tree_elem elem = (avl_tree_elem *)obj;

  Data_Get_Struct( self, avl_tree_r, t );

  t->root = avl_tree_insert( t->root, elem, cmp );

  return obj;
}

static VALUE avl_tree_rremove( VALUE self, VALUE obj )
{
  avl_tree_r *t;
  avl_tree_elem elem = (avl_tree_elem *)obj;

  Data_Get_Struct( self, avl_tree_r, t );

  t->root = avl_tree_remove( t->root, elem, cmp );

  return obj;
}

static VALUE avl_tree_rsize( VALUE self )
{
  avl_tree_r *t;
  long size;

  Data_Get_Struct( self, avl_tree_r, t );

  size = avl_tree_size( t->root );
  return INT2FIX( size );
}

static VALUE avl_tree_rmin( VALUE self )
{
  avl_tree_r *t;
  avl_tree_pos node;

  Data_Get_Struct( self, avl_tree_r, t );

  node = avl_tree_min( t->root );

  if( node )
    return ( VALUE )( avl_tree_retrieve( node ) );
  else
    return Qnil;
}

static VALUE avl_tree_rmax( VALUE self )
{
  avl_tree_r *t;
  avl_tree_pos node;

  Data_Get_Struct( self, avl_tree_r, t );

  node = avl_tree_max( t->root );

  if( node )
    return ( VALUE )( avl_tree_retrieve( node ) );
  else
    return Qnil;
}

static avl_tree_pos avl_tree_rfind( VALUE self, VALUE obj )
{
  avl_tree_r *t;
  avl_tree_elem elem = (avl_tree_elem *)obj;

  Data_Get_Struct( self, avl_tree_r, t );

  return avl_tree_find( t->root, elem, cmp );
}

static inline void yielder( avl_tree_elem elem )
{
  rb_yield( ( VALUE )elem );
}

static VALUE avl_tree_rscan_inorder( VALUE self )
{
  avl_tree_r *t;

  rb_need_block();

  Data_Get_Struct( self, avl_tree_r, t );

  avl_tree_scan_inorder( t->root, yielder );

  return Qnil;
}

static VALUE avl_tree_rexists( VALUE self, VALUE obj )
{
  avl_tree_pos pos;

  pos = avl_tree_rfind( self, obj );

  return ( pos ? Qtrue : Qfalse );
}

void Init_avl_tree_ext()
{
  VALUE AVLTree;

  AVLTree = rb_define_class( "AVLTree", rb_cData );
  rb_include_module( AVLTree, rb_mEnumerable );

  rb_define_alloc_func( AVLTree, avl_tree_ralloc );

  rb_define_method( AVLTree, "insert", avl_tree_rinsert, 1 );
  rb_define_method( AVLTree, "remove", avl_tree_rremove, 1 );

  rb_define_method( AVLTree, "size", avl_tree_rsize, 0 );
  rb_define_alias( AVLTree, "length", "size" );
  rb_define_alias( AVLTree, "count",  "size" );

  rb_define_method( AVLTree, "min", avl_tree_rmin, 0 );
  rb_define_method( AVLTree, "max", avl_tree_rmax, 0 );

  rb_define_method( AVLTree, "include?", avl_tree_rexists, 1 );

  rb_define_method( AVLTree, "each", avl_tree_rscan_inorder, 0 );

}
