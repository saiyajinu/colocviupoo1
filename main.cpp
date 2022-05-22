#include <iostream>
#include <ios>
#include <limits>
#include <iterator>
#include <list>

using namespace std;

class IOInterface {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) = 0;
};

class Produs: public IOInterface{
private:
    float pret;
    int cantitate;
    const int id;
    static int contorId;
public:
    Produs();
    virtual ~Produs(){};
    Produs(float pret, int cantitate);
    Produs(const Produs& prod);
    Produs& operator=(const Produs& prod);
    int getID();

    istream& read(istream& in){
        int rasp = 0;
        do{
            try{
                cout<<"Product price: ";
                in>>this->pret;
                if(in.fail())
                    throw 1;
                rasp = 1;
            }
            catch(int e){
                cout<<"Price introduced wrongly!\n";
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(rasp==0);
        cout<<"Product quantity: ";
        in>>this->cantitate;
        cout<<endl;
        return in;
    }

    ostream& write(ostream& out){
        out<<"Product price: "<<this->pret<<endl;
        out<<"Product quantity: "<<this->cantitate<<endl;
        out<<"Product ID: "<<this->id<<endl;
    }


    friend ostream& operator<<(ostream& out, Produs& prod){
        return prod.write(out);
    }

    friend istream& operator>>(istream& in, Produs& prod){
        return prod.read(in);
    }
};
int Produs::contorId = 0;

Produs::Produs():id(contorId++){
    this->pret = 0;
    this->cantitate = 0;
}

Produs::Produs(float pret, int cantitate):id(contorId++){
    this->pret = pret;
    this->cantitate = cantitate;
}
Produs::Produs(const Produs& prod):id(prod.id){
    this->pret = prod.pret;
    this->cantitate = prod.cantitate;
}

Produs& Produs::operator=(const Produs &prod) {
    if(this!=&prod){
        this->pret = prod.pret;
        this->cantitate = prod.cantitate;
    }
    return *this;
}

int Produs::getID() {
    return this->id;
}

class Carte:public Produs{
private:
    string titlu;
    list<string> listaAutori;
    string editura;

public:
    Carte();
    ~Carte(){};
    Carte(string titlu, list<string> listaAutori, string editura, float pret, int cantitate);
    Carte(const Carte& carte);
    Carte& operator=(const Carte& carte);

    istream& read(istream& in){
        cout<<"Title: ";
        in>>this->titlu;
        cout<<"No. of authors: ";
        int nrautori;
        in>>nrautori;
        cout<<"Author(s): "<<endl;
        for(int i = 1; i <= nrautori; i++){
            string autor;
            cout<<"Author number "<<i<<":";
            in>>autor;
            listaAutori.push_back(autor);
        }
        cout<<"Publishing house: ";
        in>>this->editura;
        Produs::read(in);
    }

    ostream& write(ostream& out){
        out<<"Title: "<<this->titlu<<endl;
        list<string>::iterator it;
        out<<"Author(s): ";
        for(it = this->listaAutori.begin(); it!=this->listaAutori.end(); it++){
            out<<*it;
            if(!(*it == this->listaAutori.back()))
                cout<<", ";
            else cout<<endl;
        }
        out<<"Publishing house: "<<this->editura<<endl;
        Produs::write(out);
        cout<<endl;

    }

    friend istream& operator>>(istream& in, Carte& carte){
        carte.read(in);
    }

    friend ostream& operator<<(ostream& out, Carte& carte){
        carte.write(out);
    }

};
Carte::Carte():Produs(){
    this->titlu = "-";
    this->editura = "-";
}

Carte::Carte(string titlu, list<string> listaAutori, string editura, float pret, int cantitate):Produs(pret, cantitate){
    this->titlu = titlu;
    this->listaAutori = listaAutori;
    this->editura = editura;
}

Carte::Carte(const Carte& carte):Produs(carte){
    this->titlu = carte.titlu;
    this->listaAutori = carte.listaAutori;
    this->editura = carte.editura;
}

Carte& Carte::operator=(const Carte& carte) {
    if(this!=&carte){
        Produs::operator=(carte);
        this->titlu = carte.titlu;
        this->listaAutori = carte.listaAutori;
        this->editura = carte.editura;
    }
    return *this;
}

class DVD:public Produs{
private:
    int nrMinute;
public:
    DVD();
    ~DVD(){};
    DVD(int nrMinute, float pret, int cantitate);
    DVD(const DVD& dvd);
    DVD& operator=(const DVD& dvd);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, DVD& dvd){
        dvd.read(in);
    }
    friend istream& operator<<(ostream& out, DVD& dvd){
        dvd.write(out);
    }
};
DVD::DVD():Produs(){
    this->nrMinute = 0;
}
DVD::DVD(int nrMinute, float pret, int cantitate):Produs(pret, cantitate){
    this->nrMinute = nrMinute;
}

DVD::DVD(const DVD& dvd):Produs(dvd){
    this->nrMinute = 0;
}

DVD &DVD::operator=(const DVD &dvd) {
    if (this!=&dvd){
        Produs::operator=(dvd);
        this->nrMinute = dvd.nrMinute;
    }
    return *this;
}
istream &DVD::read(istream &in) {
    cout<<"No. of minutes: ";
    in>>this->nrMinute;
    Produs::read(in);
}
ostream &DVD::write(ostream &out) {
    out<<"No. of minutes: "<<this->nrMinute<<endl;
    Produs::write(out);
}

class DVDMuzica: public DVD{
private:
    string album;
    list<string> listaInterpreti;
public:
    DVDMuzica();
    ~DVDMuzica(){};
    DVDMuzica(string album, list<string> listaInterpreti, int nrMinute, float pret, int cantitate);
    DVDMuzica(const DVDMuzica& dvdm);
    DVDMuzica& operator=(const DVDMuzica& dvdm);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, DVDMuzica& dvdm){
        dvdm.read(in);
    }
    friend ostream& operator<<(ostream& out, DVDMuzica& dvdm){
        dvdm.write(out);
    }
};

