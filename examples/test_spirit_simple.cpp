#include "dspirit.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace paradox;

void test_basic_operations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    // Конструкторы
    dspirit a(5.0f);
    dspirit b(3.0f);
    dspirit c(-2.0f);
    
    // Сложение
    dspirit d = a + b;
    assert(std::abs(static_cast<double>(d) - 8.0) < 0.001);
    
    // Вычитание
    dspirit e = a - b;
    assert(std::abs(static_cast<double>(e) - 2.0) < 0.001);
    
    // Умножение
    dspirit f = a * b;
    assert(std::abs(static_cast<double>(f) - 15.0) < 0.001);
    
    // Деление
    dspirit g = a / b;
    assert(std::abs(static_cast<double>(g) - (5.0/3.0)) < 0.001);
    
    // Отрицание
    dspirit h = -a;
    assert(std::abs(static_cast<double>(h) + 5.0) < 0.001);
    
    // Составные операторы
    dspirit i = a;
    i += b;
    assert(std::abs(static_cast<double>(i) - 8.0) < 0.001);
    
    dspirit j = a;
    j -= b;
    assert(std::abs(static_cast<double>(j) - 2.0) < 0.001);
    
    dspirit k = a;
    k *= b;
    assert(std::abs(static_cast<double>(k) - 15.0) < 0.001);
    
    dspirit l = a;
    l /= b;
    assert(std::abs(static_cast<double>(l) - (5.0/3.0)) < 0.001);
    
    std::cout << "Basic operations passed!\n" << std::endl;
}

void test_special_values() {
    std::cout << "Testing special values..." << std::endl;
    
    // Ноль
    assert(dspirit::ZERO.isZero());
    assert(!dspirit::ZERO.isInfinity());
    assert(dspirit::ZERO.isFinite());
    
    // Бесконечность
    assert(dspirit::INF.isInfinity());
    assert(!dspirit::INF.isZero());
    assert(!dspirit::INF.isFinite());
    assert(dspirit::INF.isPositive());
    
    // Отрицательная бесконечность
    assert(dspirit::NEG_INF.isInfinity());
    assert(dspirit::NEG_INF.isNegative());
    
    // Один
    assert(std::abs(static_cast<double>(dspirit::ONE) - 1.0) < 0.001);
    assert(dspirit::ONE.isFinite());
    assert(dspirit::ONE.isPositive());
    
    std::cout << "Special values passed!\n" << std::endl;
}

void test_comparisons() {
    std::cout << "Testing comparisons..." << std::endl;
    
    // Равенство
    assert(dspirit(5.0) == dspirit(5.0));
    assert(dspirit(5.0) != dspirit(5.1));
    assert(dspirit::ZERO == dspirit(0.0));
    
    // Сравнения
    assert(dspirit(2.0) < dspirit(3.0));
    assert(dspirit(3.0) > dspirit(2.0));
    assert(dspirit(2.0) <= dspirit(3.0));
    assert(dspirit(3.0) >= dspirit(2.0));
    assert(dspirit(2.0) <= dspirit(2.0));
    assert(dspirit(2.0) >= dspirit(2.0));
    
    // Сравнение с нулем
    assert(dspirit(1.0) > dspirit::ZERO);
    assert(dspirit(-1.0) < dspirit::ZERO);
    
    // Бесконечность
    assert(dspirit::INF > dspirit(1000000.0));
    assert(dspirit::NEG_INF < dspirit(-1000000.0));
    
    std::cout << "Comparisons passed!\n" << std::endl;
}

void test_math_functions() {
    std::cout << "Testing math functions..." << std::endl;
    
    // Абсолютное значение
    assert(dspirit(-5.0).abs() == dspirit(5.0));
    assert(dspirit(5.0).abs() == dspirit(5.0));
    
    // Обратное значение
    dspirit inv = dspirit(2.0).inverse();
    assert(std::abs(static_cast<double>(inv) - 0.5) < 0.001);
    
    // Проверки
    assert(dspirit(5.0).isPositive());
    assert(dspirit(-5.0).isNegative());
    assert(!dspirit(5.0).isZero());
    assert(!dspirit(5.0).isInfinity());
    assert(dspirit(5.0).isFinite());
    
    // Глобальные функции
    dspirit s = sqrt(dspirit(4.0));
    assert(std::abs(static_cast<double>(s) - 2.0) < 0.001);
    
    dspirit p = pow(dspirit(2.0), 3.0);
    assert(std::abs(static_cast<double>(p) - 8.0) < 0.001);
    
    dspirit e = exp(dspirit(0.0));
    assert(std::abs(static_cast<double>(e) - 1.0) < 0.001);
    
    dspirit l = log(dspirit(1.0));
    assert(std::abs(static_cast<double>(l)) < 0.001);
    
    std::cout << "Math functions passed!\n" << std::endl;
}

void test_string_operations() {
    std::cout << "Testing string operations..." << std::endl;
    
    // toString
    assert(dspirit(3.14).toString() == "3.14");
    assert(dspirit::ZERO.toString() == "0");
    assert(dspirit::INF.toString() == "inf");
    assert(dspirit::NEG_INF.toString() == "-inf");
    
    // fromString
    assert(dspirit::fromString("5.5") == dspirit(5.5));
    assert(dspirit::fromString("0") == dspirit::ZERO);
    assert(dspirit::fromString("inf") == dspirit::INF);
    assert(dspirit::fromString("-inf") == dspirit::NEG_INF);
    
    // Потоковый вывод
    std::ostringstream oss;
    oss << dspirit(3.14159);
    assert(oss.str().find("3.14159") != std::string::npos);
    
    std::cout << "String operations passed!\n" << std::endl;
}

void test_mixed_operations() {
    std::cout << "Testing mixed operations..." << std::endl;
    
    // Операции с float справа
    dspirit a = dspirit(2.0) + 3.0f;
    assert(std::abs(static_cast<double>(a) - 5.0) < 0.001);
    
    dspirit b = dspirit(2.0) - 3.0f;
    assert(std::abs(static_cast<double>(b) + 1.0) < 0.001);
    
    dspirit c = dspirit(2.0) * 3.0f;
    assert(std::abs(static_cast<double>(c) - 6.0) < 0.001);
    
    dspirit d = dspirit(6.0) / 2.0f;
    assert(std::abs(static_cast<double>(d) - 3.0) < 0.001);
    
    // Операции с float слева
    dspirit e = 3.0f + dspirit(2.0);
    assert(std::abs(static_cast<double>(e) - 5.0) < 0.001);
    
    dspirit f = 3.0f - dspirit(2.0);
    assert(std::abs(static_cast<double>(f) - 1.0) < 0.001);
    
    dspirit g = 3.0f * dspirit(2.0);
    assert(std::abs(static_cast<double>(g) - 6.0) < 0.001);
    
    dspirit h = 6.0f / dspirit(2.0);
    assert(std::abs(static_cast<double>(h) - 3.0) < 0.001);
    
    // Аналогично для double и int
    dspirit i = 2 + dspirit(3);
    assert(std::abs(static_cast<double>(i) - 5.0) < 0.001);
    
    dspirit j = dspirit(2) + 3;
    assert(std::abs(static_cast<double>(j) - 5.0) < 0.001);
    
    std::cout << "Mixed operations passed!\n" << std::endl;
}

int main() {
    std::cout << "=== Testing paradox::dspirit (simple tests) ===\n" << std::endl;
    
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