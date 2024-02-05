// Author: Milan Haruyama
// Instructor: Dr. Laxima Nuire Kandel
// Due Date: 28 April 2022

// This program will prompt the user to either encrypt or decrypt a message.
// This program will read any key written in a text file called "key.txt"
// This program will encrypt any plaintext written in a text file called "plain.txt" 
// so long as the key is larger than the plaintext.
// An example "plain.txt" and "key.txt" will be provided for the user.
// This program will create a text file called "cipher.txt" that contains the encrypted plaintext.
// This program will decrypt any ciphertext written in a text file called "cipher.txt" 
// so long as the key is larger than the ciphertext.
// This program will create a text file called "msg.txt" that contains the decrypted ciphertext.
// If the user uses an invalid input, the program will automatically end and prompt the user to try again.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct component // component of the encryption scheme (key, plaintext, ciphertext)
{
    int * ptr; // used to store array of bytes (integers)
    int length; // used to store length of component
};

struct component key(); // function that returns key from text file if it exists
struct component plaintext(); // function that returns plaintext from text file if it exists
struct component ciphertext(); // function that returns ciphertext from text file if it exists
int enc(); // encryption function that returns an integer based upon success of operation
int dec(); // decryption function that returns an integer based upon success of operation
int findPrime(); // finds the largest prime number factor of an integer

int main() // serves as a menu for the user to use; heavy labor is performed by previous functions
{
    int input;
    do
    {
        printf("Please select an option below (Integer only): \n");
        printf("0.) Exit the program. \n");
        printf("1.) Encrypt a plaintext. \n");
        printf("2.) Decrypt a ciphertext. \n");
        scanf("%1d.)", &input);
        if(input > 2)
        {
            printf("Invalid input. Please run the program again. \n");
            break;
        }
        switch (input)
        {
            case 0:
                printf("Goodbye! \n\n");
                break;
            
            case 1:
                switch (enc() )
                {
                    case 0:
                        printf("Encryption was successful! \n\n");
                        break;

                    case -1:
                        printf("plain.txt is missing! Please try again. \n\n");
                        break;
                    
                    case -2:
                        printf("key.txt is missing! Please try again. \n\n");
                        break;

                    case -3:
                        printf("key.txt is too small! Please try again. \n\n");
                        break;
                }
                break;

            case 2:
                switch (dec() )
                {
                    case 0:
                        printf("Decryption was succsessful! \n\n");
                        break;
                    
                    case -1:
                        printf("cipher.txt is missing! Please try again \n\n");
                        break;

                    case -2:
                        printf("key.txt is missing! Please try again. \n\n");
                        break;
                    
                    case -3:
                        printf("key.txt is too small! Please try again. \n\n");
                        break;
                }
                break;
        }
    } while (input); // while input integer is greater than 0 and less than 4, continue displaying the options menu

    return 0;
}

int findPrime(int num) // found on: https://www.tutorialgateway.org/c-program-to-find-prime-factors-of-a-number/
{
    int isPrime = 0, prime = 2;
    for (int i = 2; i <= num; i++)
    {
        if(num % i == 0)
        {
            isPrime = 1;
            for (int j = 2; j <= i/2; j++)
            {
                if(i % j == 0)
                {
                    isPrime = 0;
                    break;
                }
            }

            if(isPrime == 1)
                prime = i;
        }
    }
    return prime;
}

struct component key() // returns key or NULL based upon success of operation
{
    struct component key;
    key.ptr = NULL; // key.txt does not exist
    FILE * keyFile = fopen("key.txt", "r");
    if (keyFile) // if key.txt exists
    {
        char ch = fgetc(keyFile);
        int length; // length can be even or odd
        
        for(length = 0; !feof(keyFile); length++)
            ch = fgetc(keyFile);

        rewind(keyFile);
        key.ptr = (int *) malloc(length * sizeof(int)); // creates an array of integers
        key.length = length;
        
        for(int i = 0; i < length; i ++)
            key.ptr[i] = fgetc(keyFile);
    }
    fclose(keyFile);

    return key;
}

struct component plaintext() // returns plaintext or NULL based upon success of operation
{
    struct component plain;
    plain.ptr = NULL; // plain.txt does not exist
    FILE * plainFile = fopen("plain.txt", "r");
    if (plainFile) // if plain.txt exists
    {
        char ch = fgetc(plainFile);
        int length; // length must always be even

        for(length = 0; !feof(plainFile); length++)
            ch = fgetc(plainFile);
        rewind(plainFile);
        
        if(length % 2) // if length is odd, append 9 extra bytes from the string "odd"
        {
            char * append = "oddoddodd"; // string to append to the plaintext
            int i, j;
            length += 9;
            plain.ptr = (int *) malloc(length * sizeof(int)); // creates an array of integers
            for(i = 0; i < length - 9; i++) // adds the integer value of each character to the array
                plain.ptr[i] = fgetc(plainFile);

            for (j = 0; j < 9; j++) // hard codes the bytes of the string "oddoddodd" into the plaintext array
                plain.ptr[i + j] = append[j];
        }

        else // length is even
        {
            plain.ptr = (int *) malloc(length * sizeof(int)); // creates an array of integers
            for(int i = 0; i < length; i++) // adds the integer value of each character to the array
                plain.ptr[i] = fgetc(plainFile);
        }
        plain.length = length;
    }
    fclose(plainFile);

