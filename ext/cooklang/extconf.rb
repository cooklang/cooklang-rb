# frozen_string_literal: true

require "mkmf"

$VPATH << "$(srcdir)/parser"
$srcs = Dir.glob("#{$srcdir}/{,parser/}*.c").map { |n| File.basename(n) }.sort
append_cppflags("-I$(srcdir)/parser")

find_header("parser/include/CooklangParser.h")
find_header("parser/parserFiles/Cooklang.tab.h")

create_makefile("cooklang/cooklang")
