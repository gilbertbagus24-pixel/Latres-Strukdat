#include <iostream>

using namespace std;

struct nodeQueue {
    int nota;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int nota;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int nota;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = NULL;
nodeQueue* last = NULL;
nodeStack* top = NULL;
nodeTree* akar = NULL;

// menambahkan node baru ke tree berdasarkan nomor nota.
// nota lebih kecil masuk ke kiri, nota lebih besar masuk ke kanan.
// mengembalikan akar tree setelah penambahan.
nodeTree* tambah_tree(nodeTree* akar, int nota, string nama) {
    if (akar == NULL) {
        return new nodeTree {nota, nama, NULL, NULL};
    }
    if (nota < akar->nota) {
        akar->kiri = tambah_tree(akar->kiri, nota, nama);
    } else {
        akar->kanan = tambah_tree(akar->kanan, nota, nama);
    }
    return akar;
}

// mencari node di tree berdasarkan nomor nota.
// mengembalikan node yang ditemukan, atau null jika tidak ada.
nodeTree* cari_tree(nodeTree* akar, int nota) {
    if (akar == NULL || akar->nota == nota) {
        return akar;
    }
    if (nota < akar->nota) {
        return cari_tree(akar->kiri, nota);
    }
    return cari_tree(akar->kanan, nota);
}

// menghapus node di tree berdasarkan nomor nota.
// harus menangani 3 kasus: tanpa anak, satu anak, dan dua anak.
// mengembalikan akar tree setelah penghapusan.
nodeTree* hapus_tree(nodeTree* akar, int nota) {
    if (akar == NULL) {
        return NULL;
    }
    if (nota < akar->nota) {
        akar->kiri = hapus_tree(akar->kiri, nota);
    } else if (nota > akar->nota) {
        akar->kanan = hapus_tree(akar->kanan, nota);
    } else if (akar->kiri == NULL) {
        nodeTree* sisa = akar->kanan;
        delete akar;
        return sisa;
    } else if (akar->kanan == NULL) {
        nodeTree* sisa = akar->kiri;
        delete akar;
        return sisa;
    } else {
        nodeTree* pengganti = akar->kanan;
        while (pengganti->kiri != NULL) {
            pengganti = pengganti->kiri;
        }
        akar->nota = pengganti->nota;
        akar->nama = pengganti->nama;
        akar->kanan = hapus_tree(akar->kanan, pengganti->nota);
    }
    return akar;
}

// menampilkan isi tree dengan urutan: node, kiri, kanan.
// parameter no dipakai sebagai nomor urut tampilan.
void preorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    cout << no << ". [" << akar->nota << "] " << akar->nama << endl;
    no++;
    preorder(akar->kiri, no);
    preorder(akar->kanan, no);
}

// menampilkan isi tree dengan urutan: kiri, node, kanan.
// hasilnya akan terurut berdasarkan nomor nota.
void inorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    inorder(akar->kiri, no);
    cout << no << ". [" << akar->nota << "] " << akar->nama << endl;
    no++;
    inorder(akar->kanan, no);
}

// menampilkan isi tree dengan urutan: kiri, kanan, node.
void postorder(nodeTree* akar, int& no) {
    if (akar == NULL) {
        return;
    }
    postorder(akar->kiri, no);
    postorder(akar->kanan, no);
    cout << no << ". [" << akar->nota << "] " << akar->nama << endl;
    no++;
}

