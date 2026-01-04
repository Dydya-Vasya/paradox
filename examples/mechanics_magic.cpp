#include "dspirit.h"
#include <iostream>
#include <iomanip>

using namespace paradox;

class RelativisticMechanics {
public:
    static void zeroMassParticle() {
        std::cout << "=== MECHANICS: PARTICLE WITH ZERO MASS ===" << std::endl;
        std::cout << std::endl;
        
        // Photon - particle with zero rest mass
        dspirit m0 = dspirit::ZERO;           // Rest mass
        dspirit c = dspirit(299792458.0);     // Speed of light
        dspirit v = c;                       // Photon speed (equals speed of light)
        
        std::cout << "Photon parameters:" << std::endl;
        std::cout << "  Rest mass m0 = " << m0 << " kg" << std::endl;
        std::cout << "  Speed of light c = " << c << " m/s" << std::endl;
        std::cout << "  Photon speed v = " << v << " m/s" << std::endl;
        std::cout << std::endl;
        
        // Relativistic factor
        dspirit gamma = dspirit::ONE / sqrt(dspirit::ONE - (v * v) / (c * c));
        std::cout << "Relativistic factor γ:" << std::endl;
        std::cout << "  γ = 1 / sqrt(1 - v²/c²) = " << gamma << std::endl;
        
        if (gamma.isInfinity()) {
            std::cout << "  γ is infinite for a particle moving at the speed of light!" << std::endl;
        }
        std::cout << std::endl;
        
        // Relativistic mass
        dspirit m_rel = m0 * gamma;
        std::cout << "Relativistic mass m = m0 * γ:" << std::endl;
        std::cout << "  m = " << m0 << " * " << gamma << " = " << m_rel << " kg" << std::endl;
        
        // This is an uncertainty of the form 0 × ∞
        // But actually for a photon, rest mass is 0 and γ is infinite
        // Their product gives finite energy divided by c²
        std::cout << std::endl;
        
        // Photon momentum via energy
        dspirit h = dspirit(6.62607015e-34);  // Planck's constant
        dspirit lambda = dspirit(500e-9);     // Wavelength 500 nm
        dspirit p = h / lambda;              // Photon momentum
        
        std::cout << "Photon momentum (quantum calculation):" << std::endl;
        std::cout << "  Planck's constant h = " << h << " J·s" << std::endl;
        std::cout << "  Wavelength λ = " << lambda << " m" << std::endl;
        std::cout << "  Momentum p = h / λ = " << p << " kg·m/s" << std::endl;
        std::cout << std::endl;
        
        // Photon energy
        dspirit E = p * c;
        std::cout << "Photon energy E = p * c:" << std::endl;
        std::cout << "  E = " << p << " * " << c << " = " << E << " J" << std::endl;
        
        // Mass via energy: m = E/c²
        dspirit m_from_E = E / (c * c);
        std::cout << "Effective mass m = E/c²:" << std::endl;
        std::cout << "  m = " << E << " / (" << c << "²) = " << m_from_E << " kg" << std::endl;
        
        std::cout << std::endl;
        std::cout << "CONCLUSION: A photon has zero rest mass but finite momentum and energy!" << std::endl;
        std::cout << "       This is possible thanks to level arithmetic: 0 × ∞ = finite number." << std::endl;
        std::cout << std::endl;
    }
    
