//
//  ALMediaAsset.h
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 26/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

@import CoreLocation;
@import UIKit;
@import Photos;

/**
 *  @brief  The media asset type represented by the asset
 */
typedef NS_ENUM(NSInteger, ALMediaAssetType){
    /**
     *  Indicates the asset is a photo
     */
    ALMediaAssetTypePhoto,
    /**
     *  Indicates the asset is a video
     */
    ALMediaAssetTypeVideo,
    /**
     *  Indicates the asset is an audio file
     */
    ALMediaAssetTypeAudio,
    /**
     *  The file related to the asset cannot be reproduced by iOS
     */
    ALMediaAssetTypeUnknown
};

/**
 *  @brief  The subtype for the asset
 */
typedef NS_ENUM(NSInteger, ALMediaAssetSubtype){
    /**
     *  No subtype
     */
    ALMediaAssetSubtypeNone,
    /**
     *  A photo taken with the panorama function
     */
    ALMediaAssetSubtypePhotoPanorama,
    /**
     *  A photo taken with the high dynamic range function
     */
    ALMediaAssetSubtypePhotoHDR,
    /**
     *  The asset is a video whose contents are always streamed over a network connection
     */
    ALMediaAssetSubtypeVideoStreamed,
    /**
     *  The asset is a high-frame-rate video
     */
    ALMediaAssetSubtypeVideoHighFrameRate,
    /**
     *  The asset is a time-lapse video
     */
    ALMediaAssetSubtypeVideoTimelapse
};

/**
 *  @brief  Error
 */
typedef NS_ENUM(NSInteger, ALMediaAssetError){
    /**
     *  Invalid asset
     */
    ALMediaAssetErrorInvalid
};


/**
 *  @brief  This class represents a media asset. It is used to access informations such as location, creation date, media type, etc...
 */
@interface ALMediaAsset : NSObject

/**
 *  @brief  Initialize an object with a PHAsset, an object from Photos framework.
 *
 *  @param asset A PHAsset object from which the ALMediaAsset is initialized
 *
 *  @return An instance of ALMediaAsset
 */
- (instancetype)initWithAsset:(PHAsset *)asset;

/**
 *  @brief  The asset relative to this instance
 */
@property (nonatomic, strong, readonly) PHAsset *asset;

/**
 *  @brief  The creation date of the asset
 */
@property (nonatomic, strong, readonly) NSDate *creationDate;
/**
 *  @brief  The last modification date of the asset
 */
@property (nonatomic, strong, readonly) NSDate *modificationDate;
/**
 *  @brief  The width, in pixels, for the image or video related to the asset
 */
@property (nonatomic, assign, readonly) NSUInteger pixelWidth;
/**
 *  @brief  The height, in pixels, for the image or video related to the asset
 */
@property (nonatomic, assign, readonly) NSUInteger pixelHeight;
/**
 *  @brief  The location related to the asset
 */
@property (nonatomic, strong, readonly) CLLocation *location;
/**
 *  @brief  The media type of the asset
 */
@property (nonatomic, assign, readonly) ALMediaAssetType mediaType;
/**
 *  @brief  The medi  subtype of the asset
 */
@property (nonatomic, assign, readonly) ALMediaAssetSubtype mediaSubtype;

@end
