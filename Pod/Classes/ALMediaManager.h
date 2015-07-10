//
//  ALMediaManager.h
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 26/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import <Foundation/Foundation.h>
@import Photos;
#import "ALMediaAsset.h"
#import "ALImageRequestOptions.h"
#import "ALVideoRequestOptions.h"
#import "ALFetchOptions.h"



/** Notification sent when the manager finishes the media fetch */
FOUNDATION_EXTERN NSString *const ALMediaManagerFetchMediaFinished;

/** Notification sent when the manager finishes to retrieve image from asset */
FOUNDATION_EXTERN NSString *const ALMediaManagerFetchImageFromAssetFinished;

/** Notification sent when the manager finishes to retrieve player item from asset */
FOUNDATION_EXTERN NSString *const ALMediaManagerFetchPlayerItemFromAssetFinished;



/** The key used in the user info dictionary of NSNotification to store the array of assets */
FOUNDATION_EXTERN NSString *const ALMediaManagerNotificationUserInfoAssetsKey;

/** The key used in the user info dictionary of NSNotification to store the media type of the asset. It store a ALMediaAssetType value in a NSNumber object */
FOUNDATION_EXTERN NSString *const ALMediaManagerNotificationUserInfoAssetTypeKey;

/** The key used in the user info dictionary of NSNotification to store the result image from the method @a imageFromAsset */
FOUNDATION_EXTERN NSString *const ALMediaManagerNotificationUserInfoAssetImage;

/** he key used in the user info dictionary of NSNotification to store the result player item from the method @a playerItemFromAsset */
FOUNDATION_EXTERN NSString *const ALMediaManagerNotificationUserInfoAssetPlayerItem;



/**
 *  @brief  Enumeration for errors
 */
typedef NS_ENUM(NSInteger, ALMediaManagerError){
    /**
     *  Error which indicates the photos or video array is never been initialized
     */
    ALMediaManagerErrorEmptyArray
};



/**
 *  @brief  Represents the content mode for the image
 */
typedef NS_ENUM(NSInteger, ALImageContentMode){
    /**
     *  Fills the image using the default option which is ALImageContentModeAspectFit. Use this when requesting a full-sized image using the ALPhotoSizeMaximum value. The manager, in this way, return an UIImage object not scaled or cropped, but original
     */
    ALImageContentModeDefault = 0,
    /**
     *  Use this option when you want the entire image to be visible, such as when presenting it in a view with the UIViewContentModeScaleAspectFit content mode
     */
    ALImageContentModeAspectFit = ALImageContentModeDefault,
    /**
     *  Scales the image so that is completely fit the target size
     */
    ALImageContentModeAspetctFill = 1
};



/**
 *  @brief  Describes the authorization status
 */
typedef NS_ENUM(NSInteger, ALLibraryAuthorizationStatus){
    /**
     *  Explicit user permission is required for photo library access, but the user has not yet granted or denied such permission
     */
    ALLibraryAuthorizationStatusNotDetermined = 0,
    /**
     *  Your app is not authorized to access the photo library, and the user cannot grant such permission.
     
     *  Parental controls or institutional configuration profiles can restrict the user’s ability to grant photo library access to an app
     */
    ALLibraryAuthorizationStatusRestricted,
    /**
     *  The user has explicitly denied your app access to the photo library
     */
    ALLibraryAuthorizationStatusDenied,
    /**
     *  The user has explicitly granted your app access to the photo library
     */
    ALLibraryAuthorizationStatusAuthorized
};



 /** A Boolean value indicating whether the photo asset data is stored on the local device or must be downloaded from iCloud. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoIsInCloud;

/** A Boolean value indicating whether the result image is a low-quality substitute for the requested image. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoIsDegraded;

/** A unique identifier for the image request. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoRequestID;

/** A Boolean value indicating whether the image request was canceled. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoCancelled;

/** An error that occurred when Photos attempted to load the image. (NSError) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoError;



/** Maximum size available for the photo */
FOUNDATION_EXTERN CGSize ALPhotoSizeMaximum;

/** A 50x50 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailSmall;

/** A 100x100 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailMedium;

/** A 200x200 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailLarge;



/** A block used in the -imageForAsset:asset:size:contentMode:options:completionBlock */
typedef void (^ ALImageRequestCompletionBlock)(UIImage *image, NSDictionary *info);

/** A block used in the -playerItemForAsset:asset:options:completionBlock */
typedef void (^ ALVideoRequestCompletionBlock)(AVPlayerItem *playerItem, NSDictionary *info);



/**
 *  @brief  This is the delegate of the ALMediaManager object
 */
@protocol ALMediaManagerDelegate <NSObject>

/**
 *  @brief  This method is called when the manager finishes the media asset fetching
 *
 *  @param assets The array containing the @a ALMediaAsset objects
 *  @param type   The type of the assets (@a ALMediaAssetType)
 *  @see   didFinishRetrieveImageAsset:image
 *         didFinishRetrieveVideoAsset:playerItem
 */
