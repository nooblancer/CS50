#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Correct Usage: ./reverse <input_file> <output_file>\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Error: Could not open file.\n");
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, in);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        printf("Error: Input is invalid .wav file.\n");
        return 3;
    }

    // Open output file for writing
    // TODO #5
    FILE *out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Error: Could not create reversed file.\n");
        return 4;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, out);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[size];

    fseek(in, 0, SEEK_END);
    int as = ftell(in) - sizeof(WAVHEADER);
    int bs = as / size;

    for (int i = bs - 1; i >= 0; i--)
    {
        fseek(in, sizeof(WAVHEADER) + i * size, SEEK_SET);
        fread(buffer, size, 1, in);
        fwrite(buffer, size, 1, out);
    }
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE format[] = {'W', 'A', 'V', 'E'};

    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != format[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * (header.bitsPerSample / 8));
}