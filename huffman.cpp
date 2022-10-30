//-------------------------------- Problem ------------------------------------//
// Design a Huffman code for an English Language character set.
// Calculate the average length of the code.
// Compare it to the entropy of the English Language.
//-----------------------------------------------------------------------------//
#include<iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
using namespace std;
static int counter = 0;

class Huffman
{
public:
	string c;//The character
	string h;//Its huffman code
	double p;// The frequency of the character
	//int order;// tracer token for tracing with probability
	//Default constructor
	Huffman()
	{
		h = "";
	};
	//Non default constructor
	Huffman(string c, double f)
	{
		this->p = f;
		this->c = c;
		//this->order = i;
	};
	//To print the huffman code
	void  Huffman_print(Huffman* h_array)
	{
		//print the character and its huffman code for visualization
		for (int i = 0; i < 26; i++) {
			cout << h_array[i].c << "----->" << h_array[i].h << endl;
		}
	}
	void  Huffman_check_sort(Huffman* h_array)
	{
		//print the character and its frequency to check that the sort is successful
		for (int i = 0; i < 26; i++) {
			cout << h_array[i].c << "----->" << h_array[i].p << endl;
		}
	}
	Huffman* searcher_modifier(Huffman* h_array, Huffman A, Huffman B)
	{

		for (int i = 0; i < A.c.size(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (h_array[j].c[0] == A.c[i])
				{
					h_array[j].h = h_array[j].h + '1';
					break;
				}
			}
		}
		for (int i = 0; i < B.c.size(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (h_array[j].c[0] == B.c[i])
				{
					h_array[j].h = h_array[j].h + '0';
					break;
				}
			}
		}
		return h_array;
	}
	vector <Huffman> sort_Huff(vector <Huffman> operations)
	{
		stack<Huffman>s;
		int counter = 0;
		//takes the last element in the vector(The one added) and places it in position 
		Huffman temp = operations.back();
		operations.pop_back();
		//cout << "operation size: " << operations.size() << endl;		//debugging
		for (int i = operations.size() - 1; i >= 0; i--)
		{
			//cout << i << endl;			//debugging
			if (operations.at(i).p < temp.p)
			{
				counter++;
				s.push(operations.back());
				operations.pop_back();
			}
			else {
				break;
			}

		}
		operations.push_back(temp); // no changes happen push back the temp to its place 
		if (counter != 0)
		{
			while (s.empty() == false)
			{
				operations.push_back(s.top());
				s.pop();
			}

		}
		return operations;
	}
	Huffman* Create_Huffman(vector <Huffman> operations, Huffman* h_array)
	{

		if (counter != 25)
		{
			counter++;

			//sum last 2 elements
			Huffman A, B, C;
			string new_char;
			A = operations.back(); // last element
			operations.pop_back();
			B = operations.back();
			operations.pop_back();
			h_array = searcher_modifier(h_array, A, B); // increments the huffman code 
			new_char = A.c + B.c; // forms a new character and pushes it
			C = Huffman(new_char, A.p + B.p);//creating a combined character to use it for filling later
			operations.push_back(C);
			operations = sort_Huff(operations);
			//operations.push_back(C);
				// start from the end
				// check the order of the last 2 elements if not the same you can still add, if the same then we have reached the end
			return Create_Huffman(operations, h_array);
		}

		else
		{
			for (int i = 0; i < 26; i++)
			{
				reverse(h_array[i].h.begin(), h_array[i].h.end());// to reverse the huffman string 
			}
			return h_array;
		}


	}
};


Huffman* sort_func(Huffman* h_array)
{
	// To sort the array for the first time before beginning the process
	Huffman temp;
	for (int i = 0; i < 26; i++)
	{
		for (int j = i + 1; j < 26; j++)
		{
			if ((h_array[i].p) < (h_array[j].p))
			{
				temp = h_array[i];
				h_array[i] = h_array[j];
				h_array[j] = temp;
			}
		}
	}

	return h_array;
}
 
