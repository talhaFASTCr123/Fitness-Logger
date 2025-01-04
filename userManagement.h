#pragma once
#include "calculations.h"
#include "menuSystem.h"
#include "validations.h"
#include "forwardDeclarations.h"
#include <fstream>
#include <iostream>
extern string loggedInUsername;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// Send user to menu then he will login

string encryptPassword(string password) {
  // Step 1: Reverse the password
  int n = password.length();
  for (int i = 0; i < n / 2; i++) {
    char temp = password[i];
    password[i] = password[n - 1 - i];
    password[n - 1 - i] = temp;
  }

  // Step 2: XOR each character with a fixed key (e.g., 5)
  char key = 5;
  for (int i = 0; i < n; i++) {
    password[i] = password[i] ^ key; 
  }

  // Step 3: Shift ASCII values 3 places to the right
  for (int i = 0; i < n; i++) {
    password[i] = password[i] + 3;
  }

  return password;
}

string decryptPassword(string encryptedPassword) {
  // Step 1: Shift ASCII values 3 places to the left
  int n = encryptedPassword.length();
  cout << "n: " << n << endl;
  cout << "Encrypted pass: " << encryptedPassword;
  for (int i = 0; i < n; i++) {
    encryptedPassword[i] = encryptedPassword[i] - 3;
  }

  cout << "After ASCII shift: " << encryptedPassword << endl;
  // Step 2: XOR each character with the same fixed key (e.g., 5)
  char key = 5;
  for (int i = 0; i < n; i++) {
    encryptedPassword[i] = encryptedPassword[i] ^ key;
  }
  
  cout << "After XOR shift: " << encryptedPassword << endl;
  // Step 3: Reverse the password back to original order

  for (int i = 0; i < n / 2; i++) {
    char temp = encryptedPassword[i];
    encryptedPassword[i] = encryptedPassword[n - 1 - i];
    encryptedPassword[n - 1 - i] = temp;
  }
  cout << "After reverse:  << " << encryptedPassword << endl;

  return encryptedPassword;
}

void forgotPassword() {
  string username, inputAnswer, storedSecurityAnswer, storedPassword;
  int attempts = 3;

  // Step 1: Input username
  cin.ignore(); // Clear the input buffer to prevent leftover '\n' from affecting getline
  cout << endl;
  cout << "Enter your username: ";
  getline(cin, username);
  validateUsername(username);

  // Step 2: Check if the file exists
  if (checkFileExists(username) == false) {
    cout << "Error: Username does not exist!" << endl;
    return;
  }

  // Step 3: Read security answer and password from file
  ifstream inFile(username + ".txt");
  if (inFile.is_open() == false) {
    cout << "Error: Could not open user file!" << endl;
    return;
  }

  // Step 4: Locate stored security answer and password
  string line;
  getline(inFile, line);
  getline(inFile, line); // This is password line
  storedPassword = customSubstr(line, 10, -1);

  getline(inFile, line); // This is the security answer line
  storedSecurityAnswer = customSubstr(line, 17, -1);
  inFile.close();

  // Step 5: Ask the security question with 3 attempts
  while (attempts > 0) {
    cout << endl;
    cout << "Security Question: What is the name of your favourite childhood character?" << endl;
    cout << "Enter your answer: ";
    getline(cin, inputAnswer);

    if (inputAnswer == storedSecurityAnswer) {
      cout << endl;
      cout << "Security answer correct!" << endl;
      string decryptedPassword = decryptPassword(storedPassword);
      cout << "Your password is: " << decryptedPassword << endl;
      cout << endl;
      cout << "Redirecting to the main menu..." << endl;
      displayLoginMenu();
      return;
    } else {
      attempts--;
      cout << endl;
      cout << "Incorrect answer. Attempts remaining: " << attempts << endl;
    }
  }

  // Step 6: Handle case where all attempts are exhausted
  cout << "Error: Maximum attempts reached. Cannot retrieve password." << endl;
  cout << endl;
  cout << "Returning to the main menu..." << endl;
  displayLoginMenu();
}

