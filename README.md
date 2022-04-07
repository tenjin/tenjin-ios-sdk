# Summary

The native iOS SDK for Tenjin. To learn more about Tenjin and our product offering, please visit https://www.tenjin.com.

- Please see our <a href="https://github.com/tenjin/tenjin-ios-sdk/blob/master/RELEASE_NOTES.md">Release Notes</a> to see detailed version history.
- For Unity-specific instructions, please visit https://github.com/tenjin/tenjin-unity-sdk.
- For any issues or support, please contact: support@tenjin.com

### Notes:

  - Xcode 12 requirement, if you’re using iOS SDK v1.12.0 and higher.
  - For AppTrackingTransparency, be sure to update your project `.plist` file and add `Privacy - Tracking Usage Description` <a href="https://developer.apple.com/documentation/bundleresources/information_property_list/nsusertrackingusagedescription" target="_new">(NSUserTrackingUsageDescription)</a> along with the text message you want to display to users. This library is only available in iOS 14.0+.
  - For <a href="https://developer.apple.com/documentation/iad/setting_up_apple_search_ads_attribution" target="_new">Apple Search Ads Attribution</a> support, please be sure to upgrade to v1.12.6+ and add the `AdServices.framework` library. This library is only available in iOS 14.3+.

# Table of contents

- [SDK Integration][1]
	- [Tenjin initialization with ATTrackingManager][2]
		- [Displaying an ATT permission prompt][3]
			- [Configuring a user tracking description][4]
	- [SKAdNetwork and Conversion value][5]
		- [SKAdNetwork and iOS 15+ Advertiser Postbacks][6]
	- [Tenjin and GDPR][7]
	- [Device-Related Parameters][8]
- [Purchase Events][9]
	- [Subscription IAP][10]
- [Custom Events][11]
- [Deferred Deeplink][12]
- [Server-to-server integration][13]
- [App Subversion][14]
- [Impression Level Ad Revenue Integration][15]
  - [AppLovin Impression Level Ad Revenue Integration][16]
  - [IronSource Impression Level Ad Revenue Integration][17]
  - [HyperBid Impression Level Ad Revenue Integration][18]
  - [AdMob Impression Level Ad Revenue Integration][19]
  - [Topon Impression Level Ad Revenue Integration][20]
- [Attribution Info][42]

# <a id="sdk-integration"></a> SDK Integration

If you use pods, add `pod 'TenjinSDK'` to your `Podfile` then run `pod install` and skip to step 5.

1. Download the latest SDK release [here][21].

2. Drag `libTenjinSDK.a` and `TenjinSDK.h` to your project. Note: If you are testing with 32-bit iOS Simulator devices (i386), you will need to use `libTenjinSDKUniversal.a` instead of `libTenjinSDK.a`.

3. Add the following Frameworks to your project:
	  1. `AdServices.framework`
	  2. `AdSupport.framework`
	  3. `AppTrackingTransparency.framework`
	  4. `iAd.framework`
	  5. `StoreKit.framework`

![Dashboard][image-1]

4. Include the linker flags `-ObjC` under your Build Settings
![Dashboard][image-2]

5. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`.

6. Get your `API_KEY` from your [Tenjin Organization tab][22].

7. a. In your `didFinishLaunchingWithOptions` method add:
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

If you are using Swift 5, use the `getInstance()` method instead of `init()`.  See our [sample Swift app][23]

**NOTE:** Please ensure you implement this code on every `didFinishLaunchingWithOptions`, not only on the first app open of the app. If we notice that you don't follow our recommendation, we can't give you the proper support or your account might be under suspension.

7. b. Alternate initialization to handle deep links from other services. (DO NOT USE 7a and 7b. You need to use only one.)
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

You can verify if the integration is working through our <a href="https://www.tenjin.io/dashboard/sdk_diagnostics">Live Test Device Data Tool</a>. Add your `advertising_id` or `IDFA/GAID` to the list of test devices. You can find this under Support -\> <a href="https://www.tenjin.io/dashboard/debug_app_users">Test Devices</a>.  Go to the <a href="https://www.tenjin.io/dashboard/sdk_diagnostics">SDK Live page</a> and send the test events from your app.  You should see live events come in:

![][image-3]

## <a id="attrackingmanager"></a>Tenjin initialization with ATTrackingManager

Starting with iOS 14, you have the option to show the initial <a href="">ATTrackingManager</a> permissions prompt and selection to opt in/opt out users.
If the device doesn't accept tracking permission, IDFA will become zero. If the device accepts tracking permission, the `connect()` method will send the IDFA to our servers.
You can also still call Tenjin `connect()`, without using ATTrackingManager, only in below iOS 14. ATTrackingManager permissions prompt is obligatory from the end of spring 2021.

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

    [TenjinSDK init:@"<API_KEY>"];

    if (@available(iOS 14, *)) {
        [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
            [TenjinSDK connect];
        }];
    } else {
        [TenjinSDK connect];
    }
}
```

