// Минимальный тест для проверки компиляции
#include <iostream>

// Временно отключим сложную логику
int main() {
    std::cout << "=== paradox-dspirit Build Test ===" << std::endl;
    std::cout << "Platform: ";
    
    #ifdef _WIN32
        std::cout << "Windows" << std::endl;
    #elif __linux__
        std::cout << "Linux" << std::endl;
    #elif __APPLE__
        std::cout << "macOS" << std::endl;
    #else
        std::cout << "Unknown" << std::endl;
    #endif
    
    std::cout << "Compiler: ";
    
    #ifdef _MSC_VER
        std::cout << "MSVC" << std::endl;
    #elif __GNUC__
        std::cout << "GCC" << std::endl;
    #elif __clang__
        std::cout << "Clang" << std::endl;
    #else
        std::cout << "Unknown" << std::endl;
    #endif
    
    std::cout << "✅ Build test passed!" << std::endl;
    return 0;
}