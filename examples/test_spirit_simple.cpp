#include "spirit_float.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace paradox;

void test_basic_operations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    // Конструкторы
    spirit a(5.0f);
    spirit b(3.0f);
    spirit c(-2.0f);
    
    // Сложение
    spirit d = a + b;
    assert(std::abs(static_cast<double>(d) - 8.0) < 0.001);
    
    // Вычитание
    spirit e = a - b;
    assert(std::abs(static_cast<double>(e) - 2.0) < 0.001);
    
    // Умножение
    spirit f = a * b;
    assert(std::abs(static_cast<double>(f) - 15.0) < 0.001);
    
    // Деление
    spirit g = a / b;
    assert(std::abs(static_cast<double>(g) - (5.0/3.0)) < 0.001);
    
    // Отрицание
    spirit h = -a;
    assert(std::abs(static_cast<double>(h) + 5.0) < 0.001);
    
    // Составные операторы
    spirit i = a;
    i += b;
    assert(std::abs(static_cast<double>(i) - 8.0) < 0.001);
    
    spirit j = a;
    j -= b;
    assert(std::abs(static_cast<double>(j) - 2.0) < 0.001);
    
    spirit k = a;
    k *= b;
    assert(std::abs(static_cast<double>(k) - 15.0) < 0.001);
    
    spirit l = a;
    l /= b;
    assert(std::abs(static_cast<double>(l) - (5.0/3.0)) < 0.001);
    
    std::cout << "Basic operations passed!\n" << std::endl;
}

void test_special_values() {
    std::cout << "Testing special values..." << std::endl;
    
    // Ноль
    assert(spirit::ZERO.isZero());
    assert(!spirit::ZERO.isInfinity());
    assert(spirit::ZERO.isFinite());
    
    // Бесконечность
    assert(spirit::INF.isInfinity());
    assert(!spirit::INF.isZero());
    assert(!spirit::INF.isFinite());
    assert(spirit::INF.isPositive());
    
    // Отрицательная бесконечность
    assert(spirit::NEG_INF.isInfinity());
    assert(spirit::NEG_INF.isNegative());
    
    // Один
    assert(std::abs(static_cast<double>(spirit::ONE) - 1.0) < 0.001);
    assert(spirit::ONE.isFinite());
    assert(spirit::ONE.isPositive());
    
    std::cout << "Special values passed!\n" << std::endl;
}

void test_comparisons() {
    std::cout << "Testing comparisons..." << std::endl;
    
    // Равенство
    assert(spirit(5.0) == spirit(5.0));
    assert(spirit(5.0) != spirit(5.1));
    assert(spirit::ZERO == spirit(0.0));
    
    // Сравнения
    assert(spirit(2.0) < spirit(3.0));
    assert(spirit(3.0) > spirit(2.0));
    assert(spirit(2.0) <= spirit(3.0));
    assert(spirit(3.0) >= spirit(2.0));
    assert(spirit(2.0) <= spirit(2.0));
    assert(spirit(2.0) >= spirit(2.0));
    
    // Сравнение с нулем
    assert(spirit(1.0) > spirit::ZERO);
    assert(spirit(-1.0) < spirit::ZERO);
    
    // Бесконечность
    assert(spirit::INF > spirit(1000000.0));
    assert(spirit::NEG_INF < spirit(-1000000.0));
    
    std::cout << "Comparisons passed!\n" << std::endl;
}

void test_math_functions() {
    std::cout << "Testing math functions..." << std::endl;
    
    // Абсолютное значение
    assert(spirit(-5.0).abs() == spirit(5.0));
    assert(spirit(5.0).abs() == spirit(5.0));
    
    // Обратное значение
    spirit inv = spirit(2.0).inverse();
    assert(std::abs(static_cast<double>(inv) - 0.5) < 0.001);
    
    // Проверки
    assert(spirit(5.0).isPositive());
    assert(spirit(-5.0).isNegative());
    assert(!spirit(5.0).isZero());
    assert(!spirit(5.0).isInfinity());
    assert(spirit(5.0).isFinite());
    
    // Глобальные функции
    spirit s = sqrt(spirit(4.0));
    assert(std::abs(static_cast<double>(s) - 2.0) < 0.001);
    
    spirit p = pow(spirit(2.0), 3.0);
    assert(std::abs(static_cast<double>(p) - 8.0) < 0.001);
    
    spirit e = exp(spirit(0.0));
    assert(std::abs(static_cast<double>(e) - 1.0) < 0.001);
    
    spirit l = log(spirit(1.0));
    assert(std::abs(static_cast<double>(l)) < 0.001);
    
    std::cout << "Math functions passed!\n" << std::endl;
}

void test_string_operations() {
    std::cout << "Testing string operations..." << std::endl;
    
    // toString
    assert(spirit(3.14).toString() == "3.14");
    assert(spirit::ZERO.toString() == "0");
    assert(spirit::INF.toString() == "inf");
    assert(spirit::NEG_INF.toString() == "-inf");
    
    // fromString
    assert(spirit::fromString("5.5") == spirit(5.5));
    assert(spirit::fromString("0") == spirit::ZERO);
    assert(spirit::fromString("inf") == spirit::INF);
    assert(spirit::fromString("-inf") == spirit::NEG_INF);
    
    // Потоковый вывод
    std::ostringstream oss;
    oss << spirit(3.14159);
    assert(oss.str().find("3.14159") != std::string::npos);
    
    std::cout << "String operations passed!\n" << std::endl;
}

void test_mixed_operations() {
    std::cout << "Testing mixed operations..." << std::endl;
    
    // Операции с float справа
    spirit a = spirit(2.0) + 3.0f;
    assert(std::abs(static_cast<double>(a) - 5.0) < 0.001);
    
    spirit b = spirit(2.0) - 3.0f;
    assert(std::abs(static_cast<double>(b) + 1.0) < 0.001);
    
    spirit c = spirit(2.0) * 3.0f;
    assert(std::abs(static_cast<double>(c) - 6.0) < 0.001);
    
    spirit d = spirit(6.0) / 2.0f;
    assert(std::abs(static_cast<double>(d) - 3.0) < 0.001);
    
    // Операции с float слева
    spirit e = 3.0f + spirit(2.0);
    assert(std::abs(static_cast<double>(e) - 5.0) < 0.001);
    
    spirit f = 3.0f - spirit(2.0);
    assert(std::abs(static_cast<double>(f) - 1.0) < 0.001);
    
    spirit g = 3.0f * spirit(2.0);
    assert(std::abs(static_cast<double>(g) - 6.0) < 0.001);
    
    spirit h = 6.0f / spirit(2.0);
    assert(std::abs(static_cast<double>(h) - 3.0) < 0.001);
    
    // Аналогично для double и int
    spirit i = 2 + spirit(3);
    assert(std::abs(static_cast<double>(i) - 5.0) < 0.001);
    
    spirit j = spirit(2) + 3;
    assert(std::abs(static_cast<double>(j) - 5.0) < 0.001);
    
    std::cout << "Mixed operations passed!\n" << std::endl;
}

int main() {
    std::cout << "=== Testing paradox::spirit (simple tests) ===\n" << std::endl;
    
    try {
        test_basic_operations();
        test_special_values();
        test_comparisons();
        test_math_functions();
        test_string_operations();
        test_mixed_operations();
        
        std::cout << "\n=== All simple tests passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}