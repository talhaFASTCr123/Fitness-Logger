#pragma once
#include "calculations.h"
#include "userManagement.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
string loggedInUsername;




string customSubstr(const string &str, int start, int length) {
    string result = ""; // To store the resulting substring
    // Ensure start index is within bounds
    if (start < 0 || start >= str.length()) {
      return result; // Return empty string if start is out of bounds
    }

    // Default length is the remainder of the string
    if (length == -1) {
      length = str.length() - start;
    }

    // Extract the substring
    for (int i = start; i < start + length && i < str.length(); i++) { 
      result += str[i];
    }

    return result;
}




string extractNumbers(const string& str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == 'M' || str[i] == 'm' || str[i] == 'f' || str[i] == 'F') {
            result += str[i]; // Add only digits to the result
        }
    }
    return result; // Return the numeric-only string
}

float extractUserHeight(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return 0;
  }

  string line;
  string height;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer

  // Extract height from the 4th line
  getline(file, line);
  height = customSubstr(line, 8, line.length() - 8 - 1);  // "Height: " is 8 characters
  height = extractNumbers(height);  // Extract only the numeric part of height

  file.close();
  return stof(height);
}

// Function to extract weight
float extractUserWeight(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return 0;
  }

  string line;
  string weight;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer
  getline(file, line); // Height
  
  // Extract weight from the 5th line
  getline(file, line);
  weight = customSubstr(line, 8, line.length() - 8 - 1);  // "Weight: " is 8 characters
  weight = extractNumbers(weight);  // Extract only the numeric part of weight

  file.close();
  return stof(weight);
}

// Function to extract age
float extractUserAge(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return 0;
  }

  string line;
  string age;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer
  getline(file, line); // Height
  getline(file, line); // Weight
  
  // Extract age from the 6th line
  getline(file, line);
  age = customSubstr(line, 5, line.length() - 5 - 1);  // "Age: " is 5 characters
  age = extractNumbers(age);  // Extract only the numeric part of age

  file.close();
  return stof(age);
}

// Function to extract body fat percentage
float extractUserBodyFatPercentage(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return 0;
  }

  string line;
  string bodyFatPercentage;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer
  getline(file, line); // Height
  getline(file, line); // Weight
  getline(file, line); // Age

  // Extract body fat percentage from the 7th line
  getline(file, line);
  bodyFatPercentage = customSubstr(line, 21, line.length() - 21 - 1);  // "Body Fat Percentage: " is 21 characters
  bodyFatPercentage = extractNumbers(bodyFatPercentage);  // Extract only the numeric part of body fat percentage

  file.close();
  return stof(bodyFatPercentage);
}

// Function to extract gender
string extractUserGender(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return " ";
  }

  string line;
  string gender;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer
  getline(file, line); // Height
  getline(file, line); // Weight
  getline(file, line); // Age
  getline(file, line); // Body Fat Percentage

  // Extract gender from the 8th line
  getline(file, line);
  gender = customSubstr(line, 8, -1);  // "Gender: " is 8 characters

  file.close();
  return gender;
}

// Function to extract weight goal
float extractUserWeightGoal(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
      cout << "Could not open the file!" << endl;
      return 0;
  }

  string line;
  string weightGoal;
  // Skip through the first three lines
  getline(file, line); // Username
  getline(file, line); // Password
  getline(file, line); // Security Answer
  getline(file, line); // Height
  getline(file, line); // Weight
  getline(file, line); // Age
  getline(file, line); // Body fat percentage
  getline(file, line); // Gender

  // Extract weight goal from the 9th line
  getline(file, line);
  weightGoal = customSubstr(line, 13, line.length() - 13 - 1);  // "Weight Goal: " is 13 characters
  weightGoal = extractNumbers(weightGoal);  // Extract only the numeric part of weight goal

  file.close();
  return stof(weightGoal);
}



bool createMainFile(const string &username, const string &password, const string &securityAnswer, float height, float weight, int age, float bodyFatPercentage, string gender, float weightGoal) {
  // Create a file with the username as the filename
  ofstream outFile(username + ".txt");
  if (!outFile.is_open()) { // Check if file creation failed
    return false;
  }

  // Write user details to the file
  outFile << "Username: " << username << endl;
  outFile << "Password: " << password << endl;
  outFile << "Security Answer: " << securityAnswer << endl;
  outFile << "Height: " << height << " m" << endl;
  outFile << "Weight: " << weight << " kg" << endl;
  outFile << "Age: " << age << " years" << endl;
  outFile << "Body Fat Percentage: " << bodyFatPercentage << "%" << endl;
  outFile << "Gender: " << gender << endl;
  outFile << "Weight Goal: " << weightGoal << " kg" << endl;

  // Close the file
  outFile.close();
  return true;
}

