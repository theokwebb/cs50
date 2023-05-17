#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for improper usage
    if (argc != 2)
    {
        printf("Improper usage. Try ./recover [filename]\n");
        return 1;
    }

    // Open file
    FILE *filename = fopen(argv[1], "r");
    if (filename == NULL)
    {
        printf("File not found.\n");
        return 2;
    }

    // Store JPEG data
    BYTE buffer[512];

    // JPEG's found
    int found = 0;

    // Initialize file ptr
    FILE *img = NULL;

    // Create a new block of memory to store the new JPEG file name
    char *new_file = malloc(sizeof(char) * 8);
    if (new_file == NULL)
    {
        free(new_file);
        return 3;
    }

    while (fread(buffer, 512, 1, filename) == 1)
    {
        // Check if file matches JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found++;

            // If first JPEG
            if (found == 1)
            {
                // Copy new file name into block of memory
                sprintf(new_file, "%03i.jpg", 0);
                // Open the new JPEG file to write to
                img = fopen(new_file, "w");
                // Write data to the new JPEG file
                fwrite(buffer, 512, 1, img);
            }

            // If already found a JPEG
            else
            {
                // Close previous JPEG file in order to open up a new JPEG file to write to
                fclose(img);
                sprintf(new_file, "%03i.jpg", found - 1);
                img = fopen(new_file, "w");
                fwrite(buffer, 512, 1, img);
            }
        }

        // If not new JPEG, continue writing to existing JPEG
        else
        {
            if (found >= 1)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    free(new_file);
    fclose(img);
    fclose(filename);
}
