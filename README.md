# Hex and Binary Reader

A lightweight console-based hex editor and binary file inspector written in **C++**. The application provides a paginated view of binary files, allowing users to inspect raw data in **hexadecimal**, **binary**, and **ASCII** representations, as well as modify individual bytes directly.

---

## Features

-  View binary files in **hexadecimal** and **ASCII** formats.
-  Optional **8-bit binary** representation for every byte.
-  Paginated navigation for large files.
-  Direct in-place editing of individual bytes by file offset.
-  Supports both **hexadecimal** and **binary** input when editing.
-  Automatically extends the file when writing beyond its current size.
-  Simple interactive command-line interface.

---

## Technologies

- **C++17**
- **STL**
- **Binary File I/O (`fstream`)**
- **`std::bitset`**
- **Windows Console API**

---


## Project Structure

The application implements:

- Binary file reading
- Hex dump generation
- Binary conversion utilities
- Byte-level file editing
- Paginated navigation
- Interactive console interface

---

## Output Format

Each row displays:

- **File offset**
- **16 bytes in hexadecimal**
- **Optional binary representation**
- **Printable ASCII characters**

### Hex + ASCII

```text
00000020  48 65 6C 6C 6F 20 57 6F  72 6C 64 21 00 FF 1A 7E  |Hello World!...~|
```

### Binary Mode

```text
01001000 01100101 01101100 01101100 01101111 ...
```

---

## Editing

The editor allows modifying any byte by specifying:

1. File offset (hexadecimal)
2. Input mode (**Hex** or **Binary**)
3. New byte value

Changes are written directly to the original file without creating temporary copies.

---

## Purpose

This project was created as a practical exercise in low-level file manipulation and binary data processing using modern **C++**. It demonstrates working with binary streams, random-access file operations, byte-oriented processing, formatted output, and the implementation of a simple interactive command-line utility.
