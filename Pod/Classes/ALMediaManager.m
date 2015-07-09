//
//  ALMediaManager.m
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 26/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import "ALMediaManager.h"

NSString *const ALPhotoInfoIsInCloud     = @"ALPhotoInfoIsInCloud";
NSString *const ALPhotoInfoIsDegraded    = @"ALPhotoInfoIsDegraded";
NSString *const ALPhotoInfoRequestID     = @"ALPhotoInfoRequestID";
NSString *const ALPhotoInfoCancelled     = @"ALPhotoInfoCancelled";
NSString *const ALPhotoInfoError         = @"ALPhotoInfoError";

CGSize ALPhotoSizeMaximum;
CGSize ALPhotoSizeThumbnailSmall;
CGSize ALPhotoSizeThumbnailMedium;
CGSize ALPhotoSizeThumbnailLarge;

@interface ALMediaManager ()

@end

@implementation ALMediaManager

#pragma mark - Singleton

+ (instancetype)sharedManager {
    static id sharedInstance = nil;
    static dispatch_once_t oncePredicate;
    dispatch_once(&oncePredicate, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

#pragma mark - Initialize

+ (void)initialize {
    ALPhotoSizeMaximum = PHImageManagerMaximumSize;
    ALPhotoSizeThumbnailSmall = CGSizeMake(50, 50);
    ALPhotoSizeThumbnailMedium = CGSizeMake(100, 100);
    ALPhotoSizeThumbnailLarge = CGSizeMake(200, 200);
}

#pragma mark - Init

- (instancetype)init {
    self = [super init];
    if (self) {
        _photos = [NSMutableArray new];
        _videos = [NSMutableArray new];
    }
    return self;
}

#pragma mark - Private methods

#pragma mark - Fetch photos

- (void)fetchPhotosAsyncWithMediaType:(PHAssetMediaType)mediaType
                         fetchOptions:(ALFetchOptions *)options
                        callbackBlock:(void (^)(NSArray *assets, NSError *error))callbackBlock {
    
    PHFetchResult *allMediaAssets = [PHAsset fetchAssetsWithMediaType:mediaType
                                                         options:nil];
    
    NSMutableArray *allMedia = [NSMutableArray new];
    
    PHAsset *asset2 = allMediaAssets.lastObject;
    
    // Used to check if there will be returned only objects with a location associated
    BOOL onlyLocation = NO;
    
    // Check if options is not nil and associate its value to internal var
    if (options)
        onlyLocation = options.onlyMediaWithLocation;
    
    [allMediaAssets enumerateObjectsUsingBlock:^(PHAsset *asset, NSUInteger idx, BOOL *stop) {
        ALMediaAsset *mediaAsset = [[ALMediaAsset alloc] initWithAsset:asset];
        // If the request is to have only objects with location, create the correct asset
        if (onlyLocation) {
            if (asset.location) {
                [allMedia addObject:mediaAsset];
            }
        } else {
            [allMedia addObject:mediaAsset];
        }
        
        if ([asset isEqual:asset2]) {
            if (mediaType == PHAssetMediaTypeImage) {
                if (_photos)
                    [_photos removeAllObjects];
                [_photos addObjectsFromArray:allMedia];
            } else if (mediaType == PHAssetMediaTypeVideo) {
                if (_videos)
                    [_videos removeAllObjects];
                [_videos addObjectsFromArray:allMedia];
            }
            
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.delegate didFinishFetchMedia:allMedia];
                callbackBlock ? callbackBlock([allMedia copy], nil) : nil;
            });
            NSLog(@"There are %li assets", (unsigned long)allMedia.count);
        }
    }];
}

#pragma mark - PHDictionary to ALDictionary

// This method converts the dictionary returned in a request using the keys of ALMediaLibrary
- (NSDictionary *)wrapPHDictionaryToALDictionary:(NSDictionary *)PHDictionary {
    NSNumber *isInCloud = PHDictionary[PHImageResultIsInCloudKey];
    NSNumber *isDegraded = PHDictionary[PHImageResultIsDegradedKey];
    NSNumber *requestID = PHDictionary[PHImageResultRequestIDKey];
    NSNumber *isCancelled = PHDictionary[PHImageCancelledKey];
    NSError *error = PHDictionary[PHImageErrorKey];
    
    NSDictionary *info = @{ALPhotoInfoIsInCloud  : isInCloud    ? isInCloud     : [NSNull null],
                           ALPhotoInfoIsDegraded : isDegraded   ? isDegraded    : [NSNull null],
                           ALPhotoInfoRequestID  : requestID    ? requestID     : [NSNull null],
                           ALPhotoInfoCancelled  : isCancelled  ? isCancelled   : [NSNull null],
                           ALPhotoInfoError      : error        ? error         : [NSNull null]};
    
    return info;
}

