#include<iostream>
#include<cstdlib>
#include "ABODAstd.h"

using namespace std;

enum Difficulty {Easy = 1 , Medium = 2 , Hard = 3 , Mix = 4};
enum OperationType {Addition = 1 , Subtraction = 2  , Multiplication = 3 , Division = 4 , Modulas = 5 , MixOp = 6};

struct GameResults {
	int CorrectAnswers = 0;
	int WrongAnswers = 0;
};

int ReadNumberOfQuestions()
{
	return ReadPositiveNumber("HOW MANY QUESTIONS DO YOU WANT TO ANSWER");
}

Difficulty ReadQuestionsDifficulty()
{
	return (Difficulty)(ValidateNumberInRange(1, 4, "ENTER QUESTIONS LEVEL [1] EASY , [2] MEDIUM , [3] HARD , [4] MIX ?"));
	
	
}

OperationType ReadQuestionsOperationsType()
{
	return (OperationType)(ValidateNumberInRange(1, 6, "ENTER OPERATION TYPE [1] ADDITION , [2] SUBTRACTION , [3] MULTIPLICATION , [4] DIVISION , [5] MODULAS , [6] MIX ?"));
}

int NumberGenerator(Difficulty Difficulty)
{
	switch (Difficulty)
	{
	case Easy:
		return RandomNumber(1, 10);
	case Medium:
		return RandomNumber(10, 50);
	case Hard:
		return RandomNumber(50, 100);
	}
}

Difficulty IsDifficultyMix(Difficulty QuestionDifficulty)
{
	if (QuestionDifficulty == Mix)
	{
		return (Difficulty)(RandomNumber(1, 3));
	}

	else
	{
		return QuestionDifficulty;
	}
}

char RandomOperationGenerator()
{
	char OperationArray[5] = { '+' , '-' ,'*' , '/' , '%'};

	return OperationArray[RandomNumber(0, 4)];
}

char OperationGenerator(OperationType OperationType)
{
	switch (OperationType)
	{
	case Addition:
		return '+';
	case Subtraction:
		return '-';
	case Multiplication:
		return '*';
	case Division:
		return '/';
	case Modulas :
		return '%';
	case MixOp:
		return RandomOperationGenerator();
	}
}

string GetQuestionDifficultyString(Difficulty Difficulty)
{
	switch (Difficulty)
	{
	case Easy:
		return "EASY";
	case Medium:
		return "MEDIUM";
	case Hard:
		return "HARD";
	case Mix:
		return "MIX";
	}
}

string GetQuestionOperationTypeString(OperationType OperationType)
{
	switch (OperationType)
	{
	case Addition:
		return "+";
	case Subtraction:
		return "-";
	case Multiplication:
		return "*";
	case Division:
		return "/";
	case Modulas:
		return "%";
	case MixOp:
		return "MIX";
	}
}

int QuestionCalculator(int Number1, char Operation, int Number2)
{
	switch (Operation)
	{
	case '+':
		return Number1 + Number2;
	case '-':
		return Number1 - Number2;
	case '*':
		return Number1 * Number2;
	case '/':
		return Number1 / Number2;
	case '%' :
		return Number1 % Number2;
	}
}

GameResults IsAnswerRight(int PlayerAnswer, int RightAnswer, GameResults GameResult)
{
	if (PlayerAnswer == RightAnswer)
	{
		cout << "RIGHT ANSWER :-)\n";
		system("color 2F");
		GameResult.CorrectAnswers++;
	}

	else
	{
		cout << "WRONG ANSWER :-(\n\a";
		cout << "THE RIGHT ANSWER IS : " << RightAnswer << "\n";
		system("color 4F");
		GameResult.WrongAnswers++;
	}

	return GameResult;
}

GameResults GenerateQuestion(int QuestionNumber, int NumberOfQuestions, Difficulty ChosenDifficulty, OperationType OperationType, GameResults GameResult)
{
	Difficulty QuestionDifficulty = IsDifficultyMix(ChosenDifficulty);
	int Number1 = NumberGenerator(QuestionDifficulty);
	int Number2 = NumberGenerator(QuestionDifficulty);
	char Operation = OperationGenerator(OperationType);
	int RightAnswer = QuestionCalculator(Number1, Operation, Number2);

	cout << "QUESTION [" << QuestionNumber << "/" << NumberOfQuestions << "]\n\n";
	cout << Number1 << "\n";
	cout << Number2 << ' ' << Operation << "\n";
	cout << "____________________\n";

	int PlayerAnswer;
	cin >> PlayerAnswer;

	return IsAnswerRight(PlayerAnswer, RightAnswer , GameResult);

}

string FinalResult(GameResults GameResult)
{
	if (GameResult.CorrectAnswers >= GameResult.WrongAnswers)
	{
		return "PASS\n";
	}

	else
	{
		return "FAIL\n";
	}
}

void PrintGameResults(int NumberOfQuestions, Difficulty Difficulty, OperationType OperationType, GameResults GameResult)
{
	cout << "_____________________________________\n\n";
	cout << "  FINAL RESULTS IS " << FinalResult(GameResult) << "\n";
	cout << "_____________________________________\n\n";
	cout << "NUMEBER OF QUESTIONS    : " << NumberOfQuestions << "\n";
	cout << "QUESTIONS LEVEL         : " << GetQuestionDifficultyString(Difficulty) << "\n";
	cout << "OPERATION TYPE          : " << GetQuestionOperationTypeString(OperationType) << "\n";
	cout << "NUMBER OF RIGHT ANSWERS : " << GameResult.CorrectAnswers << "\n";
	cout << "NUMBER OF WRONG ANSWERS : " << GameResult.WrongAnswers << "\n";
	cout << "\n_____________________________________\n\n";
}

void MathGame()
{
	do
	{
		GameResults GameResult;
		int NumberOfQuestions = ReadNumberOfQuestions();
		Difficulty Difficulty = ReadQuestionsDifficulty();
		OperationType OperationType = ReadQuestionsOperationsType();

		for (int QuestionNumber = 1; QuestionNumber <= NumberOfQuestions; QuestionNumber++)
		{
			GameResult = GenerateQuestion(QuestionNumber, NumberOfQuestions, Difficulty, OperationType, GameResult);
		}

		PrintGameResults(NumberOfQuestions, Difficulty, OperationType, GameResult);

	} while (DoYouWantToPlayAgain());
}

int main()
{

	MathGame();

	return 0;
}