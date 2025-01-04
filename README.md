<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Fitness Logger</title>
</head>
<body>

<h1>Fitness Logger</h1>

<h2>Overview</h2>
<p>The <strong>Fitness Logger</strong> app is a versatile and efficient tool designed to help users track their fitness journeys. It allows users to log workout sessions, monitor their progress towards goals, and keep track of essential data such as weight, reps, and sets. With a focus on simplicity and functionality, the app is built to provide an easy-to-use interface for tracking fitness routines, helping users stay motivated and committed to their health and fitness goals.</p>

<h2>Features</h2>
<ul>
    <li><strong>Workout Session Logging</strong>: Allows users to log workout details such as exercise type, sets, reps, and weight used.</li>
    <li><strong>Goal Tracking</strong>: Users can set fitness goals and track their progress over time.</li>
    <li><strong>Weight Tracking</strong>: Track body weight changes and see how they align with fitness goals.</li>
    <li><strong>Data Persistence</strong>: Data is stored in files, making it easy to retrieve workout history and make updates.</li>
    <li><strong>Customizable Exercises</strong>: Users can create and modify their own set of exercises.</li>
    <li><strong>Easy-to-Use Interface</strong>: The menu system is designed to be user-friendly with options to view, update, and add new entries to the workout log.</li>
</ul>

<h2>Getting Started</h2>
<p>Follow these instructions to get the app up and running on your local machine.</p>

<h3>Prerequisites</h3>
<p>To use the <strong>Fitness Logger</strong> app, you need to have the following installed:</p>
<ul>
    <li><strong>C++ Compiler</strong>: A C++ compiler like GCC or Visual Studio to compile the source code.</li>
    <li><strong>Text Editor or IDE</strong>: Any text editor (e.g., VSCode, Sublime Text) or IDE (e.g., Visual Studio, CLion).</li>
</ul>

<h3>Installation</h3>
<ol>
    <li><strong>Clone the Repository</strong>:
        <pre><code>git clone https://github.com/talhaFASTCr123/Fitness-Logger.git</code></pre>
    </li>
    <li><strong>Navigate to the Project Directory</strong>:
        <pre><code>cd Fitness-Logger</code></pre>
    </li>
    <li><strong>Compile the Code</strong>:
        <p>For GCC, run the following command in the terminal:</p>
        <pre><code>g++ -o fitness_logger main.cpp</code></pre>
    </li>
    <li><strong>Run the App</strong>:
        <p>Once compiled, you can run the app with:</p>
        <pre><code>./fitness_logger</code></pre>
    </li>
</ol>

<h2>Usage</h2>

<h3>Main Menu</h3>
<p>Once the app is running, you'll be presented with the main menu. The menu allows you to:</p>
<ul>
    <li>Log a new workout session.</li>
    <li>View past workout data.</li>
    <li>Set and track fitness goals.</li>
    <li>Update personal details like weight.</li>
</ul>

<h3>Logging a Workout Session</h3>
<p>When logging a workout session, you’ll be prompted to:</p>
<ul>
    <li>Choose the exercise performed.</li>
    <li>Enter the number of sets, reps, and the weight used.</li>
    <li>Optionally, you can add notes about the session (e.g., any challenges faced, improvements, etc.).</li>
</ul>

<h3>Goal Tracking</h3>
<p>You can set goals for different metrics (e.g., lifting weight, running time, etc.) and track progress. The app will show your progress in a simple, easy-to-understand format.</p>

<h2>File Structure</h2>
<p>Here’s an overview of the project structure:</p>
<pre><code>
Fitness-Logger/
├── calculations.h          # Functions for performing fitness calculations
├── fileHandling.h          # Functions for file handling (saving and loading data)
├── forwardDeclarations.h   # Forward declarations for other headers
├── greet.h                 # Greeting messages displayed to the user
├── main.cpp                # Main entry point of the program
├── menuSystem.h            # Code for handling the menu system
├── userManagement.h        # User management and details (e.g., weight)
├── validations.h           # Validation functions for input data
└── workoutManagement.h     # Functions for managing workout logs
</code></pre>

<ul>
    <li><strong>calculations.h</strong>: Includes all the necessary functions to calculate things like total workout weight, goal completion, and statistics.</li>
    <li><strong>fileHandling.h</strong>: Provides functions to read from and write to files, ensuring that your workout logs and progress are saved even after the program ends.</li>
    <li><strong>workoutManagement.h</strong>: Includes functions to log and retrieve workout sessions, making sure data is well-organized.</li>
</ul>

<h2>Contributing</h2>
<p>We welcome contributions to improve the <strong>Fitness Logger</strong>. If you have any feature suggestions, bug fixes, or improvements, feel free to open an issue or submit a pull request.</p>

<h3>How to Contribute:</h3>
<ol>
    <li>Fork the repository.</li>
    <li>Create a new branch (<code>git checkout -b feature-name</code>).</li>
    <li>Make your changes.</li>
    <li>Commit your changes (<code>git commit -am 'Added new feature'</code>).</li>
    <li>Push to the branch (<code>git push origin feature-name</code>).</li>
    <li>Open a pull request.</li>
</ol>

<h2>License</h2>
<p>This project is licensed under the MIT License - see the <a href="LICENSE">LICENSE</a> file for details.</p>

<h2>Acknowledgments</h2>
<ul>
    <li>Thanks to all the contributors who help make this project better.</li>
    <li>Inspiration and ideas from various fitness tracking apps.</li>
</ul>

</body>
</html>
