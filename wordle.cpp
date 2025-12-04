#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
#include <unordered_map>
#include <map>
using namespace std;


// Add prototypes of helper functions here

void recurse(std::set<std::string>& results ,
            std::string current, 
            const std::string& in, 
            const std::string& floating,
            const std::set<std::string>& dict,
            int position);

void permutation_helper(std::set<std::string>& results, std::string input, std::string alphabet, std::map<int, char>& item_map);

std::set<std::string> get_permutations(const std::string& in, const std::string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    
    std::set<std::string> results;
		std::set<std::string> permutations = get_permutations(in, floating);

		for (std::set<std::string>::iterator it = permutations.begin(); it != permutations.end(); ++it) 
		{
			std::string temp = *it;
			recurse(results, temp, temp, floating, dict, 0);
		}

    return results;

}

std::set<std::string> get_permutations(const std::string& in, const std::string& floating) 
{
    /*
    
    three steps:
    1. build the substring that we're going to be permuting over
    2. permute over it
    3. reconstruct original string and insert it into the set
    
    */

    // 1. count how many - characters are in in, then concatanate 

    std::string working_string = floating;
    size_t count = 0;

    std::map<int, char> item_map;

    for (int i = 0; i < in.length(); i++) {
        if (in[i] == '-') {
            count++;
            if (count > floating.length()) {
                working_string += "-";
            }
        }
				else {
					item_map[i] = in[i];
				}
    }

    std::set<std::string> results;

		// 2. permute

    permutation_helper(results, "", working_string, item_map);
	
    return results;

}

void permutation_helper(std::set<std::string>& results, std::string input, std::string alphabet, std::map<int, char>& item_map)
{

    if (alphabet.empty()) {

				for (std::map<int, char>::iterator it = item_map.begin(); it != item_map.end(); ++it) {
					input.insert(it->first, 1, it->second);
				}

        results.insert(input);

        return;
    }

    for (int i = 0; i < alphabet.length(); ++i) {

        std::string new_input = input;
        std::string new_alphabet = alphabet;

        new_input.insert(input.length(), 1, alphabet[i]);
        new_alphabet.erase(i,1);

        permutation_helper(results, new_input, new_alphabet, item_map);

    }

}

void recurse(std::set<std::string>& results ,
            std::string current, 
            const std::string& in, 
            const std::string& floating,
            const std::set<std::string>& dict,
            int position) 
{

    if (current.length() == position)
    {

				

        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }

        return;
    }

    if (in[position] != '-') 
    {
        recurse(results, current, in, floating, dict, position + 1);
    }

    else 
    {
        for (int i = 0; i < 26; i++)
        {
						std::string new_current = current;
						new_current[position] = 'a' + i;
            
            recurse(results, new_current, in, floating, dict, position + 1);
        }
    }
}

// Define any helper functions here
