// *Prodotti*

//I prodotti trattati da un'erboristeria sono memorizzati in
//cinque vettori paralleli:

// - CODICE, codice di ciascun prodotto
// - NOME, nome del prodotto
// - CASA, casa produttrice
// - CLASSE, Tipologia ci prodotto (medicianle, cosmetico, prodotto,dietetico ecc...)
// - PREZZO, Prezzo del prodotto

// Carica i vettori, sviluppa le seguenti richieste

// a) stampare i dati relativi al prodotto di prezzo massimo
// di una data classe di fornita in input

// b) stampare i dati relativi a un determinato prodotto il cui
// codice è fornito in input

// c) creare un nuovo vettore contenete i nomi dei prodotti di
// una detrminata classe e stamparlo in ordine alfabetico

// d) dati in input due vettori conteneti i codici e i nuovi prezzi
// di alcuni prodotti che hanno subito un aumento, aggiornare il vettore 
// PREZZO con i nuovi prezzi

// e) Stampare della media dei prezzi di una categoria fornita in input

// f) stampare dei dati relativi ai prodtti con prezzo compreso 
// in una certa fascia, i cui estremi sono forniti in input

#include<iostream>
#include<string>
#include<iomanip>
#include<stdlib.h>

using namespace std;


//Colori 
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m" 

//Dichiarazione costanti
const int MAX=100;

//Prototipi 
int menu();
int inserimento(string codice[],string nome[],string casa[],string classe[],float prezzo[]);
void aggiungi(string codice[],string nome[],string casa[],string classe[],float prezzo[],int &n);
int a(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n,bool &trovato);
int b(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n,bool &trovato);
void c(string nome[],string nomeClasse[],string cerca, bool &trovato,string classe[],int n);
void d(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n);
float e(string classe[],float prezzo[],int n);
void f(string codice [],string nome[],string casa[],string classe[],float prezzo[],int n, float min, float max,bool &trovato);
void stampa1(string codice[],string nome[],string casa[],string classe[],float prezzo[],int pos);
void avanti();

int main(){

    //Dichiarazione Array
    string codice[MAX];
    string nome[MAX];
    string casa[MAX];
    string classe[MAX];
    float prezzo[MAX];

    string nomeClasse[MAX];

    //Dichiarazione varaibili
    int scelta,N,pos;
    bool trovato,controllo=false;
    float M,min,max;

    do{
        system("cls");
        scelta=menu();

        switch(scelta){

            case 1:{
                N=inserimento(codice,nome,casa,classe,prezzo);
                cout<<GREEN<<"Prodotti caricati con sucesso"<<RESET<<endl;
                controllo=true;
                avanti();
                break;
            }

            case 2:{
                if(controllo==false){
                    cout<<RED<<"Inserisci prima i prodotti"<<RESET<<endl;
                }
                else{
                    aggiungi(codice,nome,casa,classe,prezzo,N);
                    cout<<GREEN<<"Prodotto aggiunto con successo"<<RESET<<endl;
                }
                avanti();
                break;
            }

            case 3:{
                trovato=false;
                pos=a(codice,nome,casa,classe,prezzo,N,trovato);

                if(trovato==false){
                    cout<<RED<<"Nessun prodotto trovato"<<RESET<<endl;
                }
                else{
                    stampa1(codice,nome,casa,classe,prezzo,pos);
                }

                avanti();
                break;
            }

            case 4:{
                trovato=false;
                b(codice,nome,casa,classe,prezzo,N,trovato);

                if(trovato==false){
                    cout<<RED<<"Nessun prodotto trovato"<<RESET<<endl;
                }
                else{
                    stampa1(codice,nome,casa,classe,prezzo,pos);
                }

                avanti();
                break;
            }

            case 5:{
                trovato=false;
                string cerca;

                cout<<BLUE<<"Inserisci la classe di prodotti da riordinare: "<<RESET;
                cin>>cerca; 

                c(nome,nomeClasse,cerca,trovato,classe,N);

                avanti();
                break;
            }

            case 6:{
                d(codice,nome,casa,classe,prezzo,N);
                avanti();
                break;
            }

            case 7:{
                M=e(classe,prezzo,N);

                if(M==0){
                    cout<<RED<<"Nessun prodotto presente o la classe non esiste"<<RESET<<endl;
                }
                else{
                    cout<<"Il prezzo medio dei prodotti e' "<<M<<endl;
                }
                avanti();
                break;
            }

            case 8:{
                trovato=false;

                do{
                    cout<<BLUE<<"Inserisci il valore minimo: "<<RESET;
                    cin>>min;

                    if(min<=0){
                        cout<<RED<<"Inserisci un valore maggiore di 0"<<RESET<<endl;
                    }

                }while(min<=0);

                do{
                    cout<<BLUE<<"Inserisci il valore massimo: "<<RESET;
                    cin>>max;

                    if(max<=0 || max<min){
                        cout<<RED<<"Inserisci un valore maggiore di "<<min<<RESET<<endl;
                    }

                }while(max<=0 || max<min);

                f(codice,nome,casa,classe,prezzo,N,min,max,trovato);
                if(trovato==false){
                    cout<<RED<<"Nessun prodotto trovato per la fascia di prezzo "<<min<<" - "<<max<<RESET<<endl;
                }               
                avanti();
                break;
            }

            case 0:{
                cout<<BLUE<<"Arrivederci"<<RESET<<endl;
                break;
            }

            default: {
                cout<<RED<<"Scelta non valida"<<RESET<<endl;
                avanti();
                break;
            }

        }//switch

    }while(scelta!=0);

    return 0;
}

