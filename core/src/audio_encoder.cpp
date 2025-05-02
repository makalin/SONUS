#include "sonus/audio_encoder.hpp"
#include <cmath>
#include <algorithm>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sonus {

AudioEncoder::AudioEncoder()
    : m_sampleRate(44100)
    , m_carrierFrequency(2000.0f)
    , m_bitDuration(0.1f)
{
}

AudioEncoder::~AudioEncoder() = default;

void AudioEncoder::setSampleRate(uint32_t sampleRate) {
    m_sampleRate = sampleRate;
}

void AudioEncoder::setCarrierFrequency(float frequency) {
    m_carrierFrequency = frequency;
}

void AudioEncoder::setBitDuration(float duration) {
    m_bitDuration = duration;
}

std::vector<float> AudioEncoder::generateTone(float frequency, float duration) {
    std::vector<float> tone;
    
    // Check for potential overflow
    if (duration <= 0.0f || frequency <= 0.0f || m_sampleRate == 0) {
        return tone;
    }
    
    const double maxSamples = static_cast<double>(duration) * m_sampleRate;
    if (maxSamples > std::numeric_limits<int>::max()) {
        return tone;
    }
    
    int numSamples = static_cast<int>(maxSamples);
    tone.reserve(numSamples);
    
    for (int i = 0; i < numSamples; ++i) {
        float t = static_cast<float>(i) / m_sampleRate;
        tone.push_back(std::sin(2.0f * M_PI * frequency * t));
    }
    
    return tone;
}

std::vector<float> AudioEncoder::modulateFSK(const std::vector<uint8_t>& data) {
    std::vector<float> modulated;
    const float spaceFreq = m_carrierFrequency * 0.8f;
    const float markFreq = m_carrierFrequency * 1.2f;
    
    for (uint8_t byte : data) {
        for (int i = 7; i >= 0; --i) {
            float freq = (byte & (1 << i)) ? markFreq : spaceFreq;
            auto tone = generateTone(freq, m_bitDuration);
            modulated.insert(modulated.end(), tone.begin(), tone.end());
        }
    }
    
    return modulated;
}

std::vector<float> AudioEncoder::encodeData(const std::vector<uint8_t>& data) {
    return modulateFSK(data);
}

std::vector<float> AudioEncoder::encodeGPS(double latitude, double longitude) {
    // Convert GPS coordinates to bytes
    std::vector<uint8_t> gpsData;
    gpsData.reserve(16); // 8 bytes for each coordinate
    
    // Add latitude and longitude as 8-byte doubles
    const uint8_t* latPtr = reinterpret_cast<const uint8_t*>(&latitude);
    const uint8_t* lonPtr = reinterpret_cast<const uint8_t*>(&longitude);
    
    gpsData.insert(gpsData.end(), latPtr, latPtr + 8);
    gpsData.insert(gpsData.end(), lonPtr, lonPtr + 8);
    
    return modulateFSK(gpsData);
}

std::vector<float> AudioEncoder::encodeSOS() {
    // SOS in Morse code: ... --- ...
    std::vector<float> sosSignal;
    
    // Three short tones (S)
    for (int i = 0; i < 3; ++i) {
        auto tone = generateTone(m_carrierFrequency, m_bitDuration);
        sosSignal.insert(sosSignal.end(), tone.begin(), tone.end());
    }
    
    // Three long tones (O)
    for (int i = 0; i < 3; ++i) {
        auto tone = generateTone(m_carrierFrequency, m_bitDuration * 3);
        sosSignal.insert(sosSignal.end(), tone.begin(), tone.end());
    }
    
    // Three short tones (S)
    for (int i = 0; i < 3; ++i) {
        auto tone = generateTone(m_carrierFrequency, m_bitDuration);
        sosSignal.insert(sosSignal.end(), tone.begin(), tone.end());
    }
    
    return sosSignal;
}

} // namespace sonus 