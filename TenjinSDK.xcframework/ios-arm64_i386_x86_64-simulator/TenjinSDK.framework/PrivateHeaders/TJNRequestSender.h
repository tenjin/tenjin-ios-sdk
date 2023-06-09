
// Created by Tenjin on 2019-09-17.
// Copyright (c) 2019 Tenjin. All rights reserved.


#import <Foundation/Foundation.h>

typedef void (^HandlerBlock)(NSData *_Nullable data, NSURLResponse *_Nullable NSURLResponse, NSError *_Nullable error, BOOL retry);

@protocol TJNRequestSender

@property(nonatomic, copy) HandlerBlock _Nullable defaultPostCompletionBlock;

- (void)post:(NSString *_Nonnull)url
        body:(NSString *_Nullable)body
     headers:(NSDictionary *_Nullable)headers;

- (void)method:(NSString *_Nonnull)method
           url:(NSString *_Nonnull)url
          body:(NSMutableString *_Nullable)body;

- (void)method:(NSString *_Nonnull)method
           url:(NSString *_Nonnull)url
          body:(NSString *_Nullable)body
       headers:(NSDictionary *_Nullable)headers;

- (void) method:(NSString *_Nonnull)method
            url:(NSString *_Nonnull)url
           body:(NSString *_Nullable)body
        headers:(NSDictionary *_Nullable)headers
completionBlock:(void (^_Nullable)(NSData *_Nullable, NSURLResponse *_Nullable, NSError *_Nullable, BOOL))block;
@end
