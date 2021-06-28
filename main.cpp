#include <iostream>
#include <string.h>
#include <string>
#include<fstream>
#include <conio.h>
#include "Contact.h"

using namespace std;

void initListA();
void initListB();

void mainMenu();
void exitMenu();
void backOption();


int main(){

    initListA();
    initListB();

    mainMenu();

	return 0;
}

void mainMenu(){

        system("CLS");
		cout<<"\n\n\n\t\t\t\t\tMeniu Principal\n\t\t\t\t\t=====================\n\t\t\t\t\t[1] Lista Contacte \n\t\t\t\t\t[2] Adauga contact nou\n\t\t\t\t\t[3] Cauta contact\n\t\t\t\t\t[4] Sterge contact\n\t\t\t\t\t[5] Blocheaza contact\n\t\t\t\t\t[6] Lista contacte blocate\n\t\t\t\t\t[0] Exit\n\t\t\t\t\t=================\n\t\t\t\t\t";
		cout<<"Introdu optiunea:";
        string opt;
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
            Contact::searchContact();
            backOption();
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
            //Meniu de iesire
            exitMenu();
        }else{
            mainMenu();
        }

}

void exitMenu(){
        system("CLS");
		cout<<"\n[1] Meniu principal\t\t[0] Exit\n\nIntrodu optiunea:";
		string opt;
		getline(cin, opt);

		if(opt == "1"){
            mainMenu();
		}else if(opt == "0"){
		    system("CLS");
            exit(0);
		}else{
            exitMenu();
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
