#include <iostream>
#include <unistd.h>
using namespace std;

void OddOrEven(int array[], int size)
{
    int sum_even = 0;
    int sum_odd = 0;
  
    if(fork() == 0)
    {
        for (int i = 0; i < size; ++i)
        {
            if(array[i] % 2 != 0)
            {
                sum_odd = array[i] + sum_odd;
            }
        }
        cout << sum_odd;
    }
    else 
    {
        for(int i = 0; i < size; ++i)
        {
            if(array[i] % 2 == 0)
            {
                sum_even = array[i] + sum_even;
            }
        }
        cout << sum_even;
    }
}



int main()
{
    int size;
    const int array_size = size;
    cin >> size;
    int array[array_size];
    for(int i = 0; i < array_size; ++i)
    {
        array[i] = rand() % 100;
    }

    OddOrEven(array, array_size);
}
