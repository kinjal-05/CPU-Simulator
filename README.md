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
g++ -o simulator main.cpp -std=c++11
```

#### **Step 3: Run the Executable**
```bash
./simulator
```

#### **Step 4: Input the 8085 Assembly Code**
The simulator reads instructions from a file. Make sure to create an input file **(`program.txt`)** with valid 8085 assembly instructions.

#### **Step 5: View Execution Output**
The program will **simulate execution** and display **register/memory changes**.

---

### 📂 **Project Structure**
```plaintext
8085-Simulator/
│── main.cpp            # Main execution file
│── execute.cpp         # Instruction execution logic
│── instructions.h      # Supported instruction sets
│── registers.h         # Register and flag definitions
│── memory.h            # Memory management
│── utils.h             # Utility functions (trim, conversions, etc.)
│── program.txt         # Sample 8085 assembly input file
│── README.md           # Project documentation
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

### 📝 **Example Program (`program.txt`)**
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
📌 **Your Name** (*[@your-username](https://github.com/your-username)*)

---

### 📜 **License**
```plaintext
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software to deal in the Software without restriction.
