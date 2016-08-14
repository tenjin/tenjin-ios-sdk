//
//  TenjinSDK.h
//  TenjinSDK
//
//  Copyright (c) 2016 Tenjin. All rights reserved.
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

//This method is deprecated in favor of [transaction: andReceipt:], so Tenjin can verify your transactions
+ (void)transaction:(SKPaymentTransaction *)transaction __attribute__((deprecated));

//Use this method to submit a transaction to Tenjin, we will also attempt to verify it for our records
+ (void)transaction:(SKPaymentTransaction *)transaction andReceipt:(NSData *)receipt;

//use transactionWithProductName... when you don't use Apple's SKPaymentTransaction and need to pass revenue directly
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger)quantity andUnitPrice:(NSDecimalNumber *)price;

//use transactionWithProductName...when you don't use Apple's SKPaymentTransaction and need to pass revenue directly with a receipt
+ (void)transactionWithProductName:(NSString *)productName andCurrencyCode:(NSString *)currencyCode andQuantity:(NSInteger)quantity andUnitPrice:(NSDecimalNumber *)price andTransactionId:(NSString *)transactionId andReceipt:(NSData *)receipt;
@end
