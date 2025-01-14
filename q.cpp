#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <fstream>
#include <cctype>
#include <regex>
#include <chrono>
#include <thread>
#include <iomanip> // For setw

using namespace std;

// Function prototypes
string loopPrint(char character, int times);
bool login();
void loginSuccessful(const string& username);
bool signup();
bool adminLogin();
void viewUsers();
void viewAdmin();
bool updateAdmin();
char getValidChoice(const string &prompt, const string &validChoices);
void displayAdminLoginPage();
void clearScreen();
bool isValidUsername(const string& username);
string getNumericPhoneNumber();
bool isValidEmail(const string& email);
bool isValidDOB(const string& dob);
bool isValidPassword(const string& password);

// Main function
int main() {
    // Index Page
    cout << "\n\n\n\n\n\n\n\t\t\t" << loopPrint('*', 78);
    cout << "\n\t\t\t\t" << " ____         _____ ____\t _____   _____            _____";
    cout << "\n\t\t\t\t" << "|    | |    |   |      /\t|       |     | |\\    /| |";
    cout << "\n\t\t\t\t" << "|    | |    |   |     / \t|  ___  |_____| | \\  / | |_____";
    cout << "\n\t\t\t\t" << "|    | |    |   |    /  \t|     | |     | |  \\/  | |";
    cout << "\n\t\t\t\t" << "|____| |____| __|__ /___\t|_____| |     | |      | |_____";
    cout << "\n\t\t\t\t" << "     \\"; 
    cout << "\n\t\t\t" << loopPrint('*', 78);
    cout << "\n\n\n\n\n\n\n\n\t" << loopPrint('*', 31);
    cout << " P R E S S  A N Y  K E Y  T O  C O N T I N U E " << loopPrint('*', 31) << "\n";

    getch();

    char opt;

    do {
        clearScreen();

        cout << "\n\t\t" << loopPrint('*', 83);
        cout << "\n\t\t\t\t*\t\t\t\t\t\t*";
        cout << "\n\t\t\t\t*\t\t M A I N  M E N U \t\t*";
        cout << "\n\t\t\t\t*\t\t\t\t\t\t*";
        cout << "\n\t\t" << loopPrint('*', 83);

        cout << "\n\n\n\t\t\t\t\t1. ADMIN LOGIN";
        cout << "\n\n\n\t\t\t\t\t2. USER SIGNUP";
        cout << "\n\n\n\t\t\t\t\t3. USER LOGIN";
        cout << "\n\n\n\t\t\t\t\t0. Exit\n";

        opt = getValidChoice("\n\n\n\t\t\t\t\tEnter Your Choice: ", "1230");
        switch (opt) {
            case '1':
                displayAdminLoginPage();
                break;

            case '2':
                clearScreen();
                if (signup()) {
                    cout << "\n\n\n\t\t\t\t\tSign Up Successful! You can now log in.";
                } else {
                    cout << "\n\n\n\t\t\t\t\tSign Up Failed! Please check the input validations.";
                }
                break;

            case '3':
                login();
                break;

            case '0':
                cout << "\n\n\n\t\t\t\t\tExiting the program. Goodbye!";
                break;

            default:
                cout << "\n\n\n\t\t\t\tInvalid Option! Please try again.";
                break;
        }

        if (opt != '0') getch();

    } while (opt != '0');

    return 0;
}

// Function implementations
string loopPrint(char character, int times) {
    return string(times, character);
}

bool isValidUsername(const string& username) {
    if (username.length() < 5 || username.length() > 20) {
        cout << "\n\t\t\t\t\tUsername must be between 5 and 20 characters.";
        return false;
    }
    for (char c : username) 
	{
        if (!isalnum(c)) {
            cout << "\n\t\t\t\t\tUsername must not contain special characters.";
            return false;
        }
    }
    return true;
}
string getNumericPhoneNumber() {
    string phoneNumber;
    char ch;

    cout << "\n\n\t\t\t\t\tEnter Phone No: ";

    while (true) {
        ch = _getch(); // Read character without displaying
        if (ch == '\r') { // Enter key to finish input
            if (phoneNumber.length() == 10) {
                break; // Valid length, exit loop
            } else {
                cout << "\n\t\t\t\t\tPhone number must be exactly 10 digits. Try again: ";
                phoneNumber.clear(); // Clear invalid input
                continue;
            }
        }
        if (ch == '\b' && !phoneNumber.empty()) { // Handle backspace
            phoneNumber.pop_back();
            cout << "\b \b"; // Remove character from console
        } else if (isdigit(ch)) { // Allow only digits
            if (phoneNumber.length() < 10) {
                phoneNumber += ch;
                cout << ch; // Echo digit
            } else {
                cout << "\a"; // Beep for exceeding length
            }
        } else {
            cout << "\a"; // Beep for invalid input
        }
    }

    return phoneNumber;
}

