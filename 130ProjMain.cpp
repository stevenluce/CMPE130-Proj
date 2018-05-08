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

int num_items_in_store = 5; //Number of products

struct ProductData{
    int ProductID; //Numerical ID
    string prodname; //Name of Item
    double price; //Price
    int size; //How much space it takes up in the store (per item, so 3 of 5 size = 15 total size)
    int quantity; //How many you have
};//Structure for storing data about products

void PrintInventory(ProductData arr[]); //Print entire store inventory
void PrintID(ProductData arr[], int prodID); //Print a specific product ID's data
int OptimizeStore(int W, ProductData arr[], int n); //Given a max volume, find the best things to stock to maximize sale value



int main() {
	ProductData arr[num_items_in_store];
	ifstream inFile;
	inFile.open("data.txt");
	for(int count = 0; count < num_items_in_store; count++){
		inFile >> arr[count].ProductID >> arr[count].prodname >> arr[count].quantity >> arr[count].price >> arr[count].size;
	}//Inputs data from file, stores into array

	PrintInventory(arr);
	PrintID(arr, 3);
	OptimizeStore(5, arr, 5);
	return 0;
}



void PrintInventory(ProductData arr[]){
	cout << left << setw(5) << "ID" << right << setw(10) << "Name" << right << setw(20) << "Number of Units" << right << setw(15) << "Cost (each)" << right << setw(15) << "Size (each)" << "\n";
	for (int i=0;i<num_items_in_store;i++){
		cout << left << setw(5) << arr[i].ProductID << right << setw(10)<< arr[i].prodname << right << setw(20) << arr[i].quantity << right << setw(15) << arr[i].price << right << setw(15) << arr[i].size << "\n";
	}
	cout << "\n";
}

void PrintID(ProductData arr[], int x){
	x = x-1; //Since Product ID starts at 1, Array starts at 0
	cout << left << setw(5) << "ID" << right << setw(10) << "Name" << right << setw(20) << "Number of Units" << right << setw(15) << "Cost (each)" << right << setw(15) << "Size (each)" << "\n";
	cout << left << setw(5) << arr[x].ProductID << right << setw(10)<< arr[x].prodname << right << setw(20) << arr[x].quantity << right << setw(15) << arr[x].price << right << setw(15) << arr[x].size << "\n";
	cout << "\n";
}

int OptimizeStore(int W, ProductData arr[], int n){
	   if (n == 0 || W == 0){
		   return 0;
	   }
	   if (wt[n-1] > W){
		   return OptimizeStore(W, wt, val, n-1);
	   }
	   else return max(val[n-1] + OptimizeStore(W-wt[n-1], wt, val, n-1),OptimizeStore(W, wt, val, n-1));
}
