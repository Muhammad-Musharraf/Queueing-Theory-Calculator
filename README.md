<div align="center">

<h1>📊 Queueing Theory Calculator</h1>

<p>
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img src="https://img.shields.io/badge/Platform-Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white"/>
  <img src="https://img.shields.io/badge/API-Win32-lightgrey?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge"/>
</p>

<p>
  A <strong>Windows desktop application</strong> built in C++ with the Win32 API that computes
  real-time performance metrics for <strong>M/M/1</strong> and <strong>M/M/c</strong> queueing models —
  developed as part of the <em>Software Engineering Fundamentals</em> course.
</p>

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Queueing Models](#-queueing-models)
- [Formulas Reference](#-formulas-reference)
- [Tech Stack](#️-tech-stack)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Application Flow](#-application-flow)
- [Use Cases](#-real-world-use-cases)
- [Future Improvements](#-future-improvements)
- [License](#-license)

---

## 🔍 Overview

Queueing theory is the mathematical study of waiting lines (queues) used to predict and optimise system performance — including waiting times, queue lengths, and server utilisation.

This application provides a clean, GUI-based desktop interface where users can:

- Enter system parameters (arrival rate, service rate, number of servers)
- Instantly view computed performance metrics
- Understand both single-server and multi-server queue behaviour

> Applicable in real-world domains such as banking, call centres, hospitals, computer networks, and traffic systems.

---

## 🚀 Features

| Feature | Description |
|---|---|
| 🖥️ Native GUI | Built entirely with the Win32 API — no external UI frameworks |
| 🎬 Splash Screen | Project introduction screen on launch |
| 🔢 M/M/1 Calculator | Single-server queue analysis with exact formulas |
| 🔢 M/M/c Calculator | Multi-server queue analysis with Erlang C |
| ⚡ Real-time Output | Metrics computed instantly on button click |
| 🎯 Clean Layout | Separate input and output sections for clarity |

---

## 🧠 Queueing Models

### 🔹 M/M/1 — Single Server Queue

| Property | Detail |
|---|---|
| Arrivals | Poisson process with rate **λ** |
| Service | Exponential distribution with rate **μ** |
| Servers | **1** |
| Stability | **λ < μ** (utilisation ρ < 1) |
| Queue discipline | FCFS (First Come, First Served) |

### 🔹 M/M/c — Multi-Server Queue

| Property | Detail |
|---|---|
| Arrivals | Poisson process with rate **λ** |
| Service | Exponential distribution with rate **μ** per server |
| Servers | **c** parallel servers |
| Stability | **λ < c × μ** (utilisation ρ = λ/(cμ) < 1) |
| Queue discipline | FCFS — shared queue feeds all servers |

---

## 📐 Formulas Reference

### Common Definitions

| Symbol | Meaning |
|---|---|
| λ | Arrival rate (customers/time unit) |
| μ | Service rate per server (customers/time unit) |
| c | Number of servers |
| ρ | Server utilisation |

---

### M/M/1 Formulas

| Metric | Formula |
|---|---|
| **Utilisation** | ρ = λ / μ |
| **Prob. 0 customers (P₀)** | P₀ = 1 − ρ |
| **Prob. n customers (Pₙ)** | Pₙ = (1 − ρ) · ρⁿ |
| **Avg. queue length (Lq)** | Lq = ρ² / (1 − ρ) |
| **Avg. system length (Ls)** | Ls = ρ / (1 − ρ) |
| **Avg. wait in queue (Wq)** | Wq = λ / [μ(μ − λ)] |
| **Avg. time in system (Ws)** | Ws = 1 / (μ − λ) |

---

### M/M/c Formulas

| Metric | Formula |
|---|---|
| **Utilisation** | ρ = λ / (c · μ) |
| **Prob. 0 customers (P₀)** | P₀ = [ Σₙ₌₀^(c-1) (λ/μ)ⁿ/n! + (λ/μ)ᶜ / (c! · (1−ρ)) ]⁻¹ |
| **Erlang C — Prob. waiting** | C(c, λ/μ) = [(λ/μ)ᶜ / (c! · (1−ρ))] · P₀ |
| **Avg. queue length (Lq)** | Lq = C(c, λ/μ) · ρ / (1 − ρ) |
| **Avg. system length (Ls)** | Ls = Lq + λ/μ |
| **Avg. wait in queue (Wq)** | Wq = Lq / λ |
| **Avg. time in system (Ws)** | Ws = Wq + 1/μ |

> **Little's Law** (universal): `L = λ · W` and `Lq = λ · Wq`

---

## 🛠️ Tech Stack

```
Language   →  C++
GUI        →  Win32 API (native Windows)
IDE        →  Visual Studio / Code::Blocks
Paradigm   →  Event-driven programming (Windows message loop)
Controls   →  Edit boxes, Buttons, Static labels
Math       →  Standard C math library
```

---

## 📂 Project Structure

```
Queueing-Theory-Calculator/
│
├── .vscode/                  # VS Code workspace settings
│
├── Project Files/            # C++ source and resource files
│   ├── main.cpp              # Core application — GUI layout + queueing logic
│   ├── resource.h            # Win32 resource identifiers
│   └── *.rc / *.sln          # Project & solution files
│
├── Project Pictures/         # Screenshots of the running application
│
└── README.md                 # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites

- Windows OS (7 / 10 / 11)
- Visual Studio (recommended) **or** MinGW/Code::Blocks with Win32 support
- No external libraries required

### Build & Run

**Option A — Visual Studio**

```bash
# 1. Clone the repository
git clone https://github.com/Muhammad-Musharraf/Queueing-Theory-Calculator.git

# 2. Open the solution file in Visual Studio
#    File → Open → Project/Solution → select .sln inside "Project Files/"

# 3. Build  →  Ctrl + Shift + B
# 4. Run    →  F5  (or Ctrl + F5 for release)
```

**Option B — Command Line (MinGW)**

```bash
git clone https://github.com/Muhammad-Musharraf/Queueing-Theory-Calculator.git
cd "Queueing-Theory-Calculator/Project Files"

g++ main.cpp -o QueueCalc.exe -mwindows -lgdi32
./QueueCalc.exe
```

> ⚠️ The `-mwindows` flag is required to suppress the console window and enable the Win32 GUI subsystem.

---

## 🖥️ Application Flow

```
┌─────────────────────────────────┐
│         LAUNCH APP              │
└────────────────┬────────────────┘
                 │
                 ▼
┌─────────────────────────────────┐
│         SPLASH SCREEN           │
│  · Project title                │
│  · Group members                │
│  · Course information           │
└────────────────┬────────────────┘
                 │  (Click to continue)
                 ▼
┌─────────────────────────────────┐
│     MAIN CALCULATOR WINDOW      │
│                                 │
│  Select Model:  M/M/1 | M/M/c  │
│                                 │
│  INPUT                          │
│  ├─ λ  Arrival Rate             │
│  ├─ μ  Service Rate             │
│  └─ c  Number of Servers        │
│            [Calculate]          │
│                                 │
│  OUTPUT                         │
│  ├─ ρ    Utilisation            │
│  ├─ P₀   Prob. empty system     │
│  ├─ Lq   Avg. queue length      │
│  ├─ Ls   Avg. system length     │
│  ├─ Wq   Avg. wait in queue     │
│  └─ Ws   Avg. time in system    │
└─────────────────────────────────┘
```

---

## 🌍 Real-World Use Cases

Queueing theory — and tools like this — are applied across many industries:

| Domain | Application |
|---|---|
| 📞 Call Centres | Optimise agent count vs. customer wait time |
| 🏥 Healthcare | Model patient flow in ERs and clinics |
| 💻 Networks | Analyse packet queuing in routers |
| 🏦 Banking | Design ATM or teller service capacity |
| 🚦 Traffic | Model intersection delays and lane throughput |
| ☁️ Cloud Computing | Tune request handling in web servers |

---

## 🎯 Learning Outcomes

This project demonstrates practical application of:

- **Software Engineering** principles (design, implementation, documentation)
- **Mathematical modelling** in software (translating formulas to code)
- **Native GUI development** via the Win32 API message loop
- **Event-driven programming** patterns in C++
- **Queueing theory** concepts applied to real system analysis

---

## 🔮 Future Improvements

- [ ] Input validation with descriptive error messages
- [ ] Support for additional models: M/G/1, M/D/1, G/G/1
- [ ] Graphical charts showing queue length vs. utilisation
- [ ] Export results to CSV or PDF
- [ ] Single-window UI with tab-based model switching
- [ ] Cross-platform port (Qt or wxWidgets)

---

## 📄 License

This project was developed for **educational purposes** as part of the *Software Engineering Fundamentals* course.
Feel free to fork, adapt, and build upon it with attribution.

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature`
3. Commit your changes: `git commit -m "Add your feature"`
4. Push and open a Pull Request

---

<div align="center">

Made with ❤️ using C++ and Win32 API

⭐ If this project helped you, consider starring the repo!

</div>
