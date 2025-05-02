#pragma once

#include <vector>
#include <cstdint>

namespace sonus {

class AudioUtils {
public:
    // Normalize audio samples to [-1, 1] range
    static void normalize(std::vector<float>& samples);
    
    // Apply gain to audio samples
    static void applyGain(std::vector<float>& samples, float gain);
    
    // Mix multiple audio streams
    static std::vector<float> mix(const std::vector<std::vector<float>>& streams);
    
    // Apply simple noise reduction
    static void reduceNoise(std::vector<float>& samples, float threshold);
    
    // Calculate signal-to-noise ratio
    static float calculateSNR(const std::vector<float>& signal, const std::vector<float>& noise);
    
    // Apply simple bandpass filter
    static void bandpassFilter(std::vector<float>& samples, float lowFreq, float highFreq, uint32_t sampleRate);
    
    // Calculate audio energy
    static float calculateEnergy(const std::vector<float>& samples);
    
    // Detect silence
    static bool isSilence(const std::vector<float>& samples, float threshold);
    
    // Convert between different audio formats
    static std::vector<float> convertToFloat(const std::vector<int16_t>& samples);
    static std::vector<int16_t> convertToInt16(const std::vector<float>& samples);
};

} // namespace sonus 