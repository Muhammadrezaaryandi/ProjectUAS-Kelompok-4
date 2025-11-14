#include "data.h"

// Bagian ini digunakan untuk membaca sebuah file teks
// dan mengembalikan jumlah baris yang ada di dalam file tersebut.
int hitung_baris_file(char *namaFile) 
{
    FILE *fp = fopen(namaFile, "r");
    if (!fp) return 0;
    int count = 0;
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), fp)) count++;
    fclose(fp);
    return count;
}

// Bagian ini berfungsi untuk membaca semua data alat dari file "alat.txt"
void tampilkan_alat()
{
    FILE *fp = fopen("alat.txt", "r");
    if(!fp)
    {
        printf("Belum ada data alat.\n");
        return;
    }

    Alat alat;
    printf("\n=== DAFTAR ALAT LAB ===\n");
    printf("%-5s %-20s %-15s %-15s %-7s %s\n", 
           "ID", "Nama", "Merek", "Model", "Tahun", "Jumlah");
    printf("========================================================================\n");

    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%u,%u\n", 
        &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah) == 6)
        {