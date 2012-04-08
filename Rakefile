#!/usr/bin/env rake
require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

Rake::ExtensionTask.new('avl_tree_ext') do |ext|
  ext.lib_dir = File.join('lib', 'avl_tree_ext')
end

desc 'Run tests'
RSpec::Core::RakeTask.new do |t|
  t.pattern = './spec/**/*_spec.rb' # don't need this, it's default.
end

Rake::Task[:spec].prerequisites << :compile
