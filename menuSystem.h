#pragma once

#include "forwardDeclarations.h"

#include "userManagement.h"

#include <fstream>

#include <iostream>

#include <string>

#include <cstdlib>

#include "greet.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

void clearScreen() {
  (void) system("clear");
}

void displayWeightMenu() {
  greet();
  clearScreen();
  cout << endl << "\033[1;37m" << "Welcome to the Weight Menu!" << "\033[0m" << endl;
  int choice;
  while (true) {
    // clearScreen();
    // greet();
    cout << endl;
    cout << "1. Check Goal Progression" << endl;
    cout << "2. Update Weight" << endl;
    cout << "3. Update Weight Goal" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Please select an option: ";
    choice = getValidInteger();
    cout << endl;

    if (choice == 1) {
      clearScreen();
      greet();
      checkGoalProgression();
    } else if (choice == 2) {
      clearScreen();
      greet();
      updateWeight();
    } else if (choice == 3) {
      clearScreen();
      greet();
      updateWeightGoal();
    } else if (choice == 4) {
      clearScreen();
      greet();
      displayMainMenu();
    }
    else
    {
      clearScreen();
      greet();
      cout << "Enter a choice from 1, 2, 3 or 4" << endl;
    }
  }
}

void displayCalculatorOptions() {
  clearScreen();
  greet();
  cout << endl << "\033[1;37m" << "Welcome to the Fitness Calculator!" << "\033[0m" << endl;
  int choice;
  while (true) {
    
    cout << endl;
    cout << "1. Calculate BMI" << endl;
    cout << "2. Calculate Body Fat Percentage" << endl;
    cout << "3. Calculate maintanence calories" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Please select an option: ";
    choice = getValidInteger();
    cout << endl;
    if (choice == 1) {
      clearScreen();
      greet();
      float BMI = calculateBMI(extractUserWeight(loggedInUsername + ".txt"), extractUserHeight(loggedInUsername + ".txt"));
      cout << "Your BMI: " << BMI << endl;
      if (BMI < 18.5) {
        cout << "It seems like you're underweight. It's important to ensure you're getting enough nutrition to stay healthy." << endl;
      } else if (BMI >= 18.5 && BMI < 24.9) {
        cout << "Great job! Your BMI is within the normal range, which is a positive indicator of good health." << endl;
      } else if (BMI >= 25 && BMI < 29.9) {
        cout << "You're in the overweight range. It's always a good idea to maintain a balanced diet and regular exercise." << endl;
      } else {
        cout << "Your BMI falls into the obese category. It's a good idea to speak with a healthcare professional to develop a plan that works best for you." << endl;
      }
    } else if (choice == 2) {
      clearScreen();
      greet();
      cout << "Current Body Fat Percentage: " << extractUserBodyFatPercentage(loggedInUsername + ".txt") << "%" << endl;
    } else if (choice == 3) {
      clearScreen();
      greet();
      maintanenceCalories(extractUserWeight(loggedInUsername + ".txt"), extractUserHeight(loggedInUsername + ".txt"), extractUserAge(loggedInUsername + ".txt"),
        extractUserGender(loggedInUsername + ".txt"));
    } else if (choice == 4) {
      clearScreen();
      greet();
      displayMainMenu();
    } else {
      clearScreen();
      greet();
      cout << "Please enter a valid option from 1, 2, 3 or 4" << endl;
    }
  }
}

void displayWorkoutMenu() {
  clearScreen();
  greet();
  int choice;
  while (true) {
   
    cout << endl;
    cout << "\033[1;37m" << "Welcome to the Workout Menu!" << "\033[0m" << endl;
    cout << "1. Start New Workout" << endl;
    cout << "2. Back To Main Menu" << endl;
    cout << endl;
    cout << "Please select an option: ";
    choice = getValidInteger();

    if (choice == 1) {
      clearScreen();
      greet();
      startNewWorkout();
      break;
    } else if (choice == 2) {
      clearScreen();
      greet();
      displayMainMenu();
      break;
    } else {
      clearScreen();
      greet();
      cout << "Invalid choice. Please choose either 1 or 2." << endl;
    }
  }
}


