#ifndef utils_h
#define utils_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define uint unsigned int

// Generate and fill empty new string
char *generateString(uint size)
{
    char *str = (char *)malloc(size * sizeof(char));
    for (uint i = 0; i < size; i++)
        str[i] = '\0';

    return str;
}

// Get equal digit from char symbol
uint numfrmch(char num)
{
    if ((uint)num <= (uint)'9')
        return (uint)num - '0';

    if ((uint)num <= (uint)'Z')
        return (uint)num - 'A' + 10;

    if ((uint)num <= (uint)'z')
        return (uint)num - 'a' + 10;

    return 0;
}

// Get equal digit array from string
uint *intArrFromStr(char *P)
{
    uint size = strlen(P);
    uint *arr = (uint *)malloc(size * sizeof(uint));

    for (uint i = 0; i < size; i++)
        arr[i] = numfrmch(P[i]);

    return arr;
}

// Swap two elements from array
void swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

// Bubble sort
void sort(int *P, int start, int end)
{
    for (int i = start; i < end; i++)
        for (int j = i + 1; j < end; j++)
            if (P[j] < P[i])
                swap(&P[i], &P[j]);
}

// Print array of integer nums
void printArray(uint *P, uint size)
{
    for (uint i = 0; i < size; i++)
        printf("%u ", P[i]);

    printf("\n");
}

// Create new array and copy to it other
uint *copyArray(uint *arr, uint size)
{
    uint *new_arr = (uint *)malloc(size * sizeof(uint));

    for (uint i = 0; i < size; i++)
        new_arr[i] = arr[i];

    return new_arr;
}

void rmnline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void clearConsole()
{
    for (int i = 0; i < 64; i++)
        printf("\n");
}

void modify_line(const char *filename, int line_num, const char *new_content, int size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        fclose(file);
        return;
    }

    char *buffer = generateString(size);
    int current_line = 1;

    while (fgets(buffer, size, file))
    {
        if (current_line == line_num)
            fprintf(temp, "%s\n", new_content);
        else
            fputs(buffer, temp);
        current_line++;
    }

    fclose(file);
    fclose(temp);

    // Заменяем оригинальный файл временным
    remove(filename);
    rename("temp.txt", filename);
    free(buffer);
}

int getMax(int a, int b)
{
    return (a > b) ? a : b;
}

#endif