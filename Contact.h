#ifndef CONTACT_
#define CONTACT_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class Contact{

    private:
        string nrTel;
        string label;
        string company;
        string email;

    public:
        Contact(string = "", string = "", string = "", string = "");
        Contact(const Contact &);
       // virtual ~Contact();

        //getters
        string getNr() const;
        string getLabel() const;
        string getCompany() const;
        string getEmail() const;

        //setters
        void setNr(string nrTel);
        void setLabel(string nrTel);
        void setCompany(string nrTel);
        void setEmail(string nrTel);

        //suprascriere operatori
        friend ostream & operator <<(ostream &, const Contact &);
        friend istream & operator >>(istream &, Contact &);
        friend bool operator ==(const Contact &, const Contact &);

        //Metode utilizate pe contacte
        static void showContacts();
        static void saveContact();
        static void deleteContact();
        static void blockContact();
        static void showBlockedContacts();
        static void searchContact();

};

#endif // CONTACT_
