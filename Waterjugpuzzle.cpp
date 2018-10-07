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

};
bool isNumber(vector<string> n){
	for(string s : n){
		for(char c: s){
			if(!isdigit(c)){
				return false;
			}
		}
	}
	return true;
}
string find_fail_string(vector<string> n){
	for(string s : n){
		for(char c: s){
			if(!isdigit(c)){
				return s;
			}
		}
	}
	return " ";
}
char isJug(vector<string> n){
	int size = n.size();
	for(int i=1; i<size; i++){
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


void display_solution(State cap, State goal){
	return ;
}


int main(int argc, char * const argv[]){
	if(argc != 7){
		// Prints Usage if improper number of arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
		return 1;
	}
	vector<string> v;
	v = {"0",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]};
	string zero = "0";
	if(v[3]==zero){
		// Capacity of JugC cannot equal 0
		cout << "Error: Invalid capacity '0' for jug C.";
		return 1;
	}
	if(!isNumber(v)){
		// If all of the characters in each input string are not digits, do this
		int jug = isJug(v);
		// All Error messages based on which jug contained the first non-integer input
		if (jug==1){
			cerr << "Error: Invalid capacity '" << find_fail_string(v) << "' for jug A."  << endl;
		} else if (jug==2){
			cerr << "Error: Invalid capacity '" << find_fail_string(v) << "' for jug B."  << endl;
		} else if (jug==3) {
			cerr << "Error: Invalid capacity '" << find_fail_string(v) << "' for jug C."  << endl;
		} else if (jug==4){
			cerr << "Error: Invalid goal '" << find_fail_string(v) << "' for jug A."  << endl;
		} else if (jug==5){
			cerr << "Error: Invalid goal '" << find_fail_string(v) << "' for jug B."  << endl;
		} else {
			cerr << "Error: Invalid goal '" << find_fail_string(v) << "' for jug C."  << endl;
		}

		return 1;
	}
	int capA,capB,capC,goalA,goalB,goalC;
	capA=stoi(v[1]), capB=stoi(v[2]), capC=stoi(v[3]), goalA=stoi(v[4]), goalB=stoi(v[5]), goalC=stoi(v[6]);
	if(goalA>capA || goalB>capB || goalC>capC){
		// If any of the goals are greater than it's cap, print proper error
		if(goalA>capA){
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		}  else if(goalB>capB){
			cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		} else {
			cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		}
		return 1;
	} else if(goalA+goalB+goalC != capC){
		// If sum of all goals is greater than the capacity of C, error
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	} else{
		// If reaches this point, look for solution
		State cap(capA,capB,capC);
		State goal(goalA,goalB,goalC);
		State result(0,0,cap.c);
		bool solution = find_solution(cap, goal,result);
		if (solution){
			//display_solution(cap, goal);
			cout << "trueeee" << endl;
		} else {
			cout << "No Solution." << endl;
		}
		return 0;
	}
}
