#include <windows.h>
#include <conio.h>
#include <string>

const int FIELD_WIDTH = 35;

// struktura przechowująca dane o polu tekstowym
struct TextField {
    COORD position; 
    int cursorPos; 
    std::string text; 
};

//  do ustawienia koloru tekstu w konsoli
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//  do ustawienia pozycji kursora w konsoli
void setCursorPosition(int x, int y) {
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// do rysowania pola tekstowego w konsoli
void drawTextField(const TextField& field) {
    setCursorPosition(field.position.X, field.position.Y);
    setColor(7); 
    std::cout << field.text;
    setCursorPosition(field.position.X + field.cursorPos, field.position.Y);
}

//  do obsługi strzałek
void handleArrowKeys(int key, TextField& field) {
    switch (key) {
    case 75: //  lewo
        if (field.cursorPos > 0) {
            field.cursorPos--;
        }
        break;
    case 77: // prawo
        if (field.cursorPos < field.text.length()) {
            field.cursorPos++;
        }
        break;
    }
}

int main() {
    // początkowe wartości 
    TextField textField;
    textField.position = { 10, 5 }; 
    textField.cursorPos = 0;

    
    while (true) {
        drawTextField(textField);

        // klawiszy
        int key = _getch();
        if (key == 13) { // enter
            break;
        }
        else if (key == 8) { // backspace
            if (textField.cursorPos > 0) {
                textField.text.erase(textField.cursorPos - 1, 1);
                textField.cursorPos--;
            }
        }
        else if (key == 224) { // strzałki
            handleArrowKeys(_getch(), textField);
        }
        else if (key >= 32 && key <= 126 && textField.text.length() < FIELD_WIDTH) {
            textField.text.insert(textField.cursorPos, 1, (char)key);
            textField.cursorPos++;
        }
    }

    return 0;
}
