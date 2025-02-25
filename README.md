# Employee Management System (Managify)

Managify is a comprehensive C++ application designed to streamline the management of employee records, leaves, and payroll within an organization. This system provides a user friendly interface for both administrators and employees, enabling efficient handling of employee data, leave requests, and report generation.

## Features

- **Employee Management**:
  - Add, edit, and remove employee records.
  - Search for employees by ID or name.
  - Display all employee details.

- **Leave Management**:
  - Employees can check their remaining leave balance.
  - Employees can request leave, and the system ensures leave requests do not exceed the available balance.

- **Payroll and Leave Reports**:
  - Admins can generate detailed payroll and leave reports in CSV format.

- **User Authentication**:
  - Separate login and signup functionalities for admins and employees.
  - Credentials are securely stored in CSV files.

- **Data Persistence**:
  - All employee data is stored in a CSV file (`employee.csv`), ensuring records are retained even after the program is closed.

---

## Folder Structure

```
EmployeeManagementSystem/
├── data/ (all CSV files are stored here)
│   ├── admin_credentials.csv
│   ├── employee_credentials.csv
│   ├── employee.csv
│   ├── payroll_report.csv
│   ├── leave_report.csv
│   ├── login_attempts.log
├── include/ (header files)
│   ├── Emp.h
│   ├── Company.h
│   ├── User.h
│   ├── utils.h
├── src/ (source files)
│   ├── main.cpp
│   ├── Emp.cpp
│   ├── Company.cpp
│   ├── User.cpp
│   ├── utils.cpp
├── README.md (this file)
```

---

## Prerequisites

- **C++ Compiler**: Ensure you have a C++17-compliant compiler (e.g., `g++`).
- **Git**: To clone and manage the repository.

---

## Setup and Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/VVenkatesh215/Managify.git
   cd Managify
   ```

2. **Compile the Program**:
   Navigate to the `src/` directory and compile the program:
   ```bash
   cd src
   g++ -std=c++17 -I../include main.cpp Emp.cpp Company.cpp User.cpp utils.cpp -o managify.exe
   ```

3. **Run the Program**:
   Execute the compiled program:
   ```bash
   ./managify.exe
   ```

---

## Usage

### Main Menu
- **Admin**:
  - Sign up or log in as an admin.
  - Add, edit, or remove employees.
  - Generate payroll and leave reports.

- **Employee**:
  - Sign up or log in as an employee.
  - View personal details.
  - Check leave balance and request leave.

- **Exit**:
  - Exit the program.

---

## File Descriptions

- **`data/`**:
  - `admin_credentials.csv`: Stores admin login credentials.
  - `employee_credentials.csv`: Stores employee login credentials.
  - `employee.csv`: Stores employee records.
  - `payroll_report.csv`: Generated payroll report.
  - `leave_report.csv`: Generated leave report.
  - `login_attempts.log`: Logs login attempts.

- **`include/`**:
  - Header files for the project (`Emp.h`, `Company.h`, `User.h`, `utils.h`).

- **`src/`**:
  - Source files for the project (`main.cpp`, `Emp.cpp`, `Company.cpp`, `User.cpp`, `utils.cpp`).

---

## Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes.
4. Push your changes to your fork.
5. Submit a pull request.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- This project was developed as part of a learning exercise to demonstrate C++ programming skills and file handling.
- Special thanks to the open-source community for providing valuable resources and tools.

---

## Contact

For any questions or feedback, feel free to reach out:

- **Name**: Venkatesh V
- **Email**: your-email@example.com
- **GitHub**: [VVenkatesh215](https://github.com/VVenkatesh215)

---

Enjoy using **Managify**! Let me know if you have any questions or need further assistance. 😊# Managify
The Employee Management System (Managify) is a comprehensive C++ application designed to streamline the management of employee records, leaves, and payroll within an organization. This system provides a user-friendly interface for both administrators and employees, enabling efficient handling of employee data, leave requests, and report generation.
