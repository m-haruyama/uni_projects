/* -----------------------------------------------
       Submitted by: Milan Haruyama
       Homework number: FINAL PROJECT
       Credit to: Professor Behi

       Submitted On: 24 November 2020

       By submitting this program with my name,
       I affirm that the creation and modification
       of this program is primarily my own work.
 ------------------------------------------------ */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ASCII_A 65 //ID for capital A in ASCII
#define ASTEROID_NUMBER 10 //number of asteroids that the program will work with
#define ASTEROID_VELOCITY 25 //velocity in kilometers per second
#define GRAPH_LENGTH 110 //length of the graph's borders
#define GRAPH_SCALE 125 //scale that each asterisk on the graph represents
#define MAX 1000 //maximum for the random number generator
#define MIN 1 //minimum for the random number generator
#define NAME_LENGTH 30 //max length for any given name
#define PEOPLE 10 //number of people

 //A spaceship is navigating an asteroid field; you are to design a system that will log and display the distance between the spaceship and the asteroids.
 //Each asteroid has (x, y, z) position in space, where x, y, and z are the distances in kilometers (east-west, north-south, up-down) from the spaceship, which is at (0,0,0).
 //This program will read a file asteroids.txt that represents the ID and location of each asteroid.
 //The distance between the spaceship and each asteroid is calculated based on the asteroid's (x, y, z) position using the following formula: sqrt(x^2 + y^2 + z^2).
 //The program will be secure. The user must input their name and pin number, if both (name and pin) matches the list you have in a text file on the disk (ident.txt),
 //then the user gets access to this program. The program should allow 3 tries for name and password entry,
 //if unsuccessful after 3 tries the program should print a message to the user and terminate.

struct Asteroid //creates a structure called "Asteroid"
{
    int position[3]; //the position of an asteroid
    char *ID; //pointer used to represent the ID of an asteroid
    double distance; //the distance of an asteroid to the spacecraft
    double timeToImpact; //the time the asteroid has to impact the spacecraft
};

struct Identity
{
    char *name[NAME_LENGTH]; //pointer used to represent a name
    int PIN; //integer used to represent a PIN
};

//the following functions will be listed in order of appearance in the program
void scanIdentity(struct Identity *); //scans the identities of the crewmates
void takeUserInfo(struct Identity *); //takes the user's inputs
bool testInput(struct Identity *ptr1, struct Identity *ptr2); //tests the user's inputs against the predetermined crewmate credentials
int randomInteger(void); //generates a random integer
double calculateDistance(int x, int y, int z); //calculates the distance formula using the inputs x, y, and z
double calculateTimeToImpact(double distance); //calculates the time to impact for an asteroid
void generateAsteroidPositions(void); //calculates the void function generateAsteroidPositions
void readPositions(struct Asteroid *); //reads the positions of each asteroid using a pointer as an input
void writeDistances(struct Asteroid *); //writes the distances and positions of the asteroids using a pointer as an input
void impactAlarm(struct Asteroid *); //creates an alarm for imminent impact with an asteroid using a pointer as an input
void asteroidDistancesGraph(struct Asteroid astrdArray[]); //creates a graph of the asteroid distances using an array as an input
void sortAsteroidDistances(struct Asteroid astrdArray[]); //sorts the asteroids based on closest distance using an array as an input
void rankAsteroidDsitances(struct Asteroid astrdArray[]); //ranks the asteroids after being sorted using an array as an input

