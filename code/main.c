/*
Name: Muhammed Mishab
Date: 29 - 10 - 2025
Description: Mp3 Tag Editor and Viewer in C
*/

#include "header.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("INVALID ARGUMENTS.\nUSAGE:\n");
        printf("To view tags: ./a.out -v <mp3filename>\n");
        printf("To edit tag:  ./a.out -e <tag-option> <new_value> <mp3filename>\n");
        return FAILURE;
    }

    // Help option
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    {
        print_help();
        return SUCCESS;
    }

    // View option
    else if (strcmp(argv[1], "-v") == 0)
    {
        if (argc != 3)
        {
            printf("USAGE:\n./a.out -v <filename>\n");
            return FAILURE;
        }
        mp3_view(argv[2]);
        return SUCCESS;
    }

    // Edit option
    else if (strcmp(argv[1], "-e") == 0)
    {
        if (argc != 5)
        {
            printf("USAGE:\n./a.out -e <tag-option> <new_value> <file-name>\n");
            return FAILURE;
        }
        return mp3_edit(argv[2], argv[3], argv[4]); 
    }

    // Invalid option
    else
    {
        printf("Invalid Option: %s\n", argv[1]);
        print_help();
        return FAILURE;
    }
}

// Displays help information
void print_help(void)
{
    printf("\nUsage:\n");
    printf("  ./a.out -v <filename>                     -> View all MP3 tags\n");
    printf("  ./a.out -e <tag-option> <new_value> <file> -> Edit a tag in MP3 file\n");
    printf("\nTag Options:\n");
    printf("  -t  -> Modify Title tag\n");
    printf("  -T  -> Modify Track tag\n");
    printf("  -a  -> Modify Artist tag\n");
    printf("  -A  -> Modify Album tag\n");
    printf("  -y  -> Modify Year tag\n");
    printf("  -c  -> Modify Comment tag\n");
    printf("  -g  -> Modify Genre tag\n");
    printf("  -h  -> Show help information\n");
    printf("\nExamples:\n");
    printf("  ./a.out -v sample.mp3\n");
    printf("  ./a.out -e -A \"New Album\" sample.mp3\n\n");
}
