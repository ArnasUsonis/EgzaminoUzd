#include "header.h"

int main(){
    ifstream inputFile("tekstas.txt"); // Failas su tekstu
    ifstream inputFile2("tekstas_URL.txt"); //Url Failas
    ofstream outputFile("pasikartojantys_zodziai.txt"); // Rezultatu failas
    ofstream outputFile2("cross_reference.txt"); // Cross-reference rezultatai
    ofstream outputFile3("urls.txt"); // urlai

    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo tekstas.txt" << endl;
        return 1;
    }
    if (!inputFile2.is_open()) {
        cerr << "Nepavyko atidaryti failo tekstas_URL.txt" << endl;
        return 1;
    }

    map<string, int> ZodzioKiekis; // Saugo zodziu pasikartojimo skaiciu
    map<string, set<int>> zodzioVieta; // Saugo zodziu paminejimo vietas (galima set pakeisti vector jei norima ziureti kiek kartu tuoje pacioje eiluteje pasikorta)
    string line, word;

    int lineNumber = 1; // Eilutes numeris

    // Nuskaityti eilutes iš failo
    while (getline(inputFile, line)) {
        istringstream iss(line);
        while (iss >> word) {
            SkyrybosZenkluIstrynimas(word); // kad pasalintu - ir skyrybos zenklus
            if (!word.empty()) {
                ZodzioKiekis[word]++; // Skaiciuojame, kiek kartu zodis pasikartoja
                zodzioVieta[word].insert(lineNumber); // Saugo eilutes numeri kur pasirode zodis
            }
        }
        lineNumber++; // pereiname prie kitos eilutes
    }

    // Filtruoti zodzius kurie pasikartojo daugiau nei viena karta
    for (const auto& pair : ZodzioKiekis) {
    if (pair.second > 1) {
        outputFile << pair.first << ": " << pair.second << "\n";
    }
  }

    cout << "Rezultatai issaugoti faile pasikartojantys_zodziai.txt" << endl;

    // Isvedame cross-reference lentele
    for (const auto& pair : zodzioVieta) {
    const string& key = pair.first;
    const set<int>& vieta = pair.second;

    if (ZodzioKiekis[key] > 1) { // Tik tie žodžiai, kurie pasikartojo
        outputFile2 << key << ": ";
        for (const int& lineNum : vieta) {
            outputFile2 << lineNum << " "; // Eilutės numeriai
        }
        outputFile2 << "\n";
    }
  }

    cout << "Cross-reference lentele issaugota faile cross_reference.txt" << endl;

    //paieskos URL
    string line_url;
    set<string> urls;

    regex urlPattern("(https?://|www\\.|[a-zA-Z0-9-]+\\.[a-zA-Z]{2,})([\\w-./?%&=]*)"); //regex israiska

    // Nuskaityti eilutes is failo
    while (getline(inputFile2, line_url)) {
        // Paieska pagal reguliariaja israiska
        auto wordsBegin = sregex_iterator(line_url.begin(), line_url.end(), urlPattern);
        auto wordsEnd = sregex_iterator();

        // Surasti visus URL sioje eiluteje ir ideti i vektoriu
        for (sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
            urls.insert(i->str());
        }
    }

    // Isvedame URL i faila
    if (!urls.empty()) {
    for (const string& url : urls) {
        outputFile3 << url << endl;  //isvedame i faila
    }
     }else {
       outputFile3 << "Nepavyko rasti URL.\n";  // Jei nerandame URL, isvedame klaidos zinute
     }

     cout << "URL adresai issaugoti faile urls.txt" << endl;

    inputFile.close();
    inputFile2.close();
    outputFile.close();
    outputFile2.close();
    outputFile3.close();

    system("pause");
    return 0;
}
