# -*- encoding: utf-8 -*-
require File.expand_path('../lib/avl_tree_ext/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Federico Ravasio"]
  gem.email         = ["ravasio.federico@gmail.com"]
  gem.description   = 'AVL Tree implementation relying on a C implementation.'
  gem.summary       = ''
  gem.homepage      = 'https://github.com/razielgn/avl_tree_ext'

  gem.files         = %w{Rakefile avl_tree_ext.gemspec README.md LICENSE}
  gem.files         = Dir['ext/**/*.rb'] + Dir['ext/**/*.c'] + Dir['ext/**/*.h'] + Dir['lib/**/*.rb']
  gem.test_files    = Dir['spec/*.rb']
  gem.name          = 'avl_tree_ext'
  gem.require_paths = ['lib']
  gem.version       = AVLTree::VERSION
  gem.extensions    << 'ext/avl_tree_ext/extconf.rb'

  gem.add_development_dependency 'rake-compiler', '~> 0.8.0'
  gem.add_development_dependency 'rspec', '~> 2.9'
end
