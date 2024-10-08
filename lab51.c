#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char frame[50][50], str[50][50];
    char flag[10];
    strcpy(flag, "01111110");

    char esc[10];
    strcpy(esc, "11110000");
    int i, j, k = 0, n;

    strcpy(frame[k++], flag);

    printf("Enter length of String : \n");
    scanf("%d",&n);

    getchar();

    printf("Enter the strings:\n");
    for (i=0;i<n;i++)
    {
        fgets(str[i], 50, stdin);
        str[i][strcspn(str[i], "\n")] = 0;
    }
    for (i=0;i<n;i++)
    {
        if (strcmp(str[i], flag) != 0 && strcmp(str[i], esc) != 0)
        {
            strcpy(frame[k++], str[i]);
        }
        else
        {
            strcpy(frame[k++], esc);
            strcpy(frame[k++], str[i]);
        }
    }

    strcpy(frame[k++], flag);

    printf("\nStuffed Frame:\n");
    for (i=0;i<k;i++)
    {
        printf("%s ", frame[i]);
    }

    printf("\nUnstuffed Frame:\n");

    int destuffedCount = 0;
    for (i=1;i<k-1;i++)
    {
        if (strcmp(frame[i], esc)==0 && strcmp(frame[i+1], esc)==0)
        {
            i++;
        }
        else
        {
            strcpy(str[destuffedCount++], frame[i]);
        }
    }
    for (i=0;i<destuffedCount;i++)
    {
        printf("%s",str[i]);
    }

    return 0;
}
