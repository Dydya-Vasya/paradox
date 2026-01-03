#include "spirit_float.h"
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace paradox {

// Внутренняя реализация
class spirit::Impl {
private:
    float r_;      // Старший уровень
    float i_;      // Младший уровень
    float j_;      // Самый младший уровень
    float level_;  // Уровень старшего числа
    
    static const float epsilon;
    static const float POS_INF;
    static const float NEG_INF;

    static constexpr float RELATIVE_THRESHOLD = static_cast<float>(1e-6);
    static const float NEAR_ZERO;
    
    // Вспомогательные методы
    bool isNegligibleRelative(float small, float large) const;
    

public:
    Impl(float value = 0.0f, float level = 0.0f) {
        init(value, level);
    }
    
    Impl(float r, float i, float j, float level) 
        : r_(r), i_(i), j_(j), level_(level) {
        normalize();
    }
    
    // Копирование
    Impl(const Impl& other) = default;
    
    // Методы доступа
    float r() const { return r_; }
    float i() const { return i_; }
    float j() const { return j_; }
    float level() const { return level_; }
    
    // Вспомогательные методы
    bool isApproxZero(float value) const {
        return std::abs(value) < NEAR_ZERO;
    }
    
    bool isApproxEqual(float a, float b) const {
        return  std::abs(a - b) < epsilon;
    }
    
    bool isApproxEqualLevel(float a, float b) const {
        return std::abs(a - b) < epsilon * 0.1f;
    }
    
    void init(float value, float level = 0.0f) {
        if (isApproxZero(value)) {
            // Для нуля используем еденицу в первом отрицательном слое
            r_ = 1.0f;  // Используем 0.0f вместо 1.0f для нуля
            i_ = 0.0f;
            j_ = 0.0f;
            level_ = level - 1.0f;
        } else {
            r_ = value;
            i_ = 0.0f;
            j_ = 0.0f;
            level_ = level;
        }
    }
    
    void normalize() {
        if (isApproxZero(r_)) {
            if (!isApproxZero(i_)) {
                r_ = i_;
                i_ = j_;
                j_ = 0.0f;
                level_ -= 1.0f;
            } else if (!isApproxZero(j_)) {
                r_ = j_;
                i_ = 0.0f;
                j_ = 0.0f;
                level_ -= 2.0f;
            } else {
                // Все нули
                r_ = 1.0f;  // Устанавливаем r_ в 1 для нуля
                i_ = 0.0f;
                j_ = 0.0f;
                level_ -= 1.0f;  // Уровень на 1 ниже текущего
            }
            return;
        }
        resetLowerLevels();
    }
    
    void resetLowerLevels() {
        if (isApproxZero(i_)) i_ = 0.0f;
        if (isApproxZero(j_)) j_ = 0.0f;
    }
    
    float atLevel(float target_level) const {
        const float diff = level_ - target_level;
        
        if (std::abs(diff) < epsilon) return r_;
        if (std::abs(diff - 1.0f) < epsilon) return i_;
        if (std::abs(diff - 2.0f) < epsilon) return j_;
        
        return 0.0f;
    }
    
    // Проверки свойств (математически корректные)
    bool isZero() const { return level_ < (-epsilon); }
    bool isInfinity() const { return level_ > epsilon; }
    bool isRegular() const { return std::abs(level_) < epsilon; }
    
    // Математически корректные проверки знака
    bool isNegative() const { return !isZero() && r_ < 0.0f; }
    bool isPositive() const { return !isZero() && r_ > 0.0f; }
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
            if(result.r_ == POS_INF) return {1.0, level_ + 1};
            if(result.r_ == NEG_INF) return {-1.0, level_ + 1};
            result.i_ = i_ + other.i_;
            if(result.i_ == POS_INF) return {result.r_, 1.0f, 0.0f, level_};
            if(result.i_ == NEG_INF) return {result.r_, -1.0f, 0.0f, level_};
            result.j_ = j_ + other.j_;
            if(result.j_ == POS_INF) return {result.r_, result.i_, 1.0f, level_};
            if(result.j_ == NEG_INF) return {result.r_, result.i_, -1.0f, level_};
            result.level_ = level_;
            result.normalize();
            return result;
        }
        
        // Находим максимальный уровень
        const float max_level = (level_ > other.level_) ? level_ : other.level_;
        const float min_level = (level_ < other.level_) ? level_ : other.level_;
        
        // Если разница в уровнях больше 2, то меньшими уровнями можно пренебречь
        if (max_level - min_level > 2.5f) {
            return (level_ > other.level_) ? *this : other;
        }
        
        // Суммируем значения на каждом уровне
        const float sum_r = atLevel(max_level) + other.atLevel(max_level);
        if(sum_r == POS_INF) return {1.0, max_level + 1};
        if(sum_r == NEG_INF) return {-1.0, max_level + 1};
        const float sum_i = atLevel(max_level - 1.0f) + other.atLevel(max_level - 1.0f);
        if(sum_i == POS_INF) return {sum_r, 1.0f, 0.0f, max_level};
        if(sum_i == NEG_INF) return {sum_r, -1.0f, 0.0f, max_level};
        const float sum_j = atLevel(max_level - 2.0f) + other.atLevel(max_level - 2.0f);
        if(sum_j == POS_INF) return {sum_r, sum_i, 1.0f, max_level};
        if(sum_j == NEG_INF) return {sum_r, sum_i, -1.0f, max_level};
        Impl result(sum_r, sum_i, sum_j, max_level);
        result.normalize();
        return result;
    }
    
    Impl subtract(const Impl& other) const {
        return add(other.negate());
    }
    
    Impl multiply(const Impl& other) const {
        // Умножение: уровни складываются
        const float result_level = level_ + other.level_;
    
        const float result_r = r_ * other.r_;
        // если переполнение то увеличиваем уровень и отправляем еденицу
        if(result_r == POS_INF) return {1.0, result_level + 1};
        if(result_r == NEG_INF) return {-1.0, result_level + 1};

        const float result_i = r_ * other.i_ + i_ * other.r_;
        if(result_i == POS_INF) return {result_r, 1.0f, 0.0f, result_level};
        if(result_i == NEG_INF) return {result_r, -1.0f, 0.0f, result_level};
        
        const float result_j = r_ * other.j_ + i_ * other.i_ + j_ * other.r_;
        if(result_j == POS_INF) return {result_r, result_i, 1.0f, result_level};
        if(result_j == NEG_INF) return {result_r, result_i, -1.0f, result_level};
        
        Impl result(result_r, result_i, result_j, result_level);
        result.normalize();
        return result;
    }
    
    Impl divide(const Impl& divisor) const {
        const float result_level = level_ - divisor.level_;
              
        const float result_r = r_ / divisor.r_;
        if(result_r == POS_INF) return {1.0, result_level + 1};
        if(result_r == NEG_INF) return {-1.0, result_level + 1};
       
        const float result_i = (i_ - result_r * divisor.i_) /  divisor.r_;
        if(result_i == POS_INF) return {result_r, 1.0f, 0.0f, result_level};
        if(result_i == NEG_INF) return {result_r, -1.0f, 0.0f, result_level};
       
        const float result_j = ((j_ - result_r * divisor.j_) - result_i * divisor.i_) / divisor.r_;
        if(result_j == POS_INF) return {result_r, result_i, 1.0f, result_level};
        if(result_j == NEG_INF) return {result_r, result_i, -1.0f, result_level};
        
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
            return (r_ > 0.0f) ? std::numeric_limits<double>::infinity()
                               : -std::numeric_limits<double>::infinity();
        }
        return static_cast<double>(r_);
    }
    
    float toFloat() const {
        if (isZero()) return 0.0f;
        if (isInfinity()) {
            return (r_ > 0.0f) ? std::numeric_limits<float>::infinity()
                               : -std::numeric_limits<float>::infinity();
        }
        return r_;
    }
    
    // Создание из строки
    static Impl fromStringSimple(const std::string& s) {
        std::string str = s;
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
        
        if (str.empty()) return Impl(0.0f);
        
        // Проверяем специальные значения
        if (str == "0" || str == "0.0" || str == "0.0f") return Impl(0.0f);
        if (str == "inf" || str == "Inf" || str == "INF") return Impl(1.0f, 1.0f);
        if (str == "-inf" || str == "-Inf" || str == "-INF") return Impl(-1.0f, 1.0f);
        if (str == "1" || str == "1.0" || str == "1.0f") return Impl(1.0f);
        if (str == "-1" || str == "-1.0" || str == "-1.0f") return Impl(-1.0f);
        
        // Просто число
        try {
            float value = std::stof(str);
            return Impl(value, 0.0f);
        } catch (...) {
            throw std::invalid_argument("Cannot parse: " + s);
        }
    }
};

