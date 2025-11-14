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