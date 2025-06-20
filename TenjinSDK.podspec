Pod::Spec.new do |s|
  s.name         = "TenjinSDK"
  s.version      = "1.14.10"
  s.summary      = "TenjinSDK"
  s.description  = <<-DESC
                   Tenjin is a unique growth infrastructure platform that helps you streamline your mobile marketing.
                   DESC

  s.homepage     = "https://tenjin.com"
  s.license      = { :type => 'MIT', :text => <<-LICENSE
                      The MIT License (MIT)

                      Copyright (c) <year> <copyright holders>

                      Permission is hereby granted, free of charge, to any person obtaining a copy
                      of this software and associated documentation files (the "Software"), to deal
                      in the Software without restriction, including without limitation the rights
                      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                      copies of the Software, and to permit persons to whom the Software is
                      furnished to do so, subject to the following conditions:

                      The above copyright notice and this permission notice shall be included in
                      all copies or substantial portions of the Software.

                      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
                      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
                      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
                      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
                      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
                      THE SOFTWARE.
                      LICENSE
                  }

  s.author       = { "Tenjin" => "engineering@tenjin.com" }
  s.platform     = :ios, "9.0"

  s.source       = { :git => "https://github.com/tenjin/tenjin-ios-sdk.git", :tag => "#{s.version}" }
  s.source_files = "*.{h,m}"

  s.ios.vendored_frameworks = 'TenjinSDK.xcframework'
  s.preserve_paths = 'TenjinSDK.xcframework'
  s.vendored_frameworks = "TenjinSDK.xcframework"

  s.frameworks = "AdSupport", "AppTrackingTransparency", "iAd", "StoreKit"
  s.weak_frameworks = "AdServices"
  s.xcconfig = { "OTHER_LINKER_FLAGS" => "-ObjC -all_load", 'OTHER_LDFLAGS' => '-framework TenjinSDK' }
end
