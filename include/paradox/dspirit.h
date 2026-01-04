#ifndef PARADOX_DSPIRIT_H
#define PARADOX_DSPIRIT_H

#ifdef _WIN32
    // Windows DLL support
    #ifdef PARADOX_DSPIRIT_EXPORTS
        #define PARADOX_API __declspec(dllexport)
    #else
        #define PARADOX_API __declspec(dllimport)
    #endif
#else
    // Linux/macOS - no DLLs
    #define PARADOX_API
#endif

#include <iostream>
#include <string>

namespace paradox {

class dspirit {
public:
    // Основные конструкторы
    dspirit(double value = 0.0) noexcept;
    dspirit(float value) noexcept;
    dspirit(int value) noexcept;
    

    static dspirit fromLevel(double value, double level);

    // Деструктор
    ~dspirit();

    // Копирование и перемещение
    dspirit(const dspirit& other);
    dspirit(dspirit&& other) noexcept;
    
    // Операторы присваивания
    dspirit& operator=(const dspirit& other);
    dspirit& operator=(dspirit&& other) noexcept;
    
    // Арифметические операторы
    dspirit operator-() const;
    dspirit operator+(const dspirit& other) const;
    dspirit operator-(const dspirit& other) const;
    dspirit operator*(const dspirit& other) const;
    dspirit operator/(const dspirit& divisor) const;
    
    dspirit& operator+=(const dspirit& other);
    dspirit& operator-=(const dspirit& other);
    dspirit& operator*=(const dspirit& other);
    dspirit& operator/=(const dspirit& divisor);
    
    // Операторы с обычными числами
    dspirit operator+(double val) const;
    dspirit operator-(double val) const;
    dspirit operator*(double val) const;
    dspirit operator/(double val) const;
    
    dspirit operator+(float val) const;
    dspirit operator-(float val) const;
    dspirit operator*(float val) const;
    dspirit operator/(float val) const;
    
    dspirit operator+(int val) const;
    dspirit operator-(int val) const;
    dspirit operator*(int val) const;
    dspirit operator/(int val) const;
    
    // Операторы сравнения
    bool operator==(const dspirit& other) const;
    bool operator!=(const dspirit& other) const;
    bool operator<(const dspirit& other) const;
    bool operator>(const dspirit& other) const;
    bool operator<=(const dspirit& other) const;
    bool operator>=(const dspirit& other) const;
    
    // Математические методы
    dspirit abs() const;
    dspirit inverse() const;
    
    // Проверки свойств
    bool isZero() const;
    bool isInfinity() const;
    bool isFinite() const;
    bool isNegative() const;
    bool isPositive() const;
    bool isNonNegative() const;
    bool isNonPositive() const;
    
    // Преобразования
    explicit operator double() const;
    explicit operator float() const;
    std::string toString() const;
    
    // Статические методы
    static dspirit fromString(const std::string& s);
    static dspirit parse(const std::string& s);
    
    // Статические константы
    static const dspirit ZERO;
    static const dspirit INF;
    static const dspirit NEG_INF;
    static const dspirit ONE;
    static const dspirit NEG_ONE;
    static const dspirit EPSILON;
    
    // Математические функции
    friend dspirit sqrt(const dspirit& x);
    friend dspirit pow(const dspirit& x, double exponent);
    friend dspirit exp(const dspirit& x);
    friend dspirit log(const dspirit& x);
    friend dspirit sin(const dspirit& x);
    friend dspirit cos(const dspirit& x);
    friend dspirit tan(const dspirit& x);
    
        // Новые методы для отладки
    double debugR() const;
    double debugI() const;
    double debugJ() const;
    double debugLevel() const;
    std::string debugString() const;
    
    // Явные методы преобразования
    double toDouble() const;
    float toFloat() const;

private:
    // Скрытая реализация (Pimpl)
    class Impl;
    Impl* pimpl;
    
    // Вспомогательные конструкторы
    dspirit(Impl* impl);
    
    // Дружественные операторы для работы с числами с левой стороны
    friend dspirit operator+(double lhs, const dspirit& rhs);
    friend dspirit operator-(double lhs, const dspirit& rhs);
    friend dspirit operator*(double lhs, const dspirit& rhs);
    friend dspirit operator/(double lhs, const dspirit& rhs);
    
    friend dspirit operator+(float lhs, const dspirit& rhs);
    friend dspirit operator-(float lhs, const dspirit& rhs);
    friend dspirit operator*(float lhs, const dspirit& rhs);
    friend dspirit operator/(float lhs, const dspirit& rhs);
    
    friend dspirit operator+(int lhs, const dspirit& rhs);
    friend dspirit operator-(int lhs, const dspirit& rhs);
    friend dspirit operator*(int lhs, const dspirit& rhs);
    friend dspirit operator/(int lhs, const dspirit& rhs);
};

// Ввод/вывод
std::ostream& operator<<(std::ostream& os, const dspirit& num);
std::istream& operator>>(std::istream& is, dspirit& num);

// Операторы с числами слева
dspirit operator+(double lhs, const dspirit& rhs);
dspirit operator-(double lhs, const dspirit& rhs);
dspirit operator*(double lhs, const dspirit& rhs);
dspirit operator/(double lhs, const dspirit& rhs);

dspirit operator+(float lhs, const dspirit& rhs);
dspirit operator-(float lhs, const dspirit& rhs);
dspirit operator*(float lhs, const dspirit& rhs);
dspirit operator/(float lhs, const dspirit& rhs);

dspirit operator+(int lhs, const dspirit& rhs);
dspirit operator-(int lhs, const dspirit& rhs);
dspirit operator*(int lhs, const dspirit& rhs);
dspirit operator/(int lhs, const dspirit& rhs);

} // namespace paradox

#endif // PARADOX_DSPIRIT_H