#include "paradox/dspirit.h"

#ifdef _WIN32
#define PARADOX_DSPIRIT_EXPORTS
#endif

#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cstring>  // Добавили для strlen/memcpy

namespace paradox {

// Внутренняя реализация
class dspirit::Impl {
private:
    double r_;      // Старший уровень
    double i_;      // Младший уровень
    double j_;      // Самый младший уровень
    double level_;  // Уровень старшего числа
    
    static const double epsilon;
    static const double DOUBLE_POS_INF;
    static const double DOUBLE_NEG_INF;

    static const double NEAR_ZERO;
    
    // Вспомогательные методы
    bool isNegligibleRelative(double small, double large) const;
    

public:
    Impl(double value = 0.0, double level = 0.0) {
        init(value, level);
    }
    
    Impl(double r, double i, double j, double level) 
        : r_(r), i_(i), j_(j), level_(level) {
        normalize();
    }
    
    // Копирование
    Impl(const Impl& other) = default;
    
    // Методы доступа
    double r() const { return r_; }
    double i() const { return i_; }
    double j() const { return j_; }
    double level() const { return level_; }

    // Вспомогательные методы
    bool isApproxZero(double value) const {
        return std::abs(value) < NEAR_ZERO;
    }
    
    bool isApproxEqual(double a, double b) const {
        return  std::abs(a - b) < epsilon;
    }
    
    bool isApproxEqualLevel(double a, double b) const {
        return std::abs(a - b) < epsilon * 0.1;
    }
    
    void init(double value, double level = 0.0) {
        if (isApproxZero(value)) {
            // Для нуля используем еденицу в первом отрицательном слое
            r_ = 1.0;  // Используем 0.0 вместо 1.0 для нуля
            i_ = 0.0;
            j_ = 0.0;
            level_ = level - 1.0;
        } else {
            r_ = value;
            i_ = 0.0;
            j_ = 0.0;
            level_ = level;
        }
    }
    
    void normalize() {
        if (isApproxZero(r_)) {
            if (!isApproxZero(i_)) {
                r_ = i_;
                i_ = j_;
                j_ = 0.0;
                level_ -= 1.0;
            } else if (!isApproxZero(j_)) {
                r_ = j_;
                i_ = 0.0;
                j_ = 0.0;
                level_ -= 2.0;
            } else {
                // Все нули
                r_ = 1.0;  // Устанавливаем r_ в 1 для нуля
                i_ = 0.0;
                j_ = 0.0;
                level_ = DOUBLE_NEG_INF;  // суперноль
            }
            return;
        }
        resetLowerLevels();
    }
    
    void resetLowerLevels() {
        if (isApproxZero(i_)) i_ = 0.0;
        if (isApproxZero(j_)) j_ = 0.0;
    }
    
    double atLevel(double target_level) const {
        const double diff = level_ - target_level;
        
        if (std::abs(diff) < epsilon) return r_;
        if (std::abs(diff - 1.0) < epsilon) return i_;
        if (std::abs(diff - 2.0) < epsilon) return j_;
        
        return 0.0;
    }
    
    // Проверки свойств (математически корректные)
    bool isZero() const { return level_ < (-epsilon); }
    bool isInfinity() const { return level_ > epsilon; }
    bool isRegular() const { return std::abs(level_) < epsilon; }
    
    // Математически корректные проверки знака
    bool isNegative() const { return !isZero() && r_ < 0.0; }
    bool isPositive() const { return !isZero() && r_ > 0.0; }
    bool isNonNegative() const { return isZero() || isPositive(); }
    bool isNonPositive() const { return isZero() || isNegative(); }
    
    // Арифметические операции
    Impl negate() const {
        Impl result;
        result.r_ = -r_;
        result.i_ = -i_;
        result.j_ = -j_;
        result.level_ = level_;
        return result;
    }
    
