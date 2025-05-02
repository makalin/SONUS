# Android Implementation Guide

## Overview
This document provides detailed information about the Android implementation of the SONUS application.

## Project Structure
```
android/
├── app/
│   ├── src/
│   │   ├── main/
│   │   │   ├── java/
│   │   │   │   └── com/
│   │   │   │       └── sonus/
│   │   │   │           ├── SonusApp.kt
│   │   │   │           ├── audio/
│   │   │   │           │   └── AudioManager.kt
│   │   │   │           └── location/
│   │   │   │               └── LocationManager.kt
│   │   │   └── AndroidManifest.xml
│   ├── build.gradle
└── build.gradle
```

## Dependencies
- Kotlin 1.8.0
- Android SDK 33
- AndroidX Libraries
- Google Play Services Location
- Dexter (Permissions)

## Implementation Details

### AudioManager
The `AudioManager` class handles all audio-related operations:

```kotlin
class AudioManager(private val context: Context) {
    private val core = SonusCore()
    private var audioRecord: AudioRecord? = null
    private var audioTrack: AudioTrack? = null
    
    companion object {
        private const val SAMPLE_RATE = 44100
        private const val CHANNEL_CONFIG = AudioFormat.CHANNEL_IN_MONO
        private const val AUDIO_FORMAT = AudioFormat.ENCODING_PCM_FLOAT
        private const val BUFFER_SIZE = 4096
    }
    
    // Methods for recording, playback, and signal encoding
}
```

Key features:
- Real-time audio recording and playback
- 32-bit float PCM format
- Configurable buffer size
- Thread-safe operations

### LocationManager
The `LocationManager` class handles location services:

```kotlin
class LocationManager(private val context: Context) {
    private val locationManager = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
    private val audioManager = SonusApp.instance.audioManager
    
    // Methods for location tracking and broadcasting
}
```

Key features:
- GPS-based location tracking
- 1-meter accuracy
- Permission handling
- Location broadcasting via audio

## Permissions
Required permissions in AndroidManifest.xml:
```xml
<uses-permission android:name="android.permission.RECORD_AUDIO" />
<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
<uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
```

## Build Configuration
The project uses Gradle for build configuration:

```gradle
android {
    compileSdkVersion 33
    defaultConfig {
        minSdkVersion 21
        targetSdkVersion 33
    }
}
```

## Best Practices
1. **Memory Management**
   - Release audio resources when not in use
   - Use weak references for callbacks
   - Implement proper cleanup in onDestroy

2. **Performance**
   - Use appropriate buffer sizes
   - Implement background processing
   - Optimize location updates

3. **Error Handling**
   - Check for null references
   - Handle permission denials
   - Implement proper exception handling

## Testing
1. **Audio Testing**
   - Test recording quality
   - Verify signal encoding/decoding
   - Check playback functionality

2. **Location Testing**
   - Test GPS accuracy
   - Verify location updates
   - Test permission handling

## Troubleshooting
Common issues and solutions:

1. **Audio Recording Issues**
   - Check microphone permissions
   - Verify audio format compatibility
   - Ensure proper buffer size

2. **Location Issues**
   - Verify GPS is enabled
   - Check location permissions
   - Test in different environments

## Security Considerations
1. **Permissions**
   - Request at runtime
   - Handle denials gracefully
   - Explain usage to users

2. **Data Protection**
   - Secure location data
   - Implement proper cleanup
   - Follow Android security guidelines 