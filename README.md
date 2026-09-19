# CodeAlpha C++ Programming Internship Projects

This repository contains three completed CodeAlpha C++ internship tasks.

## Projects

### Task 1 - CGPA Calculator
- Takes course names, grades and credit hours.
- Calculates weighted grade points.
- Calculates semester GPA.
- Accepts previous semester GPA/credit data.
- Calculates final cumulative CGPA.
- Displays course-wise results.

### Task 2 - Login and Registration System
- User registration with validation.
- Duplicate username checking.
- Password confirmation.
- Local credential storage using `users.txt`.
- Login verification.
- Success/error messages.

> Note: This is an educational console project. A production authentication system should never store plaintext passwords; it should use salted password hashing and secure credential storage.

### Task 4 - Banking System
- Object-oriented design using `Customer`, `Account`, and `Transaction`.
- Customer and account creation.
- Deposits and withdrawals.
- Fund transfers.
- Transaction history.
- Account and customer information display.

## Compile

Use a C++17 compiler:

```bash
g++ -std=c++17 Task1_CGPA_Calculator/main.cpp -o cgpa
g++ -std=c++17 Task2_Login_Registration_System/main.cpp -o login
g++ -std=c++17 Task4_Banking_System/main.cpp -o banking
```

Run:

```bash
./cgpa
./login
./banking
```

## Suggested GitHub structure

```text
CodeAlpha_Cpp_Projects/
├── README.md
├── Task1_CGPA_Calculator/
│   └── main.cpp
├── Task2_Login_Registration_System/
│   └── main.cpp
└── Task4_Banking_System/
    └── main.cpp
```
