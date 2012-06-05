#include <ruby.h>

VALUE initialize_m(VALUE, VALUE);
VALUE count_m(VALUE);
VALUE count_cpu_m(VALUE);

void Init_popcount(void) {
  VALUE cPopCount = rb_define_class("PopCount", rb_cObject);
  rb_define_private_method(cPopCount, "initialize", initialize_m, 1);
  rb_define_method(cPopCount, "count", count_m, 0);
  rb_define_method(cPopCount, "count_cpu", count_cpu_m, 0);
}

VALUE initialize_m(VALUE self, VALUE value) {
  rb_ivar_set(self, rb_intern("@value"), value);
}

VALUE count_m(VALUE self) {
  VALUE value = rb_ivar_get(self, rb_intern("@value"));
  int count = 0;
  int i;
  unsigned char *p;
  static const char array[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

  p = RSTRING_PTR(value);
  for (i = 0; i < RSTRING_LEN(value); i++) {
    count += array[*p++];
  }

  return INT2FIX(count);
}

VALUE count_cpu_m(VALUE self) {
  VALUE value = rb_ivar_get(self, rb_intern("@value"));
  int count = 0;
  int i;
  long long *p;

  p = (long long *)RSTRING_PTR(value);
  for (i = 0; i < RSTRING_LEN(value); i += sizeof(long long)) {
    count += __builtin_popcountll(*p++);
  }

  return INT2FIX(count);
}
