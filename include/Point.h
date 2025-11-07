#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <memory>
#include <iostream>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x, y;

public:
    Point() : x(0), y(0) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}
    
    // Копирующий конструктор
    Point(const Point& other) : x(other.x), y(other.y) {}
    
    // Оператор присваивания
    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    
    // Операторы сравнения
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    // Геттеры
    T getX() const { return x; }
    T getY() const { return y; }
    
    // Сеттеры
    void setX(T x_val) { x = x_val; }
    void setY(T y_val) { y = y_val; }
    
    // Вывод точки
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    
    // Ввод точки
    friend std::istream& operator>>(std::istream& is, Point& point) {
        is >> point.x >> point.y;
        return is;
    }
};

#endif
