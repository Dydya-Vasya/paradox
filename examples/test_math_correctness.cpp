#include "dspirit.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace paradox;

void test_zero_properties() {
    std::cout << "Testing zero mathematical properties..." << std::endl;
    
    dspirit zero = dspirit::ZERO;
    
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
    assert(zero * dspirit(5.0) == zero);
    assert(zero * dspirit::INF == 1);
    assert(dspirit(5.0) * zero == zero);
    
    // Ноль делить на любое число (кроме нуля) равно ноль
    assert(zero / dspirit(5.0) == zero);
    
    // Любое число плюс ноль равно тому же числу
    assert(dspirit(5.0) + zero == dspirit(5.0));
    assert(dspirit::INF + zero == dspirit::INF);
    
    std::cout << "Zero properties passed!\n" << std::endl;
}

void test_sign_properties() {
    std::cout << "Testing sign properties..." << std::endl;
    
    dspirit pos(5.0);
    dspirit neg(-5.0);
    
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
    assert(dspirit::INF.isPositive());
    assert(dspirit::NEG_INF.isNegative());
    assert(!dspirit::INF.isNegative());
    assert(!dspirit::NEG_INF.isPositive());
    
    std::cout << "Sign properties passed!\n" << std::endl;
}

void test_comparisons() {
    std::cout << "Testing mathematical comparisons..." << std::endl;
    
    // Ноль сравнения
    assert(dspirit::ZERO == dspirit(0.0));
    assert(dspirit::ZERO != dspirit(0.1));
    assert(dspirit::ZERO < dspirit(0.1));
    assert(dspirit::ZERO > dspirit(-0.1));
    assert(dspirit::ZERO >= dspirit::ZERO);
    assert(dspirit::ZERO <= dspirit::ZERO);
    
    // Обычные числа
    assert(dspirit(2.0) < dspirit(3.0));
    assert(dspirit(3.0) > dspirit(2.0));
    assert(dspirit(-2.0) < dspirit(-1.0));
    assert(dspirit(-1.0) > dspirit(-2.0));
    
    // Сравнение с бесконечностью
    assert(dspirit(1000000.0) < dspirit::INF);
    assert(dspirit(-1000000.0) > dspirit::NEG_INF);
    assert(dspirit::INF > dspirit(1000000.0));
    assert(dspirit::NEG_INF < dspirit(-1000000.0));
    
    // Бесконечности
    assert(dspirit::NEG_INF < dspirit::INF);
    assert(!(dspirit::INF < dspirit::NEG_INF));
    
    std::cout << "Comparisons passed!\n" << std::endl;
}

void test_arithmetic() {
    std::cout << "Testing arithmetic operations..." << std::endl;
    
    // Сложение
    assert(dspirit(2.0) + dspirit(3.0) == dspirit(5.0));
    assert(dspirit(-2.0) + dspirit(-3.0) == dspirit(-5.0));
    assert(dspirit(2.0) + dspirit(-3.0) == dspirit(-1.0));
    
    // Вычитание
    assert(dspirit(5.0) - dspirit(3.0) == dspirit(2.0));
    assert(dspirit(3.0) - dspirit(5.0) == dspirit(-2.0));
    assert(dspirit(2.0) - dspirit(2.0) == dspirit::ZERO);
    
    // Умножение
    assert(dspirit(2.0) * dspirit(3.0) == dspirit(6.0));
    assert(dspirit(2.0) * dspirit(-3.0) == dspirit(-6.0));
    assert(dspirit(-2.0) * dspirit(-3.0) == dspirit(6.0));
    
    // Деление
    assert(dspirit(6.0) / dspirit(2.0) == dspirit(3.0));
    assert(dspirit(6.0) / dspirit(-2.0) == dspirit(-3.0));
    assert(dspirit(-6.0) / dspirit(-2.0) == dspirit(3.0));
    
    // Деление на ноль
    assert(dspirit(5.0) / dspirit::ZERO == dspirit::INF * 5.0f);
    assert(dspirit(-5.0) / dspirit::ZERO == dspirit::NEG_INF * (5.0f));
    
    // Ноль делить на ноль (неопределенность)
    dspirit zero_by_zero = dspirit::ZERO / dspirit::ZERO;
    // Проверяем, что не падает, результат зависит от реализации
    
    std::cout << "Arithmetic passed!\n" << std::endl;
}

void test_math_functions() {
    std::cout << "Testing mathematical functions..." << std::endl;
    
    // Абсолютное значение
    assert(dspirit(5.0).abs() == dspirit(5.0));
    assert(dspirit(-5.0).abs() == dspirit(5.0));
    assert(dspirit::ZERO.abs() == dspirit::ZERO);
    
    // Обратное значение
    assert(dspirit(2.0).inverse() == dspirit(0.5));
    assert(dspirit(4.0).inverse() == dspirit(0.25));
    assert(dspirit::ZERO.inverse() == dspirit::INF);
    assert(dspirit::INF.inverse() == dspirit::ZERO);
    
    // sqrt
    assert(sqrt(dspirit(4.0)) == dspirit(2.0));
    assert(sqrt(dspirit(9.0)) == dspirit(3.0));
    assert(sqrt(dspirit::ZERO) == dspirit::ZERO);
    assert(sqrt(dspirit::INF) == dspirit::INF);
    
    // pow
    assert(pow(dspirit(2.0), 3.0) == dspirit(8.0));
    assert(pow(dspirit(3.0), 2.0) == dspirit(9.0));
    assert(pow(dspirit(2.0), 0.0) == dspirit::ONE);
    assert(pow(dspirit::ZERO, 2.0) == dspirit::ZERO);
    assert(pow(dspirit::INF, 2.0) == dspirit::INF);
    
    // exp и log
    assert(exp(dspirit::ZERO) == dspirit::ONE);
    assert(log(dspirit::ONE) == dspirit::ZERO);
    assert(exp(dspirit::INF) == dspirit::INF);
    assert(exp(dspirit::NEG_INF) == dspirit::ZERO);
    assert(log(dspirit::ZERO) == dspirit::NEG_INF);
    assert(log(dspirit::INF) == dspirit::INF);
    
    std::cout << "Math functions passed!\n" << std::endl;
}

void test_edge_cases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    // Бесконечность минус бесконечность (неопределенность)
    dspirit inf_minus_inf = dspirit::INF - dspirit::INF;
    // Проверяем, что не падает
    
    // Бесконечность умножить на ноль (неопределенность)
    dspirit inf_times_zero = dspirit::INF * dspirit::ZERO;
    // Проверяем, что не падает
    
    // Проверка тригонометрических функций
    try {
        sin(dspirit::INF);
        assert(false && "Should throw for sin(inf)");
    } catch (const std::domain_error&) {
        // Ожидаемое исключение
    }
    
    try {
        sqrt(dspirit(-1.0));
        assert(false && "Should throw for sqrt(-1)");
    } catch (const std::domain_error&) {
        // Ожидаемое исключение
    }
    
    try {
        log(dspirit(-1.0));
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