# 📊 Employee Management System

This C-based console application provides a robust and efficient way to manage employee and department data. It's built with a focus on dynamic memory management, file handling, and data analysis, making it a powerful tool for small-scale HR data processing.

### 📂 Project Structure

The project is organized into three distinct files to ensure a clean and modular design:

  * `proje1.h`: The **header file** where all data structures (`struct Calisan` and `struct Birim`) are defined, along with function prototypes. It serves as the project's interface.
  * `proje1.c`: The **implementation file** containing the full logic for all functions declared in `proje1.h`. This is where the core functionality resides, including dynamic memory allocation, file I/O, and data processing.
  * `main.c`: The **main program file**. It demonstrates how to use the project's functions by reading data from external files, performing various operations, and printing the results to the console.

### 📝 Data Structures

  * `Calisan` (Employee): Represents an employee's record. It includes `calisanAdi` (first name), `calisanSoyadi` (last name), `birimKodu` (department code), `maas` (salary), and `girisYili` (start year).
  * `Birim` (Department): Represents a department. It includes `birimAdi` (department name), `birimKodu` (department code), a dynamic array of pointers to `Calisan` structs (`birimCalisanlar`), and the total number of employees in that department (`calisanSayisi`).

-----

### ✨ Key Features

This application offers a range of functionalities to manage and analyze your employee data:

  * **Data Management**: Dynamically allocates memory for new employees and departments, expanding arrays as needed.
  * **File I/O**: Efficiently imports data from `Birimler.txt` and `Calisanlar.txt` and can export data back to files for persistent storage.
  * **Salary Analysis**: Calculates the average salary for any given department and identifies which employees earn above that average.
  * **Reporting**: Generates reports for the highest-paid employee in each department.
  * **Data Updates**: Automatically updates salaries for employees who have worked for more than 10 years, ensuring they meet a specified minimum.
  * **Memory Safety**: Includes a dedicated function to properly free all dynamically allocated memory, preventing memory leaks.

-----

### 🚀 How to Compile and Run

1.  **Open your terminal** and navigate to the project directory.
2.  **Compile the source files** using a C compiler like GCC. The following command compiles `main.c` and `proje1.c` and links them into a single executable named `personnel_manager`:
    ```bash
    gcc main.c proje1.c -o personnel_manager
    ```
3.  **Run the executable** with your data files as command-line arguments. The `main.c` file expects the department file first, followed by the employee file.
    ```bash
    ./personnel_manager Birimler.txt Calisanlar.txt
    ```

### 📄 Input File Format

The program expects a specific format for its input files, with fields separated by a semicolon (`;`).

**`Birimler.txt`:**

```
IT;01
Guvenlik;02
Mühendislik;03
```

*Format: `<Department Name>;<Department Code>`*

**`Calisanlar.txt`:**

```
Mehmet Enes;Erden;01;100000;2022
Furkan;Erden;01;45000;2010
Ekrem;Bas;02;120000;2020
```

*Format: `<First Name>;<Last Name>;<Department Code>;<Salary>;<Start Year>`*

-----

### 📋 Full Function Reference

| Function Name | Description |
| :--- | :--- |
| `birimOlustur` | Creates and initializes a new `Birim` (Department) struct. |
| `calisanOlustur` | Creates and initializes a new `Calisan` (Employee) struct. |
| `calisaniBirimeEkle` | Adds a `Calisan` to a `Birim`'s internal employee list. |
| `calisanlarıDiziyeEkle` | Adds a new `Calisan` to the main dynamic employee array. |
| `birimleriDiziyeEkle` | Adds a new `Birim` to the main dynamic department array. |
| `iceAktarBirim` | Reads and imports department data from a specified file. |
| `iceAktarCalisan` | Reads and imports employee data from a specified file. |
| `dısaAktarBirim` | Exports department data from the program to a file. |
| `dısaAktarCalisan` | Exports employee data from the program to a file. |
| `birimOrtMaas` | Calculates the average salary of a given department. |
| `yüksekMaasAlanlar` | Prints employees in a department whose salary is above average. |
| `enZenginler` | Identifies and prints the highest-paid employee for each department. |
| `minimumMaas` | Updates the salary of employees with more than 10 years of service. |
| `tumVeriyiSerbestBirak`| Frees all dynamically allocated memory. **Essential for preventing memory leaks.** |

-----
