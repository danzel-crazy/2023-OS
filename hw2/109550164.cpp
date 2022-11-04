# include <iostream>
# include <thread>
# include <unistd.h>

using namespace std;

# define MAX 500
# define MAX_THREAD 4

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

long long sum[MAX_THREAD];
long long mul[MAX_THREAD];

void Addition(int start, int len, int place){
    // Addition -> matC
    for (int i = start; i < (start+len); i++) {
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
            sum[place] += matC[i][j];
        }   
    }
}
void Multiplication(int start, int len, int place){
    // Multiplication -> matD
    for (int i = start; i < start+len; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
            mul[place] += matD[i][j];
        }
    }
}

void* check(void *arg){
    int place =  *(int *)arg;
    int len = MAX/MAX_THREAD;
    sum[place] = 0;
    mul[place] = 0;
    Addition(place*len, len, place);
    Multiplication(place*len, len, place);
    pthread_exit(NULL);
}

int main()
{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    pthread_t threads[MAX_THREAD];
    int arg[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++) {
        arg[i] = i;
        pthread_create(&threads[i], NULL, check, &arg[i]);
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }
    // Addition();
    // Multiplication();
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX_THREAD; i++) {
        sum_C += sum[i];
    }
    cout << sum_C << "\n";

    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX_THREAD; i++) {
            sum_D += mul[i];
    }
    cout << sum_D << "\n";

    return 0;
}