require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

describe PopCount do
  it "string popcount" do
    pc = PopCount.new("Ruby")
    pc.count.should eq 16
  end
end
