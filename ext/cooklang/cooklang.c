#include "cooklang.h"

VALUE rb_mCooklang;

void
Init_cooklang(void)
{
  rb_mCooklang = rb_define_module("Cooklang");
  Init_cooklang_parser();
}
