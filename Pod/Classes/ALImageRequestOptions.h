//
//  ALImageRequestOptions.h
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 27/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

@import Photos;

/*!
 *  @brief  Indicates the version of image you want to retrieve
 */
typedef NS_ENUM(NSInteger, ALImageRequestOptionsVersion){
    /*!
     *  The current version, which can be the edited
     */
    ALImageRequestOptionsVersionCurrent = 0,
    /*!
     *  The original version of the asset, even if the current version is edited
     */
    ALImageRequestOptionsVersionUnadjusted,
    /*!
     *  The original version of the asset image
     */
    ALImageRequestOptionsVersionOriginal
};

/*!
 *  @brief  The delivery mode for the request
 */
typedef NS_ENUM(NSInteger, ALImageRequestOptionsDeliveryMode){
    /*!
     *  Automatically provides one or more result in order to balance quality and responsiveness. The completionBlock in the -imageForAsset:asset:size:contentMode:options:completionBlock may be called more than once. The first call may returns a low-quality image while the framework provide the high quality one. This option is not available is the synchronous property is set to NO
     */
    ALImageRequestOptionsDeliveryModeOpportunistic = 0,
    /*!
     *  Provides the highest quality image available, regardless of how much time it takes to load
     */
    ALImageRequestOptionsDeliveryModeHighQualityFormat = 1,
    /*!
     *  Provides a fast-loading image possibly sacrificing image quality
     */
    ALImageRequestOptionsDeliveryModeFastFormat = 2
};

/*!
 *  @brief  The resize mode for the request
 */
typedef NS_ENUM(NSInteger, ALImageRequestOptionsResizeMode){
    /*!
     *  No resize for the image asset
     */
    ALImageRequestOptionsResizeModeNone = 0,
    /*!
     *  Efficently resize the asset to a size similar to, or slightly larger than, the target size
     */
    ALImageRequestOptionsResizeModeFast,
    /*!
     *  Resizes the image to match the target size exactly
     */
    ALImageRequestOptionsResizeModeExact
};

/*! A block called periodically while downloading the image */
typedef void (^ ALAssetImageProgressHandler)(double progress, NSError *error, BOOL *stop, NSDictionary *info);

/*!
 *  @brief  This class allows to specify several options for the image request
 */
@interface ALImageRequestOptions : NSObject

/*!
 *  @brief  This method returns an instance with particular options
 *
 *  @return An ALImageRequestOptions with the delivery mode set to ALImageRequestOptionsDeliveryModeFastFormat
 */
+ (ALImageRequestOptions *)mostEfficentOptions;
/*!
 *  @brief  This method returns an instance with particular options
 *
 *  @return An ALImageRequestOptions with the delivery mode set to ALImageRequestOptionsDeliveryModeOpportunistic
 */
+ (ALImageRequestOptions *)balancedOptions;
/*!
 *  @brief  This method returns an instance with particular options
 *
 *  @return An ALImageRequestOptions with the delivery mode set to ALImageRequestOptionsDeliveryModeHighQualityFormat
 */
+ (ALImageRequestOptions *)bestQualityOptions;

/*!
 *  @brief  The version you want to get
 */
@property (nonatomic, assign) ALImageRequestOptionsVersion version;
/*!
 *  @brief  The delivery mode for the request
 */
@property (nonatomic, assign) ALImageRequestOptionsDeliveryMode deliveryMode;
/*!
 *  @brief  The resize mode for the request
 */
@property (nonatomic, assign) ALImageRequestOptionsResizeMode resizeMode;
/*!
 *  @brief  A Boolean value that determines whether the request will be processed synchronously.
 */
@property (nonatomic, assign) BOOL synchronous;
/*!
 *  @brief  A Boolean value that determines if the network access is allowed or not
 */
@property (nonatomic, assign) BOOL networkAccessAllowed;
/*!
 *  @brief  A block that is called periodically while downloading the image
 */
@property (nonatomic, copy) ALAssetImageProgressHandler progressHandler;

@end
