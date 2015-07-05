//
//  ALImageRequestOptions.m
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 27/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import "ALImageRequestOptions.h"

@implementation ALImageRequestOptions

- (instancetype)init {
    self = [super init];
    if (self) {
        _networkAccessAllowed = YES;
        _synchronous = YES;
        _version = ALImageRequestOptionsVersionCurrent;
        _deliveryMode = ALImageRequestOptionsDeliveryModeOpportunistic;
        _resizeMode = ALImageRequestOptionsResizeModeNone;
        _progressHandler = nil;
    }
    
    return self;
}

+ (ALImageRequestOptions *)mostEfficentOptions {
    ALImageRequestOptions *options = [ALImageRequestOptions new];
    /*! This option is not availabla if synchronous is set to NO */
    options.deliveryMode = ALImageRequestOptionsDeliveryModeFastFormat;
    
    return options;
}

+ (ALImageRequestOptions *)balancedOptions {
    ALImageRequestOptions *options = [ALImageRequestOptions new];
    options.deliveryMode = ALImageRequestOptionsDeliveryModeOpportunistic;
    
    return options;
}

+ (ALImageRequestOptions *)bestQualityOptions {
    ALImageRequestOptions *options = [ALImageRequestOptions new];
    options.deliveryMode = ALImageRequestOptionsDeliveryModeHighQualityFormat;
    
    return options;
}

@end
