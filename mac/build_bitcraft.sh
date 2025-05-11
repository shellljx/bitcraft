#!/bin/bash -e
cd $(dirname $0)

function make_dir() {
  rm -rf $1
  mkdir -p $1
}

PLATFORM="mac"

node ../build_bitcraft -p $PLATFORM -o vendor/bitcraft/$PLATFORM

node ../build_vendor glfw -p $PLATFORM -o vendor/glfw/$PLATFORM

#make_dir vendor/glfw/$PLATFORM
cp -a ../third_party/out/glfw/$PLATFORM/include/* vendor/glfw/$PLATFORM
