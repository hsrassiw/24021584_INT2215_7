#include "assessment.h"


using std::string;
using std::vector;

void updateMask(string& mask, const char ch, const string& word);
bool isCorrectChar(char ch, const string& mask);
bool isWholeWord(const string& mask);


void updateMask(string& mask, const char ch, const string& word)
{
    /***
     TODO Step 2: given a character ch, update the mask to show the character ch that is in the word
      eg . if ch = 'a' and word = "apple", then mask = "a____"

      Args:
          mask (string&): the string need to be updated
          ch (const char): the character that is tested to see if it is in the word or not
          word (const string&): the word that is needed to be tested
     */
    for (size_t i = 0; i < word.size(); ++i) {
        if (word[i] == ch) {
            mask[i] = ch;
        }
    }

}

int countMistakes(const string& word, HangmanGuesser& hmGuesser)
{
    /***
     TODO Step 3: Implement this function, which returns the number of mistakes
      tried to solve the word by the given HangmanGuesser.

     Args:
         word (const string&): the word that is needed to be tested
         hmGuesser (HangmanGuesser&): the guesser that is used to make the guess
     Returns:
         int: the number of mistakes made by the guesser
     */
    string mask(word.size(), '-');
    int mistakeCount = 0;

    hmGuesser.newGame(word.size(), '-');

    while (mask != word) {
        char ch = hmGuesser.getChar(mask);
        if (ch == 0 || mask.find(ch) != string::npos) {
            break;
        }

        bool correct = false;
        for (int i = 0; i < word.size(); ++i) {
            if (word[i] == ch) {
                mask[i] = ch;
                correct = true;
            }
        }

        if (!correct) {
            ++mistakeCount;
        }

        if (mask == word) {
            return mistakeCount;
        }
    }

    return -1;
}

void getMistakeByWordList(vector<MistakeByWord>& mistakeList, vector<string>& unsolvableList, const vector<string>& testWords, HangmanGuesser& hmGuesser)
{
    /***
     TODO Step 4: given a list of words, return a list of mistakes by word,
        where each mistake is a struct containing the word and the number of mistakes that guesser has made on that word
        you can use the updateMask function to update the mask and isCorrectChar to check if a character is correct
        you can use countMistakes to count the number of mistakes
     Args:
         mistakeList (vector<MistakeByWord>&): the list of mistakes by word
         unsolvableList (vector<string>&): the list of words that cannot be solved by the guesser
         testWords (vector<string>&): the list of words that need to be tested
         hmGuesser (HangmanGuesser&): the guesser that is used to make the guess
     */
    for (const auto& word : testWords) {
        int m = countMistakes(word, hmGuesser);
        if (m < 0) {
            unsolvableList.push_back(word);
        } else {
            mistakeList.emplace_back(MistakeByWord{m, word});
        }
    }
}

bool isCorrectChar(char ch, const string& mask)
{
    return isCharInWord(ch, mask);
}

bool isWholeWord(const string& mask)
{
    return !isCharInWord(MASK_CHAR, mask);
}