void saveToTempFile(string muscleGroupName, string exerciseName, int currentExercise[3][5], int setCount) {
  string tempFilename = loggedInUsername + "_tempWorkout.txt";
  ofstream tempFile(tempFilename, std::ios::app);

  if (!tempFile) {
    cout << "Error opening temp file!\n";
    return;
  }

  tempFile << "    - " << exerciseName << ": ";

  // If no sets were added, print "No sets"
  if (setCount == 0) {
    tempFile << "No sets\n";
  } else {
    tempFile << setCount << " sets @ ";

    // Print weights for sets inside brackets
    tempFile << "(";
    for (int i = 0; i < setCount; i++) {
      tempFile << currentExercise[0][i]; // Weights
      if (i < setCount - 1) {
        tempFile << ", "; // Add commas between weights
      }
    }
    tempFile << ") kg | "; // Closing bracket for weights, and unit "kg"

    // Print reps for sets inside brackets
    tempFile << "(";
    for (int i = 0; i < setCount; i++) {
      tempFile << currentExercise[1][i]; // Reps
      if (i < setCount - 1) {
        tempFile << ", "; // Add commas between reps
      }
    }
    tempFile << ") reps\n"; // Closing bracket for reps, and unit "reps"
  }

  tempFile.close();
}

void deleteTempFile(string loggedInUsername) {
  // Construct the filename using the logged-in username
  string filename = loggedInUsername + "_tempWorkout.txt";

  // Check if file exists before attempting to delete
  ifstream checkFile(filename.c_str());
  if (!checkFile) {
    cout << "No temporary workout file found." << endl;
    checkFile.close();
    return;
  }
  checkFile.close();

  // Attempt to delete the file
  int result = remove(filename.c_str());

  if (result == 0) {
    cout << "Temporary workout file cleaned up successfully." << endl;
  } else {
    cout << "Error cleaning up temporary workout file." << endl;
  }
}


void saveWorkoutToHistory(string muscleGroup) {
  ifstream tempfile(loggedInUsername + "_tempWorkout.txt");
  ofstream history(loggedInUsername + "_" + muscleGroup + "_workoutHistory.txt", std::ios::app);
  if (!tempfile.is_open() || !history.is_open()) {
    cout << "Error opening file!" << endl;
  }
  else {
    string line;
    while (getline(tempfile, line)) { // Read each line from the source file
      history << line << endl;
    }
    history << "\n\n\n";

    tempfile.close();
    history.close();
  }
}

void viewWorkoutHistory(string muscleGroup) {
  string historyFilename = loggedInUsername + "_" + muscleGroup + "_workoutHistory.txt";
  ifstream historyFile(historyFilename);

  if (!historyFile.is_open()) {
    cout << endl;
    cout << "\033[4m" << "Note:" << "\033[0m" << " No workout history available for this muscle group." << endl;
    cout << endl;
    return;
  }

  string line;
  string sessionData = "";
  string latestSession = "";

  // Read through the file to capture all sessions
  while (getline(historyFile, line)) {
    // Only add non-empty lines to sessionData
    if (line != "") {
      sessionData += line + "\n"; // Add each line to the session data
    }

    // If we encounter the end of a session marker (i.e.,
    // "---------------------------------------------------")
    if (line == "---------------------------------------------------") {
      latestSession = sessionData;  // Save the session as the most recent session
      sessionData = ""; // Reset for the next session
    }
  }

  // If the file doesn't end with the separator, we still want to capture the
  // last session
  if (sessionData != "") {
    latestSession = sessionData; // Assign the last session
  }

  if (latestSession == "") {
    cout << "\033[4m" << "Note:" << "\033[0m" << " No workout history available for this muscle group." << endl;
  }
  else {
    cout << "Latest workout session for " << muscleGroup << ":\n";
    cout << latestSession << endl; // Display the most recent session
  }

  historyFile.close();
}

void createCustomExerciseFile(const string &filename) {
  // Open the file in write mode
  ofstream file(filename);

  // Check if file opened successfully
  if (!file.is_open()) {
    cout << "Error creating custom exercise file." << endl;
    return;
  }

  // Write the header
  file << "================== Custom Exercises ===================\n";
  file << "Exercises:\n";

  // Close the file
  file.close();

  cout << "Custom exercise file created successfully." << endl;
  cout << endl;
}

