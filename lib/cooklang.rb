# frozen_string_literal: true

require_relative "cooklang/version"
require_relative "cooklang/timer"
require_relative "cooklang/ingredient"
require_relative "cooklang/cookware"
require_relative "cooklang/text_item"
require_relative "cooklang/step"
require_relative "cooklang/recipe"
require_relative "cooklang/cooklang"

module Cooklang
  class Error < StandardError; end

  def self.parse(text)
    parser = Parser.new
    parser.parse(text)
  end

end
