#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // Untuk setw dan left/right

using namespace std;

// Definisikan struktur data untuk menyimpan informasi karyawan
struct Karyawan {
    string nama;
    string NIP;
    string jabatan;
    double gajiPokok;
    double tunjangan;
    int jamKerja;
    double gajiTotal; // Tambahkan gajiTotal untuk menyimpan gaji total
};

// Fungsi untuk memisahkan string berdasarkan delimiter
vector<string> split(string str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Fungsi untuk membaca data karyawan dari file CSV
vector<Karyawan> bacaDataKaryawan(const string& namaFile) {
    vector<Karyawan> dataKaryawan;
    ifstream file(namaFile);

    if (file.is_open()) {
        string baris;
        while (getline(file, baris)) {
            vector<string> data = split(baris, ',');
            Karyawan karyawan;

            karyawan.nama = data[0];
            karyawan.NIP = data[1];
            karyawan.jabatan = data[2];
            karyawan.gajiPokok = stod(data[3]);
            karyawan.tunjangan = stod(data[4]);
            karyawan.jamKerja = stoi(data[5]);

            dataKaryawan.push_back(karyawan);
        }

        file.close();
        cout << "Data karyawan berhasil dimuat dari file CSV." << endl;
    } else {
        cout << "Gagal membuka file CSV!" << endl;
    }

    return dataKaryawan;
}

// Fungsi untuk menghitung gaji karyawan
void hitungGaji(vector<Karyawan>& dataKaryawan) {
    const int jamLemburPerHari = 8;
    const double gajiLemburPerJam = 1.5 * dataKaryawan[0].gajiPokok / jamLemburPerHari;

    for (Karyawan& karyawan : dataKaryawan) {
        int jamLembur = karyawan.jamKerja - (5 * jamLemburPerHari);
        double gajiLembur = jamLembur * gajiLemburPerJam;

        karyawan.gajiTotal = karyawan.gajiPokok + gajiLembur + karyawan.tunjangan;
    }
}

// Fungsi untuk mencetak tabel data karyawan
void cetakTabelKaryawan(const vector<Karyawan>& dataKaryawan) {
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "| Nama                 | NIP           | Jabatan       | Gaji Pokok | Tunjangan | Jam Kerja | Gaji Total |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;

    for (const Karyawan& karyawan : dataKaryawan) {
        cout << "| " << setw(20) << left << karyawan.nama << " | "
             << setw(15) << left << karyawan.NIP << " | "
             << setw(15) << left << karyawan.jabatan << " | "
             << setw(10) << right << karyawan.gajiPokok << " | "
             << setw(10) << right << karyawan.tunjangan << " | "
             << setw(10) << right << karyawan.jamKerja << " | "
             << setw(10) << right << karyawan.gajiTotal << " |" << endl;
    }

    cout << "+---------------------------------------------------------------------+" << endl;
}

int main() {
    const string namaFile = "penggajian_bulanan_maret_2024.csv";

    // Memuat data karyawan dari file CSV
    vector<Karyawan> dataKaryawan = bacaDataKaryawan(namaFile);

    // Hitung gaji total setiap karyawan
    hitungGaji(dataKaryawan);

    // Cetak tabel data karyawan
    cetakTabelKaryawan(dataKaryawan);

    return 0;
}
