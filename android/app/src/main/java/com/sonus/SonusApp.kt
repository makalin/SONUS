package com.sonus

import android.app.Application
import android.content.Context
import com.sonus.audio.AudioManager
import com.sonus.location.LocationManager
import com.sonus.preferences.PreferencesManager

class SonusApp : Application() {
    companion object {
        lateinit var instance: SonusApp
            private set
    }

    lateinit var audioManager: AudioManager
    lateinit var locationManager: LocationManager
    lateinit var preferencesManager: PreferencesManager

    override fun onCreate() {
        super.onCreate()
        instance = this
        
        // Initialize managers
        audioManager = AudioManager(this)
        locationManager = LocationManager(this)
        preferencesManager = PreferencesManager(this)
    }
} 