#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

string formatRupiah(int number) {
    string str = to_string(number);
    int len = str.length();
    int dLen = 3;

    while (len > dLen) {
        str.insert(len - dLen, 1, ',');
        dLen += 4;
        len += 1;
    }
    return "Rp. " + str;
}

struct Karyawan {
    string nama;
    string NIP;
    string jabatan;
    int gaji_perhari;
    int tunjangan;
    int harikerja;
    int gajiTotal;
};

int bacaDataKaryawan(const string& namaFile, Karyawan* dataKaryawan, int maxKaryawan) {
    ifstream file(namaFile);
    int count = 0;

    if (file.is_open()) {
        string baris;
        
        while (getline(file, baris) && count < maxKaryawan) {
            stringstream ss(baris);
            string kolom;
            Karyawan karyawan;

            getline(ss, kolom, ',');
            karyawan.nama = kolom;
            getline(ss, kolom, ',');
            karyawan.NIP = kolom;
            getline(ss, kolom, ',');
            karyawan.jabatan = kolom;
            getline(ss, kolom, ',');
            karyawan.gaji_perhari = stoi(kolom);
            getline(ss, kolom, ',');
            karyawan.tunjangan = stoi(kolom);
            getline(ss, kolom, ',');
            karyawan.harikerja = stoi(kolom);

            dataKaryawan[count++] = karyawan;
        }
        file.close();
        cout << "Data karyawan berhasil dimuat dari file CSV." << endl;
    } else {
        cout << "Gagal membuka file CSV!" << endl;
    }

    return count;
}

void hitungGaji(Karyawan* dataKaryawan, int jumlahKaryawan) {
    for (int i = 0; i < jumlahKaryawan; i++) {
        dataKaryawan[i].gajiTotal = (dataKaryawan[i].gaji_perhari * dataKaryawan[i].harikerja) + dataKaryawan[i].tunjangan;
    }
}

void cetakTabelKaryawan(const Karyawan* dataKaryawan, int jumlahKaryawan) {
    cout << "+----------------------------------------------------------------------------------------------------------+" << endl;
    cout << "| Nama     | NIP          | Jabatan    | Gaji Pokok    | Tunjangan     | Jam Kerja  | Gaji Total           |" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------+" << endl;

    for (int i = 0; i < jumlahKaryawan; ++i) {
        cout << "| " << setw(8) << left << dataKaryawan[i].nama << " | "
             << setw(12) << left << dataKaryawan[i].NIP << " | "
             << setw(10) << left << dataKaryawan[i].jabatan << " | "
             << setw(13) << left << formatRupiah(dataKaryawan[i].gaji_perhari) << " | "
             << setw(13) << left << formatRupiah(dataKaryawan[i].tunjangan) << " | "
             << setw(10) << left << dataKaryawan[i].harikerja << " | "
             << setw(20) << left << formatRupiah(dataKaryawan[i].gajiTotal) << " |" << endl;
    }

    cout << "+----------------------------------------------------------------------------------------------------------+" << endl;
}

int main() {
    const string namaFile = "penggajian_bulanan_maret_2024.csv";
    const int maxKaryawan = 100;
    Karyawan dataKaryawan[maxKaryawan];

    int jumlahKaryawan = bacaDataKaryawan(namaFile, dataKaryawan, maxKaryawan);
    hitungGaji(dataKaryawan, jumlahKaryawan);
    cetakTabelKaryawan(dataKaryawan, jumlahKaryawan);

    return 0;
}
