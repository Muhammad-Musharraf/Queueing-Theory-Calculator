# 📊 Queueing Theory Calculator

A Windows-based desktop application developed in C++ using the Win32 API to analyze and compute performance metrics of queueing systems, specifically **M/M/1** and **M/M/c** models.

This project is developed as part of the **Software Engineering Fundamentals** course.

---

## 📌 Overview

Queueing theory is the mathematical study of waiting lines, used to predict system performance such as waiting time, queue length, and server utilization ([Wikipedia][1]).

This application provides a simple graphical interface that allows users to input system parameters and instantly compute key performance metrics for queueing systems.

---

## 🚀 Features

* ✔ GUI-based application using Win32 API
* ✔ Splash screen (Project introduction page)
* ✔ Supports:

  * **M/M/1 (Single Server Queue)**
  * **M/M/c (Multi-Server Queue)**
* ✔ Calculates:

  * Server Utilization (ρ)
  * Probability of Zero Customers (P₀)
  * Average Queue Length (Lq)
  * Average System Length (Ls)
  * Waiting Time in Queue (Wq)
  * Total Time in System (Ws)
* ✔ Simple and user-friendly interface
* ✔ Real-time calculation on button click

---

## 🧠 Queueing Models Used

### 🔹 M/M/1 Model

* Single server system
* Poisson arrivals and exponential service times
* Stability condition:
  **λ < μ**

### 🔹 M/M/c Model

* Multiple servers
* Parallel service channels
* Stability condition:
  **λ < c × μ**

These models are widely used in real-world systems like banking, networking, and customer service operations ([MetricGate][2]).

---

## 🖥️ Tech Stack

* **Language:** C++
* **Framework:** Win32 API
* **IDE:** Visual Studio / Code::Blocks
* **Concepts Used:**

  * Event-driven programming
  * Windows message loop
  * GUI controls (Edit, Button, Static)
  * Mathematical modeling

---

## 📂 Project Structure

```bash
Queueing-Theory-Calculator/
│
├── main.cpp          # Core application (GUI + logic)
├── README.md         # Project documentation
└── assets/           # (optional) screenshots
```

---

## ⚙️ How to Run

1. Clone the repository:

```bash
git clone https://github.com/Muhammad-Musharraf/Queueing-Theory-Calculator.git
```

2. Open in Visual Studio or any C++ IDE

3. Build and run the project

---

## 📸 Application Flow

1. **Splash Screen**

   * Displays project title and group members

2. **Main Calculator Window**

   * Input:

     * λ (Arrival Rate)
     * μ (Service Rate)
     * c (Number of servers)
   * Output:

     * Queue performance metrics

---

## 🎯 Learning Outcomes

This project demonstrates:

* Application of **Software Engineering Fundamentals**
* Implementation of **mathematical models in software**
* Understanding of **queueing theory concepts**
* Development of **GUI-based desktop applications**
* Problem-solving using **C++ and Win32 API**

---

## 📚 Applications of Queueing Theory

Queueing theory is used in:

* 📞 Call centers
* 🏥 Hospitals
* 💻 Computer networks
* 🏦 Banking systems
* 🚦 Traffic systems

It helps optimize resource usage and reduce waiting time in real-world systems ([FreeSmartCalculator][3]).

---

## 🔮 Future Improvements

* Graphical visualization of queue performance
* Support for more models (M/G/1, M/D/1)
* Input validation and error handling
* Single-window optimized UI architecture
* Export results feature

---

## 📄 License

This project is for educational purposes under Software Engineering Fundamentals.

---

## ⭐ Contribution

Feel free to fork, improve, and contribute!

---




