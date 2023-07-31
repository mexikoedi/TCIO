// using namespace std to prevent usage of std::
// including iostream to use input/output operations like cout/cin
// including fstream to use read/write operations on files (otherwise both ofstream (write on files) and ifstream (read from files) needed)
using namespace std;
#include <iostream>
#include <fstream>

// Beginning of the application
void greeting()
{
    cout << "Hello.\nThis is an application which was made to test and learn various C++ elements.\n";
}

// Function to check if the input string is an integer
bool isInteger(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to check if the input string is an integer but + and - are allowed at first place
bool isInputInteger(string str)
{
    int start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        if (str[1] == '-' || str[1] == '+' || str[1] == '\0')
        {
            return false;
        }
        else
        {
            start = 1;
        }
    }
    for (int i = start; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Function to read values from the randNum array and printing them after calculation to show the generated numbers
void pointer(int *randNumArr, int lengthParam)
{
    if (lengthParam == 1)
    {
        cout << "Generated random number was the following: ";
    }
    else
    {
        cout << "Generated random numbers were the following: ";
    }

    for (int i = 0; i < lengthParam; i++)
    {
        cout << randNumArr[i] << " ";
    }

    // Test pointers/references by printing value and memory address of the array lengthParam variable and memory location of the pointer randNumArr
    cout << "\n\nPointer and reference test: \n";
    randNumArr = &lengthParam;
    cout << "Array length value: " << lengthParam << "\n";
    cout << "Array length memory address: " << &lengthParam << "\n";
    cout << "Array pointer memory location: " << randNumArr;
}

// Function which generates numbers, writes them to wl.txt, reads them again and starts a math quiz
void calculation()
{
    // Declaring variables for positive/negative random numbers and length
    int posRandNum = 0;
    int negRandNum = 0;
    int length = 0;

    // Asking user for valid array length (with variable input), converting input to int + assigning it to length and declaring the array if number is valid
    cout << "How many mathematical questions do you wish?\nAnswer: \n";
    string input;
    cin >> input;
    try
    {
        if (isInteger(input))
        {
            length = stoi(input);
            if (length == 1)
            {

                cout << "\nCalculation starts now.\n"
                     << length << " random question:\n\n";
            }
            else if (length > 1)
            {
                cout << "\nCalculation starts now.\n"
                     << length << " random questions:\n\n";
            }
            else
            {
                cout << "Invalid number for questions! Please enter a positive number!\n\n";
                calculation();
            }
        }
        else
        {
            cout << "Only numbers allowed! Please enter a positive number!\n\n";
            calculation();
        }
    }
    catch (out_of_range const &)
    {
        cout << "Please enter an integer!\n\n";
        calculation();
    }
    int randNum[length];

    // Declaring counter variable
    int k = 0;

    // Causes the program to start generating numbers from a different point in the sequence every time it runs, making it appear to be less predictable (for rand() method)
    srand(time(NULL));

    // Generating positive/negative random numbers and saving them into the randNum array
    while (k < length)
    {
        // Save positive random numbers at even positions and negative random numbers at odd positions (numbers are between 0 and 99)
        if (k % 2 == 0)
        {
            posRandNum = rand() % 100;
            randNum[k] = posRandNum;
        }
        else
        {
            negRandNum = -(rand() % 100);
            randNum[k] = negRandNum;
        }
        k++;
    }

    // Clearing wl.txt file if possible (file exists)
    if (remove("wl.txt") != 0)
    {
        perror("Error clearing wl.txt file!\n");
        cout << "Creating wl.txt file!\n\n";
    }
    else
    {
        ofstream{"wl.txt"};
    }

    // Declaring ofstream variable (writing to file) and opening wl.txt file
    ofstream wlW;
    wlW.open("wl.txt");

    // Writing the values of randNum array into wl.txt (if file is open otherwise print error)
    if (wlW.is_open())
    {
        for (int i = 0; i < length; i++)
        {
            wlW << randNum[i] << "\n";
        }
    }
    else
    {
        cout << "Couldn't open wl.txt file!";
    }

    // Closing wl.txt file
    wlW.close();

    // Declaring string variable for the values of wl.txt, ifstream variable (reading to file), counter variable, five variables for the calculation questions and opening wl.txt file
    string line;
    ifstream wlR;
    int j = 1;
    int random = 0;
    int correct = 0;
    string input_answer;
    int answer = 0;
    int solution = 0;
    wlR.open("wl.txt");

    // Reading the values of randNum array into wl.txt (if file is open otherwise print error)
    // Asking addition/subtraction questions and checking if given answer is correct (if not give correct answer)
    // Only valid answers accepted otherwise it gives an error and asks the same question again
    // At the end it will display the amount of total, correct and wrong answers
    if (wlR.is_open())
    {
        while (getline(wlR, line))
        {
            random = rand() % 100;
            if (j % 2 == 0)
            {
                cout << "Question " << j << ":\n"
                     << line << " + " << random << " = ?\n"
                     << "Answer: ";

                while (true)
                {
                    cin >> input;
                    if (isInputInteger(input))
                    {
                        try
                        {
                            answer = stoi(input);
                        }
                        catch (out_of_range const &)
                        {
                            cout << "Please enter an integer!\n";
                        }
                        break;
                    }
                    else
                    {
                        cout << "\nInvalid input! Please enter a valid integer!\n\n";
                        cout << "Question " << j << ":\n"
                             << line << " + " << random << " = ?\n"
                             << "Answer: ";
                    }
                }
                solution = stoi(line) + random;
            }
            else
            {
                cout << "Question " << j << ":\n"
                     << line << " - " << random << " = ?\n"
                     << "Answer: ";

                while (true)
                {
                    cin >> input;
                    if (isInputInteger(input))
                    {
                        try
                        {
                            answer = stoi(input);
                        }
                        catch (out_of_range const &)
                        {
                            cout << "Please enter an integer!\n";
                        }
                        break;
                    }
                    else
                    {
                        cout << "\nInvalid input! Please enter a valid integer!\n\n";
                        cout << "Question " << j << ":\n"
                             << line << " - " << random << " = ?\n"
                             << "Answer: ";
                    }
                }
                solution = stoi(line) - random;
            }
            if (answer == solution)
            {
                cout << "\nCorrect!\n\n";
                correct++;
            }
            else
            {
                cout << "\nIncorrect!\nCorrect answer is " << solution << "!\n\n";
            }
            j++;
        }
        cout << "Total amount of questions: " << length << "\nCorrect answers: " << correct << "\nFalse answers: " << length - correct << "\n\n";
    }
    else
    {
        cout << "Couldn't open wl.txt file!";
    }

    // Clearing wl.txt file if possible (file exists)
    wlR.close();

    // Clearing wl.txt file
    if (remove("wl.txt") != 0)
    {
        perror("Error clearing wl.txt file!\n");
        cout << "Creating wl.txt file!\n\n";
    }
    else
    {
        ofstream{"wl.txt"};
    }

    // Giving randNum array to pointer function
    pointer(randNum, length);
}

// End of the application
void farewell()
{
    cout << "\n\nThat's all for now.\nThank you for using this application.\n\n";
}

// Running all methods from above and pausing programm so user can read everything and close with any button
int main()
{
    greeting();
    calculation();
    farewell();
    system("pause");
}