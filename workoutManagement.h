#include "userManagement.h"
#include "greet.h"
#include "forwardDeclarations.h"
#include <fstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;

string exercises[3][6] = {
    {"Bench Press(Barbell)", "Incline Bench Press(Dumbbell)",
     "Shoulder Press(Dumbbell)", "Lateral Raises(Dumbbell)", "Tricep Pushdowns",
     "Tricep Dips"}, // Push
    {"Pull-ups", "Lat Pulldown", "Bentover Rows", "Dumbbell Rows",
     "Dumbbell Curls", "Hammer Curls"}, // Pull
    {"Barbell Squat", "Leg Press", "Romanian Deadlift", "Seated Leg Curls",
     "Leg Extensions", "Calf Raises"} // Leg
};

string customExercises[5][10] = {
    {"Barbell Squat", "Hack Squat", "Leg Press", "Leg Extensions",
     "Romanian Deadlift", "Seated Leg Curls", "Lying Leg Curls", "Hip Thrusts",
     "Calf Raises", "Lunges"}, // Legs
    {"Dumbell Curls", "Ez Bar Curls", "Hammer Curls", "Incline Curls ",
     "Preacher Curls", "Tricep Pushdown", "Overhead Tricep Extension",
     "Tricep Dips", "Skullcrushers", "JM Press"}, // Arms
    {"Bench Press(Barbell)", "Incline Bench Press(Barbell)",
     "Bench Press(Dumbbell)", "Incline Bench Press(Dumbbell)",
     "Bench Press(Machine)", "Incline Bench Press(Machine)", "Cable Flies",
     "Pec Deck", "Decline Press", "Chest Dips"}, // Chest
    {"Pull-ups", "Chin-ups", "Lat Pulldown", "Bentover Rows", "Dumbbell Rows",
     "T-Bar Rows", "Machine Row", "Cable Rows", "Inverted Rows",
     "Cable Pullovers"}, // Back
    {"Shoulder Press (Barbell)", "Shoulder Press (Dumbbell)",
     "Lateral Raises (Dumbbell)", "Lateral Raises(Cable)",
     "Front Raises (Dumbbell)", "Front Raises(Cable)",
     "Rear Delt Flys(Dumbbell)", "Rear Delt Flys(Cable)", "Face Pulls",
     "Upright Rows"} // Shoulders
};

string currentCustomWorkout[10] = {"", "", "", "", "", "", "", "", "", ""};
float totalWorkoutVolume = 0;
int exerciseIndex;

string addWorkoutNotes() {
  clearScreen();
  greet();
  cin.ignore();
  string notes;
  const int MAX_LENGTH = 200; // Maximum character length for notes

  while (true) {
    cout << "Enter post-workout notes (Less than 200 characters):\n";
    getline(cin, notes);

    // Check if the input is within the acceptable length range
    if (notes.length() <= MAX_LENGTH) {
      break;
    } else {
      cout << "Invalid input! Notes must be less than " << MAX_LENGTH << " characters.\n";
    }
  }
  return notes;
}

void displayCustomWorkout(int muscleGroup) {
  clearScreen();
  greet();
  for (int i = 0; i < 10; i++) {
    cout << (i + 1) << " -> " << customExercises[muscleGroup][i] << endl;
  }
}

