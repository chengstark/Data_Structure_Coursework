#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

vector<vector<char> > file_parser(string filename){
    ifstream fin;
    fin.open(filename, ios::in);

    char current_currenter ;
    int number_of_lines = 0;
    vector<vector<char> > result;
    vector<char> oneline;
    while (!fin.eof() ) {      
        fin.get(current_currenter);
        //cout << current_currenter;
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


 
vector<vector<char> > erosion(vector<vector<char> > matrix, char f_c, char b_c){
	vector<vector<int> > xy_tobefixed;
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		// current point is not target
    		if(matrix[i][j] == f_c){
    			//non edge
	    		if(i!=0&&i!=(matrix.size()-1)&&j!=0&&j!=(matrix[0].size()-1)){
	    			 if (matrix[i+1][j] == f_c && matrix[i-1][j] == f_c && matrix[i][j+1] == f_c && matrix[i][j-1] == f_c){
	    			 	continue;
	    			 }
	    			int count = 0;
	    			if(matrix[i-1][j] == f_c && matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c && matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i-1][j+1] == f_c && matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c && matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i-1][j] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			if(count == 1){
	    				vector<int> vec;
	    				vec.push_back(i);
	    				vec.push_back(j);
	    				xy_tobefixed.push_back(vec);
	    			}
	    		}
	    		//edge case, first line
	    		if(i == 0){
	    			if(j == 0){
	    				int count = 0;
	    				if(matrix[i+1][j] == f_c && matrix[i][j+1]){
	    					count++;
	    				}
	    				else if(matrix[i+1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j+1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				if(matrix[i+1][j] == f_c && matrix[i][j-1]){
	    					count++;
	    				}
	    				else if(matrix[i+1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j-1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}
	    		else if(i == (matrix.size()-1)){
	    			if(j == 0){
	    				int count = 0;
	    				if(matrix[i-1][j] == f_c && matrix[i][j+1]){
	    					count++;
	    				}
	    				else if(matrix[i-1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j+1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				if(matrix[i-1][j] == f_c && matrix[i][j-1]){
	    					count++;
	    				}
	    				else if(matrix[i-1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j-1] == f_c){
	    					count++;
	    				}
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
    for(vector<int> xy : xy_tobefixed){
    	matrix[xy[0]][xy[1]] = b_c;
    }
    return matrix;
}

vector<vector<char> > dilation(vector<vector<char> > matrix, char f_c){
	vector<vector<int> > xy_tobefixed;
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		// current point is not target
    		if(matrix[i][j] != f_c){
    			//non edge
	    		if(i!=0&&i!=(matrix.size()-1)&&j!=0&&j!=(matrix[0].size()-1)){
	    			int count = 0;
	    			if(matrix[i-1][j] == f_c && matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c && matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i-1][j+1] == f_c && matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c && matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i+1][j] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i-1][j] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i][j-1] == f_c){
	    				count++;
	    			}
	    			else if(matrix[i][j+1] == f_c){
	    				count++;
	    			}
	    			if(count == 1){
	    				vector<int> vec;
	    				vec.push_back(i);
	    				vec.push_back(j);
	    				xy_tobefixed.push_back(vec);
	    			}
	    		}
	    		//edge case, first line
	    		if(i == 0){
	    			if(j == 0){
	    				int count = 0;
	    				if(matrix[i+1][j] == f_c && matrix[i][j+1]){
	    					count++;
	    				}
	    				else if(matrix[i+1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j+1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				if(matrix[i+1][j] == f_c && matrix[i][j-1]){
	    					count++;
	    				}
	    				else if(matrix[i+1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j-1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    		}
	    		else if(i == (matrix.size()-1)){
	    			if(j == 0){
	    				int count = 0;
	    				if(matrix[i-1][j] == f_c && matrix[i][j+1]){
	    					count++;
	    				}
	    				else if(matrix[i-1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j+1] == f_c){
	    					count++;
	    				}
	    				if(count == 1){
	    					vector<int> vec;
	    					vec.push_back(i);
	    					vec.push_back(j);
	    					xy_tobefixed.push_back(vec);
	    				}
	    			}
	    			else if(j == (matrix[0].size()-1)){
	    				int count = 0;
	    				if(matrix[i-1][j] == f_c && matrix[i][j-1]){
	    					count++;
	    				}
	    				else if(matrix[i-1][j] == f_c){
	    					count++;
	    				}
	    				else if(matrix[i][j-1] == f_c){
	    					count++;
	    				}
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
    for(vector<int> xy : xy_tobefixed){
    	matrix[xy[0]][xy[1]] = f_c;
    }
    return matrix;
}


vector<vector<char> > replace(vector<vector<char> > matrix, char f_c, char b_c){
	vector<vector<int> > xy_tobefixed;
	for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		if(matrix[i][j] == f_c){
    			matrix[i][j] = b_c;
    		}
    	}
    }
    return matrix;
}

vector<vector<char> > opening(vector<vector<char> > matrix, char f_c, char b_c){
	vector<vector<char> > result_erosed = erosion(matrix, f_c, b_c);
	vector<vector<char> > result_dialed = dilation(result_erosed, f_c);
    return result_dialed;
}

vector<vector<char> > closing(vector<vector<char> > matrix, char f_c, char b_c){
	vector<vector<char> > result_dialed = dilation(matrix, f_c);
	vector<vector<char> > result_erosed = erosion(result_dialed, f_c, b_c);
    return result_erosed;
}


void filewriter(vector<vector<char> > matrix, string filename){
	ofstream file(filename);
	//file.open (filename);
	//file<< matrix[0][0];
    for(int i = 0; i < matrix.size(); i++){
    	for(int j = 0; j< matrix[i].size(); j++){
    		file<<matrix[i][j];
    	}
    	//file<<endl;
    }
	file.close();

}


int main(int argc, char* argv[]){
	string input_filename = argv[1];
	string output_filename = argv[2];
	string command = argv[3];

    vector<vector<char> > original = file_parser(input_filename);
	if(command == "replace"){
		vector<vector<char> > result_matrix = replace(original, char(*argv[4]), char(*argv[5]));
		filewriter(result_matrix, output_filename);
	}
	else if(command == "dilation"){
		vector<vector<char> > result_matrix = dilation(original, char(*argv[4]));
		filewriter(result_matrix, output_filename);
	}
    else if(command == "erosion"){
		vector<vector<char> >  result_matrix = erosion(original, char(*argv[4]), char(*argv[5]));
		filewriter(result_matrix, output_filename);
	}
	// else if(command == "opening"){
		
	// }
	// else if(command == "closing"){
		
	// }

 //    cout<<"--------------------------------------"<<endl;

 //    for(int i = 0; i < ro.size(); i++){
 //    	for(int j = 0; j< ro[i].size(); j++){
 //    		cout<<ro[i][j];
 //    	}
 //    	cout<<"\n";
 //    }
 //    cout<<endl;


 //    cout<<"--------------------------------------"<<endl;


 //    vector<vector<char> > rd = dilation(ro, 'X');

 //    for(int i = 0; i < rd.size(); i++){
 //    	for(int j = 0; j< rd[i].size(); j++){
 //    		cout<<rd[i][j];
 //    	}
 //    	cout<<"\n";
 //    }
 //    cout<<endl;

	// cout<<"--------------------------------------"<<endl;


    // vector<vector<char> > re = erosion(original, 'X', '.');

    // for(int i = 0; i < re.size(); i++){
    // 	for(int j = 0; j< re[i].size(); j++){
    // 		cout<<re[i][j];
    // 	}
    // 	cout<<"\n";
    // }
    // cout<<endl;


 //    cout<<"--------------------------------------"<<endl;


 //    vector<vector<char> > rp = replace(ro, 'X', 'O');

 //    for(int i = 0; i < rp.size(); i++){
 //    	for(int j = 0; j< rp[i].size(); j++){
 //    		cout<<rp[i][j];
 //    	}
 //    	cout<<"\n";
 //    }
 //    cout<<endl;

	// cout<<"--------------------------------------"<<endl;


 //    vector<vector<char> > rop = opening(ro, 'X', '.');

 //    for(int i = 0; i < rop.size(); i++){
 //    	for(int j = 0; j< rop[i].size(); j++){
 //    		cout<<rop[i][j];
 //    	}
 //    	cout<<"\n";
 //    }
 //    cout<<endl;

 //    cout<<"--------------------------------------"<<endl;


 //    vector<vector<char> > rc = closing(ro, 'X', '.');

 //    for(int i = 0; i < rc.size(); i++){
 //    	for(int j = 0; j< rc[i].size(); j++){
 //    		cout<<rc[i][j];
 //    	}
 //    	cout<<"\n";
 //    }
 //    cout<<endl;

 //    return 0;
}