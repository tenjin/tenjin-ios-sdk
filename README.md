# Summary

The Tenjin iOS SDK allows users to track events and installs in their iOS apps. To learn more about Tenjin and our product offering, please visit https://www.tenjin.com.

- Please see our <a href="https://github.com/tenjin/tenjin-ios-sdk/blob/master/RELEASE_NOTES.md">Release Notes</a> to see detailed version history.
- For Unity-specific instructions, please visit https://github.com/tenjin/tenjin-unity-sdk.
- For any issues or support, please contact: support@tenjin.com

### Notes

  - Xcode 13 requirement, if you’re using iOS SDK v1.12.17 and higher.
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
        - [Opt in/Opt out using CMP consents][41]
	- [Device-Related Parameters][8]
- [Purchase Events][9]
	- [Subscription IAP][10]
- [Custom Events][11]
- [Deferred Deeplink][12]
- [Server-to-server integration][13]
- [App Subversion][14]
- [Impression Level Ad Revenue Integration][15]
- [Attribution Info][16]
- [Customer User ID][17]
- [Analytics Installation ID][40]
- [Google DMA parameters][42]
- [Retry/cache events and IAP][39]


# <a id="sdk-integration"></a> SDK Integration

## CocoaPods
If you use pods, add `pod 'TenjinSDK'` to your `Podfile` then run `pod install` and skip to step 4 under Steps for Objective-C projects.

