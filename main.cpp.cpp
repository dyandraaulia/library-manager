#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct buku{            //perlu pake id? 
    string judul;
    string penulis;
    int tahun;
} bookdata;

void outputfile(ofstream &data){
    data<<bookdata.judul<<"\n";             // '<<' masukkan data buku ke txt
    data<<bookdata.penulis<<"\n";
    data<<bookdata.tahun<<"\n";
}

void inputfile(fstream &data){
    getline(data,bookdata.judul);
    getline(data,bookdata.penulis);
    data>>bookdata.tahun;
}

void addBook(){                  //create a txt file and write book data in it
    ofstream abook;
    abook.open("buku.txt", ios::app);
    outputfile(abook);
    abook.close();
}

void print_BookFound(){
    cout<<"\n--------------------- Book Found! ---------------------"<<endl;
    cout<<"Judul    \t: "<<bookdata.judul<<endl;
    cout<<"Penulis  \t: "<<bookdata.penulis<<endl;
    cout<<"Tahun Terbit \t: "<<bookdata.tahun<<endl;
}

void searchNoBuku(int no,string path="buku.txt"){
    fstream sbook;
    sbook.open(path);
    for(int i=0; i<no; i++){
        inputfile(sbook);
        if (iswspace(sbook.peek())) sbook.ignore();
    }
    print_BookFound();
    sbook.close();
}

void hapus(string useFor,string path="buku.txt",int k=0){
    string line;
    int n, m, size = 0;
    bool pil=1;//biar kalo useFor nya ga "delete", pil nya dah ada nilainya dan bisa ngelewatin if(pil==0)
    n = k;
    cout<<"\n-------------------------------------------------------"<<endl;
    if(useFor=="delete"){
        cout << "Pilih nomor buku yang akan dihapus!\n"; cout << "No. Buku\t: ";
        cin >> n;
        searchNoBuku(n); 
        cout << "\nHapus buku ini? [1 (ya) / 0 (tidak)]: "; cin >> pil;
    }
    if(pil==0) exit(0); //biar bisa ngelewatin ini bool pilnya di definisiin true dulu di atas soalnya useFor nya ga cuma untuk delete
    fstream dbook;
    dbook.open(path);
    while ((getline(dbook,line))){
        ++size;
    }
    m = size/3;
    buku dataBuku[m];
    dbook.clear();                          //krn eofnya udah keset di akhir setelah line 39 jd setnya dihapus dulu
    dbook.seekg(0);                         //ubah posisi kursor ke awal line lagi

    for(int i = 0; i < m ; i++){
        getline(dbook,dataBuku[i].judul);
        getline(dbook,dataBuku[i].penulis);
        dbook >> dataBuku[i].tahun;
        dbook.ignore();
    }
    dbook.close();

    dbook.open(path,ios::trunc|ios::out);
    for(int i = 0; i < m; i++){
        if(i==(n-1))continue;
        dbook << dataBuku[i].judul << endl;
        dbook << dataBuku[i].penulis << endl;
        dbook << dataBuku[i].tahun << endl;
    }
    dbook.close();
}

void addRack(string from, string to, string useFor){                  //bikin file txt trs write data book disitu
    int n;
    bool pil;
    ofstream rack;
    fstream sbook;
    sbook.open(from);
    rack.open(to,ios::out|ios::app);        //buku di rak user (yg dipinjem)
    cout<<"\n-------------------------------------------------------"<<endl;
    if(useFor=="borrow"){
        cout << "Pilih nomor buku yang akan dipinjam!\n"; //buat bedain buku kalo ada buku yg judul/penulis/tahunnya sama
        cout << "No. Buku\t: ";
        cin >> n;
        searchNoBuku(n);
        cout << "\nPinjam buku ini? [1 (ya) / 0 (tidak)]: "; cin >> pil;
    }
    else if(useFor=="return"){
        cout << "Pilih nomor pengembalian buku yang akan dikembalikan!\n"; cout << "No. Pengembalian\t: ";
        cin >> n;
        searchNoBuku(n,from);
        cout << "\nKembalikan buku ini? [1 (ya) / 0 (tidak)]: "; cin >> pil;
    }
    if(pil==0) exit(0);
     
    for(int i=0;i<n;i++){
        inputfile(sbook); //masukkin data di fstream sbook ke struct
        sbook.ignore();
    }
    outputfile(rack); //data dipindah dari struct ke fstream rack
    rack.close();
    sbook.close();
    //buat hapus data yg dipinjam/dihapus dari buku.txt atau mybooks.txt
    if(useFor=="borrow") hapus("borrow",from,n);
    else if(useFor=="return") hapus("return",from,n);
}