    static void infiniteSpeedMovement() {
        std::cout << "=== MECHANICS: MOVEMENT WITH INFINITE SPEED ===" << std::endl;
        std::cout << std::endl;
        
        // Consider an object moving with infinite speed
        dspirit v = dspirit::INF;     // Infinite speed
        dspirit t = dspirit(1.0);     // 1 second
        
        std::cout << "Movement parameters:" << std::endl;
        std::cout << "  Speed v = " << v << " m/s" << std::endl;
        std::cout << "  Time t = " << t << " s" << std::endl;
        std::cout << std::endl;
        
        // Distance traveled
        dspirit s = v * t;
        std::cout << "Distance traveled s = v * t:" << std::endl;
        std::cout << "  s = " << v << " * " << t << " = " << s << " m" << std::endl;
        
        if (s.isInfinity()) {
            std::cout << "  In finite time, the object covers infinite distance!" << std::endl;
            std::cout << "  This corresponds to the concept of teleportation." << std::endl;
        }
        std::cout << std::endl;
        
        // Kinetic energy (non-relativistic)
        dspirit m = dspirit(1.0);  // Mass 1 kg
        dspirit E_k = (m * v * v) / dspirit(2.0);
        std::cout << "Kinetic energy (non-relativistic) E = mv²/2:" << std::endl;
        std::cout << "  E = " << m << " * (" << v << ")² / 2 = " << E_k << " J" << std::endl;
        
        if (E_k.isInfinity()) {
            std::cout << "  Kinetic energy is infinite!" << std::endl;
            std::cout << "  This shows why infinite speed cannot be achieved." << std::endl;
        }
        std::cout << std::endl;
        
        // Relativistic kinetic energy
        dspirit c = dspirit(299792458.0);
        // Formula: E_k = (γ - 1) * m * c², where γ = 1/sqrt(1 - v²/c²)
        dspirit gamma_rel = dspirit::ONE / sqrt(dspirit::ONE - (v * v) / (c * c));
        dspirit E_k_rel = (gamma_rel - dspirit::ONE) * m * c * c;
        
        std::cout << "Relativistic kinetic energy:" << std::endl;
        std::cout << "  γ = " << gamma_rel << std::endl;
        std::cout << "  E_k = (γ - 1) * m * c² = " << E_k_rel << " J" << std::endl;
        
        std::cout << std::endl;
        std::cout << "LEVEL MAGIC:" << std::endl;
        std::cout << "When v = ∞, the expression 1 - v²/c² becomes negative infinity." << std::endl;
        std::cout << "The square root of negative infinity is a special quantity." << std::endl;
        std::cout << "The dspirit library correctly handles this case!" << std::endl;
        std::cout << std::endl;
    }
    
