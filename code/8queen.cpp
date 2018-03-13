//Reference from http://blog.csdn.net/hackbuteer1/article/details/6657109

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int numOfQueen = 8;
const int initial = -999999;

int board[numOfQueen];

void initialize(){
	for(int i = 0; i < numOfQueen; i++){
		board[i] = initial;
	};
};

bool isValid(int i, int j){
	for(int k = 0; k < numOfQueen; k++){
		if(board[k] == i){
			return false;
		};
		if(abs(k-j) == abs(board[k]-i)){
			return false;
		};
	};
	return true;
};

void draw(){
	for(int j = 0; j < numOfQueen; j++){
		for(int i = 0; i < numOfQueen; i++){
			if(board[j] == i){
				cout << "Q ";
			}else{
				cout << ". ";
			};
		};
		cout << endl;
	};

	for(int i = 0; i < numOfQueen; i++){
		cout << board[i] << " ";
	};

	cout << endl << "========================" << endl;
};

void queen(){
	int count = 0;
	int i = 0, j = 0;
	while(j < numOfQueen){
		while(i < numOfQueen){
			if(isValid(i, j)){
				board[j] = i;
				i = 0;
				break;
			}else{
				i++; 
			};
		};

		if(board[j] == initial){
			if(j == 0){
				break;
			}else{
				j--;
				i = board[j]+1;
				board[j] = initial;
				continue;
			};
		};

		if(j == numOfQueen-1){ 
			count++;
			cout << endl << "Answer " << count << ":" << endl;
			draw();
			i = board[j]+1;
			board[j] = initial;
			continue;
		};

		j++;
	};		
};

int main(){
	initialize();
	queen();
	return 0;
};
