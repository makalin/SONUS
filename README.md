# SONUS - Emergency Communication App

![SONUS Logo](sonus_logo.svg)

SONUS is a cross-platform application that enables emergency communication through audio signals. It can encode and decode SOS messages and GPS coordinates into audio signals, allowing for communication in situations where traditional methods may not be available.

## Features

- **Audio Signal Processing**
  - Real-time audio recording and playback
  - SOS message encoding/decoding
  - GPS coordinate transmission via audio
  - High-quality 32-bit float PCM format

- **Location Services**
  - GPS tracking with high accuracy
  - Location broadcasting via audio signals
  - Permission management
  - Background location updates

- **Cross-Platform Support**
  - Android (API 21+)
  - iOS (14.0+)
  - Shared core functionality

## Documentation

The project documentation is organized in the `docs` directory:

- [Main Documentation](docs/README.md) - Overview and technical specifications
- [Android Guide](docs/android.md) - Android-specific implementation details
- [iOS Guide](docs/ios.md) - iOS-specific implementation details

## Project Structure

```
.
├── android/                  # Android implementation
│   ├── app/
│   │   ├── src/
│   │   │   └── main/
│   │   │       ├── java/
│   │   │       │   └── com/
│   │   │       │       └── sonus/
│   │   │       └── AndroidManifest.xml
│   └── build.gradle
├── ios/                      # iOS implementation
│   ├── Sonus/
│   │   ├── SonusApp.swift
│   │   ├── AudioManager.swift
│   │   ├── LocationManager.swift
│   │   └── Info.plist
│   └── Sonus.xcodeproj/
├── docs/                     # Documentation
│   ├── README.md
│   ├── android.md
│   └── ios.md
└── README.md                 # This file
```

## Requirements

### Android
- Android Studio
- Android SDK 33
- Kotlin 1.8.0
- Gradle 7.4.2

### iOS
- Xcode 14.0+
- Swift 5.0
- iOS 14.0+

## Installation

### Android
1. Clone the repository
2. Open the project in Android Studio
3. Sync Gradle files
4. Build and run

### iOS
1. Clone the repository
2. Open `Sonus.xcodeproj` in Xcode
3. Select your development team
4. Build and run

## Usage

### Sending SOS Signal
1. Open the app
2. Grant necessary permissions
3. Press the SOS button
4. Hold the device to transmit the signal

### Broadcasting Location
1. Enable location services
2. Press the location broadcast button
3. The app will encode and transmit your coordinates

### Receiving Signals
1. Enable microphone access
2. The app will automatically detect and decode incoming signals
3. View decoded messages in the app interface

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Core Audio and Location services teams
- Open source contributors
- Test users and feedback providers
