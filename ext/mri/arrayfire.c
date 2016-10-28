#include "ruby.h"

#include "arrayfire.h"

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Device = Qnil;
VALUE Blas = Qnil;
VALUE Lapack = Qnil;

typedef struct AF_STRUCT
{
  size_t dimension;     // Method of storage (csc, dense, etc).
  size_t array;
}afstruct;

// prototypes
void Init_arrayfire();
VALUE method_test1(VALUE self);
// VALUE method_arf_init(VALUE self, VALUE val);
VALUE method_arf_init(int argc, VALUE* argv, VALUE self);
VALUE arf_alloc(VALUE self);
void arf_free(afstruct* af);
static VALUE dimension(VALUE self);
static VALUE array(VALUE self);


void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");
  rb_define_method(ArrayFire, "test1", method_test1, 0);

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", method_arf_init, -1);
  rb_define_method(Af_Array, "dimension", dimension, 0);
  rb_define_method(Af_Array, "array", array, 0);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
}

VALUE method_test1(VALUE self) {
  VALUE x;
  x = rb_str_new_cstr("Hello, world!");
  return x;
}

VALUE method_arf_init(int argc, VALUE* argv, VALUE self)
{

  afstruct* afarray;
  Data_Get_Struct(self, afstruct, afarray);
  afarray->dimension = argv[0];
  afarray->array = argv[1];


  return self;
}

VALUE arf_alloc(VALUE self)
{
  /* allocate */
  // // int* data = malloc(sizeof(int));
  // LST_String * string = malloc(sizeof(LST_String));
  afstruct * af = malloc(sizeof(afstruct));
  /* wrap */
  return Data_Wrap_Struct(self, NULL, arf_free, af);
}

void arf_free(afstruct* af)
{
  free(af);
}

static VALUE dimension(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return af->dimension;
}

static VALUE array(VALUE self)
{
  afstruct * af;

  Data_Get_Struct(self, afstruct, af);

  return af->array;
}