bool isValidEmail(const string& email) {
    const regex pattern(R"((\w+)(\.{0,1}\w+)*@(\w+)(\.\w+)+)");
    if (!regex_match(email, pattern)) {
        cout << "\n\t\t\t\t\tInvalid Email Format.";
        return false;
    }
    return true;
}
// Function to validate Date of Birth
bool isValidDOB(const string& dob) {
    // Regex pattern to check if DOB follows DD-MM-YYYY format
    regex pattern(R"(^\d{2}-\d{2}-\d{4}$)");

    // Check if the format is correct
    if (!regex_match(dob, pattern)) {
        return false;
    }

    // Extract day, month, year
    int day = stoi(dob.substr(0, 2));
    int month = stoi(dob.substr(3, 2));
    int year = stoi(dob.substr(6, 4));

    // Validate year range
    if (year < 1900 || year > 2023) {
        return false;
    }

    // Validate month range
    if (month < 1 || month > 12) {
        return false;
    }

    // Days in months validation
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Leap year adjustment
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; // February has 29 days in a leap year
    }

    // Validate day range
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

// Function to get valid Date of Birth input
string getDOB() {
    string dob;
    char ch;
    int dashCount = 0;

    cout << "\n\t\t\t\t\tEnter Date of Birth (DD-MM-YYYY): ";

    while (true) {
        ch = _getch(); // Read character without displaying

        // If Enter key is pressed, validate the input
        if (ch == '\r') { // Enter key
            if (dob.length() == 10 && dashCount == 2 && isValidDOB(dob)) {
                // Valid DOB, display eligibility message and exit loop
                //cout << "\n\t\t\t\t\tValid Date of Birth entered: " << dob;
                cout << "\n\t\t\t\t\tYou are eligible for signup." << endl;
                return dob;
            } else {
                // Invalid input
                cout << "\n\t\t\t\t\tInvalid Date of Birth! Please enter a valid date in DD-MM-YYYY format.";
                dob.clear(); // Clear invalid input
                dashCount = 0; // Reset dash counter
                cout << "\n\t\t\t\t\tEnter Date of Birth (DD-MM-YYYY): ";
                continue;
            }
        }
        // Handle Backspace to remove the last character
        else if (ch == '\b' && !dob.empty()) {
            if (dob.back() == '-') {
                dashCount--;
            }
            dob.pop_back();
            cout << "\b \b"; // Remove character from console
        }
        // Check if the character is a digit or a dash symbol
        else if (isdigit(ch) || ch == '-') {
            // Limit input to 10 characters with exactly two dashes
            if (dob.length() < 10) {
                if (ch == '-') {
                    // Ensure only two dashes are entered
                    if (dashCount < 2) {
                        dob += ch;
                        dashCount++;
                        cout << ch;
                    } else {
                        cout << "\a"; // Beep for extra dash
                    }
                } else {
                    dob += ch;
                    cout << ch; // Echo the digit
                }
            } else {
                cout << "\a"; // Beep for exceeding length
            }
        } else {
            cout << "\a"; // Beep for invalid input
        }
    }
}
bool isValidPassword(const string& password) {
    if (password.length() < 8) {
        cout << "\n\t\t\t\t\tPassword must be at least 8 characters long.";
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
        else if (ispunct(c)) hasSpecial = true;
    }
    if (!(hasUpper && hasLower && hasDigit && hasSpecial)) {
        cout << "\n\t\t\t\t\tPassword must include uppercase, lowercase, numbers, and special characters.";
        return false;
    }
    return true;
}

