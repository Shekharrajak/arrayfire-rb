require 'spec_helper'

describe ArrayFire::BLAS do
  context '#matmul' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:b) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject {c}
    it {expect(ArrayFire::BLAS.matmul(a,b)).to eq c}
  end
end