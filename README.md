<div align="center">

# 🎬 "Chi Bebinam?" (What to Watch?)

### A Smart Movie Recommender System with dual interfaces (CLI & GUI), built with C++ and SFML.

<p>
    <a href="#-key-features"><b>Features</b></a> •
    <a href="#-technologies-used"><b>Technologies</b></a> •
    <a href="#-professional-concepts"><b>Professional Concepts</b></a> •
    <a href="#-how-to-run"><b>Setup Guide</b></a>
</p>

</div>

---

## 🚀 About the Project

This project was designed as a comprehensive application of all the software engineering principles learned during my Advanced Programming (AP) course.

I built a movie recommendation system that suggests films based on user history or general trends. The highlight of this project lies in **how it was implemented**. I leveraged modern C++ features, software design principles (like <b>SOLID</b>), design patterns (like <b>Strategy</b>), and finally, the <b>SFML</b> library to craft a sleek, aesthetic graphical user interface.

The project offers two distinct outputs:
1. A **Command Line Interface (CLI)** for rapid execution and logic testing.
2. A **Graphical User Interface (GUI)** with a modern look, images, and smooth animations for an enhanced user experience.

---

## ✨ Key Features

<table align="center" width="100%">
  <tr>
    <td align="center" width="33%">
      <b>Dual Interface (CLI & GUI)</b><br>
      <small>Works seamlessly via terminal commands or through an engaging graphical interface built with SFML.</small>
    </td>
    <td align="center" width="33%">
      <b>Smart Recommendation System</b><br>
      <small>Provides personalized suggestions for users with history, and general statistics-based recommendations for new users.</small>
    </td>
    <td align="center" width="33%">
      <b>Principled Coding</b><br>
      <small>Full utilization of advanced OOP concepts, design patterns, and modern C++17 features.</small>
    </td>
  </tr>
</table>

---

## 🛠 Technologies Used

<p align="center">
  <a href="[https://isocpp.org/](https://isocpp.org/)"><img src="[https://img.shields.io/badge/C++-17-blue.svg?style=for-the-badge&logo=c%2B%2B](https://img.shields.io/badge/C++-17-blue.svg?style=for-the-badge&logo=c%2B%2B)" alt="C++17"></a>
  &nbsp;
  <a href="[https://www.sfml-dev.org/](https://www.sfml-dev.org/)"><img src="[https://img.shields.io/badge/SFML-2.6-green.svg?style=for-the-badge&logo=sfml](https://img.shields.io/badge/SFML-2.6-green.svg?style=for-the-badge&logo=sfml)" alt="SFML"></a>
  &nbsp;
  <a href="[https://www.gnu.org/software/make/](https://www.gnu.org/software/make/)"><img src="[https://img.shields.io/badge/Makefile-GNU-blueviolet.svg?style=for-the-badge&logo=gnu-make](https://img.shields.io/badge/Makefile-GNU-blueviolet.svg?style=for-the-badge&logo=gnu-make)" alt="Makefile"></a>
</p>

---

## 🏛️ Professional Concepts

### 1. Advanced OOP 🏛️
* **Encapsulation:** Each class manages its own data and behaviors (e.g., `Film` and `User` classes).
* **Abstraction:** Complexity is hidden behind simple interfaces. The `Recommender` class acts as an engine, while the GUI interacts only with its high-level methods.
* **Inheritance & Polymorphism:** An interface `IScoringStrategy` is defined, with `HistoryScorer` and `GenericScorer` inheriting from it, allowing the system to treat both scoring algorithms uniformly.

### 2. SOLID Design Principles 🧱
* **Single Responsibility:** Every class has one specific job (e.g., `Recommender` manages logic, `Scorer` classes handle math).
* **Open/Closed:** The architecture is open for extension but closed for modification. Adding a new scoring algorithm simply requires a new `IScoringStrategy` implementation.
* **Dependency Inversion:** The high-level `Recommender` class depends on the `IScoringStrategy` abstraction, not on low-level concrete classes.

### 3. Modern C++ (C++17) ✨
* **Smart Pointers (`std::unique_ptr`):** Used for automated, memory-safe resource management.
* **STL:** Heavy use of `std::vector`, `std::map`, and `std::set` for efficient data management.
* **Lambda Expressions:** Used for defining sorting logic and button event handlers, keeping the code modular and clean.

### 4. Advanced Patterns 🛠️
* **Strategy Pattern:** Completely decouples scoring algorithms from the core logic for high flexibility.
* **State Machine:** Uses `enum class AppState` in the GUI version to manage navigation (login, menu, results) cleanly without nested code.
* **Advanced Build System (Makefile):** A professional `Makefile` that compiles two separate executables (`ChiBebinam` and `ChiBebinam_sfml`) from a shared codebase.

### 5. Templates
To avoid code duplication and follow the **DRY (Don't Repeat Yourself)** principle, I implemented a generic `DataLoader<T>` template class. Instead of having separate, redundant functions for reading films and users, this template handles any data type from CSV files efficiently.

---

## ⚙️ How to Run

<details>
  <summary><b>Install SFML on Ubuntu</b></summary>
  <br>
  <p>Run the following command in your terminal:</p>
  <pre><code>sudo apt-get install libsfml-dev</code></pre>
</details>

<br>

1. **Compile:** Simply run `make` in the project root directory. It will build both the CLI and GUI versions.
   <pre><code>make</code></pre>

2. **Execute:**
   * **CLI Version:**
       <pre><code>./ChiBebinam path/to/users/file.csv path/to/films/file.csv</code></pre>
   * **GUI Version (Recommended):**
       <pre><code>./ChiBebinam_sfml path/to/users/file.csv path/to/films/file.csv</code></pre>

---

<table align="center" width="90%" style="background-color: #44475a; color: #f8f8f2; padding: 15px; border-radius: 10px;">
  <tr>
    <td>
      <h3 style="color: #ffb86c; margin-top: 0;">Important Note</h3>
      <p>
        The GUI version (<code>ChiBebinam_sfml</code>) relies on the specific <code>films.csv</code> and <code>users.csv</code> files included with the project. The actor photos, genre icons, and movie posters are manually mapped to names provided in these files. Using different datasets may cause the application to load successfully, but it will be unable to locate or display the associated images.
      </p>
    </td>
  </tr>
</table>
