//
// Created by tarog on 08.11.2019.
//

#ifndef UNTITLED3_MYLIB_H
#define UNTITLED3_MYLIB_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <utility>
#include <algorithm>
#include <array>
#include <set>
#include <cstring>
#include <random>
#include <ctime>
#include <chrono>
#include <cassert>
//#include <errors.h>

#define ull unsigned long long

namespace Func {
    double round(double num, int precision);

    std::vector<int> round(const std::vector<double> &vec);

    std::vector<std::vector<int>> round(const std::vector<std::vector<double>> &matrix);

    std::vector<double> round(const std::vector<double> &vec, int precision);

    std::vector<std::vector<double>> round(const std::vector<std::vector<double>> &matrix, int precision);

    std::vector<int> ceil(const std::vector<double> &vec);

    std::vector<std::vector<int>> ceil(const std::vector<std::vector<double>> &matrix);

    std::vector<int> floor(const std::vector<double> &vec);

    std::vector<std::vector<int>> floor(const std::vector<std::vector<double>> &matrix);

    template<typename T>
    void swap(std::vector<T> &a, ull int i, ull int j) {
        auto temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    std::vector<std::string> &split(const std::string &s, char c = ' ');

    ull int fact(ull n);

    std::vector<std::vector<char>> permutations(const std::vector<char> &source,
                                                ull n,
                                                ull m);

    double d_mean(int count, ...);

    double i_mean(int count, ...);

    double d_max(int count, ...);

    int i_max(int count, ...);

    char c_max(int count, ...);

    std::string s_max(int count, ...);

    double d_min(int count, ...);

    int i_min(int count, ...);

    char c_min(int count, ...);

    std::string s_min(int count, ...);


    template<typename T>
    std::string str(T i) {
        return std::to_string(i);
    }


    template<typename T>
    std::vector<T> matrix_1d(ull length, T fill = 0) {
        std::vector<T> res(length);
        for (auto &t: res) t = fill;
        return res;
    }

    template<typename T>
    std::vector<std::vector<T>> matrix_2d(ull height, ull width, T fill = 0) {
        std::vector<std::vector<T>> res(height, matrix_1d(width, fill));
        return res;
    }

    template<typename T>
    T sum(const std::vector<T> &vect) {
        T s{0};
        for (auto el: vect) s += el;
        return s;
    }

    template<typename T>
    T sum(const std::vector<std::vector<T>> &matrix) {
        T s{0};
        for (auto &vect: matrix) s += sum(vect);
        return s;
    }

    template<typename T>
    std::vector<T> sum(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<T> res;
        switch (axis) {
            case 1: {
                for (auto &t: matrix)
                    res.push_back(sum(t));
                return res;
            }
            case 2: {
                for (auto i = 0; i < matrix[0].size(); ++i) {
                    T s = 0;
                    for (auto j = 0; j < matrix.size(); ++j) {
                        s += matrix[j][i];
                    }
                    res.push_back(s);
                }
                return res;
            }
            default:
                throw std::range_error("Axis " + Func::str(axis) + " is incorrect for 2d matrix");
        }
    }


    template<typename T>
    bool in(const std::vector<T> &src, T sub) {
        for (auto &t: src) {
            if (sub == t) return true;
        }
        return false;
    }

    template<typename T>
    bool in(const std::vector<std::vector<T>> &src, T sub) {
        for (auto &t: src) {
            if (in(t, sub)) return true;
        }
        return false;
    }


    template<typename T>
    T max(const std::vector<T> &vec) {
        T m = vec[0];
        for (auto &t: vec)
            m = std::max(m, t);
        return m;
    }

    template<typename T>
    T max(const std::vector<std::vector<T>> &matrix) {
        T m = matrix[0][0];
        for (auto &vec: matrix)
            m = std::max(m, max(vec));
        return m;
    }

    template<typename T>
    std::vector<T> max(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<T> res;
        switch (axis) {
            case 1: {
                for (auto &t: matrix)
                    res.push_back(max(t));
                return res;
            }
            case 2: {
                for (auto i = 0; i < matrix[0].size(); ++i) {
                    T s = matrix[0][i];
                    for (auto j = 0; j < matrix.size(); ++j)
                        s = std::max(s, matrix[j][i]);
                    res.push_back(s);
                }
                return res;
            }
            default:
                throw std::range_error("Axis " + Func::str(axis) + " is incorrect for 2d matrix");
        }
    }


    template<typename T>
    T min(const std::vector<T> &vec) {
        T m = vec[0];
        for (auto &t: vec)
            m = std::min(m, t);
        return m;
    }

    template<typename T>
    T min(const std::vector<std::vector<T>> &matrix) {
        T m = matrix[0][0];
        for (auto &vec: matrix)
            m = std::min(m, min(vec));
        return m;
    }

    template<typename T>
    std::vector<T> min(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<T> res;
        switch (axis) {
            case 1: {
                for (auto &t: matrix)
                    res.push_back(min(t));
                return res;
            }
            case 2: {
                for (auto i = 0; i < matrix[0].size(); ++i) {
                    T s = matrix[0][i];
                    for (auto j = 0; j < matrix.size(); ++j)
                        s = std::min(s, matrix[j][i]);
                    res.push_back(s);
                }
                return res;
            }
            default:
                throw std::range_error("Axis " + Func::str(axis) + " is incorrect for 2d matrix");
        }
    }


    template<typename T>
    double mean(const std::vector<T> &vec) {
        return double(Func::sum(vec)) / vec.size();
    }

    template<typename T>
    double mean(const std::vector<std::vector<T>> &matrix) {
        return double(Func::sum(matrix)) / (matrix.size() * matrix[0].size());
    }

    template<typename T>
    std::vector<double> mean(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<double> res;
        switch (axis) {
            case 1: {
                for (auto &vec: matrix)
                    res.push_back(mean(vec));
                return res;
            }
            case 2: {
                for (auto i = 0; i < matrix[0].size(); ++i) {
                    double s = 0;
                    for (auto j = 0; j < matrix.size(); ++j) {
                        s += matrix[j][i];
                    }
                    res.push_back(s / matrix.size());
                }
                return res;
            }
            default:
                throw std::range_error("Axis " + Func::str(axis) + " is incorrect for 2d matrix");
        }
    }


    template<class T>
    void print(const std::vector<T> &src,
               const std::string &sep = " ",
               const std::string &end = "\n",
               std::ostream &os = std::cout) {
        for (auto &t: src) {
            os << t << sep;
        }
        os << end;
    }

    template<typename T>
    void print(const std::vector<std::vector<T>> &src,
               const std::string &sep1 = " ",
               const std::string &sep2 = "\n",
               const std::string &end = "\n",
               std::ostream &os = std::cout) {
        for (auto &vec: src) {
            print(vec, sep1, sep2, os);
        }
        os << end;
    }


    template<typename T>
    std::vector<T> flatten(const std::vector<std::vector<T>> &matrix, const int axis = 1) {
        std::vector<T> res;
        res.reserve(matrix.size() * matrix[0].size());
        switch (axis) {
            case 1: {
                for (auto &line: matrix)
                    for (auto &el: line)
                        res.push_back(el);
                return res;
            }
            case 2: {
                for (auto i = 0; i < matrix[0].size(); ++i)
                    for (auto j = 0; j < matrix.size(); ++j)
                        res.push_back(matrix[j][i]);
                return res;
            }
            default:
                throw std::range_error("Axis " + Func::str(axis) + " is incorrect for 2d matrix");
        }
    }

    template<typename T, typename P>
    std::vector<std::pair<T, P>> zip(const std::vector<T> &vec1, const std::vector<P> &vec2) {
        if (vec1.size() != vec2.size())
            throw std::range_error("Sizes of arrays mismatch");
        std::vector<std::pair<T, P>> res;
        res.reserve(vec1.size());
        for (auto i = 0; i < vec1.size(); ++i)
            res.push_back({vec1[i], vec2[i]});
        return res;
    }

    template<typename T>
    std::string type(T) {
        auto _n = typeid(T).name();

        if (_n == typeid(int).name()) return "int";
        if (_n == typeid(double).name()) return "double";
        if (_n == typeid(float).name()) return "float";
        if (_n == typeid(char).name()) return "char";
        if (_n == typeid(char *).name()) return "char*";
        if (_n == typeid(long).name()) return "long";
        if (_n == typeid(long long).name()) return "long long";
        if (_n == typeid(unsigned).name()) return "unsigned";
        if (_n == typeid(unsigned long).name()) return "unsigned long";
        if (_n == typeid(ull).name()) return "ull";
        if (_n == typeid(bool).name()) return "bool";
        if (_n == typeid(void).name()) return "void";
        if (_n == typeid(void *).name()) return "void*";
        if (_n == typeid(std::string).name()) return "string";
        if (_n == typeid(short).name()) return "short";
        if (_n == typeid(unsigned short).name()) return "unsigned short";
        if (_n == typeid(long double).name()) return "long double";

        return _n;
    }

    template<typename T>
    std::vector<std::vector<T>> dot(const std::vector<std::vector<T>> &a1, const std::vector<std::vector<T>> &a2) {

    }

    template<typename T, typename P>
    std::vector<T> copy_as(const std::vector<P> &vec) {
        auto res = matrix_1d(vec.size(), T(0));
        for (auto i = 0; i < vec.size(); ++i)
            res[i] = static_cast<T>(vec[i]);
        return res;
    }

    template<typename T, typename P>
    std::vector<std::vector<T>> copy_as(const std::vector<std::vector<P>> &matrix) {

        auto n = matrix.size(), m = matrix[0].size();

        auto res = matrix_2d(n, m, T(0));

        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < m; ++j)
                res[i][j] = static_cast<T>(matrix[i][j]);

        return res;
    }

