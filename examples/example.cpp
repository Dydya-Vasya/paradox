#include "spirit_float.h"
#include <iostream>

using namespace paradox;

int main() {
    std::cout << "=== Пример использования библиотеки spirit ===\n" << std::endl;
    
    // Создание чисел
    spirit a = 5.0;
    spirit b = 3.0;
    spirit c = -2.0;
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    
    // Арифметические операции
    std::cout << "\nАрифметика:" << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    
    // Специальные значения
    std::cout << "\nСпециальные значения:" << std::endl;
    std::cout << "Ноль: " << spirit::ZERO << std::endl;
    std::cout << "Бесконечность: " << spirit::INF << std::endl;
    std::cout << "Отрицательная бесконечность: " << spirit::NEG_INF << std::endl;
    std::cout << "Единица: " << spirit::ONE << std::endl;
    
    // Деление на ноль
    std::cout << "\nДеление на ноль:" << std::endl;
    std::cout << "5 / 0 = " << (spirit(5.0) / spirit::ZERO) << std::endl;
    std::cout << "-5 / 0 = " << (spirit(-5.0) / spirit::ZERO) << std::endl;
    
    // Проверки свойств
    std::cout << "\nПроверки свойств:" << std::endl;
    std::cout << "a положительное? " << a.isPositive() << std::endl;
    std::cout << "c отрицательное? " << c.isNegative() << std::endl;
    std::cout << "Ноль есть ноль? " << spirit::ZERO.isZero() << std::endl;
    std::cout << "Бесконечность конечна? " << spirit::INF.isFinite() << std::endl;
    
    // Математические функции
    std::cout << "\nМатематические функции:" << std::endl;
    std::cout << "Абсолютное значение c: " << c.abs() << std::endl;
    std::cout << "Обратное значение a: " << a.inverse() << std::endl;
    std::cout << "Квадратный корень из 16: " << sqrt(spirit(16.0)) << std::endl;
    std::cout << "2 в степени 3: " << pow(spirit(2.0), 3.0) << std::endl;
    
    return 0;
}