void editBook(){
    string line;
    int n, m, size = 0;
    bool pil;
    cout<<"\n-------------------------------------------------------"<<endl;
    cout << "Pilih nomor buku yang akan diedit!\n"; //buat bedain buku kalo ada buku yg judul/penulis/tahunnya sama
    cout << "No. Buku\t: ";
    cin >> n;
    searchNoBuku(n);
    cout << "\nEdit buku ini? [1 (ya) / 0 (tidak)]: "; cin >> pil;
    if(pil==0) exit(0);
    fstream ebook;
    ebook.open("buku.txt");
    while ((getline(ebook,line))){
        ++size;
    }
    m = size/3;
    buku dataBuku[m];
    ebook.clear();                          //krn eofnya udah keset di akhir setelah line 39 jd setnya dihapus dulu
    ebook.seekg(0);                         //ubah posisi kursor ke awal line lagi

    for(int i = 0; i < m ; i++){
        getline(ebook,dataBuku[i].judul);
        getline(ebook,dataBuku[i].penulis);
        ebook >> dataBuku[i].tahun;
        ebook.ignore();
    }
    ebook.close();

    cin.ignore();
    cout<<"\n--------------------- Edit Book ---------------------"<<endl;
    cout<<"Masukkan Judul Buku \t: "; getline(cin, dataBuku[n-1].judul);
    cout<<"Masukkan Penulis Buku \t: "; getline(cin, dataBuku[n-1].penulis);
    cout<<"Tahun Terbit Buku \t: "; cin>>dataBuku[n-1].tahun;

    ebook.open("buku.txt",ios::trunc|ios::out);
    for(int i = 0; i < m; i++){
        ebook << dataBuku[i].judul << endl;
        ebook << dataBuku[i].penulis << endl;
        ebook << dataBuku[i].tahun << endl;
    }
    ebook.close();
}

void searchTitle(string title,string useFor,string path="buku.txt"){             //aku bikin 3 fungsi berdasarkan filter soalnya kl pake if atau case error:(
    bool n = true; int m=0;
    fstream sbook;
    sbook.open(path);
    while(!sbook.eof()){
            inputfile(sbook);
            m++;
            
            if(bookdata.judul==title){                 //biar ga error kalo getline nya banyak
                print_BookFound();
                n = 0;                  //biar nandain kalo programnya udah pernah nemuin judulnya
                if(useFor=="edit"||useFor=="delete"||useFor=="borrow") cout << "No. Buku \t: " << m << endl;
                else if(useFor=="return") cout << "No. Pengembalian: " << m << endl;
            }
            else if(sbook.eof() && n) {
                cout<<"Maaf, buku yang anda cari belum tersedia"; //kalo udah sampe akhir baris dan programnya belum nemu judul yg sama
            }
            if(sbook.eof()&&useFor=="edit"&&n==0){ //engga ku buat else if karena kalo buku yg dicari = data terakhir, if nya yg ini ga bisa jalan kalo pake else if
                editBook();
                break;
            }
            else if(sbook.eof()&&useFor=="delete"&&n==0){
                hapus(useFor);
                break;
            }
            else if(sbook.eof()&&useFor=="borrow"&&n==0){
                addRack("buku.txt","mybooks.txt",useFor); //useFor="borrow"
                break;
            }
            else if(sbook.eof()&&useFor=="return"&&n==0){
                addRack("mybooks.txt","buku.txt",useFor); //useFor="return"
                break;
            }
            sbook.ignore();
    }
    sbook.close();
}

