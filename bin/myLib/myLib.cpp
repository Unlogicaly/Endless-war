//
// Created by tarog on 08.11.2019.
//

#include <cstdarg>
#include "myLib.h"

using std::vector;
using std::string;

vector<string> &Func::split(const string &s, char c) {
    auto result = new vector<string>{s};

    if (!s.length()) return *result;

    int prev = -1;

    for (auto i = 0; i < s.length(); ++i) {
        if (s[i] == c) {
            result->back() = string(s.begin() + prev + 1, s.end() - (s.length() - i));
            result->emplace_back("");

            prev = i;

            continue;
        }
    }
    result->back() = string(s.begin() + prev + 1, s.end());

    return *result;
}

double Func::d_mean(int count, ...) {
    va_list args;
    va_start(args, count);

    double sum = 0;
    for (auto i = 0; i < count; ++i) {
        sum += va_arg(args, double);
    }
    va_end(args);
    return sum / count;
}

double Func::i_mean(int count, ...) {
    va_list args;
    va_start(args, count);

    double sum = 0;
    for (auto i = 0; i < count; ++i) {
        sum += (va_arg(args, int));
    }
    va_end(args);
    return sum / count;
}

double Func::d_max(int count, ...) {
    va_list args;
    va_start(args, count);

    double m = va_arg(args, double);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::max(m, va_arg(args, double));
    }
    va_end(args);
    return m;
}

int Func::i_max(int count, ...) {
    va_list args;
    va_start(args, count);

    int m = va_arg(args, int);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::max(m, va_arg(args, int));
    }
    va_end(args);
    return m;
}

char Func::c_max(int count, ...) {
    va_list args;
    va_start(args, count);

    int m = va_arg(args, int);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::max(m, va_arg(args, int));
    }
    va_end(args);
    return static_cast<char>(m);
}

std::string Func::s_max(int count, ...) {
    va_list args;
    va_start(args, count);

    std::string m = std::string(va_arg(args, char*));
    for (auto i = 0; i < count - 1; ++i) {
        m = std::max(m, std::string(va_arg(args, char*)));
    }
    va_end(args);
    return m;
}

double Func::d_min(int count, ...) {
    va_list args;
    va_start(args, count);

    double m = va_arg(args, double);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::min(m, va_arg(args, double));
    }
    va_end(args);
    return m;
}

int Func::i_min(int count, ...) {
    va_list args;
    va_start(args, count);

    int m = va_arg(args, int);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::min(m, va_arg(args, int));
    }
    va_end(args);
    return m;
}

char Func::c_min(int count, ...) {
    va_list args;
    va_start(args, count);

    int m = va_arg(args, int);
    for (auto i = 0; i < count - 1; ++i) {
        m = std::min(m, va_arg(args, int));
    }
    va_end(args);
    return static_cast<char>(m);
}

std::string Func::s_min(int count, ...) {
    va_list args;
    va_start(args, count);

    std::string m = std::string(va_arg(args, char*));
    for (auto i = 0; i < count - 1; ++i) {
        m = std::min(m, std::string(va_arg(args, char*)));
    }
    va_end(args);
    return m;
}

unsigned long long int Func::fact(unsigned long long n) {

    if (n == 0 || n == 1) return 1;

    unsigned long long result = 1;

    while (n) {
        result *= n--;
    }

    return result;
}

bool next_set(vector<char> &a, unsigned long long int n, unsigned long long int m) {

    unsigned long long j;

    do {
        j = n - 2;

        while (j != -1 && a[j] >= a[j + 1]) j--;
        if (j == -1) return false;

        auto k = n - 1;

        while (a[j] >= a[k]) k--;
        Func::swap(a, j, k);

        auto l = j + 1, r = n - 1;

        while (l < r) Func::swap(a, l++, r--);

    } while (j > m - 1);

    return true;
}

vector<vector<char>> Func::permutations(const vector<char> &source, unsigned long long n, unsigned long long m) {

    vector<vector<char>> result(Func::fact(n) / Func::fact(n - m));
    vector<char> a;

    a.reserve(source.size());

    for (auto i: source) a.push_back(i);

    int i = 1;

    for (auto j = 0; j < m; ++j) result[0].push_back(a[j]);

    while (next_set(a, n, m)) {

        for (auto j = 0; j < m; ++j) result[i].push_back(a[j]);
        i++;
    }

    return result;
}

