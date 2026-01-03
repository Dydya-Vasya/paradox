#ifndef PARADOX_SPIRIT_H
#define PARADOX_SPIRIT_H

#include <iostream>
#include <string>

namespace paradox {

class spirit {
public:
    // Основные конструкторы
    spirit(float value = 0.0f) noexcept;
    spirit(double value) noexcept;
    spirit(int value) noexcept;
    
    // Деструктор
    ~spirit();

    // Копирование и перемещение
    spirit(const spirit& other);
    spirit(spirit&& other) noexcept;
    
    // Операторы присваивания
    spirit& operator=(const spirit& other);
    spirit& operator=(spirit&& other) noexcept;
    
    // Арифметические операторы
    spirit operator-() const;
    spirit operator+(const spirit& other) const;
    spirit operator-(const spirit& other) const;
    spirit operator*(const spirit& other) const;
    spirit operator/(const spirit& divisor) const;
    
    spirit& operator+=(const spirit& other);
    spirit& operator-=(const spirit& other);
    spirit& operator*=(const spirit& other);
    spirit& operator/=(const spirit& divisor);
    
    // Операторы с обычными числами
    spirit operator+(float val) const;
    spirit operator-(float val) const;
    spirit operator*(float val) const;
    spirit operator/(float val) const;
    
    spirit operator+(double val) const;
    spirit operator-(double val) const;
    spirit operator*(double val) const;
    spirit operator/(double val) const;
    
    spirit operator+(int val) const;
    spirit operator-(int val) const;
    spirit operator*(int val) const;
    spirit operator/(int val) const;
    
    // Операторы сравнения
    bool operator==(const spirit& other) const;
    bool operator!=(const spirit& other) const;
    bool operator<(const spirit& other) const;
    bool operator>(const spirit& other) const;
    bool operator<=(const spirit& other) const;
    bool operator>=(const spirit& other) const;
    
    // Математические методы
    spirit abs() const;
    spirit inverse() const;
    
    // Проверки свойств (математически корректные)
    bool isZero() const;          // Является ли нулём
    bool isInfinity() const;      // Является ли бесконечностью
    bool isFinite() const;        // Конечное число (не ноль и не бесконечность)
    bool isNegative() const;      // Отрицательное число (< 0)
    bool isPositive() const;      // Положительное число (> 0)
    bool isNonNegative() const;   // Неотрицательное (≥ 0)
    bool isNonPositive() const;   // Неположительное (≤ 0)
    
    // Преобразования
    explicit operator double() const;
    explicit operator float() const;
    std::string toString() const;
    
    // Статические методы
    static spirit fromString(const std::string& s);
    static spirit parse(const std::string& s);
    
    // Статические константы
    static const spirit ZERO;
    static const spirit INF;
    static const spirit NEG_INF;
    static const spirit ONE;
    static const spirit NEG_ONE;
    static const spirit EPSILON;
    
    // Математические функции
    friend spirit sqrt(const spirit& x);
    friend spirit pow(const spirit& x, double exponent);
    friend spirit exp(const spirit& x);
    friend spirit log(const spirit& x);
    friend spirit sin(const spirit& x);
    friend spirit cos(const spirit& x);
    friend spirit tan(const spirit& x);
    
private:
    // Скрытая реализация (Pimpl)
    class Impl;
    Impl* pimpl;
    
    // Вспомогательные конструкторы
    spirit(Impl* impl);
    
    // Дружественные операторы для работы с числами с левой стороны
    friend spirit operator+(float lhs, const spirit& rhs);
    friend spirit operator-(float lhs, const spirit& rhs);
    friend spirit operator*(float lhs, const spirit& rhs);
    friend spirit operator/(float lhs, const spirit& rhs);
    
    friend spirit operator+(double lhs, const spirit& rhs);
    friend spirit operator-(double lhs, const spirit& rhs);
    friend spirit operator*(double lhs, const spirit& rhs);
    friend spirit operator/(double lhs, const spirit& rhs);
    
    friend spirit operator+(int lhs, const spirit& rhs);
    friend spirit operator-(int lhs, const spirit& rhs);
    friend spirit operator*(int lhs, const spirit& rhs);
    friend spirit operator/(int lhs, const spirit& rhs);
};

// Ввод/вывод
std::ostream& operator<<(std::ostream& os, const spirit& num);
std::istream& operator>>(std::istream& is, spirit& num);

// Операторы с числами слева
spirit operator+(float lhs, const spirit& rhs);
spirit operator-(float lhs, const spirit& rhs);
spirit operator*(float lhs, const spirit& rhs);
spirit operator/(float lhs, const spirit& rhs);

spirit operator+(double lhs, const spirit& rhs);
spirit operator-(double lhs, const spirit& rhs);
spirit operator*(double lhs, const spirit& rhs);
spirit operator/(double lhs, const spirit& rhs);

spirit operator+(int lhs, const spirit& rhs);
spirit operator-(int lhs, const spirit& rhs);
spirit operator*(int lhs, const spirit& rhs);
spirit operator/(int lhs, const spirit& rhs);

} // namespace paradox

#endif // PARADOX_SPIRIT_H