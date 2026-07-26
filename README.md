# C-Blood-Bank-System
# 🩸 Blood Bank Management System

A console-based **Blood Bank Management System** developed in **C++** using fundamental **Data Structures and Algorithms (DSA)** concepts. The project efficiently manages donors, patients, blood inventory, emergency requests, and donation history while demonstrating the practical implementation of linked lists, binary search trees, queues, and stacks.

---

## 📌 Project Overview

The Blood Bank Management System is designed to simplify the management of blood donations and requests within a hospital or blood bank environment. It provides separate interfaces for **Donors, Patients, Nurses, and Managers**, ensuring organized access to system functionalities.

The project focuses on applying core DSA concepts to solve real-world management problems without relying on external libraries or databases.

---

## ✨ Features

### 👤 Donor Module
- Register new donors
- Validate age, blood group, phone number, and CNIC
- Prevent duplicate CNIC and phone numbers
- View donor details
- Check blood compatibility
- Donate blood and update inventory automatically

### 🏥 Patient Module
- Register patients
- Blood group validation
- Emergency level assignment
- View patient details
- Check compatible blood groups
- View current blood inventory

### 👨‍⚕️ Nurse Module
- Secure login authentication
- View all donors
- View all patients
- Register new donors and patients
- Search donor/patient by ID
- Access blood inventory

### 👨‍💼 Manager Module
- Secure login authentication
- Complete donor management
- Complete patient management
- Search donor/patient records
- Delete donor and patient records
- Add blood units
- Remove blood units
- Monitor blood inventory

### 🩸 Blood Inventory
- Supports all major blood groups:
  - A+
  - A-
  - B+
  - B-
  - AB+
  - AB-
  - O+
  - O-
- Automatic inventory updates after donation
- Blood compatibility checking

### 📂 File Handling
- Stores donor records
- Stores patient records
- Persistent record management using text files

---

# 🛠 Data Structures Implemented

This project was built to demonstrate practical applications of fundamental data structures.

| Data Structure | Purpose |
|---------------|---------|
| Linked List | Store donor records |
| Linked List | Store patient records |
| Linked List | Store blood inventory |
| Binary Search Tree (BST) | Fast searching of donor and patient IDs |
| Queue | Emergency blood request management (FIFO) |
| Stack | Donation history (LIFO) |

---

# 📖 Data Structure Usage

### Linked List
- Donor Management
- Patient Management
- Blood Inventory

### Binary Search Tree
- Fast searching of donors
- Fast searching of patients

### Queue
- Emergency blood request processing
- First request served first

### Stack
- Stores recent blood donations
- Displays donation history

---

# ✅ Input Validation

The system validates:

- Donor age (18–65 years)
- Patient age
- Blood group
- Phone number (11 digits)
- CNIC (13 digits)
- Duplicate phone numbers
- Duplicate CNICs
- Emergency level
- Blood compatibility

---

# 🔐 Authentication

Role-based login system for:

- Manager
- Nurse

Features:

- Username/password authentication
- Three login attempts
- Account lock after failed attempts

---

# 📁 Project Structure

```
BloodBankManagementSystem/

│── main.cpp
│── donor.txt
│── patient.txt
│── README.md
```

---

# 💻 Technologies Used

- C++
- Object-Oriented Programming
- File Handling
- Data Structures
- Console Application

---

# 📚 Concepts Practiced

This project strengthened my understanding of:

- Linked Lists
- Binary Search Trees
- Queue
- Stack
- File Handling
- Dynamic Memory Allocation
- Input Validation
- Searching Algorithms
- CRUD Operations
- Modular Programming
- Menu-driven Applications

---

# 🚀 Future Enhancements

Some improvements planned for future versions include:

- Graphical User Interface (GUI)
- Web-based application
- Database integration (MySQL/SQLite)
- QR Code-based donor identification
- Email/SMS notifications
- Blood expiry management
- Appointment scheduling
- Hospital integration
- Report generation
- Analytics dashboard
- Multi-user support
- Password encryption
- Cloud deployment

---

# 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Applying DSA concepts to real-world problems
- Designing modular C++ applications
- Managing dynamic data structures
- Implementing secure login systems
- Handling file-based storage
- Developing scalable console applications

---

# 📸 Sample Workflow
<img width="239" height="95" alt="image" src="https://github.com/user-attachments/assets/7d0cef97-9306-4f96-8c1b-62306ffb3605" />
<img width="230" height="115" alt="image" src="https://github.com/user-attachments/assets/550eab2b-c1c7-422f-9095-d8e07283c04e" />
<img width="239" height="119" alt="image" src="https://github.com/user-attachments/assets/e0e3246d-b01b-4159-9835-26ef7523635e" />
<img width="237" height="333" alt="image" src="https://github.com/user-attachments/assets/f50762d7-6d68-48d9-953d-27640eb637b2" />
<img width="230" height="301" alt="image" src="https://github.com/user-attachments/assets/28a81892-032c-4635-8dc3-7a97da1e9f38" />

```
Main Menu
│
├── Donor
│     ├── Register
│     ├── View Details
│     ├── Check Compatibility
│     └── Donate Blood
│
├── Patient
│     ├── Register
│     ├── View Details
│     ├── Compatibility
│     └── Inventory
│
├── Nurse
│     ├── Login
│     ├── Manage Donors
│     ├── Manage Patients
│     └── Inventory
│
└── Manager
      ├── Login
      ├── Manage Donors
      ├── Manage Patients
      ├── Inventory
      ├── Queue Requests
      └── Donation History
```

---

# 🤝 Contributing

Contributions, suggestions, and improvements are welcome.

1. Fork the repository
2. Create a new feature branch
3. Commit your changes
4. Open a Pull Request

---

# 📜 License

This project is developed for educational and learning purposes.

---