    Impl add(const Impl& other) const {
        
        // Быстрый путь для одинаковых уровней
        if (isApproxEqualLevel(level_, other.level_)) {
            Impl result;
            result.r_ = r_ + other.r_;
            if(result.r_ == DOUBLE_POS_INF) return {1.0, level_ + 1};
            if(result.r_ == DOUBLE_NEG_INF) return {-1.0, level_ + 1};
            result.i_ = i_ + other.i_;
            if(result.i_ == DOUBLE_POS_INF) return {result.r_, 1.0, 0.0, level_};
            if(result.i_ == DOUBLE_NEG_INF) return {result.r_, -1.0, 0.0, level_};
            result.j_ = j_ + other.j_;
            if(result.j_ == DOUBLE_POS_INF) return {result.r_, result.i_, 1.0, level_};
            if(result.j_ == DOUBLE_NEG_INF) return {result.r_, result.i_, -1.0, level_};
            result.level_ = level_;
            result.normalize();
            return result;
        }
        
        // Находим максимальный уровень
        const double max_level = (level_ > other.level_) ? level_ : other.level_;
        const double min_level = (level_ < other.level_) ? level_ : other.level_;
        
        // Если разница в уровнях больше 2, то меньшими уровнями можно пренебречь
        if (max_level - min_level > 2.5f) {
            return (level_ > other.level_) ? *this : other;
        }
        
        // Суммируем значения на каждом уровне
        const double sum_r = atLevel(max_level) + other.atLevel(max_level);
        if(sum_r == DOUBLE_POS_INF) return {1.0, max_level + 1};
        if(sum_r == DOUBLE_NEG_INF) return {-1.0, max_level + 1};
        const double sum_i = atLevel(max_level - 1.0) + other.atLevel(max_level - 1.0);
        if(sum_i == DOUBLE_POS_INF) return {sum_r, 1.0, 0.0, max_level};
        if(sum_i == DOUBLE_NEG_INF) return {sum_r, -1.0, 0.0, max_level};
        const double sum_j = atLevel(max_level - 2.0) + other.atLevel(max_level - 2.0);
        if(sum_j == DOUBLE_POS_INF) return {sum_r, sum_i, 1.0, max_level};
        if(sum_j == DOUBLE_NEG_INF) return {sum_r, sum_i, -1.0, max_level};
        Impl result(sum_r, sum_i, sum_j, max_level);
        result.normalize();
        return result;
    }
    
    Impl subtract(const Impl& other) const {
        return add(other.negate());
    }
    
    Impl multiply(const Impl& other) const {
        if(other.level_ == DOUBLE_NEG_INF){
            if(level_ == DOUBLE_POS_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_NEG_INF};
        }

        if(other.level_ == DOUBLE_POS_INF){
            if(level_ == DOUBLE_NEG_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_POS_INF};
        }

        if(level_ == DOUBLE_NEG_INF){
            if(other.level_ == DOUBLE_POS_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_NEG_INF};
        }

        if(level_ == DOUBLE_POS_INF){
            if(other.level_ == DOUBLE_NEG_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_POS_INF};
        }
        // Умножение: уровни складываются
        const double result_level = level_ + other.level_;
    
        const double result_r = r_ * other.r_;
        // если переполнение то увеличиваем уровень и отправляем еденицу
        if(result_r == DOUBLE_POS_INF) return {1.0, result_level + 1};
        if(result_r == DOUBLE_NEG_INF) return {-1.0, result_level + 1};

        const double result_i = r_ * other.i_ + i_ * other.r_;
        if(result_i == DOUBLE_POS_INF) return {result_r, 1.0, 0.0, result_level};
        if(result_i == DOUBLE_NEG_INF) return {result_r, -1.0, 0.0, result_level};
        
        const double result_j = r_ * other.j_ + i_ * other.i_ + j_ * other.r_;
        if(result_i == DOUBLE_POS_INF) return {result_r, result_i, 1.0, result_level};
        if(result_i == DOUBLE_NEG_INF) return {result_r, result_i, -1.0, result_level};
        
        Impl result(result_r, result_i, result_j, result_level);
        result.normalize();
        return result;
    }
    
