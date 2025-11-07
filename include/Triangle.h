#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"
#include <cmath>

template<Scalar T>
class Triangle : public Figure<T> {
private:
    T side_length;

public:
    Triangle() : side_length(0) {}
    Triangle(T side) : side_length(side) {
        calculateVertices();
    }
    
    // Копирующий конструктор
    Triangle(const Triangle& other) : side_length(other.side_length) {
        calculateVertices();
    }
    
    // Оператор присваивания
    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            side_length = other.side_length;
            this->vertices.clear();
            calculateVertices();
        }
        return *this;
    }
    
    // Оператор сравнения
    bool operator==(const Triangle& other) const {
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
        return (std::sqrt(3.0) * side_length * side_length) / 4.0;
    }
    
    void printVertices() const override {
        std::cout << "Triangle vertices: ";
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
        // Равносторонний треугольник, вписанный в окружность
        double radius = side_length / std::sqrt(3.0);
        
        this->vertices.push_back(std::make_unique<Point<T>>(0, static_cast<T>(radius)));
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(-side_length/2), static_cast<T>(-radius/2)));
        this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(side_length/2), static_cast<T>(-radius/2)));
    }
};

#endif
