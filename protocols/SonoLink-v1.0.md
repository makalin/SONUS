# 📡 SonoLink Protocol Specification  
**Version:** 1.0  
**Status:** Draft / Alpha

---

## 1. Overview

**SonoLink** is a lightweight, low-power, sound-based communication protocol for offline short-range data transmission between mobile devices.  
It is designed to **send and receive small, critical payloads** — like GPS locations or SOS messages — **using audio frequencies**, especially in post-disaster or no-network conditions.

SonoLink operates entirely using **standard smartphone microphones and speakers**, without requiring any internet, Bluetooth, or mobile signal.

---

## 2. Design Goals

- ✅ Work offline
- ✅ Ultra-low battery consumption
- ✅ No external hardware required
- ✅ Reliable short-range communication (~3–10 meters)
- ✅ Resilient against background noise (basic)
- ✅ Easy to implement natively (Android/iOS)

---

## 3. Transmission Model

- **Modulation:** Frequency-Shift Keying (**FSK**)
- **Data Rate:** ~75 bits/second
- **Carrier Frequencies:** 2000 Hz – 4000 Hz
- **Transmission Medium:** Air (via sound)
- **Error Detection:** Simple XOR checksum (future versions may implement CRC8)

---

## 4. Packet Structure

Each SonoLink packet follows this structure:

| Field            | Size      | Description                              |
|------------------|-----------|------------------------------------------|
| **Preamble**      | 1 Tone    | Start of transmission (1800 Hz tone)     |
| **Header**        | 2 Bytes   | Packet Type and Protocol Version         |
| **Payload Length**| 1 Byte    | Number of bytes in payload               |
| **Payload**       | Variable  | Encoded data (GPS, SOS, message)         |
| **Checksum**      | 1 Byte    | XOR checksum of payload                  |
| **Postamble**     | 1 Tone    | End of transmission (1500 Hz tone)       |

---

### 4.1 Field Details

- **Preamble:**  
  - 1800 Hz pure tone (duration: 200 ms)
  - Signals the beginning of a transmission.
  
- **Header:**  
  - **Byte 1 (Packet Type):**  
    - `0x01` = GPS Data  
    - `0x02` = SOS Message  
    - `0x03` = Custom Text Message  
  - **Byte 2 (Protocol Version):**  
    - `0x10` (SonoLink v1.0)

- **Payload Length:**  
  - 1 Byte indicating the number of payload bytes.

- **Payload:**  
  - Encoded data as raw bytes (e.g., latitude, longitude, message).

- **Checksum:**  
  - Single byte.  
  - XOR of all payload bytes.  
  - Used for simple error detection.

- **Postamble:**  
  - 1500 Hz pure tone (duration: 200 ms)
  - Signals the end of transmission.

---

## 5. Frequency Mapping

SonoLink maps each byte (0–255) into a unique frequency within 2000 Hz – 4000 Hz.

**Formula:**
```
Frequency (Hz) = 2000 + (Byte_Value × 8)
```

| Byte Value | Frequency (Hz) |
|------------|----------------|
| 0          | 2000            |
| 1          | 2008            |
| 2          | 2016            |
| ...        | ...             |
| 255        | 4040            |

- **Each tone** duration: 20 ms (can be adapted).
- **Gaps:** Optional 5 ms silent gap between tones for clarity.

---

## 6. Transmission Timing

| Element        | Time     |
|----------------|----------|
| Preamble Tone  | 200 ms   |
| Each Byte Tone | 20 ms    |
| Postamble Tone | 200 ms   |

- Total time for a small GPS payload (e.g., 32 bytes) ≈ ~2 seconds.

---

## 7. Error Handling

- After receiving, the device recalculates checksum.
- If checksum fails, discard packet.
- Future enhancements: add optional retry requests or error correction.

---

## 8. Use Case Examples

### 8.1 GPS Location Transmission
- **Payload Example:** `"37.7749,-122.4194"`  
- Encoded as ASCII bytes, mapped to sound frequencies.
- Nearby devices decode and display location without internet.

---

### 8.2 SOS Emergency Broadcast
- **Payload Example:** `"SOS"`  
- Repeated at intervals.

---

## 9. Future Extensions

- 🔹 Multi-packet transmission (for larger data, e.g., 512 bytes)
- 🔹 Encryption (basic XOR or lightweight symmetric encryption)
- 🔹 Adaptive modulation (frequency range selection based on noise)
- 🔹 Ultrasonic mode (if hardware permits, above 18 kHz)

---

## 10. Licensing

**SonoLink** protocol is released under the **MIT License**.  
It is free to use, modify, and distribute, even for commercial purposes, with attribution.

---

# 🚀 Let's Connect the Silence with SonoLink