### <a id="displayattprompt"></a>Displaying an ATT permission prompt

To comply with Apple’s ATT guidelines, you must provide a description for the ATT permission prompt, then implement the permission request in your application.

> Note: You must implement the permission request before serving ads in your game.

#### <a id="configureusertrackdescription"></a> Configuring a user tracking description
Apple requires a description for the ATT permission prompt. You need to set the description with the `NSUserTrackingUsageDescription` key in the `Info.plist` file of your Xcode project. You have to provide a message that informs the user why you are requesting permission to use device tracking data:

- In your Xcode project navigator, open the `Info.plist` file.
- Click the add button (+) beside any key in the property list editor to create a new property key.
- Enter the key name `NSUserTrackingUsageDescription`.
- Select a string value type.
- Enter the app tracking transparency message in the value field. Some examples include:
	- "We will use your data to provide a better and personalized ad experience."
	- "We try to show ads for apps and products that will be most interesting to you based on the apps you use, the device you are on, and the country you are in."
	- "We try to show ads for apps and products that will be most interesting to you based on the apps you use."

> Note: Apple provides specific [app store guidelines][24] that define acceptable use and messaging for all end-user facing privacy-related features. Tenjin does not provide legal advice. Therefore, the information on this page is not a substitute for seeking your own legal counsel to determine the legal requirements of your business and processes, and how to address them.

## <a id="skadnetwork-and-conversion-value"></a> SKAdNetwork and Conversion value

As part of <a href="https://developer.apple.com/documentation/storekit/skadnetwork">SKAdNetwork</a>, we created wrapper methods for `registerAppForAdNetworkAttribution()` and <a href="https://developer.apple.com/documentation/storekit/skadnetwork/3566697-updateconversionvalue">`updateConversionValue(_:)`</a>.
Our methods will register the equivalent SKAdNetwork methods and also send the conversion values to our servers.

updateConversionValue(\_:) 6 bit value should correspond to the in-app event and shouldn’t be entered as binary representation but 0-63 integer. Please refer to [this][25] page for how to implement conversion values.

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

    [TenjinSDK init:@"<API_KEY>"];

    //
    // This will call [SKAdNetwork registerAppForAdNetworkAttribution]
    //
    [TenjinSDK registerAppForAdNetworkAttribution];

    [TenjinSDK connect];

    //
    // This will call [SKAdNetwork updateConversionValue: <YOUR 6 bit value>]
    // and also send conversion value to our servers.
    //
    // You will need to use a value between 0-63 for <YOUR 6 bit value>.
    //
    [TenjinSDK updateConversionValue: <YOUR 6 bit value>];
}
```

### <a id="skadnetwork-and-ios15-plus-advertiser-postbacks"></a> SKAdNetwork and iOS 15+ Advertiser Postbacks

To specify Tenjin as the destination for your [SK Ad Network postbacks][26], do the following:

1. Select `Info.plist` in the Project navigator in Xcode.
2. Click the Add button (+) beside a key in the property list editor and press Return.
3. Type the key name `NSAdvertisingAttributionReportEndpoint`.
4. Choose String from the pop-up menu in the Type column.
5. Enter `https://tenjin-skan.com`

These steps are an adaption from Apple's instructions at [https://developer.apple.com/documentation/storekit/skadnetwork/configuring\_an\_advertised\_app][27].

