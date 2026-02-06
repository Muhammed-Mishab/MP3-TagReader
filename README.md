# MP3-TagReader (ID3 METADATA PARSER)

The objective of this project is to design and implement an **MP3 Tag Reader** that extracts and displays metadata information stored in MP3 audio files using **ID3 tags**. The project focuses on understanding MP3 file structure, binary data parsing, and low-level file handling to retrieve details such as song title, artist name, album, genre, and year. This project provides hands-on experience with multimedia file formats and system-level programming concepts.

---

## Skills Learned

* Understanding of MP3 file structure and ID3 tag standards
* Binary file handling and parsing techniques
* Low-level data processing and byte manipulation
* File I/O operations in C / C++ / Python
* Data validation and error handling
* Working with multimedia metadata formats

---

## Tools Used

* **C** for low-level file parsing
* **Linux environment** for development and testing
* **GCC** compiler
* **Sample MP3 files** with ID3v1 / ID3v2 tags

---

## Steps

Below are the key steps involved in implementing the MP3 Tag Reader:

---

### 1. MP3 File Input

The MP3 file is provided as input to the program and opened in binary mode. This allows accurate reading of metadata bytes without altering the original file content.

---

### 2. ID3 Tag Detection

The program checks for the presence of **ID3 tags** (ID3v1 or ID3v2) at the beginning or end of the MP3 file. If a valid tag header is detected, the program proceeds with metadata parsing.

---

### 3. Metadata Parsing

Metadata fields such as title, artist, album, year, and genre are extracted by reading fixed-length fields or frame-based structures defined by the ID3 standard.

---

### 4. Data Conversion and Formatting

The extracted binary data is converted into human-readable text by handling appropriate character encoding formats such as ASCII or UTF-8.

---

### 5. Displaying Metadata Output

The parsed metadata is displayed in a structured and readable format through the terminal or application interface.

---
## Conclusion

This project successfully demonstrates the extraction of MP3 metadata by parsing **ID3 tags** using low-level file operations. It enhances understanding of binary file formats, multimedia data structures, and system programming. The MP3 Tag Reader has practical applications in media players, music libraries, and digital audio management systems.

---



