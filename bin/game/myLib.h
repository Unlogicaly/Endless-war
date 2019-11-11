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
//#include <errors.h>

namespace Func
{
    double round(double num, int precision);

    template<typename T>
    void swap(std::vector<T> &a, unsigned long long int i, unsigned long long int j) {
        auto temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    std::vector<std::string> &split(const std::string &s, char c = ' ');

    unsigned long long int fact(unsigned long long n);

    std::vector<std::vector<char>> permutations(const std::vector<char> &source,
                                                unsigned long long n,
                                                unsigned long long m);

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
    std::vector<T> vector_1d(int length, T fill = 0) {
        std::vector<T> res(static_cast<unsigned long long>(length));
        for (auto &t: res) t = fill;
        return res;
    }

    template<typename T>
    std::vector<std::vector<T>> vector_2d(int height, int width, T fill = 0) {
        std::vector<std::vector<T>> res(height, vector_1d(width, fill));
        return res;
    }

    template<typename T>
    std::vector<std::vector<std::vector<T>>> vector_3d(int depth, int height, int width, T fill = 0) {
        std::vector<std::vector<std::vector<T>>> res(static_cast<unsigned long long int>(depth), vector_2d(height, width, fill));
        return res;
    }


    template <typename T>
    T sum(const std::vector<T> &vect) {
        T s{0};
        for (auto el: vect) s += el;
        return s;
    }

    template <typename T>
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
                    res.push_back(Func::sum(t));
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


    template <typename T>
    bool in(const std::vector<T> &src, T sub) {
        for (auto &t: src) {
            if (sub == t) return true;
        }
        return false;
    }

    template <typename T>
    bool in(const std::vector<std::vector<T>> &src, T sub) {
        for (auto &t: src) {
            if (in(t, sub)) return true;
        }
        return false;
    }


    template <typename T>
    T max(const std::vector<T> &vec) {
        T m = vec[0];
        for (auto &t: vec)
            m = std::max(m, t);
        return m;
    }

    template <typename T>
    T max(const std::vector<std::vector<T>> &matrix) {
        T m = matrix[0][0];
        for (auto &vec: matrix)
            m = std::max(m, Func::max(vec));
        return m;
    }

    template<typename T>
    std::vector<T> max(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<T> res;
        switch (axis) {
            case 1: {
                for (auto &t: matrix)
                    res.push_back(Func::max(t));
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


    template <typename T>
    T min(const std::vector<T> &vec) {
        T m = vec[0];
        for (auto &t: vec)
            m = std::min(m, t);
        return m;
    }

    template <typename T>
    T min(const std::vector<std::vector<T>> &matrix) {
        T m = matrix[0][0];
        for (auto &vec: matrix)
            m = std::min(m, Func::min(vec));
        return m;
    }

    template<typename T>
    std::vector<T> min(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<T> res;
        switch (axis) {
            case 1: {
                for (auto &t: matrix)
                    res.push_back(Func::min(t));
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


    template <typename T>
    double mean(const std::vector<T> &vec) {
        return double(Func::sum(vec)) / vec.size();
    }

    template<typename T>
    double mean(const std::vector<std::vector<T>> &matrix) {
        return double(Func::sum(matrix)) / (matrix.size() * matrix[0].size());
    }

    template <typename T>
    std::vector<double> mean(const std::vector<std::vector<T>> &matrix, const int axis) {
        std::vector<double> res;
        switch (axis) {
            case 1: {
                for (auto &vec: matrix)
                    res.push_back(Func::mean(vec));
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


    template <class T>
    void print(const std::vector<T> &src, const std::string &sep = " ", const std::string &end = "\n") {
        for (auto &t: src) {
            std::cout << t << sep;
        }
        std::cout << end;
    }

    template <typename T>
    void print(const std::vector<std::vector<T>> &src, const std::string &sep = " ", const std::string &end = "\n") {
        for (auto &vec: src) {
            print(vec, sep);
        }
        std::cout << end;
    }

    template<typename T, typename P>
    std::ostream &operator << (std::ostream &os, const std::pair<T, P> &src) {
        return os << "(" << src.first << ", " << src.second << ")";
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
}

#endif //UNTITLED3_MYLIB_H
