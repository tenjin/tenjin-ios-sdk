//
//  TenjinSDK.h
//  TenjinSDK
//
//  Copyright (c) 2016 Tenjin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface TenjinSDK : NSObject

// initialize the Tenjin SDK
+ (TenjinSDK *)init:(NSString *)apiToken;

//initialize the Tenjin SDK with shared secret
+ (TenjinSDK *)init:(NSString *)apiToken sharedSecret:(NSString *) secret;

//initialize the Tenjin SDK + connect
+ (TenjinSDK *)sharedInstanceWithToken:(NSString *)apiToken __deprecated_msg("use `init` and `connect`");

//initialize the Tenjin SDK + connect with a third party deeplink
+ (TenjinSDK *)sharedInstanceWithToken:(NSString *)apiToken andDeferredDeeplink:(NSURL *)url __deprecated_msg("use `init` and `connectWithDeferredDeeplink`");

//returns the shared Tenjin SDK instance
+ (TenjinSDK *)sharedInstance;

//use connect to send connect call. sharedInstanceWithToken automatically does a connect
+ (void)connect;

//use connect to send connect call. sharedInstanceWithToken automatically does a connect
+ (void)connectWithDeferredDeeplink:(NSURL *)url;

//use sendEventWithName for custom event names
+ (void)sendEventWithName:(NSString *)eventName;

//This method checks to make sure integers are passed as values.
+ (void)sendEventWithName:(NSString *)eventName andEventValue:(NSString *)eventValue;

//This method is deprecated in favor of [transaction: andReceipt:], so Tenjin can verify your transactions
+ (void)transaction:(SKPaymentTransaction *)transaction __attribute__((deprecated));

//Use this method to submit a transaction to Tenjin, we will also attempt to verify it for our records
+ (void)transaction:(SKPaymentTransaction *)transaction andReceipt:(NSData *)receipt;

//use transactionWithProductName... when you don't use Apple's SKPaymentTransaction and need to pass revenue directly
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger)quantity andUnitPrice:(NSDecimalNumber *)price;

//use transactionWithProductName...when you don't use Apple's SKPaymentTransaction and need to pass revenue directly with a NSData binary receipt
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger)quantity andUnitPrice:(NSDecimalNumber *)price andTransactionId:(NSString *)transactionId andReceipt:(NSData *)receipt;

//use this method when you want to pass in a base64 receipt instead of a NSData receipt
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger) quantity andUnitPrice:(NSDecimalNumber *)price andTransactionId:(NSString *)transactionId andBase64Receipt:(NSString *)receipt;

//use this method to register the attribution callback
- (void)registerDeepLinkHandler:(void (^)(NSDictionary * params, NSError * error))deeplinkHandler;

// GDPR opt-out
+ (void)optOut;

// GDPR opt-in
+ (void)optIn;

// GDPR opt-out of list of params
+ (void)optOutParams:(NSArray *)params;

// GDPR opt-in with list of params
+ (void)optInParams:(NSArray *)params;

// Appends app subversion to app version
+ (void)appendAppSubversion:(NSNumber *)subversion;

@end
