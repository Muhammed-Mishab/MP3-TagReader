#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

//ID3v2 HEADER STRUCT (10 bytes) 
typedef struct
{
    char id[3];               // Always "ID3"
    unsigned char version[2]; // Version bytes
    unsigned char flags;      // Flags byte
    unsigned char size[4];    // Tag size 
} ID3v2Header;

//ID3v2 FRAME HEADER STRUCT (10 bytes per frame) 
typedef struct
{
    char frame_id[5];         // Frame ID (e.g., "TIT2", "TPE1", etc.)
    unsigned int size;        // Frame size 
    unsigned short flags;     // Frame flags
} ID3v2Frame;

//MP3 TAG STRUCT (For viewing all fields)
typedef struct
{
    char title[128];
    char artist[128];
    char album[128];
    char year[8];
    char genre[64];
    char comment[256];
} MP3Tag;

//FUNCTION DECLARATIONS 
void mp3_view(const char *filename);
int mp3_edit(char *tag_option, char *new_value, char *filename);
void print_help(void);
unsigned int decode_size(unsigned char size[4]);

#endif
