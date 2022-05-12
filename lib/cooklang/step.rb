module Cooklang
  class Step

    # directions is composed from small parts like TextItem, Ingredient, Timer, Cookware
    attr_accessor :directions

    def initialize
      @directions = []
    end
  end
end