int main(void)
{
    printf("Milan Haruyama \n\n"); //prints my name
    struct Identity people[PEOPLE], inputPerson[1]; //creates the array of structures "people" and "inputPerson"
    struct Identity *ppl, *input; //creates the pointer "ppl" and "input"
    ppl = people; //sets the pointer "ppl" equal to the array of structures "people"
    input = inputPerson; //sets the pointer "input" equal to the array of structures "inputPerson"
    int i, attempts = 0; //integer "i" is used for loops; integer "attempts" is used for number of attempts performed by the user
    bool accessGranted = 0; //boolean that determines that user's status of having access granted
    scanIdentity(ppl); //scans the identities of the crew using the pointer "ppl" as an input for the function
    printf("This program is locked. \n"); //Tells the user that the safe is locked
    printf("Please enter your name and PIN. Capitalize your name. "); //Asks the user to input a code to open the safe
    takeUserInfo(input); //takes the user's inputs, using the pointer "input" as a variable for the the function
    for (i = 0; i < PEOPLE; i++) //loops the code below for the value of "PEOPLE"
    {
        if (testInput(input, ppl) == 1) //if the user's inputs match the pre-determined crewmate credentials, the program will perform the code below
        {
            i = PEOPLE; //sets i equal to "PEOPLE", which stops the loop; allows avoidance of using "break;"
            accessGranted = 1; //access has been granted
            printf("\n"); //prints a new line
            printf("Access granted! Welcome back, %s. \n\n", &input->name);
            struct Asteroid asteroid[10]; //creates an array of structures called "asteroid"
            struct Asteroid *astrd = asteroid; //creates a pointer to the array of structures "asteroid"
            generateAsteroidPositions(); //calls the function
            readPositions(astrd); //calls the function using the pointer astrd as an input
            writeDistances(astrd); //calls the function using the pointer astrd as an input
            impactAlarm(astrd); //calls the function using the pointer astrd as an input
            asteroidDistancesGraph(astrd); //calls the function using the pointer astrd as an input
            sortAsteroidDistances(astrd); //calls the function using the pointer astrd as an input
            rankAsteroidDsitances(astrd); //calls the function using the pointer astrd as an input
        }
        ppl++; //moves on to the next pointer
    }

    if (!accessGranted) //if access has not been granted, the program will perform the code below
    {
        attempts++; //number of attempts goes up by one
        printf("\n"); //prints a new line
        do //performs the code below at least once, then performs it again if certain criteria are ,et
        {
            ppl = people; //resets the pointer
            printf("Credentials not recognized by the system. Access denied! Please try again. "); //tells the user that their credentials are incorrect and asks for new ones
            takeUserInfo(input); //takes the user's inputs, using the pointer "input" as a variable for the the function
            for (i = 0; i < PEOPLE; i++) //loops the code below for the value of "PEOPLE"
            {
                if (testInput(input, ppl) == 1) //if the user's inputs match the pre-determined crewmate credentials, the program will perform the code below
                {
                    i = PEOPLE; //sets i equal to "PEOPLE", which stops the loop; allows avoidance of using "break;"
                    accessGranted = 1; //access has been granted
                    printf("\n"); //prints a new line
                    printf("Access granted! Welcome back, %s. \n\n", &input->name);
                    struct Asteroid asteroid[10]; //creates an array of structures called "asteroid"
                    struct Asteroid *astrd = asteroid; //creates a pointer to the array of structures "asteroid"
                    generateAsteroidPositions(); //calls the function
                    readPositions(astrd); //calls the function using the pointer astrd as an input
                    writeDistances(astrd); //calls the function using the pointer astrd as an input
                    impactAlarm(astrd); //calls the function using the pointer astrd as an input
                    asteroidDistancesGraph(astrd); //calls the function using the pointer astrd as an input
                    sortAsteroidDistances(astrd); //calls the function using the pointer astrd as an input
                    rankAsteroidDsitances(astrd); //calls the function using the pointer astrd as an input
                }
                ppl++; //moves on to the next pointer
            }
            attempts++; //number of attempts goes up by one
        }while((!accessGranted) && (attempts < 3)); //while access has not been granted and the number of attempts is below 3, the program loops the code above
        if ((!accessGranted) && (attempts = 3))
        {
            printf("You have exceeded the maximum number of attempts (3). Goodbye! \n"); //tells the user they've been locked out of the system
        }
    }

    return 0; //ends the program
}

void scanIdentity(struct Identity *ptr) //scans the identities of the crewmates
{
    FILE *identityRead = fopen("ident.txt", "r"); //file pointer that opens and reads the file "ident.txt"
    int i; //integer "i" is used for loops
    for (i = 0; i < PEOPLE; i++) //loops the code below for the value of "PEOPLE"
    {
        fscanf(identityRead, "%s %d", &ptr->name, &ptr->PIN); //scans the contents of "ident.txt" in search of strings and integers
        ptr++; //moves on to the next pointer
    }
    fclose(identityRead); //closes the text file "ident.txt"
}

