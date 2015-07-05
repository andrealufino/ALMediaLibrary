//
//  ALVideoRequestOptions.m
//  ProvaPhotosFromLibrary
//
//  Created by Andrea Mario Lufino on 28/06/15.
//  Copyright (c) 2015 Andrea Mario Lufino. All rights reserved.
//

#import "ALVideoRequestOptions.h"

@implementation ALVideoRequestOptions

- (instancetype)init {
    self = [super init];
    if (self) {
        _networkAccessAllowed = YES;
        _version = ALVideoRequestOptionsVersionCurrent;
        _deliveryMode = ALVideoRequestOptionsDeliveryModeMediumQualityFormat;
        _progressHandler = nil;
    }
    
    return self;
}

+ (ALVideoRequestOptions *)bestQualityOptions {
    ALVideoRequestOptions *options = [ALVideoRequestOptions new];
    options.deliveryMode = ALVideoRequestOptionsDeliveryModeHighQualityFormat;
    
    return options;
}

+ (ALVideoRequestOptions *)mostEfficentOptions {
    ALVideoRequestOptions *options = [ALVideoRequestOptions new];
    options.deliveryMode = ALVideoRequestOptionsDeliveryModeFastFormat;
    
    return options;
}

+ (ALVideoRequestOptions *)balancedOptions {
    ALVideoRequestOptions *options = [ALVideoRequestOptions new];
    options.deliveryMode = ALVideoRequestOptionsDeliveryModeMediumQualityFormat;
    
    return options;
}

@end
