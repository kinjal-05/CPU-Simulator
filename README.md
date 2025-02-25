<h1 align="center" style="color:#ff4500;">8085 Microprocessor Simulator</h1>

---


### 📌 **Overview**

This project is a **8085 microprocessor simulator** implemented in **C++**. It simulates the execution of **8085 assembly instructions**, allowing users to run programs and observe **register and memory changes**.

✨ **Supported Instructions:** `MOV, MVI, LXI, LDA, STA, LHLD, SHLD, ADD, SUB, CMP` and more!

---

### 🎯 **Features**

✅ **Instruction Parsing:** Reads and executes valid **8085 assembly instructions**.<br>
✅ **Register Operations:** Simulates **8085 registers** (A, B, C, D, E, H, L).<br>
✅ **Memory Management:** Stores and modifies **memory locations**.<br>
✅ **Flag Handling:** Simulates **8085 status flags** *(S, Z, C, AC, P)*.<br>
✅ **Execution:** Reads a program from a file and executes **step by step**.<br>

---

### 🛠️ **Prerequisites**

Ensure you have the following installed:

🔹 **C++ Compiler** (`g++` or `clang++`)<br>
🔹 **C++ Standard Library** (supports **C++11** or later)<br>
🔹 **VS Code** (optional but recommended)<br>

---

### 🚀 **How to Run the Project**

#### **Step 1: Clone the Repository**
```bash
git clone https://github.com/your-username/8085-Simulator.git
cd 8085-Simulator
```

#### **Step 2: Compile the Project**
```bash
g++ -o hello kinjal.cpp -std=c++11
```

#### **Step 3: Run the Executable**
```bash
./hello
```

#### **Step 4: Input the 8085 Assembly Code**
The simulator reads instructions from a file. Make sure to create an input file **(`test.asm`)** with valid 8085 assembly instructions.

#### **Step 5: View Execution Output**
The program will **simulate execution** and display **register/memory changes**.

---

### 📂 **Project Structure**
```plaintext
SIMULATOR/
│── .vscode/               # VS Code configuration files
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│── hello.exe              # Sample compiled executable
│── kinjal.cpp             # Main execution file
│── kinjal.exe             # Compiled executable
│── test.asm               # Sample 8085 assembly input file
│── test.txt               # Output / log file
│── README.md              # Project documentation
```

---

### 💾 **Supported Instructions**

#### **🟢 One-Token Instructions**
`XCHG, CMC, CMA, STC, DAD, LSL, LSR`

#### **🔵 Two-Token Instructions**
`LDA, STA, LHLD, SHLD, LDAX, STAX, ADD, CMP, ADI, ADC, ACI, SUB, SUI, SBB, SBI, INR, DCR, INX, DCX, ANA, ANI, XRA, XRI, ORA, ORI`

#### **🟠 Three-Token Instructions**
`MOV, MVI, LXI`

---

### 📝 **Example Program (`test.asm`)**
```assembly
MVI A, 25H
MOV B, A
ADD B
HLT
```

#### **Expected Output:**
✅ Register **A** stores **25H**.<br>
✅ Register **B** gets value **25H**.<br>
✅ `A = A + B` → **Final A = 4AH**.<br>

---

### ❓ **Troubleshooting**

🔸 **Issue: Compilation error?**<br>
✔️ Ensure you're using **C++11** or later (`g++ -std=c++11`).<br>

🔸 **Issue: Execution stops unexpectedly?**<br>
✔️ Check `program.txt` for **syntax errors**.<br>

---

### 🚀 **Future Improvements**

🔹 **Support for more 8085 instructions**<br>
🔹 **GUI-based execution** (Qt/Electron.js)<br>
🔹 **Interactive debugging mode**<br>

---

### 👨‍💻 **Contributors**
📌 **Your Name** (*[@kinjal-05](https://github.com/kinjal-05)*)

---

### 📜 **License**
```plaintext
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software to deal in the Software without restriction.
