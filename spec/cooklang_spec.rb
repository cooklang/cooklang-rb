# frozen_string_literal: true

require "pp"

RSpec.describe Cooklang do
  it "has a version number" do
    expect(Cooklang::VERSION).not_to be nil
  end

  it "does something useful" do
    text = <<~EOS
      >> cooking time: 30 mins

      Add @bacon{2%slices}"
    EOS
    parsed = Cooklang.parse text

    expect(parsed).to eq(true)
  end
end
