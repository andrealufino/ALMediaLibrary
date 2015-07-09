//
//  ALFetchOptions.h
//  Pods
//
//  Created by Andrea Mario Lufino on 08/07/15.
//
//

#import <Foundation/Foundation.h>

/**
 *  @brief  This class allows to specify options for fetch requests
 */
@interface ALFetchOptions : NSObject

/**
 *  @brief  Specfies
 */
@property (nonatomic, assign) BOOL onlyMediaWithLocation;

+ (ALFetchOptions *)fetchOptionsOnlyLocation;

@end
