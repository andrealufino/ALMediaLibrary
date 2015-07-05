//
//  ALMediaAsset.m
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 26/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import "ALMediaAsset.h"

@interface ALMediaAsset ()

@end

@implementation ALMediaAsset

- (instancetype)initWithAsset:(PHAsset *)asset {
    
    if (self = [super init]) {
        _asset = asset;
        _creationDate = asset.creationDate;
        _modificationDate = asset.modificationDate;
        _pixelWidth = asset.pixelWidth;
        _pixelHeight = asset.pixelHeight;
        _location = asset.location;
        
        _mediaType = [self mediaAssetType:asset.mediaType];
        
        _mediaSubtype = [self mediaAssetSubtype:asset.mediaSubtypes];
    }
    return self;
}

- (ALMediaAssetType)mediaAssetType:(PHAssetMediaType)assetMediaType {
    ALMediaAssetType mediaType;
    switch (assetMediaType) {
        case PHAssetMediaTypeImage:
            mediaType = ALMediaAssetTypePhoto;
            break;
        case PHAssetMediaTypeVideo:
            mediaType = ALMediaAssetTypeVideo;
            break;
        case PHAssetMediaTypeAudio:
            mediaType = ALMediaAssetTypeAudio;
            break;
        default:
            mediaType = ALMediaAssetTypeUnknown;
            break;
    }
    
    return mediaType;
}

- (ALMediaAssetSubtype)mediaAssetSubtype:(PHAssetMediaSubtype)assetMediaSubtype {
    ALMediaAssetSubtype mediaSubtype;
    switch (assetMediaSubtype) {
        case PHAssetMediaSubtypeNone:
            mediaSubtype = ALMediaAssetSubtypeNone;
            break;
        case PHAssetMediaSubtypePhotoHDR:
            mediaSubtype = ALMediaAssetSubtypePhotoHDR;
            break;
        case PHAssetMediaSubtypePhotoPanorama:
            mediaSubtype = ALMediaAssetSubtypePhotoPanorama;
            break;
        case PHAssetMediaSubtypeVideoHighFrameRate:
            mediaSubtype = ALMediaAssetSubtypeVideoHighFrameRate;
            break;
        case PHAssetMediaSubtypeVideoStreamed:
            mediaSubtype = ALMediaAssetSubtypeVideoStreamed;
            break;
        case PHAssetMediaSubtypeVideoTimelapse:
            mediaSubtype = ALMediaAssetSubtypeVideoTimelapse;
            break;
        default:
            mediaSubtype = ALMediaAssetSubtypeNone;
            break;
    }
    
    return mediaSubtype;
}

@end
