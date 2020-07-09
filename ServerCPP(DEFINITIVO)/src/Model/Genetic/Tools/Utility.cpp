#include "Utility.h"

int Utility::Random(int pMax)
{
    return Random(0,pMax);
}

int Utility::Random(int pMin, int pMax)
{
//    default_random_engine rng(std::random_device{}());
//    uniform_real_distribution<double> dist(pMin, pMax);  //(min, max)
//    //get one
//    const int random_num = (int) dist(rng);
//    return random_num;

    return (rand() % pMax) + pMin;
}

string Utility::decToBinary(int pDecimal)
{
    // Size of an integer is assumed to be 32 bits
    string result;
    for (int i = 2; i >= 0; i--)
    {
        int k = pDecimal >> i;
        if (k & 1)
            result+="1";
        else
            result+= "0";
    }
    return result;
}

int Utility::binToDec(int pBinary)
{
    int exponencial,digit;
    double decimal;

    exponencial=0;
    decimal=0;
    while(((int)(pBinary / 10)) != 0)
    {
        digit = (int)pBinary % 10;
        decimal = decimal + digit * pow(2, exponencial);
        exponencial++;
        pBinary=(int)(pBinary / 10);
    }
    decimal= decimal + pBinary * pow(2, exponencial);
//    cout << endl << "Decimal: " << decimal << endl;
    return (int)decimal;
}