    Impl divide(const Impl& divisor) const {
        if(divisor.level_ == DOUBLE_NEG_INF){
            if(level_ == DOUBLE_NEG_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_POS_INF};
        }

        if(divisor.level_ == DOUBLE_POS_INF){
            if(level_ == DOUBLE_POS_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_NEG_INF};
        }

        if(level_ == DOUBLE_NEG_INF){
            if(divisor.level_ == DOUBLE_NEG_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_NEG_INF};
        }

        if(level_ == DOUBLE_POS_INF){
            if(divisor.level_ == DOUBLE_POS_INF) return {1.0, 0.0};
            return {1.0, DOUBLE_POS_INF};
        }

        const double result_level = level_ - divisor.level_;
        
        const double result_r = r_ / divisor.r_;
        if(result_r == DOUBLE_POS_INF) return {1.0, result_level + 1};
        if(result_r == DOUBLE_NEG_INF) return {-1.0, result_level + 1};
       
        const double result_i = (i_ - result_r * divisor.i_) /  divisor.r_;
        if(result_i == DOUBLE_POS_INF) return {result_r, 1.0, 0.0, result_level};
        if(result_i == DOUBLE_NEG_INF) return {result_r, -1.0, 0.0, result_level};
       
        const double result_j = ((j_ - result_r * divisor.j_) - result_i * divisor.i_) / divisor.r_;
        if(result_j == DOUBLE_POS_INF) return {result_r, result_i, 1.0, result_level};
        if(result_j == DOUBLE_NEG_INF) return {result_r, result_i, -1.0, result_level};
        
        Impl result(result_r, result_i, result_j, result_level);
        result.normalize();
        return result;
    }
    
    // Сравнения (математически корректные)
    bool equals(const Impl& other) const {
        // Все нули равны
        if (isZero() && other.isZero()) return true;
        
        // Разные уровни (кроме нулей)
        if (!isApproxEqualLevel(level_, other.level_)) return false;
        
        // Одинаковые уровни, сравниваем старшие значения
        return isApproxEqual(r_, other.r_);
    }
    
    bool lessThan(const Impl& other) const {
        // Оба нуля
        if (isZero() && other.isZero()) return false;
        
        // Текущее - ноль, другое - нет
        if (isZero()) return other.isPositive();
        
        // Другое - ноль, текущее - нет
        if (other.isZero()) return isNegative();
        
        // Оба не нули
        // Сравнение уровней
        if (!isApproxEqualLevel(level_, other.level_)) {
            if (isPositive() && other.isPositive()) {
                return level_ < other.level_;
            }
            if (isNegative() && other.isNegative()) {
                return level_ > other.level_;
            }
            return isNegative() && other.isPositive();
        }
        
        // Одинаковые уровни, сравниваем значения
        if (!isApproxEqual(r_, other.r_)) {
            return r_ < other.r_;
        }
        if (!isApproxEqual(i_, other.i_)) {
            return i_ < other.i_;
        }
        return j_ < other.j_;
    }
    
    // Преобразования
    double toDouble() const {
        if (isZero()) return 0.0;
        if (isInfinity()) {
            return (r_ > 0.0) ? std::numeric_limits<double>::infinity()
                               : -std::numeric_limits<double>::infinity();
        }
        return static_cast<double>(r_);
    }
    
    float toFloat() const {
        if (isZero()) return 0.0;
        if (isInfinity()) {
            return (r_ > 0.0) ? std::numeric_limits<float>::infinity()
                               : -std::numeric_limits<float>::infinity();
        }
        return static_cast<float>(r_);
    }
    