void searchAuthor(string author,string useFor,string path="buku.txt"){
    bool n = true, del; int m=0;
    fstream sbook;
    sbook.open(path);
    while(!sbook.eof()){
            inputfile(sbook);
            m++;

            if(bookdata.penulis==author && bookdata.judul!=""){
                print_BookFound(); 
                n = 0;                  //biar nandain kalo programnya udah pernah nemuin judulnya   
                if(useFor=="edit"||useFor=="delete" || useFor=="borrow") cout << "No. Buku \t: " << m << endl;
                else if(useFor=="return") cout << "No. Pengembalian: " << m << endl;
            }
            else if(sbook.eof() && n) {
                cout<<"Maaf, buku yang anda cari belum tersedia"; //kalo udah sampe akhir baris dan programnya belum nemu judul yg sama
            }
            if(sbook.eof()&&useFor=="edit"&&n==0){
                editBook();
                break;
            }
            else if(sbook.eof()&&useFor=="delete"&&n==0){ 
                hapus(useFor);
                break;
            }
            else if(sbook.eof()&&useFor=="borrow"&&n==0){
                addRack("buku.txt","mybooks.txt",useFor); //useFor="borrow"
                break;
            }
            else if(sbook.eof()&&useFor=="return"&&n==0){
                addRack("mybooks.txt","buku.txt",useFor); //useFor="return"
                break;
            }
            sbook.ignore(); 
    }
    sbook.close();
}

void searchYear(int year,string useFor,string path="buku.txt"){
    bool n = true, del; int m=0;
    fstream sbook;
    sbook.open(path);
    while(!sbook.eof()){
            inputfile(sbook);
            m++;

            if(bookdata.tahun==year && bookdata.judul!=""){
                print_BookFound();
                n = 0;                  //biar nandain kalo programnya udah pernah nemuin judulnya 
                if(useFor=="edit" || useFor=="delete" || useFor=="borrow") cout << "No. Buku \t: " << m << endl;
                else if(useFor=="return") cout << "No. Pengembalian: " << m << endl;
            }
            else if(sbook.eof() && n) {
                cout<<"Maaf, buku yang anda cari belum tersedia"; //kalo udah sampe akhir baris dan programnya belum nemu judul yg sama
            }
            if(sbook.eof()&&useFor=="edit"&&n==0){
                editBook();
                break;
            }
            else if(sbook.eof()&&useFor=="delete"&&n==0){ 
                hapus(useFor);
                break;
            }
            else if(sbook.eof()&&useFor=="borrow"&&n==0){
                addRack("buku.txt","mybooks.txt",useFor); //useFor="borrow"
                break;
            }
            else if(sbook.eof()&&useFor=="return"&&n==0){
                addRack("mybooks.txt","buku.txt",useFor); //useFor="return"
                break;
            }
            sbook.ignore(); 
    }
    sbook.close();
}

