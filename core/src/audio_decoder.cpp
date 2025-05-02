#include "sonus/audio_decoder.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstring>

namespace sonus {

AudioDecoder::AudioDecoder()
    : m_sampleRate(44100)
    , m_carrierFrequency(2000.0f)
    , m_bitDuration(0.1f)
{
}

AudioDecoder::~AudioDecoder() = default;

void AudioDecoder::setSampleRate(uint32_t sampleRate) {
    m_sampleRate = sampleRate;
}

void AudioDecoder::setCarrierFrequency(float frequency) {
    m_carrierFrequency = frequency;
}

void AudioDecoder::setBitDuration(float duration) {
    m_bitDuration = duration;
}

bool AudioDecoder::detectTone(const std::vector<float>& audioData, float frequency) {
    const int samplesPerBit = static_cast<int>(m_bitDuration * m_sampleRate);
    const int numBits = audioData.size() / samplesPerBit;
    
    if (numBits == 0) return false;
    
    // Calculate the expected number of cycles for the given frequency
    const float cyclesPerBit = frequency * m_bitDuration;
    const float samplesPerCycle = m_sampleRate / frequency;
    
    // Simple energy detection
    float energy = 0.0f;
    for (size_t i = 0; i < audioData.size(); ++i) {
        energy += audioData[i] * audioData[i];
    }
    
    // Normalize energy
    energy /= audioData.size();
    
    // Threshold for tone detection
    const float threshold = 0.1f;
    return energy > threshold;
}

std::vector<float> AudioDecoder::demodulateFSK(const std::vector<float>& audioData) {
    const int samplesPerBit = static_cast<int>(m_bitDuration * m_sampleRate);
    const int numBits = audioData.size() / samplesPerBit;
    
    if (numBits == 0) return {};
    
    std::vector<float> demodulated;
    demodulated.reserve(numBits);
    
    const float spaceFreq = m_carrierFrequency * 0.8f;
    const float markFreq = m_carrierFrequency * 1.2f;
    
    for (int i = 0; i < numBits; ++i) {
        size_t start = i * samplesPerBit;
        size_t end = start + samplesPerBit;
        
        if (end > audioData.size()) break;
        
        std::vector<float> bitSamples(audioData.begin() + start, audioData.begin() + end);
        
        // Simple FSK demodulation by comparing energy at mark and space frequencies
        bool isMark = detectTone(bitSamples, markFreq);
        demodulated.push_back(isMark ? 1.0f : 0.0f);
    }
    
    return demodulated;
}

std::vector<uint8_t> AudioDecoder::decodeData(const std::vector<float>& audioData) {
    auto demodulated = demodulateFSK(audioData);
    std::vector<uint8_t> decoded;
    
    // Convert demodulated bits to bytes
    for (size_t i = 0; i < demodulated.size(); i += 8) {
        if (i + 8 > demodulated.size()) break;
        
        uint8_t byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (demodulated[i + j] > 0.5f) {
                byte |= (1 << (7 - j));
            }
        }
        decoded.push_back(byte);
    }
    
    return decoded;
}

bool AudioDecoder::decodeGPS(const std::vector<float>& audioData, double& latitude, double& longitude) {
    auto decoded = decodeData(audioData);
    
    if (decoded.size() < 16) return false;
    
    // Ensure proper alignment by copying bytes
    double lat, lon;
    std::memcpy(&lat, decoded.data(), sizeof(double));
    std::memcpy(&lon, decoded.data() + sizeof(double), sizeof(double));
    
    latitude = lat;
    longitude = lon;
    
    return true;
}

bool AudioDecoder::detectSOS(const std::vector<float>& audioData) {
    // Look for the SOS pattern: three short tones, three long tones, three short tones
    const int samplesPerShort = static_cast<int>(m_bitDuration * m_sampleRate);
    const int samplesPerLong = samplesPerShort * 3;
    
    // Check for three short tones
    for (int i = 0; i < 3; ++i) {
        size_t start = i * samplesPerShort;
        if (start + samplesPerShort > audioData.size()) return false;
        
        std::vector<float> tone(audioData.begin() + start, 
                              audioData.begin() + start + samplesPerShort);
        if (!detectTone(tone, m_carrierFrequency)) return false;
    }
    
    // Check for three long tones
    for (int i = 0; i < 3; ++i) {
        size_t start = 3 * samplesPerShort + i * samplesPerLong;
        if (start + samplesPerLong > audioData.size()) return false;
        
        std::vector<float> tone(audioData.begin() + start,
                              audioData.begin() + start + samplesPerLong);
        if (!detectTone(tone, m_carrierFrequency)) return false;
    }
    
    // Check for three short tones
    for (int i = 0; i < 3; ++i) {
        size_t start = 3 * samplesPerShort + 3 * samplesPerLong + i * samplesPerShort;
        if (start + samplesPerShort > audioData.size()) return false;
        
        std::vector<float> tone(audioData.begin() + start,
                              audioData.begin() + start + samplesPerShort);
        if (!detectTone(tone, m_carrierFrequency)) return false;
    }
    
    return true;
}

} // namespace sonus 