void takeUserInfo(struct Identity *ptr) //takes the user's inputs
{
    scanf("%s %d", &ptr->name, &ptr->PIN); //sets the user's input as pointers for name and pin
}

bool testInput(struct Identity *ptr1, struct Identity *ptr2) //tests the user's inputs against the predetermined crewmate credentials
{
    bool correct = 0; //boolean used to determine if the user's input is correct or not
    if ((strcmp(ptr1->name, ptr2->name) == 0) && (ptr1->PIN == ptr2->PIN)) //if the input matches any one of the 10 predetermined credentials
    {
        correct = 1; //credentials are correct
    }
    return correct; //returns whether or not the credentials are correct
}

int randomInteger(void) //generates a random integer
{
    int randomInt; //integer for a randomly generated integer
    randomInt = MIN + rand() % MAX; //sets "randomInt" equal to a random integer between 1 and 1000
    return randomInt; //returns the value of "randomInt"
}

double calculateDistance(int x, int y, int z) //calculates the distance formula using the inputs x, y, and z
{
    double distance; //double for a calculated distance
    distance = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); //calculation of distance
    return distance; //returns calculated value
}

double calculateTimeToImpact(double distance) //calculates the time to impact for an asteroid
{
    double timeToImpact; //double for a calculated time to impact
    int y = ASTEROID_VELOCITY; //integer "y" is equal to the asteroid's velocity
    timeToImpact = distance / y; //calculation of time to impact
    return timeToImpact; //returns calculated value
}

void generateAsteroidPositions(void) //generates a random position for each asteroid
{
    FILE* asteroidWrite = fopen("asteroid.txt", "w"); //file pointer that writes a file called "asteroid.txt"
    int i, j, x, y, z; //declares the integers i and j
    srand(time(NULL)); //uses the current time as a seed for a random value
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops 10 times
    {
        for (j = 0; j < 3; j++) //loops 3 times
        {
            switch (j) //switch statement based off the value of the integer "j"
            {
                case 0: //when j = 1
                    {
                        x = randomInteger(); //generates a random integer for the x coordinate
                        break; //returns back to the loop
                    }
                case 1: //when j = 2;
                    {
                        y = randomInteger(); //generates a random integer for the y coordinate
                        break; //returns back to the loop
                    }
                case 2: //when j = 3
                    {
                        z = randomInteger(); //generates a random integer for the z coordinate
                        break; //returns back to the loop
                    }
            }
        }
        //creates a text file called "asteroid.txt" and puts all of the asteroid data onto it
        fprintf(asteroidWrite, "%c %d %d %d \n", i + ASCII_A, x, y, z); //prints the ID and (x, y, z) coordinates of an asteroid
    }
    fclose(asteroidWrite); //closes the file "asteroid.txt"
}

void readPositions(struct Asteroid *ptr) //reads the positions of each asteroid using a pointer as an input
{
    FILE*asteroidRead = fopen("asteroid.txt", "r"); //file pointer that reads from a file called "asteroid.txt"
    int i;
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops for the value of "ASTEROID_NUMBER"
    {
        fscanf(asteroidRead, "%s %d %d %d", &ptr->ID, &ptr->position[0], &ptr->position[1], &ptr->position[2]); //scans for a string and three integers, corresponding to the ID and (x, y, z) coordinates of an asteroid
        ptr++; //moves on to the next pointer
    }
    fclose(asteroidRead); //closes the file "asteroid.txt"
}

void writeDistances(struct Asteroid *ptr) //writes the distances and positions of the asteroids using a pointer as an input
{
    FILE* distanceWrite = fopen("distance.txt", "w"); //file pointer that opens a file called "distance.txt"
    int i;
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops for the value of "ASTEROID_NUMBER"
    {
        ptr->distance = calculateDistance(ptr->position[0], ptr->position[1], ptr->position[2]); //calls the function calculateDistance using the coordinates of each asteroid as inputs
        //opens a file called "distance.txt"
        fprintf(distanceWrite, "%s %d %d %d %.2f \n", &ptr->ID, ptr->position[0], ptr->position[1], ptr->position[2], ptr->distance); //prints the ID and (x, y, z) coordinates of an asteroid onto the file "distance.txt"
        ptr++; //moves onto the next pointer
    }
    fclose(distanceWrite); //closes the file "distance.txt"
}