    // Создание из строки
    static Impl fromStringSimple(const std::string& s) {
        std::string str = s;
        
        str.erase(std::remove_if(str.begin(), str.end(), 
                  [](unsigned char c) { return std::isspace(c); }), 
                  str.end());
        
        if (str.empty()) return Impl(0.0);
        
        if (str == "0" || str == "0.0") return Impl(0.0);
        if (str == "inf" || str == "Inf" || str == "INF") return Impl(1.0, 1.0);
        if (str == "-inf" || str == "-Inf" || str == "-INF") return Impl(-1.0, 1.0);
        if (str == "1" || str == "1.0") return Impl(1.0);
        if (str == "-1" || str == "-1.0") return Impl(-1.0);
        
        try {
            double value = std::stod(str);
            return Impl(value, 0.0);
        } catch (...) {
            throw std::invalid_argument("Cannot parse: " + s);
        }
    }
};

 dspirit dspirit::fromLevel(double value, double level) {
        return dspirit(new Impl(value, level));
    }


// Инициализация статической константы
const double dspirit::Impl::epsilon = std::numeric_limits<double>::epsilon() * 10;
const double dspirit::Impl::DOUBLE_POS_INF = std::numeric_limits<double>::infinity();
const double dspirit::Impl::DOUBLE_NEG_INF = -dspirit::Impl::DOUBLE_POS_INF;

const double dspirit::Impl::NEAR_ZERO = std::numeric_limits<double>::min() * 100.0;

// Конструкторы dspirit
dspirit::dspirit(double value) noexcept : pimpl(new Impl(value)) {}
dspirit::dspirit(float value) noexcept : pimpl(new Impl(static_cast<double>(value))) {}
dspirit::dspirit(int value) noexcept : pimpl(new Impl(static_cast<double>(value))) {}

// Скрытый конструктор
dspirit::dspirit(Impl* impl) : pimpl(impl) {}

// Деструктор, копирование, перемещение
dspirit::~dspirit() { delete pimpl; }

dspirit::dspirit(const dspirit& other) : pimpl(new Impl(*other.pimpl)) {}
dspirit::dspirit(dspirit&& other) noexcept : pimpl(other.pimpl) { other.pimpl = nullptr; }

dspirit& dspirit::operator=(const dspirit& other) {
    if (this != &other) {
        delete pimpl;
        pimpl = new Impl(*other.pimpl);
    }
    return *this;
}

dspirit& dspirit::operator=(dspirit&& other) noexcept {
    if (this != &other) {
        delete pimpl;
        pimpl = other.pimpl;
        other.pimpl = nullptr;
    }
    return *this;
}

double dspirit::debugR() const { return pimpl->r(); }
double dspirit::debugI() const { return pimpl->i(); }
double dspirit::debugJ() const { return pimpl->j(); }
double dspirit::debugLevel() const { return pimpl->level(); }
 

double dspirit::toDouble() const {
    return static_cast<double>(*this);
}

float dspirit::toFloat() const {
    return static_cast<float>(*this);
}

std::string dspirit::debugString() const {
    std::ostringstream oss;
    
    if (isZero()) {
        oss << "ZERO(r=" << debugR() << ", i=" << debugI() 
            << ", j=" << debugJ() << ", level=" << debugLevel() << ")";
    } else if (isInfinity()) {
        oss << (isNegative() ? "-INF" : "INF") 
            << "(r=" << debugR() << ", level=" << debugLevel() << ")";
    } else {
        oss << "NUM(value=" << static_cast<double>(*this) 
            << ", r=" << debugR() << ", i=" << debugI() 
            << ", j=" << debugJ() << ", level=" << debugLevel() << ")";
    }
    
    return oss.str();
}

// Арифметические операторы
dspirit dspirit::operator-() const { return dspirit(new Impl(pimpl->negate())); }

dspirit dspirit::operator+(const dspirit& other) const {
    return dspirit(new Impl(pimpl->add(*other.pimpl)));
}

dspirit dspirit::operator-(const dspirit& other) const {
    return dspirit(new Impl(pimpl->subtract(*other.pimpl)));
}

dspirit dspirit::operator*(const dspirit& other) const {
    return dspirit(new Impl(pimpl->multiply(*other.pimpl)));
}

dspirit dspirit::operator/(const dspirit& divisor) const {
    return dspirit(new Impl(pimpl->divide(*divisor.pimpl)));
}

// Составные операторы
dspirit& dspirit::operator+=(const dspirit& other) { *this = *this + other; return *this; }
dspirit& dspirit::operator-=(const dspirit& other) { *this = *this - other; return *this; }
dspirit& dspirit::operator*=(const dspirit& other) { *this = *this * other; return *this; }
dspirit& dspirit::operator/=(const dspirit& divisor) { *this = *this / divisor; return *this; }

// Операторы с обычными числами
dspirit dspirit::operator+(double val) const { return *this + dspirit(val); }
dspirit dspirit::operator-(double val) const { return *this - dspirit(val); }
dspirit dspirit::operator*(double val) const { return *this * dspirit(val); }
dspirit dspirit::operator/(double val) const { return *this / dspirit(val); }

dspirit dspirit::operator+(float val) const { return *this + dspirit(val); }
dspirit dspirit::operator-(float val) const { return *this - dspirit(val); }
dspirit dspirit::operator*(float val) const { return *this * dspirit(val); }
dspirit dspirit::operator/(float val) const { return *this / dspirit(val); }

dspirit dspirit::operator+(int val) const { return *this + dspirit(val); }
dspirit dspirit::operator-(int val) const { return *this - dspirit(val); }
dspirit dspirit::operator*(int val) const { return *this * dspirit(val); }
dspirit dspirit::operator/(int val) const { return *this / dspirit(val); }

// Операторы сравнения
bool dspirit::operator==(const dspirit& other) const {
    return pimpl->equals(*other.pimpl);
}

bool dspirit::operator!=(const dspirit& other) const {
    return !(*this == other);
}

bool dspirit::operator<(const dspirit& other) const {
    return pimpl->lessThan(*other.pimpl);
}

bool dspirit::operator>(const dspirit& other) const {
    return other < *this;
}

bool dspirit::operator<=(const dspirit& other) const {
    return !(*this > other);
}

bool dspirit::operator>=(const dspirit& other) const {
    return !(*this < other);
}

// Математические методы
dspirit dspirit::abs() const {
    if (isNegative()) {
        return -*this;
    }
    return *this;
}

dspirit dspirit::inverse() const {
    if (isZero()) return dspirit::INF;
    return dspirit::ONE / *this;
}

// Проверки свойств (математически корректные)
bool dspirit::isZero() const { return pimpl->isZero(); }
bool dspirit::isInfinity() const { return pimpl->isInfinity(); }
bool dspirit::isFinite() const { return !pimpl->isZero() && !pimpl->isInfinity(); }
bool dspirit::isNegative() const { return pimpl->isNegative(); }
bool dspirit::isPositive() const { return pimpl->isPositive(); }
bool dspirit::isNonNegative() const { return pimpl->isNonNegative(); }
bool dspirit::isNonPositive() const { return pimpl->isNonPositive(); }

// Преобразования
dspirit::operator double() const { return pimpl->toDouble(); }
dspirit::operator float() const { return pimpl->toFloat(); }

std::string dspirit::toString() const {
    std::ostringstream oss;
    oss.precision(10);
    
    if (isZero()) {
        oss << "0";
    } else if (isInfinity()) {
        if (isNegative()) {
            oss << "-inf";
        } else {
            oss << "inf";
        }
    } else {
        oss << static_cast<double>(*this);
    }
    
    return oss.str();
}

// Статические методы
dspirit dspirit::fromString(const std::string& s) {
    return dspirit(new Impl(Impl::fromStringSimple(s)));
}

dspirit dspirit::parse(const std::string& s) {
    return fromString(s);
}

// Статические константы
const dspirit dspirit::ZERO(0.0);
const dspirit dspirit::INF(new Impl(1.0, 1.0));
const dspirit dspirit::NEG_INF(new Impl(-1.0, 1.0));
const dspirit dspirit::ONE(1.0);
const dspirit dspirit::NEG_ONE(-1.0);
const dspirit dspirit::EPSILON(new Impl(1.0, -1.0));
const dspirit dspirit::SUPER_ZERO(new Impl(1.0, DOUBLE_NEG_INF));
const dspirit dspirit::SUPER_INF(new Impl(1.0, DOUBLE_POS_INF));


// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& os, const dspirit& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, dspirit& num) {
    std::string s;
    is >> s;
    num = dspirit::fromString(s);
    return is;
}

