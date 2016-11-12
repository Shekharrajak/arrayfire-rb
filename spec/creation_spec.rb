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
end
