Tenjin iOS SDK (Deployment Version 6.0+)
==============

Tenjin install/session integration instructions:
-------------------------------
- If you use pods add `pod 'TenjinSDK'` to your `Podfile` then run `pod install` and skip to step 5!

#####1. Download the SDK <a href="https://github.com/Ordinance/tenjin-ios-sdk/archive/master.zip"> here</a>.
#####2. Drag `libTenjinSDKUniversal.a` and `TenjinSDK.h` to your project. 
#####3. Add the following Frameworks to your project:
  - `AdSupport.framework`
  - `iAd.framework` 
  - `StoreKit.framework`

![Dashboard](https://s3.amazonaws.com/tenjin-instructions/ios_link_binary.png "dashboard")

#####4. Include the linker flags `-ObjC` and `-all_load` under your Build Settings
![Dashboard](https://s3.amazonaws.com/tenjin-instructions/ios_linker_flags.png "dashboard")

#####5. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`.
#####6. Get your `API_KEY` from your <a href="https://tenjin.io/dashboard/organizations">Tenjin Organization tab.</a>
#####7. In your `didFinishLaunchingWithOptions` method add: 
```objectivec
[TenjinSDK sharedInstanceWithToken:@"<API_KEY>"];
```

Here's an example of what your integration should look like in your `AppDelegate.m` file:

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TenjinSDK sharedInstanceWithToken:@"<API_KEY>"];
    
    //All your other stuff
    ...
}
```
#####8. Make sure Tenjin is receives all your events in the <a href="https://tenjin.io/dashboard/sdk_diagnostics"> Tenjin Diagnostic tab.</a>


Tenjin purchase event integration instructions:
--------
There are two ways to handle revenue events: 
#####1. Pass a `(SKPaymentTransaction *) transaction` object:
After a purchase has been verified and `SKPaymentTransactionStatePurchased` you can pass Tenjin the transaction which was purchased:
```objectivec
[TenjinSDK transaction: transaction];
```
OR
#####2. Pass a transaction manually (usually this is necessary if purchases are not handled by Apple):
To use this method, you will need a `productName`, `currencyCode`, `quantity`, and the unit `price` of the transaction:
```objectivec
NSString *productName = @"product_1";
NSString *currencyCode = @"USD";
NSDecimalNumber *price = [NSDecimalNumber decimalNumberWithString:@"0.99"];
NSInteger quantity = 1;

[TenjinSDK  transactionWithProductName: productName 
            andCurrencyCode: currencyCode 
            andQuantity: quantity 
            andUnitPrice: price];
```


Tenjin custom event integration instructions:
--------
There are two handlers that you can use to pass custom events: 
- ```sendEventWithName: (NSString *)eventName``` and 
- ```sendEventWithName:(NSString*)eventName andEventValue:(NSString*)eventValue```

You can use these to pass Tenjin custom interactions with your app to tie this to user level cost from each acquisition source that you use through Tenjin's platform. Here are some examples of usage:

```objectivec
//send a particular event when you award points to a user (in this case 100 points are awarded to a user)
[TenjinSDK sendEventWithName:@"points_awarded" andEventValue:@"100"];

//send a particular event for when someone swipes on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right"];

```