DVDMuzica::DVDMuzica():DVD() {
    this->album = "-";
}

DVDMuzica::DVDMuzica(string album, list<string> listaInterpreti, int nrMinute, float pret, int cantitate):DVD( nrMinute, pret, cantitate){
    this->album = album;
    this->listaInterpreti = listaInterpreti;
}

DVDMuzica::DVDMuzica(const DVDMuzica& dvdm):DVD(dvdm) {
    this->album = dvdm.album;
    this->listaInterpreti = dvdm.listaInterpreti;
}

DVDMuzica& DVDMuzica::operator=(const DVDMuzica &dvdm) {
    if(this!=&dvdm){
        DVD::operator=(dvdm);
        this->album = dvdm.album;
        this->listaInterpreti = dvdm.listaInterpreti;
    }
    return *this;
}

istream& DVDMuzica::read(istream &in) {
    cout<<"Album name: ";
    in>>this->album;
    cout<<"No. of interprets: ";
    int nr;
    in>>nr;
    list<string>::iterator it;
    cout<<"Interpret(s): "<<endl;
    for(int i = 1; i <= nr; i++){
        string interpret;
        cout<<"Interpret number "<<i<<": ";
        in>>interpret;
        listaInterpreti.push_back(interpret);
    }
    DVD::read(in);
}

ostream& DVDMuzica::write(ostream &out) {
    out<<"Album name: "<<this->album<<endl;
    list<string>::iterator it;
    for(it = this->listaInterpreti.begin(); it!=this->listaInterpreti.end(); it++){
        out<<*it;
        if(!(*it == this->listaInterpreti.back()))
            cout<<", ";
        else cout<<endl;
    }
    DVD::write(out);
}

class DVDFilm: public DVD{
private:
    string nume;
    string gen;
public:
    DVDFilm();
    ~DVDFilm(){};
    DVDFilm(string nume, string gen, int nrMinute, float pret, int cantitate);
    DVDFilm(const DVDFilm& dvdf);
    DVDFilm& operator=(const DVDFilm& dvdf);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, DVDFilm& dvdf){
        dvdf.read(in);
    }
    friend ostream& operator<<(ostream& out, DVDFilm& dvdf){
        dvdf.write(out);
    }
};

DVDFilm::DVDFilm():DVD() {
    this->nume = "-";
    this->gen = "-";
}

