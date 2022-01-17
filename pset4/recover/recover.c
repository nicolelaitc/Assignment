#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <cs50.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //take the command-line argument
    FILE *file = fopen(argv[1], "r"); //open the card

    if (argc != 2)
    {
        printf("You should only open a file.\n");
        return 1;
    }

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[512];
    int i = 0;
    char filename[] = "xxx.jpg";

    FILE *img = fopen(filename, "w");

    //repeat searching until the end of the card
    while (fread(&buffer, sizeof(BYTE), 512, file)) //Read 512 bytes into a buffer
    {
        //Open a file called ###.JPEG

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)//If start of new JPEG (by looking at the header)
        {
            fclose(img); //Close the file I was writing

            sprintf(filename, "%03i.jpg", i);
            printf("%s\n", filename);

            i++;

            img = fopen(filename, "w"); //Open the new
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }

        else //Else
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }

    }
    fclose(file);   //Close any remaining files

}