#pragma mark - PHImageRequestOptions to ALImageRequestOptions

// This method converts the options of class ALImageRequestOptions to the one used in the Photos framework
- (PHImageRequestOptions *)convertFromALImageRequestOptions:(ALImageRequestOptions *)options {
    PHImageRequestOptions *imageOptions = [PHImageRequestOptions new];
    imageOptions.version = (PHImageRequestOptionsVersion)options.version;
    imageOptions.deliveryMode = (PHImageRequestOptionsDeliveryMode)options.deliveryMode;
    imageOptions.resizeMode = (PHImageRequestOptionsResizeMode)options.resizeMode;
    imageOptions.synchronous = options.synchronous;
    imageOptions.networkAccessAllowed = options.networkAccessAllowed;
    if (options.progressHandler)
        imageOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            options.progressHandler(progress, error, stop, info);
        };
    else
        imageOptions.progressHandler = nil;
    
    return imageOptions;
}

#pragma mark - PHVideoRequestOptions to ALVideoRequestOptions

// This method converts the options of class ALVideoRequestOptions to the one used in the Photos framework
- (PHVideoRequestOptions *)convertFromALVideoRequestOptions:(ALVideoRequestOptions *)options {
    PHVideoRequestOptions *videoOptions = [PHVideoRequestOptions new];
    videoOptions.version = (PHVideoRequestOptionsVersion)options.version;
    videoOptions.deliveryMode = (PHVideoRequestOptionsDeliveryMode)options.deliveryMode;
    videoOptions.networkAccessAllowed = options.networkAccessAllowed;
    if (options.progressHandler)
        videoOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            options.progressHandler(progress, error, stop, info);
        };
    else
        videoOptions.progressHandler = nil;
    
    return videoOptions;
}

#pragma mark - Public methods

+ (ALLibraryAuthorizationStatus)isAuthorized {
    PHAuthorizationStatus status = [PHPhotoLibrary authorizationStatus];
    
    return (NSInteger)status;
}

#pragma mark - All photos and videos

- (void)allPhotosWithOptions:(ALFetchOptions *)options callbackBlock:(void (^)(NSArray *assets, NSError *error))callbackBlock {
    [self fetchPhotosAsyncWithMediaType:PHAssetMediaTypeImage
                           fetchOptions:options
                          callbackBlock:callbackBlock];
    [ALFetchOptions fetchOptionsOnlyLocation];
}

- (void)allVideosWithOptions:(ALFetchOptions *)options callbackBlock:(void (^)(NSArray *, NSError *))callbackBlock {
    [self fetchPhotosAsyncWithMediaType:PHAssetMediaTypeVideo
                           fetchOptions:options
                          callbackBlock:callbackBlock];
}

- (void)allMedia:(void (^)(NSArray *, NSError *))callbackBlock {
    
}

#pragma mark - Image request from asset

- (void)imageForAsset:(ALMediaAsset *)asset
                 size:(CGSize)size
          contentMode:(ALImageContentMode)contentMode
              options:(ALImageRequestOptions *)options
      completionBlock:(ALImageRequestCompletionBlock)callbackBlock {
    
    [[PHImageManager defaultManager] requestImageForAsset:asset.asset
                                               targetSize:size
                                              contentMode:(int)contentMode
                                                  options:[self convertFromALImageRequestOptions:options]
                                            resultHandler:^(UIImage *result, NSDictionary *info) {
                                                callbackBlock(result, [self wrapPHDictionaryToALDictionary:info]);
                                            }];
}

#pragma mark - Video request from asset

- (PHImageRequestID)playerItemForAsset:(ALMediaAsset *)asset
                               options:(ALVideoRequestOptions *)options
                       completionBlock:(ALVideoRequestCompletionBlock)completionBlock {
    PHImageRequestID requestID = [[PHImageManager defaultManager] requestPlayerItemForVideo:asset.asset
                                                                                    options:[self convertFromALVideoRequestOptions:options]
                                                                               resultHandler:^(AVPlayerItem *playerItem, NSDictionary *info) {
                                                                                   completionBlock(playerItem, info);
                                                                               }];
    
    return requestID;
}

@end
