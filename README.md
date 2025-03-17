# Radio & Keypad Library for March Hackathon 2025

## Repository Structure
```
March-Hackathon-2025/
│─── Radio/            # Radio communication library
│    ├── Radio.h
│    ├── Radio.cpp
│─── KYPD/             # Keypad input library
│    ├── KYPD.h
│    ├── KYPD.cpp
│─── docs/             # Additional materials (PDFs, instructions, etc.)
│    ├── guide.pdf
│    ├── datasheet.pdf
│─── README.md         # This documentation file
│─── LICENSE           # Licensing file
```

---

## 📌 How to Use the Libraries
Since some participants may not have access to the Arduino `libraries/` folder, follow the steps below to use the **Radio** and **KYPD** libraries manually.

### 1️⃣ **Adding the Libraries to Your Project**

#### **Method 1: Include Libraries Inside Your Project Folder (Recommended)**
1. Copy the `Radio/` and `KYPD/` folders **into the same directory as your sketch** (`.ino` file).
2. In your Arduino sketch (`.ino` file), include the headers with:
   ```cpp
   #include "Radio/Radio.h"
   #include "KYPD/KYPD.h"
   ```

#### **Method 2: Install Libraries in the Arduino Libraries Folder**
1. Copy `Radio/` and `KYPD/` folders to your Arduino libraries directory:
   - On **Windows**: `C:\Users\YourName\Documents\Arduino\libraries\`
   - On **Linux/macOS**: `~/Arduino/libraries/`
2. Restart Arduino IDE.
3. Include the libraries normally:
   ```cpp
   #include <Radio.h>
   #include <KYPD.h>
   ```

---

## 📄 **Additional Materials**
For more information, refer to the PDF guides available in the `docs/` folder:
- **`guide.pdf`** – Detailed explanation of the libraries and hardware setup.
- **`datasheet.pdf`** – Specifications and pinouts for the supported modules.

---

## ❓ **Troubleshooting & Support**
If you encounter issues:
- Ensure all connections are correct and modules are powered properly.
- Verify that the library headers (`Radio.h`, `KYPD.h`) are included in your project.
- Check the `examples/` folder for working Arduino sketches.

For additional support, feel free to ask in the **Hackathon Discord** or open an **issue on GitHub**.

---

🚀 **Happy Hacking & Good Luck in March Hackathon 2025!** 🎉

