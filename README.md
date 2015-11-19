Tenjin iOS SDK (Deployment Version 6.0+)
==============

Tenjin install/session integration instructions:
-------------------------------
- If you use pods add `pod 'TenjinSDK'` to your `Podfile` then run `pod install` and skip to step 5!

#####1. Download the SDK's contents <a href="https://github.com/Ordinance/tenjin-ios-sdk/archive/master.zip"> here</a>.
#####2. Drag `libTenjinSDK.a` and `TenjinSDK.h` to your project. 
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
#####8. Validate your live events by <a href="https://tenjin.io/dashboard/debug_app_users">adding your Test Device</a> and observing your events come through in the live <a href="https://tenjin.io/dashboard/sdk_diagnostics/live"> Tenjin Diagnostic tab.</a>


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
- `ProductName` -> The name of your product
- `CurrencyCode` -> The currency of your price
- `Quantity` -> The number of transactions that will be counted
- `UnitPrice` -> The price of each transaction
As a result the Total Revenue that will be counted here is: `TotalRevenue` = `Quantity`*`UnitPrice`

Tenjin custom event integration instructions:
--------
You can also use the Tenjin SDK to pass a custom event:
- ```sendEventWithName: (NSString *)eventName``` and

You can use these to pass Tenjin custom interactions with your app to tie this to user level cost from each acquisition source that you use through Tenjin's platform. Here are some examples of usage:

```objectivec
//send a particular event for when someone swipes on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right"];

```
