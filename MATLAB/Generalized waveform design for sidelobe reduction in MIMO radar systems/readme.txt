# Generalized Waveform Design for Sidelobe Reduction in MIMO Radar Systems

This repository contains the simulation codes for the paper:

**Ehsan Raei, Mohammad Alaee-Kerahroodi, Prabhu Babu, M.R. Bhavani Shankar, "Generalized Waveform Design for Sidelobe Reduction in MIMO Radar Systems," *Signal Processing*, Elsevier, 2022. DOI: [10.1016/j.sigpro.2022.108914](https://doi.org/10.1016/j.sigpro.2022.108914).**

---

## 🚀 Overview

This repository includes the code used in the paper, which focuses on generalized waveform design for sidelobe reduction in MIMO radar systems. Specifically, the paper presents a design methodology for phase-only (constant modulus) sequences with low Peak Sidelobe Level (PSL) and Integrated Sidelobe Level (ISL), optimizing radar performance by reducing sidelobes and improving target detection.

### Key Aspects of the Paper:
- **Optimization of Phase-Only Sequences**: The work minimizes the weighted \( \ell_{p} \)-norm of the auto- and cross-correlation sidelobes to reduce PSL and ISL.
- **BSUM Algorithm**: Block successive upper bound minimization (BSUM) is used to solve the non-convex, NP-hard optimization problem.
- **Unimodular Sequences**: The paper focuses on unimodular sequences that are suitable for practical radar systems with amplifier constraints.
- **Performance**: The optimized sequences outperform state-of-the-art counterparts both in terms of PSL and computational time.

---

## 📁 Contents

### 1. **Code Files**
The following code files are included in this repository:
- **WeBEST_d_1file**: Implements the design for the optimization of auto- and cross-correlation sidelobes, using the BSUM algorithm - discrete phase.
- **WeBEST_e_1file**: Implements the design for the optimization of auto- and cross-correlation sidelobes, using the BSUM algorithm - continous phase.
- **WeBEST_v_1file**: Implements the design for the optimization of auto- and cross-correlation sidelobes, using the BSUM algorithm - continous phase, and gradient.


---

## 🛠️ How to Use

1. **Download the repository**: Clone or download the files from this repository.
2. **Run the Scripts**: Open the MATLAB environment and run the relevant script (`WeBEST_d_1file`, `WeBEST_e_1file`, or `WeBEST_v_1file`) depending on the task you want to perform.
3. **Check Results**: The optimization results, including the PSL and ISL values, will be displayed in the MATLAB environment.

---

## ✉️ Code Authors

- **Ehsan Raei**: 
- **Mohammad Alaee-Kerahroodi**: [Email](mailto:mohammad.alaee@uni.lu)


---

## 📞 Contact

For any inquiries or further assistance, please reach out to the authors via email.

---

## 🔗 Related Resources

- [Paper on ScienceDirect](https://www.sciencedirect.com/science/article/abs/pii/S0165168422004534)
- [RadarMIMO Website](https://radarmimo.com/)

---

## ⚙️ Requirements

- **MATLAB**: The code is written for MATLAB and assumes the availability of standard MATLAB toolboxes.

---

## 🤝 Contributions

We welcome contributions to improve the code or extend its functionalities. If you would like to contribute, please feel free to fork the repository and submit a pull request.

---

## 🌟 Acknowledgements

Special thanks to the research community for their continuous support in improving radar waveform design methodologies and contributing to the state-of-the-art research in this field.
