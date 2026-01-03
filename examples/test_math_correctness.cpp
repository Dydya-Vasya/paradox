#include "spirit_float.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace paradox;

void test_zero_properties() {
    std::cout << "Testing zero mathematical properties..." << std::endl;
    
    spirit zero = spirit::ZERO;
    
    // Ноль не имеет знака
    assert(zero.isZero());
    assert(!zero.isPositive());
    assert(!zero.isNegative());
    assert(zero.isNonNegative());  // Ноль неотрицателен
    assert(zero.isNonPositive());  // Ноль неположителен
    
    // Отрицание нуля равно нулю
    assert(-zero == zero);
    assert(zero.abs() == zero);
    
    // Ноль плюс ноль равно ноль
    assert(zero + zero == zero);
    
    // Ноль умножить на любое число равно ноль
    assert(zero * spirit(5.0) == zero);
    assert(zero * spirit::INF == 1);
    assert(spirit(5.0) * zero == zero);
    
    // Ноль делить на любое число (кроме нуля) равно ноль
    assert(zero / spirit(5.0) == zero);
    
    // Любое число плюс ноль равно тому же числу
    assert(spirit(5.0) + zero == spirit(5.0));
    assert(spirit::INF + zero == spirit::INF);
    
    std::cout << "Zero properties passed!\n" << std::endl;
}

void test_sign_properties() {
    std::cout << "Testing sign properties..." << std::endl;
    
    spirit pos(5.0);
    spirit neg(-5.0);
    
    // Положительные числа
    assert(pos.isPositive());
    assert(!pos.isNegative());
    assert(pos.isNonNegative());
    assert(!pos.isNonPositive());
    
    // Отрицательные числа
    assert(neg.isNegative());
    assert(!neg.isPositive());
    assert(!neg.isNonNegative());
    assert(neg.isNonPositive());
    
    // Бесконечности
    assert(spirit::INF.isPositive());
    assert(spirit::NEG_INF.isNegative());
    assert(!spirit::INF.isNegative());
    assert(!spirit::NEG_INF.isPositive());
    
    std::cout << "Sign properties passed!\n" << std::endl;
}

void test_comparisons() {
    std::cout << "Testing mathematical comparisons..." << std::endl;
    
    // Ноль сравнения
    assert(spirit::ZERO == spirit(0.0));
    assert(spirit::ZERO != spirit(0.1));
    assert(spirit::ZERO < spirit(0.1));
    assert(spirit::ZERO > spirit(-0.1));
    assert(spirit::ZERO >= spirit::ZERO);
    assert(spirit::ZERO <= spirit::ZERO);
    
    // Обычные числа
    assert(spirit(2.0) < spirit(3.0));
    assert(spirit(3.0) > spirit(2.0));
    assert(spirit(-2.0) < spirit(-1.0));
    assert(spirit(-1.0) > spirit(-2.0));
    
    // Сравнение с бесконечностью
    assert(spirit(1000000.0) < spirit::INF);
    assert(spirit(-1000000.0) > spirit::NEG_INF);
    assert(spirit::INF > spirit(1000000.0));
    assert(spirit::NEG_INF < spirit(-1000000.0));
    
    // Бесконечности
    assert(spirit::NEG_INF < spirit::INF);
    assert(!(spirit::INF < spirit::NEG_INF));
    
    std::cout << "Comparisons passed!\n" << std::endl;
}