int menu(){

    int s;

    cout<<BLUE<<"\t -----Menu'-----\n"<<RESET;
    cout<<BLUE<<"1. "<<RESET<<"Inserisci i prodotti \n";
    cout<<BLUE<<"2. "<<RESET<<"Aggiungi un nuovo prodotto \n";
    cout<<BLUE<<"3. "<<RESET<<"Cerca il prdotto piu' costoso data la classe \n";
    cout<<BLUE<<"4. "<<RESET<<"Cerca il prodotto dato il codice \n";
    cout<<BLUE<<"5. "<<RESET<<"Riordina i prodotti per classe \n";
    cout<<BLUE<<"6. "<<RESET<<"Aggiorna prezzi \n";
    cout<<BLUE<<"7. "<<RESET<<"Calcola la media di una categoria di prodotti \n";
    cout<<BLUE<<"0. "<<RESET<<"Esci \n";

    cout<<BLUE<<"\nFai la tua scelta: "<<RESET;
    cin>>s;

    cout<<"\n";

    return s;
}

int inserimento(string codice[],string nome[],string casa[],string classe[],float prezzo[]){

    int n;
    bool controlla=false;

    do{
        cout<<BLUE<<"Inserisci il numero di prodotti da inserire: "<<RESET;
        cin>>n;

        if(n<=0 || n>MAX){
            cout<<RED<<"Inserisci un numero positivo minore di "<<MAX<<RESET;
            cout<<"\n\n";
        }

    }while(n<=0 || n>MAX);

    cout<<"\n";

    for(int i=0; i<n; i++){

        do{
            cout<<BLUE<<"Inserisci il codice del "<<i+1<<" prodotto: "<<RESET;
            cin>>codice[i];

            for(int j=0; j<i; j++){

                if(codice[i]==codice[j]){
                    controlla=true;
                    cout<<RED<<"Il codice inserito e' gia' stato inserrito ad un altro prdotto "<<RESET;
                    cout<<"\n\n";
                }
            }
        }while(controlla==true);

        cout<<BLUE<<"Inserisci il nome del "<<i+1<<" prodotto: "<<RESET;
        cin.ignore();
        getline(cin,nome[i]);

        cout<<BLUE<<"Inserisci la casa produttrice del "<<i+1<<" prodotto: "<<RESET;
        cin.ignore();
        getline(cin,casa[i]);

        cout<<BLUE<<"Inserisci la classe del "<<i+1<<" prodotto: "<<RESET;
        cin>>classe[i];

        do{
            cout<<BLUE<<"Inserisci il prezzo del "<<i+1<<" prodotto: "<<RESET;
            cin>>prezzo[i];

            if(prezzo[i]<=0){
                cout<<RED<<"Inserisci un prezzo maggiore di 0"<<RESET;
                cout<<"\n\n";
            }

        }while(prezzo[i]<=0);

        cout<<"\n";

    }//for

    return n;
    
}

void aggiungi(string codice[],string nome[],string casa[],string classe[],float prezzo[],int &n){

    cout<<BLUE<<"Inserisci il codice del prodotto da aggiungere: "<<RESET;
    cin>>codice[n];

    cout<<BLUE<<"Inserisci il nome del prodotto da aggiungere: "<<RESET;
    cin.ignore();
    getline(cin,nome[n]);

    cout<<BLUE<<"Inserisci la casa produttrice del prodotto da aggiungere: "<<RESET;
    cin.ignore();
    getline(cin,casa[n]);

    cout<<BLUE<<"Inserisci la classe del prodotto da aggiungere: "<<RESET;
    cin>>classe[n];

    do{
        cout<<BLUE<<"Inserisci il prezzo del prodotto da aggiungere: "<<RESET;
        cin>>prezzo[n];

        if(prezzo[n]<=0){
            cout<<RED<<"Inserisci un prezzo maggiore di 0"<<RESET;
            cout<<"\n\n";
        }

    }while(prezzo[n]<=0);

    n++;
}

int a(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n,bool &trovato){

    string cerca;
    float max;
    int pos;

    cout<<BLUE<<"Inserisci la classe del prodotto da cercare: "<<RESET;
    cin>>cerca;

    for(int i=0; i<cerca.length(); i++){
        cerca[i]=toupper(cerca[i]);
    }

    for(int i=0; i<n; i++){

        string temp1=classe[i];

        for(int j=0; j<temp1.length(); j++){
            temp1[j]=toupper(temp1[j]);
        }

        if(cerca==temp1){
            max=prezzo[i];
            pos=i;
            trovato=true;
        }
    }

    cout<<"\n";

    return pos;
}