// Инициализация статической константы
const float spirit::Impl::epsilon = std::numeric_limits<float>::epsilon() * 10;
const float spirit::Impl::POS_INF = std::numeric_limits<float>::infinity();
const float spirit::Impl::NEG_INF = -spirit::Impl::POS_INF;

const float spirit::Impl::NEAR_ZERO = std::numeric_limits<float>::min() * 100.0f;

// Конструкторы spirit
spirit::spirit(float value) noexcept : pimpl(new Impl(value)) {}
spirit::spirit(double value) noexcept : pimpl(new Impl(static_cast<float>(value))) {}
spirit::spirit(int value) noexcept : pimpl(new Impl(static_cast<float>(value))) {}

// Скрытый конструктор
spirit::spirit(Impl* impl) : pimpl(impl) {}

// Деструктор, копирование, перемещение
spirit::~spirit() { delete pimpl; }

spirit::spirit(const spirit& other) : pimpl(new Impl(*other.pimpl)) {}
spirit::spirit(spirit&& other) noexcept : pimpl(other.pimpl) { other.pimpl = nullptr; }

spirit& spirit::operator=(const spirit& other) {
    if (this != &other) {
        delete pimpl;
        pimpl = new Impl(*other.pimpl);
    }
    return *this;
}

spirit& spirit::operator=(spirit&& other) noexcept {
    if (this != &other) {
        delete pimpl;
        pimpl = other.pimpl;
        other.pimpl = nullptr;
    }
    return *this;
}

