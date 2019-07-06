#define _PIN5 8
#define _PIN6 9
#define _PIN13 10
#define _PIN19 11

void setup()
{
    pinMode(_PIN5, OUTPUT);
    pinMode(_PIN6, OUTPUT);
    pinMode(_PIN13, OUTPUT);
    pinMode(_PIN19, OUTPUT);
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

void loop()
{
    clearAll();
    for (int i = 2; i <= 128; i += 2)
    {
        center(false, i);
        delay(10);
    }
    clearAll();
    for (int i = 128; i >= 0; i -= 2)
    {
        center(false, i);
        delay(10);
    }

    move(false, 8, 20);
    move(true, 8, 20);
    for (int i = 1; i <= 64; i *= 2)
        alternate(10, i, 100);
}