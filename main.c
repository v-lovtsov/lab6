#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "utils.h"

int main()
{
    char *inputn = generateString(100);
    char *input_tree = generateString(2000000);

    // Чтение первой строки
    fgets(inputn, sizeof(inputn), stdin);
    rmnline(inputn);
    if (inputn == NULL || strlen(inputn) == 0)
    {
        printf("Empty input\n");
        return 0;
    }

    int N = atoi(inputn);
    if (N < 0 || N > 2000000)
    {
        printf("Bad input\n");
        return 0;
    }

    // Чтение второй строки
    if (fgets(input_tree, sizeof(input_tree), stdin) == NULL)
    {
        printf("Bad input\n");
        return 0;
    }

    char *token = strtok(input_tree, " ");
    int count = 0;
    int *numbers = (int *)malloc(N * sizeof(int));

    while (token != NULL && count < N)
    {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    if (count != N)
    {
        printf("Bad input\n");
        free(numbers);
        return 0;
    }

    NODE *root = NULL;
    char *rotation_types[100];
    int rotation_count = 0;

    for (int i = 0; i < N; i++)
        root = insert(root, numbers[i], NULL, rotation_types, &rotation_count);

    // Вывод результатов
    if (N < 100)
        for (int i = 0; i < rotation_count; i++)
            printf("%s ", rotation_types[i]);

    printf("%d\n", getHeight(root));

    // Освобождение памяти
    free(numbers);
    freeTree(root);

    return 0;
}
