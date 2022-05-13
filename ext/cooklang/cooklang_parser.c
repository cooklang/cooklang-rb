#include <cooklang.h>

VALUE cCooklangParser;

int parse_metadata(Recipe * recipe, VALUE * metadata)
{
	ListIterator meta_data_iterator;
	Metadata *current_meta_data;

	meta_data_iterator = createIterator(recipe->metaData);
	current_meta_data = nextElement(&meta_data_iterator);

	while (current_meta_data != NULL) {
		rb_hash_aset(metadata,
					 rb_str_new2(current_meta_data->identifier),
					 rb_str_new2(current_meta_data->content));
		current_meta_data = nextElement(&meta_data_iterator);
	}

	// TODO error handling
	return 0;
}

VALUE parse(VALUE self, VALUE text)
{
	VALUE recipe_klass;
	VALUE r_recipe;
	VALUE metadata;
    VALUE r_text = StringValue(text);
    char *recipe_string = RSTRING_PTR(r_text);

    Recipe *recipe = parseRecipeString(recipe_string);

	recipe_klass = rb_const_get_at(rb_mCooklang, rb_intern("Recipe"));
	r_recipe = rb_class_new_instance(0, NULL, recipe_klass);
	metadata = rb_iv_get(r_recipe, "@metadata");

	parse_metadata(recipe, metadata);

    return r_recipe;
}

void Init_cooklang_parser(void)
{
#undef rb_intern
#if 0
    rb_mCooklang = rb_define_module("Cooklang");
#endif

    cCooklangParser = rb_define_class_under(rb_mCooklang, "Parser", rb_cObject);

    // rb_require("cooklang/recipe");

    rb_define_method(cCooklangParser, "parse", parse, 1);
}