// Операторы с числами слева
dspirit operator+(double lhs, const dspirit& rhs) { return dspirit(lhs) + rhs; }
dspirit operator-(double lhs, const dspirit& rhs) { return dspirit(lhs) - rhs; }
dspirit operator*(double lhs, const dspirit& rhs) { return dspirit(lhs) * rhs; }
dspirit operator/(double lhs, const dspirit& rhs) { return dspirit(lhs) / rhs; }

dspirit operator+(float lhs, const dspirit& rhs) { return dspirit(lhs) + rhs; }
dspirit operator-(float lhs, const dspirit& rhs) { return dspirit(lhs) - rhs; }
dspirit operator*(float lhs, const dspirit& rhs) { return dspirit(lhs) * rhs; }
dspirit operator/(float lhs, const dspirit& rhs) { return dspirit(lhs) / rhs; }

dspirit operator+(int lhs, const dspirit& rhs) { return dspirit(lhs) + rhs; }
dspirit operator-(int lhs, const dspirit& rhs) { return dspirit(lhs) - rhs; }
dspirit operator*(int lhs, const dspirit& rhs) { return dspirit(lhs) * rhs; }
dspirit operator/(int lhs, const dspirit& rhs) { return dspirit(lhs) / rhs; }

// Математические функции
dspirit sqrt(const dspirit& x) {
    if (x.isZero()) return dspirit::ZERO;
    if (x.isInfinity()) return dspirit::INF;
    if (x.isNegative()) {
        throw std::domain_error("sqrt of negative number");
    }
    return dspirit(std::sqrt(static_cast<double>(x)));
}

