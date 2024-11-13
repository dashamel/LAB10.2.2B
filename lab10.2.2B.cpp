#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // для підтримки кирилиці

using namespace std;

enum Speciality { ComputerScience, Informatics, MathAndEconomics, PhysicsAndInformatics, LaborEducation };
string specialityStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

union ExtraGrade {
    int programmingGrade;
    int numericalMethodsGrade;
    int pedagogyGrade;
};

// Структура для представлення студента
struct Student {
    string surname;
    int course;
    Speciality speciality;
    int physicsGrade;
    int mathGrade;
    ExtraGrade extraGrade;
    double halfbal;
};

// Прототипи функцій
void Create(Student* s, const int N);
void Print(const Student* s, const int N);
double CalculateAverage(const Student& s);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    Student* s = new Student[N];

    int menuItem;
    do {
        cout << "\n\nВиберіть дію:\n";
        cout << " [1] - введення даних студентів\n";
        cout << " [2] - вивід даних на екран\n";
        cout << " [3] - індексне сортування\n";
        cout << " [0] - вихід\n";
        cout << "Введіть значення: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3: {
            int* indices = IndexSort(s, N);
            cout << "Дані після індексного сортування:\n";
            PrintIndexSorted(s, indices, N);
            delete[] indices;
            break;
        }
        case 0:
            break;
        default:
            cout << "Невірний вибір! Введіть число з меню.\n";
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        cout << " Прізвище: ";
        cin >> s[i].surname;
        cout << " Курс: ";
        cin >> s[i].course;
        cout << " Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> speciality;

        s[i].speciality = static_cast<Speciality>(speciality);
        cout << " Оцінка з фізики: ";
        cin >> s[i].physicsGrade;
        cout << " Оцінка з математики: ";
        cin >> s[i].mathGrade;

        // Введення третьої оцінки залежно від спеціальності
        switch (s[i].speciality) {
        case ComputerScience:
            cout << " Оцінка з програмування: ";
            cin >> s[i].extraGrade.programmingGrade;
            break;
        case Informatics:
            cout << " Оцінка з чисельних методів: ";
            cin >> s[i].extraGrade.numericalMethodsGrade;
            break;
        default:
            cout << " Оцінка з педагогіки: ";
            cin >> s[i].extraGrade.pedagogyGrade;
            break;
        }

        s[i].halfbal = CalculateAverage(s[i]);
    }
}

void Print(const Student* s, const int N) 
{
    cout << "================================================================================================================================================\n";
    cout << "| №  | Прізвище       | Курс | Спеціальність             |  Фізика | Математика | Програмування | Чисельні методи  | Педагогіка | Середній бал |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << i + 1 << " | "
            << setw(16) << left << s[i].surname << "| "
            << setw(4) << s[i].course << " | "
            << setw(26) << left << specialityStr[s[i].speciality] << "| "
            << setw(7) << s[i].physicsGrade << " | "
            << setw(10) << s[i].mathGrade << " | ";

        if (s[i].speciality == ComputerScience) {
            cout << setw(13) << s[i].extraGrade.programmingGrade << " | "
                << setw(16) << "-" << " | "
                << setw(10) << "-" << " |";
        }
        else if (s[i].speciality == Informatics) {
            cout << setw(13) << "-" << " | "
                << setw(16) << s[i].extraGrade.numericalMethodsGrade << " | "
                << setw(10) << "-" << " |";
        }
        else {
            cout << setw(13) << "-" << " | "
                << setw(16) << "-" << " | "
                << setw(10) << s[i].extraGrade.pedagogyGrade << " |";
        }
        cout << " " << setw(12) << fixed << setprecision(2) << s[i].halfbal << " |\n";
    }
    cout << "================================================================================================================================================\n";
} 

double CalculateAverage(const Student& s) {
    double sum = s.physicsGrade + s.mathGrade;

    switch (s.speciality) {
    case ComputerScience:
        sum += s.extraGrade.programmingGrade;
        break;
    case Informatics:
        sum += s.extraGrade.numericalMethodsGrade;
        break;
    default:
        sum += s.extraGrade.pedagogyGrade;
        break;
    }

    return sum / 3.0;
}

int* IndexSort(Student* s, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (
                (s[I[j]].halfbal < s[I[j + 1]].halfbal) ||
                (s[I[j]].halfbal == s[I[j + 1]].halfbal && s[I[j]].course > s[I[j + 1]].course) ||
                (s[I[j]].halfbal == s[I[j + 1]].halfbal && s[I[j]].course == s[I[j + 1]].course && s[I[j]].surname < s[I[j + 1]].surname)
                ) {
                swap(I[j], I[j + 1]);
            }
        }
    }

    return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "================================================================================================================================================\n";
    cout << "| №  | Прізвище       | Курс | Спеціальність             |  Фізика | Математика | Програмування | Чисельні методи  | Педагогіка | Середній бал |\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        int idx = I[i];
        cout << "| " << setw(1) << i + 1 << " | "
            << setw(16) << left << s[idx].surname << "| "
            << setw(4) << s[idx].course << " | "
            << setw(26) << left << specialityStr[s[idx].speciality] << "| " 
            << setw(7) << s[idx].physicsGrade << " | "
            << setw(10) << s[idx].mathGrade << " | ";

        if (s[idx].speciality == ComputerScience) {
            cout << setw(13) << s[idx].extraGrade.programmingGrade << " | "
                << setw(16) << "-" << " | "
                << setw(10) << "-" << " |";
        }
        else if (s[idx].speciality == Informatics) {
            cout << setw(13) << "-" << " | " 
                << setw(16) << s[idx].extraGrade.numericalMethodsGrade << " | "
                << setw(10) << "-" << " |";
        }
        else {
            cout << setw(13) << "-" << " | "
                << setw(16) << "-" << " | "
                << setw(10) << s[idx].extraGrade.pedagogyGrade << " |"; 
        }
        cout << " " << setw(12) << fixed << setprecision(2) << s[idx].halfbal << " |\n";
    }
    cout << "================================================================================================================================================\n";
}
