#include "Contact.h"
#include <string.h>

typedef struct node{
    Contact c;
    struct node *next;
}node;

typedef struct lista{
    node *head;
}lista;

lista l;
lista bl;


void printLista(){
    if(l.head == nullptr){
        cout << "Lista goala" << endl;
        return;
    }

    node *itr = l.head;
    while(itr != NULL){
        cout << itr->c << endl;
        itr = itr->next;
    }
    cout << "-------------------" << endl;
}

void printListaB(){
    if(bl.head == nullptr){
        cout << "Lista goala" << endl;
        return;
    }

    node *itr = bl.head;
    while(itr != NULL){
        cout << itr->c << endl;
        itr = itr->next;
    }
    cout << "-------------------" << endl;
}

void appendToList(lista &l, Contact c){
    node *tmp = new node;
    tmp->c = c;
    tmp->next = nullptr;
    if(l.head == nullptr){
        l.head = tmp;
    }else{
        node *itr = l.head;
        while(itr->next != nullptr){
            itr = itr->next;
        }
        itr->next = tmp;
    }
}

void deleteFromList(lista &l, Contact c){
    if(l.head->c == c){
        node *tmp = l.head;
        l.head = l.head->next;
        delete tmp;
    }else{
        node *itr = l.head;
        node *prev = nullptr;

        while(!(itr->c == c)){
            prev = itr;
            itr = itr->next;
        }
        prev->next = itr->next;
        delete itr;
    }
}

fstream fp;
Contact c;


void initList(){
    fp.open("Contacte.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		appendToList(l, c);
	}
	fp.close();
}

void initListB(){
    fp.open("ContacteBlocate.txt",ios::in);
    while(fp.read((char*)&c,sizeof(Contact))){
		appendToList(bl, c);
	}
	fp.close();
}


void updateContacts(){
    fp.open("Contacte.txt", ios::out | ios::trunc);
    node *itr = l.head;
    while(itr != NULL){
        c = itr->c;
        fp.write((char*)&c, sizeof(Contact));
        itr = itr->next;
    }
    fp.close();
}

void updateBlockedContacts(){
    fp.open("ContacteBlocate.txt", ios::out | ios::trunc);
    node *itr = bl.head;
    while(itr != NULL){
        c = itr->c;
        fp.write((char*)&c, sizeof(Contact));
        itr = itr->next;
    }
    fp.close();
}

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

void Contact::saveContact(){
    system("CLS");
    cin >> c;
    appendToList(l, c);
    updateContacts();
    cout<<endl<<endl<<"Contact adaugat cu succes...";
}


void Contact::deleteContact(){
    system("CLS");
    if(l.head == nullptr && bl.head == nullptr){
        cout << "Nu exista nici-un contact momentan!" << endl;
        return;
    }


    cout <<"Introdu numarul de telefon: ";
    string nr;
    getline(cin, nr);

    node *itr = nullptr;
    if(l.head != nullptr){
        itr = l.head;
        while(itr->c.getNr() != nr){
            itr = itr->next;
            if(itr == nullptr){
                break;
            }
        }
    }

    node *itrB = nullptr;
    if(bl.head != nullptr){
         itrB = bl.head;
         while(itrB->c.getNr() != nr){
            itrB = itrB->next;
            if(itrB == nullptr){
                break;
            }
        }
    }

    if(itr == nullptr && itrB == nullptr){
        cout << "Contactul nu exista!" << endl;
    }else if(itr != nullptr){
        c = itr->c;
        deleteFromList(l, c);
        updateContacts();
    }else if(itrB != nullptr){
        c = itrB->c;
        deleteFromList(bl, c);
        updateBlockedContacts();
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
    if(l.head == NULL){
        cout << "Nu exista nici-un contact momentan!" << endl;
        return;
    }

    cout <<"Introdu numarul de telefon: ";
    string nr;
    getline(cin, nr);

    node *itr = l.head;
    while(itr->c.getNr() != nr){
        itr = itr->next;
        if(itr == nullptr){
            break;
        }
    }

     if(itr != nullptr){

        c = itr->c;
        appendToList(bl, c);
        updateBlockedContacts();
        deleteFromList(l, c);
        updateContacts();
        cout<<endl<<endl<<"Contact blocat cu succes...";

    }else{
        cout << "Contactul nu exista sau este deja blocat!" << endl;
    }

}