void test_arithmetic() {
    std::cout << "Testing arithmetic operations..." << std::endl;
    
    // Сложение
    assert(spirit(2.0) + spirit(3.0) == spirit(5.0));
    assert(spirit(-2.0) + spirit(-3.0) == spirit(-5.0));
    assert(spirit(2.0) + spirit(-3.0) == spirit(-1.0));
    
    // Вычитание
    assert(spirit(5.0) - spirit(3.0) == spirit(2.0));
    assert(spirit(3.0) - spirit(5.0) == spirit(-2.0));
    assert(spirit(2.0) - spirit(2.0) == spirit::ZERO);
    
    // Умножение
    assert(spirit(2.0) * spirit(3.0) == spirit(6.0));
    assert(spirit(2.0) * spirit(-3.0) == spirit(-6.0));
    assert(spirit(-2.0) * spirit(-3.0) == spirit(6.0));
    
    // Деление
    assert(spirit(6.0) / spirit(2.0) == spirit(3.0));
    assert(spirit(6.0) / spirit(-2.0) == spirit(-3.0));
    assert(spirit(-6.0) / spirit(-2.0) == spirit(3.0));
    
    // Деление на ноль
    assert(spirit(5.0) / spirit::ZERO == spirit::INF * 5.0f);
    assert(spirit(-5.0) / spirit::ZERO == spirit::NEG_INF * (5.0f));
    
    // Ноль делить на ноль (неопределенность)
    spirit zero_by_zero = spirit::ZERO / spirit::ZERO;
    // Проверяем, что не падает, результат зависит от реализации
    
    std::cout << "Arithmetic passed!\n" << std::endl;
}

void test_math_functions() {
    std::cout << "Testing mathematical functions..." << std::endl;
    
    // Абсолютное значение
    assert(spirit(5.0).abs() == spirit(5.0));
    assert(spirit(-5.0).abs() == spirit(5.0));
    assert(spirit::ZERO.abs() == spirit::ZERO);
    
    // Обратное значение
    assert(spirit(2.0).inverse() == spirit(0.5));
    assert(spirit(4.0).inverse() == spirit(0.25));
    assert(spirit::ZERO.inverse() == spirit::INF);
    assert(spirit::INF.inverse() == spirit::ZERO);
    
    // sqrt
    assert(sqrt(spirit(4.0)) == spirit(2.0));
    assert(sqrt(spirit(9.0)) == spirit(3.0));
    assert(sqrt(spirit::ZERO) == spirit::ZERO);
    assert(sqrt(spirit::INF) == spirit::INF);
    
    // pow
    assert(pow(spirit(2.0), 3.0) == spirit(8.0));
    assert(pow(spirit(3.0), 2.0) == spirit(9.0));
    assert(pow(spirit(2.0), 0.0) == spirit::ONE);
    assert(pow(spirit::ZERO, 2.0) == spirit::ZERO);
    assert(pow(spirit::INF, 2.0) == spirit::INF);
    
    // exp и log
    assert(exp(spirit::ZERO) == spirit::ONE);
    assert(log(spirit::ONE) == spirit::ZERO);
    assert(exp(spirit::INF) == spirit::INF);
    assert(exp(spirit::NEG_INF) == spirit::ZERO);
    assert(log(spirit::ZERO) == spirit::NEG_INF);
    assert(log(spirit::INF) == spirit::INF);
    
    std::cout << "Math functions passed!\n" << std::endl;
}

void test_edge_cases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    // Бесконечность минус бесконечность (неопределенность)
    spirit inf_minus_inf = spirit::INF - spirit::INF;
    // Проверяем, что не падает
    
    // Бесконечность умножить на ноль (неопределенность)
    spirit inf_times_zero = spirit::INF * spirit::ZERO;
    // Проверяем, что не падает
    
    // Проверка тригонометрических функций
    try {
        sin(spirit::INF);
        assert(false && "Should throw for sin(inf)");
    } catch (const std::domain_error&) {
        // Ожидаемое исключение
    }
    
    try {
        sqrt(spirit(-1.0));
        assert(false && "Should throw for sqrt(-1)");
    } catch (const std::domain_error&) {
        // Ожидаемое исключение
    }
    
    try {
        log(spirit(-1.0));
        assert(false && "Should throw for log(-1)");
    } catch (const std::domain_error&) {
        // Ожидаемое исключение
    }
    
    std::cout << "Edge cases passed!\n" << std::endl;
}

int main() {
    std::cout << "=== Testing mathematical correctness ===\n" << std::endl;
    
    try {
        test_zero_properties();
        test_sign_properties();
        test_comparisons();
        test_arithmetic();
        test_math_functions();
        test_edge_cases();
        
        std::cout << "\n=== All mathematical tests passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}