double Func::round(double num, int precision) {
    return std::round(pow(10, precision) * num) / pow(10, precision);
}

int Func::randint(int start, int end) {

    std::default_random_engine dev(
            static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::uniform_int_distribution<int> dist(start, end);

    return dist(dev);
}

std::vector<int> Func::randint(int start, int end, unsigned long long int size) {
    std::default_random_engine dev(
            static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::uniform_int_distribution<int> dist(start, end);

    auto res = Func::matrix_1d(size, 0);

    for (auto i = 0; i < size; ++i)
        res[i] = dist(dev);

    return res;
}

double Func::rand() {
    std::default_random_engine dev(
            static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution<double> distribution;

    return distribution(dev);
}

std::vector<double> Func::rand(unsigned long long int size) {
    std::default_random_engine dev(
            static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution<double> distribution;

    auto res = Func::matrix_1d(size, 0.);

    for (auto i = 0; i < size; ++i) {
        res[i] = distribution(dev);
    }

    return res;
}

std::vector<double> Func::linspace(double start, double end, unsigned long long int q) {
    double step = (end - start) / double(q - 1);

    auto res = matrix_1d(q, 0.);

    for (auto i = 0; i < q; ++i) {
        res[i] = start;
        start += step;
    }
    return res;
}

std::vector<int> Func::round(const std::vector<double> &vec) {
    auto n = vec.size();

    auto res = Func::matrix_1d<int>(n, 0);

    for (auto i = 0; i < n; ++i)
        res[i] = static_cast<int>(std::round(vec[i]));

    return res;
}

std::vector<std::vector<int>> Func::round(const std::vector<std::vector<double>> &matrix) {
    auto n = matrix.size(), m = matrix[0].size();

    auto res = Func::matrix_2d<int>(n, m, 0);

    for (decltype(n) i{0}; i < n; ++i)
        for (decltype(m) j{0}; j < m; ++j)
            res[i][j] = static_cast<int>(std::round(matrix[i][j]));

    return res;
}

std::vector<double> Func::round(const std::vector<double> &vec, int precision) {
    auto n = vec.size();

    auto res = Func::matrix_1d<double>(n, 0.);

    for (decltype(n) i{0}; i < n; ++i)
        res[i] = Func::round(vec[i], precision);

    return res;
}

std::vector<std::vector<double>> Func::round(const std::vector<std::vector<double>> &matrix, int precision) {
    auto n = matrix.size(), m = matrix[0].size();

    auto res = Func::matrix_2d<double>(n, m, 0);

    for (decltype(n) i{0}; i < n; ++i)
        for (decltype(m) j{0}; j < m; ++j)
            res[i][j] = Func::round(matrix[i][j], precision);

    return res;
}

std::vector<int> Func::ceil(const std::vector<double> &vec) {
    auto n = vec.size();

    auto res = Func::matrix_1d<int>(n, 0);

    for (decltype(n) i{0}; i < n; ++i)
        res[i] = static_cast<int>(std::ceil(vec[i]));
}

std::vector<std::vector<int>> Func::ceil(const std::vector<std::vector<double>> &matrix) {
    auto n = matrix.size(), m = matrix[0].size();

    auto res = Func::matrix_2d<int>(n, m, 0);

    for (decltype(n) i{0}; i < n; ++i)
        for (decltype(m) j{0}; j < m; ++j)
            res[i][j] = static_cast<int>(std::ceil(matrix[i][j]));

    return res;
}

std::vector<int> Func::floor(const std::vector<double> &vec) {
    auto n = vec.size();

    auto res = Func::matrix_1d<int>(n, 0);

    for (decltype(n) i{0}; i < n; ++i)
        res[i] = static_cast<int>(std::floor(vec[i]));

    return res;
}

std::vector<std::vector<int>> Func::floor(const std::vector<std::vector<double>> &matrix) {
    auto n = matrix.size(), m = matrix[0].size();

    auto res = Func::matrix_2d<int>(n, m, 0);

    for (decltype(n) i{0}; i < n; ++i)
        for (decltype(m) j{0}; j < m; ++j)
            res[i][j] = static_cast<int>(std::floor(matrix[i][j]));

    return res;
}