## <a id="gdpr"></a> Tenjin and GDPR

As part of GDPR compliance, with Tenjin's SDK you can opt-in, opt-out devices/users, or select which specific device-related params to opt-in or opt-out.  `OptOut()` will not send any API requests to Tenjin, and we will not process any events.

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

To opt-in/opt-out specific device-related parameters, you can use the `OptInParams()` or `OptOutParams()`.  `OptInParams()` will only send device-related parameters that are specified.  `OptOutParams()` will send all device-related parameters except ones that are specified.  

- Kindly note that we require the following parameter to properly track devices in Tenjin's system. If the mandatory parameter is missing, the event will not be processed or recorded.

	- `developer_device_id`

If you intend to use Google Ads, you will also need to add: `platform`, `os_version`, `locale`, `device_model`, and `build_id`.

If you want to only get specific device-related parameters, use `OptInParams()`. In example below, we will only these device-related parameters: `ip_address`, `advertising_id`, `developer_device_id`, `limit_ad_tracking`, and `iad`:

```objectivec
[TenjinSDK init:@"<API_KEY>"];

NSArray *optInParams = @[@"ip_address", @"advertising_id", @"developer_device_id", @"limit_ad_tracking", @"iad"];
[TenjinSDK optInParams:optInParams];

[TenjinSDK connect];
```

If you want to send ALL parameters except specific device-related parameters, use `OptOutParams()`.  In the example below, we will send ALL device-related parameters except: `locale`, `timezone`, and `build_id` parameters.
```objectivec
[TenjinSDK init:@"<API_KEY>"];

NSArray *optOutParams = @[@"country", @"timezone", @"language"];
[TenjinSDK optOutParams:optOutParams];

[TenjinSDK connect];
```

### <a id="device-related-parameters"></a> Device-Related Parameters

| Param  | Description | Reference |
| ------------- | ------------- | ------------- |
| ip\_address  | IP Address | |
| advertising\_id  | Device Advertising ID | [iOS][28] |
| developer\_device\_id | ID for Vendor | [iOS][29] |
| limit\_ad\_tracking  | limit ad tracking enabled | [iOS][30] |
| platform | platform  | iOS |
| iad | Apple Search Ad parameters | [iOS][31] |
| os\_version | operating system version | [iOS][32] |
| device | device name | [iOS (hw.machine)][33] |
| device\_model | device model | [iOS (hw.model)][34] |
| device\_model\_name | device machine  | [iOS (hw.model)][35] |
| device\_cpu | device cpu name | [iOS (hw.cputype)][36] |
| os\_version\_release | operating system version | [iOS][37] |
| build\_id | build ID | [iOS (kern.osversion)][38] |
| locale | device locale | [iOS][39] |
| country | locale country | [iOS][40] |
| timezone | timezone | [iOS][41] |


# <a id="purchase-events"></a>Purchase Events

Pass `(SKPaymentTransaction *) transaction` and `(NSData *)receipt` object, after the verification of the purchase, and then you can pass `SKPaymentTransactionStatePurchased` to Tenjin for the transaction which was purchased:
```objectivec
//Get the NSData receipt
NSURL *receiptURL = [[NSBundle mainBundle] appStoreReceiptURL];
NSData *receiptData = [NSData dataWithContentsOfURL:receiptURL];

//Pass the transaction and the receiptData to Tenjin
[TenjinSDK transaction: transaction andReceipt: receiptData];
```

**Disclaimer:** If you are implementing purchase events on Tenjin for the first time, make sure to verify the data with other tools you’re using before you start scaling up your user acquisition campaigns using purchase data.

## <a id="subscription-iap"></a> Subscription IAP

**IMPORTANT:** If you have subscription IAP, you will need to add your app's public key in the <a href="https://www.tenjin.io/dashboard/apps" target="_new"> Tenjin dashboard</a>. You can retrieve your iOS App-Specific Shared Secret from the <a href="https://itunesconnect.apple.com/WebObjects/iTunesConnect.woa/ra/ng/app/887212194/addons">iTunes Connect Console</a> \> Select your app \> Features \> In-App Purchases \> App-Specific Shared Secret.

