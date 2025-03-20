package com.gmail.shellljx.bitcraft

import android.content.Context
import android.graphics.SurfaceTexture
import android.os.Build
import android.util.AttributeSet
import android.view.TextureView

class CraftView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
) : TextureView(context, attrs), TextureView.SurfaceTextureListener {

    private val craftClient = BitCraftClient(111)
    private var craftSurface: CraftSurface? = null
    private var isSurfaceDestroyed = false

    init {
        isOpaque = false
        surfaceTextureListener = this
    }

    override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
        craftSurface?.release()
        craftSurface = null
        craftSurface = CraftSurface.FromSurfaceTexture(surface)
        craftClient.setSurface(craftSurface)
        isSurfaceDestroyed = false
        craftSurface?.clearAll()
        flush()
    }

    override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {
        craftSurface?.let {
            it.updateSize()
            it.clearAll()
            it.freeCache()
            flush()
        }
    }

    override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
        isSurfaceDestroyed = true
        craftClient.surface = null
        craftSurface?.freeCache()
        craftSurface?.release()
        craftSurface = null
        return true
    }

    override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {
    }

    fun flush() {
        updateViewInternal()
    }

    private fun updateViewInternal() {
        if (!isAttachedToWindow) return
        if (isSurfaceDestroyed) return
        if (craftClient.surface == null) return
        val changed = craftClient.flush()
        if (changed) {
            post {
                isOpaque = !isOpaque
                isOpaque = !isOpaque
            }
        }
    }
}