//*User Sign Up Menu*//
bool signup() {
    cout << "\n\n\t\t" << loopPrint('*', 83);
    cout << "\n\t\t\t\t\t*\t U S E R S I G N U P \t*";
    cout << "\n\t\t" << loopPrint('*', 83);

	string username;
    // Loop until a valid username is entered
    while (true) {
        cout << "\n\n\t\t\t\t\tEnter Username: ";
        cin >> username;

        if (isValidUsername(username)) {
            cout << "\t\t\t\t\tUsername is valid.";
            break; // Exit the loop if the username is valid
        } else {
            cout << "\n\t\t\t\t\tPlease try again.";
        }
    }

    string phoneNumber = getNumericPhoneNumber();

    string email;
    while (true) {
        cout << "\n\n\t\t\t\t\tEnter Email: ";
        cin >> email;

        if (isValidEmail(email)) {
            break; // Exit the loop if the email is valid
        } else {
            cout << "\n\t\t\t\t\tPlease enter a valid email address.";
        }
    }

    string dob = getDOB();  // Get valid DOB input
    //cout << "\n\t\t\t\t\tDate of Birth entered: " << dob << endl; // Display entered DOB

	string password;
    while (true) {
        cout << "\n\n\t\t\t\t\tEnter Password: ";
        cin >> password;

        if (isValidPassword(password)) {
            cout << "\n\t\t\t\t\tPassword is valid.";
            break; // Exit loop if valid
        } else {
            cout << "\n\t\t\t\t\tPlease try again.";
        }
    }

    string confirmPassword;
    while (true) {
        cout << "\n\n\t\t\t\t\tConfirm Password: ";
        cin >> confirmPassword;

        if (confirmPassword == password) {
            cout << "\n\t\t\t\t\tPasswords match.";
            break; // Exit loop if passwords match
        } else {
            cout << "\n\t\t\t\t\tPasswords do not match. Please try again.";
        }
    }

    // Open file in append mode
    ofstream usersFile("users.txt", ios::app);
    if (!usersFile) {
        cout << "\n\n\t\t\t\t\tError: Could not save user data!";
        return false;
    }

    // If file is empty, add headers
    if (usersFile.tellp() == 0) {
        usersFile << left << setw(20) << "Username"
                  << setw(20) << "Password"
                  << setw(20) << "Phone Number"
                  << setw(30) << "Email"
                  << setw(15) << "DOB" << endl;
        usersFile << string(105, '-') << endl;
    }

    // Save user data in formatted table
    usersFile << left << setw(20) << username
              << setw(20) << password
              << setw(20) << phoneNumber
              << setw(30) << email
              << setw(15) << dob << endl;

    usersFile.close();
    cout << "\n\n\t\t\t\t\tUser data saved successfully!";
    return true;

}

//USer Rules//
void viewRules() {
    cout << "\n\n\t\t" << loopPrint('*', 83);
    cout << "\n\t\t\t\t*\t R U L E S  A N D  R E G U L A T I O N S \t*";
    cout << "\n\t\t" << loopPrint('*', 83);

    cout << "\n\n\t\t\t\t1. Eligibility to Play:";
    cout << "\n\t\t\t\t   - Players must register and log in to participate in the quiz.";
    cout << "\n\t\t\t\t   - Only one account per player is allowed.";
    cout << "\n\n\t\t\t\t2. Format:";
    cout << "\n\t\t\t\t   - The quiz consists of multiple-choice questions (MCQs).";
    cout << "\n\t\t\t\t   - Each question has four options, and only one is correct.";
    cout << "\n\t\t\t\t   - Players must select their answers within the time limit (if applicable).";
    cout << "\n\n\t\t\t\t3. Scoring:";
    cout << "\n\t\t\t\t   - Correct answers earn points.";
    cout << "\n\t\t\t\t   - No negative marking for incorrect answers.";
    cout << "\n\n\t\t\t\t4. Gameplay:";
    cout << "\n\t\t\t\t   - Players cannot skip questions unless specified.";
    cout << "\n\t\t\t\t   - Once an answer is submitted, it cannot be changed.";
    cout << "\n\n\t\t\t\t5. Time Limit:";
    cout << "\n\t\t\t\t   - Each question must be answered within a specific time (e.g., 30 seconds).";
    cout << "\n\t\t\t\t   - Failing to do so will count as incorrect.";
    cout << "\n\n\t\t\t\t6. Fair Play:";
    cout << "\n\t\t\t\t   - Use of external help is not allowed.";
    cout << "\n\t\t\t\t   - Collaborating with other players is strictly prohibited.";
    cout << "\n\n\t\t\t\t7. Winning Criteria:";
    cout << "\n\t\t\t\t   - The player with the highest score is the winner.";
    cout << "\n\t\t\t\t   - In case of a tie, a tie-breaker round may be conducted.";
    cout << "\n\n\t\t\t\t8. Respect and Conduct:";
    cout << "\n\t\t\t\t   - Players must maintain respectful communication.";
    cout << "\n\t\t\t\t   - Any inappropriate behavior or cheating will result in disqualification.";
    cout << "\n\n\t\t\t\t9. Technical Issues:";
    cout << "\n\t\t\t\t   - If technical issues occur, the quiz may be paused or rescheduled.";
    cout << "\n\n\t\t" << loopPrint('*', 83);

    cin.ignore();  // Clear input buffer
    cin.get();     // Wait for the user to press a key
}

