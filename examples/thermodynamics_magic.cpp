#include "dspirit.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace paradox;

class Thermodynamics {
public:
    static void absoluteZero() {
        std::cout << "=== THERMODYNAMICS: ABSOLUTE ZERO ===" << std::endl;
        std::cout << std::endl;
        
        dspirit T = dspirit::ZERO;          // Absolute zero temperature
        dspirit k = dspirit(1.380649e-23);  // Boltzmann constant
        
        std::cout << "Temperature T = " << T << " K" << std::endl;
        std::cout << "Boltzmann constant k = " << k << " J/K" << std::endl;
        std::cout << std::endl;
        
        // Average kinetic energy of ideal gas molecule
        dspirit E_avg = (dspirit(3.0) / dspirit(2.0)) * k * T;
        std::cout << "Average kinetic energy of molecule:" << std::endl;
        std::cout << "  ⟨E⟩ = (3/2) * k * T = " << E_avg << " J" << std::endl;
        
        if (E_avg.isZero()) {
            std::cout << "  At absolute zero, average kinetic energy is zero." << std::endl;
        }
        std::cout << std::endl;
        
        // Entropy at absolute zero (third law of thermodynamics)
        dspirit S = dspirit::ZERO;
        std::cout << "Entropy at T = 0:" << std::endl;
        std::cout << "  S = " << S << " J/K" << std::endl;
        std::cout << "  This is the third law of thermodynamics: S → 0 as T → 0." << std::endl;
        std::cout << std::endl;
        
        // Heat capacity at absolute zero
        // For many systems C → 0 as T → 0
        dspirit C_v = dspirit::ZERO;
        std::cout << "Heat capacity at T = 0:" << std::endl;
        std::cout << "  C_v = " << C_v << " J/(kg·K)" << std::endl;
        std::cout << std::endl;
        
        // Boltzmann distribution at T → 0
        dspirit E1 = dspirit(1.0e-20);  // Energy level 1
        dspirit E2 = dspirit(2.0e-20);  // Energy level 2
        
        dspirit p1 = exp(-E1 / (k * T));
        dspirit p2 = exp(-E2 / (k * T));
        
        std::cout << "Boltzmann distribution at T → 0:" << std::endl;
        std::cout << "  Occupancy probability of level 1: p1 = exp(-E1/kT) = " << p1 << std::endl;
        std::cout << "  Occupancy probability of level 2: p2 = exp(-E2/kT) = " << p2 << std::endl;
        
        // At T = 0, exp(-E/kT) = exp(-∞) = 0 for E > 0
        // But for ground state (E = 0) probability should be 1
        dspirit E0 = dspirit::ZERO;
        dspirit p0 = exp(-E0 / (k * T));  // exp(0/0) - uncertainty!
        
        std::cout << "  Occupancy probability of ground state (E=0):" << std::endl;
        std::cout << "    p0 = exp(-0/0) = " << p0 << " (uncertainty 0/0)" << std::endl;
        
        std::cout << std::endl;
        std::cout << "LEVEL MAGIC:" << std::endl;
        std::cout << "The dspirit library allows working with expressions like 0/0" << std::endl;
        std::cout << "and exp(-∞), obtaining physically meaningful results." << std::endl;
        std::cout << std::endl;
    }
    
