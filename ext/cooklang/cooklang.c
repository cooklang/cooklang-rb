#include "cooklang.h"

VALUE rb_mCooklang;

void
Init_cooklang(void)
{
  rb_mCooklang = rb_define_module("Cooklang");
  char *recipeString = "add @bacon";
  Recipe *parsedRecipe = parseRecipeString(recipeString);
}
