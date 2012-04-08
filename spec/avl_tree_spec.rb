require 'spec_helper'

describe AVLTree do
  context 'empty tree' do
    its(:length) { should be_zero }
    its(:count)  { should be_zero }
    its(:size)   { should be_zero }
    its(:min)    { should be_nil }
    its(:max)    { should be_nil }
    its(:to_a)   { should be_empty }
  end

  it 'should include Enumerable' do
    subject.class.ancestors.should include Enumerable
  end

  it 'should increment the size when inserting one element' do
    expect do
      subject.insert 'a'
    end.to change{ subject.size }.by 1
  end

  it 'should discard existing elements' do
    2.times{ subject.insert 9 }
    subject.count.should == 1
  end

  it 'should include the element once inserted' do
    subject.insert [1]
    subject.should include [1]
  end

  it 'should report 4 as the minimum of 4 8 9' do
    [9, 4, 8].each{ |n| subject.insert n }
    subject.min.should == 4
  end

  it 'should report 89 as the maximum of 45 78 89' do
    [78, 89, 45].each{ |n| subject.insert n }
    subject.max.should == 89
  end

  it 'should not include a removed element' do
    subject.insert 89
    subject.remove 89
    subject.should_not include 89
  end

  it 'should decrement the size when deleting one element' do
    subject.insert 7

    expect do
      subject.remove 7
    end.to change{ subject.count }.by -1
  end

  it 'should convert to a sorted array' do
    elements = [8, 4, 7, 2, 3, 6]
    elements.each{ |i| subject.insert i }
    subject.to_a.should == elements.sort
  end

  it 'should raise an error if inserting heterogeneous elements' do
    expect do
      subject.insert [1,2,3]
      subject.insert 8.9
    end.to raise_error(TypeError)
  end
end
