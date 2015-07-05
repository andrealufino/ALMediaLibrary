#
# Be sure to run `pod lib lint ALMediaLibrary.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# Any lines starting with a # are optional, but encouraged
#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "ALMediaLibrary"
  s.version          = "0.1.0"
  s.summary          = "A wrapper around Photos framework"
  s.description      = "This is a wrapper around the Photos framework"
  s.homepage         = "https://github.com/andrealufino/ALMediaLibrary"
  s.license          = 'MIT'
  s.author           = { "Andrea Mario Lufino" => "andrea.lufino@me.com" }
  s.source           = { :git => "https://github.com/andrealufino/ALMediaLibrary.git", :tag => s.version.to_s }

  s.platform     = :ios, '8.0'
  s.requires_arc = true

  s.source_files = 'Pod/Classes/**/*'
  s.resource_bundles = {
    'ALMediaLibrary' => ['Pod/Assets/*.png']
  }

  s.frameworks = 'UIKit', 'MapKit', 'Photos'
end
