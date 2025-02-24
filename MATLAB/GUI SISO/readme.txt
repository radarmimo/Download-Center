# GUI SISO Waveform Optimization Tool

Welcome to the **GUI SISO Waveform Optimization Tool**, designed to streamline waveform design using the **Continuous Phase Constraint (CPM)** and **Discrete Phase Constraint (DPM)** algorithms. This graphical user interface (GUI) enables you to effortlessly generate optimized waveforms tailored to your specific requirements.

---

## 🚀 Getting Started

To get started, follow these steps:

1. **Launch the GUI**: 
   - Open MATLAB and execute the `mSISO.m` script to launch the GUI.

2. **Select an Algorithm**: 
   - Choose either the **CPM** or **DPM** algorithm based on your optimization goals.

3. **Input the Initial Sequence**: 
   - Provide the initial sequence that you wish to optimize.

4. **Run the Optimization**: 
   - Click the "Run Optimization" button to start the optimization process.

---

## 🔧 Algorithm Selection

### **CPM (Continuous Phase Constraint)**
- **Objective**: Minimize the Peak Sidelobe Level (PSL) or Integrated Sidelobe Level (ISL) while ensuring phase continuity.
- **Features**: 
   - Optimizes the waveform by minimizing sidelobes.
   - Enforces a unimodular constraint for phase continuity across the sequence.

### **DPM (Discrete Phase Constraint)**
- **Objective**: Select an optimal waveform from a predefined alphabet of discrete phase values, aiming to minimize PSL or ISL.
- **Features**:
   - Utilizes a set of discrete phase values for the waveform design.
   - Focuses on optimizing sidelobe levels within the given constraints.

---

## 🛠️ Using the GUI SISO Tool

1. **Select the Optimization Algorithm**: 
   - Choose either **CPM** or **DPM** from the dropdown menu based on your waveform optimization needs.

2. **Input the Initial Sequence**: 
   - Input a sequence that will serve as the starting point for optimization. The GUI will optimize this sequence based on the selected algorithm.

3. **Configure Parameters**: 
   - Set any additional parameters specific to the algorithm, such as optimization weights, phase alphabet (for DPM), and other configurations.

4. **Run the Optimization**: 
   - Click the "Run Optimization" button to initiate the optimization process. The algorithm will be applied to the input sequence.

5. **View the Results**: 
   - Once the optimization is complete, the GUI will display the optimized waveform along with key metrics such as **Peak Sidelobe Level (PSL)**, **Integrated Sidelobe Level (ISL)**, and other relevant optimization results.

---

## 📖 Reference

For detailed explanations of the algorithms and the underlying optimization framework, refer to the following paper:

- **M. Alaee-Kerahroodi, A. Aubry, A. De Maio, M. M. Naghsh, and M. Modarres-Hashemi, "A Coordinate-Descent Framework to Design Low PSL/ISL Sequences,"** IEEE Transactions on Signal Processing, vol. 65, no. 22, pp. 5942-5956, 15 Nov. 2017. DOI: [10.1109/TSP.2017.2723354](https://doi.org/10.1109/TSP.2017.2723354).

---

## 💡 Tips

- Ensure that all relevant files are in the same directory as `mSISO.m` to avoid errors.
- The optimization results will be displayed immediately after running the process. You can save the results for further analysis.
  
---

## ✉️ Contact

For any inquiries, feedback, or assistance, please reach out to us at:  
📧 **info@radarmimo.com**

---

## 📜 License

**Copyright 2023 Mohammad Alaee**

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

- The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

**THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.**

---

## 🤝 Contributions

We welcome contributions to enhance or extend the functionalities of this tool. If you'd like to contribute, please fork the repository and submit a pull request.

---

## 🔗 Related Resources

- [RadarMIMO Website](https://radarmimo.com/)
