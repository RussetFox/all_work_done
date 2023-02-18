#include <openssl/evp.h>
#include <string.h>
#include <cctype>
#include <functional>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <condition_variable>
#include <csignal>

//Tablice globalne hasel oraz hasel plus uzytkownikow
std::vector <std::string> passw, userFound;
std::vector <std::vector<std::string>>hashPlusUser;
std::mutex globalMutex; 
std::condition_variable condVar;
bool passFound;


//Signal handler - wypisanie wszystkich zlamanych hasel
void signal_handler(int signal_number){
	for (int i = 0; i < hashPlusUser.size(); i++){
		if (!hashPlusUser[i][0].empty()) std::cout << "Haslo: " << hashPlusUser[i][0]
		<< "   dla uzytkownika: " << hashPlusUser[i][2] << std::endl;
	}
}


//Funkcja zmiany liter na cyfry
void lettersToNumbers(std::string& changedString){
	for(auto& c : changedString){
		switch (c){
			case 'a':
			c = '4';
			break;
			case 'b':
			c = '8';
			break;
			case 'e':
			c = '3';
			break;
			case 'i':
			c = '1';
			break;
			case 's':
			c = '5';
			break;
			case 'o':
			c = '0';
			break;
			default:
			break;
		}
	}

}


//Funkcje zmiany liter na duze
void emptyFunction(std::string& changedString){
}

void changeFirstLetter(std::string& changedString){
	changedString[0] = toupper(changedString[0]);
}

void changeAllLetters(std::string& changedString){
	for(auto& c : changedString) c = toupper(c);
}


//Funkcja generujaca kombinacje
char signs[] = {'!','@','#','$',
	'%', '_'};
std::vector<std::string> combinations;
void combinationFunction(std:: string helper,int k)
{
	if (k == 0) {combinations.push_back(helper); return;}
	for (int i = 0; i< sizeof(signs)/sizeof(signs[0]); i++){
		std::string new_helper = helper+signs[i]; 
		combinationFunction(new_helper, k-1);
	}
}


//Wektor funkcji do zmiany wielkosci liter
std::vector<std::function<void(std::string&)>> strChange = {emptyFunction, changeFirstLetter, changeAllLetters};


void bytes2md5(const char *data, int len, char *md5buf) {
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len, i;
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, data, len);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);
	for (i = 0; i < md_len; i++) {
		snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
	}
}

//Watek konsumenta
void consumer(){
	while(true){
		std::unique_lock<std::mutex> lock(globalMutex);
		condVar.wait(lock,[]{return passFound;});
		std::cout << "Znaleziono haslo dla uzytkownika: " << userFound.back()<< '\n';
		passFound = false;
	};
}

//Konwersja do hasz
std::string convertToHash(std::string convertedPsw){
	std:: string temp;
	const char * cstr= (convertedPsw.c_str());
	char md5[33];
	bytes2md5(cstr, strlen(cstr), md5);
	return md5;

}

//Same wyrazy z roznymi literami
void breakMethod1(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i < passw.size(); i++){
		actualPassw = passw[i];
		for(int j = 0; j < 3; j++){
			strChange[j](actualPassw);
			hashBreaker = convertToHash(actualPassw);
			for (int k = 0; k < hashPlusUser.size(); k++){
				if (hashPlusUser[k][0].empty()){
					if (hashBreaker == hashPlusUser[k][1]){
					std::lock_guard<std::mutex> lock(globalMutex);
					hashPlusUser[k][0] = actualPassw;
					userFound.push_back(hashPlusUser[k][2]);
					passFound = true;
					condVar.notify_one();
					}
				}
			}
		}
	}
}

//Wyrazy z liczba na koncu
void breakMethod2(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i <= 9999 ; i++){
		for (int j = 0; j < passw.size(); j++){
			actualPassw = passw[j] + std::to_string(i);
			for(int k = 0; k < 3; k++){
				strChange[k](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}
					}
				}
			}
		}
	}
}

//Wyrazy z liczba na poczatku
void breakMethod3(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int i = 0; i <= 9999; i++){
		for (int j = 0; j < passw.size(); j++){
			helpPassw = passw[j];
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				actualPassw = std::to_string(i) + helpPassw;
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}					
					}
				}
			}
		}
	}
}

