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