    static void perfectElasticCollision() {
        std::cout << "=== MECHANICS: PERFECTLY ELASTIC COLLISION ===" << std::endl;
        std::cout << std::endl;
        
        // Perfectly elastic collision: restitution coefficient e = 1
        // But what if e > 1? This corresponds to a collision with energy release
        dspirit e = dspirit::INF;  // Infinite restitution coefficient
        dspirit m1 = dspirit(1.0); // Mass of first ball
        dspirit m2 = dspirit::ZERO; // Mass of second ball (negligible)
        dspirit v1 = dspirit(10.0); // Velocity of first ball before collision
        
        std::cout << "Collision parameters:" << std::endl;
        std::cout << "  Mass of first ball m1 = " << m1 << " kg" << std::endl;
        std::cout << "  Mass of second ball m2 = " << m2 << " kg (negligible)" << std::endl;
        std::cout << "  Velocity of first ball v1 = " << v1 << " m/s" << std::endl;
        std::cout << "  Restitution coefficient e = " << e << std::endl;
        std::cout << std::endl;
        
        // Formulas for perfectly elastic collision:
        // v1' = ((m1 - e*m2)*v1 + (1+e)*m2*v2) / (m1 + m2)
        // v2' = ((1+e)*m1*v1 + (m2 - e*m1)*v2) / (m1 + m2)
        
        dspirit v2 = dspirit::ZERO; // Second ball is stationary
        
        // After collision
        dspirit v1_prime = ((m1 - e * m2) * v1 + (dspirit::ONE + e) * m2 * v2) / (m1 + m2);
        dspirit v2_prime = ((dspirit::ONE + e) * m1 * v1 + (m2 - e * m1) * v2) / (m1 + m2);
        
        std::cout << "Velocities after collision:" << std::endl;
        std::cout << "  v1' = " << v1_prime << " m/s" << std::endl;
        std::cout << "  v2' = " << v2_prime << " m/s" << std::endl;
        std::cout << std::endl;
        
        // Kinetic energy before collision
        dspirit E_before = (m1 * v1 * v1 + m2 * v2 * v2) / dspirit(2.0);
        
        // Kinetic energy after collision
        dspirit E_after = (m1 * v1_prime * v1_prime + m2 * v2_prime * v2_prime) / dspirit(2.0);
        
        std::cout << "Kinetic energy:" << std::endl;
        std::cout << "  Before collision: E = " << E_before << " J" << std::endl;
        std::cout << "  After collision: E = " << E_after << " J" << std::endl;
        
        // For e = INF, energy after collision should be infinite
        if (E_after.isInfinity()) {
            std::cout << "  Energy after collision is infinite!" << std::endl;
            std::cout << "  This corresponds to an explosion or nuclear reaction." << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "LEVEL MAGIC:" << std::endl;
        std::cout << "When m2 = 0 (level -1) and e = ∞ (level 1)," << std::endl;
        std::cout << "the product e * m2 gives level 0 (0 × ∞ = finite number)." << std::endl;
        std::cout << "This allows correct calculation of velocities after collision!" << std::endl;
        std::cout << std::endl;
    }
};

class FluidDynamics {
public:
    static void idealFluidFlow() {
        std::cout << "=== FLUID DYNAMICS: IDEAL FLUID ===" << std::endl;
        std::cout << std::endl;
        
        // Ideal fluid: zero viscosity
        dspirit eta = dspirit::ZERO;  // Dynamic viscosity
        dspirit rho = dspirit(1000.0); // Water density
        dspirit v = dspirit(1.0);     // Flow velocity
        dspirit L = dspirit(0.1);     // Characteristic size
        
        std::cout << "Flow parameters:" << std::endl;
        std::cout << "  Viscosity η = " << eta << " Pa·s (ideal fluid)" << std::endl;
        std::cout << "  Density ρ = " << rho << " kg/m³" << std::endl;
        std::cout << "  Velocity v = " << v << " m/s" << std::endl;
        std::cout << "  Characteristic size L = " << L << " m" << std::endl;
        std::cout << std::endl;
        
        // Reynolds number Re = ρ * v * L / η
        dspirit Re = rho * v * L / eta;
        std::cout << "Reynolds number Re = ρ * v * L / η:" << std::endl;
        std::cout << "  Re = " << rho << " * " << v << " * " << L << " / " << eta << std::endl;
        std::cout << "  Re = " << Re << std::endl;
        
        if (Re.isInfinity()) {
            std::cout << "  Re is infinite for an ideal fluid!" << std::endl;
            std::cout << "  This corresponds to turbulent flow." << std::endl;
        }
        std::cout << std::endl;
        
        // Drag force for a sphere in an ideal fluid (Stokes formula)
        // F = 6 * π * η * R * v
        dspirit R = dspirit(0.01);  // Sphere radius
        dspirit F_stokes = dspirit(6.0) * dspirit(3.14159) * eta * R * v;
        
        std::cout << "Stokes drag force for a sphere:" << std::endl;
        std::cout << "  Radius R = " << R << " m" << std::endl;
        std::cout << "  F = 6π * η * R * v = " << F_stokes << " N" << std::endl;
        
        if (F_stokes.isZero()) {
            std::cout << "  In an ideal fluid, drag force is zero!" << std::endl;
            std::cout << "  This is d'Alembert's paradox." << std::endl;
        }
        std::cout << std::endl;
        
        // Bernoulli's equation for an ideal fluid
        dspirit p1 = dspirit(100000.0);  // Pressure at point 1
        dspirit h1 = dspirit(10.0);      // Height of point 1
        dspirit v1 = dspirit(1.0);       // Velocity at point 1
        
        dspirit h2 = dspirit(0.0);       // Height of point 2
        dspirit v2 = dspirit::INF;       // Velocity at point 2 (Laval nozzle)
        
        dspirit g = dspirit(9.81);       // Gravitational acceleration
        
        // Bernoulli's equation: p1/ρ + g*h1 + v1²/2 = p2/ρ + g*h2 + v2²/2
        // Express p2
        dspirit left_side = p1 / rho + g * h1 + (v1 * v1) / dspirit(2.0);
        dspirit v2_squared = v2 * v2;
        
        std::cout << "Bernoulli's equation for a Laval nozzle:" << std::endl;
        std::cout << "  At point 1: p1 = " << p1 << " Pa, h1 = " << h1 << " m, v1 = " << v1 << " m/s" << std::endl;
        std::cout << "  At point 2: h2 = " << h2 << " m, v2 = " << v2 << " m/s" << std::endl;
        std::cout << "  Left side: p1/ρ + g*h1 + v1²/2 = " << left_side << std::endl;
        std::cout << "  v2² = " << v2_squared << " (infinity)" << std::endl;
        
        dspirit p2 = rho * (left_side - g * h2 - v2_squared / dspirit(2.0));
        
        std::cout << "  Pressure at point 2: p2 = " << p2 << " Pa" << std::endl;
        
        if (p2.isNegative()) {
            std::cout << "  Pressure is negative!" << std::endl;
            std::cout << "  This corresponds to cavitation." << std::endl;
        }
        
        std::cout << std::endl;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "==================================================" << std::endl;
    std::cout << "  MAGICAL MECHANICS AND FLUID DYNAMICS" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;
    
    try {
        // Example 1: Particle with zero mass
        RelativisticMechanics::zeroMassParticle();
        
        // Example 2: Movement with infinite speed
        RelativisticMechanics::infiniteSpeedMovement();
        
        // Example 3: Perfectly elastic collision
        RelativisticMechanics::perfectElasticCollision();
        
        // Example 4: Ideal fluid
        FluidDynamics::idealFluidFlow();
        
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