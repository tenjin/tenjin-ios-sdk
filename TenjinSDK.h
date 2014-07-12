//
//  TenjinSDK.h
//  TenjinSDK
//
//  Copyright (c) 2014 Tenjin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TenjinSDK : NSObject

+ (TenjinSDK *)sharedInstanceWithToken:(NSString *)apiToken;

@end
