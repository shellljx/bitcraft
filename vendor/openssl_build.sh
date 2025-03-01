#!/bin/bash

function buildMac() {
  make clean
  ./configure --release no-shared no-apps no-tests no-docs no-dso no-ssl2 no-ssl3 no-tls no-tls1_1 no-tls1_2 --prefix=$outdir/mac --openssldir=$outdir/mac
  make install
}

function buildAndroidArch {
  make clean
  ./configure "$1" --release no-shared no-apps no-tests no-docs no-dso no-ssl2 no-ssl3 no-tls no-tls1_1 no-tls1_2 --prefix="$outdir/android/$2" --openssldir="$outdir/android/$2"
  make install
}

function buildAndroid() {
  export ANDROID_NDK_ROOT="$ANDROID_NDK"
  export PATH=$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/darwin-x86_64/bin:$PATH

  buildAndroidArch android-arm armeabi-v7a
  buildAndroidArch android-arm64 arm64-v8a
  buildAndroidArch android-x86 x86
  buildAndroidArch android-x86_64 x86_64
}

echo "start build openssl $outdir}"
if [ $# -eq 0 ]; then
    echo "No arguments provided. Please specify one of the following: {mac|android}"
    exit 1
fi

CURRENT_SCRIPT_DIR="$1"
PLATFORM="$2"
ANDROID_NDK="$3"

outdir="$CURRENT_SCRIPT_DIR/../third_party/out/openssl"
#cd "$CURRENT_SCRIPT_DIR/../third_party/openssl" || exit 1

if [ "$PLATFORM" == "mac" ]; then
  echo "build mac openssl"
  buildMac
elif [ "$PLATFORM" == "android" ]; then
  echo "build android openssl"
  buildAndroid
fi