void displayProfile() {
  clearScreen();
  greet();
  cout << endl;
  cout << "\033[1;37m" << "<<< Profile Information >>>" << "\033[1;37m" << endl;
  cout << "Username: " << loggedInUsername << endl;
  cout << "Height: " << extractUserHeight(loggedInUsername + ".txt") << " m" << endl;
  cout << "Weight: " << extractUserWeight(loggedInUsername + ".txt") << " kg" << endl;
  cout << "Age: " << extractUserAge(loggedInUsername + ".txt") << " years" << endl;
  cout << "Body Fat Percentage: " << extractUserBodyFatPercentage(loggedInUsername + ".txt") << "%" << endl;
  cout << "Gender: " << extractUserGender(loggedInUsername + ".txt") << endl;
  cout << "Weight Goal: " << extractUserWeightGoal(loggedInUsername + ".txt") << "kg" << endl;
  cout << "\n1. Back To Main Menu" << endl;
  int choice = -1;
  choice = getValidInteger();
  while (choice != 1) {
    cout << "Enter 1 to return to Main Menu: ";
  }
  if (choice == 1) {
    clearScreen();
    greet();
    displayMainMenu();
  }
}

void displayMainMenu() {
  clearScreen();
  greet();
  int choice;
  while (true) {
    cout << endl << "\033[1;37m" << "Welcome to the Main Menu!" << "\033[1;37m" << endl;
    cout << "1. Workout Menu" << endl;
    cout << "2. Display Profile" << endl;
    cout << "3. Calculator" << endl;
    cout << "4. Weight Options" << endl;
    cout << "5. Logout" << endl;
    cout << "Please select an option: ";
    choice = getValidInteger();

    if (choice == 1) {
      clearScreen();
      greet();
      displayWorkoutMenu();
      break;
    } else if (choice == 2) {
      clearScreen();
      greet();
      displayProfile();
      break;
    } else if (choice == 3) {
      clearScreen();
      greet();
      displayCalculatorOptions();
      break;
    } else if (choice == 4) {
      clearScreen();
      greet();
      displayWeightMenu();
      break;
    } else if (choice == 5) {
      clearScreen();
      greet();
      displayLoginMenu();
      break;
    } else {
      clearScreen();
      greet();
      cout << "Invalid choice. Please choose either 1, 2, 3, 4 or 5." << endl;
    }
  }
}


void displayLoginMenu() {
  int choice;
  while (true) {
    cout << endl;
    cout << "\033[1;37m" << "Welcome to the Fitness Logger!" << "\033[1;37m" << endl;
    cout << "1. Login" << endl;
    cout << "2. Forgot password?" << endl;
    cout << "3. Don't have an account? Register" << endl;
    cout << "4. Exit Program." << endl;
    cout << endl;
    cout << "Please select an option (1, 2, 3 or 4): ";
    choice = getValidInteger();

    if (choice == 1) {
      clearScreen();
      greet();
      cout << endl;
      loginUser();
      break;
    } else if (choice == 2) {
      clearScreen();
      greet();
      cout << endl;
      forgotPassword();
    } else if (choice == 3) {
      clearScreen();
      greet();
      // Idhar new user register hoga
      cout << endl;
      cout << "You will now be redirected to the registration menu..." << endl;
      cout << endl;
      registerUser();
      break;
    } else if (choice == 4) {
      clearScreen();
      greet();
      cout << endl;
      cout << "Exiting the program. Goodbye!" << endl;
      exit(0);
    } else {
      clearScreen();
      greet();
      cout << endl;
      cout << "Invalid choice! Please choose either 1, 2, 3 or 4." << endl;
    }
  }
}
