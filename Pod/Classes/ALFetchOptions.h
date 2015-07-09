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
 *  @brief  Specfies to retrieve only media asset with a location associated.
 */
@property (nonatomic, assign) BOOL onlyMediaWithLocation;

/**
 *  @brief  ALFetchOptions instance with the @a onlyMediaWithLocation property set to YES
 *
 *  @return An insance with the @a onlyMediaWithLocation property set to YES
 */
+ (ALFetchOptions *)fetchOptionsOnlyLocation;

@end
