/*
@title		PA3, Part 2: Data Extraction from HTML file Using REGEX
@author		Oneal Abdulrahim
@course		CSCE 221-503
@due		20 October 2016
@purpose	This program intends to extend the student's knowledge of the
			Linked List data structure, as well as expose the student to REGEX
			and their usage in C++. We will also discover that industry experts
			will laugh in our faces if we ever try to use REGEX to parse HTML.
*/
#include <string>
#include <iostream>
#include <fstream>
#include <list> // no trust of my implementation :p
#include <vector>
#include <regex>
using namespace std;

// forward declare
struct PTNode;
void getPeerTeachers(regex name_pattern, regex email_pattern,
					 regex courses_pattern, string file_name);

int main() {
	// get all the names, courses, emails with these expressions
	regex name{R"(<h3>([A-Z][a-z]+ .+)<\/h3>)"};
	regex email{R"((\w+)(\.|_)?(\w*)@(\w+)(\.)?(\w+).(\w+))"};
	regex courses{R"(CSCE [0-9][0-9][0-9])"};
	
	// print out the expressions
	cout << "Names found by: \t(<h3>([A-Z][a-z]+ .+)<\\/h3>)" << endl
		 << "Emails found by:\t((\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.)?(\\w+).(\\w+))"
		 << endl << "Courses found by:\t(CSCE [0-9][0-9][0-9])\n" << endl;
	
	// do everything else (methods described below)
	getPeerTeachers(name, email, courses, "file.html");
	
	return 0; // safely exit
}

/// Peer Teacher node
/*
The data payload for each linked list of PT's
@property name		A string containing the peer teacher's first and last names
@property email		A string containing the peer teacher's email
@property courses	A string containing all the courses the PT teaches */
struct PTNode {
	string name;
	string email;
	string courses;
	
	// Default constructor (email default value allows for easy spotting of
	// empty or incorrect objects)
	PTNode(string n = "", string e = "noemail@tamu.edu", string c = "| ")
			: name(n), email(e), courses(c) {}		
};

/// Output operator overload
//Overloads ostream << to allow for proper output of a Peer Teacher Node object
ostream& operator << (ostream &out, const PTNode &ptnode) {
		out << ptnode.name << " ("
			<< ptnode.email <<")\n"
			<< ptnode.courses << endl << endl;
		return out;
}

/// Data extraction and printing
/*
This method does everything the assignment asks for:
	-- loads a html file to parse using regex expressions
	-- reads the file line by line and loads PTNode objects with data found
	-- loads linked list of each PTNodes to a vector of linked lists
	-- prints this vector
	
	-- categorizes peer teachers by courses taught
	-- loads this into vector of linked lists (where each LL is a course)
	-- prints this vector
This method also keeps us from stuffing everything in main
@param	name_pattern		The regex pattern for finding names
@param	email_pattern		The regex pattern for finding emails
@param	courses_pattern		The regex pattern for finding courses
@param	file_name			The name of the file to read from */
void getPeerTeachers(regex name_pattern, regex email_pattern,
					 regex courses_pattern, string file_name) {
	vector<list<PTNode>> peer_teachers;
	
	// reading in from a file called file_name
	ifstream html_file(file_name);
	string line;
	
	// create smatch objects for each match type
	smatch name_match;
	smatch email_match;
	smatch course_match;
	
	// will be our temporary nodes for PT data throughout matching
	PTNode* temp = new PTNode();
	
	// we will use this later when making lists organized by course id
	// it will be loaded with ID's when found a course #
	vector<int> courses;
	
	// read line by line and check for matches of each type
	while (getline(html_file, line)) {
		// Does the line have any names?
		regex_search(line, name_match, name_pattern);
		if (name_match[1] != "") {
			// If we match a name, it's the start of a new PT
			list<PTNode> pt_info;
			pt_info.push_back(*temp);
			
			// push back the vector of PT's
			peer_teachers.push_back(pt_info);
			temp = new PTNode(); // reset our temp
			
			temp -> name = name_match[1]; // load name
		}
		
		// Does the line have any emails?
		regex_search(line, email_match, email_pattern);
		if (email_match[0] != "") {
			temp -> email = email_match[0]; // loads email
		}
		
		// Does the line have any courses?
		regex_search(line, course_match, courses_pattern);
		for (string match : course_match) {
			if (match != "") {
				temp -> courses.append(match).append(" | "); // loads course
				// checks to see if we have the course id already recorded,
				// then adds it into the course ids vector
				if (find(courses.begin(), courses.end(), stoi(match.substr(5)))
					== courses.end()) {
					courses.push_back(stoi(match.substr(5)));		
				}
			}
		}
	}
	
	// my implementation adds an empty PT at the front, so let's delete it
	// cheap and easy
	peer_teachers.erase(peer_teachers.begin());
	
	// print out all of the peer teacher's names, emails, and course info
	list<PTNode>::const_iterator j;
	for (int i = 0; i < peer_teachers.size(); ++i) {
		for (j = peer_teachers[i].begin(); j != peer_teachers[i].end(); ++j) {
			if (j -> courses != "| ") {
				cout << *j; // ***as long as they have courses!***
			}
		}
	}
	
	// vector of string linked lists for organizaiton by course
	// string type because my implementation used strings to store course ID's
	vector<list<string>> by_course;
	sort(courses.begin(), courses.end()); // go from low --> high level courses
	
	/*
	Below loop structure:
	
	for every course id in courses:
		for every peer teacher linked list:
			for every peer teacher node:
				if their course matches the current course
					if their name isnt already in the names
						add their name
	
	pure sadness and O(n^2) but hey it works */
	
	list<string>::const_iterator k;
	// we have all the course id's already, from the above declared vector
	for (int m = 0; m < courses.size(); ++m) {
		list<string> names;
		names.push_back(to_string(courses[m])); // first index is course #
		
		list<PTNode>::const_iterator o;
		for (int n = 0; n < peer_teachers.size(); ++n) { // go through all PT's
			for (o = peer_teachers[n].begin(); o != peer_teachers[n].end(); ++o) {
				// if the course id is found within the PT's courses,
				if (((o -> courses).find(to_string(courses[m]))) != string::npos) {
					// and if the name of the PT isn't already added in our list
					if (find(names.begin(), names.end(), o -> name) == names.end())
						names.push_back(o -> name); // add PT name to names
				}
			}
		}
		by_course.push_back(names); // add our list to vector
	}
	
	// finally, print out names by their course #
	for (int i = 0; i < by_course.size(); ++i) {
		cout << "----- PT's for CSCE " << *by_course[i].begin()
			 << " -----" << endl;
		int count = 0;
		for (k = by_course[i].begin(); k != by_course[i].end(); ++k) {
			++count;
			if (k == by_course[i].begin()) ++k; // the first item is course #
			cout << *k << '\n';
		}
		
		cout << "\nTotal: " << count << endl << endl;
	}
}