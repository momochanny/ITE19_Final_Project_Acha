#include <stdio.h>
#include <string.h>

// Function to convert a single Roman numeral character to its decimal value
int romanToDecimal(char ch) {
    // Match each Roman numeral character to its corresponding decimal value
    switch (ch) {
        case 'I': return 1;  // Roman numeral 'I' equals 1
        case 'V': return 5;  // Roman numeral 'V' equals 5
        case 'X': return 10; // Roman numeral 'X' equals 10
        case 'L': return 50; // Roman numeral 'L' equals 50
        case 'C': return 100; // Roman numeral 'C' equals 100
        case 'D': return 500; // Roman numeral 'D' equals 500
        case 'M': return 1000; // Roman numeral 'M' equals 1000
        default: return 0; // Return 0 for invalid characters
    }
}

// Function to convert a Roman numeral string to its decimal value
int convertRomanToDecimal(const char roman[]) {
    int total = 0; // Initialize the total value to 0
    int i;

    // Iterate through the Roman numeral string
    for (i = 0; i < strlen(roman); i++) {
        // If the current value is less than the next value, subtract it
        if (romanToDecimal(roman[i]) < romanToDecimal(roman[i + 1])) {
            total -= romanToDecimal(roman[i]);
        }
        // Otherwise, add it to the total
        else {
            total += romanToDecimal(roman[i]);
        }
    }
    return total; // Return the computed decimal value
}

// Function to convert a number to its word representation
void numberToWords(int num, char *words) {
    // Arrays for word representations of digits, teens, tens, and large numbers
    static const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    static const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    static const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    static const char *thousands[] = {"", "Thousand", "Million"};

    char temp[500] = ""; // Temporary string to hold intermediate results
    char final_result[500] = ""; // Final result string
    int part = 0; // Counter for thousand/million/billion segments

    // Process the number in chunks of 3 digits (thousands, millions, etc.)
    while (num > 0) {
        char segment[100] = ""; // String for the current segment
        int n = num % 1000; // Extract the last three digits

        if (n != 0) { // If the segment is not zero, convert it to words
            // Handle hundreds place
            if (n / 100 > 0) {
                sprintf(segment + strlen(segment), "%s Hundred ", ones[n / 100]);
            }

            n %= 100; // Remove the hundreds place

            // Handle tens and ones place
            if (n >= 10 && n <= 19) {
                sprintf(segment + strlen(segment), "%s ", teens[n - 10]); // Teens
            } else {
                if (n / 10 > 0) {
                    sprintf(segment + strlen(segment), "%s ", tens[n / 10]); // Tens
                }
                if (n % 10 > 0) {
                    sprintf(segment + strlen(segment), "%s ", ones[n % 10]); // Ones
                }
            }

            // Add the appropriate thousand/million label
            if (thousands[part][0] != '\0') {
                sprintf(segment + strlen(segment), "%s ", thousands[part]);
            }
        }

        // Prepend this segment to the final result to maintain proper order
        sprintf(temp, "%s%s", segment, final_result);
        strcpy(final_result, temp);

        num /= 1000; // Move to the next higher segment
        part++;
    }

    strcpy(words, final_result); // Copy the final result to the output
}

// Function to perform arithmetic operations
int performArithmetic(int num1, int num2, char operation) {
    // Perform the operation based on the given operator
    switch (operation) {
        case '+': return num1 + num2; // Addition
        case '-': return num1 - num2; // Subtraction
        case '*': return num1 * num2; // Multiplication
        default: return 0; // Default to 0 for invalid operators
    }
}

// Main function
int main() {
    FILE *inputFile, *outputFile;
    char roman1[50], roman2[50], operation;
    int decimal1, decimal2, result;
    char resultWords[500];

    // Open input and output files
    inputFile = fopen("Input.txt", "r");
    outputFile = fopen("Output.txt", "w");

    // Check if files opened successfully
    if (!inputFile || !outputFile) {
        printf("Error opening file!");
        return 1;
    }

    // Process each line in the input file
    while (fscanf(inputFile, "%s %c %s", roman1, &operation, roman2) != EOF) {
        // Convert Roman numerals to decimal
        decimal1 = convertRomanToDecimal(roman1);
        decimal2 = convertRomanToDecimal(roman2);
        // Perform the arithmetic operation
        result = performArithmetic(decimal1, decimal2, operation);
        // Convert the result to words
        numberToWords(result, resultWords);
        // Write the results to the output file
        fprintf(outputFile, "%d (%s) %c %d (%s) = %d (%s)\n",
                decimal1, roman1, operation, decimal2, roman2, result, resultWords);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion and calculations complete. Check Output.txt\n");
    return 0;
}
