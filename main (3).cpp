#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
    const string filename = "test.bin"; // имя файла
    const long long filesize = 2LL * 1024 * 1024 * 1024; // размер файла в байтах

    // генерация случайных чисел и запись в файл
    ofstream out(filename, ios::out | ios::binary);
    srand(static_cast<unsigned int>(time(nullptr)));
    for (long long i = 0; i < filesize / sizeof(int); i++) {
        int random_num = rand();
        out.write(reinterpret_cast<char*>(&random_num), sizeof(int));
    }
    out.close();

    // чтение и сортировка содержимого файла
    ifstream in(filename, ios::in | ios::binary);
    const int buffer_size = 1024 * 1024; // размер буфера для считывания
    int* buffer = new int[buffer_size / sizeof(int)];
    long long read_bytes = 0; // количество уже считанных байт из файла
    while (read_bytes < filesize) {
        // чтение из файла в буфер
        long long bytes_left = filesize - read_bytes;
        int count = min(static_cast<long long>(buffer_size), bytes_left) / sizeof(int);
        in.read(reinterpret_cast<char*>(buffer), count * sizeof(int));

        // сортировка буфера
        sort(buffer, buffer + count);

        // запись буфера в выходной файл
        ofstream out("sorted.bin", ios::app | ios::binary);
        out.write(reinterpret_cast<char*>(buffer), count * sizeof(int));
        out.close();

        // обновление счетчика считанных байт
        read_bytes += count * sizeof(int);
    }
    in.close();

    // освобождение выделенной памяти
    delete[] buffer;

    return 0;
}