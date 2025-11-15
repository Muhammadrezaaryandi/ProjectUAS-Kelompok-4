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