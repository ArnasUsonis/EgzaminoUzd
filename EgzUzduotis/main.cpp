#include "header.h"

int main(){
    ifstream inputFile("tekstas.txt"); // Failas su tekstu
    ifstream inputFile2("tekstas_URL.txt"); //Url Failas
    ofstream outputFile("pasikartojantys_zodziai.txt"); // Rezultatų failas
    ofstream outputFile2("cross_reference.txt"); // Cross-reference rezultatai
    ofstream outputFile3("urls.txt"); // urlai

    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo tekstas.txt" << endl;
        return 1;
    }

    map<string, int> wordCount; // Saugo žodžių pasikartojimo skaičių
    map<string, set<int>> wordLocations; // Saugo žodžių paminėjimo vietas (galima set pakeisti vector jei norima ziureti kiek kartu tuoje pacioje eiluteje pasikorta)
    string line, word;

    int lineNumber = 1; // Eilutės numeris

    // Nuskaityti eilutes iš failo
    while (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> word) {
            keepAlphaNumeric(word); // kad pasalintu - ir skyrybos zenklus
            if (!word.empty()) {
                wordCount[word]++; // Skaičiuojame, kiek kartų žodis pasikartoja
                wordLocations[word].insert(lineNumber); // Saugo eilutės numerį, kur pasirodė žodis
            }
        }
        lineNumber++; // pereiname prie kitos eilutes
    }

    // Filtruoti žodžius, kurie pasikartojo daugiau nei vieną kartą
    for (const auto& [key, value] : wordCount) {
        if (value > 1) {
            outputFile << key << ": " << value << "\n";
        }
    }

    cout << "Rezultatai issaugoti faile pasikartojantys_zodziai.txt" << endl;

    // Išvedame cross-reference lentelę
    for (const auto& [key, locations] : wordLocations) {
        if (wordCount[key] > 1) { // Tik tie žodžiai, kurie pasikartojo
            outputFile2 << key << ": ";
            for (const int& lineNum : locations) {
                outputFile2 << lineNum << " "; // Eilutės numeriai, kur pasirodė žodis
            }
            outputFile2 << "\n";
        }
    }

    cout << "Cross-reference lentele issaugota faile cross_reference.txt" << endl;

    inputFile.close();
    inputFile2.close();
    outputFile.close();
    outputFile2.close();
    outputFile3.close();

    return 0;
}