**Kindly note that you are responsible to send a subscription transaction one time during each subscription interval (i.e., For example, for a monthly subscription, you will need to send us 1 transaction per month).**

In the example timeline below, a transaction event should only be sent at the "First Charge" and "Renewal" events. During the trial period, do not send Tenjin the transaction event.  Tenjin does not de-dupe duplicate transactions.

<img src="https://docs-assets.developer.apple.com/published/6631e50f32/110c0e3f-e0e3-4dbd-bc28-d8db4b28bd1c.png" />

For more information on subscriptions, please see: <a href="https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/StoreKitGuide/Chapters/Subscriptions.html">Apple documentation on Working with Subscriptions</a>

# <a id="custom-events"></a>Custom Events

**IMPORTANT: DO NOT SEND CUSTOM EVENTS BEFORE THE CONNECT/INITIALIZATION** event (above). The initialization must come before sending any custom events.

**IMPORTANT: Limit custom event names to less than 80 characters. Do not exceed 500 unique custom event names.**

You can also use the Tenjin SDK to pass a custom event:
- `sendEventWithName: (NSString *)eventName` and

You can use these to pass Tenjin custom interactions with your app to tie this to user level cost from each acquisition source that you use through Tenjin's platform. Here are some examples of usage:

```objectivec
//send a particular event for when someone swipes on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right"];

```

Custom events can also pass an `NSString` `eventValue`. Tenjin will use this `eventValue` as a count or sum for all custom events with the same `eventName`. The `eventValue` MUST BE AN INTEGER. If the `eventValue` is not an integer, we will not send the event.

# <a id="deferred-deeplink"></a>Deferred Deeplink

Tenjin supports the ability to direct users to a specific part of your app after a new attributed installation via Tenjin's campaign tracking URLs. You can utilize the `registerDeepLinkHandler` handler to access the deferred deeplink through `params[@"deferred_deeplink_url"]` that is passed to the Tenjin campaign tracking URLs. To test, you can follow the instructions found <a href="http://help.tenjin.io/t/how-do-i-use-and-test-deferred-deeplinks-with-my-campaigns/547">here</a>.

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

Below are the parameters, if available, that returned to the deferred deeplink callback:

| Parameter             | Description                                                      |
|-----------------------|------------------------------------------------------------------|
| advertising\_id        | IDFA of the device                                               |
| developer\_device\_id   | IDFV of the device                                               |
| ad\_network            | Ad Network of the campaign                                       |
| campaign\_id           | Tenjin campaign ID                                               |
| campaign\_name         | Tenjin campaign name                                             |
| site\_id               | Site ID of source app                                            |
| deferred\_deeplink\_url | The deferred deep-link of the campaign                           |
| clicked\_tenjin\_link   | Boolean representing if the device was tracked by Tenjin         |
| is\_first\_session      | Boolean representing if this is the first session for the device |


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
# <a id="server-to-server"></a>Server-to-server integration

Tenjin offers server-to-server integration. If you want to access to the documentation, please send email to support@tenjin.com.

# <a id="subversion"></a>App Subversion parameter for A/B Testing (requires DataVault)

If you are running A/B tests and want to report the differences, we can append a numeric value to your app version using the `appendAppSubversion` method.  For example, if your app version `1.0.1`, and set `appendAppSubversion: @8888`, it will report as `1.0.1.8888`.

This data will appear within DataVault, where you will be able to run reports using the app subversion values.

```objectivec
[TenjinSDK init:@"<API_KEY>"];
[TenjinSDK appendAppSubversion:@8888];
[TenjinSDK connect];
```

# <a id="ilrd"></a>Impression Level Ad Revenue Integration

Tenjin supports the ability to integrate with the Impression Level Ad Revenue (ILRD) feature from,
- AppLovin
- IronSource
- HyperBid
- AdMob
- TopOn

This feature allows you to receive events which correspond to your ad revenue that is affected by each advertisement show to a user. To enable this feature, follow the below instructions.

> *NOTE*: ILRD is a paid product, please contact your Tenjin account manager to discuss the price.

## <a id="applovin"></a>AppLovin Impression Level Ad Revenue Integration

