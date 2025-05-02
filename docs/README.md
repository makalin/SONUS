# SONUS Documentation

## Overview
SONUS is a cross-platform application that enables emergency communication through audio signals. It can encode and decode SOS messages and GPS coordinates into audio signals, allowing for communication in situations where traditional methods may not be available.

## Core Components

### 1. Audio Signal Processing
- **Encoding**: Converts SOS messages and GPS coordinates into audio signals
- **Decoding**: Extracts information from received audio signals
- **Signal Processing**: Handles audio recording and playback

### 2. Location Services
- **GPS Tracking**: Monitors and updates user location
- **Location Broadcasting**: Encodes and transmits location data via audio signals
- **Permission Management**: Handles location access permissions

### 3. Platform-Specific Implementations

#### Android
- **AudioManager**: Handles audio recording and playback using Android's AudioRecord and AudioTrack
- **LocationManager**: Manages location services using Android's LocationManager
- **Permissions**: Handles runtime permissions for microphone and location access

#### iOS
- **AudioManager**: Implements audio functionality using AVFoundation
- **LocationManager**: Manages location services using CoreLocation
- **Permissions**: Handles privacy permissions for microphone and location access

## Technical Specifications

### Audio Format
- Sample Rate: 44.1 kHz
- Channels: Mono
- Bit Depth: 32-bit float
- Endianness: Little-endian

### Signal Encoding
- SOS Signal: Encoded as a specific audio pattern
- GPS Data: Encoded as a sequence of audio tones representing coordinates

### Location Accuracy
- Android: Uses GPS_PROVIDER with 1-meter accuracy
- iOS: Uses kCLLocationAccuracyBest with 1-meter distance filter

## API Documentation

### Core Library
- `encodeSOS()`: Generates audio signal for SOS message
- `encodeGPS(latitude, longitude)`: Generates audio signal for location data
- `decodeAudio(data)`: Extracts information from received audio signal

### Android
- `AudioManager.startRecording(onDataReceived)`: Starts audio recording
- `AudioManager.playAudio(data)`: Plays audio data
- `LocationManager.startLocationUpdates(onLocationUpdate)`: Starts location tracking
- `LocationManager.broadcastLocation(location)`: Broadcasts location via audio

### iOS
- `AudioManager.startRecording(onDataReceived)`: Starts audio recording
- `AudioManager.playAudio(data)`: Plays audio data
- `LocationManager.startLocationUpdates(handler)`: Starts location tracking
- `LocationManager.broadcastLocation(location)`: Broadcasts location via audio

## Security Considerations
- All sensitive permissions are requested at runtime
- Location data is only transmitted when explicitly requested
- Audio signals are encoded with error correction

## Performance Considerations
- Audio processing is optimized for real-time operation
- Location updates are filtered to minimize battery impact
- Memory usage is managed to prevent leaks

## Troubleshooting
- Check microphone permissions if audio recording fails
- Ensure location services are enabled for GPS functionality
- Verify audio output device is properly connected
- Monitor battery usage for extended operation

## Contributing
Please refer to the main project README for contribution guidelines.

## License
This project is licensed under the MIT License - see the LICENSE file for details. 