void saveToCustomTempFile(string exerciseName, int exerciseData[3][5], int setCount) {
  // Open the temp file in append mode
  ofstream tempFile(loggedInUsername + "_customTempWorkout.txt", ios::app);

  if (!tempFile.is_open()) {
    cout << "Error opening temp workout file." << endl;
    return;
  }

  // If no sets, write "No sets"
  if (setCount == 0) {
    tempFile << "    - " << exerciseName << ": No sets\n";
  } else {
    // Write exercise name and start the set details
    tempFile << "    - " << exerciseName << ": " << setCount << " sets @ (";

    // Write weights
    for (int i = 0; i < setCount; i++) {
      tempFile << exerciseData[0][i];
      if (i < setCount - 1)
        tempFile << ", ";
    }
    tempFile << ") kg | (";

    // Write reps
    for (int i = 0; i < setCount; i++) {
      tempFile << exerciseData[1][i];
      if (i < setCount - 1)
        tempFile << ", ";
    }
    tempFile << ") reps\n";
  }

  tempFile.close();
}

void saveCustomWorkoutToHistory() {
  // Open history file in append mode
  ofstream historyFile(loggedInUsername + "_customWorkoutHistory.txt", ios::app);

  // Open temp workout file to read its contents
  ifstream tempFile(loggedInUsername + "_customTempWorkout.txt");

  // Check if files opened successfully
  if (!historyFile.is_open()) {
    cout << "Error opening workout history file." << endl;
    return;
  }

  if (!tempFile.is_open()) {
    cout << "Error opening temporary workout file." << endl;
    return;
  }

  // Copy contents of temp file to history file
  string line;
  while (getline(tempFile, line)) {
    historyFile << line << endl;
  }

  // Add extra newlines to separate workout sessions
  historyFile << endl << endl << endl; // 3 spaces

  // Close both files
  historyFile.close();
  tempFile.close();
}

void deleteCustomTempFile(string username) {
  // Create filename
  string filename = username + "_customTempWorkout.txt";

  // Convert string to char array manually
  char filenameCopy[200]; // Make sure this is large enough
  for (int i = 0; i < filename.length(); i++) {
    filenameCopy[i] = filename[i];
  }
  filenameCopy[filename.length()] = '\0'; // Null-terminate the string

  // Try to delete the file
  if (remove(filenameCopy) != 0) {
    // If file doesn't exist or can't be deleted, print message
    cout << "Could not delete temporary workout file." << endl;
  } else {
    cout << "Temporary workout file deleted successfully." << endl;
  }
}

void viewCustomWorkoutHistory() {
  // Input file stream
  ifstream inputFile(loggedInUsername + "_customWorkoutHistory.txt");
  if (!inputFile) {
    cout << "\033[4m" << "Note:" << "\033[0m" << " No workout history available for this muscle group." << endl;
  }

  string line;
  string latestSession;  // Store the latest session details
  string currentSession; // Temporarily hold the current session
  bool inSession = false;

  // Read the file line-by-line
  while (getline(inputFile, line)) {
    // Detect session start by checking if the line begins with "============
    // Workout Session"
    if (line.size() >= 28) { // Ensure line is long enough
      bool isSessionStart = true;
      for (int i = 0; i < 28; i++) {
        if (line[i] != "============ Workout Session"[i]) {
          isSessionStart = false;
          break;
        }
      }

      if (isSessionStart) {
        if (inSession) {
          // Save the previous session as the latest session
          latestSession = currentSession;
          currentSession.clear();
        }
        inSession = true; // Start capturing a new session
      }
    }

    // If inside a session, append the line
    if (inSession) {
      currentSession += line + "\n";
    }
  }

  // Save the last session as the latest session
  if (!currentSession.empty()) {
    latestSession = currentSession;
  }

  inputFile.close();

  // Display the latest session
  cout << latestSession;
}