void registerUser() {
  string username, password, securityAnswer;
  float height, weight, weightGoal;
  int age, bodyFatPercentage;
  string gender;

  // Input username with validation and file existence check
  do {
    cout << "Enter your username (Min. 3 Chars): ";
    cin.ignore();
    getline(cin, username); // Use getline to capture full username

    // Validate username
    validateUsername(username);

    // Check if the file for this username already exists
    if (checkFileExists(username)) {
      cout << "This username already exists. Redirecting to login..." << endl;
      clearScreen();
      greet();
      displayLoginMenu();
      return; // Exit the function to prevent overwriting the file
    }
  } while (validateUsername(username) == false); // Validate username

  // Input password with validation
  do {
    cout << "Enter a password: ";
    getline(cin, password);
  } while (validatePassword(password) == false);

  // Fixed security question
  cout << "Security Question: What is the name of your favourite childhood character?" << endl;
  cout << "Enter your answer: ";
  getline(cin, securityAnswer);

  // Input height with validation
  do {
    clearScreen();
    greet();
    cout << "Enter your height (in m): ";
    height = getValidFloat();
  } while (validateHeight(height) == false);

  // Input weight with validation
  do {
    clearScreen();
    greet();
    cout << "Enter your weight (in kg): ";
    weight = getValidFloat();
  } while (validateWeight(weight) == false);

  // Input age with validation
  do {
    clearScreen();
    greet();
    cout << "Enter your age: ";
    age = getValidInteger();
  } while (validateAge(age) == false);

  // Input gender with validation
  do {
    clearScreen();
    greet();
    cout << "Enter your gender (M/F): ";
    cin >> gender;
  } while (validateGender(gender) == false);

  // Input weight goal with validation
  do {
    clearScreen();
    greet();
    cout << "Enter your weight goal (in kg): ";
    weightGoal = getValidInteger();
  } while (validateWeightGoal(weightGoal, weight) == false);

  // Calculate  body fat percentage
  bodyFatPercentage = calculateBodyFatPercentage(gender, age, weight, height);
 
  // Call createMainFile() to handle file creation

  string encryptedPassword = encryptPassword(password);
  cout << "Encrypted password: " << encryptedPassword << endl;
  if (createMainFile(username, encryptedPassword, securityAnswer, height, weight, age, bodyFatPercentage, gender, weightGoal)) {
    cout << "User registered successfully!" << endl;
    clearScreen();
    greet();
    displayLoginMenu();
  } else {
    cout << "Error: Could not create user file!" << endl;
    clearScreen();
    greet();
    displayLoginMenu();
  }
}

void loginUser() {
  string username, password, storedPasswordLine, line, extractedPassword;
  int passwordAttempts = 3;
  cin.ignore();
  // Try to get a valid username
  cout << "Enter your username: ";
  // cin.ignore();
  getline(cin, username);
  validateUsername(username);

  if (checkFileExists(username)) {
    cout << "Username found!" << endl;
  } else {
    cout << "Username not found. Please try again." << endl;
    cout << "Redirecting to the Login Menu..." << endl;
    displayLoginMenu();
    return; // Exit the function to prevent overwriting the file
    }

  // Open the user's file to retrieve the password
  ifstream userFile(username + ".txt");
  if (!userFile.is_open()) {
    cout << "Error: Unable to access user data. Redirecting to the main menu..." << endl;
    displayLoginMenu(); // Call displayLoginMenu() for redirection
    return;
  }

  // Retrieve the stored password from the file
  getline(userFile, line);
  getline(userFile, line); // Second line is the password one
  storedPasswordLine = line;

  extractedPassword = customSubstr(storedPasswordLine, 10, -1);
  userFile.close();

  // Try to match the password

  while (passwordAttempts > 0) {
    cout << endl;
    cout << "Enter your password: ";
    getline(cin, password);

    string decryptedPassword = decryptPassword(extractedPassword);
    if (password == decryptedPassword) {
      loggedInUsername = username;
      cout << "Login successful! Welcome, " << username << "!" << endl << endl;
      displayMainMenu();
      return;
    }
    else {
      passwordAttempts--;
      if (passwordAttempts > 0) {
        cout << "Incorrect password. You have " << passwordAttempts << " attempts remaining." << endl;
      }
      else {
        int choice = -1;
        while (choice < 1 || choice > 2)
        {
          cout << "All attempts exhausted." << endl;
          cout << "1. Forgot Password" << endl;
          cout << "2. Return to Main Menu" << endl;
          cout << "Please select an option (1 or 2): ";
          choice = getValidInteger();
        }

        if (choice == 1) {
          cout << "Redirecting to forgot password..." << endl;
          forgotPassword();
        } else if (choice == 2) {
          cout << "Redirecting to the Login Menu..." << endl;
          displayLoginMenu();
        }
        return;
      }
    }
  }
}
