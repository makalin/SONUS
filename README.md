# 🎵 SONUS

**The Sound of Survival** — An innovative earthquake whistle & SOS app that **communicates using sound** when everything else fails.

---

## 🌟 Overview

**SONUS** is a survival-focused mobile application that transforms smartphones into:
- **Emergency Whistles**
- **SOS Broadcasters**
- **Offline GPS Senders** via **SonoLink Protocol**

Built for disaster scenarios like earthquakes where communication networks are down, SONUS empowers survivors to alert nearby people and rescuers using **sound waves**.

---

## 🚨 Key Features

- **Seismic Whistle Mode**  
  Emits a loud, piercing whistle for manual rescue signaling.

- **Auto-SOS Broadcast**  
  Sends automated SOS patterns to nearby devices using offline sound codes.

- **Sender & Receiver Mode**  
  - **Sender:** Encodes and transmits GPS location using **audio frequencies**.
  - **Receiver:** Listens, decodes, and displays the sender's coordinates.
  - Powered by our custom **SonoLink** protocol.

- **Rescue Beacon Flash**  
  Strobe the flashlight in emergency patterns.

- **Low Battery Mode**  
  Optimized for minimal power consumption during critical hours.

- **Shake Detection**  
  Activate SOS mode by physically shaking the device.

---

## ⚙️ Technical Highlights

- **Full Native Development:**  
  - Android (Java/Kotlin + C++)  
  - iOS (Objective-C/Swift + C++)
  
- **Audio-Based Communication:**  
  - Short-range (~3-10 meters)
  - Completely offline (no Wi-Fi, no Bluetooth required)

- **Cross-Platform Core:**  
  Audio modulation/demodulation handled via a shared **C++ library** for efficiency and consistency.

---

## 📡 SonoLink Protocol

**SonoLink** is the custom low-level communication protocol developed for SONUS.  
It enables sound-based transmission of small data payloads like GPS coordinates and SOS alerts.

🔗 **[Full SonoLink Protocol Specification](./protocols/SonoLink-v1.0.md)**

---

# 📁 Repo Structure

```
/android/      -> Android native project
/ios/          -> iOS native project
/core/         -> C++ core sound processing
/protocols/    -> Protocol documentation (SonoLink-v1.0.md)
/docs/         -> Project documentation
README.md
LICENSE
```

---

## 📄 Roadmap

- [x] Define SonoLink v1.0
- [ ] Implement native C++ core audio encoder/decoder
- [ ] Integrate Sender/Receiver modes
- [ ] Add multi-packet support (large messages)
- [ ] Add optional encryption layer for secured communications
- [ ] Open-source Beta release

---

## 🤝 Contributing

Contributions are welcome!  
We are especially looking for:
- Audio engineers familiar with FSK/ASK modulation.
- C++ developers for low-level optimization.
- Mobile app testers with a focus on disaster recovery scenarios.

Please see `CONTRIBUTING.md` (to be added) for guidelines.

---

## 🛡 License

MIT License  
Feel free to fork, build, improve, and save lives.

---

## 🚀 Project Status

> **Currently in early active development.**  
> Early beta versions expected soon!

---

## 👨‍💻 Contributors

We would like to thank the following individuals for their contributions to this project:

- **@argeolog_** - For providing the original idea and inspiration via their [tweet](https://x.com/argeolog_/status/1916237137604981163). Their work on the "Düdüğüm" app, a React Native application for earthquake alerts, inspired this project.

- **Mehmet Turgay AKALIN**  
  [GitHub Profile](https://github.com/makalin)  
  Developer, creator of SONUS and SonoLink protocol.  
  Focused on building open, resilient, and innovative systems for real-world problems.
  
---

## How to Contribute
If you'd like to contribute to this project, please check out our [CONTRIBUTING.md](CONTRIBUTING.md) file for guidelines.

---

# 📢 Stay tuned for updates!
