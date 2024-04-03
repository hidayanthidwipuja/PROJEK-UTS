#include <iostream>
#include <string>

using namespace std;

float NilaiMahasiswa[5];

struct Mahasiswa {
    string Nama;
    string Kelas;
    string Npm;
    float NilaiMahasiswa[5];
    char IP;
    Mahasiswa* next; // Pointer ke node berikutnya dalam linked list
};

class MahasiswaList {
private:
    Mahasiswa* head; // Pointer ke elemen pertama dalam linked list
public:
    MahasiswaList() : head(nullptr) {} // Constructor untuk inisialisasi head

    // Method untuk menambahkan data mahasiswa ke linked list
    void tambahData() {
        Mahasiswa* baru = new Mahasiswa();
        cout << "\nMasukkan Data Mahasiswa\n\n";
        cout << "Masukkan NPM: ";
        cin >> baru->Npm;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, baru->Nama);
        cout << "Masukkan Nilai Absen: ";
        baru->NilaiMahasiswa[0] = MasukanNilai();
        cout << "Masukkan Nilai Tugas: ";
        baru->NilaiMahasiswa[1] = MasukanNilai();
        cout << "Masukkan Nilai UTS: ";
        baru->NilaiMahasiswa[2] = MasukanNilai();
        cout << "Masukkan Nilai UAS: ";
        baru->NilaiMahasiswa[3] = MasukanNilai();

        // Menghitung nilai akhir dan predikat
        baru->NilaiMahasiswa[4] = 0.1 * baru->NilaiMahasiswa[0] +
                                     0.2 * baru->NilaiMahasiswa[1] +
                                     0.3 * baru->NilaiMahasiswa[2] +
                                     0.4 * baru->NilaiMahasiswa[3];
        PredikatPadaNilai(baru);

        baru->next = head;
        head = baru;
    }

    // Method untuk menampilkan seluruh data mahasiswa dalam linked list
    void tampilkanData() {
        Mahasiswa* current = head;
        int counter = 1;
        while (current != nullptr) {
            cout << "Data Mahasiswa ke-" << counter << endl << endl;
            cout << "Nama: " << current->Nama << endl;
            cout << "NPM: " << current->Npm << endl;
            cout << "Nilai Mahasiswa ke-" << counter << endl;
            cout << "Nilai absen: " << current->NilaiMahasiswa[0] << endl;
            cout << "Nilai tugas: " << current->NilaiMahasiswa[1] << endl;
            cout << "Nilai UTS: " << current->NilaiMahasiswa[2] << endl;
            cout << "Nilai UAS: " << current->NilaiMahasiswa[3] << endl;
            cout << "Nilai Akhir " << current->NilaiMahasiswa[4] << " Mahasiswa Mendapatkan Predikat " << current->IP << endl;
            cout << endl;
            current = current->next;
            counter++;
        }
    }

    // Method untuk menghapus data mahasiswa berdasarkan NPM
    void hapusData(string Npm) {
        Mahasiswa* current = head;
        Mahasiswa* prev = nullptr;
        while (current != nullptr) {
            if (current->Npm == Npm) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Data dengan NPM " << Npm << " telah dihapus." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Data dengan NPM " << Npm << " tidak ditemukan." << endl;
    }

    // Method untuk mencari data mahasiswa berdasarkan NPM dan mengeditnya
    void editData(string Npm) {
        Mahasiswa* current = head;
        while (current != nullptr) {
            if (current->Npm == Npm) {
                cout << "Edit Data Mahasiswa:" << endl;
                cout << "Masukkan Nama: ";
                cin.ignore();
                getline(cin, current->Nama);
                cout << "Masukkan Nilai Absen: ";
                current->NilaiMahasiswa[0] = MasukanNilai();
                cout << "Masukkan Nilai Tugas: ";
                current->NilaiMahasiswa[1] = MasukanNilai();
                cout << "Masukkan Nilai UTS: ";
                current->NilaiMahasiswa[2] = MasukanNilai();
                cout << "Masukkan Nilai UAS: ";
                current->NilaiMahasiswa[3] = MasukanNilai();

                // Menghitung nilai akhir dan predikat
                current->NilaiMahasiswa[4] = 0.1 * current->NilaiMahasiswa[0] +
                                             0.2 * current->NilaiMahasiswa[1] +
                                             0.3 * current->NilaiMahasiswa[2] +
                                             0.4 * current->NilaiMahasiswa[3];
                PredikatPadaNilai(current);

                cout << "Data berhasil diubah." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Data dengan NPM " << Npm << " tidak ditemukan." << endl;
    }

    // Method untuk memasukkan nilai dengan validasi
    float MasukanNilai() {
        float nilai;
        do {
            cin >> nilai;
            if (nilai > 100 || nilai < 0) {
                cout << "Nilai yang dimasukkan tidak valid. Silakan masukkan kembali: ";
            }
        } while (nilai > 100 || nilai < 0);
        return nilai;
    }

    // Method untuk menentukan predikat pada nilai
    void PredikatPadaNilai(Mahasiswa* mahasiswa) {
        if (mahasiswa->NilaiMahasiswa[4] >= 80) {
            mahasiswa->IP = 'A';
        } else if (mahasiswa->NilaiMahasiswa[4] >= 70) {
            mahasiswa->IP = 'B';
        } else if (mahasiswa->NilaiMahasiswa[4] >= 60) {
            mahasiswa->IP = 'C';
        } else if (mahasiswa->NilaiMahasiswa[4] >= 50) {
            mahasiswa->IP = 'D';
        } else {
            mahasiswa->IP = 'E';
        }
    }

    // Destructor untuk menghapus seluruh elemen dalam linked list
    ~MahasiswaList() {
        Mahasiswa* current = head;
        while (current != nullptr) {
                        Mahasiswa* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr; // Set head menjadi nullptr setelah semua elemen dihapus
    }
};

int main() {
    MahasiswaList daftarMahasiswa;

    int pilihan;
    string npm;

    do {
        cout << "\nSelamat Datang di Program Manajemen Data Mahasiswa\n";
        cout << "Menu:\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Edit Data Mahasiswa\n";
        cout << "4. Hapus Data Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                daftarMahasiswa.tambahData();
                break;
            case 2:
                daftarMahasiswa.tampilkanData();
                break;
            case 3:
                cout << "Masukkan NPM mahasiswa yang akan di-edit: ";
                cin >> npm;
                daftarMahasiswa.editData(npm);
                break;
            case 4:
                cout << "Masukkan NPM mahasiswa yang akan dihapus: ";
                cin >> npm;
                daftarMahasiswa.hapusData(npm);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}

