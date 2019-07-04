#include <iostream>
#include <string>

#define ZEROS "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
#define ONES "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
#define RANDOM "00101010111010000000001110001001000000100101110101000101011000100000110000100000100100001110100111010101000000001100000111100110"

using namespace std;

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
                n++;
            current += n;
            cout << bit << " : " << n << endl;
            if (current == row.size())
                break;
        }
    }
}

int main()
{
    displayRow("1");
    // displayRow(ZEROS);
    // displayRow(ONES);
    // displayRow(RANDOM);
    return 0;
}