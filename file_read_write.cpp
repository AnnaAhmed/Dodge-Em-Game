#include <iostream>
#include <string> 
#include <fstream> //it contains implementation of ofstream and ifstream


using namespace std;

int main () {
	
	
	int high_Scores[10] = { 200, 180, 170, 160}; //scores array
	
	//writing to a file
	ofstream fout;
	fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
	
	for (int i = 0; i < 10; i++){
		fout << high_Scores[i] << endl;
	}
		
	fout.close();
	
	//reading from a file
	string score;
	ifstream fin ("high score.txt"); //name of the file it is supposed to read
	if (fin.is_open())
	{
		while ( getline (fin, score) ) //this loop will run depending on the number of lines in the file
		{
		  cout << score << '\n';
		  
		  //HINT: use stoi() to convert string into Integer
		  
		}
		fin.close();
	}
	
	else 
		cout << "Unable to open file"; 
	
	return 0;
}
