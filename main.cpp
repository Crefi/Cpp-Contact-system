#include <iostream>
#include <string.h>
#include <string>
#include<fstream>
#include <conio.h>
#include "Contact.h"

using namespace std;

void printLista();
void printListaB();
void initList();
void initListB();

void mainMenu();
void exitMenu();
void backOption();


int main(){

    initList();
    initListB();


    mainMenu();


	return 0;
}

void mainMenu(){

        system("CLS");
		cout<<"\n\n\n\t\t\t\t\tMeniu Principal\n\t\t\t\t\t=====================\n\t\t\t\t\t[1] Lista Contacte \n\t\t\t\t\t[2] Adauga contact nou\n\t\t\t\t\t[3] Cauta contact\n\t\t\t\t\t[4] Sterge contact\n\t\t\t\t\t[5] Blocheaza contact\n\t\t\t\t\t[6] Lista contacte blocate\n\t\t\t\t\t[0] Exit\n\t\t\t\t\t=================\n\t\t\t\t\t";
		cout<<"Introdu optiunea:";
        string opt;
        while(opt != "1" || opt != "2" || opt != "3" || opt != "4" || opt != "5" || opt != "6" || opt != "0" || opt != "f"){
            getline(cin, opt);
            if(opt == "1"){
                 //Arata contacte
                 Contact::showContacts();
                 backOption();
			}else if(opt == "2"){
			    //Adauga contact nou
			    Contact::saveContact();
			    backOption();
			}else if(opt == "3"){
				//Cauta contact
			}else if(opt == "4"){
                //Sterge contact
                Contact::deleteContact();
                backOption();
			}else if(opt == "5"){
                //Blocheaza contact
                Contact::blockContact();
                backOption();
			}else if(opt == "6"){
                //Contact blocate

                Contact::showBlockedContacts();
                backOption();
			}else if(opt == "0"){
                exitMenu();
			}else if(opt == "f"){
			    system("CLS");
                printLista();
                backOption();
			}else if(opt == "b"){
                system("CLS");
                printListaB();
                backOption();
			}else{
			    mainMenu();
			    break;
			}
        }

}

void exitMenu(){
        system("CLS");
		cout<<"\n[1] Meniu principal\t\t[0] Exit\n\nIntrodu optiunea:";
		string opt;

		while(opt != "1" || opt != "2"){
            getline(cin, opt);
 			if(opt == "1"){
				mainMenu();
				break;
			}else if(opt == "0"){
                system("CLS");
				exit(0);
			}else{
                exitMenu();
                break;
			}
 		}
}

void backOption(){
    cout << "\nPress backspace to go back";
    char op = 8;
    int val = getch();

    while(val != op){
       val = getch();
    }

    if(val == op){
        mainMenu();
    }
}
