# frozen_string_literal: true

require "pp"

RSpec.describe Cooklang do
  it "has a version number" do
    expect(Cooklang::VERSION).not_to be nil
  end

  it "does something useful" do
    text = <<~EOS
      >> cooking time: 30 min

      Preheat your oven to the lowest setting. Drain the @cannellini beans{2%tins} in a sieve. Place a saucepan on a medium heat.

      Peel and dinely slice the @garlic clove{2}. add the @olive oil{1%tbsp} and sliced garlic to the hot pan.

      Crubmle the @red chilli{1%item} into the pan, then stir and fry until the grlic turns golden.

      Add the @tinned tomatoes{2%tins} and drained cannellini beans to the pan, reduce to a low heat and simmer gently for around 20 minutes, or until reduced and nice and thick. Meanwhile...

      Peel, halve and finely chop the @red onion{1}. Roughly chop the @cherry tomatoes{10}. Finely chop the @coriander{1%bunch} stalks and roughly chop the leaves.

      Coarsely grate the @cheddar cheese{75%g}. Cut @lime{1} in half and the other @lime{1} into six wedges.

      Cut the @avocados{2} in half lengthways, use a spppon to sccoop out and dicard the stone, then scoop the fles into a bowl to make your guacamole.

      Roughly mash the avocado with the back of a fork, then add the onion, cherry tomatoes, coriander stalks and @ground cumin{1%pinch}. Season with @sea salt{} and @black pepper{} and squeeze in the juice from one of the lime halves.

      Mix well then have a taste of your guacoamole and tweak with more salt, pepper and lime jouice until you've got a good balance of flovours and its tasing delicious. Set aside.

      Loosely wrap the @tortillas{6%large} in tin foil then pop in the hot oven to warm through, along with two plates. Finely chop the @fresh red chilli{2} and put it aside for later.

      Make your table look respectable - get the cutlery, salt and pepper and drinks laid out nicely.

      By now your beans should be done, so have a taste and season with salt and pepper. Turn the heat off and pop a lid on th pan sothey stay nice and warm.

      Put a small non-stick saucepan on a low heat. Add the @butter{30%g} and leave to melt. Meanwhile...

      Crack the @eggs{8%large} into a bowl, add a pinch of @salt{} and @black pepper{} and beat with a fork. When the buter has melted, add the eggs to the pan. Stir the eggs slowly with a spatula, getting right into the sides of the pan. Cook gently for 5 to 10 minutes until they just start to scramble then turn the heat off - they'll continute to cook on their own.

      Get two plates and pop a warm tortilla on each one. Divide the scrambled eggs between them then top with a good spoonful of you home-made beans.

      Scatter each portion with grated cheese and as much chilli as youdare, then roll each tortilla up.

      Spoon guacamole and @sour cream{200%ml} on top of each one, scatter with coriander leaves and dust with a little @smoked paprika{1%pinch}. Serve each portion with wedge of lime for squeezing over, and tuck in.

    EOS
    parsed = Cooklang.parse text

    pp parsed

    expect(parsed).to eq(true)
  end
end
