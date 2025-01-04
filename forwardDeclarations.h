#include <string>
using namespace std;
#pragma once

// Forward declarations to break circular dependencies
void registerUser();
void loginUser();
void forgotPassword();
void displayLoginMenu();
void displayMainMenu();
void workoutMenu();
void displayProfileMenu();
void startNewWorkout();
void maintanenceCalories(float weight, float height, int age, string gender);
float calculateBMI(float weight, float height);
int calculateBodyFatPercentage(string gender, int age, float weight, float height);
float extractUserWeight(const string& filename);
float extractUserWeightGoal(const string& filename);
bool createMainFile(const string &username, const string &password, const string &securityAnswer, float height, float weight, int age, float bodyFatPercentage, string gender, float weightGoal);
int getValidInteger();
void updateWeight();
void updateWeightGoal();
string customSubstr(const string& str, int start, int length);
float extractUserHeight(const string& filename);
float extractUserWeight(const string& filename);
float extractUserAge(const string& filename);
float extractUserBodyFatPercentage(const string& filename);
string extractUserGender(const string& filename);
float extractUserWeightGoal(const string& filename);
void viewWorkoutHistory(string muscleGroup);
void saveToCustomTempFile(string exerciseName, int exerciseData[3][5], int setCount);
void saveCustomWorkoutToHistory();
void saveToTempFile(string muscleGroupName, string exerciseName, int currentExercise[3][5], int setCount);
void viewCustomWorkoutHistory();
void deleteCustomTempFile(string username);
void createCustomExerciseFile(const string &filename);
void deleteTempFile(string loggedInUsername);
void saveWorkoutToHistory(string muscleGroup);
float getValidFloat();
void clearScreen();
void greet();

extern string loggedInUsername;