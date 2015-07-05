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

/*!
 *  @brief  Enumeration for errors
 */
typedef NS_ENUM(NSInteger, ALMediaManagerError){
    /*!
     *  Error which indicates the photos or video array is never been initialized
     */
    ALMediaManagerErrorEmptyArray
};

/*!
 *  @brief  Represents the content mode for the image
 */
typedef NS_ENUM(NSInteger, ALImageContentMode){
    /*!
     *  Fills the image using the default option which is ALImageContentModeAspectFit. Use this when requesting a full-sized image using the ALPhotoSizeMaximum value. The manager, in this way, return an UIImage object not scaled or cropped, but original
     */
    ALImageContentModeDefault = 0,
    /*!
     *  Use this option when you want the entire image to be visible, such as when presenting it in a view with the UIViewContentModeScaleAspectFit content mode
     */
    ALImageContentModeAspectFit = ALImageContentModeDefault,
    /*!
     *  Scales the image so that is completely fit the target size
     */
    ALImageContentModeAspetctFill = 1
};

/*!
 *  @brief  Describes the authorization status
 */
typedef NS_ENUM(NSInteger, ALLibraryAuthorizationStatus){
    /*!
     *  Explicit user permission is required for photo library access, but the user has not yet granted or denied such permission
     */
    ALLibraryAuthorizationStatusNotDetermined = 0,
    /*!
     *  Your app is not authorized to access the photo library, and the user cannot grant such permission.
     
     *  Parental controls or institutional configuration profiles can restrict the user’s ability to grant photo library access to an app
     */
    ALLibraryAuthorizationStatusRestricted,
    /*!
     *  The user has explicitly denied your app access to the photo library
     */
    ALLibraryAuthorizationStatusDenied,
    /*!
     *  The user has explicitly granted your app access to the photo library
     */
    ALLibraryAuthorizationStatusAuthorized
};

 /*! A Boolean value indicating whether the photo asset data is stored on the local device or must be downloaded from iCloud. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoIsInCloud;
/*! A Boolean value indicating whether the result image is a low-quality substitute for the requested image. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoIsDegraded;
/*! A unique identifier for the image request. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoRequestID;
/*! A Boolean value indicating whether the image request was canceled. (NSNumber) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoCancelled;
/*! An error that occurred when Photos attempted to load the image. (NSError) */
FOUNDATION_EXTERN NSString *const ALPhotoInfoError;

/*! Maximum size available for the photo */
FOUNDATION_EXTERN CGSize ALPhotoSizeMaximum;
/*! A 50x50 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailSmall;
/*! A 100x100 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailMedium;
/*! A 200x200 thumbnail */
FOUNDATION_EXTERN CGSize ALPhotoSizeThumbnailLarge;

/*! A block used in the -imageForAsset:asset:size:contentMode:options:completionBlock */
typedef void (^ ALImageRequestCompletionBlock)(UIImage *image, NSDictionary *info);
/*! A block used in the -playerItemForAsset:asset:options:completionBlock */
typedef void (^ ALVideoRequestCompletionBlock)(AVPlayerItem *playerItem, NSDictionary *info);

/*!
 * This is the main class you use to retrieve photos and videos.
 */

@interface ALMediaManager : NSObject

/*!
 *  The singleton instance
 *
 *  @return The singleton instance
 */
+ (ALMediaManager *)sharedManager;

/*!
 *  The photos array. This property is updated every time you call -allPhotos:(void (^)(NSArray *assets, NSError *error))
 */
@property (nonatomic, strong, readonly) NSMutableArray *photos;
/*!
 *  The videos array. This property is updated every time you call -allVideos:(void (^)(NSArray *assets, NSError *error))
 */
@property (nonatomic, strong, readonly) NSMutableArray *videos;

/*!
 *  @brief  Check the authorization status for the library
 *
 *  @return ALLibraryAuthorizationStatus which determines the specific authorization status
 */
+ (ALLibraryAuthorizationStatus)isAuthorized;

/*!
 *  This method retrieve all the photos from the user photo library and returns it as ALMediaAsset object into an array in the completion block
 *
 *  @param callbackBlock The completion block for the method which returns NSArray of ALMediaAsset
 
 *  @see -allVideos:callbackBlock
 */
- (void)allPhotos:(void (^)(NSArray *assets, NSError *error))callbackBlock;

/*!
 *  This method retrieve all the videos from the user photo library and returns it as ALMediaAsset object into an array in the completion block
 *
 *  @param callbackBlock The completion block for the method which returns NSArray of ALMediaAsset
 
 *  @see -allPhotos:callbackBlock
 */
- (void)allVideos:(void (^)(NSArray *assets, NSError *error))callbackBlock;
//- (void)allMedia:(void (^)(NSArray *assets, NSError *error))callbackBlock;

/*!
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
      completionBlock:(ALImageRequestCompletionBlock)callbackBlock;

/*!
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
