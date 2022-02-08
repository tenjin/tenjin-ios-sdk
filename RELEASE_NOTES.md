v1.0.0
----
- First release to measure app opens and installs

v1.0.1
----
- Bundle requirements into `.a` lib
- Include custom events
- Fix bugs
- Include SDK Versioning

v1.0.2
----
- Include receipt validation => use StoreKit API to validate and pass transactions to Tenjin Server
- Standardize revenue event capture => Allow users to send revenue events manually (ProductID, Currency Locale, Quantity, Price). They can also send us a SKPaymentTransaction where we send our server the following on our own. Need to figure out a way to check and validate receipts.
- Change GET requests to POST

v1.1.0
----
- Add `device` parameter to request
- iAd attribution to pass `iad` and `iad_impression_ts` => requires developer to include iAd.framework

v1.1.1
----
- Update to build version 7.0

v1.1.2
----
- Update to build 6.0

v1.1.3
----
- Update settings to make iOS9 easier

v1.1.4
----
- Now compiles with bitcode enabled & embedded

v1.2.0
----
- Check to make sure eventValue for custom events is an integer

v1.3.0
----
- Pass `receipt` to server to validate transaction
- Deprecate just accepting SKPaymentTransaction. If you pass SKPaymentTransaction we will also require a receipt
- Pass `transaction_id` to server
- Refactor

v.1.3.1
----
- Allow manual transaction call for that accepts a `transaction_id` and `receipt` for receipt validation
- Set up to allow Unity to have receipt validation

v1.4.0
----
- Use SFSafariViewController in iOS9 to capture cookies for accurate web to app tracking. No longer require IP Address to match web to app fingerprinted installs
- DRY up device params methods
- Fix SDK Demo app

v1.4.1
----
- Fix SFSafariViewController with time delay to make cookie tracking more accurate

v1.4.2
----
- Add vendor ID

v1.4.3
----
- Remove deprecated iAd network code

v1.4.4
----
- Reduce view controller time for cookie tracking
- Ignore cookie tracking for iOS10 based on beta testing

v1.4.5
----
- Reduce view controller time to 0.5s

v1.4.6
----
- Reduce view controller time to 0.05s
- Add better comments to SDK methods

v1.4.7
----
- Go back to zero delay in cookie tracking for viewcontroller. Don't need to worry about deleting the cookie on app open.

v1.4.8
----
- Make OS version check compatible for versions < iOS8

v1.4.9
----
- Take out SFSafariViewController for tracking cookies -> Apple is not allowing it per section 5.1.1 (iv) https://developer.apple.com/app-store/review/guidelines/#data-collection-and-storage

v1.5.0
----
- Include Apple Search Ads attribution

v1.5.1
----
- Allow users to pass in base64 receipts for receipt validation on purchases

v1.5.2
----
- Allow developers to use bitcode for their apps

v1.5.3
----
- Update for most recent Apple API calls

v1.6.0
----
- Update connection URL logic to session HTTP logic for recent Apple SDK calls
- Deferred Deeplink URL logic (beta)

v1.7.0
----
- Allow developer to pass a deferred deeplink into Tenjin

v1.7.1
----
- Update for NSSession threading issues

v1.7.2
----
- Update SDK to always fire handler callback

v1.7.3
----
- Add retry logic for `getUser` if not 200/202 error

v1.7.4
----
- Add App Device User Agent params

v1.7.5
----
- Add GDPR Support

v1.7.6
----
- Update GDPR Support

v1.7.7
----
- Fix GDPR bug

v1.7.8
----
- Version bump for Cordova

v1.7.9
----
- Fix NSInvalidArgumentException bug

v1.8.2
----
- Add App Subversion method

v1.9.1
----
- Create getInstance() alternative to init() for Swift 5 support

v1.9.2
----
- Use circle ci to build and release

v1.10.1
---
- Integrate MoPub Impression Level Revenue

v1.10.2
---

- CI unification

v1.10.3
---

- New logger
- Bugfix for duplicate ILRD events under unity

v1.11.0
----
- Send wrapper sdk version prepended to sdk_version


v1.12.0
----
- Architecture redesign
- iOS 14 changes

v1.12.1
----
- Create wrapper for ATTracking requestTrackingAuthorizationWithCompletionHandler

v1.12.2
----
- Upgrade CI pipeline with XCode 12

v1.12.3
----
- Remove AppTrackingTransparency import. https://github.com/tenjin/ios-sdk/pull/120
- Update dependencies for sample app. https://github.com/tenjin/ios-sdk/pull/122
- Don't send tracking status for pre ios-14 device. https://github.com/tenjin/ios-sdk/pull/121

v1.12.4
----
- Fix memory bug https://github.com/tenjin/ios-sdk/pull/125

v1.12.5
----
- Remove unused methods https://adromance.atlassian.net/browse/TENJIN-7919

v1.12.6
----
- Apple Ads Attribution Token https://adromance.atlassian.net/browse/TENJIN-7382

v1.12.7
----
- Update Appcenter library version

v1.12.8
 ----
 - AppLovin Impression Level Ad Revenue
