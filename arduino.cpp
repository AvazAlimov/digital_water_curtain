#include <SPI.h>
#include <SD.h>

#define _PIN5 5
#define _PIN6 6
#define _PIN13 7
#define _PIN19 8

File myFile;
String buffer;

void setup()
{
    pinMode(_PIN5, OUTPUT);
    pinMode(_PIN6, OUTPUT);
    pinMode(_PIN13, OUTPUT);
    pinMode(_PIN19, OUTPUT);

    Serial.begin(9600);
    while (!Serial)
    {
        ;
    }
    Serial.print("Initializing SD card...");
    if (!SD.begin(4))
    {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
    Serial.println("initialization done.");
}

void clearAll()
{
    digitalWrite(_PIN19, LOW);
    digitalWrite(_PIN13, HIGH);
    digitalWrite(_PIN13, LOW);
    digitalWrite(_PIN19, HIGH);
}

void shiftOnes(int pins)
{
    digitalWrite(_PIN19, HIGH);
    digitalWrite(_PIN13, LOW);
    digitalWrite(_PIN5, HIGH);
    for (int i = 0; i < pins; i++)
    {
        digitalWrite(_PIN6, HIGH);
        digitalWrite(_PIN6, LOW);
    }
    digitalWrite(_PIN5, LOW);
    digitalWrite(_PIN13, HIGH);
    digitalWrite(_PIN13, LOW);
}

void shiftZeros(int pins)
{
    digitalWrite(_PIN19, HIGH);
    digitalWrite(_PIN19, HIGH);
    digitalWrite(_PIN5, LOW);
    digitalWrite(_PIN13, LOW);
    for (int i = 0; i < pins; i++)
    {
        digitalWrite(_PIN6, HIGH);
        digitalWrite(_PIN6, LOW);
    }
    digitalWrite(_PIN13, HIGH);
    digitalWrite(_PIN13, LOW);
}

void alternate(int loops, int size, int delayTime)
{
    for (int loop = 0; loop < loops; loop++)
    {
        clearAll();
        for (int i = 0; i < 64 / size; i++)
        {
            shiftOnes(size);
            shiftZeros(size);
        }
        delay(delayTime);

        clearAll();
        for (int i = 0; i < 64 / size; i++)
        {
            shiftZeros(size);
            shiftOnes(size);
        }
        delay(delayTime);
    }
}

void move(bool forward, int size, int delayTime)
{
    if (forward)
    {
        clearAll();
        shiftOnes(size);
        for (int i = 0; i < 128 - size; i++)
        {
            shiftZeros(1);
            delay(delayTime);
        }
    }
    else
    {
        for (int i = 128 - size; i > -1; i--)
        {
            clearAll();
            shiftOnes(size);
            shiftZeros(i);
            delay(delayTime);
        }
    }
}

void center(bool inverse, int size)
{
    int range = (128 - size) / 2;
    if (!inverse)
    {
        shiftZeros(range);
        shiftOnes(size);
        shiftZeros(range);
    }
    else
    {
        shiftZeros(size);
        shiftOnes(range);
        shiftZeros(size);
    }
}

void displayRow(String row)
{
    if (row.length() > 1)
    {
        int current = 0;
        while (true)
        {
            int n = 0;
            char bit = row.charAt(current);
            while (bit == row.charAt(current + n) && current + n < row.length())
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
            if (current == row.length())
            {
                break;
            }
        }
    }
}

void loop()
{
    myFile = SD.open("data.txt");
    if (myFile)
    {
        while (myFile.available())
        {
            buffer = myFile.readStringUntil('\n');
            clearAll();
            displayRow(String(buffer));
            delay(50);
        }
        myFile.close();
    }
    else
    {
        Serial.println("error opening file");
    }
}