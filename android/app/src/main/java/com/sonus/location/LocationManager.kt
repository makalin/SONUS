package com.sonus.location

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.os.Bundle
import androidx.core.app.ActivityCompat
import com.sonus.SonusApp
import com.sonus.audio.AudioManager

class LocationManager(private val context: Context) {
    private val locationManager = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
    private val audioManager = SonusApp.instance.audioManager
    private var locationListener: LocationListener? = null

    fun startLocationUpdates(onLocationUpdate: (Location) -> Unit) {
        if (ActivityCompat.checkSelfPermission(
                context,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            return
        }

        locationListener = object : LocationListener {
            override fun onLocationChanged(location: Location) {
                onLocationUpdate(location)
            }

            override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {}
            override fun onProviderEnabled(provider: String) {}
            override fun onProviderDisabled(provider: String) {}
        }

        locationManager.requestLocationUpdates(
            LocationManager.GPS_PROVIDER,
            1000L, // 1 second
            1f, // 1 meter
            locationListener!!
        )
    }

    fun stopLocationUpdates() {
        locationListener?.let {
            locationManager.removeUpdates(it)
            locationListener = null
        }
    }

    fun broadcastLocation(location: Location) {
        val audioData = audioManager.encodeGPS(location.latitude, location.longitude)
        audioManager.playAudio(audioData)
    }

    fun getLastKnownLocation(): Location? {
        if (ActivityCompat.checkSelfPermission(
                context,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            return null
        }
        return locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER)
    }
} 