> *NOTE,* Please ensure you have the latest AppLovin iOS SDK installed (\> 11.0.0)

```objectivec
[TenjinSDK init:@"TENJIN_API_KEY"];
[TenjinSDK subscribeAppLovinImpressions];

```

## <a id="ironsource"></a>IronSource Impression Level Ad Revenue Integration

> *NOTE*, Please ensure you have the latest IronSource iOS SDK installed (\> 7.1.14)

```objectivec
[TenjinSDK init:@"TENJIN_API_KEY"];
[TenjinSDK subscribeIronSourceImpressions];

```

## <a id="hyperbid"></a>HyperBid Impression Level Ad Revenue Integration

> *NOTE,* Please ensure you have the latest HyperBid iOS SDK installed (\> 5.7.79)

```objectivec
[TenjinSDK handleHyperBidILRD:(NSDictionary)adImpression];
```

## <a id="admob"></a>AdMob Impression Level Ad Revenue Integration

> *NOTE*, Please ensure you have the latest Google-Mobile-Ads-SDK iOS SDK installed (\> 8.10.0)

```objectivec
[TenjinSDK handleAdMobILRD:(GADBannerView)bannerView :(GADAdValue)value];
```

## <a id="topon"></a>TopOn Impression Level Ad Revenue Integration

> *NOTE*, Please ensure you have the latest AnyThinkiOS iOS SDK installed (\> 5.7.99)

```objectivec
[TenjinSDK handleTopOnILRD:(NSDictionary)adImpression];
```

## <a id="attributionInfo"></a>Attribution Info

```objectivec
[[TenjinSDK sharedInstance] getAttributionInfo:^(NSMutableDictionary *attributionInfo) {
    NSLog(@"TenjinSDK getAttributionInfo result: %@", attributionInfo);
}];    
```

[1]:	#sdk-integration
[2]:	#attrackingmanager
[3]:	#displayattprompt
[4]:	#configureusertrackdescription
[5]:	#skadnetwork-and-conversion-value
[6]:	#skadnetwork-and-ios15-plus-advertiser-postbacks
[7]:	#gdpr
[8]:	#device-related-parameters
[9]:	#purchase-events
[10]:	#subscription-iap
[11]:	#custom-events
[12]:	#deferred-deeplink
[13]:	#server-to-server
[14]:	#subversion
[15]:	#ilrd
[16]:	#applovin
[17]:	#ironsource
[18]:	#hyperbid
[19]:	#admob
[20]:	#topon
[21]:	https://github.com/tenjin/tenjin-ios-sdk/releases
[22]:	https://tenjin.io/dashboard/organizations
[23]:	https://github.com/tenjin/tenjin-ios-sdk-swift
[24]:	https://developer.apple.com/app-store/user-privacy-and-data-use/
[25]:	https://docs.tenjin.com/en/tracking/sk_adnetwork.html#cv
[26]:	https://developer.apple.com/documentation/storekit/skadnetwork/receiving_ad_attributions_and_postbacks
[27]:	https://developer.apple.com/documentation/storekit/skadnetwork/configuring_an_advertised_app
[28]:	https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614151-advertisingidentifier
[29]:	https://developer.apple.com/documentation/uikit/uidevice/1620059-identifierforvendor
[30]:	https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614148-isadvertisingtrackingenabled
[31]:	https://searchads.apple.com/advanced/help/measure-results/#attribution-api
[32]:	https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion
[33]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[34]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[35]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[36]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[37]:	https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion
[38]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[39]:	https://developer.apple.com/documentation/foundation/nslocalekey
[40]:	https://developer.apple.com/documentation/foundation/nslocalecountrycode
[41]:	https://developer.apple.com/documentation/foundation/nstimezone/1387209-localtimezone
[42]:	#attributionInfo

[image-1]:	https://github.com/tenjin/tenjin-ios-sdk/blob/master/assets/ios_link_binary.png?raw=true "dashboard"
[image-2]:	https://github.com/tenjin/tenjin-ios-sdk/raw/master/assets/ios_linker_flags.png?raw=true "dashboard"
[image-3]:	https://s3.amazonaws.com/tenjin-instructions/sdk_live_open_events.png
