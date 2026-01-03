#include <paradox/dspirit.h>
#include <iostream>

int main() {
    using namespace paradox;
    
    std::cout << "=== Testing paradox-dspirit ===" << std::endl;
    
    dspirit a = 10.0;
    dspirit b = 20.0;
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    
    // Тест бесконечности
    dspirit inf = dspirit::INF;
    std::cout << "inf = " << inf << std::endl;
    std::cout << "inf + 100 = " << (inf + 100) << std::endl;
    
    return 0;
}