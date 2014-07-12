Tenjin iOS SDK
==============

Xcode integration instructions:
-------------------------------
1. Download and unzip the .zip file from https://github.com/Ordinance/tenjin-ios-sdk/archive/master.zip
2. Drag and drop `libTenjinSDKUniversal.a` and `TenjinSDK.h` to your project (most people stick this in a folder called `TenjinSDK`)
3. Add the `AdSupport.framework` by clicking on your project -> "Build Phases" -> "Link Binary With Libraries" -> "+"
4. Include the linker flags `-ObjC` and `-all_load` under your project -> "Build Settings" -> "Linking"
4. Go to your AppDelegate file, by default `AppDelegate.m`, and `#import "TenjinSDK.h"`
5. Get your `API_KEY` from cfarm@tenjin.io
6. In your `didFinishLaunchingWithOptions` method add: `[TenjinSDK sharedInstanceWithToken:<API_KEY>];`

Here's an example of what your integration should look like in your `AppDelegate.m` file:

```
#import "TenjinSDK.h"

@implementation TJNAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [TenjinSDK sharedInstanceWithToken:@"X6SJQRU3UE3PXWJDEQB2S17GE7YZ3S08"];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
}
```