void updateWeight() {
  string filename = loggedInUsername + ".txt";       // Original file
  string tempFilename = loggedInUsername + "tempUpdate.txt"; // Temporary file
  ifstream infile(filename);
  ofstream tempFile(tempFilename);

  if (!infile || !tempFile) {
    cout << "Error: Unable to open file for reading or writing." << endl;
    return;
  }

  int newWeight = -1;
  cout << "Enter your new weight: ";
  newWeight = getValidFloat();
  while (newWeight < 20 || newWeight > 250) {
    clearScreen();
    greet();
    cout << "Invalid weight. Please enter a weight between 20 and 250 kgs: "<<endl;
    cout << "Enter your new weight: ";
    newWeight = getValidFloat();
  }

  string line;
  int lineCount = 0;
  while (getline(infile, line)) {
    lineCount++;
    if (lineCount == 5) {
      // Replace the 5th line with the new weight
      tempFile << "Weight: " << newWeight << " kg" << endl;
    } else if (lineCount == 7) {
      tempFile << "Body Fat Percentage: " << calculateBodyFatPercentage(extractUserGender(loggedInUsername + ".txt"), extractUserAge(loggedInUsername + ".txt"), newWeight, extractUserHeight(loggedInUsername + ".txt")) << "%" << endl;
    } else {
      // Copy other lines as-is
      tempFile << line << endl;
    }
  }

  infile.close();
  tempFile.close();

  // Reopen the temp file for reading
  ifstream tempFileRead(tempFilename);
  ofstream originalFile(filename);

  if (!tempFileRead || !originalFile) {
    cout << "Error: Unable to open files for overwriting." << endl;
    return;
  }

  // Copy contents from the temp file back to the original file
  while (getline(tempFileRead, line)) {
    originalFile << line << endl;
  }

  tempFileRead.close();
  originalFile.close();

  // Remove the temporary file
  // remove(tempFilename.c_str());

  // Convert string to char array manually
  char tempFileNameCopy[200]; // Make sure this is large enough
  for (int i = 0; i < tempFilename.length(); i++) {
    tempFileNameCopy[i] = tempFilename[i];
  }
  tempFileNameCopy[tempFilename.length()] = '\0'; // Null-terminate the string

  // Try to delete the file
  if (remove(tempFileNameCopy) != 0) {
    // If file doesn't exist or can't be deleted, print message
    cout << "Could not delete temporary workout file." << endl;
  } else {
    cout << "Temporary workout file deleted successfully." << endl;
  }

  cout << "Weight updated successfully!" << endl;
}





void updateWeightGoal() {
  string filename = loggedInUsername + ".txt"; // Original file
  string tempFilename = loggedInUsername + "tempUpdate.txt"; // Temporary file
  ifstream infile(filename);
  ofstream tempFile(tempFilename);

  if (!infile || !tempFile) {
    cout << "Error: Unable to open file for reading or writing." << endl;
    return;
  }

  int newWeightGoal = -1;
  cout << "Enter your new weight goal: ";
  newWeightGoal = getValidFloat();
  while (newWeightGoal < 20 || newWeightGoal > 250) {
      clearScreen();
      greet();
      cout << "Invalid weight goal. Please enter a weight goal between 20 and 250 kgs: "<<endl;
      cout << "Enter your new weight goal: ";
      newWeightGoal = getValidFloat();
  }

  string line;
  int lineCount = 0;
  while (getline(infile, line)) {
      lineCount++;
      if (lineCount == 9) {
          // Replace the 5th line with the new weight
          tempFile << "Weight Goal: " << newWeightGoal << " kg" << endl;
      } else {
          // Copy other lines as-is
          tempFile << line << endl;
      }
  }

  infile.close();
  tempFile.close();

  // Reopen the temp file for reading
  ifstream tempFileRead(tempFilename);
  ofstream originalFile(filename);

  if (!tempFileRead || !originalFile) {
      cout << "Error: Unable to open files for overwriting." << endl;
      return;
  }

  // Copy contents from the temp file back to the original file
  while (getline(tempFileRead, line)) {
      originalFile << line << endl;
  }

  tempFileRead.close();
  originalFile.close();

  // Remove the temporary file
  // Convert string to char array manually
  char tempFileNameCopy[200]; // Make sure this is large enough
  for (int i = 0; i < tempFilename.length(); i++) {
    tempFileNameCopy[i] = tempFilename[i];
  }
  tempFileNameCopy[tempFilename.length()] = '\0'; // Null-terminate the string

  // Try to delete the file
  if (remove(tempFileNameCopy) != 0) {
    // If file doesn't exist or can't be deleted, print message
    cout << "Could not delete temporary workout file." << endl;
  } else {
    cout << "Temporary workout file deleted successfully." << endl;
  }

  cout << "Weight updated successfully!" << endl;

  cout << "Goal updated successfully!" << endl;
}