void startCustomSession() {
  // view previous
  viewCustomWorkoutHistory();

  // Reset total workout volume
  int totalWorkoutVolume = 0;

  // Create temp file and write initial header
  ofstream tempFile(loggedInUsername + "_customTempWorkout.txt");
  tempFile << "============ Workout Session - " << getCurrentDate() << " ============\n";
  tempFile << "Type: Custom Workout" << "\nExercises:\n";
  tempFile.close();

  int totalDuration = 0;

  // Process each exercise
  int i = 0;
  while (currentCustomWorkout[i] != "" && i < 10) {
    string exerciseName = currentCustomWorkout[i];
    cout << endl << "-> Exercise: " << exerciseName << "\n";

    int currentExercise[3][5] = {{0}}; // Weights, Reps, Volume
    int setCount = 0;

    while (setCount < 5) {
      int choice;
      cout << endl;
      cout << "1. Add Set\n2. Skip (Go to next exercise)\n\n";
      cout << "Please select an option: ";
      choice = getValidInteger();
      while (choice < 1 || choice > 2) {
        cout << "Invalid choice! Please choose either 1 or 2." << endl;
        cout << "Please select an option: ";
        choice = getValidInteger();
      }

      if (choice == 2)
        break;

      if (choice == 1) {
       
        cout << "\nEnter weight for set " << (setCount + 1) << " (in kg): ";
        currentExercise[0][setCount] = getValidInteger(); // validations
        while (currentExercise[0][setCount] <= 0 || currentExercise[0][setCount] > 600) {
          cout << "Invalid input! Weight must be between 0 and 600 kgs." << endl;
          cout << "\nEnter weight for set " << (setCount + 1) << " (in kg): ";
          currentExercise[0][setCount] = getValidInteger();
        }
        cout << endl;
        cout << "\nEnter reps for set " << (setCount + 1) << " : ";
        currentExercise[1][setCount] = getValidInteger(); // validations
        while (currentExercise[1][setCount] <= 0 || currentExercise[1][setCount] > 100) {
          cout << "Invalid input! Reps must be between 0 and 100." << endl;
          cout << "\nEnter reps for set " << (setCount + 1) << ": ";
          cin >> currentExercise[1][setCount];
        }

        currentExercise[2][setCount] = calculateSetVolume(currentExercise[0][setCount], currentExercise[1][setCount]);
        totalWorkoutVolume += currentExercise[2][setCount];
        setCount++;
        totalDuration += 5;
      } else {
        cout << "Invalid choice. Try again.\n";
      }
    }

    saveToCustomTempFile(exerciseName, currentExercise, setCount);

    cout << "\033[4m" << "Note:" << "\033[0m" << " Data for " << exerciseName << " has been saved.\n";
    if (setCount == 0) {
      cout << "No sets added for this exercise.\n";
    }
    i++;
  }

  // Add total volume and footer to the temp file
  ofstream finalTempFile(loggedInUsername + "_customTempWorkout.txt", ios::app);
  finalTempFile << "\nTotal Volume: " << totalWorkoutVolume << " kg\n";
  finalTempFile << "Post-workout notes: " << addWorkoutNotes() << "\n";
  finalTempFile << "Total Duration: " << totalDuration << " minutes\n";
  finalTempFile << "========================================================\n";
  finalTempFile.close();

  // Ask user to save or discard session
  int saveChoice = -1;
  cout << "Do you want to save this workout session?\n1. Save\n2. Discard\n";
  saveChoice = getValidInteger();
  while (saveChoice < 1 || saveChoice > 2) {
    cout << "Invalid choice! Please choose either 1 or 2." << endl;
    saveChoice = getValidInteger();
  }

  if (saveChoice == 2) {
    deleteCustomTempFile(loggedInUsername);
    cout << "Custom Workout session discarded.\n";
  } else {
    saveCustomWorkoutToHistory();
    deleteCustomTempFile(loggedInUsername);
    cout << "Custom Workout session saved successfully.\n";
  }
}

void loadCustomWorkout() {
  int count = 0;
  ifstream previous(loggedInUsername + "_customExercises.txt");

  string line;

  while (getline(previous, line)) {
    // Skip header lines
    if (line == "================== Custom Exercises ==================" ||
        line == "Exercises:") {
      continue;
    }

    // If we encounter the footer, stop reading
    if (line == "=======================================================") {
      break;
    }

    // Start reading exercise lines after the header
    if (line[0] == ' ' && line[1] == ' ' && line[2] == '-') {
      // Find the position of the comma
      int startPos = 3; // Skip the initial "  - " part (2 spaces and 1 dash)
      int endPos = -1;
      for (int i = startPos; i < line.length(); i++) {
        if (line[i] == ',') {
          endPos = i;
          break;
        }
      }

      if (endPos != -1) {
        // Extract the exercise name from the line
        string exerciseName = "";
        for (int i = startPos; i < endPos; i++) {
          exerciseName += line[i];
        }
        // Add the exercise to the array
        currentCustomWorkout[count] = exerciseName;
        count++;
      }
    }
  }
  previous.close();
}

