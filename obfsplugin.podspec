Pod::Spec.new do |s|
  s.name         = "obfsplugin"
  s.version      = "1.0"
  s.summary      = "obfsplugin"
  s.description  = "obfsplugin"
  s.homepage     = "https://github.com/breakwa11"
  s.license      = "MIT"
  s.authors      = { "Break Wa11" => "mmgac001@gmail.com" }
  s.ios.deployment_target = "8.0"
  s.osx.deployment_target = "10.7"
  s.watchos.deployment_target = "2.0"
  s.source = { :git => "https://github.com/breakwa11/obfsplugin.git",
               :branch=>'master' }
  s.source_files  = [
    "c/*.{h,c}",
  ]
  s.header_mappings_dir = "c"
  s.public_header_files = [
    "c/obfsplugin.h",
    "c/obfs.h",
  ]
  s.requires_arc = false
end
