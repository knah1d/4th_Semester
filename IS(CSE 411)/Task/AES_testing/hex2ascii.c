#include <stdio.h>
#include <string.h>

void hexToAscii(const unsigned char* hexString, char* asciiString) {
    int length = strlen((const char*)hexString) / 2; // Length of ASCII string
    
    for (int i = 0; i < length; i++) {
        sscanf((const char*)(hexString + 2 * i), "%2hhx", &asciiString[i]); // Convert two characters at a time
    }
    
    asciiString[length] = '\0'; // Null-terminate the ASCII string
}

int main() {
    unsigned char hexString[33] = "5468697320697320612073696d706c65"; // Example hexadecimal string
    char asciiString[100]; // Buffer to store the ASCII string
    
    // Convert hexadecimal string to ASCII
    hexToAscii(hexString, asciiString);
    
    // Print the result
    printf("Hexadecimal: %s\n", hexString);
    printf("ASCII: %s\n", asciiString);

    return 0;
}
