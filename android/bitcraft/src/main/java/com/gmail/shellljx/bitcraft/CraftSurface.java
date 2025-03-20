package com.gmail.shellljx.bitcraft;

import android.graphics.SurfaceTexture;
import android.opengl.EGL14;
import android.opengl.EGLContext;
import android.view.Surface;

public class CraftSurface {

    public static CraftSurface FromSurfaceTexture(SurfaceTexture surfaceTexture) {
        return FromSurfaceTexture(surfaceTexture, EGL14.EGL_NO_CONTEXT);
    }

    public static CraftSurface FromSurfaceTexture(SurfaceTexture surfaceTexture, EGLContext shareContext) {
        if (surfaceTexture == null) {
            return null;
        }
        CraftSurface craftSurface = FromSurface(new Surface(surfaceTexture), shareContext);
        if (craftSurface != null) {
            craftSurface.needsReleaseSurface = true;
        }
        return craftSurface;
    }

    public static CraftSurface FromSurface(Surface surface, EGLContext shareContext) {
        if (surface == null) {
            return null;
        }
        long handle = 0;
        if (shareContext != null && shareContext != EGL14.EGL_NO_CONTEXT) {
            handle = shareContext.getNativeHandle();
        }
        long nativeSurface = SetupFromSurfaceWithGLContext(surface, handle);
        if (nativeSurface == 0) {
            return null;
        }
        CraftSurface craftSurface = new CraftSurface(nativeSurface);
        craftSurface.surface = surface;
        return craftSurface;
    }

    private CraftSurface(long nativeSurface) {
        this.nativeSurface = nativeSurface;
    }

    private Surface surface = null;
    private boolean needsReleaseSurface = false;

    public void release() {

    }

    private static native long SetupFromSurfaceWithGLContext(Surface surface, long shareContext);

    public native void updateSize();

    public native boolean clearAll();

    public native void freeCache();

    private native void nativeRelease();

    private static native void nativeInit();

    private native void nativeFinalize();

    @Override
    protected void finalize() throws Throwable {
        nativeFinalize();
    }

    static {
        System.loadLibrary("bitcraft");
        nativeInit();
    }

    long nativeSurface = 0;
}
