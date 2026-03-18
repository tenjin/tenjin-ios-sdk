// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "TenjinSDK",
    products: [
        .library(
            name: "TenjinSDK",
            targets: ["TenjinSDK"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(name: "TenjinSDK",
                      path: "./TenjinSDK.xcframework")
    ]
)