// Арифметические операторы
spirit spirit::operator-() const { return spirit(new Impl(pimpl->negate())); }

spirit spirit::operator+(const spirit& other) const {
    return spirit(new Impl(pimpl->add(*other.pimpl)));
}

spirit spirit::operator-(const spirit& other) const {
    return spirit(new Impl(pimpl->subtract(*other.pimpl)));
}

spirit spirit::operator*(const spirit& other) const {
    return spirit(new Impl(pimpl->multiply(*other.pimpl)));
}

spirit spirit::operator/(const spirit& divisor) const {
    return spirit(new Impl(pimpl->divide(*divisor.pimpl)));
}

// Составные операторы
spirit& spirit::operator+=(const spirit& other) { *this = *this + other; return *this; }
spirit& spirit::operator-=(const spirit& other) { *this = *this - other; return *this; }
spirit& spirit::operator*=(const spirit& other) { *this = *this * other; return *this; }
spirit& spirit::operator/=(const spirit& divisor) { *this = *this / divisor; return *this; }

// Операторы с обычными числами
spirit spirit::operator+(float val) const { return *this + spirit(val); }
spirit spirit::operator-(float val) const { return *this - spirit(val); }
spirit spirit::operator*(float val) const { return *this * spirit(val); }
spirit spirit::operator/(float val) const { return *this / spirit(val); }

spirit spirit::operator+(double val) const { return *this + spirit(val); }
spirit spirit::operator-(double val) const { return *this - spirit(val); }
spirit spirit::operator*(double val) const { return *this * spirit(val); }
spirit spirit::operator/(double val) const { return *this / spirit(val); }

spirit spirit::operator+(int val) const { return *this + spirit(val); }
spirit spirit::operator-(int val) const { return *this - spirit(val); }
spirit spirit::operator*(int val) const { return *this * spirit(val); }
spirit spirit::operator/(int val) const { return *this / spirit(val); }

// Операторы сравнения
bool spirit::operator==(const spirit& other) const {
    return pimpl->equals(*other.pimpl);
}

bool spirit::operator!=(const spirit& other) const {
    return !(*this == other);
}

bool spirit::operator<(const spirit& other) const {
    return pimpl->lessThan(*other.pimpl);
}

bool spirit::operator>(const spirit& other) const {
    return other < *this;
}

bool spirit::operator<=(const spirit& other) const {
    return !(*this > other);
}

bool spirit::operator>=(const spirit& other) const {
    return !(*this < other);
}

// Математические методы
spirit spirit::abs() const {
    if (isNegative()) {
        return -*this;
    }
    return *this;
}

spirit spirit::inverse() const {
    if (isZero()) return spirit::INF;
    return spirit::ONE / *this;
}

