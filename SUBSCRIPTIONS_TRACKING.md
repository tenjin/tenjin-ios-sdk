# Tenjin – iOS Subscription Tracking

Track subscription purchases with Tenjin for server-side verification and attribution.

> **Subscription tracking is opt-in.** Connecting/initializing the SDK does **not** automatically capture subscription or purchase events. You must explicitly call one of the methods below from your StoreKit 2 purchase-handling code.
>
> **Troubleshooting:** if general events (session, custom events, etc.) are arriving on the dashboard but subscription events are not, this is the most common cause. Check that one of the methods below is actually being called at purchase time.

## Methods

### `subscription(withProductName:...)` — Manual Parameters

Pass all SK2 transaction data manually. Use this when your IAP implementation gives you direct access to StoreKit 2 transaction details.

```swift
TenjinSDK.subscription(
    withProductName: String,         // Product ID
    andCurrencyCode: String,         // ISO 4217 currency code (e.g., "USD")
    andUnitPrice: NSDecimalNumber,   // Price (e.g., 9.99)
    andTransactionId: String,        // SK2 transaction ID
    andOriginalTransactionId: String,// Original transaction ID (for renewals)
    andBase64Receipt: String,        // JWS signed transaction token
    andSKTransaction: String         // SK2 transaction JSON representation
)
```

### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `productName` | `String` | Product identifier |
| `currencyCode` | `String` | ISO 4217 currency code (e.g., "USD") |
| `unitPrice` | `NSDecimalNumber` | Price (e.g., 9.99) |
| `transactionId` | `String` | Transaction ID from StoreKit 2 |
| `originalTransactionId` | `String` | Original transaction ID (for renewals) |
| `receipt` | `String` | JWS signed transaction token |
| `skTransaction` | `String` | StoreKit 2 transaction JSON representation |

---

### `subscriptionWithStoreKit(forProductId:...)` — Native SK2 Fetch (iOS 16+)

Fetches the latest StoreKit 2 transaction for a product and sends it to Tenjin in a single call. No SK2 data needs to be extracted manually. This is the recommended approach when your IAP library (e.g., RevenueCat, Adapty, Qonversion) doesn't expose SK2 transaction data.

```swift
TenjinSDK.subscriptionWithStoreKit(
    forProductId: String,            // Product ID
    andCurrencyCode: String,         // ISO 4217 currency code (e.g., "USD")
    andUnitPrice: NSDecimalNumber    // Price (e.g., 9.99)
)
```

> **Note:** Requires iOS 16.0+.

---

### `TenjinSDK.purchasesManager().subscription(_:)` — Direct SK2 Transaction

If you already have a StoreKit 2 `Transaction` object, you can pass it directly to the Tenjin purchases manager. This is the most straightforward approach for native StoreKit 2 implementations.

```swift
if #available(iOS 16.0, *) {
    TenjinSDK.purchasesManager().subscription(transaction)
}
```

---

## Using StoreKit 2 (Direct Integration)

### Handling Purchases

```swift
import StoreKit

func handlePurchase(_ result: VerificationResult<Transaction>) async {
    switch result {
    case .verified(let transaction):
        if transaction.productType == .autoRenewable ||
           transaction.productType == .nonRenewable {
            if #available(iOS 16.0, *) {
                TenjinSDK.purchasesManager().subscription(transaction)
            }
        }

        await transaction.finish()

    case .unverified(_, let error):
        print("Transaction verification failed: \(error)")
    }
}
```

### Observing Transaction Updates

```swift
func observeTransactionUpdates() {
    Task.detached {
        for await result in Transaction.updates {
            if case .verified(let transaction) = result {
                if transaction.productType == .autoRenewable ||
                   transaction.productType == .nonRenewable {
                    if #available(iOS 16.0, *) {
                        TenjinSDK.purchasesManager().subscription(transaction)
                    }
                }
            }
        }
    }
}
```

---
