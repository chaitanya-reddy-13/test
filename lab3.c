#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[100];
    printf("Enter data : ");
    scanf("%s", input);

    int inputLength = strlen(input);
    int maxDataSize = inputLength + inputLength / 5 + 12;
    char *data = (char *)malloc(maxDataSize * sizeof(char));

    int j = 0, count = 0;

    data[j++] = '0';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '0';

    for (int i = 0; i < inputLength; i++) {
        if (count == 5) {
            data[j++] = '0';
            count = 0;
        }
        data[j++] = input[i];
        if (input[i] == '1') {
            count++;
        } else {
            count = 0;
        }
    }
    if (count == 5) {
        data[j++] = '0';
    }
    data[j++] = '0';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '1';
    data[j++] = '0';
    data[j] = '\0';
    printf("Stuffed data: %s\n", data);
    int dataLength = strlen(data);
    char *res = (char *)malloc((inputLength) * sizeof(char));
    int k = 0, j1 = 8, c = 0;
    while (k<inputLength) {
        if (c == 5) {
            j1++;
            c = 0;
            continue;
        }
        res[k++] = data[j1];
        if (data[j1] == '1') {
            c++;
        } else {
            c = 0;
        }
        j1++;
    }

    res[k] = '\0';
    printf("Original data: %s\n", res);

    free(data);
    free(res);
    return 0;
}
