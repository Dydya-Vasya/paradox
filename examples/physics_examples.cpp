#include "dspirit.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace paradox;

class ElectricalCircuit {
public:
    // Закон Ома: I = U / R
    static dspirit calculateCurrent(const dspirit& voltage, const dspirit& resistance) {
        std::cout << "Расчет тока по закону Ома:" << std::endl;
        std::cout << "  Напряжение U = " << voltage << " В" << std::endl;
        std::cout << "  Сопротивление R = " << resistance << " Ом" << std::endl;
        
        dspirit current = voltage / resistance;
        
        std::cout << "  Ток I = U / R = " << current << " А" << std::endl;
        std::cout << std::endl;
        
        return current;
    }
    
    // Мощность: P = U² / R = I² * R = U * I
    static dspirit calculatePower(const dspirit& voltage, const dspirit& resistance) {
        dspirit power = (voltage * voltage) / resistance;
        
        std::cout << "Расчет мощности:" << std::endl;
        std::cout << "  P = U² / R = (" << voltage << ")² / " << resistance 
                  << " = " << power << " Вт" << std::endl;
        std::cout << std::endl;
        
        return power;
    }
    
    // Сопротивление при параллельном соединении: 1/R = 1/R1 + 1/R2 + ...
    static dspirit parallelResistance(const std::vector<dspirit>& resistances) {
        dspirit totalInverse = dspirit::ZERO;
        
        std::cout << "Параллельное соединение сопротивлений:" << std::endl;
        for (size_t i = 0; i < resistances.size(); ++i) {
            std::cout << "  R" << (i+1) << " = " << resistances[i] << " Ом" << std::endl;
            if (!resistances[i].isZero()) {
                totalInverse += resistances[i].inverse();
            } else {
                // Если одно из сопротивлений равно нулю, общее сопротивление тоже ноль
                std::cout << "  Обнаружено нулевое сопротивление!" << std::endl;
                return dspirit::ZERO;
            }
        }
        
        dspirit totalResistance = totalInverse.inverse();
        std::cout << "  Общее сопротивление: R = " << totalResistance << " Ом" << std::endl;
        std::cout << std::endl;
        
        return totalResistance;
    }
};

class CapacitorCircuit {
public:
    // Заряд конденсатора: Q = C * U
    static dspirit calculateCharge(const dspirit& capacitance, const dspirit& voltage) {
        dspirit charge = capacitance * voltage;
        
        std::cout << "Расчет заряда конденсатора:" << std::endl;
        std::cout << "  Ёмкость C = " << capacitance << " Ф" << std::endl;
        std::cout << "  Напряжение U = " << voltage << " В" << std::endl;
        std::cout << "  Заряд Q = C * U = " << charge << " Кл" << std::endl;
        std::cout << std::endl;
        
        return charge;
    }
    
    // Ток через конденсатор: I = C * dU/dt
    static dspirit calculateCurrent(const dspirit& capacitance, const dspirit& dU_dt) {
        dspirit current = capacitance * dU_dt;
        
        std::cout << "Ток через конденсатор:" << std::endl;
        std::cout << "  I = C * dU/dt = " << capacitance << " * " << dU_dt 
                  << " = " << current << " А" << std::endl;
        std::cout << std::endl;
        
        return current;
    }
    
    // Энергия конденсатора: W = C * U² / 2
    static dspirit calculateEnergy(const dspirit& capacitance, const dspirit& voltage) {
        dspirit energy = (capacitance * voltage * voltage) / dspirit(2.0);
        
        std::cout << "Энергия конденсатора:" << std::endl;
        std::cout << "  W = C * U² / 2 = " << capacitance << " * (" << voltage 
                  << ")² / 2 = " << energy << " Дж" << std::endl;
        std::cout << std::endl;
        
        return energy;
    }
};

class SuperconductorExperiment {
public:
    static void run() {
        std::cout << "=== ЭКСПЕРИМЕНТ С СВЕРХПРОВОДНИКОМ ===" << std::endl;
        std::cout << "Сверхпроводник имеет нулевое сопротивление!" << std::endl;
        std::cout << std::endl;
        
        dspirit zeroResistance = dspirit::ZERO;  // Сверхпроводник
        dspirit voltage(12.0);  // Напряжение 12 В
        
        std::cout << "Ситуация 1: Обычный источник напряжения" << std::endl;
        dspirit current1 = ElectricalCircuit::calculateCurrent(voltage, zeroResistance);
        
        if (current1.isInfinity()) {
            std::cout << "  ВЫВОД: Ток стремится к бесконечности!" << std::endl;
            std::cout << "  Это демонстрирует, почему сверхпроводники могут проводить" << std::endl;
            std::cout << "  огромные токи без потерь на нагревание." << std::endl;
        }
        std::cout << std::endl;
        
        std::cout << "Ситуация 2: Идеальный источник тока" << std::endl;
        dspirit finiteCurrent(5.0);  // Источник тока 5 А
        // Напряжение на сверхпроводнике должно быть нулевым
        dspirit voltage2 = finiteCurrent * zeroResistance;
        std::cout << "  Если источник обеспечивает конечный ток I = " << finiteCurrent << " А," << std::endl;
        std::cout << "  то напряжение на сверхпроводнике U = I * R = " << finiteCurrent 
                  << " * " << zeroResistance << " = " << voltage2 << " В" << std::endl;
        std::cout << std::endl;
    }
};

