#include <iostream>
#include <string>
#include <wiringPi.h>

#define PIN5 21
#define PIN6 22
#define PIN13 23
#define PIN19 24

using namespace std;

void setup()
{
    if (wiringPiSetup() < 0)
        exit(1);

    pinMode(PIN5, OUTPUT);
    pinMode(PIN6, OUTPUT);
    pinMode(PIN13, OUTPUT);
    pinMode(PIN19, OUTPUT);
}

void clearAll()
{
    digitalWrite(PIN19, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN13, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN13, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN19, HIGH);
    delayMicroseconds(1);
}

void shiftOnes(int pins)
{
    digitalWrite(PIN19, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN13, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN5, HIGH);
    delayMicroseconds(1);

    for (int i = 0; i < pins; i++)
    {
        digitalWrite(PIN6, HIGH);
        delayMicroseconds(1);
        digitalWrite(PIN6, LOW);
        delayMicroseconds(1);
    }

    digitalWrite(PIN5, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN13, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN13, LOW);
    delayMicroseconds(1);
}

void shiftZeros(int pins)
{
    digitalWrite(PIN19, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN19, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN5, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN13, LOW);
    delayMicroseconds(1);

    for (int i = 0; i < pins; i++)
    {
        digitalWrite(PIN6, HIGH);
        delayMicroseconds(1);
        digitalWrite(PIN6, LOW);
        delayMicroseconds(1);
    }

    digitalWrite(PIN13, HIGH);
    delayMicroseconds(1);
    digitalWrite(PIN13, LOW);
    delayMicroseconds(1);
}

void displayRow(string row)
{
    if (row.size() > 1)
    {
        int current = 0;
        while (true)
        {
            int n = 0;
            char bit = row[current];
            while (bit == row[current + n] && current + n < row.size())
            {
                n++;
            }
            current += n;
            if (bit == '1')
            {
                shiftOnes(n);
            }
            else
            {
                shiftZeros(n);
            }
            if (current == row.size())
            {
                break;
            }
        }
    }
}

int main()
{
    setup();

    while (true)
    {
        clearAll();
        shiftOnes(4);
        for (int i = 0; i < 124; i++)
        {
            shiftZeros(1);
            delay(10);
        }

        for (int i = 124; i > -1; i--)
        {
            clearAll();
            shiftOnes(4);
            shiftZeros(i);
            delay(10);
        }

        clearAll();
        for (int i = 0; i < 8; i++)
        {
            shiftOnes(8);
            shiftZeros(8);
        }
        delay(100);

        clearAll();
        for (int i = 0; i < 8; i++)
        {
            shiftZeros(8);
            shiftOnes(8);
        }
        delay(100);
    }

    return 0;
}
