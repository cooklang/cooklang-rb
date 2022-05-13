#include <cooklang.h>

VALUE cCooklangParser;

int parse_metadata(Recipe * c_recipe, VALUE * metadata)
{
	ListIterator meta_data_iterator;
	Metadata *current_meta_data;

	meta_data_iterator = createIterator(c_recipe->metaData);
	current_meta_data = nextElement(&meta_data_iterator);

	char *key;
	char *value;

	while (current_meta_data != NULL) {
		key = current_meta_data->identifier;
		value = current_meta_data->content;

		rb_hash_aset(metadata, rb_str_new2(key), rb_str_new2(value));

		current_meta_data = nextElement(&meta_data_iterator);
	}

	// TODO error handling
	return 1;
}

// VALUE parse_step(Step * step)
// {
// 	// loop through every direction
// 	int directionsTotal;

//     directionIterator = createIterator(step->directions);
//     currentDirection = nextElement(&directionIterator);
//     step = (*env)->NewObject(env, stepClass, stepConstructor);

//     directionsTotal = getLength(step->directions);
//     	if (directionsTotal > 0) {

//       	}
// }


int parse_steps(List * c_steps, VALUE * r_steps)
{
	VALUE step_klass;
	VALUE r_step;
	ListIterator step_iterator;
  	Step *current_step;

  	step_klass = rb_const_get_at(rb_mCooklang, rb_intern("Step"));
	r_step = rb_class_new_instance(0, NULL, step_klass);

  	step_iterator = createIterator(c_steps);
  	current_step = nextElement(&step_iterator);

  	while (current_step != NULL) {
    	// r_step = parse_step(current_step);

      	current_step = nextElement(&step_iterator);
    }

	// TODO error handling
	return 1;
}

VALUE parse(VALUE self, VALUE text)
{
	VALUE recipe_klass;
	VALUE r_recipe;
	VALUE r_metadata;
	VALUE r_steps;
    VALUE r_text = StringValue(text);

    char *recipe_string = RSTRING_PTR(r_text);

    Recipe *c_recipe = parseRecipeString(recipe_string);

	recipe_klass = rb_const_get_at(rb_mCooklang, rb_intern("Recipe"));
	r_recipe = rb_class_new_instance(0, NULL, recipe_klass);

	r_metadata = rb_iv_get(r_recipe, "@metadata");
	r_steps = rb_iv_get(r_recipe, "@steps");

	parse_metadata(c_recipe, r_metadata);
	parse_steps(c_recipe->stepList, r_steps);

    return r_recipe;
}

void Init_cooklang_parser(void)
{
#undef rb_intern
#if 0
    rb_mCooklang = rb_define_module("Cooklang");
#endif

    cCooklangParser = rb_define_class_under(rb_mCooklang, "Parser", rb_cObject);

    rb_define_method(cCooklangParser, "parse", parse, 1);
}
