#include "header.h"

int main(){
    ifstream inputFile("tekstas.txt"); // Failas su tekstu
    ofstream outputFile("pasikartojantys_zodziai.txt"); // Rezultatų failas

    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo tekstas.txt" << endl;
        return 1;
    }

    map<string, int> wordCount;
    string line, word;

    // Nuskaityti eilutes iš failo
    while (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> word) {
            removePunctuation(word); // Pašalinti skyrybos ženklus
            if (!word.empty()) {
                wordCount[word]++;
            }
        }
    }

    // Filtruoti žodžius, kurie pasikartojo daugiau nei vieną kartą
    for (const auto& [key, value] : wordCount) {
        if (value > 1) {
            outputFile << key << ": " << value << "\n";
        }
    }

    cout << "Rezultatai issaugoti faile pasikartojantys_zodziai.txt" << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
