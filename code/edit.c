#include "header.h"

unsigned int decode_size(unsigned char size[4])
{
    return ((size[0] & 0x7F) << 21) |
           ((size[1] & 0x7F) << 14) |
           ((size[2] & 0x7F) << 7)  |
           (size[3] & 0x7F);
}

int mp3_edit(char *tag_option, char *new_value, char *filename)
{
    FILE *fp = fopen(filename, "r+b");
    if (!fp)
    {
        printf("Error: Cannot open file %s\n", filename);
        return FAILURE;
    }

    ID3v2Header header;
    fread(&header, sizeof(header), 1, fp);

    if (strncmp(header.id, "ID3", 3) != 0)
    {
        printf("Error: Not a valid ID3v2 file.\n");
        fclose(fp);
        return FAILURE;
    }

    unsigned int tag_size = decode_size(header.size);
    unsigned int tag_end = tag_size + 10;

    char frame_id[5];
    char label[20];

    printf("------------------------------------------------------------\n");
    printf("--------------------Select Edit option--------------------\n");
    printf("------------------------------------------------------------\n");

    if (strcmp(tag_option, "-t") == 0)
    {
        strcpy(frame_id, "TIT2");
        strcpy(label, "Title");
    }
    else if (strcmp(tag_option, "-a") == 0)
    {
        strcpy(frame_id, "TPE1");
        strcpy(label, "Artist");
    }
    else if (strcmp(tag_option, "-A") == 0)
    {
        strcpy(frame_id, "TALB");
        strcpy(label, "Album");
    }
    else if (strcmp(tag_option, "-y") == 0)
    {
        strcpy(frame_id, "TYER");
        strcpy(label, "Year");
    }
    else if (strcmp(tag_option, "-g") == 0)
    {
        strcpy(frame_id, "TCON");
        strcpy(label, "Genre");
    }
    else if (strcmp(tag_option, "-c") == 0)
    {
        strcpy(frame_id, "COMM");
        strcpy(label, "Comment");
    }
    else
    {
        printf("Invalid option! Use -t, -a, -A, -y, -g, -c\n");
        fclose(fp);
        return FAILURE;
    }

    // Move to start of frames
    fseek(fp, 10, SEEK_SET);

    unsigned char buffer[10];
    while (ftell(fp) < tag_end)
    {
        if (fread(buffer, 1, 10, fp) != 10)
            break;

        // Empty frame area
        if (buffer[0] == 0)
            break;

        char current_id[5];
        memcpy(current_id, buffer, 4);
        current_id[4] = '\0';

        // Decode frame size
        unsigned int size = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];

        if (strncmp(current_id, frame_id, 4) == 0)
        {
            printf("--------------------Select %s change option--------------------\n", label);
            printf("        %s : %s\n", label, new_value);

            // Move to frame content (after header)
            fseek(fp, 1, SEEK_CUR); // skip text encoding byte

            // Clear the existing text area before writing new data
            long clear_pos = ftell(fp);
            for (unsigned int i = 0; i < size - 1; i++)
                fputc('\0', fp);

            // Move back and write the new tag text
            fseek(fp, clear_pos, SEEK_SET);
            fwrite(new_value, strlen(new_value), 1, fp);

            printf("--------------------%s changed successfully--------------------\n", label);
            fclose(fp);
            return SUCCESS;
        }

        // Skip frame data and move to next frame
        fseek(fp, size, SEEK_CUR);
    }

    // If loop ends without finding frame
    printf("Frame not found!\n");
    fclose(fp);
    return FAILURE;
}