    static void infiniteTemperature() {
        std::cout << "=== THERMODYNAMICS: INFINITE TEMPERATURE ===" << std::endl;
        std::cout << std::endl;
        
        dspirit T = dspirit::INF;           // Infinite temperature
        dspirit k = dspirit(1.380649e-23);  // Boltzmann constant
        
        std::cout << "Temperature T = " << T << " K" << std::endl;
        std::cout << "Boltzmann constant k = " << k << " J/K" << std::endl;
        std::cout << std::endl;
        
        // Average kinetic energy
        dspirit E_avg = (dspirit(3.0) / dspirit(2.0)) * k * T;
        std::cout << "Average kinetic energy:" << std::endl;
        std::cout << "  ⟨E⟩ = (3/2) * k * T = " << E_avg << " J" << std::endl;
        
        if (E_avg.isInfinity()) {
            std::cout << "  At infinite temperature, energy is infinite." << std::endl;
        }
        std::cout << std::endl;
        
        // Boltzmann distribution at T → ∞
        dspirit E1 = dspirit(1.0);  // Energy level 1
        dspirit E2 = dspirit(2.0);  // Energy level 2
        
        dspirit p1 = exp(-E1 / (k * T));
        dspirit p2 = exp(-E2 / (k * T));
        
        std::cout << "Boltzmann distribution at T → ∞:" << std::endl;
        std::cout << "  p1 = exp(-E1/kT) = exp(-" << E1 << "/(" << k << "*" << T << "))" << std::endl;
        std::cout << "  p1 = exp(0) = " << p1 << " (since E1/kT → 0)" << std::endl;
        std::cout << "  p2 = exp(-E2/kT) = " << p2 << std::endl;
        
        // At T = ∞, exp(-E/kT) = exp(0) = 1 for any finite E
        std::cout << "  All levels are equally populated!" << std::endl;
        std::cout << std::endl;
        
        // Entropy at T → ∞
        // For system with N levels, S = k * ln(N) for uniform distribution
        dspirit N = dspirit(1000.0);  // Number of levels
        dspirit S = k * log(N);
        
        std::cout << "Entropy at T → ∞:" << std::endl;
        std::cout << "  For system with N = " << N << " levels:" << std::endl;
        std::cout << "  S = k * ln(N) = " << S << " J/K" << std::endl;
        
        std::cout << std::endl;
    }
    