// meminta input nomor nota dan nama cucian, lalu memasukkannya ke queue (posisi paling belakang).
// error handling: nota bukan angka atau kurang dari 1, nota sudah dipakai
// (cek di queue dan stack), dan nama kosong.
void tambah_cucian() {
    int nota;
    string nama;
    cout << "Masukkan nomor nota: ";
    cin >> nota;
    if (cin.fail() || nota <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor nota harus berupa angka lebih dari 0!" << endl << endl;
        return;
    }

    nodeQueue* q = front;
    while (q != NULL) {cout << "Pilihan yang anda masukkan salah!" << endl;
                cout << "Silahkan coba lagi." << endl << endl;
        if (q->nota == nota) {
            cout << "Nomor nota sudah digunakan!" << endl << endl;
            return;
        }
        q = q->next;
    }
    nodeStack* s = top;
    while (s != NULL) {
        if (s->nota == nota) {
            cout << "Nomor nota sudah digunakan!" << endl << endl;
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama cucian: ";
    cin.ignore();
    getline(cin, nama);
    if (nama.empty()) {
        cout << "Nama cucian tidak boleh kosong!" << endl << endl;
        return;
    }

    nodeQueue* nb = new nodeQueue {nota, nama, NULL};
    if (front == NULL) {
        front = last = nb;
    } else {
        last->next = nb;
        last = nb;
    }
    cout << "Berhasil memasukkan cucian!" << endl << endl;

}

// menampilkan seluruh cucian di queue dari depan sampai belakang.
// error handling jika queue kosong.
void lihat_antrean() {
    if (front == NULL) {
        cout << "Antrean cucian masih kosong!" << endl << endl;
        return;
    }
    cout << "=== Cucian Dalam Antrean ===" << endl << endl;
    nodeQueue* nb = front;
    int no = 1;
    while (nb != NULL) {
        cout << no << ". [" << nb->nota << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

// mengambil cucian paling depan dari queue, lalu memindahkannya ke stack (posisi paling atas)
// dan memasukkannya ke tree (rak). node queue dihapus setelah dipindahkan.
// error handling jika queue kosong.
void proses_cucian() {
    if (front == NULL) {
        cout << "Antrean cucian masih kosong!" << endl << endl;
        return;
    }

    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack {hapus->nota, hapus->nama, top};
    top = nb;
    akar = tambah_tree(akar, hapus->nota, hapus->nama);
    cout << "Berhasil memproses cucian " << hapus->nama << "!" << endl << endl;
    front = hapus->next;
    if (front == NULL) {
        last = NULL;
    }
    delete hapus;
}

// menampilkan seluruh cucian di stack dari atas sampai bawah.
// error handling jika stack kosong.
void lihat_riwayat() {
    if (top == NULL) {
        cout << "Belum ada cucian yang selesai!" << endl << endl;
        return;
    }
    cout << "=== Cucian Yang Sudah Selesai ===" << endl << endl;
    nodeStack* nb = top;
    int no = 1;
    while (nb != NULL) {
        cout << no << ". [" << nb->nota << "] " << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

// meminta input nomor nota, lalu mencarinya di tree (rak) dan menampilkan datanya.
// error handling jika rak kosong, input nota tidak valid, atau nota tidak ditemukan.
void cari_cucian() {
    if (akar == NULL) {
        cout << "Rak masih kosong!" << endl << endl;
        return;
    }
    int nota;
    cout << "Masukkan nomor nota: ";
    cin >> nota;
    if (cin.fail() || nota <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor nota harus berupa angka lebih dari 0!" << endl << endl;
        return;
    }
    nodeTree* hasil = cari_tree(akar, nota);
    if (hasil == NULL) {
        cout << "Cucian dengan nota " << nota << " tidak ada di rak!" << endl << endl;
        return;
    }
    cout << "Ditemukan: [" << hasil->nota << "] " << hasil->nama << endl << endl;
}

// meminta user memilih pre-order, in-order, atau post-order,
// lalu menampilkan isi tree sesuai pilihan.
// error handling jika rak kosong atau pilihan tidak valid.
void lihat_rak() {
    if (akar == NULL) {
        cout << "Rak masih kosong!" << endl << endl;
        return;
    }
    char pil;
    int no = 1;
    cout << "=== Isi Rak Cucian ===" << endl << endl;
    cout << "1. Pre-order" << endl;
    cout << "2. In-order" << endl;
    cout << "3. Post-order" << endl << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pil;
    cout << endl;
    switch (pil) {
        case '1': {
            preorder(akar, no);
            break;
        }
        case '2': {
            inorder(akar, no);
            break;
        }
        case '3': {
            postorder(akar, no);
            break;
        }
        default: {
            cout << "Pilihan yang anda masukkan salah!" << endl;
        }
    }
    cout << endl;
}

// meminta input nomor nota cucian yang diambil pelanggan, lalu menghapusnya dari tree (rak).
// data di stack tidak ikut terhapus.
// error handling jika rak kosong, input nota tidak valid, atau nota tidak ditemukan.
void ambil_cucian() {
    if (akar == NULL) {
        cout << "Rak masih kosong!" << endl << endl;
        return;
    }
    int nota;
    cout << "Masukkan nomor nota: ";
    cin >> nota;
    if (cin.fail() || nota <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor nota harus berupa angka lebih dari 0!" << endl << endl;
        return;
    }
    nodeTree* hasil = cari_tree(akar, nota);
    if (hasil == NULL) {
        cout << "Cucian dengan nota " << nota << " tidak ada di rak!" << endl << endl;
        return;
    }
    cout << "Cucian " << hasil->nama << " telah diambil pelanggan!" << endl << endl;
    akar = hapus_tree(akar, nota);
}

// menampilkan menu utama dan memanggil fungsi sesuai pilihan user sampai user memilih keluar.
// menu: tambah cucian (bisa diulang), lihat antrean, proses cucian, lihat riwayat,
// cari cucian, lihat isi rak, ambil cucian, dan keluar.
// error handling jika pilihan di luar menu.
int main(){
    char pil = '0'; 
    while (pil != '8'){
        cout << "=== Manajemen Laundry Rani ===" << endl << endl;
        cout << "1. Tambah Cucian" << endl;
        cout << "2. Lihat Cucian Dalam Antrean" << endl;
        cout << "3. Proses Cucian" << endl;
        cout << "4. Lihat Cucian Yang Sudah Selesai" << endl;
        cout << "5. Cari Cucian Di Rak" << endl;
        cout << "6. Lihat Isi Rak" << endl;
        cout << "7. Ambil Cucian" << endl;
        cout << "8. Keluar" << endl << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pil;
        switch(pil){
            case '1' : {
                char pil_tambah = 'y';
                while(pil_tambah == 'y' || pil_tambah == 'Y'){
                    tambah_cucian();
                    cout << "Apakah anda ingin menambahkan cucian lagi? (y/n): ";
                    cin >> pil_tambah;
                }
                break;
            }
            case '2': {
                lihat_antrean();
                break;
            }
            case '3': {
                proses_cucian();
                break;
            }
            case '4': {
                lihat_riwayat();
                break;
            }
            case '5': {
                cari_cucian();
                break;
            }
            case '6': {
                lihat_rak();
                break;
            }
            case '7': {
                ambil_cucian();
                break;
            }
            case '8': {
                cout << "Exiting program";
                exit(0);
            }
            default : {
                cout << "Pilihan yang anda masukkan salah!" << endl;
                cout << "Silahkan coba lagi." << endl << endl;
                
            }

        }
    } 

}
