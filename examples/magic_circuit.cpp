#include "dspirit.h"
#include <iostream>
#include <iomanip>

using namespace paradox;

int main() {
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "==================================================" << std::endl;
    std::cout << "  MAGIC CIRCUIT: PARALLEL CONNECTION" << std::endl;
    std::cout << "       WITH AN IDEAL CONDUCTOR" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;
    
    // Circuit parameters
    dspirit U = 12;           // Voltage source, V
    dspirit R1 = 10;          // Series resistance, Ohm
    dspirit R2 = 20;          // Parallel end resistance, Ohm
    dspirit R3 = 0;          // Ideal conductor (0 Ohm)
    
    std::cout << "CIRCUIT PARAMETERS:" << std::endl;
    std::cout << "Voltage source: U = " << U << " V" << std::endl;
    std::cout << "Series resistance: R1 = " << R1 << " Ohm" << std::endl;
    std::cout << "Parallel resistance: R2 = " << R2 << " Ohm" << std::endl;
    std::cout << "Ideal conductor: R3 = " << R3 << " Ohm" << std::endl;
    std::cout << std::endl;
    
    // Circuit diagram:
    // [U]---[R1]---[A]---[R2]---[B]
    //                |           |
    //               [R3]         |
    //                |-----------|
    
    std::cout << "CIRCUIT DIAGRAM:" << std::endl;
    std::cout << "    [U=12V]" << std::endl;
    std::cout << "       |" << std::endl;
    std::cout << "      [R1=10Ω]" << std::endl;
    std::cout << "       |" << std::endl;
    std::cout << "       A (connection point)" << std::endl;
    std::cout << "       |\\" << std::endl;
    std::cout << "      [R2=20Ω] [R3=0Ω]" << std::endl;
    std::cout << "       |       |" << std::endl;
    std::cout << "       B-------|" << std::endl;
    std::cout << "       |" << std::endl;
    std::cout << "      [GND]" << std::endl;
    std::cout << std::endl;
    
    // Step 1: Equivalent resistance of parallel connection R2 and R3
    std::cout << "STEP 1: EQUIVALENT RESISTANCE OF PARALLEL CONNECTION" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    
    // For parallel connection: 1/R_par = 1/R2 + 1/R3
    dspirit R_par_inv = R2.inverse() + R3.inverse();
    dspirit R_par = R_par_inv.inverse();
    
    std::cout << "1/R_par = 1/R2 + 1/R3 = 1/" << R2 << " + 1/" << R3 << std::endl;
    std::cout << "1/R_par = " << R2.inverse() << " + " << R3.inverse() << std::endl;
    std::cout << "1/R_par = " << R_par_inv << std::endl;
    std::cout << "R_par = 1 / (1/R_par) = " << R_par << " Ohm" << std::endl;
    
    if (R_par.isZero()) {
        std::cout << "CONCLUSION: Parallel connection with an ideal conductor has zero resistance!" << std::endl;
    }
    std::cout << std::endl;
    
    // Step 2: Total circuit resistance
    std::cout << "STEP 2: TOTAL CIRCUIT RESISTANCE" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    
    dspirit R_total = R1 + R_par;
    std::cout << "R_total = R1 + R_par = " << R1 << " + " << R_par << std::endl;
    std::cout << "R_total = " << R_total << " Ohm" << std::endl;
    std::cout << std::endl;
    
    // Step 3: Total current in the circuit
    std::cout << "STEP 3: TOTAL CURRENT IN THE CIRCUIT (BY OHM'S LAW)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    
    dspirit I_total = U / R_total;
    std::cout << "I_total = U / R_total = " << U << " / " << R_total << std::endl;
    std::cout << "I_total = " << I_total << " A" << std::endl;
    std::cout << std::endl;
    
    // Step 4: Voltage at point A (at parallel connection)
    std::cout << "STEP 4: VOLTAGE AT POINT A" << std::endl;
    std::cout << "--------------------------" << std::endl;
    
    dspirit U_A = I_total * R_par;
    std::cout << "U_A = I_total × R_par = " << I_total << " × " << R_par << std::endl;
    std::cout << "U_A = " << U_A << " V" << std::endl;
    
    // Look at internal representation
    std::cout << std::endl;
    std::cout << "DETAILED ANALYSIS OF U_A:" << std::endl;
    std::cout << "  Regular layer: " << U_A.toString() << std::endl;
    
    if (U_A.isZero()) {
        std::cout << "  In the regular layer, voltage equals 0" << std::endl;
    } else if (U_A.isInfinity()) {
        std::cout << "  In the regular layer, voltage is infinite" << std::endl;
    }
    std::cout << std::endl;
    
    // Step 5: Currents through each branch of parallel connection
    std::cout << "STEP 5: CURRENTS THROUGH PARALLEL BRANCHES" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    // Current through R2 (regular resistor)
    dspirit I_R2 = U_A / R2;
    std::cout << "Through R2 (20 Ohm):" << std::endl;
    std::cout << "  I_R2 = U_A / R2 = " << U_A << " / " << R2 << std::endl;
    std::cout << "  I_R2 = " << I_R2 << " A" << std::endl;
    
    // Current through R3 (ideal conductor)
    dspirit I_R3 = U_A / R3;
    std::cout << "\nThrough R3 (0 Ohm - ideal conductor):" << std::endl;
    std::cout << "  I_R3 = U_A / R3 = " << U_A << " / " << R3 << std::endl;
    std::cout << "  I_R3 = " << I_R3 << " A" << std::endl;
    
    // Check: I_total should equal I_R2 + I_R3
    dspirit I_sum = I_R2 + I_R3;
    std::cout << "\nCheck: I_total = I_R2 + I_R3" << std::endl;
    std::cout << "  " << I_total << " = " << I_R2 << " + " << I_R3 << std::endl;
    std::cout << "  " << I_total << " = " << I_sum << std::endl;
    
    if (I_total == I_sum) {
        std::cout << "  ✓ Kirchhoff's first law is satisfied!" << std::endl;
    } else {
        std::cout << "  ✗ Kirchhoff's first law is not satisfied" << std::endl;
    }
    std::cout << std::endl;
    
    // Step 6: MAGIC - why is I_R3 finite?
    std::cout << "STEP 6: MAGIC OF LAYERS" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    std::cout << "Let's see what happens at different levels:" << std::endl;
    std::cout << std::endl;
    
    // Create representation with explicit level for R3
    // In reality, R3 = dspirit::ZERO already has level -1
    // But let's create it explicitly with coefficient 1 at level -1
    dspirit R3_detailed = 0.0f;  // 1 * ε (very small, but not zero)
    
    std::cout << "Detailed representation of ideal conductor:" << std::endl;
    std::cout << "  R3_detailed = " << R3_detailed << " Ohm" << std::endl;
    std::cout << "  This means: resistance equals infinitesimal quantity ε" << std::endl;
    std::cout << std::endl;
    
    // Recalculate with R3_detailed
    dspirit R_par_inv_detailed = R2.inverse() + R3_detailed.inverse();
    dspirit R_par_detailed = R_par_inv_detailed.inverse();
    dspirit R_total_detailed = R1 + R_par_detailed;
    dspirit I_total_detailed = U / R_total_detailed;
    dspirit U_A_detailed = I_total_detailed * R_par_detailed;
    dspirit I_R3_detailed = U_A_detailed / R3_detailed;
    
    std::cout << "Recalculation with detailed representation of R3:" << std::endl;
    std::cout << "  R_par = " << R_par_detailed << " Ohm" << std::endl;
    std::cout << "  R_total = " << R_total_detailed << " Ohm" << std::endl;
    std::cout << "  I_total = " << I_total_detailed << " A" << std::endl;
    std::cout << "  U_A = " << U_A_detailed << " V" << std::endl;
    std::cout << "  I_R3 = U_A / R3 = " << I_R3_detailed << " A" << std::endl;
    std::cout << std::endl;
    
    // Level analysis
    std::cout << "LEVEL ANALYSIS:" << std::endl;
    std::cout << "---------------" << std::endl;
    
    // U_A is at level -1 (infinitesimal)
    // R3 is at level -1 (infinitesimal)
    // Their ratio gives level 0 (finite number)
    
    std::cout << "U_A is at level -1: this is an infinitesimal quantity" << std::endl;
    std::cout << "R3 is at level -1: this is also an infinitesimal quantity" << std::endl;
    std::cout << "I_R3 = U_A / R3: level (-1) - (-1) = 0" << std::endl;
    std::cout << "Thus, I_R3 is at regular level 0 - this is a finite number!" << std::endl;
    std::cout << std::endl;
    
    // Step 7: Power calculation
    std::cout << "STEP 7: POWER CALCULATION" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    dspirit P_R1 = I_total * I_total * R1;
    dspirit P_R2 = I_R2 * I_R2 * R2;
    dspirit P_R3 = I_R3 * I_R3 * R3;
    dspirit P_total = U * I_total;
    dspirit P_sum = P_R1 + P_R2 + P_R3;
    
    std::cout << "Power on R1: P_R1 = I² × R1 = " << P_R1 << " W" << std::endl;
    std::cout << "Power on R2: P_R2 = I_R2² × R2 = " << P_R2 << " W" << std::endl;
    std::cout << "Power on R3: P_R3 = I_R3² × R3 = " << P_R3 << " W" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Total power: P_sum = P_R1 + P_R2 + P_R3 = " << P_sum << " W" << std::endl;
    std::cout << "Total power from source: P_total = U × I_total = " << P_total << " W" << std::endl;
    
    if (P_total == P_sum) {
        std::cout << "✓ Power balance is satisfied!" << std::endl;
    } else {
        std::cout << "✗ Power balance is not satisfied" << std::endl;
    }
    std::cout << std::endl;
    
    // Step 8: Practical meaning
    std::cout << "STEP 8: PRACTICAL MEANING" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    std::cout << "This circuit models a situation where:" << std::endl;
    std::cout << "1. We have a regular load (R2 = 20 Ohm)" << std::endl;
    std::cout << "2. An almost ideal conductor (very small resistance) is connected in parallel" << std::endl;
    std::cout << "3. The entire circuit is protected by a series resistor (R1 = 10 Ohm)" << std::endl;
    std::cout << std::endl;
    
    std::cout << "RESULTS:" << std::endl;
    std::cout << "1. Total current: " << I_total << " A" << std::endl;
    std::cout << "2. Voltage at connection point: " << U_A << " V (practically 0)" << std::endl;
    std::cout << "3. Current through regular load: " << I_R2 << " A (practically 0)" << std::endl;
    std::cout << "4. Current through ideal conductor: " << I_R3 << " A (almost all current!)" << std::endl;
    std::cout << std::endl;
    
    std::cout << "PHYSICAL INTERPRETATION:" << std::endl;
    std::cout << "The ideal conductor 'shorts' the parallel connection," << std::endl;
    std::cout << "so almost all current goes through it, not through the regular load." << std::endl;
    std::cout << "At the same time, the voltage drop across the parallel connection" << std::endl;
    std::cout << "is very small, but not exactly zero (level -1)." << std::endl;
    std::cout << std::endl;
    
    // Additional analysis: what if R3 is not ideal, but just very small?
    std::cout << "ADDITIONAL ANALYSIS: DIFFERENT VALUES OF R3" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    
    std::cout << "Let's see how current I_R3 changes with different values of R3:" << std::endl;
    std::cout << std::endl;
    
    std::cout << std::setw(15) << "R3 (Ohm)" << std::setw(20) << "I_R3 (A)" << std::setw(25) << "U_A (V)" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    // Test different R3 values
    double r3_values[] = {0.001, 0.01, 0.1, 1.0, 10.0, 20.0, 100.0};
    
    for (double r3_val : r3_values) {
        dspirit R3_test(r3_val);
        dspirit R_par_test = dspirit::ONE / (R2.inverse() + R3_test.inverse());
        dspirit R_total_test = R1 + R_par_test;
        dspirit I_total_test = U / R_total_test;
        dspirit U_A_test = I_total_test * R_par_test;
        dspirit I_R3_test = U_A_test / R3_test;
        
        std::cout << std::setw(15) << r3_val 
                  << std::setw(20) << static_cast<double>(I_R3_test)
                  << std::setw(25) << static_cast<double>(U_A_test) << std::endl;
    }
    
    // Ideal case (R3 = 0)
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::setw(15) << "0 (ideal)" 
              << std::setw(20) << static_cast<double>(I_R3)
              << std::setw(25) << static_cast<double>(U_A) << std::endl;
    
    std::cout << std::endl;
    std::cout << "CONCLUSION: When R3 → 0, current I_R3 tends to a finite value!" << std::endl;
    std::cout << "       This value equals U / R1 = " << (U / R1) << " A" << std::endl;
    
    std::cout << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "          MAGIC SUCCESSFULLY COMPLETED!" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    return 0;
}