//Liczba przed + wyraz + liczba na koncu
void breakMethod4(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int i = 0; i <= 9999; i++){
		for (int j = 0; j < passw.size(); j++){
			helpPassw = passw[j];
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				for(int m = 0; m <= 9999; m++){	
					actualPassw = std::to_string(i) + helpPassw + std::to_string(m);
					hashBreaker = convertToHash(actualPassw);
					for (int l = 0; l < hashPlusUser.size(); l++){
						if (hashPlusUser[l][0].empty()){
							if (hashBreaker == hashPlusUser[l][1]){
								std::lock_guard<std::mutex> lock(globalMutex);
								hashPlusUser[l][0] = actualPassw;
								userFound.push_back(hashPlusUser[l][2]);
								passFound = true;
								condVar.notify_one();
							}
						}
					}	
				}
			}
		}
	}
}


//Wyraz + wyraz
void breakMethod5(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i < passw.size()-1; i++){
		actualPassw = passw[i]+passw[i+1];
		for(int j = 0; j < 3; j++){
			strChange[j](actualPassw);
			hashBreaker = convertToHash(actualPassw);
			for (int k = 0; k < hashPlusUser.size(); k++){
				if (hashPlusUser[k][0].empty()){
					if (hashBreaker == hashPlusUser[k][1]){
					std::lock_guard<std::mutex> lock(globalMutex);
					hashPlusUser[k][0] = actualPassw;
					userFound.push_back(hashPlusUser[k][2]);
					passFound = true;
					condVar.notify_one();
					}
				}
			}
		}
	}
}

//Wyraz + liczba + wyraz
void breakMethod6(){
	std:: string actualPassw, hashBreaker;
	for (int l = 0;l <=9999 ; l++){
		for (int i = 0; i < passw.size()-1; i++){
			actualPassw = passw[i]+std::to_string(l)+passw[i+1];
			for(int j = 0; j < 3; j++){
				strChange[j](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int k = 0; k < hashPlusUser.size(); k++){
					if (hashPlusUser[k][0].empty()){
						if (hashBreaker == hashPlusUser[k][1]){
						std::lock_guard<std::mutex> lock(globalMutex);
						hashPlusUser[k][0] = actualPassw;
						userFound.push_back(hashPlusUser[k][2]);
						passFound = true;
						condVar.notify_one();
						}
					}
				}
			}
		}
	}	
}

//Slowo z zamiana liter na cyfry
void breakMethod7(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i < passw.size(); i++){
		actualPassw = passw[i];
		lettersToNumbers(actualPassw);
		for(int j = 0; j < 3; j++){
			strChange[j](actualPassw);
			hashBreaker = convertToHash(actualPassw);
			for (int k = 0; k < hashPlusUser.size(); k++){
				if (hashPlusUser[k][0].empty()){
					if (hashBreaker == hashPlusUser[k][1]){
					std::lock_guard<std::mutex> lock(globalMutex);
					hashPlusUser[k][0] = actualPassw;
					userFound.push_back(hashPlusUser[k][2]);
					passFound = true;
					condVar.notify_one();
					}
				}
			}
		}
	}
}


//Slowo + specjalny znak
void breakMethod8(){
	std:: string actualPassw, hashBreaker;
		for (int j = 0; j < passw.size(); j++){
		for (int i = 0; i < combinations.size() ; i++){
			actualPassw = passw[j] + combinations[i];
			for(int k = 0; k < 3; k++){
				strChange[k](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}
					}
				}
			}
		}	
	}
}

//Znak specjalny + slowo
void breakMethod9(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int j = 0; j < passw.size(); j++){
		for (int i = 0; i < combinations.size() ; i++){
			helpPassw = passw[j];
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				actualPassw = combinations[i] + helpPassw;
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}					
					}
				}
			}
		}
	}
}


