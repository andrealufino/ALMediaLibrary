//
//  ALVideoRequestOptions.h
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 28/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @brief  The version of the video
 */
typedef NS_ENUM(NSInteger, ALVideoRequestOptionsVersion){
    /**
     *  The current version
     */
    ALVideoRequestOptionsVersionCurrent = 0,
    /**
     *  The original version
     */
    ALVideoRequestOptionsVersionOriginal
};

/**
 *  @brief  The delivery mode for the request
 */
typedef NS_ENUM(NSInteger, ALVideoRequestOptionsDeliveryMode){
    /**
     *  Automatically determines which quality of video data to provide based on the request and current conditions
     */
    ALVideoRequestOptionsDeliveryModeAutomatic = 0,
    /**
     *  Provides only the highest quality video available
     */
    ALVideoRequestOptionsDeliveryModeHighQualityFormat = 1,
    /**
     *  Provides a video of moderate quality unless a higher quality version is locally cached.
     
     *  When the networkAccessAllowed property is YES, the medium quality option provides a version of the video asset that is suitable for streaming from iCloud and displaying on a device—for example, an MP4 video with 720p resolution. If a higher-quality version is already cached on the device, Photos provides that video instead
     */
    ALVideoRequestOptionsDeliveryModeMediumQualityFormat = 2,
    /**
     *  Provides whatever quality of video can be most quickly loaded.
     
     *  When the networkAccessAllowed property is YES, the fast option provides a version of the video asset suitable for streaming from iCloud over a low-quality connection—for example, an MP4 video with 360p resolution. If a higher-quality version is already cached on the device, Photos provides that video instead
     */
    ALVideoRequestOptionsDeliveryModeFastFormat = 3
};

/**
 *  @brief  This block could be called multiple times during the download of the video.
 *
 *  @param progress The progress of the download (double)
 *  @param error    A possible error
 *  @param stop     A pointer to stop. If you set this to YES, the request will be stopped
 *  @param info     A dictionary with info for the request
 */
typedef void (^ ALAssetVideoProgressHandler)(double progress, NSError *error, BOOL *stop, NSDictionary *info);

/**
 *  @brief  This class allows to specify some options for a video request
 */
@interface ALVideoRequestOptions : NSObject

/**
 *  @brief  This is the most efficent options instance for a request
 *
 *  @return An ALVideoRequestOptions instance with delivery mode set to ALVideoRequestOptionsDeliveryModeFastFormat
 */
+ (ALVideoRequestOptions *)mostEfficentOptions;
/**
 *  @brief  This is the balanced options
 *
 *  @return An ALVideoRequestOptions instance with delivery mode set to ALVideoRequestOptionsDeliveryModeMediumQualityFormat
 */
+ (ALVideoRequestOptions *)balancedOptions;
/**
 *  @brief  This is the best quality options
 *
 *  @return An ALVideoRequestOptions instance with delivery mode set to ALVideoRequestOptionsDeliveryModeHighQualityFormat
 */
+ (ALVideoRequestOptions *)bestQualityOptions;

/**
 *  @brief  The version of the request
 */
@property (nonatomic, assign) ALVideoRequestOptionsVersion version;
/**
 *  @brief  The delivery mode for the request
 */
@property (nonatomic, assign) ALVideoRequestOptionsDeliveryMode deliveryMode;
/**
 *  @brief  A Boolean value determines if the access to the network is allowed or not
 */
@property (nonatomic, assign) BOOL networkAccessAllowed;
/**
 *  @brief  The progress handler for the request
 */
@property (nonatomic, copy) ALAssetVideoProgressHandler progressHandler;

@end
