#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>
#include <chrono>
#include "complex.hpp"

std::vector<std::vector<complex_double>> matrix1, matrix2, result;

void* multiply(void *arg) {
    int i = *((int*)arg);
    int j = *((int*)arg + 1);
    int step = *((int*)arg + 2);

    for (int k = 0; k < step; ++k) {
        result[i][j] = 0;
        for (int x = 0; x < matrix1[0].size(); ++x) {
            result[i][j] += matrix1[i][x] * matrix2[x][j];
        }
        i = (i * matrix1.size() + j + 1) / matrix1.size();
        j = (j + 1) % matrix1.size();
    }
                     
    return nullptr;
}

int main(int argc, char **argv) {
    int number_of_threads = atoi(argv[1]);
    if (number_of_threads <= 0) {
        std::cerr << "Заданное число потоков не может быть использовано." << std::endl;
        return -1;
    }

    int n1, m1, n2, m2;
    std::cout<<"Введите размер первой матрицы\n";
    std::cin >> n1 >> m1;
    std::cout<<"Введите первую матрицу\n";
    matrix1.resize(n1, std::vector<complex_double>(m1));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            std::cin >> matrix1[i][j];
        }
    }
    std::cout<<"Введите размер второй матрицы\n";
    std::cin >> n2 >> m2;
    std::cout<<"Введите вторую матрицу\n";
    matrix2.resize(n2, std::vector<complex_double>(m2));
    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < m2; ++j) {
            std::cin >> matrix2[i][j];
        }
    }
    
    if (m1 != n2) {
        std::cerr << "Неверные размеры матриц: невозможно перемножить\n";
        return -1;
    }

    result.resize(n1, std::vector<complex_double>(m2, complex_double()));
    number_of_threads = std::min(number_of_threads, n1 * m2);
    std::vector<pthread_t> threads(number_of_threads);
    std::vector<int[3]> args(number_of_threads);
    int nm = n1 * m2;
    int position = 0;

    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    for (int _ = 0; _ < threads.size(); ++_) {
        int step = nm / number_of_threads--;
        nm -= step;
        int i = position / m2;
        int j = position % m2;

        args[_][0] = i; args[_][1] = j; args[_][2] = step;

        pthread_create(&threads[_], NULL, multiply, args[_]);
        position += step;
    }

    nm = n1 * m2, number_of_threads = threads.size();
    position = 0;
    for (int _ = 0; _ < threads.size(); ++_) {
        pthread_join(threads[_], nullptr);
    }

    
    std::cout << '\n';
    std::cout<<"Результат:\n";
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << "Время работы программы: " << duration.count() << " микросекунд. " << "\n";
}