    static void perfectHeatEngine() {
        std::cout << "=== THERMODYNAMICS: PERFECT HEAT ENGINE ===" << std::endl;
        std::cout << std::endl;
        
        // Carnot cycle with infinite heater temperature
        dspirit T_hot = dspirit::INF;  // Heater temperature
        dspirit T_cold = dspirit(300.0);  // Refrigerator temperature
        
        std::cout << "Carnot cycle parameters:" << std::endl;
        std::cout << "  Heater temperature T_h = " << T_hot << " K" << std::endl;
        std::cout << "  Refrigerator temperature T_c = " << T_cold << " K" << std::endl;
        std::cout << std::endl;
        
        // Carnot efficiency: η = 1 - T_c / T_h
        dspirit eta = dspirit::ONE - T_cold / T_hot;
        std::cout << "Carnot efficiency η = 1 - T_c / T_h:" << std::endl;
        std::cout << "  η = 1 - " << T_cold << " / " << T_hot << std::endl;
        std::cout << "  η = " << eta << std::endl;
        
        if (eta == dspirit::ONE) {
            std::cout << "  Efficiency is 100% at infinite heater temperature!" << std::endl;
        }
        std::cout << std::endl;
        
        // Work per cycle
        dspirit Q_h = dspirit(1000.0);  // Heat from heater
        dspirit W = eta * Q_h;         // Useful work
        
        std::cout << "Work per cycle:" << std::endl;
        std::cout << "  Heat from heater Q_h = " << Q_h << " J" << std::endl;
        std::cout << "  Useful work W = η * Q_h = " << W << " J" << std::endl;
        
        if (W == Q_h) {
            std::cout << "  All heat is converted to work!" << std::endl;
        }
        std::cout << std::endl;
        
        // Heat given to refrigerator
        dspirit Q_c = Q_h - W;
        std::cout << "Heat to refrigerator Q_c = Q_h - W:" << std::endl;
        std::cout << "  Q_c = " << Q_h << " - " << W << " = " << Q_c << " J" << std::endl;
        
        if (Q_c.isZero()) {
            std::cout << "  No heat is transferred to refrigerator!" << std::endl;
            std::cout << "  This contradicts the second law of thermodynamics." << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "LEVEL MAGIC:" << std::endl;
        std::cout << "When T_h = ∞, expression T_c/T_h = 0 (finite/infinite = 0)." << std::endl;
        std::cout << "Therefore η = 1 - 0 = 1." << std::endl;
        std::cout << "The library correctly computes such ratios!" << std::endl;
        std::cout << std::endl;
    }
};

class QuantumStatistics {
public:
    static void boseEinsteinCondensate() {
        std::cout << "=== QUANTUM STATISTICS: BOSE-EINSTEIN CONDENSATE ===" << std::endl;
        std::cout << std::endl;
        
        // Below critical temperature, macroscopic number of particles
        // occupies ground state (energy E = 0)
        
        dspirit T = dspirit::ZERO;          // Absolute zero
        dspirit mu = dspirit::ZERO;         // Chemical potential (for bosons at T=0, μ=0)
        dspirit k = dspirit(1.380649e-23);  // Boltzmann constant
        
        std::cout << "Condensate parameters:" << std::endl;
        std::cout << "  Temperature T = " << T << " K" << std::endl;
        std::cout << "  Chemical potential μ = " << mu << " J" << std::endl;
        std::cout << std::endl;
        
        // Bose-Einstein distribution: f(E) = 1 / (exp((E-μ)/kT) - 1)
        // For ground state (E=0) at T=0 and μ=0:
        // f(0) = 1 / (exp(0/0) - 1) - uncertainty!
        
        dspirit E = dspirit::ZERO;
        dspirit exponent = exp((E - mu) / (k * T));
        dspirit f_BE = dspirit::ONE / (exponent - dspirit::ONE);
        
        std::cout << "Bose-Einstein distribution for ground state:" << std::endl;
        std::cout << "  f(0) = 1 / (exp((0-0)/(k*0)) - 1)" << std::endl;
        std::cout << "  exp((E-μ)/kT) = exp(" << (E - mu) << "/(" << k << "*" << T << ")) = " << exponent << std::endl;
        std::cout << "  f(0) = " << f_BE << std::endl;
        
        if (f_BE.isInfinity()) {
            std::cout << "  Number of particles in ground state is infinite!" << std::endl;
            std::cout << "  This corresponds to macroscopic occupancy." << std::endl;
        }
        std::cout << std::endl;
        
        // For excited states (E > 0) at T=0:
        dspirit E_excited = dspirit(1.0e-23);  // Small but positive energy
        dspirit f_excited = dspirit::ONE / (exp((E_excited - mu) / (k * T)) - dspirit::ONE);
        
        std::cout << "Distribution for excited state:" << std::endl;
        std::cout << "  E = " << E_excited << " J" << std::endl;
        std::cout << "  f(E) = 1 / (exp((E-μ)/kT) - 1) = " << f_excited << std::endl;
        
        if (f_excited.isZero()) {
            std::cout << "  Excited states are not populated at T=0!" << std::endl;
        }
        std::cout << std::endl;
        
        // Critical temperature for ideal Bose gas
        dspirit h = dspirit(6.62607015e-34);    // Planck's constant
        dspirit m = dspirit(6.6464764e-27);     // Mass of helium-4 atom
        dspirit n = dspirit(2.5e28);            // Particle concentration
        
        // Formula: T_c = (2πħ²/mk) * (n/ζ(3/2))^(2/3)
        dspirit hbar = h / (dspirit(2.0) * dspirit(3.1415926535));
        dspirit zeta_3_2 = dspirit(2.612);      // Riemann zeta function ζ(3/2)
        
        dspirit T_c = (dspirit(2.0) * dspirit(3.1415926535) * hbar * hbar / (m * k)) 
                     * pow(n / zeta_3_2, static_cast<float>(dspirit(2.0)) / static_cast<float>(dspirit(3.0)));
        
        std::cout << "Critical temperature of Bose-Einstein condensate:" << std::endl;
        std::cout << "  Concentration n = " << n << " m⁻³" << std::endl;
        std::cout << "  Atom mass m = " << m << " kg" << std::endl;
        std::cout << "  T_c = " << T_c << " K" << std::endl;
        std::cout << std::endl;
        
        // Fraction of particles in condensate at T < T_c
        dspirit T_actual = dspirit(0.5) * T_c;  // Temperature below critical
        dspirit N0_N = dspirit::ONE - pow(T_actual / T_c, static_cast<float>(dspirit(3.0)) / static_cast<float>(dspirit(2.0)));
        
        std::cout << "Fraction of particles in condensate at T = " << T_actual << " K:" << std::endl;
        std::cout << "  N0/N = 1 - (T/T_c)^(3/2) = " << N0_N << std::endl;
        
        std::cout << std::endl;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "==================================================" << std::endl;
    std::cout << "  MAGICAL THERMODYNAMICS AND QUANTUM STATISTICS" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;
    
    try {
        // Example 1: Absolute zero
        Thermodynamics::absoluteZero();
        
        // Example 2: Infinite temperature
        Thermodynamics::infiniteTemperature();
        
        // Example 3: Perfect heat engine
        Thermodynamics::perfectHeatEngine();
        
        // Example 4: Bose-Einstein condensate
        QuantumStatistics::boseEinsteinCondensate();
        
        std::cout << "==================================================" << std::endl;
        std::cout << "          MAGIC SUCCESSFULLY COMPLETED!" << std::endl;
        std::cout << "==================================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
}