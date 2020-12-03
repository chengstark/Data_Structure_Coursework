#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


// function to readin a file input and convert it into a 2D vector
vector<vector<char> > file_parser(string filename){
    ifstream fin;
    fin.open(filename, ios::in);

    char current_currenter ;
    vector<vector<char> > result;
    vector<char> oneline;
    //parsing into a 2D vector
    while (!fin.eof() ) {      
        fin.get(current_currenter);
        oneline.push_back(current_currenter);  
        if (current_currenter == '\n'){
            result.push_back(oneline);
            oneline.clear();
        }
    }
    return result;
}

/*
The number and purpose of the remaining arguments on the command line depend on the operation. For
a replace operation, the 4th argument is the character that should be removed from the image and the 5th
argument is the character that should be substituted in those locations. For the dilation operation, the
4th argument is the foreground character (clusters of pixels of this “color” should increase in size). For the
erosion operation, the 4th argument is the foreground character (clusters of pixels of this “color” should
decrease in size). We also need to know the background color that will replace pixels that are removed from
the foreground object and the 5th argument is that background character.
Note that certain ASCII characters have special meaning on the command line, and it will be necessary to
escape that meaning by preceding those characters by a backslash to make sure your program receives
the desired character.
*/


// erosion function
vector<vector<char> > erosion(vector<vector<char> > matrix, char foreground_char, char background_char){
	vector<vector<int> > xy_tobefixed;
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		// current point is not target char
    		if(matrix[i][j] == foreground_char){
    			// non edge locations
	    		if(i!=0&&i!=(matrix.size()-1)&&j!=0&&j!=(matrix[0].size()-1)){
	    			// if overlay with all pixels of the structuring elemens, dont do anything
	    			 if (matrix[i+1][j] == foreground_char && matrix[i-1][j] == foreground_char && matrix[i][j+1] == foreground_char && matrix[i][j-1] == foreground_char){
	    			 	continue;
	    			 }
	    			 // count how many overlays of structuring element overlay with target char
	    			int count = 0;
	    			// upper and left part of structuring element overlay with target char
	    			if(matrix[i-1][j] == foreground_char && matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// lower and left part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char && matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// upper and right part of structuring element overlay with target char
	    			else if(matrix[i-1][j+1] == foreground_char && matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// lower and right part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char && matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// lower part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char){
	    				count++;
	    			}
	    			// upper part of structuring element overlay with target char
	    			else if(matrix[i-1][j] == foreground_char){
	    				count++;
	    			}
	    			// left part of structuring element overlay with target char
	    			else if(matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// right part of structuring element overlay with target char
	    			else if(matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// if overlay valid, store the coordinates for modification later on
	    			if(count == 1){
	    				vector<int> vec;
	    				vec.push_back(i);
	    				vec.push_back(j);
	    				xy_tobefixed.push_back(vec);
	    			}
	    		}
	    		// edge case, first line
	    		if(i == 0){
	    			// upper left corner of the whole graph
	    			if(j == 0){
	    				int count = 0;
	    				// lower and right part of structuring element overlay with target char
	    				if(matrix[i+1][j] == foreground_char && matrix[i][j+1]){
	    					count++;
	    				}
	    				// lower part of structuring element overlay with target char
	    				else if(matrix[i+1][j] == foreground_char){
	    					count++;
	    				}
	    				// right part of structuring element overlay with target char
	    				else if(matrix[i][j+1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			// upper right corner of the whole graph
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				// lower and right part of structuring element overlay with target char
	    				if(matrix[i+1][j] == foreground_char && matrix[i][j-1]){
	    					count++;
	    				}
	    				// lower part of structuring element overlay with target char
	    				else if(matrix[i+1][j] == foreground_char){
	    					count++;
	    				}
	    				// left part of structuring element overlay with target char
	    				else if(matrix[i][j-1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}
	    		// edge case last line
	    		else if(i == (matrix.size()-1)){
	    			// lower left corner of the whole graph
	    			if(j == 0){
	    				int count = 0;
	    				// upper and right part of structuring element overlay with target char
	    				if(matrix[i-1][j] == foreground_char && matrix[i][j+1]){
	    					count++;
	    				}
	    				// upper part of structuring element overlay with target char
	    				else if(matrix[i-1][j] == foreground_char){
	    					count++;
	    				}
	    				// right part of structuring element overlay with target char
	    				else if(matrix[i][j+1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			// lower right corner of the whole map
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				// upper and left part of structuring element overlay with target char
	    				if(matrix[i-1][j] == foreground_char && matrix[i][j-1]){
	    					count++;
	    				}
	    				// upper part of structuring element overlay with target char
	    				else if(matrix[i-1][j] == foreground_char){
	    					count++;
	    				}
	    				// left part of structuring element overlay with target char
	    				else if(matrix[i][j-1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}

    		}
    	}
    }
    // modify all locations with new background char
    for(vector<int> xy : xy_tobefixed){
    	matrix[xy[0]][xy[1]] = background_char;
    }
    return matrix;
}

//dilation function
vector<vector<char> > dilation(vector<vector<char> > matrix, char foreground_char){
	vector<vector<int> > xy_tobefixed;
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		// current point is not target char
    		if(matrix[i][j] != foreground_char){
    			//non edge location
	    		if(i!=0&&i!=(matrix.size()-1)&&j!=0&&j!=(matrix[0].size()-1)){
	    			// count how many overlays of structuring element overlay with target char
	    			int count = 0;
	    			// upper and left part of structuring element overlay with target char
	    			if(matrix[i-1][j] == foreground_char && matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// lower and left part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char && matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// upper and right part of structuring element overlay with target char
	    			else if(matrix[i-1][j+1] == foreground_char && matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// lower and right part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char && matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// lower part of structuring element overlay with target char
	    			else if(matrix[i+1][j] == foreground_char){
	    				count++;
	    			}
	    			// upper part of structuring element overlay with target char
	    			else if(matrix[i-1][j] == foreground_char){
	    				count++;
	    			}
	    			// left part of structuring element overlay with target char
	    			else if(matrix[i][j-1] == foreground_char){
	    				count++;
	    			}
	    			// right part of structuring element overlay with target char
	    			else if(matrix[i][j+1] == foreground_char){
	    				count++;
	    			}
	    			// if overlay valid, store the coordinates for modification later on
	    			if(count == 1){
	    				vector<int> vec;
	    				vec.push_back(i);
	    				vec.push_back(j);
	    				xy_tobefixed.push_back(vec);
	    			}
	    		}
	    		//edge case, first line
	    		if(i == 0){
	    			// upper left corner of the whole graph
	    			if(j == 0){
	    				int count = 0;
	    				// lower and right part of structuring element overlay with target char
	    				if(matrix[i+1][j] == foreground_char && matrix[i][j+1]){
	    					count++;
	    				}
	    				// lower part of structuring element overlay with target char
	    				else if(matrix[i+1][j] == foreground_char){
	    					count++;
	    				}
	    				// right part of structuring element overlay with target char
	    				else if(matrix[i][j+1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			// upper right corner of the whole graph
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				// lower and right part of structuring element overlay with target char
	    				if(matrix[i+1][j] == foreground_char && matrix[i][j-1]){
	    					count++;
	    				}
	    				// lower part of structuring element overlay with target char
	    				else if(matrix[i+1][j] == foreground_char){
	    					count++;
	    				}
	    				// left part of structuring element overlay with target char
	    				else if(matrix[i][j-1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}
	    		// edge case last line
	    		else if(i == (matrix.size()-1)){
	    			// lower left corner of the whole graph
	    			if(j == 0){
	    				int count = 0;
	    				// upper and right part of structuring element overlay with target char
	    				if(matrix[i-1][j] == foreground_char && matrix[i][j+1]){
	    					count++;
	    				}
	    				// upper part of structuring element overlay with target char
	    				else if(matrix[i-1][j] == foreground_char){
	    					count++;
	    				}
	    				// right part of structuring element overlay with target char
	    				else if(matrix[i][j+1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			// lower right corner of the whole map
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				// upper and left part of structuring element overlay with target char
	    				if(matrix[i-1][j] == foreground_char && matrix[i][j-1]){
	    					count++;
	    				}
	    				// upper part of structuring element overlay with target char
	    				else if(matrix[i-1][j] == foreground_char){
	    					count++;
	    				}
	    				// left part of structuring element overlay with target char
	    				else if(matrix[i][j-1] == foreground_char){
	    					count++;
	    				}
	    				// if overlay valid, store the coordinates for modification later on
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}

    		}
    	}
    }
    // modify all locations with new background char
    for(vector<int> xy : xy_tobefixed){
    	matrix[xy[0]][xy[1]] = foreground_char;
    }
    return matrix;
}


vector<vector<char> > replace(vector<vector<char> > matrix, char foreground_char, char background_char){
	vector<vector<int> > xy_tobefixed;
	// loop through all the pixels
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		// if target char is detected, replace it with the new char
    		if(matrix[i][j] == foreground_char){
    			matrix[i][j] = background_char;
    		}
    	}
    }
    return matrix;
}

// vector<vector<char> > opening(vector<vector<char> > matrix, char foreground_char, char background_char){
// 	vector<vector<char> > result_erosed = erosion(matrix, foreground_char, background_char);
// 	vector<vector<char> > result_dialed = dilation(result_erosed, foreground_char);
//     return result_dialed;
// }

// vector<vector<char> > closing(vector<vector<char> > matrix, char foreground_char, char background_char){
// 	vector<vector<char> > result_dialed = dilation(matrix, foreground_char);
// 	vector<vector<char> > result_erosed = erosion(result_dialed, foreground_char, background_char);
//     return result_erosed;
// }

//file writing function
void filewriter(vector<vector<char> > matrix, string filename){
	ofstream file(filename);
	// loop through all pixels and write them into a file, skip the original '\n'
    for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		if(matrix[i][j] == '\n'){
    			continue;
    		}
    		else{
    			file<<matrix[i][j];
    		}
    	}
    	// prevent last extra line
    	if(i != (matrix.size()-1)){
   			file<<'\n';
   		}
    }
	file.close();
}


int main(int argc, char* argv[]){
	// parse the input arguements 
	string input_filename = argv[1];
	string output_filename = argv[2];
	string command = argv[3];

	// create a matrix from the file
    vector<vector<char> > original_matrix = file_parser(input_filename);
    // replace excution
	if(command == "replace"){
		vector<vector<char> > result_matrix = replace(original_matrix, char(*argv[4]), char(*argv[5]));
		filewriter(result_matrix, output_filename);
	}
	// dilation excution
	else if(command == "dilation"){
		vector<vector<char> > result_matrix = dilation(original_matrix, char(*argv[4]));
		filewriter(result_matrix, output_filename);
	}
	// erosion excution
    else if(command == "erosion"){
		vector<vector<char> >  result_matrix = erosion(original_matrix, char(*argv[4]), char(*argv[5]));
		filewriter(result_matrix, output_filename);
	}
}