// User Login Menu //
bool login() {
    // User Login Screen
    clearScreen();
    cout << "\n\t\t" << loopPrint('*', 83);
    cout << "\n\t\t\t\t*\t\t U S E R  L O G I N \t\t*";
    cout << "\n\t\t" << loopPrint('*', 83);

    string username, password;

    cout << "\n\n\t\t\t\t\tEnter Username: ";
    cin >> username;

    cout << "\n\t\t\t\t\tEnter Password: ";
    cin >> password;

    // Open the file for reading
    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "\n\n\t\t\t\t\tError: Could not open user data file!";
        return false;
    }

    string fileUsername, filePassword, filePhoneNumber, fileEmail, fileDOB;
    string headerLine; // To skip the header row and separator

    // Skip headers and separator line
    getline(usersFile, headerLine);
    getline(usersFile, headerLine);

    while (usersFile >> fileUsername >> filePassword >> filePhoneNumber >> fileEmail >> fileDOB) {
        // Match username and password
        if (fileUsername == username && filePassword == password) {
            usersFile.close();
            loginSuccessful(username); // Call the separate function
            return true;
        }
    }

    usersFile.close();

    // Invalid Login Message
    cout << "\n\n\t\t\t\t\t? Invalid username or password. Please try again.";
    return false;
}

void loginSuccessful(const string& username) {
    cout << "\n\n\t\t\t\t\tLogin Successful! Welcome, " << username << "!";

    while (true) {
        cout << "\n\t\t\t\t\tDo you want to enter the game? (Y/N): ";
        char choice;
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'Y') {
            // Outer loop to redisplay the game menu
            while (true) {
                clearScreen(); // Clear the screen before displaying the menu
                cout << "\n\t\t" << loopPrint('*', 83);
                cout << "\n\t\t\t\t*\t W E L C O M E  T O  T H E  Q U I Z  G A M E \t*";
                cout << "\n\t\t" << loopPrint('*', 83);

                cout << "\n\n\t\t\t\t\t Choose an option:";
                cout << "\n\n\t\t\t\t\t1. Start a Quiz";
                cout << "\n\n\t\t\t\t\t2. View Rules & Regulations";
                cout << "\n\n\t\t\t\t\t3. View High Scores";
                cout << "\n\n\t\t\t\t\t4. Exit to Main Menu";
                cout << "\n\n\t\t\t\t\tEnter your choice: ";
                int gameChoice;
                cin >> gameChoice;

                if (cin.fail()) { // Handle invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\n\t\t\t\t\t? Invalid choice. Please try again.";
                    continue;
                }

                switch (gameChoice) {
                    case 1:
                        cout << "\n\n\t\t\t\t\t Starting a new quiz... Good luck!";
                        // Logic for starting a quiz
                        // startNewQuiz();
                        break;

                    case 2:
                        clearScreen();
                        viewRules();
                        break;

                    case 3:
                        cout << "\n\n\t\t\t\t\tView High Scores";
                        // Logic for viewing high scores
                        // viewHighScores();
                        break;

                    case 4:
                        cout << "\n\n\t\t\t\t\tReturning to Main Menu...";
                        return; // Exit to the main menu
                        break;

                    default:
                        cout << "\n\n\t\t\t\t\t? Invalid choice. Please try again.";
                }

                // Pause and wait for the user to press a key before returning to the menu
                cout << "\n\n\t\t\t\t\tPress Enter to return to the game menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
                cin.get(); // Wait for Enter key
            }

        } else if (choice == 'N') {
            // Back to Main Menu Message
            cout << "\n\n\t\t\t\t\tReturning to Main Menu...\n";
            return;
        } else {
            cout << "\n\n\t\t\t\t\t? Invalid input. Please press Y or N.";
        }
    }
}