    int randint(int start, int end);

    std::vector<int> randint(int start, int end, ull int size);

    double rand();

    std::vector<double> rand(ull int size);

    template<typename T>
    std::vector<std::vector<T>> reshape(const std::vector<T> &vec, ull h, ull w) {
        if (h * w != vec.size())
            throw std::range_error("Can't reshape vector with size " + str(vec.size()) +
                                   " to matrix " + str(h) + "x" + str(w));

        auto res = matrix_2d(h, w, T(0));

        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
                res[i][j] = vec[i * w + j];

        return res;
    }

    template<typename T>
    std::vector<std::vector<T>> reshape(const std::vector<std::vector<T>> &matrix, ull h, ull w) {
        auto n = matrix.size(), m = matrix[0].size();
        if (h * w != n * m)
            throw std::range_error("Can't reshape matrix " + str(n) + "x" + str(m) +
                                   " to matrix " + str(h) + "x" + str(w));

        auto res = matrix_2d(h, w, T(0));

        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
                res[i][j] = matrix[(i * w + j) / m][(i * w + j) % m];

        return res;
    }

    template<typename T>
    std::pair<ull, ull> shape(const std::vector<std::vector<T>> &matrix) {
        return {matrix.size(), matrix[0].size()};
    }

    template<typename T>
    T clipped(T src, T low, T high) {
        assert(high > low);
        return std::max(std::min(src, high), low);
    }