//Slowo + znak specjalny + kolejne slowo
void breakMethod10(){
	std:: string actualPassw, hashBreaker;
		for (int i = 0; i < passw.size()-1; i++){
			for (int l = 0; l < combinations.size(); l++){
			actualPassw = passw[i]+combinations[l]+passw[i+1];
			for(int j = 0; j < 3; j++){
				strChange[j](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int k = 0; k < hashPlusUser.size(); k++){
					if (hashPlusUser[k][0].empty()){
						if (hashBreaker == hashPlusUser[k][1]){
						std::lock_guard<std::mutex> lock(globalMutex);
						hashPlusUser[k][0] = actualPassw;
						userFound.push_back(hashPlusUser[k][2]);
						passFound = true;
						condVar.notify_one();
						}
					}
				}
			}
		}
	}	
}
//Znak specjalny + slowo +zamiana liter na znaki
void breakMethod11(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int j = 0; j < passw.size(); j++){
		for (int i = 0; i < combinations.size() ; i++){
			helpPassw = passw[j];
			lettersToNumbers(helpPassw);
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				actualPassw = combinations[i] + helpPassw;
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}					
					}
				}
			}
		}
	}
}

//Slowo + znak specjalny + kolejne slowo zamiana liter na cyfry
void breakMethod12(){
	std:: string actualPassw, hashBreaker;
		for (int i = 0; i < passw.size()-1; i++){
			for (int l = 0; l < combinations.size(); l++){
			actualPassw = passw[i]+combinations[l]+passw[i+1];
			lettersToNumbers(actualPassw);
			for(int j = 0; j < 3; j++){
				strChange[j](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int k = 0; k < hashPlusUser.size(); k++){
					if (hashPlusUser[k][0].empty()){
						if (hashBreaker == hashPlusUser[k][1]){
						std::lock_guard<std::mutex> lock(globalMutex);
						hashPlusUser[k][0] = actualPassw;
						userFound.push_back(hashPlusUser[k][2]);
						passFound = true;
						condVar.notify_one();
						}
					}
				}
			}
		}
	}	
}

//Slowo + specjalny znak + zamiana liter na cyfry
void breakMethod13(){
	std:: string actualPassw, hashBreaker;
		for (int j = 0; j < passw.size(); j++){
		for (int i = 0; i < combinations.size() ; i++){
			actualPassw = passw[j] + combinations[i];
			lettersToNumbers(actualPassw);
			for(int k = 0; k < 3; k++){
				strChange[k](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}
					}
				}
			}
		}	
	}
}

//Slowo + liczba + slowo + zamiana liter
void breakMethod14(){
	std:: string actualPassw, hashBreaker;
	for (int l = 0;l <=9999 ; l++){
		for (int i = 0; i < passw.size()-1; i++){
			actualPassw = passw[i]+std::to_string(l)+passw[i+1];
			lettersToNumbers(actualPassw);
			for(int j = 0; j < 3; j++){
				strChange[j](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int k = 0; k < hashPlusUser.size(); k++){
					if (hashPlusUser[k][0].empty()){
						if (hashBreaker == hashPlusUser[k][1]){
						std::lock_guard<std::mutex> lock(globalMutex);
						hashPlusUser[k][0] = actualPassw;
						userFound.push_back(hashPlusUser[k][2]);
						passFound = true;
						condVar.notify_one();
						}
					}
				}
			}
		}
	}	
}

//Wyraz + wyraz +zamiana liter na numer
void breakMethod15(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i < passw.size()-1; i++){
		actualPassw = passw[i]+passw[i+1];
		lettersToNumbers(actualPassw);
		for(int j = 0; j < 3; j++){
			strChange[j](actualPassw);
			hashBreaker = convertToHash(actualPassw);
			for (int k = 0; k < hashPlusUser.size(); k++){
				if (hashPlusUser[k][0].empty()){
					if (hashBreaker == hashPlusUser[k][1]){
					std::lock_guard<std::mutex> lock(globalMutex);
					hashPlusUser[k][0] = actualPassw;
					userFound.push_back(hashPlusUser[k][2]);
					passFound = true;
					condVar.notify_one();
					}
				}
			}
		}
	}
}

//Liczba + wyraz + liczba + zamiania liter na cyfry
void breakMethod16(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int i = 0; i <= 9999; i++){
		for (int j = 0; j < passw.size(); j++){
			helpPassw = passw[j];
			lettersToNumbers(helpPassw);
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				for(int m = 0; m <= 9999; m++){	
					actualPassw = std::to_string(i) + helpPassw + std::to_string(m);
					hashBreaker = convertToHash(actualPassw);
					for (int l = 0; l < hashPlusUser.size(); l++){
						if (hashPlusUser[l][0].empty()){
							if (hashBreaker == hashPlusUser[l][1]){
								std::lock_guard<std::mutex> lock(globalMutex);
								hashPlusUser[l][0] = actualPassw;
								userFound.push_back(hashPlusUser[l][2]);
								passFound = true;
								condVar.notify_one();
							}
						}
					}	
				}
			}
		}
	}
}

