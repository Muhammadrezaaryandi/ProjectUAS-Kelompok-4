#include "data.h"

// Fungsi untuk menampilkan seluruh alat yang tersedia
void lihat_alat() {
    // Memanggil fungsi tampilkan_alat() dari file alat.h
    tampilkan_alat();
}

// Fungsi untuk melakukan peminjaman alat
void pinjam_alat(const char *username) {
    // Membuka file data alat, file sementara, dan file untuk mencatat peminjaman
    FILE *fp = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *pinjam = fopen("peminjaman.txt", "a");

    // Mengecek apakah semua file berhasil dibuka
    if (!fp || !temp || !pinjam) {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    // Mendeklarasi variabel untuk menyimpan ID alat dan jumlah alat
    unsigned int id, jumlah;
    Alat alat;
    // Variabel found akan digunakan untuk mesngecek apakah ID alat ditemukan atau tidak
    int found = 0;

    // Meminta input ID alat dan jumlah alat yang ingin dipinjam user
    printf("Masukkan ID alat: ");
    scanf("%u", &id);
    printf("Jumlah yang dipinjam: ");
    scanf("%u", &jumlah);

    // Membaca isi file alat baris per baris
    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n",
       &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {

       // Mengecek apakah ID cocok dan stok mencukupi, maka lakukan peminjaman dan mengurangi stok di file alat.txt
       if (alat.id == id && alat.jumlah >= jumlah)
       {
           alat.jumlah -= jumlah;

           // Catat transaksi ke file peminjaman.txt
           fprintf(pinjam, "%s %u %s %u\n", username, alat.id, alat.nama, jumlah);
           printf("Peminjaman berhasil!\n");
           // Menandai bahwa alat ditemukan dan proses berhasil
           found = 1;
        }
        // Menulis data alat yang sudah diperbarui ataupun tidak ke file sementara
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }

    if (!found) {
        prinf("Alat tidak ditemukan atau stok kurang!\n");
    }

    // Menutup file dan mengganti file lama dengan file baru
    fclose(fp);
    fclose(temp);
    fclose(pinjam);
    remove("alat.txt");
    rename("temp.txt", "alat.txt");
}

// Fungsi untuk menampilkan alat yang sedang dipinjam user
void lihat_pinjaman(const char *username) {
    // Membuka file peminjaman.txt untuk dibaca
    FILE *fp = fopen("Peminjaman.txt", "r");
    if (!fp) {
        printf("Belum ada data peminjaman.\n");
        return;
    }

    Peminjaman p;
    printf("\n=== ALAT YANG DIPINJAM (%s) ===\n",  username);

    // Membaca riwayat peminjaman baris demi baris
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        // Menampilkan data yang hanya dimiliki user yang sama
        if (strcmp(p.username, username) == 0)
            printf("ID: %u | Nama: %s | Jumlah: %u\n", p.idAlat, p.namaAlat, p.jumlahPinjam);
    }

    fclose(fp);
}

// Fungsi untuk mengembalikan alat yang sebelumnya dipinjam oleh user
void kembalikan_alat(const char *username) {
    // Membuka file peminjaman, file sementara, file alat, dan file alat sementara
    FILE *fp = fopen("peminjaman.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *alatFile = fopen("alat.txt", "r");
    FILE *alatTemp = fopen("alatTemp.txt", "w");

    // Mengecek apakah semua file berhasil dibuka
    if (!fp || !temp || !alatFile || !alatTemp) {
        printf("Gagal membuka file!\n");
        return;
    }

    unsigned int id;
    // Meminta user untuk menginput ID alat yang ingin dikembalikan
    printf("Masukkan ID alat: ");
    scanf("%u", &id);

    // Struct untuk menyimpan data peminjaman dan data alat
    peminjaman p;
    Alat alat;

    int found = 0;
    unsigned int jumlahKembali = 0;

    // Menghapus data peminjaman sesuai ID alat yang dipinjam
    while (fscanf(fp, "%s %u %s %u", p.username, &p.idAlat, p.namaAlat, &p.jumlahPinjam) == 4) {
        // Mengecek apakah data milik user dan ID alat cocok, maka ambil jumlah yang dikembalikan
        if (strcmp(p.username, username) == 0 && p.idAlat == id) {
            jumlahKembali = p.jumlahPinjam;
            found = 1;
        } else {
            fprintf(temp, "%s %u %s %u\n", p.username, p.idAlat, p.namaAlat, p.jumlahPinjam);
        }
    }

    // Menutup file dan mengganti file lama dengan file baru
    fclose(fp);
    fclose(temp);
    remove("pemminjaman.txt");
    rename("temp.txt", "peminjaman.txt");

    // Menambah stok kembali ke file alat.txt
    while (fscanf(alatFile, "%u,%[^,],%[^,],%[^,],%u,%u\n", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6) {
        if (alat.id == id) {
            alat.jumlah += jumlahKembali;
        }
        fprintf(alatTemp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);