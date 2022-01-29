#include "test.h"
#include <iostream>
#include <float.h>
#include <random>
#include <ctime>
#include <limits>
#include <chrono>
#include "DivideAndConquer2D.h"
Test::Test()
{

}

/********************************************************************************************
User inputs.
*********************************************************************************************/

//Enter input size up to 20000 to run:
int g = 20000;


//Enter number of trials
int trials = 10;

/********************************************************************************************
Struct, function and array declarations.
*********************************************************************************************/




Point2D<double> P[20000];


void Test::testAll() {
    //Array declarations
    
    //Fill array P with random values.
    // Note: rand() + rand() used instead of just rand() to increase the likelihood that
    //  the arrays will have distinct values.
    // Note: It is important to generate a new set of random numbers for each trial in
    //  order to test the algorithms' run times on different inputs.

    for (int j = 0; j < g; j++)
    {
        P[j].x = (unsigned int)(rand() + rand() - 1);
        P[j].y = (unsigned int)(rand() + rand() - 1);
    }
    //Heading for output
    std::cout << std::endl << "Results:" << std::endl << std::endl << "# Elements\t\tRun Time\t\tTrials" << std::endl;
    Test::testBruce();
    Test::testDivideAndConquer2D();
}

/********************************************************************************************
Simulation and running time measurements.
*********************************************************************************************/
void Test::testBruce()
{
    

    //Initialize seed for random number generator
    srand(time(NULL));
    int sumTime = 0; //Will be used to calculate the average
    int i1, i2;
    double dst;
    //Loop to run multiple trials
    for (int i = 0; i < trials; i++)
    {
        

        //Store startTime of algorithm execution
        auto startTime = std::chrono::high_resolution_clock::now();

        //Execute algorithm

        std::tie(i1,i2,dst)=bruteForce(P, g);


        std::cout << i1 << "\t\t\t" << i2 << "\t\t\t\t" << dst << std::endl;
        //Store finishTime of algorithm execution and calculate runTime
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto runTime = finishTime - startTime; //Execution time
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(runTime).count();

        sumTime += microseconds; //When loop exits, this will be the sum of all the trials
    }

    //Calculate average run time over all trials
    int averageTime = sumTime / trials;
    
    //Output results
    std::cout << g << "\t\t\t" << averageTime << "\t\t\t\t" << trials << std::endl;

}

void Test::testDivideAndConquer2D()

{

    //Initialize seed for random number generator
    srand(time(NULL));

    

    int sumTime = 0; //Will be used to calculate the average
    int i1, i2;
    double dst;
    //Loop to run multiple trials
    for (int i = 0; i < trials; i++)
    {


        //Store startTime of algorithm execution
        auto startTime = std::chrono::high_resolution_clock::now();
        DivideAndConquer2D<Point2D<double>> divide(P, g);
        std::tie(i1, i2, dst)= divide.closestPair();

        std::cout << i1 << "\t\t\t" << i2 << "\t\t\t\t" << dst << std::endl;
        //Store finishTime of algorithm execution and calculate runTime
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto runTime = finishTime - startTime; //Execution time
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(runTime).count();

        sumTime += microseconds; //When loop exits, this will be the sum of all the trials
    }

    //Calculate average run time over all trials
    int averageTime = sumTime / trials;

    //Output results
    std::cout << g << "\t\t\t" << averageTime << "\t\t\t\t" << trials << std::endl;

}








