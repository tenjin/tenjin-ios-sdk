Tenjin iOS SDK (iOS 6.0+)
==============

Tenjin install/session integration instructions:
-------------------------------
1. Download and unzip the .zip file from https://github.com/Ordinance/tenjin-ios-sdk/archive/master.zip
2. Drag and drop `libTenjinSDKUniversal.a` and `TenjinSDK.h` to your project (most people stick this in a folder called `TenjinSDK`) 
3. Add `AdSupport.framework` by clicking on your project -> "Build Phases" -> "Link Binary With Libraries" -> "+"
4. Include the linker flags `-ObjC` and `-all_load` under your project -> "Build Settings" -> "Linking" -> "Other Linker Flags"
4. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`
5. Get your `API_KEY` from https://tenjin.io/dashboard/organizations
6. In your `didFinishLaunchingWithOptions` method add: `[TenjinSDK sharedInstanceWithToken:@"<API_KEY>"];`

Here's an example of what your integration should look like in your `AppDelegate.m` file:

```
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TenjinSDK sharedInstanceWithToken:@"<API_KEY>"];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
}
```

Tenjin custom event integration instructions:
--------
There are two handlers that you can use to pass custom events: `sendEventWithName: (NSString *)eventName` and `sendEventWithName:(NSString*)eventName andEventValue:(NSString*)eventValue`.

You can use these to pass Tenjin custom interactions with your app to tie this to user level cost from each acquisition source that you use through Tenjin's platform. Here are some examples of usage:

```
//send a revenue event with a value when a user purchases an item
[TenjinSDK sendEventWithName:@"revenue" andEventValue:@"0.99"];

//send a particular event for when someone swipes on a part of your app
[TenjinSDK sendEventWithName:@"swipe_right"];

```