DVDFilm::DVDFilm(string nume, string gen, int nrMinute, float pret, int cantitate):DVD(nrMinute, pret, cantitate) {
    this->nume = nume;
    this->gen = gen;
}

DVDFilm::DVDFilm(const DVDFilm &dvdf):DVD(dvdf) {
    this->nume = dvdf.nume;
    this->gen = dvdf.nume;
}

DVDFilm& DVDFilm::operator=(const DVDFilm& dvdf) {
    if(this!=&dvdf){
        DVD::operator=(dvdf);
        this->nume = dvdf.nume;
        this->gen = dvdf.gen;
    }
    return *this;
}

istream &DVDFilm::read(istream &in) {
    cout<<"Film name: ";
    in>>this->nume;
    cout<<"Genre: ";
    in>>this->gen;
    DVD::read(in);
}

ostream &DVDFilm::write(ostream &out) {
    out<<"Film name: "<<this->nume<<endl;
    out<<"Genre: "<<this->gen<<endl;
    DVD::write(out);
}

class Colectie: public Produs{
private:
    string nume;
public:
    Colectie();
    ~Colectie(){};
    Colectie(string nume, float pret, int cantitate);
    Colectie(Colectie& col);
    Colectie& operator=(const Colectie& col);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, Colectie& col){
        col.read(in);
    }
    friend ostream& operator<<(ostream& out, Colectie& col){
        col.write(out);
    }


};

Colectie::Colectie():Produs() {
    this->nume = "-";
}

Colectie::Colectie(string nume, float pret, int cantitate):Produs(pret, cantitate) {
    this->nume = nume;
}

Colectie::Colectie(Colectie &col):Produs(col) {
    this->nume = col.nume;
}

Colectie &Colectie::operator=(const Colectie &col) {
    if(this!=&col){
        Produs::operator=(col);
        this->nume=col.nume;
    }
    return *this;
}

istream &Colectie::read(istream &in) {
    cout<<"Name: ";
    in>>this->nume;
    Produs::read(in);
}

ostream &Colectie::write(ostream &out) {
    cout<<"Name: "<<this->nume<<endl;
    Produs::write(out);
}

class Figurina:public Colectie{
private:
    string categorie;
    string brand;
    string material;
public:
    Figurina();
    ~Figurina(){};
    Figurina(string categorie, string brand, string material, string nume, float pret, int cantitate);
    Figurina(Figurina& fig);
    Figurina& operator=(const Figurina& fig);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, Figurina& fig){
        fig.read(in);
    }
    friend ostream& operator<<(ostream& out, Figurina& fig){
        fig.write(out);
    }
};

Figurina::Figurina():Colectie() {
    this->categorie = "-";
    this->brand = "-";
    this->material = "-";
}

Figurina::Figurina(string categorie, string brand, string material, string nume, float pret, int cantitate):Colectie(nume, pret, cantitate) {
    this->categorie = categorie;
    this->brand = brand;
    this->material = material;
}

Figurina::Figurina(Figurina &fig):Colectie(fig) {
    this->categorie = fig.categorie;
    this->brand = fig.brand;
    this->material = fig.material;
}

Figurina &Figurina::operator=(const Figurina &fig) {
    Colectie::operator=(fig);
    this->categorie = fig.categorie;
    this->brand = fig.brand;
    this->material = fig.material;
    return *this;
}

istream &Figurina::read(istream &in) {
    cout<<"Category: ";
    in>>this->categorie;
    cout<<"Brand: ";
    in>>this->brand;
    cout<<"Material: ";
    in>>this->material;
    Colectie::read(in);
}

ostream &Figurina::write(ostream &out) {
    out<<"Category: ";
    out<<this->categorie<<endl;
    out<<"Brand: ";
    out<<this->brand<<endl;
    out<<"Material: ";
    out<<this->material<<endl;
    Colectie::write(out);
}

class Poster: public Colectie{
private:
    string format;
public:
    Poster();
    ~Poster(){};
    Poster(string format, string nume, float pret, int cantitate);
    Poster(Poster& poster);
    Poster& operator=(const Poster& poster);
    istream& read(istream& in);
    ostream& write(ostream& out);
    friend istream& operator>>(istream& in, Poster& poster){
        poster.read(in);
    }
    friend ostream& operator<<(ostream& out, Poster& poster){
        poster.write(out);
    }
};

