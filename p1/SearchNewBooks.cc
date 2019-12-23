// Copyright [2019] <Guoqin Sun>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono> // NOLINT (build/c++11)

using namespace std;

class Book{
public:
    int getISBN() const {
        return ISBN;
    }
    void setISBN(int ISBN) {
        Book::ISBN = ISBN;
    }
    const std::string &getType() const {
        return type;
    }
    void setType(const std::string &type) {
        Book::type = type;
    }
    Book(int x, std::string y): ISBN(x), type(y){}

    friend std::ostream& operator<<(std::ostream& os, const Book& b) {
        os << "ISBN: " <<  b.ISBN << std::endl << "Type: " << b.type << std::endl;
        return os;
    }
    friend const bool operator<(const Book x, const Book y) {
        if(x.ISBN == y.ISBN){
            if((x.type == "digital" && y.type == "new")
               ||(x.type == "digital" && y.type == "used")
               ||(x.type == "new" && y.type == "used")){
                return true;
            }else {
                return false;
            }
        }else {
            return x.ISBN < y.ISBN;
        }
    }

    friend const bool operator>(const Book x, const Book y) {
        if(x.ISBN == y.ISBN){
            if( (x.type == "new" && y.type == "digital")
                || (x.type == "used" && y.type == "digital")
                || (x.type == "used" && y.type == "new") ){
                return true;
            } else {
                return false;
            }
        } else {
            return x.ISBN > y.ISBN;
        }
    }
    friend const bool operator==(const Book x, const Book y) {
        if( (x.ISBN == y.ISBN) && (x.type == y.type) ) {
            return true;
        }else {
            return false;
        }
    }

private:
    int ISBN;
    std::string type;
};



int LinearSearch(vector<Book> &newBook, vector<Book> &requestBook){
    int count = 0;
    signed int requestSize = requestBook.size();
    signed int newSize = newBook.size();
    for(int i = 0; i < requestSize; ++i){
        for(int j = 0; j < newSize; ++j){
            if(requestBook[i] == newBook[j]){
                count++;
            }
        }
    }
    return count;
}

bool BinarySearch(vector<Book> &newBook, Book requestBook){

    vector<Book>::iterator iter;
    //Sorting first
    sort(newBook.begin(), newBook.end());
    
    //begin binary search
    int i = 0;
    signed int j = newBook.size() - 1;

    while (i < j) {
        int m = (i + j) / 2;
        if (requestBook > newBook[m]){
            i = m + 1;
        } else {
            j = m;
        }

    }
    if (requestBook == newBook[i]){
        return true;
    } else {
        return false;
    }

}

void TimeMeasurement(){
    std::chrono::high_resolution_clock::time_point start;
    start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "CPU time: " << elapsed_us << " microseconds";
    cout << endl;
}


int main(int argc, char* argv[]) {

    if(argc != 4){
        cerr << "Usage: ./SearchNewBooks <newBooks.dat> "
                "<request.dat> <result_file.dat>" << endl;
        return 1;
    }
    ifstream myfile(argv[1]);
    ifstream myfile1(argv[2]);

    if(!myfile.is_open()){
        cerr << "Error: cannot open file " << argv[1] << endl;
        return 1;
    }else if(!myfile1.is_open()){
        cerr << "Error: cannot open file " << argv[2] << endl;
        return 1;
    }

    //store in 2 vectors
    vector<Book> newBook;
    vector<Book> requestBook;

    int count = 0;

    int num[12000];
    char c;
    string s[12000];
    //FIXME: i size
    int i = 0;
    while(!myfile.eof()){
        myfile >> num[i] >> c >> s[i];

        Book book(num[i], s[i]);
        newBook.push_back(book);
        i++;
    }

    int j = 0;
    while(!myfile1.eof()) {
        myfile1 >> num[i] >> c >> s[i];
        Book book(num[i], s[i]);
        requestBook.push_back(book);
        j++;
    }

/////////////////////////////////////////////////////////////////////////////
    cout << "Choice of search method ([l]inear, [b]inary)?" << endl;
    //Begin sorting and time measurement
    char c1;
    signed int requestSize = requestBook.size();

    cin >> c1;
    while (c1 != 'l' && c1 != 'b') {
        cerr << "Incorrect choice" << endl;
        cin >> c1;
    }
    if (c1 == 'l') {

        count = LinearSearch(newBook, requestBook);
        TimeMeasurement();
    } else if (c1 == 'b') {
        for(int i = 0; i < requestSize; ++i){
            if(BinarySearch(newBook, requestBook[i])){
                count ++;
            }
        }
        TimeMeasurement();
    }

    //4. output the number to a new file
    ofstream myfile2(argv[3]);
    myfile2 << count;

    return 0;
}
