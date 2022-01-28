#include "test.h"
#include <iostream>
#include <float.h>
#include <random>
#include <ctime>
#include <limits>
#include <chrono>
#include "DivideAndConquer2D.h"
using namespace std;
Test::Test()
{

}

/********************************************************************************************
User inputs.
*********************************************************************************************/

//Enter input size up to 20000 to run:
int g = 20000;


//Enter number of trials
int trials = 20;

/********************************************************************************************
Struct, function and array declarations.
*********************************************************************************************/









/********************************************************************************************
Simulation and running time measurements.
*********************************************************************************************/
void Test::testBruce()
{
    //Array declarations
    Point2D<double> P[20000];

    //Initialize seed for random number generator
    srand(time(NULL));

    //Heading for output
    cout << endl << "Results:" << endl << endl << "# Elements\t\tRun Time\t\tTrials" << endl;

    int sumTime = 0; //Will be used to calculate the average

    //Loop to run multiple trials
    for (int i = 0; i < trials; i++)
    {
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

        //Store startTime of algorithm execution
        auto startTime = std::chrono::high_resolution_clock::now();

        //Execute algorithm

        bruteForce(P, g);



        //Store finishTime of algorithm execution and calculate runTime
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto runTime = finishTime - startTime; //Execution time
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(runTime).count();

        sumTime += microseconds; //When loop exits, this will be the sum of all the trials
    }

    //Calculate average run time over all trials
    int averageTime = sumTime / trials;

    //Output results
    cout << g << "\t\t\t" << averageTime << "\t\t\t\t" << trials << endl;

}

void Test::testDivideAndConquer2D()

{
    //Array declarations
    Point2D<double> P[20000];

    //Initialize seed for random number generator
    srand(time(NULL));

    //Heading for output
    cout << endl << "Results:" << endl << endl << "# Elements\t\tRun Time\t\tTrials" << endl;

    int sumTime = 0; //Will be used to calculate the average

    //Loop to run multiple trials
    for (int i = 0; i < trials; i++)
    {
        //Fill array P with random values.
        // Note: rand() + rand() used instead of just rand() to increase the likelihood that
        //  the arrays will have distinct values.
        // Note: It is important to generate a new set of random numbers for each trial in
        //  order to test the algorithms' run times on different inputs.
        for (int j = 0; j < g; j++)
        {
            P[j].x = (double)(rand() + rand() - 1);
            P[j].y = (double)(rand() + rand() - 1);
        }

        //Store startTime of algorithm execution
        auto startTime = std::chrono::high_resolution_clock::now();


        DivideAndConquer2D<Point2D<double>>::closestPair(P, g);


        //Store finishTime of algorithm execution and calculate runTime
        auto finishTime = std::chrono::high_resolution_clock::now();
        auto runTime = finishTime - startTime; //Execution time
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(runTime).count();

        sumTime += microseconds; //When loop exits, this will be the sum of all the trials
    }

    //Calculate average run time over all trials
    int averageTime = sumTime / trials;

    //Output results
    cout << g << "\t\t\t" << averageTime << "\t\t\t\t" << trials << endl;

}