    template<typename T>
    std::vector<T> clipped(const std::vector<T> &vec, T low, T high) {
        assert(high > low);
        auto res = matrix_1d(vec.size(), T(0));

        for (auto i = 0; i < vec.size(); ++i)
            res[i] = std::max(std::min(vec[i], high), low);

        return res;
    }

    template<typename T>
    std::vector<std::vector<T>> clipped(const std::vector<std::vector<T>> &matrix, T low, T high) {
        assert(high > low);

        auto n = matrix.size(), m = matrix[0].size();

        auto res = matrix_2d(n, m, T(0));

        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < m; ++j)
                res[i][j] = std::max(std::min(matrix[i][j], high), low);

        return res;
    }

    template<typename T>
    void clip(T &src, T low, T high) {
        assert(high > low);
        src = std::max(std::min(src, high), low);
    }

    template<typename T>
    void clip(std::vector<T> &vec, T low, T high) {
        assert(high > low);

        for (auto i = 0; i < vec.size(); ++i)
            vec[i] = std::max(std::min(vec[i], high), low);
    }

    template<typename T>
    void clip(std::vector<std::vector<T>> &matrix, T low, T high) {
        assert(high > low);

        auto n = matrix.size(), m = matrix[0].size();

        for (auto i = 0; i < n; ++i)
            for (auto j = 0; j < m; ++j)
                matrix[i][j] = std::max(std::min(matrix[i][j], high), low);
    }

    template<typename T>
    std::vector<T> range(T start, T end, T step = 1) {
        assert((end - start) * step > 0);

        std::vector<T> res;

        while (step > 0 == start < end) {
            res.push_back(start);
            start += step;
        }
        return res;
    }

    template<typename T>
    std::vector<T> range(T end) {
        assert(end);
        T step = (end > 0 ? 1 : -1);
        return range(0, end, step);
    }

    std::vector<double> linspace(double start, double end, ull int q);
}

