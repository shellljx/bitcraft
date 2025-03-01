package com.gmail.shellljx.bitcraft;

public class MinecraftProtocol {
    private long nativeContext = 0;

    static {
        System.loadLibrary("bitcraft");
    }
}
