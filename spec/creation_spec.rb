require 'spec_helper'

# e.g. y = Af_Array.new(ndims, dims, elements, dtype)

describe ArrayFire::Af_Array do
  context '#initialize' do
    let(:i) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject { i }
    it { expect(i.ndims).to eq 2 }
    it { expect(i.dimension).to eq [2,2] }
    it { expect(i.array).to eq [1,2,3,4] }
    it{
      pending("only float supported currently")
      expect(i.dtype).to eq :float64
    }
  end

  context '#addition' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject {c}
    it {expect(a+b).to eq c}
    it {expect(c.ndims).to eq a.ndims}
    it {expect(c.dimension).to eq a.dimension}
  end
end
