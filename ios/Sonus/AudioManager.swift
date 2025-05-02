import Foundation
import AVFoundation

class AudioManager: NSObject {
    private var audioEngine: AVAudioEngine?
    private var audioPlayer: AVAudioPlayerNode?
    private var audioRecorder: AVAudioRecorder?
    private var isRecording = false
    private var isPlaying = false
    
    private let sampleRate: Double = 44100
    private let channelCount: Int = 1
    private let bitDepth: Int = 32
    
    override init() {
        super.init()
        setupAudioSession()
    }
    
    private func setupAudioSession() {
        let audioSession = AVAudioSession.sharedInstance()
        do {
            try audioSession.setCategory(.playAndRecord, mode: .default)
            try audioSession.setActive(true)
        } catch {
            print("Failed to set up audio session: \(error)")
        }
    }
    
    func startRecording(onDataReceived: @escaping (Data) -> Void) {
        guard !isRecording else { return }
        
        let settings: [String: Any] = [
            AVFormatIDKey: kAudioFormatLinearPCM,
            AVSampleRateKey: sampleRate,
            AVNumberOfChannelsKey: channelCount,
            AVLinearPCMBitDepthKey: bitDepth,
            AVLinearPCMIsFloatKey: true,
            AVLinearPCMIsBigEndianKey: false
        ]
        
        let tempFile = FileManager.default.temporaryDirectory.appendingPathComponent("recording.wav")
        
        do {
            audioRecorder = try AVAudioRecorder(url: tempFile, settings: settings)
            audioRecorder?.record()
            isRecording = true
            
            // Start a timer to read recorded data
            Timer.scheduledTimer(withTimeInterval: 0.1, repeats: true) { [weak self] timer in
                guard let self = self, self.isRecording else {
                    timer.invalidate()
                    return
                }
                
                if let data = try? Data(contentsOf: tempFile) {
                    onDataReceived(data)
                }
            }
        } catch {
            print("Failed to start recording: \(error)")
        }
    }
    
    func stopRecording() {
        audioRecorder?.stop()
        isRecording = false
    }
    
    func playAudio(data: Data) {
        guard !isPlaying else { return }
        
        do {
            let audioFile = try AVAudioFile(forReading: data)
            audioPlayer = AVAudioPlayerNode()
            audioEngine = AVAudioEngine()
            
            guard let player = audioPlayer, let engine = audioEngine else { return }
            
            engine.attach(player)
            engine.connect(player, to: engine.mainMixerNode, format: audioFile.processingFormat)
            
            try engine.start()
            player.scheduleFile(audioFile, at: nil)
            player.play()
            
            isPlaying = true
            
            // Stop when playback is complete
            Timer.scheduledTimer(withTimeInterval: audioFile.duration, repeats: false) { [weak self] _ in
                self?.stopPlaying()
            }
        } catch {
            print("Failed to play audio: \(error)")
        }
    }
    
    func stopPlaying() {
        audioPlayer?.stop()
        audioEngine?.stop()
        isPlaying = false
    }
    
    func encodeSOS() -> Data {
        let sosSignal = SonusCore.shared.encodeSOS()
        return Data(bytes: sosSignal, count: sosSignal.count * MemoryLayout<Float>.size)
    }
    
    func encodeGPS(latitude: Double, longitude: Double) -> Data {
        let gpsSignal = SonusCore.shared.encodeGPS(latitude: latitude, longitude: longitude)
        return Data(bytes: gpsSignal, count: gpsSignal.count * MemoryLayout<Float>.size)
    }
} 