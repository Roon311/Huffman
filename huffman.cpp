//-------------------------------- Problem ------------------------------------//
// Design a Huffman code for an English Language character set.
// Calculate the average length of the code.
// Compare it to the entropy of the English Language.
//-----------------------------------------------------------------------------//
#include<iostream>
#include <vector>
#include <stack>
using namespace std;
static int counter = 0;

class Huffman
{
public:
	string c;//The character
	string h;//Its huffman code
	double p;
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
		for (int i = 0; i < 26; i++) {
			cout << h_array[i].c << "----->" << h_array[i].h << endl;
		}
	}
	void  Huffman_check_sort(Huffman* h_array)
	{
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
		cout << "operation size: " << operations.size() << endl;
		for (int i = operations.size() - 1; i >= 0; i--)
		{
			cout << i << endl;
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
		//  a		b		c		  d		      e
		// 0.25	  0.125    0.125    0.125		0.1257
		int cursor = 0; // cursor that would be used during looping

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
	Huffman temp, temp_1, temp_2;
	for (int i = 0; i < 26; i++)
	{
		for (int j = i + 1; j < 26; j++)
		{
			if ((h_array[i].p) < (h_array[j].p))
			{
				temp = h_array[i];
				h_array[i] = h_array[j];
				h_array[j] = temp;
				//h_array[i].order = i;// you did not debug this yet
				//h_array[j].order = j;// you did not debug this yet
			}
		}
	}

	return h_array;
}
// 
void main()
{
	string c_array[26] = { "A","B","C","D","E","F","G","H","I","J" ,"K","L","M" ,"N","O","P" ,"Q","R","S" ,"T","U","V" ,"W","X","Y","Z" };
	double f_array[26] = { 8.12,1.49,2.71,4.32,12.02,2.30,2.03,5.92,7.31,0.10,0.69,3.98,2.61,6.95,7.68,1.82,0.11,6.02,6.28,9.10,2.88,1.11,2.09,0.17,2.11,0.07 };
	Huffman h_array[26];//array of huffman objects
	for (int i = 0; i < 26; i++)
	{
		h_array[i] = Huffman(c_array[i], f_array[i]);
	}
	//up to this step we have an array of huffman objects which carry the character, the probability of the character, and the  huffman string.
	//we need to sort the array once before beginning and setting the order
	sort_func(h_array);
	h_array->Huffman_check_sort(h_array); // check that the array was sorted correctly for debugging
	vector<Huffman> operations;
	for (int i = 0; i < 26; i++)
	{
		operations.push_back(h_array[i]);
	}
	h_array->Create_Huffman(operations, h_array);// This takes each huffman object and fills its huffman code
	//Print huffman codes
	h_array->Huffman_print(h_array);
}