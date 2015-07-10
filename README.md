# ALMediaLibrary

[![Version](https://img.shields.io/cocoapods/v/ALMediaLibrary.svg?style=flat)](http://cocoapods.org/pods/ALMediaLibrary)
[![License](https://img.shields.io/cocoapods/l/ALMediaLibrary.svg?style=flat)](http://cocoapods.org/pods/ALMediaLibrary)
[![Platform](https://img.shields.io/cocoapods/p/ALMediaLibrary.svg?style=flat)](http://cocoapods.org/pods/ALMediaLibrary)

## Usage

To run the example project, clone the repo, and run `pod install` from the Example directory first.

You can find the methods in the ALMediaManager.h interface.

There are these methods : 
- find all photos of user library (allPhotosWithOptions:options:callbackBlock:);
- find all videos of user library (allVideosWithOptions:options:callbackBlock:);
- fetch an asset (ALMediaAsset object) to retrieve the relative photo or video with several options (ALImageRequestOptions and ALVideoRequestOptions);

All methods work with blocks.

You can also use the delegate and the NSNotificationCenter to listen for the finish of the fetching of all media and even for the single image and player item.
Look at ALMediaManager.h to see the notifications to listen and for the ALMediaManagerDelegate.

Every class has its own documentation. 

## Requirements

iOS 8.0 and later

## Installation

ALMediaLibrary is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

```ruby
pod "ALMediaLibrary"
```

## Author

Andrea Mario Lufino, andrea.lufino@me.com

## License

ALMediaLibrary is available under the MIT license. See the LICENSE file for more info.