## Swift Package Manager
If you use SPM, add Tenjin’s SDK package through Xcode with this repository [here](https://github.com/tenjin/tenjin-ios-spm) and skip to step 4 under Steps for Swift projects.

1. Download the latest SDK release [here][38].

2. Drag `TenjinSDK.xcframework` and `TenjinSDK.h` to your project under build phases -> "Link Binary With Libraries".

3. Include the linker flags `-ObjC` under your Build Settings
![Dashboard][image-2]

## Steps for Objective-C projects

4. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`.

5. Get your `SDK_KEY` from your app page. Note: `SDK_KEY` is unique for each of your app. You can create up to 3 keys for the same app.
   ![Dashboard][image-4]

6. In your `didFinishLaunchingWithOptions` method add:
    ```objectivec
    [TenjinSDK initialize:@"<SDK_KEY>"];
    [TenjinSDK connect];
    ```

7. To enable Tenjin iOS SDK debug logs add:
    ```objectivec
      [TenjinSDK debugLogs];
    ```

    Here's an example of what your integration in Objective-C projects should look like in your `AppDelegate.m` file:

    ```objectivec
    #import "TenjinSDK.h"
    
    @implementation TJNAppDelegate
    
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
    {
        [TenjinSDK initialize:@"<SDK_KEY>"];
        [TenjinSDK connect];
    
        //All your other stuff
        ...
    }
    ```

## Steps for Swift projects

4. Add Objective-C Bridging Header file for swift projects,
    <ol type="a">
      <li>Create a header file
        <ol type="i">
          <li>File -> New -> File -> “Sources”</li>
          <li>Choose “Header” File - > Click Next</li>
          <li>The header file name should “YourProjectName-Bridging-Header” -> Under “Targets” -> Select the app target -> Click "Next"</li>
           </li>
        </ol>
      </li>
      <li>In the header file - “YourProjectName-Bridging-Header.h”
        <ol type="i">
          <li>Add - `#import "TenjinSDK.h"`</li>
        </ol>
      </li>
      <li>Go to the app target and under “Build Settings”
        <ol type="i">
          <li>Go to the section “Swift Compiler - General”</li>
          <li>Go to the sub-section “Objective-C Bridging Header” and drag the header file - “YourProjectName-Bridging-Header.h” to the field.</li>
        </ol>
      </li>
    </ol>

6. Get your `SDK_KEY` from your app page.

7. In your `didFinishLaunchingWithOptions` method add:
    ```swift
    TenjinSDK.getInstance("<SDK_KEY>")
    TenjinSDK.connect()
    ```
    If you are using Swift 5, use the `getInstance()` method instead of `init()`.  See our [sample Swift app][19].


9. To enable Tenjin iOS SDK debug logs add:
    ```swift
      TenjinSDK.debugLogs();
    ```

    Here's an example of what your integration in Swift projects should look like in your `AppDelegate.swift` file:

    ```swift
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        TenjinSDK.getInstance("<SDK_KEY>")
        TenjinSDK.connect() 
        return true
    }
    ```

> [!NOTE]
> Please ensure you implement this code on every `didFinishLaunchingWithOptions`, not only on the first app open of the app. If we notice that you don't follow our recommendation, we can't give you the proper support or your account might be under suspension.

In the step 7, you can also try alternate initialization to handle deep links from other services. If you use other services to produce deferred deep links, you can pass Tenjin those deep links to handle the attribution logic with your Tenjin enabled deep links.

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

    [TenjinSDK initialize:@"<SDK_KEY>"];

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

    [TenjinSDK initialize:@"<SDK_KEY>"];

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

> [!NOTE]
> You must implement the permission request before serving ads in your game.

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

> [!NOTE]
> Apple provides specific [app store guidelines][20] that define acceptable use and messaging for all end-user facing privacy-related features. Tenjin does not provide legal advice. Therefore, the information on this page is not a substitute for seeking your own legal counsel to determine the legal requirements of your business and processes, and how to address them.

## <a id="skadnetwork-and-conversion-value"></a> SKAdNetwork and Conversion value

As part of <a href="https://developer.apple.com/documentation/storekit/skadnetwork">SKAdNetwork</a>, we created a wrapper method for <a href="https://developer.apple.com/documentation/storekit/skadnetwork/3919928-updatepostbackconversionvalue">`updatePostbackConversionValue(_:)`</a>.
Our method will register the equivalent SKAdNetwork methods and also send the conversion values to our servers.

`updatePostbackConversionValue(\_:)` 6 bit value should correspond to the in-app event and shouldn’t be entered as binary representation but 0-63 integer. Please refer to [this][21] page for how to implement conversion values.

As of iOS 16.1, which supports SKAdNetwork 4.0, you can now send `coarseValue` (String, with possible variants being "low", "medium" or "high") and `lockWindow` (Boolean) as parameters on the update postback method:

`updatePostbackConversionValue(_ conversionValue: Integer, coarseValue: String)`

`updatePostbackConversionValue(_ conversionValue: Integer, coarseValue: String, lockWindow: Bool)`

-   For iOS version 16.1+ which supports SKAdNetwork 4.0, you can call this method as many times as you want and can make the conversion value lower or higher than the previous value.
    
-   For iOS versions lower than 16.1 supporting SKAdnetWork versions lower than 4.0, you can call this method and our SDK will automatically detect the iOS version and update `conversionValue` only.

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TenjinSDK initialize:@"<SDK_KEY>"];
    [TenjinSDK connect];

    //
    // This will call [SKAdNetwork updatePostbackConversionValue: <YOUR 6 bit value>]
    // and also send conversion value to our servers.
    //
    // You will need to use a value between 0-63 for <YOUR 6 bit value>.
    //
    [TenjinSDK updatePostbackConversionValue: <YOUR 6 bit value>];
    
    // For iOS 16.1+ (SKAN 4.0)

    [TenjinSDK updatePostbackConversionValue: <YOUR 6 bit value> coarseValue:@"medium"];

    [TenjinSDK updatePostbackConversionValue: <YOUR 6 bit value> coarseValue:@"medium" lockWindow:true];

}
}
```

### <a id="skadnetwork-and-ios15-plus-advertiser-postbacks"></a> SKAdNetwork and iOS 15+ Advertiser Postbacks

To specify Tenjin as the destination for your [SK Ad Network postbacks][22], do the following:

1. Select `Info.plist` in the Project navigator in Xcode.
2. Click the Add button (+) beside a key in the property list editor and press Return.
3. Type the key name `NSAdvertisingAttributionReportEndpoint`.
4. Choose String from the pop-up menu in the Type column.
5. Enter `https://tenjin-skan.com`

These steps are an adaption from Apple's instructions at [https://developer.apple.com/documentation/storekit/skadnetwork/configuring\_an\_advertised\_app][23].

## <a id="gdpr"></a> GDPR

As part of GDPR compliance, with Tenjin's SDK you can opt-in, opt-out devices/users, or select which specific device-related params to opt-in or opt-out.  `OptOut()` will not send any API requests to Tenjin, and we will not process any events.

To opt-in/opt-out:

```objectivec
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{

  [TenjinSDK initialize:@"<SDK_KEY>"];

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

If you intend to use Google Ads, you will also need to add: `platform`, `os_version`, `app_version`, `locale`, `device_model`, and `build_id`.

If you want to only get specific device-related parameters, use `OptInParams()`. In example below, we will only these device-related parameters: `ip_address`, `advertising_id`, `developer_device_id`, `limit_ad_tracking`, and `iad`:

```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];

NSArray *optInParams = @[@"ip_address", @"advertising_id", @"developer_device_id", @"limit_ad_tracking", @"iad"];
[TenjinSDK optInParams:optInParams];

[TenjinSDK connect];
```

If you want to send ALL parameters except specific device-related parameters, use `OptOutParams()`.  In the example below, we will send ALL device-related parameters except: `locale`, `timezone`, and `build_id` parameters.
```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];

NSArray *optOutParams = @[@"country", @"timezone", @"language"];
[TenjinSDK optOutParams:optOutParams];

[TenjinSDK connect];
```

### <a id="optin-cmp"></a>Opt in/out using CMP
You can automatically opt in or opt out using your CMP consents (purpose 1) which are already saved in the user's device. The method returns a boolean to let you know if it's opted in or out.

`optInOutUsingCMP()`

```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];
optInOut = [TenjinSDK optInOutUsingCMP]; 
```

### <a id="device-related-parameters"></a> Device-Related Parameters

| Param  | Description | Reference |
| ------------- | ------------- | ------------- |
| ip\_address  | IP Address | |
| advertising\_id  | Device Advertising ID | [iOS][24] |
| developer\_device\_id | ID for Vendor | [iOS][25] |
| limit\_ad\_tracking  | limit ad tracking enabled | [iOS][26] |
| platform | platform  | iOS |
| iad | Apple Search Ad parameters | [iOS][27] |
| os\_version | operating system version | [iOS][28] |
| device | device name | [iOS (hw.machine)][29] |
| device\_model | device model | [iOS (hw.model)][30] |
| device\_model\_name | device machine  | [iOS (hw.model)][31] |
| device\_cpu | device cpu name | [iOS (hw.cputype)][32] |
| os\_version\_release | operating system version | [iOS][33] |
| build\_id | build ID | [iOS (kern.osversion)][34] |
| locale | device locale | [iOS][35] |
| country | locale country | [iOS][36] |
| timezone | timezone | [iOS][37] |

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

:warning: **(Flexible App Store Commission setup)**

Choose between 15% and 30% App Store’s revenue commission via our new setup. The steps are -
* Go to CONFIGURE --> Apps
* Click on the app you want to change it for
* Under the ‘App Store Commission’ section click ‘Edit’
* Choose 30% or 15% as your desired app store commission.
* Select the start date and end date (Or you can keep the end date blank if you dont want an end date)
* Click Save (note: the 15% commission can be applied only to dates moving forward and not historical dates. So please set the start date from the date you make the change and forward)

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

```objectivec
//send a particular event for when someone swipes and an event value on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right" andEventValue:@"1"];
```

# <a id="server-to-server"></a>Server-to-server integration

Tenjin offers server-to-server integration. If you want to access to the documentation, please send email to support@tenjin.com.

# <a id="subversion"></a>App Subversion parameter for A/B Testing (requires DataVault)

If you are running A/B tests and want to report the differences, we can append a numeric value to your app version using the `appendAppSubversion` method.  For example, if your app version `1.0.1`, and set `appendAppSubversion: @8888`, it will report as `1.0.1.8888`.

This data will appear within DataVault, where you will be able to run reports using the app subversion values.

```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];
[TenjinSDK appendAppSubversion:@8888];
[TenjinSDK connect];
```

# <a id="ilrd"></a>Impression Level Ad Revenue Integration

Tenjin supports the ability to integrate with the Impression Level Ad Revenue (ILRD) feature from,
- AppLovin
- Unity LevelPlay
- HyperBid
- AdMob
- TopOn
- CAS
- TradPlus

This feature allows you to receive events which correspond to your ad revenue that is affected by each advertisement show to a user. To enable this feature, follow the below instructions.

> [!WARNING]
> ILRD is a paid feature, so please contact your Tenjin account manager to discuss the price at first before sending ILRD events.

# <a id="attributionInfo"></a>Live Ops Campaigns

Tenjin supports retrieving of attributes, which are required for developers to get analytics installation id (previously known as tenjin reference id). This parameter can be used when there is no advertising id.

> [!WARNING]
> LiveOps Campaigns is a paid feature, so please contact your Tenjin account manager if you are interested in.

# <a id="customer-user-id"></a>Customer User ID
You can set and get customer user id to send as a parameter on events.

`setCustomerUserId(userId: "user_id")`

`getCustomerUserId()`

```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];
[TenjinSDK setCustomerUserId:@"user_id"];
userId = [TenjinSDK getCustomerUserId]; 
```

# <a id="analytics-id"></a>Analytics Installation ID
You can get the analytics id which is generated randomly and saved in the local storage of the device.

`getAnalyticsInstallationId()`

```objectivec
[TenjinSDK initialize:@"<SDK_KEY>"];
analyticsId = [TenjinSDK getAnalyticsInstallationId]; 
```

# <a id="google-dma"></a>Google DMA parameters
If you already have a CMP integrated, Google DMA parameters will be automatically collected by the Tenjin SDK. There’s nothing to implement in the Tenjin SDK if you have a CMP integrated.
If you want to override your CMP, or simply want to build your own consent mechanisms, you can use the following:

`setGoogleDMAParametersWithAdPersonalization(bool, bool)`

```objectivec
[[TeninSDK sharedInstance] setGoogleDMAParametersWithAdPersonalization:adPersonalization adUserData:adUserData]; 
```
To explicitly manage the collection of Google DMA parameters, you have the flexibility to opt in or opt out at any time. While the default setting is to opt in, you can easily adjust your preferences using the optInGoogleDMA or optOutGoogleDMA methods, ensuring full control over your data privacy settings:

```objectivec
[[TeninSDK sharedInstance] optInGoogleDMA]; 
[[TeninSDK sharedInstance] optOutGoogleDMA]; 
```

# <a id="retry-cache"></a>Retry/cache of events/IAP
You can enable/disable retrying and caching events and IAP when requests fail or users don't have internet connection. These events will be sent after a new event has been added to the queue and user has recovered connection.

`setCacheEventSetting(true)`

```objectivec
[TenjinSDK setCacheEventSetting:true];
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
[16]:	#attributionInfo
[17]:   #customer-user-id
[18]:	https://tenjin.io/dashboard/organizations
[19]:	https://github.com/tenjin/tenjin-ios-sdk-swift-demo
[20]:	https://developer.apple.com/app-store/user-privacy-and-data-use/
[21]:	https://docs.tenjin.com/en/tracking/sk_adnetwork.html#cv
[22]:	https://developer.apple.com/documentation/storekit/skadnetwork/receiving_ad_attributions_and_postbacks
[23]:	https://developer.apple.com/documentation/storekit/skadnetwork/configuring_an_advertised_app
[24]:	https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614151-advertisingidentifier
[25]:	https://developer.apple.com/documentation/uikit/uidevice/1620059-identifierforvendor
[26]:	https://developer.apple.com/documentation/adsupport/asidentifiermanager/1614148-isadvertisingtrackingenabled
[27]:	https://searchads.apple.com/advanced/help/measure-results/#attribution-api
[28]:	https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion
[29]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[30]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[31]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[32]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[33]:	https://developer.apple.com/documentation/uikit/uidevice/1620043-systemversion
[34]:	https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/sysctl.3.html
[35]:	https://developer.apple.com/documentation/foundation/nslocalekey
[36]:	https://developer.apple.com/documentation/foundation/nslocalecountrycode
[37]:	https://developer.apple.com/documentation/foundation/nstimezone/1387209-localtimezone
[38]:    https://github.com/tenjin/tenjin-ios-sdk/releases
[39]: #retry-cache
[40]: #analytics-id
[41]: #optin-cmp
[42]: #google-dma
[image-1]:	https://github.com/tenjin/tenjin-ios-sdk/blob/master/assets/ios_link_binary.png?raw=true "dashboard"
[image-2]:	https://github.com/tenjin/tenjin-ios-sdk/raw/master/assets/ios_linker_flags.png?raw=true "dashboard"
[image-3]:	https://s3.amazonaws.com/tenjin-instructions/sdk_live_open_events.png
[image-4]:	https://s3.amazonaws.com/tenjin-instructions/app_api_key.png
