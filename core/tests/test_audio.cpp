#include "sonus/audio_encoder.hpp"
#include "sonus/audio_decoder.hpp"
#include <gtest/gtest.h>
#include <cmath>

using namespace sonus;

class AudioTest : public ::testing::Test {
protected:
    void SetUp() override {
        encoder = std::make_unique<AudioEncoder>();
        decoder = std::make_unique<AudioDecoder>();
    }

    std::unique_ptr<AudioEncoder> encoder;
    std::unique_ptr<AudioDecoder> decoder;
};

TEST_F(AudioTest, EncodeDecodeData) {
    std::vector<uint8_t> testData = {0x55, 0xAA, 0xFF};
    auto encoded = encoder->encodeData(testData);
    auto decoded = decoder->decodeData(encoded);
    
    EXPECT_EQ(decoded.size(), testData.size());
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(decoded[i], testData[i]);
    }
}

TEST_F(AudioTest, EncodeDecodeGPS) {
    double testLat = 41.0082;
    double testLon = 28.9784;
    
    auto encoded = encoder->encodeGPS(testLat, testLon);
    
    double decodedLat, decodedLon;
    bool success = decoder->decodeGPS(encoded, decodedLat, decodedLon);
    
    EXPECT_TRUE(success);
    EXPECT_NEAR(decodedLat, testLat, 0.0001);
    EXPECT_NEAR(decodedLon, testLon, 0.0001);
}

TEST_F(AudioTest, DetectSOS) {
    auto sosSignal = encoder->encodeSOS();
    bool detected = decoder->detectSOS(sosSignal);
    
    EXPECT_TRUE(detected);
}

TEST_F(AudioTest, DetectSOSInNoise) {
    auto sosSignal = encoder->encodeSOS();
    
    // Add some noise to the signal
    for (auto& sample : sosSignal) {
        sample += (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 0.1f;
    }
    
    bool detected = decoder->detectSOS(sosSignal);
    EXPECT_TRUE(detected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 