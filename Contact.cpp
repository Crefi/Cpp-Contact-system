#include "Contact.h"
#include <string.h>
#include <list>

list <Contact> contacteActive;
list <Contact> contacteBlocate;

fstream fp;
Contact c;

void initListA(){
    fp.open("Contacte.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		contacteActive.insert(contacteActive.end(), c);
	}
	fp.close();
}

void initListB(){
    fp.open("ContacteBlocate.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		contacteActive.insert(contacteBlocate.end(), c);
	}
	fp.close();
}


void updateActiveContacts(){
    fp.open("Contacte.txt", ios::out | ios::trunc);

    for(auto const &i : contacteActive){
        c = i;
        fp.write((char*)&c, sizeof(Contact));
    }
    fp.close();
}

void updateBlockedContacts(){
    fp.open("ContacteBlocate.txt", ios::out | ios::trunc);

    for(auto const &i : contacteBlocate){
        c = i;
        fp.write((char*)&c, sizeof(Contact));
    }

    fp.close();
}

//constructori

Contact::Contact(string nrTel, string label, string company, string email){
    this->nrTel = nrTel;
    this->label = label;
    this->company = company;
    this->email = email;
}

Contact::Contact(const Contact &c){
    this->nrTel = c.nrTel;
    this->label = c.label;
    this->company = c.company;
    this->email = c.email;
}

//getters

string Contact::getNr() const{
    return this->nrTel;
}

string Contact::getLabel() const{
    return this->label;
}

string Contact::getCompany() const{
    return this->company;
}

string Contact::getEmail() const{
    return this->email;
}

//setters

void Contact::setNr(string nrTel){
    this->nrTel = nrTel;
}

void Contact:: setLabel(string label){
    this->label = label;
}

void Contact:: setCompany(string company){
    this->company = company;
}

void Contact:: setEmail(string email){
     this->email = email;
}

//suprascriere operatori

ostream & operator <<(ostream &st, const Contact &c){
    st << "Numar de telefon: " << c.nrTel << endl;
    st << "Label: " << c.label << endl;
    st << "Companie: " << c.company << endl;
    st << "Email: " << c.email << endl;
    return st;
}

istream & operator >>(istream &st, Contact &c){
   cout << "Numar de telefon: ";
   getline(st, c.nrTel);
   cout << "Label: ";
   getline(st, c.label);
   cout << "Companie: ";
   getline(st, c.company);
   cout << "Email: ";
   getline(st, c.email);
   return st;
}

 bool operator ==(const Contact &c1, const Contact &c2){
    if(c1.nrTel == c2.nrTel && c1.label == c2.label && c1.company == c2.company && c1.email == c2.email){
        return true;
    }
    return false;
}

//Metode utilizate pe contacte

Contact cautaInListe(string str, int opt);

void Contact::showContacts(){
    system("CLS");
    cout<<"\t\t================================\n\t\t\tLISTA DE CONTACTE\n\t\t================================\n\n";
    fp.open("Contacte.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		cout << c;
		cout<<endl<<"=================================================\n"<<endl;
	}
	fp.close();
}

bool contineLitera(string nr){
    for(int i = 0; i < nr.size(); i++){
        if(nr[i] < 48 || nr[i] > 57){
            return 1;
        }
    }
    return 0;
}

void Contact::saveContact(){
    system("CLS");
    cin >> c;
    if(contineLitera(c.getNr())){
        system("CLS");
        cout << "Numarul introdus trebuie sa fie format doar din numere!" << endl;
    }else if(cautaInListe(c.getNr(), 1).getNr() != ""){
        system("CLS");
        cout << "Numarul exista deja intr-una dintre liste!" << endl;
    }else{
        contacteActive.insert(contacteActive.end(),c);
        updateActiveContacts();
        cout<<endl<<endl<<"Contact adaugat cu succes...";
    }
}

void Contact::deleteContact(){
    system("CLS");
    //daca listele sunt goale nu are rost sa cautam mai departe
    if(contacteActive.empty() && contacteBlocate.empty()){
        cout << "Nu exista nici-un contact momentan!" << endl;
        return;
    }

    cout <<"Introdu numarul de telefon: ";
    string nr;
    getline(cin, nr);

    //cauta in prima lista
    list<Contact>::iterator itr1;
    int flag1 = 0;
    for(itr1 = contacteActive.begin(); itr1 != contacteActive.end(); itr1++){
        if(itr1->getNr() == nr){
            flag1 = 1;
            break;
        }
    }

    //cauta in a doua lista
    list<Contact>::iterator itr2;
    int flag2 = 0;
    for(itr2 = contacteBlocate.begin(); itr2 != contacteBlocate.end(); itr2++){
        if(itr2->getNr() == nr){
            flag2 = 1;
            break;
        }
    }

    if(flag1 == 0 && flag2 == 0){
        cout << "Contactul nu exista!" << endl;
    }else if(flag1 == 1){
       contacteActive.erase(itr1);
       updateActiveContacts();
       cout << "Numarul a fost sters din lista de contacte active!" << endl;
    }else if(flag2 == 1){
        contacteBlocate.erase(itr2);
        updateBlockedContacts();
        cout << "Numarul a fost sters din lista de contacte blocate!" << endl;
    }

}


