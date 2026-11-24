#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;
struct Bid{
    string bidderId;
    double amount;       // bid price
    long long timestamp; // Unix ms
    int auctionId;
};

// ---------- Utilities ----------
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount
        << " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}

// ---------- TODO: Implement these ----------
bool SoSanhBid(const Bid& a, const Bid& b) {
    if (a.amount==b.amount) {
        return a.timestamp<b.timestamp;
    }
    return a.amount<b.amount;
}
void insertionSort(vector<Bid>& v)// Task A
{
    for(int i=1; i<v.size(); i++) 
    {
        Bid key=v[i];
        int j=i-1;
        while(j>=0 && SoSanhBid(key, v[j]))
        {
            v[j+1]=v[j];
            j=j-1;
        }
        v[j+1]=key;
    }
}
void selectionSort(vector<Bid>& v)// Task B
{
    for(int i=0; i<v.size(); i++) 
    {
        int maxIdx=i;
        for (int j=i+1; j<v.size(); j++) {
            if (v[j].amount > v[maxIdx].amount) {
                maxIdx=j;
            }
        }
        swap(v[i],v[maxIdx]);
    }
	cout<<"Top 3:";
    for (int i=0; i<min(v.size(), (size_t)3); ++i) { // ở đoạn này, em sử dụng LLM với lệnh "hãy hướng dẫn tôi cách in ra top 3 và giải thích"
        cout<<v[i].bidderId<<"\t";
    }
}
void interchangeSort(vector<Bid>& v)        // Task C
{
    int count = 0;
    for(int i = 0; i<v.size(); i++) 
    {
        for (int j=i+1; j<v.size(); j++) {
            if (v[i].amount>v[j].amount) {
                swap(v[i],v[j]);
                count++;
            }
        }
    }
    cout<<"Total number of swaps:"<<count<<endl;
}
bool bubbleSortEarlyStop(vector<Bid>& v)    // Task D — returns true if stable (no swaps on a full pass)
{
    bool stop=true;
    for (int i=0; i<v.size(); i++) {
        bool swapped = false;
        for (int j=0; j<v.size()-i-1; j++) {
            if (v[j].amount>v[j+1].amount) {
                swap(v[j], v[j+1]);
                swapped=true;
                if (i==0) 
                    stop = false;
            }
        }
        if(!swapped) 
            break;
    }
    if(stop) 
    {
        cout <<"STABLE"<<endl;
        return true;
    }
    else 
    {
        cout <<"UNSTABLE"<<endl;
        return false;
    }
}
int medianOfThree(vector<Bid>& v, int low, int high) {
	if (low >= high) return low;
    int mid = (low + high) / 2;
    if(SoSanhBid(v[mid],v[low]))
		swap(v[mid], v[low]);
	if(SoSanhBid(v[high], v[low]))
		swap(v[high], v[low]);
    if(SoSanhBid(v[high], v[mid]))
		swap(v[high], v[mid]);
    return mid;
}
int partition(vector<Bid>& v, int low, int high) {
    int medIdx = medianOfThree(v, low, high);
    swap(v[medIdx], v[high]);
    Bid pivot = v[high];
    int i=low-1;
    for (int j=low; j<high;j++) 
    {
        if (!SoSanhBid(pivot, v[j])) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}
void quickSort(vector<Bid>& v, int low, int high) {
    if (low < high) 
    {
        int pi = partition(v, low, high);
        quickSort(v, low, pi-1);
        quickSort(v, pi+1, high);
    }
}
void quickSortWrapper(vector<Bid>& v) {
    if (v.empty()) return;
    auto start = chrono::high_resolution_clock::now();
    quickSort(v, 0, v.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Runtime: "<<time_taken << " miliseconds\n";
}
//Hàm này em sử dụng LLM để tạo ra random data
void generateRandomBids() {
    ofstream file("Test_Data/large.txt");
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        return;
    }
    mt19937 gen(random_device{}());
    uniform_real_distribution<double> amountDist(100, 1000000);
    uniform_int_distribution<long long> timestampDist(1, 1000000000);
    uniform_int_distribution<int> auctionDist(1, 100);
    for (int i = 0; i < 100000; i++) {
        string bidderId = "Bidder_" + to_string(i + 1);
        double amount = amountDist(gen);
        long long timestamp = timestampDist(gen);
        int auctionId = auctionDist(gen);
        file <<bidderId<< " "
            <<amount<< " "
            <<timestamp<< " "
            <<auctionId<< "\n";
    }
    file.close();
    cout<<"Tao thanh cong file"<<endl;
}
// ---------- Driver ----------
int main(int argc, char* argv[]) {
    vector<Bid> small;
	if (!loadBids("Test_Data/small.txt", small)) {
		cout<<"Failed to load small.txt\n";
		return 1;
	}
    //Task A
	cout << "Task A: Insertion Sort\n";
	vector<Bid> a(small.begin(), small.begin()+4);
    insertionSort(a);
    printBids(a);
	cout << endl;

	//Task B
	cout << "Task B: Selection Sort\n";
	vector<Bid> b(small.begin(), small.begin()+4);
	selectionSort(b);

	//Task C
	cout << endl;
	cout << "Task C: Interchange Sort\n";
    vector<Bid> c(small.begin() + 4, small.begin() + 8);
    interchangeSort(c);

	//Task D
	cout<<endl;
	cout<<"Task D: Bubble Sort Early Stop\n";
	cout<<"Test 1: Sorted input\n";
	vector<Bid> d1(small.begin() + 8, small.begin() + 12);
    bubbleSortEarlyStop(d1);
    cout<<"Test 2: Reversed input\n";
    vector<Bid> d2(small.begin() + 12, small.end());
    bubbleSortEarlyStop(d2);
    
    //Task E
    cout<<endl;
    cout<<"Task E: Quick Sort\n";
    generateRandomBids();
    vector<Bid> bids;
    loadBids("Test_Data/large.txt", bids);
    quickSortWrapper(bids);
    cout << "After sorting:\n";
    printBids(bids,5);
}