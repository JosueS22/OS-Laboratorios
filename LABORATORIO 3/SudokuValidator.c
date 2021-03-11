#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h>

#define ROW 9
#define COLUMN 9

char board[ROW][COLUMN];
int valid_columns, valid_rows;

int checkRows() {
    omp_set_nested(1);

    int grid[9];
    int valid = 0;
    
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int i = 0; i < ROW; i++) {
        char valid_nums[] = "123456789";
        char *s;
        
        for (s = &valid_nums[0]; *s != '\0'; s++) {
            int found = 0;
            int j = 0;
            while (found == 0 && j < COLUMN) {
                if (board[i][j] == *s) {
                    found = 1;
                }
                j++;
            }
            if (found == 0) {
                valid = -1;
            }
        }
    }
    return valid;
}

int checkRows_args(char temp[ROW][COLUMN]) {
    omp_set_nested(1);

    int grid[9];
    int valid = 0;
    #pragma omp parallel for private(grid) schedule(dynamic)

    for (int i = 0; i < ROW; i++) {
        char valid_nums[] = "123456789";
        char *s;
        
        for (s = &valid_nums[0]; *s != '\0'; s++) {
            int found = 0;
            int j = 0;
            while (found == 0 && j < COLUMN) {
                if (temp[i][j] == *s) {
                    found = 1;
                }
                j++;
            }
            if (found == 0) {
                valid = -1;
            }
        }
    }
    return valid;
}

int checkColumns() {
    omp_set_nested(1);

    int grid[9];
    int valid = 0;
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int i = 0; i < COLUMN; i++) {
        char valid_nums[] = "123456789";
        char *s;
        for (s = &valid_nums[0]; *s != '\0'; s++) {
            int found = 0;
            int j = 0;
            while (found == 0 && j < ROW) {
                if (board[j][i] == *s) {
                    found = 1;
                }
                j++;
            }
            if (found == 0) {
                valid = -1;
            }
        }
    }
    return valid;
}

int verify_sub_matrix() {
    omp_set_nested(1);

    char temp_board[ROW][COLUMN];
    int row = 0, column = 0;

    int grid[9];
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int x = 0; x < 3; x++) {
        #pragma omp parallel for schedule(dynamic)
        for (int y = 0; y < 3; y++) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < 3; i++) {
                #pragma omp parallel for schedule(dynamic)
                for (int j = 0; j < 3; j++) {
                    temp_board[row][column] = board[i + (x * 3)][j + (y * 3)];
                    column++;
                }
            }
            column = 0;
            row++;
        }
    }
    return checkRows_args(temp_board);
}

void *complete_column_verification() {
    printf("Thread id verificacion de columnas: %ld\n", syscall(SYS_gettid));
    valid_columns = checkColumns();
    pthread_exit(0);
}

void *complete_row_verification() {
    printf("Thread id verificacion de filas: %ld\n", syscall(SYS_gettid));
    valid_rows = checkRows();
    pthread_exit(0);
}

void map_board_from_file(int fd) {
    omp_set_nested(1);

    struct stat stat_s;
    int status = fstat(fd, &stat_s);
    int size = stat_s.st_size;
    char *ptr = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    int position = 0;
    int grid[9];
    #pragma omp parallel for private(grid) schedule(dynamic)
    for (int i = 0; i < ROW; i++) {
        #pragma omp parallel for schedule(dynamic)
        for (int j = 0; j < COLUMN; j++) {
            board[i][j] = ptr[position];
            position++;
        }
    }
    munmap(ptr,size);
    close(fd);
}

int main(int argc, char *argv[]) {
    omp_set_num_threads(1);

    int input;
    if ((input = open(argv[1], O_RDONLY))) {
        map_board_from_file(input);
        pid_t parent_pid = getpid();

        if (fork() == 0) {
            char p_pid[6];
            sprintf(p_pid, "%d", (int)parent_pid);
            execlp("ps", "ps", "-p", p_pid, "-lLf", NULL);
        } else {
            pthread_t col_verification;
            
            printf("Thread en ejecucion: %ld\n", syscall(SYS_gettid));
            wait(NULL);
            printf("El proceso hijo 1 termino\n");

            pthread_t row_verification;
            
            if (valid_rows == 0 && valid_columns == 0) {
                printf("LA SOLUCION DEL SUDOKU ES VALIDA\n");
            } else {
                printf("LA SOLUCION DEL SUDOKU NO ES VALIDA\n");
            }
        }

        int f2 = fork();
        if (f2 == 0) {
            char p_pid[6];
            sprintf(p_pid, "%d", (int)parent_pid);
            execlp("ps", "ps", "-p", p_pid, "-lLf", NULL);
        } else {
            wait(NULL);
            printf("El proceso hijo 2 termino\n");
            return 0;
        }
    }
}