void Filter(string useFor){
    string t, a;
    int y;
    filterMenu:
    if(useFor=="search") cout<<"Cari Buku yang akan dicari dengan filter: \n";
    else if(useFor=="edit") cout<<"Cari Buku yang akan diedit dengan filter: \n";
    else if(useFor=="delete") cout<<"Cari buku untuk dihapus berdasarkan filter\n";
    else if(useFor=="borrow") cout << "Cari Buku yang akan dipinjam dengan filter: \n";
    else if(useFor=="return") cout<<"Cari buku untuk dikembalikan berdasarkan filter\n";
    cout<<"1. Judul\n"<<"2. Penulis\n"<<"3. Tahun\n"<<"4. Kembali\n"<<"5. Keluar\n";
    int pil;
    cout<<"Pilihan Anda: "; cin>>pil;
    
    switch (pil){
        case 1: 
            cin.ignore(); //biar ga error kalo pake getline >1 kali
            cout<<"\nJudul buku yang dicari: ";
            getline(cin,t);
            if(useFor=="search")searchTitle(t,"search");
            else if(useFor=="edit")searchTitle(t,"edit");
            else if(useFor=="delete")searchTitle(t,"delete");
            else if(useFor=="borrow")searchTitle(t,"borrow");
            else if(useFor=="return")searchTitle(t,"return","mybooks.txt");
            break;
        case 2:
            cin.ignore();
            cout<<"\nNama penulis buku yang dicari: ";
            getline(cin,a);
            if(useFor=="search") searchAuthor(a,"search");
            if(useFor=="edit") searchAuthor(a,"edit");
            else if(useFor=="delete") searchAuthor(a,"delete");
            else if(useFor=="borrow") searchAuthor(a,"borrow");
            else if(useFor=="return")searchAuthor(a,"return","mybooks.txt");
            break;
        case 3:
            cout<<"\nTahun Terbit buku yang dicari: ";
            cin>>y;
            if(useFor=="search") searchYear(y,"search");
            if(useFor=="edit") searchYear(y,"edit");
            else if(useFor=="delete") searchYear(y,"delete");
            else if(useFor=="borrow") searchYear(y,"borrow");
            else if(useFor=="return") searchYear(y,"return","mybooks.txt");
            break;
        case 4:
            //goto librarian;
            break;
        case 5:
            exit(0);
        default:
            cout << "wrong input.\n";
            goto filterMenu;
            break;
        } 
}

void sortAlp(struct buku dataBuku[80], int n){          //bubble sort struct diurutkan dari string judul
    struct buku temp;
    for(int i=0;i<n-1;i++){
        for(int j=0; j<(n-i-1); j++){
            if(dataBuku[j].judul>dataBuku[j+1].judul){
                temp=dataBuku[j];
                dataBuku[j]=dataBuku[j+1];
                dataBuku[j+1]=temp;
            }
        }
    }
}

void displayRack(){                 
    int size=0;
    string line;
    ifstream dbook;
    dbook.open("mybooks.txt");
    while ((getline(dbook,line))){
        ++size;
    }
    int n=size/3;                               
    buku dataBuku[n];
    dbook.clear();                          
    dbook.seekg(0);                         
    for(int i=0; i<n; i++){                
        getline(dbook, dataBuku[i].judul);
        getline(dbook, dataBuku[i].penulis);
        dbook>>dataBuku[i].tahun;
        dbook.ignore();
    }
    sortAlp(dataBuku, n);
    for(int i=0; i<n; i++){                
        cout<<"Judul Buku: "<<dataBuku[i].judul<<"\n";
        cout<<"Penulis: "<<dataBuku[i].penulis<<"\n";
        cout<<"Tahun Terbit: "<<dataBuku[i].tahun<<"\n";
        cout<<"------------------------------------"<<"\n";
    }
    dbook.close();
}

//TAMPILKAN SELURUH BUKU DI DATABASE
void displayBook(){                 
    int size=0;
    string line;
    ifstream dbook;
    dbook.open("buku.txt");
    while ((getline(dbook,line))){
        ++size;
    }
    int n=size/3;                               //jumlah baris dibagi 3 (data struct->judul, penulis, tahun)
    buku dataBuku[n];
    dbook.clear();                          //krn eofnya udah keset di akhir setelah line 39 jd setnya dihapus dulu
    dbook.seekg(0);                         //ubah posisi kursor ke awal line lagi
    for(int i=0; i<n; i++){                //input data dari txt ke array
        getline(dbook, dataBuku[i].judul);
        getline(dbook, dataBuku[i].penulis);
        dbook>>dataBuku[i].tahun;
        dbook.ignore();
    }
    sortAlp(dataBuku, n);
    for(int i=0; i<n; i++){                //input data dari txt ke array
        cout<<"Judul Buku: "<<dataBuku[i].judul<<"\n";
        cout<<"Penulis: "<<dataBuku[i].penulis<<"\n";
        cout<<"Tahun Terbit: "<<dataBuku[i].tahun<<"\n";
        cout<<"------------------------------------"<<"\n";
    }
    dbook.close();
}

