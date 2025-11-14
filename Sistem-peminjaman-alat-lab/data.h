#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Berbagai header
// =============================
// STRUCT DATA
// =============================
typedef struct {
    unsigned int id;
    char nama[50];
    char merek[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah;
} Alat;

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // "admin" atau "user"
} Akun;

typedef struct {
    char username[50];
    unsigned int idAlat;
    char namaAlat[50];
    unsigned int jumlahPinjam;
} Peminjaman;