void createCustomWorkout(const string &customExerciseFilename) {
  int muscleGroup = -1, addExerciseChoice = -1;
  bool addExercise = true;
  exerciseIndex = 0;
  cout << endl;
  cout << "Creating Custom Workout...\n\n";

  // Open the custom exercise file in append mode to add exercises dynamically
  ofstream customFile(customExerciseFilename, ios::app);
  if (!customFile.is_open()) {
    cout << "Error opening custom exercise file: " << customExerciseFilename << endl;
    return;
  }

  // Display muscle groups to the user
  while (addExercise == true && exerciseIndex < 10) {
    clearScreen();
    greet();
    muscleGroup = -1;
    cout << "Please select a muscle group:" << endl;
    cout << "1. Legs\n2. Arms\n3. Chest\n4. Back\n5. Shoulders\n\n";
    cout << "Please select an option: ";
    muscleGroup = getValidInteger();
    while (muscleGroup < 1 || muscleGroup > 5) {
      clearScreen();
      greet();
      cout<<"Invalid choice! Please choose a valid muscle group.(1 to 5)"<<endl;
      cout << "Please select a muscle group:" << endl;
      cout << "1. Legs\n2. Arms\n3. Chest\n4. Back\n5. Shoulders\n\n";
      cout << "Please select an option: ";
      muscleGroup = getValidInteger();
    }

    // Adjust index for zero-based array
    muscleGroup = muscleGroup - 1;

    // Show exercises for the selected muscle group
    displayCustomWorkout(muscleGroup);
    int exerciseChoice = -1;
    while (exerciseChoice < 1 || exerciseChoice > 10) {
      cout << "Select an exercise to add to the workout (1-10):\n";
      exerciseChoice = getValidInteger();
    }

    // Adjust `exerciseChoice` to zero-based index
    exerciseChoice = exerciseChoice - 1;

    // Assign the selected exercise to `currentCustomWorkout`
    string selectedExercise = customExercises[muscleGroup][exerciseChoice];
    currentCustomWorkout[exerciseIndex] = selectedExercise;
    cout << "You have selected: " << selectedExercise << endl;
    exerciseIndex++;

    // Get muscle group name dynamically within this function
    string muscleGroupName;
    switch (muscleGroup) {
    case 0:
      muscleGroupName = "Legs";
      break;
    case 1:
      muscleGroupName = "Arms";
      break;
    case 2:
      muscleGroupName = "Chest";
      break;
    case 3:
      muscleGroupName = "Back";
      break;
    case 4:
      muscleGroupName = "Shoulders";
      break;
    default:
      muscleGroupName = "Unknown";
      break;
    }

    // Write the exercise to the custom exercise file
    customFile << "  - " << selectedExercise << ", Muscle group: " << muscleGroupName << endl;

    // Ask if user wants to add another exercise
    addExerciseChoice = -1;
    while (addExerciseChoice < 1 || addExerciseChoice > 2) {
      cout << "Do you want to add another exercise?\n1. Yes\n2. No\n";
      addExerciseChoice = getValidInteger();
    }

    if (addExerciseChoice == 2) {
      addExercise = false;
    }
  }

  // Display the selected exercises for the workout
  cout << "\nYour selected exercises for this workout are:\n";
  for (int i = 0; i < exerciseIndex; i++) {
    cout << (i + 1) << ". " << currentCustomWorkout[i] << endl;
  }
  cout << "\nCustom workout has been set up successfully!\n";

  // Add the footer to the file
  customFile << "=======================================================" << endl;
  customFile.close();
}

