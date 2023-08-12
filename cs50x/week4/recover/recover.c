#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // checking filename is provided
    if (argc != 2)
    {
        printf("Correct Usage: ./recover <filename>\n");
        return 1;
    }

    // opening card.raw
    FILE *f = fopen(argv[1], "r");
    // checking if file is open
    if (f == NULL)
    {
        printf("Error: Can't open %s\n", argv[1]);
        return 2;
    }

    // reading and storing file into buffer
    BYTE buffer[512];
    char filename[8];
    FILE *img = NULL;
    int counter = 0;

    while (fread(&buffer, sizeof(BYTE), 512, f) == 512)
    {
        // checking for header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if not first, close previous
            if (!(counter == 0))
            {
                fclose(img);
            }

            // make new file 00x.jpg
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }
        // writing data of images (JPEGs) in img
        if (!(counter == 0))
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(f);
    fclose(img);
    return 0;
}