void viewUsers() {
    clearScreen();
    cout << "\n\t\t" << loopPrint('*', 105);
    cout << "\n\t\t\t\t*\t\t V I E W  U S E R S \t\t*";
    cout << "\n\t\t" << loopPrint('*', 105);

    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "\n\n\t\t\t\t\tNo users found or file cannot be opened.";
    } else
    {
        string line;
        cout << "\n\n\t\t\t\t\tRegistered Users:\n";
        cout << "\n\t\t" << loopPrint('-', 105);

        while (getline(usersFile, line)) {
            cout << "\n\t\t\t\t\t" << line;
        }

        cout << "\n\t\t" << loopPrint('-', 105);
    }

    usersFile.close();
}

void viewAdmin() {
    // Admin details
    string adminName = "Gamer";
    string adminEmail = "admin@gmail.com";
    string adminPhone = "12345678910";
    string adminRole = "System Administrator";

    // Display admin details
    cout << "\n\n\t\t" << string(60, '*');
    cout << "\n\t\t\t\t  A D M I N  D E T A I L S";
    cout << "\n\t\t" << string(60, '*');
    cout << "\n\n\t\t\t\tName: " << adminName;
    cout << "\n\t\t\t\tEmail: " << adminEmail;
    cout << "\n\t\t\t\tPhone: " << adminPhone;
    cout << "\n\t\t\t\tRole: " << adminRole;
    cout << "\n\t\t" << string(60, '*') << "\n";
}
//Add Question//
void addQuestion() {
    clearScreen(); // Clear screen before starting the process
    cout << "\n\t\t" << loopPrint('*', 83);
    cout << "\n\t\t\t\t*\t A D D  Q U E S T I O N \t*";
    cout << "\n\t\t" << loopPrint('*', 83);

// Variables to store question details
    string questionText;
    string optionA, optionB, optionC, optionD;
    char correctOption;
    char addMore = 'Y';  // Variable to control whether more questions are added

    do {
        // Get the question details from the admin
        cout << "\n\n\t\t\t\tEnter the question: ";
        cin.ignore(); // To handle leftover newline character from previous input
        getline(cin, questionText);

        cout << "\n\t\t\t\tEnter option A: ";
        getline(cin, optionA);

        cout << "\n\t\t\t\tEnter option B: ";
        getline(cin, optionB);

        cout << "\n\t\t\t\tEnter option C: ";
        getline(cin, optionC);

        cout << "\n\t\t\t\tEnter option D: ";
        getline(cin, optionD);

        // Get the correct option
        while (true) {
            cout << "\n\t\t\t\tEnter the correct option (A/B/C/D): ";
            cin >> correctOption;
            correctOption = toupper(correctOption);

            if (correctOption == 'A' || correctOption == 'B' || correctOption == 'C' || correctOption == 'D') {
                break; // Valid input
            } else {
                cout << "\n\t\t\t\t? Invalid input. Please enter A, B, C, or D.";
            }
        }

        // Open the file in append mode
        ofstream questionsFile("questions.txt", ios::app);
        if (!questionsFile) {
            cout << "\n\n\t\t\t\tError: Unable to open the questions file!";
            return;
        }

        // Write the question details to the file
        questionsFile << questionText << "|" 
                      << optionA << "|" 
                      << optionB << "|" 
                      << optionC << "|" 
                      << optionD << "|" 
                      << correctOption << endl;

        // Ask the user if they want to add more questions
        cout << "\n\n\t\t\t\tDo you want to add more questions? (Y/N): ";
        cin >> addMore;

        // Ensure the input is valid
        if (addMore != 'Y' && addMore != 'y' && addMore != 'N' && addMore != 'n') {
            cout << "\n\t\t\t\t? Invalid input. Please press Y or N.";
            cout << "\n\t\t\t\tReturning to admin menu...\n";
            break;  // Exit the loop on invalid input
        }

    } while (addMore == 'Y' || addMore == 'y'); // Repeat if 'Y' or 'y' is pressed

    // Close the file
    cout << "\n\n\t\t\t\tAll questions added successfully!";
    cout << "\n\n\t\t\t\tPress Enter to return to the admin menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    cin.get(); // Wait for Enter key
}
//View Question//
viewQuestion(){
 clearScreen(); // Clear the screen before displaying questions
    ifstream questionsFile("questions.txt");
    if (!questionsFile) {
        cout << "\n\n\t\t\t\tError: Could not open the questions file!";
    }

    string line;
    int questionNumber = 1;
    
    // Read each question and display it
    while (getline(questionsFile, line)) {
        // Split the line using '|' as delimiter
        stringstream ss(line);
        string questionText, optionA, optionB, optionC, optionD, correctOption;

        // Extract question data
        getline(ss, questionText, '|');
        getline(ss, optionA, '|');
        getline(ss, optionB, '|');
        getline(ss, optionC, '|');
        getline(ss, optionD, '|');
        getline(ss, correctOption, '|');

        // Display the question and options
        cout << "\n\n\t\t\t\tQuestion " << questionNumber++ << ": " << questionText;
        cout << "\n\t\t\t\tA) " << optionA;
        cout << "\n\t\t\t\tB) " << optionB;
        cout << "\n\t\t\t\tC) " << optionC;
        cout << "\n\t\t\t\tD) " << optionD;
        cout << "\n\t\t\t\tCorrect Answer: " << correctOption << endl;
    }

    questionsFile.close();

    cout << "\n\n\t\t\t\tPress Enter to return to the admin menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    cin.get(); // Wait for Enter key
}

