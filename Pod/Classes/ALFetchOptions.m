//
//  ALFetchOptions.m
//  Pods
//
//  Created by Andrea Mario Lufino on 08/07/15.
//
//

#import "ALFetchOptions.h"

@implementation ALFetchOptions

- (instancetype)init {
    if (self = [super init]) {
        _onlyMediaWithLocation = NO;
    }
    return self;
}

+ (ALFetchOptions *)fetchOptionsOnlyLocation {
    ALFetchOptions *options = [ALFetchOptions new];
    options.onlyMediaWithLocation = YES;
    
    return options;
}

@end
