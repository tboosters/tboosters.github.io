#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct block{
	int i;
	int j;
	int walls;
	bool visited = false;
	bool isTerminal = false;
	vector<block*> neighbours;
	block* ancestor;
};

int toHex(char c){
	if('0' <= c && c <= '9'){
		return c-'0';
	}else{
		return c-'A'+10;
	}
}

vector<block*> initMaze(int m, int n){
	vector<block*> maze;

	for(int i = 0; i < m; i++){
		string rowIn;
		cin >> rowIn;
		for(int j = 0; j < n; j++){
			block* b = new block;
			b->i = i;
			b->j = j;
			b->walls = toHex(rowIn[j]);
			b->isTerminal = false;
			maze.push_back(b);
		}
	}

	for(int i = 0; i < maze.size(); i++){
		if((maze[i]->walls | 0x7) == 0x7){
			if(i-n >= 0){
				maze[i]->neighbours.push_back(maze[i-n]);
			}else{
				maze[i]->isTerminal = true;
			}
		}
		if((maze[i]->walls | 0xB) == 0xB){
			if((i+1)%n != 0){
				maze[i]->neighbours.push_back(maze[i+1]);
			}else{
				maze[i]->isTerminal = true;
			}
		}
		if((maze[i]->walls | 0xD) == 0xD){
			if(i+n < m*n){
				maze[i]->neighbours.push_back(maze[i+n]);
			}else{
				maze[i]->isTerminal = true;
			}
		}
		if((maze[i]->walls | 0xE) == 0xE){
			if(i%n != 0){
				maze[i]->neighbours.push_back(maze[i-1]);
			}else{
				maze[i]->isTerminal = true;
			}
		}
	}
	return maze;
}

string check(vector<block*> maze){
	bool foundPath = false;
	bool multiPath = false;
	int count = 0;

	deque<block*> frontier;
	vector<block*> visited;
	block* start;

	for(int i = 0; i < maze.size(); i++){
		if(maze[i]->isTerminal){
			start = maze[i];
			frontier.push_back(maze[i]);
			break;
		}
	}
	while(!frontier.empty()){
		block* current = frontier.front();
		current->visited = true;
		count++;
		frontier.pop_front();
		if(current->isTerminal && current != start){
			if(!foundPath){
				foundPath = true;
			}
		}
		for(int i = 0; i < current->neighbours.size(); i++){
			if(!current->neighbours[i]->visited){
					if(find(frontier.begin(), frontier.end(), current->neighbours[i]) == frontier.end()){
						current->neighbours[i]->ancestor = current;
						frontier.push_back(current->neighbours[i]);
					}
			}else{
				if(current->ancestor != current->neighbours[i]){
					multiPath = true;
				}
			}
		}
	}

	if(!foundPath){
		return "NO SOLUTION";
	}else if(count == maze.size()){
		if(multiPath){
			return "MULTIPLE PATHS";
		}
		return "MAZE OK";
	}
	return "UNREACHABLE CELL";
}

int main(){
	int m = -1, n = -1;
	vector< vector<int> > maze;
	cin >> m >> n;
	while(m != 0 && n != 0){
		vector<block*> maze = initMaze(m, n);
		cout << check(maze) << endl;
		cin >> m >> n;
	}
	return 0;
}
