#pragma once
#include "forwardDeclarations.h"
#include <cmath> // for abs()
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
float totalVolume = 0.0;

int calculateBodyFatPercentage(string gender, int age, float weight, float height) {
  int bodyFatPercentage;
  float bmi = calculateBMI(weight, height);
  if (gender == "M" || gender == "m") {
    bodyFatPercentage = (1.20 * bmi) + (0.23 * age) - 16.2;
  } else {
    bodyFatPercentage = (1.20 * bmi) + (0.23 * age) - 5.4;
  }

  if (bodyFatPercentage > 100)
  {
    bodyFatPercentage = 100;
  }
  return bodyFatPercentage;
}

// void displayProgressBar(float percentage) {
//   int totalBars = 20; // Total length of the progress bar
//   int filledBars = int(totalBars * (percentage / 100.0)); // Number of filled
//   sections

//   cout << "[";
//   for (int i = 0; i < filledBars; i++) {
//     cout << "="; // Filled part
//   }
//   for (int i = filledBars; i < totalBars; i++) {
//     cout << "-"; // Empty part
//   }
//   cout << "] " << int(percentage) << "% complete" << endl;
// }

void displayProgressBar(float percentage) {
  int totalBars = 20; // Total length of the progress bar
  int filledBars = int(totalBars * (percentage / 100.0)); // Number of filled sections

  // Determine color based on percentage
  string color;
  if (percentage >= 0 && percentage <= 30) {
    color = "\033[31m"; // Red (for 0-30%)
  } else if (percentage >= 31 && percentage <= 70) {
    color = "\033[33m"; // Yellow (for 31-70%)
  } else if (percentage >= 71 && percentage <= 100) {
    color = "\033[32m"; // Green (for 71-100%)
  } else {
    color = "\033[0m"; // Reset to default color
  }

  cout << color << "["; // Start with colored opening bracket
  for (int i = 0; i < filledBars; i++) {
    cout << "="; // Filled part
  }
  for (int i = filledBars; i < totalBars; i++) {
    cout << "-"; // Empty part
  }
  cout << "] " << int(percentage) << "% complete" << "\033[0m" << endl; // Reset color after the bar
}


float calculateBMI(float weight, float height) {
  return weight / (height * height);
}

int calculateSetVolume(int weight, int reps) { 
  return weight * reps;
}

void maintanenceCalories(float weight, float height, int age, string gender)
// how far from goal
{
  float bmr; // (Basal Metabolic Rate)
  float activityFactor;

  // Calculate BMR based on gender, already validated
  if (gender == "M" || gender == "m") {
    bmr = 10 * weight + 6.25 * height - 5 * age + 5; // For men
  } else if (gender == "F" || gender == "f") {
    bmr = 10 * weight + 6.25 * height - 5 * age - 161; // For women
  }

  // Ask the user to select an activity level
  int activityChoice = -1;
  
  while (activityChoice < 1 || activityChoice > 5) {
    cout << "Select your activity level:" << endl;
    cout << "1. Sedentary (little or no exercise)" << endl;
    cout << "2. Lightly active (light exercise/sports 1-3 days/week)" << endl;
    cout << "3. Moderately active (moderate exercise/sports 3-5 days/week)" << endl;
    cout << "4. Very active (hard exercise/sports 6-7 days a week)" << endl;
    cout << "5. Super active (very hard exercise/physical job)" << endl;
    cout << "Please select an option: ";
    activityChoice = getValidInteger();
  }
  // Set the activity factor based on the user's choice
  switch (activityChoice) {
  case 1:
    activityFactor = 1.2;
    break;
  case 2:
    activityFactor = 1.375;
    break;
  case 3:
    activityFactor = 1.55;
    break;
  case 4:
    activityFactor = 1.725;
    break;
  case 5:
    activityFactor = 1.9;
    break;
  }

  float maintenanceCalories = bmr * activityFactor;
  cout << "Your maintenance calories are: " << maintenanceCalories << " kcal/day." << endl;
}

float calculateWorkoutVolume(int weights[], int sets, int reps) {
  float totalVolume = 0;
  for (int set = 0; set < sets; set++) {
    totalVolume += weights[set] * reps;
  }
  return totalVolume;
}


string getCurrentDate() { // For GUI (DD-MM-YYYY format)
  time_t now = time(0);
  tm *ltm = localtime(&now);

  string date = std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday);
  return date;
}

string getCurrentTime() {
  time_t now = time(0);
  tm *ltm = localtime(&now);

  string timeStr = std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
  return timeStr;
}

void checkGoalProgression() {
  float progress;
  float currentWeight = extractUserWeight(loggedInUsername + ".txt");
  float weightGoal = extractUserWeightGoal(loggedInUsername + ".txt");
  int weightDifference = abs(weightGoal - currentWeight);
  if (currentWeight > weightGoal) {
    progress = (weightGoal / currentWeight) * 100;
  } else {
    progress = (currentWeight / weightGoal) * 100;
  }
  if (progress > 100) {
    progress = 100;
  }

  cout << "You are " << weightDifference << " kg away from your weight goal of " << weightGoal << " kgs." << endl;
  displayProgressBar(progress);
}
