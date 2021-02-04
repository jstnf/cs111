#include <cmath>
#include <iostream>
#include "./header/InfInt.h" // Credit https://github.com/sercantutar/infint

int inverseMod(int, int);
char decrypt(int, int, int);

// CS111 HW 2 Problem 2 code solution
// jfigu042@ucr.edu / byutu001@ucr.edu
// RSA protocol
int main() {
    // Encrypted message
    int encrypted[] = {
        19, 14, 51, 20,  7, 10, 21,
         7, 10, 25,  7, 26, 27, 12,
        10, 26, 33, 25,  7, 21, 14,
         8, 21,  7, 21, 14, 51,  7,
        17, 26,  8, 52, 25,  7,  9,
         8, 20, 20, 26, 21,  7, 27,
        51,  7, 39, 51,  8,  9, 14,
        51, 15,  7, 15, 26,  7, 20,
        26, 21,  7,  8, 15, 11, 33,
        25, 21,  7, 21, 14, 51,  7,
        17, 26,  8, 52, 25,  7,  8,
        15, 11, 33, 25, 21,  7, 21,
        14, 51,  7,  8,  9, 21, 10,
        26, 20,  7, 25, 21, 51, 18,
        25
    };
    int encryptedLength = 99;

    // Alice's RSA public key (23, 55)
    int e = 23, n = 55; 

    // We choose prime factors 5 and 11 for p and q (5 * 11 = 55 = n)
    int p = 5, q = 11;

    // Calculate phiN = (p - 1)(q - 1)
    int phiN = (p - 1) * (q - 1);

    // Calculate the inverse modulo of phiN
    int d = inverseMod(e, phiN);

    // Now go through every number in the encrypted message and use the formula
    // D(C) = C^d(mod n) where C = the encrypted number
    for (int i = 0; i < encryptedLength; i++) {
        char decrypted = decrypt(encrypted[i], d, n);
        std::cout << decrypted;
    }
}

/**
 * Use the RSA protocol to calculate the mappings of the encrypted values to
 * their respective characters.
 *
 * D(C) = C^d (mod n)
 */
char decrypt(int c, int d, int n) {
    InfInt decrypted = c;
    // Naive implementation of exponentiation because InfInt does not have direct pow function
    for (int j = 0; j < d - 1; j++) {
        decrypted *= c;
    }
    decrypted %= n;

    int decryptedInt = decrypted.toInt();
    if (decryptedInt >= 2 && decryptedInt < 28) {
        return decryptedInt + 63; // 'A' starts at 65 on ASCII
    } else if (decryptedInt == 28) {
        return ' ';
    } else {
        return '?';
    }
}

/**
 * We apply a simple brute force approach to calculate the inverse mod, given e and phiN.
 *
 * Using the equation a * x (mod m) = 1, where a is the number to inverse and x is a number
 * that when multiplied, results in a remainder of 1 given the modulo m.
 *
 * We will check all integers (1 < x < phiN).
*/
int inverseMod(int e, int phiN) {
    for (int x = 1; x < phiN; x++) {
        if ((e * x) % phiN == 1) return x;
    }

    // No such inverse mod exists - possible in extreme situations
    return phiN;
}