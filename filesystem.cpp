#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i, a, b) for (int i = a; i < b; i++)
#define REPR(i, a, b) for (int i = a; i > b; i--)
#define mk make_pair
#define INT_SIZE 4

class Page
{
    vector<pair<int, int>> v;
    int max_size;
    int cur_size;

public:
    Page(int max_size)
    {
        this->max_size = max_size;
        cur_size = max_size - 4*INT_SIZE;
    }
    bool insert(int,int);
    int search(int); 
    int countRecords();
};

bool Page::insert(int key, int size){
    if(cur_size < (size + INT_SIZE)){
        return false;
    }

    cur_size -= (size + INT_SIZE);
    v.push_back(mk(key, size));
    return true;
}

int Page::search(int k) {
    int i;
    REP(i, 0, v.size()) {
        if (v[i].first == k) {
            return i+1;
        }
    }

    return -1;
}

int Page::countRecords() {
    return v.size();
}

class File {
    vector<Page*> pages;
    int max_size;
    int cur_size;
    int total_entries;
    int countPages();

public:
    File(int max_size)
    {
        this->max_size = max_size;
        cur_size = max_size;
        total_entries = 0;
    }

    void insert(int,int);
    pair<int,int> search(int);
    void status();
};

int File::countPages() {
    return pages.size();
}

void File::insert(int key, int size) {
    int i;
    total_entries++;
    REP(i,0,countPages()) {
        if (pages[i]->insert(key,size)) {
            return;
        }
    }
    Page* page = new Page(max_size);
    page->insert(key,size);
    pages.push_back(page);
}

pair<int,int> File::search(int key){
    int i;
    REP(i,0,countPages()) {
        if (pages[i]->search(key) != -1) {
            return mk(i+1,pages[i]->search(key));
        }
    }
    return mk(-1,-1);
}

void File::status() {  
    cout << countPages() << " ";

    int i;
    REP(i,0,countPages()) {
        cout << pages[i]->countRecords() << " ";
    }
    cout << endl;
}

int main() {
    int page_size;

    cin >> page_size;

    File* file = new File(page_size);

    int n;
    int key,size;
    pair<int,int> result;

    while (cin >> n) {
        if (n == 1) {
            cin >> size >> key;
            file->insert(key,size);
        } else if (n == 2) {
            file->status();
        } else if (n == 3) {
            cin >> key;
            result = file->search(key);
            cout << result.first << " " << result.second << endl;
        } else {
            return 0;
        }
    }

    return 0;
}