// πρόγραμμα το οποιο υλοποιεί τον αλγόριθμο Horspool για την εύρεση ενός προτύπου
// σε μία συμβολοσειρά. Εμφανίζει τις θέσεις όπου έχουμε ταίριασμα του προτύπου
// και το πλήθος των συγκρίσεων που εκτελούνται


#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define N 16    // Πλήθος συμβόλων
#define FILENAME "data.txt" // όνομα αρχείου που περιέχει το κείμενο και το πρότυπο

// Πρωτότυπα συναρτήσεων
int horspool(string pattern,  int m, string text, int n, int shift[], int pos, int &comp);
int shiftTable(int shift[], int n, string P, int m);
int position(char c);


int main() {
    int shift[N];   // πίνακας ολίσθησης
    string text;    // κείμενο όπου κάνουμε την αναζήτηση
    string pattern;   //πρότυπο
    int i, pos;
    int m,n;
    int count=0;    // πλήθος εμφανίσεων του προτύπου στο κείμενο
    int comparisons=0;  // πλήθος συγκρίσεων
    char c;

    ifstream file;  // αρχείο
    // άνοισμα αρχείου
    file.open(FILENAME, ios::in);

    if(file.is_open()){
        // διαβάζουμε το πρότυπο. Πρέπει να περιέχεται στην πρώτη γραμμή του αρχείου
        getline(file,pattern,'\n');
        // Εάν είναι κενό το πρότυπο τότε το πρόγραμμα σταματάει με το κατάλληλο μήνυμα
        if (pattern.length()==0){
            cout<<"empty pattern";
            return 1;
        }
        // Διαβάζουμε το κείμενο το οποίο βρίσκεται στο αρχείο (αγνοώντας τις αλλαγές γραμμής)
        while(!file.eof()){
            file >> c;
            // έλεγχος εάν ο χαρακτήρας που διαβάστηκε είναι αποδεκτός
            if(position(c)==-1){
                // εάν δεν είναι εμφανίζεται το κατάλληλο μήνυμα
                cout<<endl<<"Σrong file format";
                return 2;
            }
            // αν είναι αποδεκτός προσθέτουμε τον χαρακτήρα στο κείμενο
            text.append(1,c);
        }
        m=pattern.length(); // μήκος του προτύπου
        n=text.length();    // μήκος του κειμένου
        // εμφάνιση κειμένου και προτύπου
        cout<<endl<<"Text:"<<text;
        cout<<endl<<"Pattern:"<<pattern;
        // εμφάνιση μήκους κειμένου και προτύπου
        cout <<endl<<"Text length:"<<n;
        cout <<endl<<"Pattern length:"<<m<<endl;

        // υπολογισμός του πίνακα ολίσθησης
        shiftTable(shift, N, pattern, pattern.length());
        // εμφάνιση του πίνακα ολίσθησης
        cout<<endl<<"Shift Table:"<<endl;
        for(i=0;i<N;i++)
            cout<<shift[i]<<" ";
        cout<<endl<<endl<<"Performing Horspool's algotithm:";
        // αρχικά η αναζήτηση του προτύπου ξεκινά από τα αριστερά
        pos=-1;
        do{
            // καλούμε διαδοχικά τον Horspool συνεχίζοντας κάθε φορά από την επομένη της θέσης όπου έχουμε ταίριασμα
            pos=horspool(pattern, m, text, n, shift, pos+1, comparisons);
            if(pos!=-1) {
                // εκτύπωση της θέσης όπου έχουμε ταίριασμα
                cout << endl<<"position:" << pos;
                // αύξηση μετρητή
                count++;
            }
        // αν δεν βρούμε το πρότυπο τότε η συνάρτηση horspool επιστρέφει -1
        }while(pos!=-1);
        // εκτύπωση πλήθους ταιριασμάτων
        cout<<endl<<"The pattern was found "<<count<<" times."<<endl;
        // συνολικό πλήθος συγκρίσεων
        cout<<endl<<"Total comparisons when using Horspool:"<<comparisons;
        // με ομή βία το μέγιστο πλήθος συγκρίσεων είναι m*n
        cout<<endl<<"Brute force algorithm, maximum:"<<m*n;
    }
    else
        cout << "Cannot open file";
}

// Συνέρτηση που παίρνει έναν χαρακτήρα και επιστρέφει τη θέση στον πίανκα ολίσθησης
// ταυτόχρονα ελέγχει αν ο χαρακτήρας είναι εγκυρος, αφού αν δεν είναι έγκυρος επιστρέφει -1
int position(char c){
    if('0'<=c && c<='9')
        return (int) (c-'0');
    if(c=='A' || c=='a') return 10;
    else if(c=='B' || c=='b') return 11;
    else if(c=='C' || c=='c') return 12;
    else if(c=='D' || c=='d') return 13;
    else if(c=='E' || c=='e') return 14;
    else if(c=='F' || c=='f') return 15;
    else return -1;
}


// Συνάρτηση που υπολογίζει τον πίανακα ολίσθησης για ένα πρότυπο P
int shiftTable(int shift[], int n, string P, int m){
    int i,j;
    // Αρχικά θέτουμε σε όλες τις θέσεις του πίνακα το m
    for(i=0;i<n;i++)
        shift[i]=m;
    // Θέτουμε τις σωστές τιμές για κάθε χαρακτήρα
    for(j=0;j<m-1;j++)
        shift[position(P[j])]=m-1-j;
}


// Συνάρτηση που εκτελεί τον αλγόριθμο Horspool.
// Παίρνει σαν παράμετρους:
// το πρότυπο Pattern και τη διάσταση του m
// το κείμενο text και τη διάστασή του n
// τον πίνακα ολίσθησης shift
// τη θέση pos από όπου θα ξεκινήσει η αναζήτηση
// τη μεταβλητή comp που περιέχει το πλήθος των συγκρίσεων που θα εκτελεστούν
// Επιστρέφει τη θέση όπου βρέθηκε το πρότυπο
// αν δεν βρεθεί το πρότυπο επιστρέφει το -1

int horspool(string pattern, int m, string text, int n, int shift[], int pos, int &comp){
    int i,k;
    // αρχική θέση του δείκτη
    i=pos+m-1;
    // μέχρι τέλους του κειμένου
    while(i<=n-1){
        k=0;
        // όσο βρίσκουμε ίδιους χαρακτήρες προχωράμε το k
        // και αυξάνουμε ταυτόχρονα πλήθος συγκρίσεων
        while(++comp && k<=m-1 && pattern[m-1-k]==text[i-k]){
            k++;
        }
        if(k==m)
            return i-m+1;
        else
            i+=shift[position(text[i])];
    }
    return -1;
}

