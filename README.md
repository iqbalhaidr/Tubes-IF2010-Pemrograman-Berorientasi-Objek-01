# Tugas Besar 1 IF2010 Pemrograman Berorientasi Objek 2024/2025
### Deskripsi Singkat

Tugas Besar ini adalah sebuah program simulasi berbasis CLI (Command-Line Interface) yang dikembangkan menggunakan bahasa C++ dan menerapkan prinsip Pemrograman Berorientasi Objek (OOP) dan materi mengenai bahasa C++ yang telah dipelajari pada mata kuliah Pemrograman Berbasis Objek IF2010.

Program ini dirancang dengan berbagai kelas dan objek, serta menerapkan prinsip-prinsip seperti enkapsulasi, inheritance, polimorfisme, dan abstraksi untuk OOP serta penggunaan STL dari bahasa C++. Program harus dapat dikompilasi dan dijalankan di sistem operasi Linux/UNIX, menggunakan Makefile sebagai sistem build.

---
## Prasyarat Sistem

### Persyaratan Kompilasi
* **Compiler:** GCC versi 11.0 atau lebih baru
* **Standar C++:** C+11 / C++14 / C++17
* **Sistem Operasi:** Linux/Unix (Ubuntu 20.04 LTS atau lebih baru disarankan)
* **Dukungan untuk Windows:** Gunakan WSL (Windows Subsystem for Linux) jika menggunakan Windows

* **Dependensi Library:**
  * build-essential
  * g++
  * make

### Instalasi Dependensi (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential g++ make
```

---

## Cara Penggunaan

### Kompilasi Program

1. **Clone Repository**
   ```bash
   https://github.com/Labpro-21/if2010-2425-tubes-1-lah
   ```
2. **Build dan Kompilasi Program**
   ```bash
   make 
   ```

3. **Jalankan Program:**
   ```bash
   cd bin
   ./game 
   ```

4. **Membersihkan File:**
   ```bash
   make clean
   ```


---

## Pembagian Tugas

<table border="1">
  <tr>
    <th>Nama Anggota</th>
    <th>NIM</th>
    <th>Tugas Utama</th>
  </tr>
  <tr>
    <td>Muhammad Aufa Farabi</td>
    <td>13523023</td>
    <td>Unit, Character, Mobs, Damage</td>
  </tr>
  <tr>
    <td>Joel Hotlan Haris Siahaan</td>
    <td>13523025</td>
    <td>Shop, Mobs</td>
  </tr>
  <tr>
    <td>Julius Arthur</td>
    <td>13523030</td>
    <td>Skill & Effect</td>
  </tr>
  <tr>
    <td>Ferdinand Gabe Tua Sinaga</td>
    <td>13523051</td>
    <td>Items & Inventory</td>
  </tr>
  <tr>
    <td>Muhammad Iqbal Haidar</td>
    <td>13523111</td>
    <td>Dungeon</td>
  </tr>
</table>

---

## Daftar Fitur


<table border="1">
  <tr>
    <th>Nama Fitur</th>
    <th>Status</th>
    <th>Nama Fitur</th>
    <th>Status</th>
  </tr>
  <tr>
    <td>Unit</td>
    <td align="center">✓</td>
    <td>Character</td>
    <td align="center">✓</td>
  </tr>
  <tr>
    <td>Skill dan Skillpath</td>
    <td align="center">✓</td>
    <td>Effect</td>
    <td align="center">✓</td>
  </tr>
  <tr>
    <td>Dungeon</td>
    <td align="center">✓</td>
    <td>Mobs</td>
    <td align="center">✓</td>
  </tr>
  <tr>
    <td>Shop</td>
    <td align="center">✓</td>
    <td>Items</td>
    <td align="center">✓</td>
  </tr>
  <tr>
    <td>Damage</td>
    <td align="center">✓</td>
    <td>Inventory</td>
    <td align="center">✓</td>
  </tr>
  <tr>
    <td>Save/Load</td>
    <td align="center">✓</td>
    <td></td>
    <td></td>
  </tr>
</table>

---