Huffman* Huffman_main(Huffman* h_array)
{
	sort_func(h_array);//sort once for the first time
	h_array->Huffman_check_sort(h_array);
	//---------------------------------Debugging------------------------------------//

	//h_array->Huffman_check_sort(h_array); // check that the array was sorted correctly for debugging

	//------------------------------------------------------------------------------//
	vector<Huffman> operations;
	for (int i = 0; i < 26; i++)
	{
		operations.push_back(h_array[i]);
	}
	counter = 0;
	h_array->Create_Huffman(operations, h_array);// This takes each huffman object and fills its huffman code
	//Print huffman codes
	h_array->Huffman_print(h_array);
	return h_array;
}
string Get_File_Content(string name)
{
	fstream my_file;
	string file_content="";
	my_file.open(name+".txt", ios::in);
	if (!my_file)
	{
		cout << "File not created!"<<endl;
	}
	else
	{
		cout << "File created successfully!"<<endl;
		my_file >> file_content;
		my_file.close();
	}	
	return file_content;
}
void Save_File_Content(string name,string huffman)
{
	fstream my_file;
	my_file.open(name+".txt", ios::out);
	if (!my_file)
	{
		cout << "File not created!"<<endl;
	}
	else
	{
		cout << "File created successfully!"<<endl;
		my_file << huffman;
		my_file.close();
	}
}
double* Frequency_file_former(string name,double* f_array_2)
{
	string content;
	content = Get_File_Content(name);
	string s;
	int counter_freq = 65; //ASCII for letter A
	int temp_counter=0;
	//double freq[26];
	while (counter_freq <= 90)
	{
		for (int i = 0; i < content.length(); i++)
		{
			//s.push_back(content[i]);
			if (content[i] == counter_freq)
			{
				temp_counter++;
			}
		}
		f_array_2[counter_freq - 65] = temp_counter;
		temp_counter = 0;
		counter_freq++;
	}
	return f_array_2;
}
double Frequency_Sum_Creator(Huffman* h_array)
{
	double sum = 0;
	for (int i = 0; i < 26; i++)
	{
		sum += h_array[i].p;
	}
	return sum;
}
double Average_Calc(Huffman* h_array)
{
	double avg = 0;
	double freq_sum = Frequency_Sum_Creator(h_array);
	for (int i = 0; i < 26; i++)
	{
		avg += h_array[i].h.length()* h_array[i].p/ freq_sum;
	}
	cout << "The average length is: " <<avg<<endl;
	return avg;
}
void main()
{
	/// <summary>
	/// the frequency was obtained from https://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
	/// 1.Create the arrays.
	/// 2.Create array of objects to encapsulate the data.
	/// 3.sort the array once before working on it.
	/// 4.Create vector of huffman objects to work on.
	/// 5.Call the function Create_Huffman which is responsible for creating the huffman code, this function calls several functions
	/// 6.print the huffman character and its encoding
	/// </summary>
	string c_array[26] = { "A","B","C","D","E","F","G","H","I","J" ,"K","L","M" ,"N","O","P" ,"Q","R","S" ,"T","U","V" ,"W","X","Y","Z" };
	double f_array[26] = { 8.12,1.49,2.71,4.32,12.02,2.30,2.03,5.92,7.31,0.10,0.69,3.98,2.61,6.95,7.68,1.82,0.11,6.02,6.28,9.10,2.88,1.11,2.09,0.17,2.11,0.07};
	Huffman h_array[26];//array of huffman objects
	for (int i = 0; i < 26; i++)
	{
		h_array[i] = Huffman(c_array[i], f_array[i]);
	}
	//up to this step we have an array of huffman objects which carry the character, the probability of the character, and the  huffman string.
	//we need to sort the array once before beginning and setting the order
	Huffman_main(h_array);
	//Task 2 Encoding a text file into huffman code
	
	string name;
	//cout << "Enter your file name: "; cin >> name;
	cout << "Enter your file name: "; cin >> name;
	string content =Get_File_Content(name);
	//cout << content;
	string huffman = "";
	string s;
	int huffman_size = 0;
	for (int i = 0; i < content.length(); i++)
	{
		s.push_back(content[i]);
		for (int j = 0; j <26; j++)
		{
			if (s == h_array[j].c)
			{	
				huffman = huffman + h_array[j].h;
				break;
			}
		}
		s.pop_back();
	}
	cout << "Enter your file name you would like to save to: "; cin >> name;
	cout <<"The huffman representation of the file is:"<<endl<<huffman<<endl;
	Save_File_Content(name, huffman);
	while (!huffman.empty())
	{
		huffman.pop_back();
		huffman_size++;
	}
	//cout << "The bit sequence length is:" << huffman_size << endl;

	//Task 3 
	cout << "Enter the file name you would like to gather the frequency from: "; cin >> name;
	double* f_array_2 = new double[26];
	f_array_2=Frequency_file_former(name, f_array_2);
	Huffman h_array_2[26];
	cout << f_array_2[1];
		for (int i = 0; i < 26; i++)
	{
		h_array_2[i] = Huffman(c_array[i], f_array_2[i]);
	}
	h_array_2->Huffman_check_sort(h_array_2);
	Huffman_main(h_array_2);
	s = "";
	for (int i = 0; i < content.length(); i++)
	{
		s.push_back(content[i]);
		for (int j = 0; j < 26; j++)
		{
			if (s == h_array_2[j].c)
			{
				huffman = huffman + h_array_2[j].h;
				break;
			}
		}
		s.pop_back();
	}
	int huffman_size_2 = 0;
	while (!huffman.empty())
	{
		huffman.pop_back();
		huffman_size_2++;
	}

	//----------------------------Entropy--------------------------------------------//
	double entropy = 0;
	double entropy_2 = 0;
	double temp_sum = 0;
	double temp_sum_2 = 0;
	for (int i = 0; i < 26; i++)
	{
		temp_sum = temp_sum + f_array[i];
		temp_sum_2 = temp_sum_2 + f_array_2[i];
	}
	for (int i = 0; i < 26; i++)
	{
		entropy += (f_array[i] / temp_sum * log2(f_array[i] / temp_sum));
		entropy_2 += (f_array_2[i] / temp_sum_2 * log2(f_array_2[i] / temp_sum_2));

	}
	entropy = entropy * -1;
	entropy_2 = entropy_2 * -1;

	//----------------------------------------------------------------------------------//


	cout << "---------------------------------------Using the english character freqency set-----------------------------------------" << endl;
	cout << "Sum of frequencies: " << temp_sum << endl;
	Average_Calc(h_array);
	cout << "The bit sequence length is:" << huffman_size<< endl;
	cout << "Entropy is: " << entropy << endl;
	cout << "-------------------------------------------Using the File character freqency set----------------------------------------" << endl;
	cout << "Sum of frequencies: " << temp_sum_2 << endl;
	cout << "The bit sequence length is:" << huffman_size_2 << endl;
	Average_Calc(h_array_2);
	cout << "Entropy is: " << entropy_2 << endl;

}