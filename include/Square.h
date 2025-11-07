#ifndef SQUARE_H
#define SQUARE_H

#include "Figure.h"
#include <cmath>

template<Scalar T>
class Square : public Figure<T> {
private:
    T side_length;

public:
    Square() : side_length(0) {}
    Square(T side) : side_length(side) {
        calculateVertices();
    }
    
    // Копирующий конструктор
    Square(const Square& other) : side_length(other.side_length) {
        calculateVertices();
    }
    
    // Оператор присваивания
    Square& operator=(const Square& other) {
        if (this != &other) {
            side_length = other.side_length;
            this->vertices.clear();
            calculateVertices();
        }
        return *this;
    }
    
    // Оператор сравнения
    bool operator==(const Square& other) const {
        return Figure<T>::operator==(other) && side_length == other.side_length;
    }
    
    // Реализация виртуальных методов
    Point<T> getCenter() const override {
        if (this->vertices.empty()) return Point<T>(0, 0);
        
        T sum_x = 0, sum_y = 0;
        for (const auto& vertex : this->vertices) {
            sum_x += vertex->getX();
            sum_y += vertex->getY();
        }
        return Point<T>(sum_x / this->vertices.size(), sum_y / this->vertices.size());
    }
    
    double getArea() const override {
        return static_cast<double>(side_length * side_length);
    }
    
    void printVertices() const override {
        std::cout << "Square vertices: ";
        for (size_t i = 0; i < this->vertices.size(); ++i) {
            std::cout << *this->vertices[i];
            if (i != this->vertices.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    void readFromStream(std::istream& is) override {
        is >> side_length;
        calculateVertices();
    }
    
    T getSideLength() const { return side_length; }

private:
    void calculateVertices() {
        this->vertices.clear();
        // Квадрат, вписанный в окружность
        double radius = side_length / std::sqrt(2.0);
        
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(radius), static_cast<T>(radius)));
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(-radius), static_cast<T>(radius)));
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(-radius), static_cast<T>(-radius)));
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(radius), static_cast<T>(-radius)));
    }
};

#endif
