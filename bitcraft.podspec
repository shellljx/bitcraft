BITCRAFT_ROOT = __dir__

vendorNames = "zlib"
commonCFlags = ["-fvisibility=hidden -Wall -Wextra -Weffc++ -pedantic -Werror=return-type"]

if  ENV["PLATFORM"] == "mac"
  system("depsync mac")
  system("node build_vendor #{vendorNames} -o #{BITCRAFT_ROOT}/mac/Pods/bitcraft-vendor -p mac --xcframework")
else
  system("depsync ios")
  system("node build_vendor #{vendorNames} -o #{BITCRAFT_ROOT}/ios/Pods/bitcraft-vendor -p ios --xcframework")
end

Pod::Spec.new do |s|
  s.name     = 'bitcraft'
  s.version  = '1.0.0'
  s.ios.deployment_target   = '9.0'
  s.osx.deployment_target   = '10.13'
  s.summary  = 'The bitcraft library on iOS and macOS'
  s.homepage = 'https://github.com/shellljx/McProtocol'
  s.author   = { 'shell' => 'shellljx@gmail.com' }
  s.requires_arc = false
  s.source   = {
    :git => 'git@github.com:shellljx/McProtocol.git'
  }

  $source_files =   'src/base/**/*.{h,cpp}',
                    'src/base/**/*.{h,cc}',
                    'src/rendering/**/*.{h,cpp}',
                    'src/rendering/**/*.{h,cc}',
                    'src/platform/*.{h,cpp}'

  s.source_files = $source_files;

  s.compiler_flags = '-Wno-documentation'

  s.osx.public_header_files = 'src/platform/mac/*.h',
                              'src/platform/cocoa/*.h'
                              
  s.osx.source_files =  'src/platform/mac/**/*.{h,cpp,mm,m}',
                        'src/platform/cocoa/**/*.{h,cpp,mm,m}'
  s.osx.frameworks   = ['ApplicationServices', 'AGL', 'OpenGL', 'QuartzCore', 'Cocoa', 'Foundation', 'VideoToolbox', 'CoreMedia']
  s.osx.libraries = ["iconv", "c++"]
  s.osx.vendored_libraries = 'third_party/out/openssl/mac/lib/libssl.a',
                         'third_party/out/openssl/mac/lib/libcrypto.a'

  s.ios.public_header_files = 'src/platform/ios/*.h',
                              'src/platform/cocoa/*.h'
                              
  s.ios.source_files =  'src/platform/ios/*.{h,cpp,mm,m}',
                          'src/platform/ios/private/*.{h,cpp,mm,m}',
                          'src/platform/cocoa/**/*.{h,cpp,mm,m}'

  s.ios.frameworks   = ['UIKit', 'CoreFoundation', 'QuartzCore', 'CoreGraphics', 'CoreText', 'OpenGLES', 'VideoToolbox', 'CoreMedia']
  s.ios.libraries = ["iconv","c++"]
  s.ios.vendored_libraries = 'third_party/out/openssl/mac/lib/libssl.a',
                         'third_party/out/openssl/mac/lib/libcrypto.a'

  armv7CFlags = commonCFlags + ["-fno-aligned-allocation"]
  s.xcconfig = {'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17','CLANG_CXX_LIBRARY' => 'libc++',"HEADER_SEARCH_PATHS" => "#{BITCRAFT_ROOT}/src #{BITCRAFT_ROOT}/third_party/asio/asio/include #{BITCRAFT_ROOT}/third_party/openssl/include #{BITCRAFT_ROOT}/third_party/stb #{BITCRAFT_ROOT}/third_party/rectpack2D/src #{BITCRAFT_ROOT}/third_party/glm #{BITCRAFT_ROOT}/third_party/json/include #{BITCRAFT_ROOT}/third_party/zlib"}
  s.ios.xcconfig = {"OTHER_CFLAGS" => commonCFlags.join(" "),"OTHER_CFLAGS[sdk=iphoneos*][arch=armv7]" => armv7CFlags.join(" "),"EXPORTED_SYMBOLS_FILE" => "${PODS_ROOT}/../bitcraft.lds","OTHER_LDFLAGS" => "-w","VALIDATE_WORKSPACE_SKIPPED_SDK_FRAMEWORKS" => "OpenGLES"}
  s.osx.xcconfig = {"OTHER_CFLAGS" => commonCFlags.join(" ")}
  s.ios.vendored_frameworks = 'ios/Pods/bitcraft-vendor/libbitcraft-vendor.xcframework'
  s.osx.vendored_frameworks = 'mac/Pods/bitcraft-vendor/libbitcraft-vendor.xcframework'
end