void startCustomWorkout() {
  clearScreen();
  greet();
  string customExerciseFilename = loggedInUsername + "_customExercises.txt";
  int choice = -1;

  // Check if the custom exercise file exists
  ifstream customFile(customExerciseFilename);
  if (!customFile.is_open()) {
    cout << "No custom exercise file found.\n";
    cout << "Creating a new custom exercise file...\n";
    createCustomExerciseFile(customExerciseFilename); // This creates the file if it doesn't exist
    createCustomWorkout(customExerciseFilename);
  } else {
    cout << "Custom exercise file exists. What would you like to do?\n";
    while (choice < 1 || choice > 2) {
      cout << "1. Use existing custom workout\n";
      cout << "2. Create new custom workout\n";
      choice = getValidInteger();
    }

    // If user chooses option 2 (create new custom workout), overwrite the
    // existing file
    if (choice == 2) {
      cout << "Replacing the custom workout...\n";
      createCustomExerciseFile(customExerciseFilename);
      // Now, you can re-open the file and add new exercises
      createCustomWorkout(customExerciseFilename);
    } else if (choice == 1) {
      loadCustomWorkout();
    }
  }
  customFile.close();

  // Proceed to the custom workout creation

  startCustomSession();
}

void startDefaultSession(string loggedInUsername, int muscleGroup) {
  string muscleGroupName;
  if (muscleGroup == 0)
    muscleGroupName = "Push";
  if (muscleGroup == 1)
    muscleGroupName = "Pull";
  if (muscleGroup == 2)
    muscleGroupName = "Legs";

  viewWorkoutHistory(muscleGroupName);
  // Initialize workout log
  ofstream tempFile(loggedInUsername + "_tempWorkout.txt");
  tempFile << "--------- Workout Session - " << getCurrentDate() << " -------------\n";
  tempFile << "Focus: " << muscleGroupName << "\nExercises:\n";
  tempFile.close();

  // Total number of exercises in the muscle group (we'll loop through 6
  // exercises)
  int totalDuration = 0; // 5 minutes per exercise

  // Process each exercise
  for (int i = 0; i < 6; i++) {
    string exerciseName = exercises[muscleGroup][i];
    cout << endl << "-> Exercise: " << exerciseName << "\n";

    int currentExercise[3][5] = {{0}}; // Weights, Reps, Volume
    int setCount = 0;

    while (setCount < 5) {
      int choice = -1;
      while (choice < 1 || choice > 2) {
        cout<<endl;
        cout << "1. Add Set\n2. Skip (Go to next exercise)\n";
        cout << "Please select an option: ";
        choice = getValidInteger(); // validation
      }

      if (choice == 2)
        break;

      if (choice == 1) {
        
        cout << endl;
        cout << "Enter weight for set " << (setCount + 1) << ": ";
        currentExercise[0][setCount] = getValidInteger(); // validation: max 600kg
        while (currentExercise[0][setCount] <= 0 || currentExercise[0][setCount] > 600) {
          cout << "Invalid input! Weight must be between 0 and 600 kgs." << endl;
          cout << "Enter weight for set " << (setCount + 1) << "(in kg) : ";
          currentExercise[0][setCount] = getValidInteger();
        }

        cout << "Enter reps for set " << (setCount + 1) << ": ";
        currentExercise[1][setCount] = getValidInteger(); // validation: max 100 reps
        while (currentExercise[1][setCount] <= 0 || currentExercise[1][setCount] > 100) {
          cout << "Invalid input! Reps must be between 0 and 100." << endl;
          cout << "Enter reps for set " << (setCount + 1) << " : ";
          currentExercise[1][setCount] = getValidInteger();
        }

        currentExercise[2][setCount] = calculateSetVolume(currentExercise[0][setCount], currentExercise[1][setCount]);
        totalWorkoutVolume += currentExercise[2][setCount];
        setCount++;
        totalDuration += 5;
      } else {
        cout << "Invalid choice. Try again.\n";
      }
    }

    saveToTempFile(muscleGroupName, exerciseName, currentExercise, setCount);

    cout << "\033[4m" << "Note:" << "\033[0m" << " Data for " << exerciseName << " has been saved.\n";
    if (setCount == 0) {
      cout << "No sets added for this exercise.\n";
    }
  }

  // Add total volume and footer to the temp file
  tempFile.open(loggedInUsername + "_tempWorkout.txt", std::ios::app);
  tempFile << "\nTotal Volume: " << totalWorkoutVolume << " kg\n";
  tempFile << "Post-workout notes: " << addWorkoutNotes() << "\n";
  tempFile << "Total Duration: " << totalDuration << " minutes\n"; // Added total duration here
  tempFile << "---------------------------------------------------\n";
  tempFile.close();

  // Ask user to save or discard session
  int saveChoice = -1;
  clearScreen();
  greet();
  cout << "Do you want to save this workout session?\n1. Save\n2. Discard\n";
  saveChoice = getValidInteger();
  while (saveChoice < 1 || saveChoice > 2) {
    cout << "Invalid input! Please enter 1 to save or 2 to discard: ";
    saveChoice = getValidInteger();
  }

  if (saveChoice == 2) {
    deleteTempFile(loggedInUsername);
    cout << "Workout session discarded.\n";
  } else {
    saveWorkoutToHistory(muscleGroupName);
    deleteTempFile(loggedInUsername);
    cout << "Workout session saved successfully.\n";
  }
}