//Admin Login//
void displayAdminLoginPage() {
    clearScreen();
    cout << "\n\t\t" << loopPrint('*', 83);
    cout << "\n\t\t\t\t*\t\t A D M I N  L O G I N \t\t*";
    cout << "\n\t\t" << loopPrint('*', 83);

    if (adminLogin()) {
        cout << "\n\n\t\t\t\t\tAdmin Login Successful! Press any key to proceed to Admin Menu.";
        getch();

        char adminOpt;
        do {
            clearScreen();
            cout << "\n\t\t" << loopPrint('*', 83);
            cout << "\n\t\t\t\t*\t\t\t\t\t\t*";
            cout << "\n\t\t\t\t*\t\t A D M I N  M E N U \t\t*";
            cout << "\n\t\t\t\t*\t\t\t\t\t\t*";
            cout << "\n\t\t" << loopPrint('*', 83);

            cout << "\n\n\t\t\t\t\t1. View Users";
            cout << "\n\n\t\t\t\t\t2. View Admin";
            cout << "\n\n\t\t\t\t\t3. Add Question";
            cout << "\n\n\t\t\t\t\t4. View Question";
            cout << "\n\n\t\t\t\t\t0. Back to Main Menu\n";

            adminOpt = getValidChoice("\n\n\t\t\t\t\tEnter Your Choice: ", "12340");

            switch (adminOpt) {
                case '1':
                    clearScreen();
                    viewUsers();
                    cout << "\n\n\t\t\t\t\tPress any key to continue: ";
                    getch();
                    break;

                case '2':
                    clearScreen();
                    viewAdmin();
                    cout << "\n\n\t\t\t\t\tPress any key to continue: ";
                    getch();
                    break;
                    
                case '3':
                    clearScreen();
                    addQuestion();
                    getch();
                    break;
                    
                case '4':
                    clearScreen();
                    viewQuestion();
                    getch();
                    break;

                /*case '3':
                    clearScreen();
                    if (updateAdmin()) {
                        cout << "\n\n\t\t\t\t\tAdmin Details Updated Successfully!";
                    } else {
                        cout << "\n\n\t\t\t\t\tFailed to Update Admin Details!";
                    }
                    cout << "\n\n\t\t\t\t\tPress any key to continue: ";
                    getch();
                    break;*/

                case '0':
                    cout << "\n\n\t\t\t\t\tReturning to Main Menu...";
                    getch();
                    break;

                default:
                    cout << "\n\n\t\t\t\t\tInvalid Option! Please try again.";
                    break;
            }

        } while (adminOpt != '0');
    } else {
        cout << "\n\n\t\t\t\t\tAdmin Login Failed! Invalid credentials. Returning to Main Menu.";
        getch();
    }
}

bool adminLogin() {
    string adminUsername = "admin";
    string adminPassword = "admin123";

    string username, password;
    cout << "\n\n\t\t\t\t\tAdmin Username: ";
    cin >> username;

    cout << "\n\n\t\t\t\t\tPassword: ";
    char ch;
    password = "";
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.erase(password.size() - 1);
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }

    return (username == adminUsername && password == adminPassword);
}

void clearScreen() {
    system("cls");
}

char getValidChoice(const string &prompt, const string &validChoices) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;

        if (validChoices.find(choice) != string::npos) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        } else {
            cout << "\n\t\t\t\t\tInvalid option! Please enter a valid choice." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
