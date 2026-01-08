#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("How to use: ./exe_comparer <program name>\nThis program compares <program name> instances in my_results & og_program");
        return 1;
    }
    printf("Program name: %s\n", argv[1]);
    char flink1[30] = "./my_results/";
    char flink2[30] = "./og_programs/";
    strcat(flink1, argv[1]);
    strcat(flink2, argv[1]);
    printf("%s\n%s\n", flink1, flink2);
    FILE *file1 = fopen(flink1, "rb");
    if (file1 == NULL) {
        printf("Error opening file 1\n");
        return 1;
    }

    FILE *file2 = fopen(flink2, "rb");
    if (file2 == NULL) {
        printf("Error opening file 2\n");
        fclose(file1);
        return 1;
    }
 
    int byte_count = 0;
    while (!feof(file2) && !feof(file1)) {
        unsigned char byte1 = fgetc(file1);
        unsigned char byte2 = fgetc(file2);
        byte_count++;
 
        if (byte1 != byte2) {
            printf("Files differ. Bytes compared: %d\n", byte_count);
            fclose(file1);
            fclose(file2);
            return 1;
        }
    }
 
    printf("Files are identical with %d bytes compared\n", byte_count);
    fclose(file1);
    fclose(file2);
    return 0;
}