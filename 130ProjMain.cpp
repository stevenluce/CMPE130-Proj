/*
 * Since this is a relatively simple project,
 * I will require that you add the volume attribute to the product.
 * Also, have a limited space volume on the store shelves.
 * The problem would be to maximize the profit given the available shelf space.
 * You can use dynamic programming to solve this.
 * Make sure that the data you have is realistic and contains at least 200 different items.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int num_items_in_store = 209; //Number of products

struct ProductData{
    int ProductID; //Numerical ID
    string prodname; //Name of Item
    int price; //Price
    int size; //How much space it takes up in the store (per item, so 3 of 5 size = 15 total size)
    int quantity; //How many you have
};//Structure for storing data about products

void PrintInventory(ProductData arr[]); //Print entire store inventory
void PrintID(ProductData arr[], int prodID); //Print a specific product ID's data
int knapSack(int W, int wt[], int val[], int n); //Given a max volume, find the best things to stock to maximize sale value
void DisplayMenu();


int main() {
	ProductData arr[num_items_in_store];
	ifstream inFile;
	inFile.open("data.txt");
	for(int count = 0; count < num_items_in_store; count++){
		inFile >> arr[count].ProductID >> arr[count].prodname >> arr[count].quantity >> arr[count].price >> arr[count].size;
	}//Inputs data from file, stores into array
	int val[num_items_in_store] = {}; //Array for item value
	int wt[num_items_in_store] = {}; //Array for item size
	int W = 100; //Max Weight
	for(int i=0;i<num_items_in_store;i++){
		val[i] = arr[i].price;
	} //Put structure data into array
	for(int i=0;i<num_items_in_store;i++){
			wt[i] = arr[i].size;
	}//Put structure data into array
	int n = sizeof(val)/sizeof(val[0]);
	char choice = -1;
	int sel_ID = -1;
	string mystr;
//Pre-menu functions, setting up back-end
	bool LOOP = true;
	while (LOOP != false){
	DisplayMenu();
	cin >> choice;
	switch(choice){
	 case '1':
		 PrintInventory(arr);
		 break;
	 case '2':
		 cout << "Select the Product ID you would like to print: \n";
		 cin >> sel_ID;
		 PrintID(arr, sel_ID);
		 break;
	 case '3':
		 cout << "Enter maximum shelf capacity: \n";
		 cin >> W;
		 cout << "Maximum Value: $";
		 printf("%d", knapSack(W, wt, val, n));
		 cout << "\n";
		 break;
	 case '4':
		 cout << "Quitting...\n";
		 return 0;
	 default:
		 break;
	}
	}
	//printf("%d", knapSack(W, wt, val, n)); //Print greatest value
	//PrintInventory(arr); //Print entire inventory
	//PrintID(arr, 3); //Print ID
	return 0;
}

void PrintInventory(ProductData arr[]){
	cout << left << setw(10) << "ID" << right << setw(20) << "Name" << right << setw(20) << "Number of Units" << right << setw(20) << "Cost (each)" << right << setw(20) << "Size (each)" << "\n";
	for (int i=0;i<num_items_in_store;i++){
		cout << left << setw(10) << arr[i].ProductID << right << setw(20)<< arr[i].prodname << right << setw(20) << arr[i].quantity << right << setw(20) << arr[i].price << right << setw(20) << arr[i].size << "\n";
	}
	cout << "\n";
}

void PrintID(ProductData arr[], int x){
	x = x-1; //Since Product ID starts at 1, Array starts at 0
	cout << left << setw(10) << "ID" << right << setw(20) << "Name" << right << setw(20) << "Number of Units" << right << setw(20) << "Cost (each)" << right << setw(20) << "Size (each)" << "\n";
	cout << left << setw(10) << arr[x].ProductID << right << setw(20)<< arr[x].prodname << right << setw(20) << arr[x].quantity << right << setw(20) << arr[x].price << right << setw(20) << arr[x].size << "\n";
	cout << "\n";
}

int knapSack(int W, int wt[], int val[], int n){
   int i, w;
   int K[n+1][W+1];
   for (i = 0; i <= n; i++){
       for (w = 0; w <= W; w++){
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
   return K[n][W];
}

void DisplayMenu(){
	cout << "**********************\n";
	cout << "What would you like to do? \n";
	cout << "1: Print entire inventory \n";
	cout << "2: Search Product ID \n";
	cout << "3: Optimize store \n";
	cout << "4: Quit \n";
	cout << "**********************\n";
}

