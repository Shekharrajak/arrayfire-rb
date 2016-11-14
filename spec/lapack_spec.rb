require 'spec_helper'

describe ArrayFire::LAPACK do
  context '#cholesky' do
    let(:a) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:lower) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    let(:upper) { ArrayFire::Af_Array.new 2, [2,2],[1,2,3,4] }
    subject {a}
    it {expect(ArrayFire::LAPACK.choleskyLower(a)).to eq lower}
    it {expect(ArrayFire::LAPACK.choleskyUpper(a)).to eq upper}
  end
end