void impactAlarm(struct Asteroid *ptr) //creates an alarm for imminent impact with an asteroid using a pointer as an input
{
    int i;
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops for the value of "ASTEROID_NUMBER"
    {
         if (ptr->distance < 750) //if the distance from an asteroid to the spacecraft is less than 750 km, the program will run the code below
         {
             ptr->timeToImpact = calculateTimeToImpact(ptr->distance); //calculates the time of impact of the asteroid selected
             printf("Alert!!! Asteroid %s is %.2f kilometers away! Time to impact is %.2f seconds! Immediate course of action is required! \n", &ptr->ID, ptr->distance, ptr->timeToImpact);
             //prints an alert containing the distance and time of impact of an asteroid
         }
         ptr++; //moves onto the next function
    }
    printf("\n \n"); //prints two new lines
}

void asteroidDistancesGraph(struct Asteroid astrdArray[]) //creates a graph of the asteroid distances using an array as an input
{
    int i, j;
    int asterisks; //represents number of asterisks to be used
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops for the value of "ASTEROID_NUMBER"
    {
        asterisks = astrdArray[i].distance / GRAPH_SCALE; //the number of asterisks used will be calculated by dividing the distance of an asteroid by the graph scale
        printf("\t %s|", &astrdArray[i].ID); //prints the ID followed by a separating bar
        for (j = 0; j < asterisks; j++) //loops for the number of asterisks needed to scale the distance
        {
            printf("\t *"); //prints a table and an asterisk
        }
        printf("\n \t"); //prints a new line and a table
        for (j = 0; j < GRAPH_LENGTH; j++) //loops for the value of "GRAPH_LENGTH"
        {
            printf("="); //prints an equal sign, used to box the graph
        }
        printf("\n"); //prints a new line
    }
    printf("\t 0 \t 125 \t 250 \t 375 \t 500 \t 625 \t 750 \t 875 \t 1000 \t 1125 \t 1250 \t 1375 \t 1500 \t 1750 \n"); //prints the graph markers, using a scale of 0 - 1750 with increments of 125 kilometers
    printf ("\t Scale of distances in kilometers \n \n"); //prints the scale of distances
}

void sortAsteroidDistances(struct Asteroid astrdArray[]) //sorts the asteroids based on closest distance using an array as an input
{
    struct Asteroid temp; //a temporary variable
    for (int i = 0; i < ASTEROID_NUMBER - 1; i++) //loops for "ASTEROID_NUMBER" minus 1
    {
        for (int j = 0; j < (ASTEROID_NUMBER - 1 - i); j++) //loops for "ASTEROID_NUMBER" minus 1 minus "i"
        {
            if (astrdArray[j].distance > astrdArray[j + 1].distance) //if the distance of an asteroid is greater than the distance of the next asteroid, the program will run the code below
            {
                temp = astrdArray[j]; //sets the temporary variable equal to the first asteroid distance
                astrdArray[j] = astrdArray[j + 1]; //sets the first asteroid distance equal to the next asteroid distance
                astrdArray[j + 1] = temp; //sets the asteroid distance next in line from the first one used as the temporary variable, thus setting it equal to the first distance (a little wordy, I know)
                //in short, this if statement will flip the order of two distances, making the smaller distance one tier lower than the greater distance
                //i.e. if distance #1 equals 750 kilometers and distance #2 equals 500 kilometers, this bit of code will make distance #1 500 and distance #2 750
            }
        }
    }
}

void rankAsteroidDsitances(struct Asteroid astrdArray[]) //ranks the asteroids after being sorted using an array as an input
{
    int i;
    printf("Asteroid ranking by closest distance: \n"); //prints the heading for the asteroid rankings
    for (i = 0; i < ASTEROID_NUMBER; i++) //loops for the value of "ASTEROID_NUMBER"
    {
        printf("Asteroid %s: %.2f kilometers away. \n", &astrdArray[i].ID, astrdArray[i].distance); //prints the asteroids ranked on distance, with the smallest being closest to the top
    }
}