void displayDefaultWorkout(int muscleGroup) {
  clearScreen();
  greet();
  if (muscleGroup == 0) {
    cout << endl;
    cout << "<<< Push Workout >>>" << endl;
    cout << endl;
  } else if (muscleGroup == 1) {
    cout << endl;
    cout << "<<< Pull Workout >>>" << endl;
    cout << endl;
    cout << endl;
  } else if (muscleGroup == 2) {
    cout << endl;
    cout << "<<< Legs Workout >>>" << endl;
    cout << endl;
  }

  for (int i = 0; i < 6; i++) {
    cout << "-> " << exercises[muscleGroup][i] << endl;
  }
}

void startDefaultWorkout(string exercises[3][6]) {
  clearScreen();
  greet();
  int choice = -1;

  // Display muscle groups to the user
  while (choice < 1 || choice > 3) {
    cout << endl;
    cout << "<<< Muscle Group >>>\n";
    cout << "1. Push\n2. Pull\n3. Legs\n\n";
    cout << "Please select an option: ";

    choice = getValidInteger();
    if (choice < 1 || choice > 3) {
      clearScreen();
      greet();
      cout << "Invalid choice! Please select 1, 2, or 3.\n";
    }
  }

  // Adjust index for zero-based array
  choice = choice - 1;

  // Show exercises for the selected muscle group
  displayDefaultWorkout(choice);
  startDefaultSession(loggedInUsername, choice);
}

void startNewWorkout() {
    clearScreen();
    greet();
    int workoutChoice = -1;
    string currentWorkout[6]; // 6 exercises in total for default

    // Ask user to choose workout type (Default/Custom)
      cout << endl;
      cout << "<<< Workout Type >>> \n1. Default Workout\n2. Custom Workout\n";
      cout << "Please select an option: ";
      workoutChoice = getValidInteger();
      while (workoutChoice < 1 || workoutChoice > 2) {
          clearScreen();
          greet();
          cout << "Invalid choice! Please select 1 or 2.\n";
          cout << endl;
          cout << "<<< Workout Type >>> \n1. Default Workout\n2. Custom Workout\n";
          cout << "Please select an option: ";

          workoutChoice = getValidInteger();
          if (workoutChoice < 1 || workoutChoice > 2)
          {
            cout << "Invalid choice! Please select 1 or 2.\n";
          }
      }

    // Process workout based on user's choice
    if (workoutChoice == 1) {
        clearScreen();
        greet();
        startDefaultWorkout(exercises);
        displayWorkoutMenu();
    } else if (workoutChoice == 2) {
        clearScreen();
        greet();
        startCustomWorkout();
        displayWorkoutMenu();
    }
}

