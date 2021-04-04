#include <iostream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

int palindromeLength(string str, int beginning, int end, int** array, const int length)
{
	//base condition: if end is before beginning
	if (beginning > end)
		return 0;

	//if the string only has one character, then the longest palindrome is 1
	if (beginning == end)
		return 1;

	//if the solution hasn't already been found (if array coords are empty)
	//solve it and store it in the array
	if (array[beginning][end] == NULL)
	{
		//if the first and last characters are the same, add to the palindrome
		//recursively search inward
		if (str[beginning] == str[end])
			array[length][length] = palindromeLength(str, beginning + 1, end - 1, array, length) + 2;
		else
			//if the first and last character are different:
			//find the max after recurring removing the first char and last char
			array[length][length] = max(palindromeLength(str, beginning, end - 1, array, length), palindromeLength(str, beginning + 1, end, array, length));
	}

	//return the subproblem solution
	return array[length][length];
}

string longestPalindrome(string str, string reverseStr, int strLength, int reverseLength, int** array)
{
	//return an empty string if we have reached the end of either string
	if (strLength == 0 || reverseLength == 0)
		return "";

	//if the last character of both strings match
	if (str[strLength - 1] == reverseStr[reverseLength - 1])
	{
		//concatinate the character to the palindrome string and recur
		return longestPalindrome(str, reverseStr, strLength - 1, reverseLength - 1, array) + str[strLength - 1];
	}
	//else the last characters are different
	//using the length of palindromes array found, decide what direction to continue looking for the palindrome
	if (array[strLength - 1][reverseLength] > array[strLength][reverseLength - 1])
		return longestPalindrome(str, reverseStr, strLength - 1, reverseLength, array);
	return longestPalindrome(str, reverseStr, strLength, reverseLength - 1, array);
}


int main()
{
	cout << "Enter string: " << endl;
	string str;
	cin >> str;

	int length = str.length();

	//create a 2D array to store solutions in
	//pointers because the size won't be known until after compiling
	// the solution will be stored in coord (length, length)
	int **array = new int*[length + 1];
	for (int i = 0; i < length + 1; ++i)
		array[i] = new int[length + 1];
	for (int i = 0; i < length + 1; ++i)
	{
		for (int j = 0; j < length + 1; ++j)
			array[i][j] = NULL;
	}

	string reverseStr = str;
	//user the reverse algorithm from c++'s library to make reverseStr
	reverse(reverseStr.begin(), reverseStr.end());

	string longestPal = longestPalindrome(str, reverseStr, length, length, array);

	int palLength = palindromeLength(str, 0, length - 1, array, length);

	cout << "The length of the longest palindrome is " << palLength << endl;

	cout << "The longest palindromic sequence is " << longestPal << endl;

	// my visual studio is dumb and needs this or it closes the window
	cout << "\nPress any key to continue...";
	cin.ignore();
	cin.get();
	return 0;
}