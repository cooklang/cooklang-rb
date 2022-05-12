# frozen_string_literal: true

require "mkmf"

$VPATH << "$(srcdir)/parser/parserFiles"
$VPATH << "$(srcdir)/parser/src"
$srcs = %w(cooklang.c cooklang_parser.c Cooklang.tab.c LinkedListLib.c CooklangRecipe.c CooklangParser.c)

create_makefile("cooklang")