Poster::Poster():Colectie() {
    this->format = "-";
}

Poster::Poster(string format, string nume, float pret, int cantitate):Colectie(nume, pret, cantitate) {
    this->format = format;
}

Poster::Poster(Poster& poster):Colectie(poster) {
    this->format = poster.format;
}

Poster& Poster::operator=(const Poster& poster){
    if (this!=&poster){
        Colectie::operator=(poster);
        this->format = poster.format;
    }
    return *this;
}

istream& Poster::read(istream& in){
    int rasp = 0;
    do{
        try{
            cout<<"Format: ";
            in>>this->format;
            if(this->format[0] != 'A' && this->format[0] != 'a')
                throw 'a';
            rasp = 1;
        }
        catch(char e){
            cout<<"Format introduced wrongly!"<<endl;
        }
    }while(rasp == 0);

    Colectie::read(in);
}

ostream& Poster::write(ostream& out){
    out<<"Format: "<<this->format<<endl;
    Colectie::write(out);
}

class Meniu{
private:
    static Meniu* meniu;
    Produs* produse[100];
    int nrProduse;
    Meniu(){};
    Meniu& operator=(istream& in){};
    Meniu(Meniu& meniu){};
    ~Meniu()
    {
        if(produse!=NULL)
            delete produse;
        if(meniu!=NULL)
            delete meniu;
    }
public:
    static Meniu* getInstance(){
        if(!meniu)
            meniu = new Meniu();
        return meniu;
    }

    void startMeniu(){
        this->nrProduse = 0;
        cout<<"Welcome to our library!"<<endl;
        int rasp1, continua = 1;
        while(continua){
            cout<<"Menu"<<endl;
            cout<<"1. Add Product"<<endl;
            cout<<"2. Show Product by Number"<<endl;
            cout<<"3. Edit Product"<<endl;
            cout<<"4. Order Products"<<endl;
            cout<<"5. Search by Book Title"<<endl;
            cout<<"6. Show Product with biggest quantity"<<endl;
            cout<<"7. Show all Products"<<endl;
            cout<<"0. Stop"<<endl;
            cin>>rasp1;
            cout<<endl;
            switch(rasp1){
                case 1:{
                    int rasp2;
                    cout<<"What Type of Product?"<<endl;
                    cout<<"1.Music DVD"<<endl;
                    cout<<"2.Film DVD"<<endl;
                    cout<<"3.Figurine"<<endl;
                    cout<<"4.Poster"<<endl;
                    cin>>rasp2;
                    switch(rasp2){
                        case 1:{
                            DVDMuzica aux;
                            cin>>aux;
                            produse[nrProduse++] = new DVDMuzica(aux);
                            break;
                        }
                        case 2:{
                            DVDFilm aux;
                            cin>>aux;
                            produse[nrProduse++] = new DVDFilm(aux);
                            break;
                        }
                        case 3:{
                            Figurina aux;
                            cin>>aux;
                            produse[nrProduse++] = new Figurina(aux);
                            break;
                        }
                        case 4:{
                            Poster aux;
                            cin>>aux;
                            produse[nrProduse++] = new Poster(aux);
                            break;
                        }
                    }
                    break;
                }
                case 2:{
                    int prodnr;
                    cout<<"Number of products: "<<this->nrProduse<<endl;
                    cout<<"Product number to show: ";
                    cin>>prodnr;
                    cout<<endl;
                    if(prodnr > this->nrProduse){
                        cout<<"Wrong Product Number"<<endl;
                        break;
                        }
                    cout<<*produse[prodnr]<<endl;
                    break;
                }
                case 7:{
                    for(int i=0; i<nrProduse;i++)
                        cout<<*produse[i]<<endl;
                }
                case 0 :{
                    continua = 0;
                    break;
                }
                default:{
                    cout<<"Wrong input";
                    break;
                }
            }
        }
    }

};
Meniu* Meniu::meniu = 0;

int main() {
    Meniu *m = m->getInstance();;
    m->startMeniu();
    return 0;
}