dspirit pow(const dspirit& x, double exponent) {
    if (x.isZero()) {
        if (exponent > 0) return dspirit::ZERO;
        if (exponent < 0) return dspirit::INF;
        return dspirit::ONE;  // 0^0 = 1 (по соглашению)
    }
    
    if (x.isInfinity()) {
        if (exponent > 0) return dspirit::INF;
        if (exponent < 0) return dspirit::ZERO;
        return dspirit::ONE;
    }
    
    return dspirit(std::pow(static_cast<double>(x), exponent));
}

dspirit exp(const dspirit& x) {
    if (x.isZero()) return dspirit::ONE;
    if (x.isInfinity()) {
        if (x.isPositive()) return dspirit::INF;
        else return dspirit::ZERO;
    }
    return dspirit(std::exp(static_cast<double>(x)));
}

dspirit log(const dspirit& x) {
    if (x.isZero()) return dspirit::NEG_INF;
    if (x.isInfinity()) return dspirit::INF;
    if (x.isNegative()) {
        throw std::domain_error("log of negative number");
    }
    return dspirit(std::log(static_cast<double>(x)));
}

dspirit sin(const dspirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("sin of infinity");
    }
    return dspirit(std::sin(static_cast<double>(x)));
}

dspirit cos(const dspirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("cos of infinity");
    }
    return dspirit(std::cos(static_cast<double>(x)));
}

dspirit tan(const dspirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("tan of infinity");
    }
    return dspirit(std::tan(static_cast<double>(x)));
}

} // namespace paradox