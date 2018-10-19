/* Waterjugpuzzle.cpp
 * Created on: Oct 4, 2018
 * Damon Del Priore and Brandon Soong
 * I pledge my honor that I have abided by the Stevens Honor System
 */

#include "Waterjugpuzzle.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>


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
	void add_direction(string s){
		//void function that pushes a string into vector directions
		directions.push_back(s);
	}
	bool operator==(State s){
		//overloading operator allows for comparison using ==
		return this->a == s.a && this->b==s.b;
	}
	void print_directions() {
		//print functions of directions
		int size = directions.size();
		for (int i = 0; i < size; i++) {
			cout << directions[i] << endl;
		}
	}

};

// Create global variables for the cap and goal states
State cap(0,0,0);
State goal(0,0,0);
void setCap(State c){
	//setter for cap
	cap = c;
}
State getCap() {
	//getter for cap
	return cap;
}
void setGoal(State g){
	//setter for goal
	goal = g;
}
State getGoal() {
	//getter for goal
	return goal;
}

State pour(State r, int case_num){
	//Pour function that runs through all 6 specific states and prints the proper output.
	int i = case_num;
	State cap = getCap();
	State result = r;
	string AtoC = "";
	if (i==1){
		// Pour from C to A
		if(result.a < cap.a && result.c>0){
			int value1 = result.c;
			result.a += result.c;
			result.c -= result.c;
			if(result.a > cap.a){
				while(result.a!=cap.a){
					result.a -= 1;
					result.c += 1;
					value1--;
				}
			}
			if (value1 == 1){
				AtoC = "Pour 1 gallon from C to A. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value1) + " gallons from C to A. " + result.to_string();
			}
		}
	}
	if (i==2){
		// Pour from B to A
		if(result.a < cap.a && result.b>0){
			int value2 = result.b;
			result.a += result.b;
			result.b -= result.b;
			if(result.a > cap.a){
				while(result.a!=cap.a){
					result.a -= 1;
					result.b += 1;
					value2 --;
				}
			}
			if (value2 == 1){
				AtoC = "Pour 1 gallon from B to A. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value2) + " gallons from B to A. " + result.to_string();
			}
		}
	}
	if (i == 3){
		// Pour from C to B
		if(result.b < cap.b && result.c>0){
			int value3 = result.c;
			result.b += result.c;
			result.c -= result.c;
			if(result.b > cap.b){
				while(result.b!=cap.b){
					result.b -= 1;
					result.c += 1;
					value3--;
				}
			}
			if (value3 == 1){
				AtoC = "Pour 1 gallon from C to B. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value3) + " gallons from C to B. " + result.to_string();
			}
		}
	}
	if (i == 4){
		// Pour from A to B
		if(result.b < cap.b && result.a>0){
			int value4 = result.a;
			result.b += result.a;
			result.a -= result.a;
			if(result.b > cap.b){
				while(result.b!=cap.b){
					result.b -= 1;
					result.a += 1;
					value4--;
				}
			}
			if (value4 == 1){
				AtoC = "Pour 1 gallon from A to B. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value4) + " gallons from A to B. " + result.to_string();
			}
		}
	}
	if(i == 5){
		// Pour from B to C
		if(result.c < cap.c && result.b>0){
			int value5 = result.b;
			result.c += result.b;
			result.b -= result.b;
			if(result.c > cap.c){
				while(result.c!=cap.c){
					result.c -= 1;
					result.b += 1;
					value5--;
				}
			}
			if (value5 == 1){
				AtoC = "Pour 1 gallon from B to C. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value5) + " gallons from B to C. " + result.to_string();
			}
		}
	}
	if(i == 6){
		// Pour from A to C
		if(result.c < cap.c && result.a>0){
			int value6 = result.a;
			result.c += result.a;
			result.a -= result.a;
			if(result.c > cap.c){
				while(result.c!=cap.c){
					result.c -= 1;
					result.a += 1;
					value6--;
				}
			}
			if (value6 == 1){
				AtoC = "Pour 1 gallon from A to C. " + result.to_string();
			} else {
				AtoC = "Pour " + to_string(value6) + " gallons from A to C. " +  result.to_string();
			}
		}
	}
	result.add_direction(AtoC);
	return result;

}

void find_solutions(int c){
	//Find solutions function that implements a queue and a while loop. Has the initial state print statement, and the no solution call.
	bool visited[1000][1000];
	State g = getGoal();
	vector<State> exists;
	int cCap = c;
	State initial(0,0,cCap);
	queue<State> q;
	q.push(initial);
	visited[initial.a][initial.b] = true;
	vector<State> next;
	while (!q.empty()) {
		State front = q.front();
		for(int i=1; i<=6;i++){
			if(front == g ){
				cout << "Initial state. " << initial.to_string() << endl;
				front.print_directions();
				return;
			}
			next.push_back(pour(front, i));
		}
		for (auto &s: next) {
			if(!(s==front)){
				if(!visited[s.a][s.b]){
					visited[s.a][s.b] = true;
					q.push(s);
				}
			}
		}
		q.pop();
	}
	cout<< "No solution." << endl;
}

int main(int argc, char * const argv[]){
	if(argc != 7){
		// Prints Usage if improper number of arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
		return 1;
	}
	istringstream is1(argv[1]), is2(argv[2]), is3(argv[3]), is4(argv[4]), is5(argv[5]), is6(argv[6]);
	int capA, capB, capC, goalA, goalB, goalC;
	// Check for proper inputs in each jug using stringstream, otherwise print an error
	if(!(is1 >> capA) || capA<0){
		cerr << "Error: Invalid capacity '" << is1.str() << "' for jug A."  << endl;
		return 1;
	} if (!(is2 >> capB) || capB<0){
		cerr << "Error: Invalid capacity '" << is2.str() << "' for jug B."  << endl;
		return 1;
	} if (!(is3 >> capC) || capC<0){
		cerr << "Error: Invalid capacity '" << is3.str() << "' for jug C."  << endl;
		return 1;
	} if (!(is4 >> goalA)|| goalA<0){
		cerr << "Error: Invalid goal '" << is4.str() << "' for jug A."  << endl;
		return 1;
	} if (!(is5 >> goalB)|| goalB<0){
		cerr << "Error: Invalid goal '" << is5.str() << "' for jug B."  << endl;
		return 1;
	} if (!(is6 >> goalC) || goalC<0){
		cerr << "Error: Invalid goal '" << is6.str() << "' for jug C."  << endl;
		return 1;
	} if(capC == 0){
		// Capacity of JugC cannot equal 0
		cout << "Error: Invalid capacity '0' for jug C.";
		return 1;
	} if(goalA>capA){
		// If any of the goals are greater than it's cap, print proper error
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	} if(goalB>capB){
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	} if(goalC>capC) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	} if(goalA+goalB+goalC != capC){
		// If sum of all goals is greater than the capacity of C, error
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	State cap(capA,capB,capC);
	State goal(goalA,goalB,goalC);
	setCap(cap);
	setGoal(goal);
	find_solutions(cap.c);
	return 0;
}