- (void)didFinishFetchMedia:(NSArray *)assets ofType:(ALMediaAssetType)type;

/**
 *  @brief  Called when the manager finishes to retrieve the image from the asset with @a imageFromAsset method
 *
 *  @param image The resulting image
 *  @see   didFinishRetrieveVideoAsset:playerItem
 */
- (void)didFinishRetrieveImageAsset:(UIImage *)image;

/**
 *  @brief  Called when the manager finishes to retrieve the player item from the asset in @a playerItemFromAsset method
 *
 *  @param playerItem The player item object related to the video asset (AVPlayerItem)
 *  @see   didFinishRetrieveImageAsset:image
 */
- (void)didFinishRetrieveVideoAsset:(AVPlayerItem *)playerItem;

@end



/**
 * This is the main class you use to retrieve photos and videos.
 */
@interface ALMediaManager : NSObject

/**
 *  The singleton instance
 *
 *  @return The singleton instance
 */
+ (ALMediaManager *)sharedManager;

/**
 *  @brief    Set this property to YES allow to listen the notification when fetch of photos and videos is finished. This property is set to NO by default
 *  @remarks  To set this property to YES doesn't disable the callbackBlock or the delegate (if you set it). So, if you want only NSNotificationCenter, pass nil to the callbackBlock of allPhotos and allVideos. The @a assets array will be passed into the user info of the notification object, with the key @a ALMediaManagerNotificationUserInfoAssetsKey and the media type of the fetch in question will be at the key @a ALMediaManagerNotificationUserInfoAssetTypeKey as a @a ALMediaAssetType struct stored in @a NSNumber object, so you can compare its @a integerValue with @a ALMediaType options
 */
@property (nonatomic, assign) BOOL useNSNotificationCenter;

/**
 *  The photos array. This property is updated every time you call -allPhotosWithOptions:options:callbackBlock:
 */
@property (nonatomic, strong, readonly) NSMutableArray *photos;
/**
 *  The videos array. This property is updated every time you call -allVideosWithOptions:options:callbackBlock:
 */
@property (nonatomic, strong, readonly) NSMutableArray *videos;

@property (nonatomic, weak) id<ALMediaManagerDelegate> delegate;

/**
 *  @brief  Check the authorization status for the library
 *
 *  @return ALLibraryAuthorizationStatus which determines the specific authorization status
 */
+ (ALLibraryAuthorizationStatus)isAuthorized;

/**
 *  This method retrieves all the photos from the user photo library and returns it as ALMediaAsset object into an array in the completion block
 *
 *  @param options       The fetch options for the request
 *  @param callbackBlock The completion block for the method which returns NSArray of ALMediaAsset
 
 *  @see -allVideos:callbackBlock
 */
- (void)allPhotosWithOptions:(ALFetchOptions *)options callbackBlock:(void (^)(NSArray *assets, NSError *error))callbackBlock;

/**
 *  This method retrieve all the videos from the user photo library and returns it as ALMediaAsset object into an array in the completion block
 *
 *  @param options       The fetch options for the request
 *  @param callbackBlock The completion block for the method which returns NSArray of ALMediaAsset
 
 *  @see -allPhotos:callbackBlock
 */
- (void)allVideosWithOptions:(ALFetchOptions *)options callbackBlock:(void (^)(NSArray *, NSError *))callbackBlock;
//- (void)allMedia:(void (^)(NSArray *assets, NSError *error))callbackBlock;

/**
 *  This method retrieve the UIImage object of a given asset. You can customize your request through the parameters
 *
 *  @param asset         The ALMediaAsset object from which retrieve the image
 *  @param size          A CGSize object needed for the size of the image. You can also use ALPhotoSizeMaximum and ALPhotoSizeThumbnail
 *  @param contentMode   ALImageContentMode for the UIImage object
 *  @param options       ALImageRequestOptions object which represents the specific for the request
 *  @param callbackBlock The callback block which returns an UIImage object and an NSDictionary with photo info
 
 *  @see -playerItemForAsset:asset:options:completionBlock
 */
- (void)imageForAsset:(ALMediaAsset *)asset
                 size:(CGSize)size
          contentMode:(ALImageContentMode)contentMode
              options:(ALImageRequestOptions *)options
      completionBlock:(ALImageRequestCompletionBlock)completionBlock;

/**
 *  This method retrieve the AVPlayerItem object relative to a given video asset (ALMediaAsset object).
 *
 *  @param asset           The ALMediaAsset from which retrieve the video
 *  @param options         ALVideoRequestOptions object which represents the specific for the request
 *  @param completionBlock The callback block which returns the AVPlayerItem and NSDictionary with photo info
 *
 *  @return PHImageRequestID which is a int value represents the unique identifier of the asynchronous request
 */
- (PHImageRequestID)playerItemForAsset:(ALMediaAsset *)asset
                               options:(ALVideoRequestOptions *)options
                       completionBlock:(ALVideoRequestCompletionBlock)completionBlock;

@end
