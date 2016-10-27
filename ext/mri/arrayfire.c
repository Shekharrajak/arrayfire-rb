#include "ruby.h"

#include "arrayfire.h"

VALUE ArrayFire = Qnil;
VALUE Af_Array = Qnil;
VALUE Device = Qnil;
VALUE Blas = Qnil;
VALUE Lapack = Qnil;


struct myStruct
{
  int a;
  int b;
};

static void mystruct_free(void *s)
{
  xfree(s);
}



// prototypes
void Init_arrayfire();
VALUE method_test1(VALUE self);
VALUE method_arf_init(VALUE self, VALUE val);
VALUE arf_alloc(VALUE self);
void arf_free(int* data);


void Init_arrayfire() {
  ArrayFire = rb_define_module("ArrayFire");
  rb_define_method(ArrayFire, "test1", method_test1, 0);

  Af_Array = rb_define_class_under(ArrayFire, "Af_Array", rb_cObject);
  rb_define_alloc_func(Af_Array, arf_alloc);
  rb_define_method(Af_Array, "initialize", method_arf_init, 1);

  Device = rb_define_class_under(ArrayFire, "Device", rb_cObject);

  Blas = rb_define_class_under(ArrayFire, "BLAS", rb_cObject);

  Lapack = rb_define_class_under(ArrayFire, "LAPACK", rb_cObject);
}

VALUE method_test1(VALUE self) {
  // af_info();
  VALUE x;
  // char x[] = "hello";
  x = rb_str_new_cstr("Hello, world!");
  // int x = 10;
  return x;
}

VALUE method_arf_init(VALUE self, VALUE val)
{
  int* data;
  /* unwrap */
  Data_Get_Struct(self, int, data);

  *data = NUM2INT(val);

  return self;
}

VALUE arf_alloc(VALUE self)
{
  /* allocate */
  int* data = malloc(sizeof(int));

  /* wrap */
  return Data_Wrap_Struct(self, NULL, arf_free, data);
}

void arf_free(int* data)
{
  free(data);
}