#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Struct untuk menyimpan informasi tanggal dan acara
struct Tanggal {
    int hari;
    int bulan;
    int tahun;
    char acara[50];
};

// Enum untuk nama bulan
enum Bulan { JANUARI = 1, FEBRUARI, MARET, APRIL, MEI, JUNI, JULI, AGUSTUS, SEPTEMBER, OKTOBER, NOVEMBER, DESEMBER };

// Fungsi untuk menampilkan kalender
void tampilkanKalender(int bulan, int tahun) {
    printf("\nKalender Bulan %d Tahun %d:\n", bulan, tahun);
    printf("Sen Sel Rab Kam Jum Sab Min\n");

    // Tentukan jumlah hari dalam bulan
    int jumlahHari;
    if (bulan == FEBRUARI) {
        jumlahHari = (tahun % 4 == 0 && (tahun % 100 != 0 || tahun % 400 == 0)) ? 29 : 28;
    } else if (bulan == APRIL || bulan == JUNI || bulan == SEPTEMBER || bulan == NOVEMBER) {
        jumlahHari = 30;
    } else {
        jumlahHari = 31;
    }

    // Menentukan hari pertama (Algoritma Sederhana)
    int hariPertama = (1 + 2 * bulan + (3 * (bulan + 1)) / 5 + tahun + tahun / 4 - tahun / 100 + tahun / 400) % 7;
    if (hariPertama == 0) hariPertama = 7;

    // Menampilkan tanggal
    for (int i = 1; i < hariPertama; i++) {
        printf("    ");
    }

    for (int i = 1; i <= jumlahHari; i++) {
        printf("%3d ", i);
        if ((i + hariPertama - 1) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Fungsi untuk menambahkan acara pada tanggal tertentu
void tambahAcara(struct Tanggal kalender[], int *jumlahAcara) {
    printf("\nMasukkan Tanggal (dd mm yyyy): ");
    scanf("%d %d %d", &kalender[*jumlahAcara].hari, &kalender[*jumlahAcara].bulan, &kalender[*jumlahAcara].tahun);
    getchar(); // Membersihkan buffer

    printf("Masukkan Acara: ");
    fgets(kalender[*jumlahAcara].acara, 50, stdin);
    strtok(kalender[*jumlahAcara].acara, "\n"); // Menghapus newline di akhir string

    (*jumlahAcara)++;
    printf("Acara berhasil ditambahkan!\n");
}

// Fungsi untuk menyimpan acara ke dalam file
void simpanAcaraKeFile(struct Tanggal kalender[], int jumlahAcara) {
    FILE *file = fopen("acara.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    for (int i = 0; i < jumlahAcara; i++) {
        fprintf(file, "%d %d %d %s\n", kalender[i].hari, kalender[i].bulan, kalender[i].tahun, kalender[i].acara);
    }

    fclose(file);
    printf("Data acara berhasil disimpan ke file!\n");
}

// Fungsi untuk membaca acara dari file
void bacaAcaraDariFile(struct Tanggal kalender[], int *jumlahAcara) {
    FILE *file = fopen("acara.txt", "r");
    if (file == NULL) {
        printf("File acara.txt tidak ditemukan. Tidak ada data yang dimuat.\n");
        return;
    }

    *jumlahAcara = 0;
    while (fscanf(file, "%d %d %d %[^\n]", &kalender[*jumlahAcara].hari, 
                  &kalender[*jumlahAcara].bulan, 
                  &kalender[*jumlahAcara].tahun, 
                  kalender[*jumlahAcara].acara) == 4) {
        (*jumlahAcara)++;
    }

    fclose(file);
    printf("Data acara berhasil dimuat dari file!\n");
}


// Fungsi untuk menampilkan daftar acara
void tampilkanAcara(struct Tanggal kalender[], int jumlahAcara) {
    printf("\nDaftar Acara:\n");
    for (int i = 0; i < jumlahAcara; i++) {
        printf("Tanggal: %02d-%02d-%04d, Acara: %s\n",
               kalender[i].hari, kalender[i].bulan, kalender[i].tahun, kalender[i].acara);
    }
}

// Fungsi untuk mencari acara berdasarkan tanggal
void cariAcara(struct Tanggal kalender[], int jumlahAcara) {
    int hari, bulan, tahun;
    printf("\nMasukkan Tanggal untuk mencari acara (dd mm yyyy): ");
    scanf("%d %d %d", &hari, &bulan, &tahun);

    bool ditemukan = false;
    for (int i = 0; i < jumlahAcara; i++) {
        if (kalender[i].hari == hari && kalender[i].bulan == bulan && kalender[i].tahun == tahun) {
            printf("Acara ditemukan: %s\n", kalender[i].acara);
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        printf("Tidak ada acara pada tanggal tersebut.\n");
    }
}

// Fungsi untuk mengurutkan acara berdasarkan tanggal (Bubble Sort)
void urutkanAcara(struct Tanggal kalender[], int jumlahAcara) {
    for (int i = 0; i < jumlahAcara - 1; i++) {
        for (int j = 0; j < jumlahAcara - i - 1; j++) {
            if (kalender[j].tahun > kalender[j + 1].tahun ||
                (kalender[j].tahun == kalender[j + 1].tahun && kalender[j].bulan > kalender[j + 1].bulan) ||
                (kalender[j].tahun == kalender[j + 1].tahun && kalender[j].bulan == kalender[j + 1].bulan && kalender[j].hari > kalender[j + 1].hari)) {
                struct Tanggal temp = kalender[j];
                kalender[j] = kalender[j + 1];
                kalender[j + 1] = temp;
            }
        }
    }
    printf("Acara berhasil diurutkan berdasarkan tanggal.\n");
}

int main() {
    struct Tanggal kalender[100]; // Array untuk menyimpan acara
    int jumlahAcara = 0;         // Jumlah acara yang terdaftar

    // Memuat data acara dari file
    bacaAcaraDariFile(kalender, &jumlahAcara);

    int pilihan;
    do {
        printf("\n=== Kalender Digital Interaktif ===\n");
        printf("1. Tampilkan Kalender\n");
        printf("2. Tambah Acara\n");
        printf("3. Tampilkan Acara\n");
        printf("4. Cari Acara\n");
        printf("5. Urutkan Acara\n");
        printf("6. Simpan dan Keluar\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                int bulan, tahun;
                printf("\nMasukkan Bulan dan Tahun (mm yyyy): ");
                scanf("%d %d", &bulan, &tahun);
                tampilkanKalender(bulan, tahun);
                break;
            }
            case 2:
                tambahAcara(kalender, &jumlahAcara);
                break;
            case 3:
                tampilkanAcara(kalender, jumlahAcara);
                break;
            case 4:
                cariAcara(kalender, jumlahAcara);
                break;
            case 5:
                urutkanAcara(kalender, jumlahAcara);
                break;
            case 6:
                simpanAcaraKeFile(kalender, jumlahAcara);
                printf("Keluar dari program. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid, coba lagi.\n");
        }
    } while (pilihan != 6);

    return 0;
}
