module Cooklang

  class Recipe

    attr_accessor :metadata

    # all the recipe paragraphs will represent recipe steps
    attr_accessor :steps

    def initialize
      @metadata = {}
      @steps = []
    end

  end

end
