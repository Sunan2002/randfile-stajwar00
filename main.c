#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

int random_gen(){
    int fd = open("/dev/random", O_RDONLY);
    int num[1];
    int gen = read(fd, num, sizeof(int));
    return num[0];
    close(fd);
}

int main(){
    
    //Create array of random values
    int arr[10];
    for(int i = 0; i < 10; i++){
        arr[i] = random_gen();
    }
    printf("\nPrinting Original Array:/n [");
    for(int i = 0; i < 10; i++){
        printf("%d,",arr[i]);
    }
    
    //Writing array to the file
    printf("\n\nWriting Array to the File\n ==========================\n");
    int wr = open ("numbers.txt", O_RDWR | O_CREAT, 0644);
    if (wr == -1) printf("Error #%d, %s", errno, strerror(errno));
    write(wr, arr, 10 * sizeof(int));
    close(wr);
    
    //Reading file into a different array
    printf("\nReading File into another Array\n ==========================\n");
    int brr[10];
    int rd = open ("numbers.txt", O_RDONLY);
    if (rd == -1) printf("Error #%d, %s", errno, strerror(errno));
    read (rd, brr, 10 * sizeof(int));
    close(rd);
    printf("\nPrinting new array:\n [");
    for(int i = 0; i < 10; i++){
        printf("%d,", brr[i]);
    }
    
    //Array Check
    printf("\n\nVerify the Arrays Match\n =============================\n");
    for(int i = 0; i < 10; i++){
        if (arr[i] != brr[i]){
            printf("The two arrays are different at index %d\n", i);
        }
        else{
            printf("The two arrays are the same at index %d\n", i);
        }
    }
    
}
