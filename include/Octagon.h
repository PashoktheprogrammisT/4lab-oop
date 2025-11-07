#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"
#include <cmath>

template<Scalar T>
class Octagon : public Figure<T> {
private:
    T side_length;

public:
    Octagon() : side_length(0) {}
    Octagon(T side) : side_length(side) {
        calculateVertices();
    }
    
    // Копирующий конструктор
    Octagon(const Octagon& other) : side_length(other.side_length) {
        calculateVertices();
    }
    
    // Оператор присваивания
    Octagon& operator=(const Octagon& other) {
        if (this != &other) {
            side_length = other.side_length;
            this->vertices.clear();
            calculateVertices();
        }
        return *this;
    }
    
    // Оператор сравнения
    bool operator==(const Octagon& other) const {
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
        return 2.0 * (1.0 + std::sqrt(2.0)) * static_cast<double>(side_length * side_length);
    }
    
    void printVertices() const override {
        std::cout << "Octagon vertices: ";
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
        double radius = side_length / (2.0 * std::sin(M_PI / 8.0));
        
        for (int i = 0; i < 8; ++i) {
            double angle = 2.0 * M_PI * i / 8.0 - M_PI / 8.0;
            double x = radius * std::cos(angle);
            double y = radius * std::sin(angle);
            this->vertices.push_back(std::make_unique<Point<T>>(static_cast<T>(x), static_cast<T>(y)));
        }
    }
};

#endif