// Проверки свойств (математически корректные)
bool spirit::isZero() const { return pimpl->isZero(); }
bool spirit::isInfinity() const { return pimpl->isInfinity(); }
bool spirit::isFinite() const { return !pimpl->isZero() && !pimpl->isInfinity(); }
bool spirit::isNegative() const { return pimpl->isNegative(); }
bool spirit::isPositive() const { return pimpl->isPositive(); }
bool spirit::isNonNegative() const { return pimpl->isNonNegative(); }
bool spirit::isNonPositive() const { return pimpl->isNonPositive(); }

// Преобразования
spirit::operator double() const { return pimpl->toDouble(); }
spirit::operator float() const { return pimpl->toFloat(); }

std::string spirit::toString() const {
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
spirit spirit::fromString(const std::string& s) {
    return spirit(new Impl(Impl::fromStringSimple(s)));
}

spirit spirit::parse(const std::string& s) {
    return fromString(s);
}

// Статические константы
const spirit spirit::ZERO(0.0f);
const spirit spirit::INF(new Impl(1.0f, 1.0f));
const spirit spirit::NEG_INF(new Impl(-1.0f, 1.0f));
const spirit spirit::ONE(1.0f);
const spirit spirit::NEG_ONE(-1.0f);
const spirit spirit::EPSILON(new Impl(1.0f, -1.0f));

// Операторы ввода/вывода
std::ostream& operator<<(std::ostream& os, const spirit& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, spirit& num) {
    std::string s;
    is >> s;
    num = spirit::fromString(s);
    return is;
}

// Операторы с числами слева
spirit operator+(float lhs, const spirit& rhs) { return spirit(lhs) + rhs; }
spirit operator-(float lhs, const spirit& rhs) { return spirit(lhs) - rhs; }
spirit operator*(float lhs, const spirit& rhs) { return spirit(lhs) * rhs; }
spirit operator/(float lhs, const spirit& rhs) { return spirit(lhs) / rhs; }

spirit operator+(double lhs, const spirit& rhs) { return spirit(lhs) + rhs; }
spirit operator-(double lhs, const spirit& rhs) { return spirit(lhs) - rhs; }
spirit operator*(double lhs, const spirit& rhs) { return spirit(lhs) * rhs; }
spirit operator/(double lhs, const spirit& rhs) { return spirit(lhs) / rhs; }

spirit operator+(int lhs, const spirit& rhs) { return spirit(lhs) + rhs; }
spirit operator-(int lhs, const spirit& rhs) { return spirit(lhs) - rhs; }
spirit operator*(int lhs, const spirit& rhs) { return spirit(lhs) * rhs; }
spirit operator/(int lhs, const spirit& rhs) { return spirit(lhs) / rhs; }

// Математические функции
spirit sqrt(const spirit& x) {
    if (x.isZero()) return spirit::ZERO;
    if (x.isInfinity()) return spirit::INF;
    if (x.isNegative()) {
        throw std::domain_error("sqrt of negative number");
    }
    return spirit(std::sqrt(static_cast<float>(x)));
}

spirit pow(const spirit& x, double exponent) {
    if (x.isZero()) {
        if (exponent > 0) return spirit::ZERO;
        if (exponent < 0) return spirit::INF;
        return spirit::ONE;  // 0^0 = 1 (по соглашению)
    }
    
    if (x.isInfinity()) {
        if (exponent > 0) return spirit::INF;
        if (exponent < 0) return spirit::ZERO;
        return spirit::ONE;
    }
    
    return spirit(std::pow(static_cast<float>(x), exponent));
}

spirit exp(const spirit& x) {
    if (x.isZero()) return spirit::ONE;
    if (x.isInfinity()) {
        if (x.isPositive()) return spirit::INF;
        else return spirit::ZERO;
    }
    return spirit(std::exp(static_cast<float>(x)));
}

spirit log(const spirit& x) {
    if (x.isZero()) return spirit::NEG_INF;
    if (x.isInfinity()) return spirit::INF;
    if (x.isNegative()) {
        throw std::domain_error("log of negative number");
    }
    return spirit(std::log(static_cast<float>(x)));
}

spirit sin(const spirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("sin of infinity");
    }
    return spirit(std::sin(static_cast<float>(x)));
}

spirit cos(const spirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("cos of infinity");
    }
    return spirit(std::cos(static_cast<float>(x)));
}

spirit tan(const spirit& x) {
    if (x.isInfinity()) {
        throw std::domain_error("tan of infinity");
    }
    return spirit(std::tan(static_cast<float>(x)));
}

} // namespace paradox