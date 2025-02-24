# Coordinate-Descent Framework to Design Low PSL/ISL Sequences

This repository contains MATLAB code designed to implement the coordinate-descent framework for designing low Peak-to-Sidelobe (PSL) and Inter-Sidelobe (ISL) sequences. The methods are described in the paper:

**"A Coordinate-Descent Framework to Design Low PSL/ISL Sequences"**  
IEEE Transactions on Signal Processing, vol. 65, no. 22, pp. 5942-5956, Nov. 15, 2017.

## 🚀 Overview

The code implements algorithms for designing sequences with low PSL and ISL, which are critical for radar and communication systems. The main functions are:

- **`cpm.m`**: Designs constant modulus sequences.
- **`lpCPM.m`**: Initializes continuous phase for PSL minimization.
- **`dpm.m`**: Designs discrete phase sequences, including binary sequences.
- **`lpDPM.m`**: Initializes discrete phase for PSL minimization, including binary sequences.

## 📊 Reproducing the Figures

To reproduce the figures reported in the paper, you can run the script **`FigTSP2017.m`**.

This script generates the figures presented in the paper and demonstrates the effectiveness of the coordinate-descent framework.

### Paper Citation:
If you use this code in your work, please cite the following paper:

```bibtex
@article{alaee2017coordinate,
  title={A Coordinate-Descent Framework to Design Low PSL/ISL Sequences},
  author={Mohammad Alaee-Kerahroodi},
  journal={IEEE Transactions on Signal Processing},
  volume={65},
  number={22},
  pages={5942--5956},
  year={2017},
  publisher={IEEE}
}


📥 License
This code is released under the following license:

Copyright (c) 2020, Mohammad Alaee, Website: https://radarmimo.com/

License Terms:
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation and/or other materials provided with the distribution.
All advertising materials mentioning features or use of this software must display the following acknowledgment:
"This product includes software developed by Mohammad Alaee, https://radarmimo.com/".
DISCLAIMER: This software is provided "as is" without warranties of any kind. In no event shall the author be liable for any direct, indirect, incidental, special, exemplary, or consequential damages arising from the use of this software.

⚙️ Requirements
To use this code, you will need:

MATLAB: Code is written for MATLAB and should work in standard MATLAB environments.
MATLAB Toolboxes: Ensure you have the Signal Processing Toolbox for certain operations.
📞 Contact
For any questions or support, feel free to reach out:

📧 Email: info@radarmimo.com
📧 Email: mohammad.alaee@uni.lu
📧 Email: mmalaee@yahoo.com
🔗 Website and Resources
🌐 Website: https://radarmimo.com/