template<typename T, typename P>
std::ostream &operator<<(std::ostream &os, const std::pair<T, P> &src) {
    return os << "(" << src.first << ", " << src.second << ")";
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &a1, const std::vector<T> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<T>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] * a2[i];

    return res;
}

template<typename T, typename P>
std::vector<double> operator*(const std::vector<T> &a1, const std::vector<P> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<double>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] * a2[i];

    return res;
}

template<typename T>
std::vector<std::vector<T>> operator*(const std::vector<std::vector<T>> &a1,
                                      const std::vector<std::vector<T>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<T>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] * a2[i][j];

    return res;
}

template<typename T, typename P>
std::vector<std::vector<double>> operator*(const std::vector<std::vector<T>> &a1,
                                           const std::vector<std::vector<P>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<double>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] * a2[i][j];

    return res;
}


template<typename T>
std::vector<double> operator/(const std::vector<T> &a1, const std::vector<T> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    if (Func::in(a2, T(0)))
        throw std::runtime_error("Zero devising error");

    auto res = Func::matrix_1d<double>(n);

    for (auto i = 0; i < n; ++i) res[i] = double(a1[i]) / a2[i];

    return res;
}

template<typename T, typename P>
std::vector<double> operator/(const std::vector<T> &a1, const std::vector<P> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    if (Func::in(a2, P(0)))
        throw std::runtime_error("Zero devising error");

    auto res = Func::matrix_1d<double>(n);

    for (auto i = 0; i < n; ++i) res[i] = double(a1[i]) / a2[i];

    return res;
}

template<typename T>
std::vector<std::vector<double>> operator/(const std::vector<std::vector<T>> &a1,
                                           const std::vector<std::vector<T>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    if (Func::in(a2, T(0)))
        throw std::runtime_error("Zero devising error");

    auto res = Func::matrix_2d<double>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = double(a1[i][j]) / a2[i][j];

    return res;
}

template<typename T, typename P>
std::vector<std::vector<double>> operator/(const std::vector<std::vector<T>> &a1,
                                           const std::vector<std::vector<P>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    if (Func::in(a2, P(0)))
        throw std::runtime_error("Zero devising error");

    auto res = Func::matrix_2d<double>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = double(a1[i][j]) / a2[i][j];

    return res;
}


template<typename T>
std::vector<T> operator+(const std::vector<T> &a1, const std::vector<T> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<T>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] + a2[i];

    return res;
}

template<typename T, typename P>
std::vector<double> operator+(const std::vector<T> &a1, const std::vector<P> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<double>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] + a2[i];

    return res;
}

template<typename T>
std::vector<std::vector<T>> operator+(const std::vector<std::vector<T>> &a1,
                                      const std::vector<std::vector<T>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<T>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] + a2[i][j];

    return res;
}

template<typename T, typename P>
std::vector<std::vector<double>> operator+(const std::vector<std::vector<T>> &a1,
                                           const std::vector<std::vector<P>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<double>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] + a2[i][j];

    return res;
}


template<typename T>
std::vector<T> operator-(const std::vector<T> &a1, const std::vector<T> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<T>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] - a2[i];

    return res;
}

template<typename T, typename P>
std::vector<double> operator-(const std::vector<T> &a1, const std::vector<P> &a2) {

    auto n = a1.size();

    if (n != a2.size())
        throw std::range_error("Can't multiple vectors with different lengths");

    auto res = Func::matrix_1d<double>(n);

    for (auto i = 0; i < n; ++i) res[i] = a1[i] - a2[i];

    return res;
}

template<typename T>
std::vector<std::vector<T>> operator-(const std::vector<std::vector<T>> &a1,
                                      const std::vector<std::vector<T>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<T>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] - a2[i][j];

    return res;
}

template<typename T, typename P>
std::vector<std::vector<double>> operator-(const std::vector<std::vector<T>> &a1,
                                           const std::vector<std::vector<P>> &a2) {

    auto n = a1.size(), m = a1[0].size();

    if (n != a2.size() or m != a2[0].size())
        throw std::range_error("Can't multiple matrix with different sizes");

    auto res = Func::matrix_2d<double>(n, m);

    for (auto i = 0; i < n; ++i)
        for (auto j = 0; j < m; ++j)
            res[i][j] = a1[i][j] - a2[i][j];

    return res;
}

#endif //UNTITLED3_MYLIB_H
