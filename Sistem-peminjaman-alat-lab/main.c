#include <stdio.h>
#include <string.h> 
#include "data.h"

void garis() {
    printf("========================================================================\n");
}

// Fungsi utama program
int main(int argc, char *argv[]) {

        // Validasi jumlah argumen command line
    if (argc < 3) 
    {
        printf("Format: %s <username> <password>\n", argv[0]);
        return 1;
    }

    // Variabel untuk menyimpan role user
    char role[10];
    
    // Proses login dengan memanggil fungsi login dari alat.h
    if (!login(argv[1], argv[2], role)) 
    {
        printf("[!] Login gagal. Username atau password salah.\n");
        return 0;
    }

    // Tampilan setelah login berhasil