int b(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n,bool &trovato){

    string cerca,temp;
    int pos;

    cout<<BLUE<<"Inserisci il codice del prodotto da cercare: "<<RESET;
    cin>>cerca;

    for(int i=0; i<cerca.length(); i++){
        cerca[i]=toupper(cerca[i]);
    }

    for(int i=0; i<n; i++){

        string temp1=codice[i];

        for(int j=0; j<temp1.length(); j++){
            temp1[j]=toupper(temp1[j]);
        }

        if(cerca==temp1){
            pos=i;
            trovato=true;
        }
    }

    return pos;
}

void stampa1(string codice[],string nome[],string casa[],string classe[],float prezzo[],int pos){

    cout<<BLUE<<"Codice: "<<RESET<<codice[pos]<<endl;
    cout<<BLUE<<"Nome: "<<RESET<<nome[pos]<<endl;
    cout<<BLUE<<"Casa produttrice: "<<RESET<<casa[pos]<<endl;
    cout<<BLUE<<"Classe: "<<RESET<<classe[pos]<<endl;
    cout<<BLUE<<"Prezzo: "<<RESET<<prezzo[pos]<<endl;
}

void avanti(){
    cout<<"\n\nPremi invio per andare avanti\n";
    cin.ignore();
    cin.get();
}

void c(string nome[],string nomeClasse[],string cerca, bool &trovato,string classe[],int n){

    string temp;
    int x=0;

    for(int i=0; i<cerca.length(); i++){
        cerca[i]=toupper(cerca[i]);
    }

    for(int i=0; i<n; i++){

        temp=classe[i];

        for(int j=0; j<temp.length(); j++){
            temp[j]=toupper(temp[j]);
        }

        if(cerca==temp){
            nomeClasse[x]=nome[i];
            x++;
            trovato=true;
        }

        //nome[i]=nomeClasse[i];
    }

    for(int i=0;i<n-1;i++){

        for(int j=i+1;j<n;j++){

            if(nomeClasse[i]>nomeClasse[j]){
                swap(nomeClasse[i],nomeClasse[j]);
            }
        }
    }

    for(int i=0; i<n; i++){
        cout<<i+1<<") "<<nomeClasse[i]<<endl;
    }
}

void d(string codice[],string nome[],string casa[],string classe[],float prezzo[],int n){

    int x;

    for(int i=0;i<n;i++){
        cout<<i+1<<"Prodotto\n";
        for(int j=0;j<5; j++){
            cout<<BLUE<<"Codice: "<<RESET<<codice[i]<<endl;
            cout<<BLUE<<"Nome: "<<RESET<<nome[i]<<endl;
            cout<<BLUE<<"Casa produttrice: "<<RESET<<casa[i]<<endl;
            cout<<BLUE<<"Classe: "<<RESET<<classe[i]<<endl;
            cout<<BLUE<<"Prezzo: "<<RESET<<prezzo[i]<<endl;
            cout<<"\n";
        }
    }

    do{
        cout<<BLUE<<"Inserisci il numero del prodotto da modificare: "<<RESET;
        cin>>x;

        if(x<=0 || x>n){
            cout<<RED<<"Inserisci un prodotto esistente"<<RESET;
            cout<<"\n\n";
        }

    }while(x<=0 || x>n);

    do{
        cout<<BLUE<<"Inserisci il nuovo prezzo: "<<RESET;
        cin>>prezzo[x-1];

        if(prezzo[x-1]<=0){
            cout<<RED<<"Inserisci un prezzo positivo"<<RESET;
            cout<<"\n\n";
        }

    }while(prezzo[x-1]<=0);
}

float e(string classe[],float prezzo[],int n){

    float x=0,y=0;
    string cerca,temp;

    cout<<BLUE<<"Inserisci la classe dei prodotti: ";
    cin>>cerca;

    for(int i=0; i<cerca.length(); i++){
        cerca[i]=toupper(cerca[i]);
    }

    for(int i=0; i<n; i++){

        temp=classe[i];

        for(int j=0; j<temp.length(); j++){
            temp[j]=toupper(temp[j]);
        }

        if(cerca==temp){
            x+=prezzo[i];
            y++;
        }
    }

    if(y==0){
        return 0;
    }
    else{
        return x/y;
    }
}

void f(string codice [],string nome[],string casa[],string classe[],float prezzo[],int n, float min, float max,bool &trovato){

    for(int i=0; i<n; i++){
        if(prezzo[i]>=min && prezzo[i]<=max){
            cout<<BLUE<<"Codice: "<<RESET<<codice[i]<<endl;
            cout<<BLUE<<"Nome: "<<RESET<<nome[i]<<endl;
            cout<<BLUE<<"Casa produttrice: "<<RESET<<casa[i]<<endl;
            cout<<BLUE<<"Classe: "<<RESET<<classe[i]<<endl;
            cout<<BLUE<<"Prezzo: "<<RESET<<prezzo[i]<<endl;
            cout<<"\n";
            trovato=true;
        }
    }
}