#include <cooklang.h>

VALUE cCooklangParser;

VALUE parse_text(Direction * direction)
{
	VALUE text_klass;
	VALUE r_text;

	text_klass = rb_const_get_at(rb_mCooklang, rb_intern("TextItem"));
	r_text = rb_class_new_instance(0, NULL, text_klass);

	rb_iv_set(r_text, "@value", rb_str_new2(direction->value));

	return r_text;
}

VALUE parse_ingredient(Direction * direction)
{
	VALUE ingredient_klass;
	VALUE r_ingredient;

	ingredient_klass = rb_const_get_at(rb_mCooklang, rb_intern("Ingredient"));
	r_ingredient = rb_class_new_instance(0, NULL, ingredient_klass);

	rb_iv_set(r_ingredient, "@name", rb_str_new2(direction->value));

	if (direction->quantityString == NULL) {
	    if (direction->quantity != -1) {
	      rb_iv_set(r_ingredient, "@quantity", rb_float_new(direction->quantity));
	    } else {
	      rb_iv_set(r_ingredient, "@quantity", rb_str_new2(""));
	    }
	} else {
	    rb_iv_set(r_ingredient, "@quantity", rb_str_new2(direction->quantityString));
	}

	if (direction->unit == NULL) {
		rb_iv_set(r_ingredient, "@units", rb_str_new2(""));
	} else {
		rb_iv_set(r_ingredient, "@units", rb_str_new2(direction->unit));
	}

	return r_ingredient;
}

VALUE parse_timer(Direction * direction)
{
	VALUE timer_klass;
	VALUE r_timer;

	timer_klass = rb_const_get_at(rb_mCooklang, rb_intern("Timer"));
	r_timer = rb_class_new_instance(0, NULL, timer_klass);

	rb_iv_set(r_timer, "@name", rb_str_new2(direction->value));

	if (direction->quantityString == NULL) {
	    if (direction->quantity != -1) {
	      rb_iv_set(r_timer, "@quantity", rb_float_new(direction->quantity));
	    } else {
	      rb_iv_set(r_timer, "@quantity", rb_str_new2(""));
	    }
	} else {
	    rb_iv_set(r_timer, "@quantity", rb_str_new2(direction->quantityString));
	}

	if (direction->unit == NULL) {
		rb_iv_set(r_timer, "@units", rb_str_new2(""));
	} else {
		rb_iv_set(r_timer, "@units", rb_str_new2(direction->unit));
	}

	return r_timer;
}

VALUE parse_cookware(Direction * direction)
{
	VALUE cookware_klass;
	VALUE r_cookware;

	cookware_klass = rb_const_get_at(rb_mCooklang, rb_intern("Cookware"));
	r_cookware = rb_class_new_instance(0, NULL, cookware_klass);
	rb_iv_set(r_cookware, "@value", rb_str_new2("test"));

	rb_iv_set(r_cookware, "@name", rb_str_new2(direction->value));

	if (direction->quantityString == NULL) {
	    if (direction->quantity != -1) {
	      rb_iv_set(r_cookware, "@quantity", rb_float_new(direction->quantity));
	    } else {
	      rb_iv_set(r_cookware, "@quantity", rb_str_new2(""));
	    }
	} else {
	    rb_iv_set(r_cookware, "@quantity", rb_str_new2(direction->quantityString));
	}

	return r_cookware;
}


VALUE parse_direction(Direction * direction)
{
	// TODO make type constant, so we can use switch here
	// TEXT
    if (strcmp(direction->type, "text") == 0) {
    	return parse_text(direction);

    // INGREDIENT
    } else if (strcmp(direction->type, "ingredient") == 0) {
    	return parse_ingredient(direction);

    // TIMER
    } else if (strcmp(direction->type, "timer") == 0) {
    	return parse_timer(direction);

	// COOKWARE
    } else if (strcmp(direction->type, "cookware") == 0) {
    	return parse_cookware(direction);

    // UH, OH...
    } else {
      	return 0;
    }
}

VALUE parse_step(Step * step)
{
	VALUE step_klass;
	VALUE r_step;
	VALUE r_directions;
	VALUE r_direction;

	ListIterator direction_iterator;
  	Direction *current_direction;

	step_klass = rb_const_get_at(rb_mCooklang, rb_intern("Step"));
	r_step = rb_class_new_instance(0, NULL, step_klass);
	r_directions = rb_iv_get(r_step, "@directions");

    direction_iterator = createIterator(step->directions);
    current_direction = nextElement(&direction_iterator);

	if (getLength(step->directions) > 0) {
		while (current_direction != NULL) {
			r_direction = parse_direction(current_direction);

			rb_ary_push(r_directions, r_direction);

			current_direction = nextElement(&direction_iterator);
		}
  	}
	return r_step;
}


int parse_steps(List * c_steps, VALUE * r_steps)
{
	VALUE r_step;
	ListIterator step_iterator;
  	Step *current_step;

  	step_iterator = createIterator(c_steps);
  	current_step = nextElement(&step_iterator);

  	while (current_step != NULL) {
    	r_step = parse_step(current_step);

    	rb_ary_push(r_steps, r_step);

      	current_step = nextElement(&step_iterator);
    }

	// TODO error handling
	return 1;
}

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
