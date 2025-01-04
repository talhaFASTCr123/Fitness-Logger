#pragma once
#include <fstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

bool validateUsername(string &username) {
  if (username == "" || username.length() > 15 || username.length() < 3) {
    cout << "Username must not be empty and should be between 3 and 15 characters long." << endl;
    return false;
  }

  // Replace spaces with underscores
  for (int i = 0; username[i] != '\0'; i++) {
    if (username[i] == ' ') {
      username[i] = '_'; // Replace space with underscore
    }
  }

  return true; // Return true if no empty string and spaces are replaced
}

bool validatePassword(string &password) { // Pass by reference to modify the input string
  // Check if password is not empty
  if (password == "") {
    cout << "Password cannot be empty." << endl;
    return false;
  }

  // Replace spaces with underscores
  for (int i = 0; password[i] != '\0'; i++) {
    if (password[i] == ' ') {
      password[i] = '_';
    }
  }
  
  // Check if password length is at least 6 characters
  int length = 0;
  for (int i = 0; password[i] != '\0'; i++) {
    length++;
  }
  if (length < 6) {
    cout << "Enter at least 6 characters!" << endl;
    return false;
  }
  return true; // Return true if password meets length requirement
}

bool validateHeight(float height) {
  // Check if height is within realistic bounds
  if (height > 1 && height < 2.5) {
    return true;
  }
  cout << "Height should be between 1m and 2.5m!" << endl;
  return false;
}

bool validateWeight(float weight) {
  // Check if weight is within realistic bounds
  if (weight > 20 && weight < 250) {
    return true;
  }
  cout<<"Weight should be between 20kg and 250kg!"<<endl;
  return false;
}

bool validateAge(int age) {
  // Check if age is within realistic bounds
  if (age >= 15 && age < 150) {
    return true;
  }
  cout << "Age should be between 15 and 150!" << endl;
  return false;
}

bool validateGender(string gender) {
  // Check if gender is either 'M/m' or 'F/f'
  if (gender == "M" || gender == "m" || gender == "F" || gender == "f") {
    return true;
  }
  cout << "Gender should be either 'M/m' or 'F/f'!" << endl;
  return false;
}

bool validateWeightGoal(float weightGoal, float currentWeight) {
  // Check if weight goal is positive and within 100 kg of the current weight
  if (weightGoal > 0 && (weightGoal - currentWeight < 100) && (currentWeight - weightGoal < 100)) {
    return true;
  }
  cout << "Weight goal should be positive and within 100 kg of the current weight!" << endl;
  return false;
}

bool checkFileExists(const string &username) {
  ifstream inFile(username + ".txt");
  if (inFile.is_open()) { // If the file is successfully opened
    inFile.close();       // Close the file
    return true;          // File exists
  }
  return false; // File does not exist
}



int getValidInteger() {
    string input; // Input as a string
    // cout << "Please enter an integer: ";
    cin >> input; // Read input as a string

    // Check each character in the input string
    for (char c : input) {
        if (c < '0' || c > '9') { // ASCII check for digits
            cout << "Invalid input! Number should be a positive integer." << endl;
            return -1; // Return -1 if any character is not a digit
        }
    }

    return stoi(input); // Return the integer, if it is one
}


float getValidFloat() {
  string input; // Input as a string
  cin >> input; // Read input as a string

  // Check each character in the input string
  for (char c : input) 
  {
    if (!((c >= '0' && c <= '9') || (c == '.'))) 
    { // ASCII check for digits
      cout << "Invalid input! Number should be a positive decimal." << endl;
      return -1;
    }
  }
  return stof(input);
}
