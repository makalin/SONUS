#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace sonus {

class AudioDecoder {
public:
    AudioDecoder();
    ~AudioDecoder();

    // Decode audio data into bytes
    std::vector<uint8_t> decodeData(const std::vector<float>& audioData);
    
    // Decode GPS coordinates from audio
    bool decodeGPS(const std::vector<float>& audioData, double& latitude, double& longitude);
    
    // Detect SOS signal
    bool detectSOS(const std::vector<float>& audioData);
    
    // Set decoding parameters
    void setSampleRate(uint32_t sampleRate);
    void setCarrierFrequency(float frequency);
    void setBitDuration(float duration);

private:
    uint32_t m_sampleRate;
    float m_carrierFrequency;
    float m_bitDuration;
    
    // Helper methods
    std::vector<float> demodulateFSK(const std::vector<float>& audioData);
    bool detectTone(const std::vector<float>& audioData, float frequency);
}; 