# <span style="color:#1E90FF; font-size: 2.5em;">8085 Simulator</span>  

## <span style="color:#FFA500;">Overview</span>  
This project is an **8085 microprocessor simulator** implemented in **C++**. It simulates the execution of **8085 assembly instructions**, allowing users to run programs and observe register and memory changes.  
The simulator supports various **8085 instructions** like `MOV`, `MVI`, `LXI`, `LDA`, `STA`, `LHLD`, `SHLD`, `ADD`, `SUB`, `CMP`, and more.  

---

## <span style="color:#20B2AA;">🚀 Features</span>  
✅ **Instruction Parsing:** Reads and executes **8085 assembly instructions**.  
✅ **Register Operations:** Simulates **8085 registers** (`A, B, C, D, E, H, L`).  
✅ **Memory Management:** Stores and modifies memory locations.  
✅ **Flag Handling:** Simulates **8085 status flags** (`S, Z, C, AC, P`).  
✅ **Program Execution:** Reads an assembly program from a file and executes it step by step.  

### <span style="color:#FF4500;">Instruction Categorization:</span>  
📌 **One-token instructions:** `XCHG`, `CMC`, `CMA`, `STC`, `DAD`, etc.  
📌 **Two-token instructions:** `LDA`, `STA`, `LHLD`, `SHLD`, etc.  
📌 **Three-token instructions:** `MOV`, `MVI`, `LXI`, etc.  
📌 **8-bit & 16-bit Instructions**  

---

## <span style="color:#FFD700; font-size: 1.5em;">📌 Prerequisites</span>  
Ensure you have the following installed on your system:  
🔹 **C++ Compiler** (`g++` or `clang++`)  
🔹 **C++ Standard Library** (supports **C++11 or later**)  
🔹 **VS Code** _(optional but recommended)_  

---

## <span style="color:#32CD32;">💻 How to Run the Project</span>  

### 🔹 Step 1: Clone the Repository  
```sh
git clone https://github.com/your-username/8085-Simulator.git
cd 8085-Simulator
