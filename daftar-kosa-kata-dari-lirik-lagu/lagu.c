#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD 100
#define MAX_LINE 1000
#define MAX_WORDS 5000

// Bagian ini untuk mengubah karakter dalam string menjadi huruf kecil
void toLowerCase(char *str) 
{ 
    for(int i = 0; str[i]; i++)
        {str[i] = tolower(str[i]);}
}

// Bagian ini untuk menghapus semua karakter kecuali huruf, spasi, dan karakter (')
void cleanText(char *str)
{ int j = 0;
  for(int i = 0; str[i] != '\0'; i++) {
     if(isalpha(str[i]) || str[i] == ' ' || str[i] == '\'') {  
        str[j++] = str[i];
     }
  }
  str[j] = '\0';
}

//Mengecek apakah kata sudah pernah ada sebelumnya
int isDuplicate(char words[][MAX_WORD], Int count, char *word) {
  for(int i = 0; i < count; i++) {
     if(strcmp(words[i], word) == 0)
        return 1;
  }
  return 0;
}

int main() {
  //Deklarasi variabel untuk file input dan output, buffer dan baris, daftar kata, penghitung kata unik, dan judul lagu
  FILE *fin, *fout;
  char line[MAX_LINE];
  char words[MAX_WORDS][MAX_WORD];
  int count = 0;
  char title[200];

  //Membuka file lirik untuk dibaca
  fin = fopen("lirik.txt", "r");
  if (!fin){
      printf("File lirik.txt tidak ditemukan!\n");
      return 1;
  }

  //Membuat file output untuk menulis kosa-kata
  fout = fopen("kosa-kata.txt", "w");
  if (!fout) {
      printf("Gagal membuat file kosa-kata.txt!\n");
      fclose(fin);
      return 1;
  }

  //Membaca baris pertama sebagai judul lagu nantinya
  fgets(title, sizeof(title), fin);
  fprintf(fout, "%s", title);
  
    // Membaca lirik baris demi baris
    while (fgets(line, sizeof(line), fin)) {

        // Memanggil fungsi untuk mengubah lirik jadi huruf kecil
        toLowerCase(line);

        // Memanggil fungsi untuk membersihkan karakter yang tidak perlu
        cleanText(line);

        // Mengambil kata satu-per-satu
        char *token = strtok(line, " ");
        while (token != NULL) {

            // Lewati token kosong atau hanya karakter (')
            if (strlen(token) > 0 && !(strlen(token) == 1 && token[0] == '\'')) {

                // Jika kata belum pernah muncul, maka disimpan
                if (!isDuplicate(words, count, token)) {
                    strcpy(words[count], token);