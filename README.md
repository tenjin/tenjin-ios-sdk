

Please see our [Release Notes](https://github.com/tenjin/tenjin-ios-sdk/wiki) to see detailed version history.

For Unity-specific instructions, please visit https://github.com/tenjin/tenjin-unity-sdk.

Tenjin iOS SDK (v1.7.6) (268KB) (Deployment Version 6.0+)
==============
Note: We recommend using the latest version of <a href="https://developer.apple.com/xcode/">Xcode</a> when integrating our SDK.

Tenjin initialization:
-------------------------------
- If you use pods add `pod 'TenjinSDK'` to your `Podfile` then run `pod install` and skip to step 5!

##### 1. Download the SDK's contents [here](https://github.com/tenjin/tenjin-ios-sdk/archive/master.zip)
##### 2. Drag `libTenjinSDK.a` and `TenjinSDK.h` to your project. Note: If you are testing with 32-bit iOS Simulator devices (i386), you will need to use `libTenjinSDKUniversal.a` instead of `libTenjinSDK.a`.
##### 3. Add the following Frameworks to your project:
  - `AdSupport.framework`
  - `StoreKit.framework`
  - `iAd.framework`

![Dashboard](https://s3.amazonaws.com/tenjin-instructions/ios_link_binary.png "dashboard")

##### 4. Include the linker flags `-ObjC` under your Build Settings
![Dashboard](https://s3.amazonaws.com/tenjin-instructions/ios_linker_flags.png "dashboard")

##### 5. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`.
##### 6. Get your `API_KEY` from your [Tenjin Organization tab](https://tenjin.io/dashboard/organizations).
##### 7a. In your `didFinishLaunchingWithOptions` method add:
```objectivec
[TenjinSDK init:@"<API_KEY>"];
[TenjinSDK connect];
```

Here's an example of what your integration should look like in your `AppDelegate.m` file:

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TenjinSDK init:@"<API_KEY>"];
    [TenjinSDK connect];

    //All your other stuff
    ...
}
```

##### 7b. Alternate initialization to handle deep links from other services. (DO NOT USE 7a and 7b. You need to use only one.)
If you use other services to produce deferred deep links, you can pass Tenjin those deep links to handle the attribution logic with your Tenjin enabled deep links. 

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  
    [TenjinSDK init:@"<API_KEY>"];

    //get your deep link from your other 3rd party service
    NSURL *url = [NSURL withString: @"your_deep_link"];
    
    //if you have a deep link that's generated from a third party service then pass it to tenjin to handle the attribution of deep links holistically
    if(url) {
      [TenjinSDK connectWithDeferredDeeplink:url];
    }
    else{
      [TenjinSDK connect];
    }

    //All your other stuff
    //...
}
```

You can verify if the integration is working through our <a href="https://www.tenjin.io/dashboard/sdk_diagnostics">Live Test Device Data Tool</a>. Add your `advertising_id` or `IDFA/GAID` to the list of test devices. You can find this under Support -> <a href="https://www.tenjin.io/dashboard/debug_app_users">Test Devices</a>.  Go to the <a href="https://www.tenjin.io/dashboard/sdk_diagnostics">SDK Live page</a> and send a test events from your app.  You should see live events come in:
![](https://s3.amazonaws.com/tenjin-instructions/sdk_live_open_events.png)

Tenjin and GDPR:
-------
As part of GDPR compliance, with Tenjin's SDK you can opt-in, opt-out devices/users, or select which specific device-related params to opt-in or opt-out.  `OptOut()` will not send any API requests to Tenjin and we will not process any events.

To opt-in/opt-out:

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  
  [TenjinSDK init:@"<API_KEY>"];

  if ([self checkOptInValue]) {
      [TenjinSDK optIn];
  }
  else {
      [TenjinSDK optOut];
  }

  [TenjinSDK connect];

  //All your other stuff
  //..
}

-(BOOL) checkOptInValue
{
  // check opt-in value
  // return YES; // if user opted-in
  return NO;
}
```

To opt-in/opt-out specific device-related parameters, you can use the `OptInParams()` or `OptOutParams()`.  `OptInParams()` will only send device-related parameters that are specified.  `OptOutParams()` will send all device-related parameters except ones that are specified.  **Please note that we require at least `ip_address`, `advertising_id`, `developer_device_id`, `limit_ad_tracking`, `referrer` (Android), and `iad` (iOS) to properly track devices in Tenjin's system.**

If you want to only get specific device-related parameters, use `OptInParams()`. In example below, we will only these device-related parameters: `ip_address`, `advertising_id`, `developer_device_id`, `limit_ad_tracking`, `referrer`, and `iad`:

```objectivec
[TenjinSDK init:@"<API_KEY>"];

NSArray *optInParams = @[@"ip_address", @"advertising_id", @"developer_device_id", @"limit_ad_tracking", @"referrer", @"iad"];
[TenjinSDK optInParams:optInParams];

[TenjinSDK connect];
```

If you want to send ALL parameters except specfic device-related parameters, use `OptOutParams()`.  In example below, we will send ALL device-related parameters except: `locale`, `timezone`, and `build_id` parameters.
```objectivec
[TenjinSDK init:@"<API_KEY>"];

NSArray *optOutParams = @[@"country", @"timezone", @"language"];
[TenjinSDK optOutParams:optOutParams];

[TenjinSDK connect];
```

#### Device-Related Parameters

| Param  | Description | Reference |
| ------------- | ------------- | ------------- |
| ip_address  | IP Address | |
| advertising_id  | Device Advertising ID | [iOS](https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614151-advertisingidentifier) |
| developer_device_id | ID for Vendor | [iOS](https://developer.apple.com/documentation/uikit/uidevice/1620059-identifierforvendor) |
| limit_ad_tracking  | limit ad tracking enabled | [iOS](https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614148-isadvertisingtrackingenabled) |
| platform | platform  | iOS |
| iad | Apple Search Ad parameters | [iOS](https://searchads.apple.com/advanced/help/measure-results/#attribution-api) |
| os_version | operating system version | [iOS](https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion) |
| device | device name | [iOS (hw.machine)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html) |
| device_model | device model | [iOS (hw.model)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html) |
| device_model_name | device machine  | [iOS (hw.model)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html) |
| device_cpu | device cpu name | [iOS (hw.cputype)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html) |
| os_version_release | operating system version | [iOS](https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion) |
| build_id | build ID | [iOS (kern.osversion)](https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html) |
| locale | device locale | [iOS](https://developer.apple.com/documentation/foundation/nslocalekey) |
| country | locale country | [iOS](https://developer.apple.com/documentation/foundation/nslocalecountrycode) |
| timezone | timezone | [iOS](https://developer.apple.com/documentation/foundation/nstimezone/1387209-localtimezone) |


Tenjin purchase event integration instructions:
-------

There are two ways to handle revenue events:

##### 1. Pass `(SKPaymentTransaction *) transaction` and `(NSData *)receipt` object:
After a purchase has been verified and `SKPaymentTransactionStatePurchased` you can pass Tenjin the transaction which was purchased:
```objectivec
//Get the NSData receipt
NSURL *receiptURL = [[NSBundle mainBundle] appStoreReceiptURL];
NSData *receiptData = [NSData dataWithContentsOfURL:receiptURL];

//Pass the transaction and the receiptData to Tenjin
[TenjinSDK transaction: transaction andReceipt: receiptData];
```
**IMPORTANT:** If you have subscription IAP, you will need to add your app's public key in the <a href="https://www.tenjin.io/dashboard/apps" target="_new"> Tenjin dashboard</a>. You can retreive your iOS App-Specific Shared Secret from the <a href="https://itunesconnect.apple.com/WebObjects/iTunesConnect.woa/ra/ng/app/887212194/addons">iTunes Connect Console</a> > Select your app > Features > In-App Purchases > App-Specific Shared Secret.

**Please note that you are responsible to send subscription transaction one time during each subscription interval (i.e. For example, for a monthly subscription, you will need to send us 1 transaction per month).**  

In the example timeline below, a transaction event should only be sent at the "First Charge" and "Renewal" events. During the trial period, do not send Tenjin the transaction event.  Tenjin does not de-dupe duplicate transactions.

<img src="https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/StoreKitGuide/Art/subscription_timeline_2x.png" />

For more information on subscriptions, please see: <a href="https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/StoreKitGuide/Chapters/Subscriptions.html">Apple documentation on Working with Subscriptions</a>

OR altertnatively, you can send non-validated IAP purchase events:

##### 2. Pass a transaction manually (usually this is necessary if purchases are not handled by Apple):
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
- `ProductName` -> The name or ID of your product
- `CurrencyCode` -> The currency of your unit price
- `Quantity` -> The number of products that are counted for this purchase event
- `UnitPrice` -> The price of each product

Total Revenue calculated is: `TotalRevenue` = `Quantity` * `UnitPrice`

Tenjin custom event integration instructions:
--------
**IMPORTANT: DO NOT SEND CUSTOM EVENTS BEFORE THE CONNECT/INITIALIZATION** event (above). The initialization must come before any custom events are sent. 

You can also use the Tenjin SDK to pass a custom event:
- ```sendEventWithName: (NSString *)eventName``` and

You can use these to pass Tenjin custom interactions with your app to tie this to user level cost from each acquisition source that you use through Tenjin's platform. Here are some examples of usage:

```objectivec
//send a particular event for when someone swipes on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right"];

```

Custom events can also pass an `NSString` `eventValue`. Tenjin will use this `eventValue` as a count or sum for all custom events with the same `eventName`. The `eventValue` MUST BE AN INTEGER. If the `eventValue` is not an integer, we will not send the event. 

Tenjin deferred deeplink integration instructions:
-------
Tenjin supports the ability to direct users to a specific part of your app after a new attributed install via Tenjin's campaign tracking URLs. You can utilize the `registerDeepLinkHandler` handler to access the deferred deeplink through `params[@"deferred_deeplink_url"]` that is passed on the Tenjin campaign tracking URLs. To test you can follow the instructions found <a href="http://help.tenjin.io/t/how-do-i-use-and-test-deferred-deeplinks-with-my-campaigns/547">here</a>.

```objectivec

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //initialize the Tenjin SDK like you normally would for attribution
    [TenjinSDK init:@"<API_KEY>"];
    [TenjinSDK connect]

    //If you want to utilize the deeplink capabilities in Tenjin, utilize the registerDeepLinkHandler to retrieve the deferred_deeplink_url from the params NSDictionary object
    [[TenjinSDK sharedInstance] registerDeepLinkHandler:^(NSDictionary *params, NSError *error) {
        if([params[@"clicked_tenjin_link"] boolValue]){
            if([params[@"is_first_session"] boolValue]){
                
                //use the params to retrieve deferred_deeplink_url through params[@"deferred_deeplink_url"]
                //use the deferred_deeplink_url to direct the user to a specific part of your app
                
            } else{

            }
        }
    }];
}
```

You can also use the v1.7.2+ SDK for handling post-install logic using the `params` provided in this `registerDeepLinkHandler`. For example, if you have a paid app, you can register your paid app install in the following way:

```objectivec

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //initialize the Tenjin SDK like you normally would for attribution
    [TenjinSDK init:@"<API_KEY>"];
    [TenjinSDK connect]

    //If you want to utilize the deeplink capabilities in Tenjin, utilize the registerDeepLinkHandler to retrieve the deferred_deeplink_url from the params NSDictionary object
    [[TenjinSDK sharedInstance] registerDeepLinkHandler:^(NSDictionary *params, NSError *error) {
        
          if([params[@"is_first_session"] boolValue]){
              //send paid app price and revenue to Tenjin
              
          } else{

          }
        
    }];
}
```
