# Huffman
The frequency was obtained from https://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
	 1.Create the arrays.
	 2.Create array of objects to encapsulate the data.
	 3.sort the array once before working on it.
	 4.Create vector of huffman objects to work on.
	 5.Call the function Create_Huffman which is responsible for creating the huffman code, this function calls several functions
	 6.print the huffman character and its encoding
	 
#Functions
The first function is the main function which is the function where the frequency array and the character arrays where declared.
string c_array[26] = { "A","B","C","D","E","F","G","H","I","J" ,"K","L","M" ,"N","O","P" ,"Q","R","S" ,"T","U","V" ,"W","X","Y","Z" };
double f_array[26] = { 8.12,1.49,2.71,4.32,12.02,2.30,2.03,5.92,7.31,0.10,0.69,3.98,2.61,6.95,7.68,1.82,0.11,6.02,6.28,9.10,2.88,1.11,2.09,0.17,2.11,0.07 };

The character aray is declared as a string due to casting issues that would be discussed later in this documentation	