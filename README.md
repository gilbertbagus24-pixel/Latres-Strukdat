# 🧺 Aplikasi Pengelola Cucian Laundry

Aplikasi pengelola cucian laundry berbasis **C++** yang dirancang untuk membantu proses pencatatan, pengelolaan antrean, pemrosesan, hingga pengambilan cucian pelanggan.

Program ini dibuat untuk menyelesaikan permasalahan pencatatan cucian secara manual yang berpotensi menyebabkan urutan cucian tertukar dan nota sulit ditemukan kembali.

## 📌 Fitur Program

Program menyediakan beberapa fitur utama sebagai berikut:

### 1. Tambah Cucian
- Menambahkan cucian baru dengan memasukkan nomor nota dan nama cucian.
- Nomor nota harus berupa angka lebih dari 0.
- Nomor nota tidak boleh duplikat, baik pada antrean maupun daftar cucian selesai.
- Nama cucian tidak boleh kosong.
- Cucian baru ditambahkan pada posisi paling belakang antrean.

### 2. Lihat Cucian Dalam Antrean
- Menampilkan seluruh cucian yang masih menunggu untuk diproses.
- Data ditampilkan berdasarkan urutan antrean, mulai dari yang paling depan hingga paling belakang.
- Menampilkan error handling apabila antrean kosong.

### 3. Proses Cucian
- Memproses cucian yang berada di posisi paling depan antrean.
- Menghapus cucian dari penyimpanan antrean.
- Memindahkan cucian yang telah diproses ke:
  - Daftar cucian selesai, pada posisi paling atas.
  - Rak cucian yang disimpan menggunakan Binary Search Tree (BST).
- Menampilkan pemberitahuan setelah cucian berhasil diproses.

### 4. Lihat Cucian yang Sudah Selesai
- Menampilkan seluruh cucian yang telah selesai diproses.
- Data ditampilkan mulai dari posisi teratas hingga terbawah.
- Menampilkan error handling apabila belum terdapat cucian yang selesai diproses.

### 5. Cari Cucian di Rak
- Mencari cucian berdasarkan nomor nota.
- Menampilkan informasi cucian apabila ditemukan.
- Menampilkan error handling apabila rak kosong, nomor nota tidak valid, atau data tidak ditemukan.

### 6. Lihat Isi Rak
Menampilkan seluruh cucian yang tersimpan di rak menggunakan tiga metode traversal Binary Search Tree:

- **Pre-order:** Root → Left → Right
- **In-order:** Left → Root → Right
- **Post-order:** Left → Right → Root

Pengguna dapat memilih metode traversal yang diinginkan.

### 7. Ambil Cucian
- Mengambil cucian berdasarkan nomor nota.
- Menghapus data cucian dari rak apabila ditemukan.
- Menampilkan pemberitahuan apabila cucian berhasil diambil.
- Data pada daftar cucian selesai tetap disimpan meskipun cucian telah diambil dari rak.
- Penghapusan node BST harus menangani tiga kondisi: tanpa anak, satu anak, dan dua anak.

### 8. Keluar
Mengakhiri program.

---

## 🏗️ Struktur Data yang Digunakan

Program wajib menggunakan struktur data berikut:

### 1. Linked List

Linked List digunakan untuk menyimpan dua jenis data:

**Antrean Cucian**
- Menggunakan prinsip FIFO (First In, First Out).
- Cucian yang pertama masuk akan menjadi cucian pertama yang diproses.
- Penambahan data dilakukan pada bagian belakang antrean.
- Pemrosesan menghapus data dari bagian depan antrean.

**Cucian Selesai**
- Menyimpan seluruh cucian yang telah selesai diproses.
- Cucian yang baru selesai diproses ditempatkan pada posisi paling atas.
- Data tetap tersimpan meskipun cucian telah diambil pelanggan.

### 2. Binary Search Tree (BST)

Binary Search Tree digunakan untuk menyimpan cucian yang telah selesai diproses dan masih berada di rak menunggu pengambilan pelanggan.

Pengurutan node berdasarkan nomor nota dengan ketentuan:
- Nomor nota lebih kecil ditempatkan pada subtree kiri.
- Nomor nota lebih besar ditempatkan pada subtree kanan.

Operasi yang digunakan:
- Insert: Menambahkan cucian ke dalam BST.
- Search: Mencari cucian berdasarkan nomor nota.
- Delete: Menghapus cucian berdasarkan nomor nota.
- Traversal: Menampilkan isi rak menggunakan Pre-order, In-order, dan Post-order.

---

## 🔄 Alur Kerja Program

1. Pengguna membuka program dan ditampilkan halaman menu utama.
2. Pengguna memilih fitur yang tersedia.
3. Cucian baru dimasukkan ke dalam antrean menggunakan Linked List.
4. Cucian diproses berdasarkan urutan FIFO.
5. Setelah diproses, cucian dipindahkan ke daftar cucian selesai dan rak menggunakan BST.
6. Pengguna dapat melihat, mencari, atau menampilkan isi rak menggunakan traversal.
7. Ketika pelanggan mengambil cucian, data dihapus dari BST tetapi tetap tersimpan dalam daftar cucian selesai.
8. Pengguna dapat kembali ke menu utama atau keluar dari program.

---

## ⚙️ Ketentuan Program

- Bahasa pemrograman: **C++**
- Penyimpanan antrean wajib menggunakan Linked List.
- Penyimpanan cucian selesai wajib menggunakan Linked List.
- Penyimpanan rak wajib menggunakan Binary Search Tree.
- Tidak diperkenankan menggunakan Array.
- Tidak diperkenankan menggunakan STL Container, seperti:
  - `queue`
  - `stack`
  - `vector`
  - `set`
  - `map`
  - dan sejenisnya.
- Penghapusan node BST wajib menangani tiga kondisi:
  1. Node tanpa anak (Leaf Node).
  2. Node dengan satu anak.
  3. Node dengan dua anak.
- Setiap input harus memiliki validasi dan error handling.

---

## 💻 Cara Menjalankan Program

Pastikan compiler C++ telah terpasang pada komputer.

### 1. Clone Repository

```bash
git clone <repository-url>
```

### 2. Masuk ke Direktori Repository

```bash
cd <nama-repository>
```

### 3. Compile Program

```bash
g++ NIM_Latres.cpp -o laundry
```

### 4. Jalankan Program

**Linux:**
```bash
./laundry
```

**Windows:**
```bash
laundry.exe
```

---

## 📚 Tujuan Pembelajaran

Melalui program ini, diharapkan dapat memahami dan mengimplementasikan:

- Konsep Linked List.
- Implementasi antrean menggunakan prinsip FIFO.
- Pengelolaan data menggunakan Linked List.
- Konsep Binary Search Tree.
- Operasi Insert, Search, dan Delete pada BST.
- Tiga metode Tree Traversal.
- Penanganan berbagai kasus penghapusan node BST.
- Validasi input dan error handling dalam C++.

---

**Catatan:** Repository ini merupakan implementasi dari soal Latihan Responsi dengan studi kasus pengelolaan cucian laundry.
