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

    //paieskos URL
    string line_url;
    set<string> urls;

    regex urlPattern("(https?://|www\\.|[a-zA-Z0-9-]+\\.[a-zA-Z]{2,})([\\w-./?%&=]*)");

    // Nuskaityti eilutes iš failo
    while (getline(inputFile2, line_url)) {
        // Paieška pagal reguliariąją išraišką
        auto wordsBegin = sregex_iterator(line_url.begin(), line_url.end(), urlPattern);
        auto wordsEnd = sregex_iterator();

        // Surasti visus URL šioje eilutėje ir įdėti į vektorių
        for (sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
            urls.insert(i->str());
        }
    }

    // Išvedame URL į ekraną ir į failą
    if (!urls.empty()) {
    for (const string& url : urls) {
        outputFile3 << url << endl;  // Tik išvedame į failą
    }
     }else {
       outputFile3 << "Nepavyko rasti URL.\n";  // Jei nerandame URL, išvedame klaidos žinutę
     }

     cout << "URL adresai issaugoti faile urls.txt" << endl;

    inputFile.close();
    inputFile2.close();
    outputFile.close();
    outputFile2.close();
    outputFile3.close();

    return 0;
}
