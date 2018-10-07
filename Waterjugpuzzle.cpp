/*
 * Waterjugpuzzle.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: Damon
 */


#include "Waterjugpuzzle.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

struct State {
	int a, b, c;
	vector<string> directions;
	State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
	/*
int main() {
    State s(0, 0, 8);
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;
}
	 */
};
int isNumber(vector<string> n){
	for(string s : n){
		for(char c: s){
			if(!isdigit(c)){
				int x = (int)c;
				return x;
			}
		}
	}
	return -1;
}
char isJug(vector<string> n){
	int size = n.size();
	for(int i=0; i<size; i++){
		for(char c: n[i]){
			if(!isdigit(c)){
				return i;
			}
		}
	}
	return -1;
}

bool isEqualStates(State s1, State s2){
	State one(s1.a,s1.b,s1.c);
	State two(s2.a,s2.b,s2.c);
	string one1 = one.to_string();
	if (one.directions[0] == two.directions[0]){
		return true;
	}
	return false;
}

bool find_solution(State c, State g, State r){
	State cap = c;
	State goal = g;
	State result = r;

	// Case 1
	if(result.a != cap.a && result.c>=cap.a-result.a){
		result.a += cap.a-result.a;
		result.c -= cap.a-result.a;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	// Case 2
	if(result.a != cap.a && result.b>=cap.a-result.a){
		result.a += cap.a-result.a;
		result.b -= cap.a-result.a;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	// Case 3
	if(result.b != cap.b && result.c>=cap.b-result.b){
		result.b += cap.b-result.b;
		result.c -= cap.b-result.b;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	// Case 4
	if(result.b != cap.b && result.a>=cap.b-result.b){
		result.b += cap.b-result.b;
		result.a -= cap.b-result.b;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	// Case 5
	if(result.c != cap.c && result.b>=cap.c-result.c){
		result.c += cap.c-result.c;
		result.b -= cap.c-result.c;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	// Case 6
	if(result.c != cap.c && result.a>=cap.c-result.c){
		result.c += cap.c-result.c;
		result.a -= cap.c-result.c;
		if(isEqualStates(result,goal)){
			return true;
		}else {
			find_solution(c, g, result);
		}
	}
	return false;
}
void case1(State c, State r){
	if(r.a != c.a || r.a-r.c<=r.c){
		r.a += c.a-r.a;
		r.c -= c.a-r.a;
	}
}
void display_solution(State cap, State goal){
	return ;
}
int main(int argc, char * const argv[]){
	int c = argc;
	vector<string> v;
	v = {"0",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]};
	int num_test =isNumber(v);
	int capA,capB,capC,goalA,goalB,goalC;
	if(c != 7){
		// Prints Usage if improper number of arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
		return 1;
		if(num_test!=-1){
			cerr << "Error: Invalid capacity '" << (char)num_test << "' for jug "<< toupper(isJug(v)) <<"."  << endl;
			return 1;
		}
		capA=stoi(v[1]), capB=stoi(v[2]), capC=stoi(v[3]), goalA=stoi(v[4]), goalB=stoi(v[5]), goalC=stoi(v[6]);
		if(goalA>capA || goalB>capB || goalC>capC){
			if(goalA>capA){
				cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			}  else if(goalB>capB){
				cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
			} else {
				cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
			}
			return 1;
		} else if(goalA+goalB+goalC != capC){
			cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
			return 1;
		} else{
			State cap(capA,capB,capC);
			State goal(goalA,goalB,goalC);
			State result(0,0,cap.c);
			bool solution = find_solution(cap, goal,result);
			if (solution){
				//display_solution(cap, cap);
				cout << "trueeee" << endl;
			} else {
				cout << "No Solution." << endl;
			}
			return 0;
		}
	}
}
