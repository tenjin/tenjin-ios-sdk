//
//  TenjinSDK.h
//  TenjinSDK
//
//  Copyright (c) 2014 Tenjin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface TenjinSDK : NSObject

//required to initialize the Tenjin SDK
+ (TenjinSDK *)sharedInstanceWithToken:(NSString *)apiToken;

//use sendEventWithName for custom event names
+ (void)sendEventWithName:(NSString *)eventName;

//This method checks to make sure integers are passed as values.
+ (void)sendEventWithName:(NSString *)eventName andEventValue:(NSString *)eventValue;

//use transaction: when you would like us to automatically validate and collect data about your SKPaymentTransaction
+ (void)transaction:(SKPaymentTransaction *)transaction;

//use transactionWithProductName... when you don't use Apple's SKPaymentTransaction and need to pass revenue directly
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger)quantity andUnitPrice:(NSDecimalNumber *)price;

@end
