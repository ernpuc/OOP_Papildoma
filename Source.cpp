#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <regex>

using std::left;
using std::setw;
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::multimap;
using std::string;
using std::less;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::make_pair;
using std::regex;
using std::regex_search;

void pildFailas(multimap< string, int, less< string > >& wordLoc, map< string, int, less< string > >& wordCount);
void printResult(multimap< string, int, less< string > > wordLoc, map< string, int, less< string > > wordCount);
string istrintiZenklus(const std::string& input);

int main()
{
	system("chcp 65001");								//Konsolėje rodomos lietuviškos raidės
	system("cls");
	multimap< string, int, less< string > > wordLoc;	//Žodžiai ir eilutės, kuriose jie pasirodo
	map< string, int, less< string > > wordCount;		//Žodžiai ir jų pasikartojimų skaičius
	pildFailas(wordLoc, wordCount);
	printResult(wordLoc, wordCount);
	return 0;
}

//Funkcija, kuri iš failo žodžiais užpildo map konteinerius
void pildFailas(multimap< string, int, less< string > >& wordLoc, map< string, int, less< string > >& wordCount) {
	string pavad;
	string eil;
	string elem;
	int n = 0;
	cout << "Įveskite failo pavadinimą: ";
	cin >> pavad;
	cout << "Tekste pasikartojančios nuorodos: " << endl;
	regex urlRegex1(R"(https?://\S+)");
	regex urlRegex2(R"(www\.\S+)");
	ifstream df(pavad);
	while (std::getline(df, eil)) {
		std::istringstream iss(eil);
		if (!eil.empty()) n++;
		while (iss >> elem) {
			if (regex_search(elem, urlRegex1) || regex_search(elem, urlRegex2)) cout << elem << endl;
			elem = istrintiZenklus(elem);
			wordLoc.insert(make_pair(elem, n));
			wordCount[elem]++;
		}
	}
}

//Funckija spausdinanti rezultatus
void printResult(multimap< string, int, less< string > > wordLoc, map< string, int, less< string > > wordCount) {
	ofstream rf1("Uzd1.txt");
	ofstream rf2("Uzd2.txt");
	rf1 << "Skaičius  Žodis" << endl;
	rf1 << "---------------" << endl;
	rf2 << "Eilutė    Žodis" << endl;
	rf2 << "---------------" << endl;
	cout << "Tekste daugiau nei vieną kartą pasikartojantys žodžiai ir jų pasikartojimų skaičius įrašyti į 'Uzd1.txt'" << endl;
	cout << "Tekste daugiau nei vieną kartą pasikartojantys žodžiai ir teksto eilutės, kuriose jie yra, įrašyti į 'Uzd2.txt'" << endl;
	for (const auto& i : wordCount) {
		if (i.second > 1) {
			rf1 << left << setw(10) << i.second << i.first << endl;
			auto range = wordLoc.equal_range(i.first);
			for (auto &it = range.first; it != range.second; ++it) {
				rf2 << left << setw(10) << it->second << it->first << endl;
			}
		}
	}
}

string istrintiZenklus(const std::string& input) {
	std::string result = input;
	result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char c) {
		return !std::isalnum(c);
		}), result.end());
	return result;
}