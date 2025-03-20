# Radio & Keypad Library for March Hackathon 2025

## Repository Structure
```
March-Hackathon-2025/
│─── Radio/            # Radio communication library
│    ├── Radio.h
│    ├── Radio.cpp
│    ├── examples/     # Example sketches for Radio library
│─── KYPD/             # Keypad input library
│    ├── KYPD.h
│    ├── KYPD.cpp
│    ├── examples/     # Example sketches for KYPD library
│─── docs/             # Additional materials (PDFs, instructions, etc.)
│    ├── Presentation_1st_day.pdf
│    ├── Tasks.pdf
│─── README.md         # This documentation file
│─── LICENSE           # Licensing file
```

---

## 📌 How to Use the Libraries
Since some participants may not have access to the Arduino `libraries/` folder, follow the steps below to use the **Radio** and **KYPD** libraries manually.

### 1️⃣ **Adding the Libraries to Your Project**

#### **Method 1: Include Libraries Inside Your Project Folder (Recommended)**
1. Copy the `Radio.h` and `Radio.cpp` files **into the same directory as your sketch** (`.ino` file).
2. In your Arduino sketch (`.ino` file), include the headers with:
   ```cpp
   #include "Radio.h"
   ```
3. Do the same with the `KYPD.h` and `KYPD.cpp` files, so you have KYPD library.
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
4. This might not work on the university computers, so stick with **Method 1** in this case
---

## 📄 **Additional Materials**
For more information, refer to the PDF guides available in the `docs/` folder:
- **`Presentation_1st_day.pdf`** – Detailed explanation of the libraries and hardware setup.
- **`Tasks.pdf`** – Competition tasks.

---

🚀 **Happy Hacking & Good Luck in March Hackathon 2025!** 🎉

