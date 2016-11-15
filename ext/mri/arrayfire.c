// #include "ruby.h"

#include "arrayfire.h"
#include <stdio.h>
#include <math.h>

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Device = Qnil;
VALUE Blas = Qnil;
VALUE Lapack = Qnil;


// prototypes
// void Init_arrayfire();
static VALUE test1(VALUE self);
// VALUE method_arf_init(VALUE self, VALUE val);
static VALUE arf_init(int argc, VALUE* argv, VALUE self);
static VALUE arf_alloc(VALUE klass);
static void arf_free(afstruct* af);
static VALUE ndims(VALUE self);
static VALUE dimension(VALUE self);
static VALUE array(VALUE self);
static void array2(VALUE self);
static VALUE get_info(VALUE self);

#define DEF_ELEMENTWISE_RUBY_ACCESSOR(oper, name)                 \
static VALUE arf_ew_##name(VALUE left_val, VALUE right_val) {  \
  return elementwise_op(arf::EW_##oper, left_val, right_val);  \
}

#define DECL_ELEMENTWISE_RUBY_ACCESSOR(name)    static VALUE arf_ew_##name(VALUE left_val, VALUE right_val);
DECL_ELEMENTWISE_RUBY_ACCESSOR(add)


static VALUE elementwise_op(arf::ewop_t op, VALUE left_val, VALUE right_val);
/*
 * Macro defines an element-wise accessor function for some operation.
 *
 * This is only responsible for the Ruby accessor! You still have to write the actual functions, obviously.
 */

static VALUE arf_eqeq(VALUE left_val, VALUE right_val);


void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");
  rb_define_method(ArrayFire, "test1", (METHOD)test1, 0);

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", (METHOD)arf_init, -1);
  rb_define_method(Af_Array, "ndims", (METHOD)ndims, 0);
  rb_define_method(Af_Array, "dimension", (METHOD)dimension, 0);
  rb_define_method(Af_Array, "array", (METHOD)array, 0);
  rb_define_method(Af_Array, "array2", (METHOD)array2, 0);
  rb_define_method(Af_Array, "+",(METHOD)arf_ew_add,1);
  rb_define_method(Af_Array, "==",(METHOD)arf_eqeq,1);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);
  rb_define_method(Device, "getInfo", (METHOD)get_info, 0);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
}

VALUE test1(VALUE self) {
  VALUE x;
  x = rb_str_new_cstr("Hello, world!");
  return x;
}

VALUE arf_init(int argc, VALUE* argv, VALUE self)
{
  afstruct* afarray;
  Data_Get_Struct(self, afstruct, afarray);
  afarray->ndims = argv[0];
  afarray->dimension = &argv[1];
  size_t *myGlobalArray;
  memcpy(&myGlobalArray, argv[1], argv[0] * sizeof(size_t) );
  // ALLOC_N(type, n)
  afarray->array = &argv[2];
  // for(size_t i = 0; i < argv[0]; i++){
  //   // count *= left->dimension[i];
  //   printf("%d\n",myGlobalArray[i]);
  // }

  arf::createArray(&argv[2], afarray);
  return self;
}

static VALUE arf_alloc(VALUE klass)
{
  /* allocate */
  afstruct* af = ALLOC(afstruct);
  /* wrap */
  return Data_Wrap_Struct(klass, NULL, arf_free, af);
}


static void arf_free(afstruct* af)
{
  free(af);
}

static VALUE ndims(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return af->ndims;
}

static VALUE dimension(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return *af->dimension;
}

static VALUE array(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return *af->array;
}

static void array2(VALUE self){
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);
  af_print_array(af->arr);
}

static VALUE get_info(VALUE self)
{
  VALUE x;
  af_info();
  arf::test();
  return x;
}


DEF_ELEMENTWISE_RUBY_ACCESSOR(ADD, add)

static VALUE elementwise_op(arf::ewop_t op, VALUE left_val, VALUE right_val) {

  afstruct* left;
  afstruct* right;
  afstruct* result = ALLOC(afstruct);

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);


  result->ndims = left->ndims;
  result->dimension = left->dimension;
  af_add( &result->arr, left->arr, right->arr, 0);

  return Data_Wrap_Struct(CLASS_OF(left_val), NULL, arf_free, result);
}

static VALUE arf_eqeq(VALUE left_val, VALUE right_val) {
  afstruct* left;
  afstruct* right;

  bool result = true;

  size_t i;
  size_t count = 1;

  Data_Get_Struct(left_val, afstruct, left);
  Data_Get_Struct(right_val, afstruct, right);

  printf("%d\n", left->ndims);

  // for(size_t i = 0; i < left->ndims; i++){
  //   count *= left->dimension[i];
  // }

  // for(size_t i = 0; i < count; i++){
  //   if(left->array[i]!= right->array[i]){
  //     return Qfalse;
  //   }
  // }

  return Qtrue;
}

// void arf_register_values(VALUE* values, size_t n) {
//   if (!gc_value_holder_struct)
//     __nm_initialize_value_container();
//   if (values) {
//     NM_GC_LL_NODE* to_insert = NULL;
//     if (allocated_pool->start) {
//       to_insert = allocated_pool->start;
//       allocated_pool->start = to_insert->next;
//     } else {
//       to_insert = NM_ALLOC_NONRUBY(NM_GC_LL_NODE);
//     }
//     to_insert->val = values;
//     to_insert->n = n;
//     to_insert->next = gc_value_holder_struct->start;
//     gc_value_holder_struct->start = to_insert;
//   }
// }