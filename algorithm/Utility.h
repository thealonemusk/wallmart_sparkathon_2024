#include <iostream>
#include <random>

using namespace std;

int getRandomNumber(int start_index, int end_index) {
    std::random_device dev;
    std::mt19937 rng(dev());
    // distribution in range [start_index, end_index]
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start_index,
                                                                   end_index);
    return dist6(rng);
}

string generateRandomName(int length) {
    string possibleChars = "abcdefghijklmnopqrstuvwxyz";

    string name;
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % possibleChars.length();
        name += possibleChars[randomIndex];
    }

    return name;
}