class QuantumTunnelingExample {
public:
    static void run() {
        std::cout << "=== КВАНТОВОЕ ТУННЕЛИРОВАНИЕ ===" << std::endl;
        std::cout << "Моделирование вероятности туннелирования через бесконечно высокий барьер" << std::endl;
        std::cout << std::endl;
        
        // Вероятность туннелирования: P ~ exp(-2 * k * L)
        // где k = sqrt(2m(V-E))/ħ
        
        dspirit barrierHeight = dspirit::INF;  // Бесконечно высокий барьер
        dspirit electronEnergy(1.0);  // Энергия электрона 1 эВ
        
        std::cout << "Высота барьера V = " << barrierHeight << std::endl;
        std::cout << "Энергия электрона E = " << electronEnergy << " эВ" << std::endl;
        
        // Для бесконечно высокого барьера (V → ∞) вероятность туннелирования → 0
        dspirit tunnelingProbability = exp(dspirit::NEG_INF);  // exp(-∞) = 0
        
        std::cout << "Вероятность туннелирования P = exp(-∞) = " << tunnelingProbability << std::endl;
        std::cout << "Вывод: Через бесконечно высокий барьер туннелирование невозможно!" << std::endl;
        std::cout << std::endl;
    }
};

class RelativityExample {
public:
    static void run() {
        std::cout << "=== ОТНОСИТЕЛЬНОСТЬ: ДВИЖЕНИЕ СО СВЕТОВОЙ СКОРОСТЬЮ ===" << std::endl;
        std::cout << std::endl;
        
        dspirit c(299792458.0);  // Скорость света, м/с
        dspirit v = c;  // Скорость объекта равна скорости света
        
        std::cout << "Скорость света c = " << c << " м/с" << std::endl;
        std::cout << "Скорость объекта v = " << v << " м/с" << std::endl;
        
        // Релятивистский фактор: γ = 1 / sqrt(1 - v²/c²)
        // При v = c: 1 - v²/c² = 0
        dspirit gamma = dspirit::ONE / sqrt(dspirit::ONE - (v * v) / (c * c));
        
        std::cout << "Релятивистский фактор γ = 1 / sqrt(1 - v²/c²)" << std::endl;
        std::cout << "При v = c: γ = " << gamma << std::endl;
        
        if (gamma.isInfinity()) {
            std::cout << "Вывод: Для объекта, движущегося со скоростью света," << std::endl;
            std::cout << "релятивистский фактор стремится к бесконечности." << std::endl;
            std::cout << "Это означает, что время для такого объекта останавливается," << std::endl;
            std::cout << "а его масса становится бесконечной (с точки зрения неподвижного наблюдателя)." << std::endl;
        }
        std::cout << std::endl;
    }
};