    return plain;
}

struct component ciphertext()
{
    struct component cipher;
    cipher.ptr = NULL; // cipher.txt does not exist
    FILE * cipherFile = fopen("cipher.txt", "r");
    if (cipherFile)
    {
        int byte = 0;
        int length;

        fscanf(cipherFile, "%d", &byte);
        for(length = 0; !feof(cipherFile); length++) // counts the number of integers in cipher.txt to obtain length
            fscanf(cipherFile, "%d", &byte);
        rewind(cipherFile);

        cipher.ptr = (int *) malloc(length * sizeof(int)); // creates an array of integers
        cipher.length = length;

        for(int i = 0; i < length; i++) // adds the integers to the array
        {
            fscanf(cipherFile, "%d", &byte);
            cipher.ptr[i] = byte;
        }
    }
    fclose(cipherFile);

    return cipher;
}

int enc()
{
    int success = -1;
    struct component plain = plaintext();
    if (plain.ptr) // if plain.txt exists
    {
        success = -2; // key.txt does not exist
        struct component k = key();
        if (k.ptr) // if key.txt exists
        {
            success = -3; // key.txt is too small
            if(k.length > plain.length) // if key.txt is larger than plain.txt
            {
                char ch = 0;
                int length = plain.length;
                int n = findPrime(length); // n = segment length (in bytes)
                int m = length/n; // m = # of segments
                int segments[n][m], a = 0;

                // breaks up plaintext into segments
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        segments[j][i] = plain.ptr[a];
                        a++;
                    }
                }

                // below is where the magic happens //
                struct component cipher;
                FILE * cipherFile = fopen("cipher.txt", "w");

                //XORs each segment with the key
                cipher.ptr = (int *) malloc(length*sizeof(int));
                cipher.length = length;
                a = 0;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        cipher.ptr[a] = (segments[j][i] ^ k.ptr[i]);
                        a++;
                    }
                }
                a = 0;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        cipher.ptr[a] ^= k.ptr[k.length - a - 1];
                        fprintf(cipherFile, "%d ", cipher.ptr[a]);
                        a++;
                    }
                }
                fclose(cipherFile);
                success = 0; //successful encryption
            }
        }
    }

    return success;     // success = 0: successful encryption
}                       // success = -1: missing plain.txt
                        // success = -2: missing key.txt
                        // success = -3; key.txt is too small

int dec()
{
    int success = -1; // cipher.txt does not exist
    struct component cipher = ciphertext();
    if (cipher.ptr) // if cipher.txt exists
    {
        struct component k = key();
        success = -2; // key.txt does not exist
        if (k.ptr) // if key.txt exists
        {
            success = -3; // key.txt is too big
            if(k.length > cipher.length) // if key.txt is larger than cipher.txt
            {
                char append[10];
                int length = cipher.length;
                int n = findPrime(length); // n = segment length (in bytes)
                int m = length/n; // m = # of segments
                int segments[n][m], a = 0;

                // breaks up plaintext into segments
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        segments[j][i] = cipher.ptr[a];
                        a++;
                    }
                }

                struct component msg;
                msg.ptr = (int *) malloc(length*sizeof(int));
                msg.length = length;
                FILE * msgFile = fopen("msg.txt", "w");
                a = 0;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        msg.ptr[a] = (segments[j][i] ^ k.ptr[k.length - a - 1]);
                        a++;
                    }
                }
                a = 0;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        msg.ptr[a] ^= k.ptr[i];
                        a++;
                    }
                }

                //reads the last characters of the plaintext
                for(int i = 0; i < 9; i++)
                    append[i] = msg.ptr[length - 9 + i];
                append[10] = '\0'; //adds a null terminator

                //if the last nine characters are "oddoddodd", subtract 9 from length
                if (!strcmp(append, "oddoddodd"))
                    length -= 9;
                
                //prints the plaintext onto msg.txt
                for (int i = 0; i < length; i++)
                    fprintf(msgFile, "%c", msg.ptr[i]);

                fclose(msgFile);
                success = 0; //successful decryption
            }
        }
    }
    
    return success; // success = 0: successful decryption
}                   // success = -1: missing cipher.txt
                    // success = -2: missing key.txt
                    // success = -3; key.text is too small
    
    