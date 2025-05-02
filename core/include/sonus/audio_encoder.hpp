#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace sonus {

class AudioEncoder {
public:
    AudioEncoder();
    ~AudioEncoder();

    // Encode data into audio frequencies
    std::vector<float> encodeData(const std::vector<uint8_t>& data);
    
    // Encode GPS coordinates
    std::vector<float> encodeGPS(double latitude, double longitude);
    
    // Encode SOS signal
    std::vector<float> encodeSOS();
    
    // Set encoding parameters
    void setSampleRate(uint32_t sampleRate);
    void setCarrierFrequency(float frequency);
    void setBitDuration(float duration);

private:
    uint32_t m_sampleRate;
    float m_carrierFrequency;
    float m_bitDuration;
    
    // Helper methods
    std::vector<float> generateTone(float frequency, float duration);
    std::vector<float> modulateFSK(const std::vector<uint8_t>& data);
}; 