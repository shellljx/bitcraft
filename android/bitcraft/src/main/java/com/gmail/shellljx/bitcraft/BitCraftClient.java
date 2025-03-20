package com.gmail.shellljx.bitcraft;

public class BitCraftClient {

    public BitCraftClient(int version) {
        nativeSetup(version);
    }

    public void setSurface(CraftSurface surface) {
        this.craftSurface = surface;
        if (surface == null) {
            nativeSetSurface(0);
        } else {
            nativeSetSurface(surface.nativeSurface);
        }
    }

    public boolean flush() {
        return flushAndFenceSync();
    }

    public CraftSurface getSurface() {
        return craftSurface;
    }

    private native boolean flushAndFenceSync();

    private native void nativeSetSurface(long surface);

    public void release() {
        nativeRelease();
    }

    private native final void nativeRelease();

    protected void finalize() {
        nativeFinalize();
    }

    private native void nativeFinalize();

    private native final void nativeSetup(int version);

    private static native void nativeInit();

    static {
        System.loadLibrary("bitcraft");
        nativeInit();
    }

    private CraftSurface craftSurface;
    private long nativeContext = 0;
}