void Contact::showBlockedContacts(){
    system("CLS");
    cout<<"\t\t================================\n\t\t\tLISTA DE CONTACTE BLOCATE\n\t\t================================\n\n";
    fp.open("ContacteBlocate.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		cout << c;
		cout<<endl<<"=================================================\n"<<endl;
	}
	fp.close();
}

void Contact::blockContact(){
    system("CLS");
    if(contacteActive.empty()){
        cout << "Nu exista nici-un contact momentan!" << endl;
        return;
    }

     cout <<"Introdu numarul de telefon: ";
     string nr;
     getline(cin, nr);

     list<Contact>::iterator itr;
     int flag = 0;
     for(itr = contacteActive.begin(); itr != contacteActive.end(); itr++){
        if(itr->getNr() == nr){
            flag = 1;
            break;
        }
     }

     if(flag == 1){
        contacteBlocate.insert(contacteBlocate.end(), *itr);
        updateBlockedContacts();
        contacteActive.erase(itr);
        updateActiveContacts();
        cout<<endl<<endl<<"Contact blocat cu succes...";
    }else{
        cout << "Contactul nu exista sau este deja blocat!" << endl;
    }

}

Contact cautaInListe(string str, int opt){

    //cauta in prima lista
    list <Contact>::iterator itr1;
    int flag1 = 0;
    for(itr1 = contacteActive.begin(); itr1 != contacteActive.end(); itr1++){
        if(itr1->getNr() == str && opt == 1){
            flag1 = 1;
            break;
        }else if(itr1->getLabel() == str && opt == 2){
            flag1 = 1;
            break;
        }else if(itr1->getCompany() == str && opt == 3){
            flag1 = 1;
            break;
        }else if(itr1->getEmail() == str && opt == 4){
            flag1 = 1;
            break;
        }
     }

    //cauta in a doua lista
    list<Contact>::iterator itr2;
    int flag2 = 0;
    for(itr2 = contacteBlocate.begin(); itr2 != contacteBlocate.end(); itr2++){
         if(itr2->getNr() == str && opt == 1){
            flag2 = 1;
            break;
        }else if(itr2->getLabel() == str && opt == 2){
            flag2 = 1;
            break;
        }else if(itr2->getCompany() == str && opt == 3){
            flag2 = 1;
            break;
        }else if(itr2->getEmail() == str && opt == 4){
            flag2 = 1;
            break;
        }
    }

    if(flag1 == 0 && flag2 == 0){
        return Contact();
    }else if(flag1 == 1){
        cout << "Numarul exista in lista de contacte active.\n" << endl;
        return *itr1;
    }else if(flag2 == 1){
        cout << "Numarul exista in lista de contacte blocate.\n" << endl;
        return *itr2;
    }

}

void Contact::searchContact(){
    system("CLS");

    //daca listele sunt goale nu are rost sa cautam mai departe
    if(contacteActive.empty() && contacteBlocate.empty()){
        cout << "Nu exista nici-un contact momentan!" << endl;
        return;
    }

    cout << "1.Cauta dupa numar" << endl;
    cout << "2.Cauta dupa label" << endl;
    cout << "3.Cauta dupa nume companie" << endl;
    cout << "4.Cauta dupa email" << endl << endl;

    string opt;
    cout << "Introdu optiunea: ";
    getline(cin, opt);

    if(opt == "1"){
        system("CLS");
        string nr;
        cout << "Introdu numarul: ";
        getline(cin, nr);
        Contact con = cautaInListe(nr,1);
        if(con.getNr() != ""){
            cout << con;
        }else{
            cout << "Numarul nu exista in nici-o lista.\n" << endl;
        }

    }else if(opt == "2"){
        system("CLS");
        string label;
        cout << "Introdu label: ";
        getline(cin, label);
        Contact con = cautaInListe(label,2);
        if(con.getLabel() != ""){
            cout << con;
        }else{
            cout << "Numarul nu exista in nici-o lista.\n" << endl;
        }

    }else if(opt == "3"){
        system("CLS");
        string nume;
        cout << "Introdu nume companie: ";
        getline(cin, nume);
        Contact con = cautaInListe(nume,3);
        if(con.getCompany() != ""){
            cout << con;
        }else{
            cout << "Numarul nu exista in nici-o lista.\n" << endl;
        }

    }else if(opt == "4"){
        system("CLS");

        string email;
        cout << "Introdu email: ";
        getline(cin, email);
        Contact con = cautaInListe(email,4);
        if(con.getEmail() != ""){
            cout << con;
        }else{
            cout << "Numarul nu exista in nici-o lista.\n" << endl;
        }

    }else{
        searchContact();
    }
}