class CalculusExamples {
public:
    static void run() {
        std::cout << "=== МАТЕМАТИЧЕСКИЕ ПРИМЕРЫ ===" << std::endl;
        std::cout << std::endl;
        
        // Предел sin(x)/x при x → 0
        std::cout << "1. Предел sin(x)/x при x → 0:" << std::endl;
        dspirit x1 = dspirit::ZERO;
        dspirit limit1 = sin(x1) / x1;
        std::cout << "   lim(x→0) sin(x)/x = " << limit1 << std::endl;
        std::cout << "   Известный результат: 1" << std::endl;
        std::cout << std::endl;
        
        
        // Интеграл от 0 до ∞: ∫e^(-x) dx
        std::cout << "3. Интеграл от 0 до ∞: ∫e^(-x) dx" << std::endl;
        dspirit integral = -exp(dspirit::NEG_INF) + exp(dspirit::ZERO);
        std::cout << "   ∫[0,∞] e^(-x) dx = [-e^(-x)]₀^∞ = " << integral << std::endl;
        std::cout << "   Известный результат: 1" << std::endl;
        std::cout << std::endl;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "========================================" << std::endl;
    std::cout << "  ФИЗИЧЕСКИЕ ПРИМЕРЫ С БИБЛИОТЕКОЙ dspirit" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    try {
        // Пример 1: Закон Ома с разными сопротивлениями
        std::cout << "ПРИМЕР 1: ЗАКОН ОМА" << std::endl;
        std::cout << "====================" << std::endl;
        
        // Обычный резистор
        ElectricalCircuit::calculateCurrent(dspirit(12.0), dspirit(4.0));
        
        // Сверхпроводник (нулевое сопротивление)
        ElectricalCircuit::calculateCurrent(dspirit(12.0), dspirit::ZERO);
        
        // Бесконечное сопротивление (разрыв цепи)
        ElectricalCircuit::calculateCurrent(dspirit(12.0), dspirit::INF);
        
        // Пример 2: Сверхпроводник
        SuperconductorExperiment::run();
        
        // Пример 3: Квантовое туннелирование
        QuantumTunnelingExample::run();
        
        // Пример 4: Относительность
        RelativityExample::run();
        
        // Пример 5: Математические пределы
        CalculusExamples::run();
        
        // Пример 6: Параллельное соединение
        std::cout << "ПРИМЕР 6: ПАРАЛЛЕЛЬНОЕ СОЕДИНЕНИЕ" << std::endl;
        std::cout << "================================" << std::endl;
        std::vector<dspirit> resistors = {dspirit(100.0), dspirit(200.0), dspirit(300.0)};
        dspirit parallelR = ElectricalCircuit::parallelResistance(resistors);
        std::cout << "При напряжении 24 В ток будет: ";
        dspirit currentParallel = ElectricalCircuit::calculateCurrent(dspirit(24.0), parallelR);
        
        // Пример 7: Конденсаторы
        std::cout << "ПРИМЕР 7: КОНДЕНСАТОРЫ" << std::endl;
        std::cout << "======================" << std::endl;
        
        CapacitorCircuit::calculateCharge(dspirit(0.0001), dspirit(100.0));  // 100 мкФ, 100 В
        CapacitorCircuit::calculateCurrent(dspirit(0.0001), dspirit(1000.0));  // dU/dt = 1000 В/с
        CapacitorCircuit::calculateEnergy(dspirit(0.0001), dspirit(100.0));
        
        // Пример 8: Короткое замыкание
        std::cout << "ПРИМЕР 8: КОРОТКОЕ ЗАМЫКАНИЕ" << std::endl;
        std::cout << "============================" << std::endl;
        
        dspirit shortCircuitResistance = dspirit::EPSILON;  // Очень маленькое сопротивление
        dspirit batteryVoltage(1.5);  // Батарейка 1.5 В
        
        std::cout << "Короткое замыкание батарейки:" << std::endl;
        dspirit shortCircuitCurrent = batteryVoltage / shortCircuitResistance;
        dspirit shortCircuitPower = ElectricalCircuit::calculatePower(batteryVoltage, shortCircuitResistance);
        
        std::cout << "  Ток короткого замыкания: " << shortCircuitCurrent << " А" << std::endl;
        std::cout << "  Мощность: " << shortCircuitPower << " Вт" << std::endl;
        std::cout << "  Вывод: При коротком замыкании ток стремится к бесконечности," << std::endl;
        std::cout << "  что приводит к перегреву и возможному возгоранию." << std::endl;
        std::cout << std::endl;
        
        // Пример 9: Пределы в электротехнике
        std::cout << "ПРИМЕР 9: ПРЕДЕЛЫ В ЭЛЕКТРОТЕХНИКЕ" << std::endl;
        std::cout << "==================================" << std::endl;
        
        dspirit R1(10.0);
        dspirit R2(20.0);
        
        // Последовательное соединение
        std::cout << "Последовательное соединение R1 и R2:" << std::endl;
        std::cout << "  R_посл = R1 + R2 = " << (R1 + R2) << " Ом" << std::endl;
        
        // Параллельное соединение
        std::cout << "Параллельное соединение R1 и R2:" << std::endl;
        dspirit R_par = dspirit::ONE / (R1.inverse() + R2.inverse());
        std::cout << "  R_пар = 1/(1/R1 + 1/R2) = " << R_par << " Ом" << std::endl;
        
        // Что происходит, когда R1 → 0?
        std::cout << "\nИсследование предела при R1 → 0:" << std::endl;
        dspirit R1_small = dspirit::EPSILON;  // Очень маленькое сопротивление
        dspirit R_par_small = dspirit::ONE / (R1_small.inverse() + R2.inverse());
        std::cout << "  Если R1 = " << R1_small << " Ом, то R_пар ≈ " << R_par_small << " Ом" << std::endl;
        std::cout << "  Вывод: При R1 → 0, общее сопротивление также → 0" << std::endl;
        
        std::cout << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "       ВСЕ ПРИМЕРЫ ВЫПОЛНЕНЫ!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка" << std::endl;
        return 1;
    }
}