//Liczba + wyraz + zamiana liter na cyfry
void breakMethod17(){
	std:: string actualPassw, helpPassw, hashBreaker;
	for (int i = 0; i <= 9999; i++){
		for (int j = 0; j < passw.size(); j++){
			helpPassw = passw[j];
			lettersToNumbers(helpPassw);
			for(int k = 0; k < 3; k++){
				strChange[k](helpPassw);
				actualPassw = std::to_string(i) + helpPassw;
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}					
					}
				}
			}
		}
	}
}

//Wyrazy z liczba na koncu
void breakMethod18(){
	std:: string actualPassw, hashBreaker;
	for (int i = 0; i <= 9999 ; i++){
		for (int j = 0; j < passw.size(); j++){
			actualPassw = passw[j] + std::to_string(i);
			lettersToNumbers(actualPassw);
			for(int k = 0; k < 3; k++){
				strChange[k](actualPassw);
				hashBreaker = convertToHash(actualPassw);
				for (int l = 0; l < hashPlusUser.size(); l++){
					if (hashPlusUser[l][0].empty()){
						if (hashBreaker == hashPlusUser[l][1]){
							std::lock_guard<std::mutex> lock(globalMutex);
							hashPlusUser[l][0] = actualPassw;
							userFound.push_back(hashPlusUser[l][2]);
							passFound = true;
							condVar.notify_one();
						}
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{   
    std::ifstream dictionary, users;
    std::string test, userpsw, mail, line;

	signal(SIGHUP, signal_handler);


	//Otwarcie i czytanie pliku z haslami slownikowymi
    dictionary.open(argv[1]);
    if(!dictionary.is_open()){
    	std::cerr << "Problem otwarcia pliku" << std::endl;
    	return 1;
    	}	
    while(std::getline(dictionary, test)){
			passw.push_back(test);
        }
    dictionary.close();


	//Otwarcie pliku uzytkownikow z haslami i lamanie hasel
	users.open(argv[2]);
	if(!users.is_open()){
		std::cerr << "Problem otwarcia pliku" << std::endl;
		return 1;
	}
	int help = 0;
	while (std::getline(users, line)){
		std::istringstream line_stream(line);
		line_stream >> userpsw >> userpsw;
		line_stream >> mail;
		hashPlusUser.push_back(std::vector<std::string>(3));
		hashPlusUser[help][1] = userpsw;
		hashPlusUser[help][2] = mail;
		help++;
	}
	users.close();

	combinationFunction("",/*sizeof(signs)/sizeof(signs[0]*/4);
	

	std::vector<std::function<void()>> thrFunctions= {breakMethod1, breakMethod2, breakMethod3, breakMethod4, 
	breakMethod5, breakMethod6,breakMethod7,breakMethod8,breakMethod9, breakMethod10,breakMethod11,
	breakMethod12, breakMethod13, breakMethod14, breakMethod15,breakMethod16,breakMethod17, 
	breakMethod18,consumer};
	std::vector<std::thread> threadVect;
	for (auto &fn : thrFunctions){
		threadVect.emplace_back(fn);
	}
	for (auto &th : threadVect){
		th.join();
	}

}


//jthread, pthread, std::thread
//wewnetrzna zmienna w jthread pozwalajaca na zabicie watku
//Ile watkow: 1. mieszanina duzych i malych liter hasel slownikowych 2. dopisywanie postfixu na koncu plus duze litery jak w 1  3. 2 ale prefix zamiast postfix 4. polaczenie 2+3 (przynajmniej na 2 cyfry)
//5. cyfra pomiedzy 2 wyrazami + zmiana liter (od 1-5 na 4.0)

//Na 4.5 dodawanie znakow specjalnych (!@#$%^&*()\|~) minimum 5 znakow. Modyfikacja wszystkich watkow z zadania poprzedniego
//Na maksa jeszcze jakis dowolny watek

//Na sygnal sighup wyswietla wszystkie znalezione hasla
//Mozna pominac podmiane pliku slowniku i haszy