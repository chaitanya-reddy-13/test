#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char divisor[100];
    char data[100];
    char quotient[100];
    char remainder[100];
    int curr = 0;

    printf("Enter divisor\n");
    scanf("%s", divisor);
    printf("Enter data\n");
    scanf("%s", data);
    char data1[200];  // Buffer to store original data + remainder
    strcpy(data1, data);
    int data_len = strlen(data);
    int divisor_len = strlen(divisor);

    // Append (divisor_len - 1) zeros to the original data
    for (int i = 0; i < divisor_len - 1; i++) {
        data[data_len + i] = '0';
    }
    data[data_len + divisor_len - 1] = '\0';  // Null-terminate the modified data

    // Perform division on the data to find the remainder
    while (strlen(data) >= divisor_len) {
        char temp[100];
        int k = 0;

        if (data[0] == '1') {  // If the leading bit is 1, perform XOR
            quotient[curr] = '1';
            curr++;

            for (int i = 0; i < divisor_len; i++) {
                int a = divisor[i] - '0';
                int b = data[i] - '0';
                temp[i] = (a ^ b) + '0';  // XOR operation
                k++;
            }
        } else {  // If the leading bit is 0, shift the data without XOR
            quotient[curr] = '0';
            curr++;
            for (int i = 0; i < divisor_len; i++) {
                temp[i] = data[i];
                k++;
            }
        }

        // Copy the remaining part of the data
        for (int i = divisor_len; i < strlen(data); i++) {
            temp[k++] = data[i];
        }
        temp[k] = '\0';  // Null-terminate the temp string

        // Remove leading zeroes from temp
        int zero_count = 0;
        while (temp[zero_count] == '0' && zero_count < strlen(temp)) {
            zero_count++;
        }
        strcpy(data, temp + zero_count);  // Update data with the shifted value
    }

    // The remaining data now contains the remainder, we need to add this to the original data
    strcpy(remainder, data);  // Save the remainder
    printf("Remainder: %s\n", remainder); // Debug print

    // Combine original data with the remainder to form coded data
    for (int i = 0; i < strlen(remainder); i++) {
        data1[data_len + i] = remainder[i];
    }
    data1[data_len + strlen(remainder)] = '\0';  // Null-terminate the coded data

    printf("Coded data is \n%s\n", data1);

    // Receiver side check
    char data2[200];  // Buffer to store received data
    printf("Enter receiver data\n");
    scanf("%s", data2);
    strcpy(data, data2);  // Initialize data with the received data
    curr = 0;  // Reset current index of the quotient

    // Perform division on received data
    while (strlen(data) >= divisor_len) {
        char temp[100];
        int k = 0;

        if (data[0] == '1') {  // If the leading bit is 1, perform XOR
            quotient[curr] = '1';
            curr++;

            for (int i = 0; i < divisor_len; i++) {
                int a = divisor[i] - '0';
                int b = data[i] - '0';
                temp[i] = (a ^ b) + '0';  // XOR operation
                k++;
            }
        } else {  // If the leading bit is 0, shift the data without XOR
            quotient[curr] = '0';
            curr++;
            for (int i = 0; i < divisor_len; i++) {
                temp[i] = data[i];
                k++;
            }
        }

        // Copy the remaining part of the data
        for (int i = divisor_len; i < strlen(data); i++) {
            temp[k++] = data[i];
        }
        temp[k] = '\0';  // Null-terminate the temp string

        // Remove leading zeroes from temp
        int zero_count = 0;
        while (temp[zero_count] == '0' && zero_count < strlen(temp)) {
            zero_count++;
        }
        strcpy(data, temp + zero_count);  // Update data with the shifted value
    }

    // Check if the remainder is zero
    int i = 0;
    int m = 0;
    data_len = strlen(data);  // Update data_len for the new length of data

    while (i < data_len) {
        if (data[i] == '1') {  // If there's a '1' in remainder, data is corrupted
            m = 1;
            break;
        }
        i++;
    }

    if (m == 1) {
        printf("Data is corrupted\n");
    } else {
        printf("\nSender code and receiver code are same\n");
    }

    return 0;  // Add return statement for main function
}
