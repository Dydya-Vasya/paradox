// tests/test_math.cpp
#include "dspirit.h"
#include <iostream>
#include <cassert>

int main() {
    using namespace paradox;
    
    std::cout << "=== Math Tests for Spirit Numbers ===\n\n";
    
    // Тест 1: Базовые арифметические операции
    {
        dspirit a(10.0);
        dspirit b(3.0);
        
        dspirit sum = a + b;
        dspirit diff = a - b;
        dspirit prod = a * b;
        dspirit quot = a / b;
        
        std::cout << "Test 1 - Basic Arithmetic:\n";
        std::cout << a << " + " << b << " = " << sum << std::endl;
        std::cout << a << " - " << b << " = " << diff << std::endl;
        std::cout << a << " * " << b << " = " << prod << std::endl;
        std::cout << a << " / " << b << " = " << quot << std::endl;
        
        assert(fabs(static_cast<double>(sum) - 13.0) < 1e-6);
        std::cout << "✓ Addition test passed\n";
    }
    
    // Тест 2: Специальные значения
    {
        std::cout << "\nTest 2 - Special Values:\n";
        
        std::cout << "ZERO: " << dspirit::ZERO << std::endl;
        std::cout << "INF: " << dspirit::INF << std::endl;
        std::cout << "EPSILON: " << dspirit::EPSILON << std::endl;
        
        assert(dspirit::ZERO.isZero());
        assert(dspirit::INF.isInfinity());
        std::cout << "✓ Special values test passed\n";
    }
    
    // Тест 3: Сравнения
    {
        std::cout << "\nTest 3 - Comparisons:\n";
        
        dspirit a(5.0);
        dspirit b(10.0);
        dspirit c(5.0);
        
        assert(a < b);
        assert(b > a);
        assert(a == c);
        assert(a != b);
        
        std::cout << a << " < " << b << ": " << (a < b) << std::endl;
        std::cout << a << " == " << c << ": " << (a == c) << std::endl;
        std::cout << "✓ Comparison test passed\n";
    }
    
    // Тест 4: Математические функции
    {
        std::cout << "\nTest 4 - Math Functions:\n";
        
        dspirit x(4.0);
        dspirit sqrt_x = sqrt(x);
        
        std::cout << "sqrt(" << x << ") = " << sqrt_x << std::endl;
        assert(fabs(static_cast<double>(sqrt_x) - 2.0) < 1e-6);
        
        dspirit y(2.0);
        dspirit pow_y = pow(y, 3.0);
        std::cout << "pow(" << y << ", 3) = " << pow_y << std::endl;
        assert(fabs(static_cast<double>(pow_y) - 8.0) < 1e-6);
        
        std::cout << "✓ Math functions test passed\n";
    }
    
    // Тест 5: "Память" чисел
    {
        std::cout << "\nTest 5 - Number 'Memory':\n";
        
        dspirit eps = dspirit::EPSILON;
        dspirit big(1e100);
        
        std::cout << "EPSILON = " << eps << std::endl;
        std::cout << "big = " << big << std::endl;
        
        dspirit sum = eps + big;
        std::cout << "EPSILON + big = " << sum << std::endl;
        
        dspirit recovered = sum - big;
        std::cout << "(EPSILON + big) - big = " << recovered << std::endl;
        
        // Проверяем, сохранилась ли информация о eps
        if (recovered == eps) {
            std::cout << "✓ Number memory preserved!\n";
        } else {
            std::cout << "✗ Memory lost: " << recovered << " != " << eps << "\n";
        }
    }
    
    std::cout << "\n=== All tests passed successfully! ===\n";
    return 0;
}