int main(){
    int choice; 
    firstmenu:
    cout<<"----------- Selamat Datang di Perpustakaan Online! -----------\n";
    cout<<"Siapa Anda?\n"<<"1.Pengunjung\n"<<"2.Pustakawan\n";
    cout<<"--------------------------------------------------------------\n";
    cout<<"Pilih 1 atau 2: "; cin>>choice;
    
    //MENU PENGUNJUNG
    if(choice==1){
        system("cls");
        user:
        int userchoice;
        bool inp;
        cout<<"--------------------------------------------------------------\n";
        cout<<"            Selamat Datang, Pengunjung Perpustakaan!          \n";
        cout<<"--------------------------------------------------------------\n";
        cout<<"1. Cari Buku\n"<<"2. Pinjam Buku\n"<<"3. Kembalikan Buku\n"<<"4. Lihat Semua Buku\n"<<"5. Lihat Buku Saya\n"<<"6. Ganti Peran\n"<<"7. Keluar\n";
        cout<<"--------------------------------------------------------------\n";
        cout<<"Pilihan Anda: "; cin>>userchoice;
        switch (userchoice)
        {
        case 1:
            search:
            system("cls");
            Filter("search");
            cout<<"Apakah Anda ingin mencari buku lagi? [1 (ya) / 0 (tidak)] "; cin>>inp;
            if (inp) goto search;
            else {
                system("cls");
                goto user;
            }
            break;
        case 2:{
            Filter("borrow");
        }
            break;
        case 3:
            Filter("return");
            break;
        case 4:
            system("cls");
            displayBook();
            cout<<"[1 (Kembali) / 0 (Keluar)] "; cin>>inp;
            if (inp) goto user;
            else exit(0);
            break;
        case 5:{
            system("cls");
            displayRack();
            cout<<"[1 (Kembali) / 0 (Keluar)] "; cin>>inp;
            if (inp) goto user;
            else exit(0);
            break;
        }
        case 6:
            system("cls");
            goto firstmenu;
            break;
        case 7:
            exit(0);
        default:
            system("cls");
            cout<<"Input salah!\n";
            goto user;
            break;
        }

    }

    //MENU PUSTAKAWAN   
    else if(choice==2){
        system("cls");
        librarian:
        int libchoice;
        cout<<"--------------------------------------------------------------\n";
        cout<<"                  Selamat Datang, Pustakawan!                 \n";
        cout<<"--------------------------------------------------------------\n";
        cout<<"1. Cari Buku\n"<<"2. Lihat Semua Buku\n"<<"3. Tambah Buku\n"<<"4. Hapus Buku\n"<<"5. Edit Buku\n"<<"6. Ganti Peran\n"<<"7. Keluar\n";
        cout<<"--------------------------------------------------------------\n";
        cout<<"Pilihan Anda: "; cin>>libchoice;
        switch (libchoice)
        {
        case 1:
            cari:
            bool i;
            Filter("search");
            cout<<"\nApakah Anda ingin mencari buku lagi? [1 (ya) / 0 (tidak)] "; cin>>i; cout << endl;
            if (i) goto cari;
            else {
                system("cls");
                goto librarian;
            }
            break;
        case 2:
            cout<<"\n";
            displayBook();
            break;
        case 3: {
            int inp=1;
            while(inp!=0){
            cin.ignore();
            cout<<"\nMasukkan Judul Buku \t: "; getline(cin, bookdata.judul);
            cout<<"Masukkan Penulis Buku \t: "; getline(cin,bookdata.penulis);
            cout<<"Tahun Terbit Buku \t: "; cin>>bookdata.tahun;               //infinite loop ketika input selain int
            addBook();
            cout<<"\nApakah Anda ingin input data buku lagi? [1 (ya) / 0 (tidak)] "; cin>>inp;
            }
            system("cls");
            goto librarian;
            break;
            }
        case 4:
            Filter("delete");
            break;
        case 5:
            Filter("edit");
            break;
        case 6:
            goto firstmenu;
            break;
        case 7:
            exit(0);
        default:
            goto librarian;
            break;
        }        
    }
    else{
        system("cls");        //works on windows only, linux&mac use 'clear'
        cout<<"Masukkan angka 1 atau 2\n";
        goto firstmenu;
    }
    return 0;
}
