#pragma once

#include <string>
#include <map>
#include <memory>
#include <mutex>

namespace sonus {

class Config {
public:
    static Config& getInstance();
    
    // Load configuration from file
    bool loadFromFile(const std::string& filename);
    
    // Save configuration to file
    bool saveToFile(const std::string& filename);
    
    // Get/set configuration values
    template<typename T>
    T get(const std::string& key, const T& defaultValue = T()) const;
    
    template<typename T>
    void set(const std::string& key, const T& value);
    
    // Audio configuration
    struct AudioConfig {
        uint32_t sampleRate = 44100;
        float carrierFrequency = 2000.0f;
        float bitDuration = 0.1f;
        float noiseThreshold = 0.1f;
        float gain = 1.0f;
    };
    
    AudioConfig getAudioConfig() const;
    void setAudioConfig(const AudioConfig& config);
    
private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    
    std::map<std::string, std::string> m_config;
    mutable std::mutex m_mutex;
    AudioConfig m_audioConfig;
};

} // namespace sonus 