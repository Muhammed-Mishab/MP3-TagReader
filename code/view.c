#include "header.h"

void mp3_view(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror("Error opening file");
        return;
    }

    unsigned char header[10];
    fread(header, 1, 10, fp);

    if (strncmp((char *)header, "ID3", 3) != 0)
    {
        printf("No ID3v2 tag found in %s\n", filename);
        fclose(fp);
        return;
    }

    unsigned int tag_size = ((header[6] & 0x7F) << 21) |
                            ((header[7] & 0x7F) << 14) |
                            ((header[8] & 0x7F) << 7) |
                            (header[9] & 0x7F);

    printf("\n-------------- ID3v2 TAG INFO ------------------\n");

    while (1)
    {
        unsigned char frame_header[10];
        if (fread(frame_header, 1, 10, fp) < 10)
            break;

        if (frame_header[0] == 0)
            break;

        char frame_id[5] = {0};
        strncpy(frame_id, (char *)frame_header, 4);

        unsigned int frame_size = (frame_header[4] << 24) |
                                  (frame_header[5] << 16) |
                                  (frame_header[6] << 8) |
                                  (frame_header[7]);

        if (frame_size == 0)
            break;

        char *data = malloc(frame_size + 1);
        fread(data, 1, frame_size, fp);
        data[frame_size] = '\0';

        char *text = data + 1; // skip encoding byte

        if (strcmp(frame_id, "TIT2") == 0)
            printf("Title  : %s\n", text);
        else if (strcmp(frame_id, "TPE1") == 0)
            printf("Artist : %s\n", text);
        else if (strcmp(frame_id, "TALB") == 0)
            printf("Album  : %s\n", text);
        else if (strcmp(frame_id, "TYER") == 0)
            printf("Year   : %s\n", text);
        else if (strcmp(frame_id, "TCON") == 0)
            printf("Genre  : %s\n", text);
        else if (strcmp(frame_id, "COMM") == 0)
            printf("Comment: %s\n", text);

        free(data);
    }

    printf("---------------------------------------------------\n");
    fclose(fp);
}
