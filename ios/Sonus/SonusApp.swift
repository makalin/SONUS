import UIKit
import AVFoundation
import CoreLocation

@main
class AppDelegate: UIResponder, UIApplicationDelegate {
    var window: UIWindow?
    let audioManager = AudioManager()
    let locationManager = LocationManager()
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Request audio permissions
        AVAudioSession.sharedInstance().requestRecordPermission { granted in
            if granted {
                print("Audio permission granted")
            }
        }
        
        // Request location permissions
        locationManager.requestLocationPermission()
        
        return true
    }
}

class SonusApp {
    static let shared = SonusApp()
    
    let audioManager: AudioManager
    let locationManager: LocationManager
    
    private init() {
        audioManager = AudioManager()
        locationManager = LocationManager()
    }
} 