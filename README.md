# 🏦 Bank Management System (C++)

A console-based bank management application built with **C++**. It manages client accounts and transactions, and stores all data in a plain text file.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Status](https://img.shields.io/badge/Status-Completed-success)

---

## 📸 Demo

<!-- Drag a screenshot or GIF of the main menu here while editing -->

---

## ✨ Features

### Client Management
| Feature | Description |
|---|---|
| **Show Clients** | Displays all clients in a formatted table |
| **Add Client** | Adds one or more clients, rejects duplicate account numbers |
| **Delete Client** | Finds the client, asks for confirmation, then deletes |
| **Update Client** | Edits a client's details after confirmation |
| **Find Client** | Searches for a client by account number |

### Transactions
| Feature | Description |
|---|---|
| **Deposit** | Adds an amount to a client's balance |
| **Withdraw** | Subtracts an amount, and blocks it if it exceeds the balance |
| **Total Balances** | Lists every client's balance with the overall total |

---

## 🛠️ Tech & Concepts Used

- **Language:** C++
- **IDE:** Visual Studio
- **Concepts:** structs, vectors, enums, file handling (`fstream`), string splitting, functions, references, input validation

---

## 🗂️ How Data Is Stored

Each client is one line in the `Clients` file, with fields separated by `#//#`:

```
AccountNumber#//#PINCode#//#Name#//#Phone#//#Balance
```

Example:

```
A101#//#1234#//#Ahmed Ali#//#0100000000#//#5000.000000
```

---

## 🧩 How It Works

Every operation follows the same pattern:

```
Load file → vector  →  Find the record  →  Modify the vector  →  Save vector → file
```

The code is split into three layers:

1. **Data layer:** reading, writing and converting records to and from lines
2. **Logic layer:** find, add, delete, update, deposit and withdraw
3. **UI layer:** screens and menus

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR-USERNAME/Bank-Management-System-CPP.git
   ```
2. Open `Bank Project.vcxproj` in **Visual Studio**
3. Make sure the `Clients` file is in the same folder the program runs from
4. Build and run with **Ctrl + F5**

> The `Clients` file in this repo contains dummy data for testing.

---

## 📚 What I Learned

- Reading and writing files, and using them as a simple database
- Designing small functions that each do one job
- Passing by reference vs. by value
- Debugging real issues, like an early `close()` wiping data, a missing `break` in a `switch`, and empty lines in the file crashing the program

---


## 👤 Author

**Youssef Omar**
[LinkedIn](www.linkedin.com/in/youssef-omar-665b82305) · [GitHub](https://github.com/youssefomar10-10)
