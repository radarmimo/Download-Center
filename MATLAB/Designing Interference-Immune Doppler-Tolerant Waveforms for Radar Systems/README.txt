# Designing Interference-Immune Doppler-Tolerant Waveforms for Radar Systems

This repository contains MATLAB code developed to support the findings and methodologies presented in the paper titled:

**"Designing Interference-Immune Doppler-Tolerant Waveforms for Radar Systems"**  
Published in *IEEE Transactions on Aerospace and Electronic Systems (TAES)*  
DOI: [10.1109/TAES.2022.9928573](https://ieeexplore.ieee.org/document/9928573)


## 🚀 Overview

This repository includes tools for designing optimized waveform sequences that combine the Doppler-tolerant characteristics of Linear Frequency Modulation (LFM) waveforms with the interference-immune properties of tailored polyphase sequences. The approach is based on the majorization–minimization framework and uses Peak Sidelobe Level (PSL) and Integrated Sidelobe Level (ISL) cost functions to optimize the waveform design.

### Main Features:
- **Waveform Design for Dynamic Detection**: Code to design sequences with Doppler-tolerant characteristics, similar to LFM waveforms, combined with minimal PSL/ISL and interference immunity similar to polyphase sequences.
- **Optimized Sequences**: The optimization considers parameters like degree Q of polynomial phase behavior, subsequence length M, and the total number of subsequences L to achieve optimal Doppler tolerance and low cross-correlation.
- **Automotive Application**: The method is demonstrated for an automotive scenario to showcase its practical application in real-world radar systems.

## 🔥 Getting Started

### Main Functionality

The core function of the proposed waveform design method is contained in the **`main functions`** folder. The main file designed for this paper is:

- **`PECS.m`**: This script implements the majorization–minimization framework to design Doppler-tolerant waveforms with minimal PSL/ISL. It optimizes the sequence design based on the parameters mentioned in the paper, including the degree of polynomial phase behavior and subsequence characteristics.

Users interested in exploring the methodology further are encouraged to check out the code in this file.

## 📥 License

This code is released under the following license:

**Copyright (c) 2022, Robin Amar**

### License Terms:
- Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation and/or other materials provided with the distribution.
  3. All advertising materials mentioning features or use of this software must display the following acknowledgment:  
     "This product includes software developed by Robin Amar".

**DISCLAIMER**: This software is provided "as is" without warranties of any kind. In no event shall the author be liable for any direct, indirect, incidental, special, exemplary, or consequential damages arising from the use of this software.

---

## ⚙️ Requirements

To use this code, you will need:

- **MATLAB**: Code is written for MATLAB and should work in standard MATLAB environments.

---

## 📞 Contact

For any questions or support, feel free to reach out:
- 📧 Email: [mohammad.alaee@uni.lu](mailto:mohammad.alaee@uni.lu) 

---

## 🔗 Website and Resources

- 🌐 **Website**: [https://radarmimo.com/](https://radarmimo.com/)

---

## 🤝 Contributions

Contributions to improve or extend the functionality of the code are welcome. If you would like to contribute, feel free to fork the repository and submit a pull request.

---

## 🌟 Acknowledgements

Special thanks to all those who supported this work, and to the community contributing to radar signal processing research.
