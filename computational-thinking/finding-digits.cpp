#include <iostream>

int main()
{
    int v;
    int u;
    int a;
    int result = 1;
    int seed = 0;

    while (result != (v + u + a)) {
        srand(seed);

        v = rand() % 10;
        u = rand() % 10;
        a = rand() % 10;

        if (v == 0 || u == 0 || a == 0) {
            seed++;
            continue;
        }

        result = (v * 100) + (u * 10) + a;

        v += v * 10;
        u += u * 10;
        a += a * 10;

        seed++;

        std::cout << v  << " + " << u << " + " << a << " = " << result << std::endl;
    }

    return 0;
}
