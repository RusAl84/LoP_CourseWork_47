// Сафин Ильяс Радикович, БАСО-02-22
// Курсовая работа, вариант 47
// Начало работы - 19 марта 2023 года

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> // для функции system();
#include <cstdio> // для функции remove();
#include <cstring> // для функции strcpy_s();
#include <windows.h> // для SetConsoleCP(1251);

using namespace std;

// Структуры
struct Initials {
    char Surname[20];
    char Name[20];
    char Patronymic[20];
};
struct Birthdate {
    short DD;
    short MM;
    short YYYY;
};
struct StudyPlace {
    short EntranceYear;
    char Faculty[6];
    char Department[11];
    char Group[11];
};
struct Semestr {
    short ProgramID;
    short Subjects[10];
};
struct Grade {
    Semestr Terms[9];
};
struct StudyProgram {
    short ProgramID;
    char Subject1[41];
    char Subject2[41];
    char Subject3[41];
    char Subject4[41];
    char Subject5[41];
    char Subject6[41];
    char Subject7[41];
    char Subject8[41];
    char Subject9[41];
    char Subject10[41];
};

int IsStudyProgramExists(short* ProgramID_, StudyProgram* Classes, int* ClassesAmount)
{
    for (int i = 0; i < *ClassesAmount; i++)
    {
        if (Classes[i].ProgramID == *ProgramID_)
        {
            return i;
        }
    }
    return -1;
}

int AreIDsEqual(const char a[8], const char b[8])
{
    for (int i = 0; i < 8; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

// Классы
class Student {
public:
    char UniqueID[8];
    Initials initials;
    Birthdate birthdate;
    StudyPlace studyplace;
    short sex; // 0 - девушка, 1 - парень
    Grade grade;
    
    Student() 
    {
        strcpy_s(UniqueID, "00А0000");
        strcpy_s(initials.Surname, "Иванов");
        strcpy_s(initials.Name, "Иван");
        strcpy_s(initials.Patronymic, "Иванович");
        birthdate.DD = 1;
        birthdate.MM = 1;
        birthdate.YYYY = 2000;
        studyplace.EntranceYear = 0;
        strcpy_s(studyplace.Faculty, "ИКБ");
        strcpy_s(studyplace.Department, "КБ-1");
        strcpy_s(studyplace.Group, "БАСО-02-22");
        sex = 1;
        for (int i = 0; i < 9; i++)
        {
            grade.Terms[i].ProgramID = 241;
            for (int z = 0; z < 10; z++)
            {
                grade.Terms[i].Subjects[z] = 0;
            }
        }
    }
    ~Student() {}
    void PrintMark(char SubjectName[41], short Mark)
    {

        if (Mark == 0)
        {
            cout << SubjectName << " - Нет оценки" << endl;
        }
        else
        {
            cout << SubjectName << " - " << Mark << endl;
        }
    }
    void PrintShortInfo()
    {
        if ((string)UniqueID != "00А0000") // Не печатаю пустых студентов
        {
            cout << UniqueID << " / " << initials.Surname << " " << initials.Name[0] << "." << initials.Patronymic[0] << "." << " / " << studyplace.Group << endl; 
        }
    }
    void PrintInfo(StudyProgram* Classes, int* ClassesAmount) 
    {
        if ((string)UniqueID != "00А0000") // Не печатаю пустых студентов
        {
            short* Mark = (short*) new short;
            short* SemestrProgramID = (short*) new short;
            short* TempID = (short*) new short;
            cout << "============ Ученик " << UniqueID << " ============" << endl;
            cout << "ФИО: " << initials.Surname << " " << initials.Name << " " << initials.Patronymic << endl;
            cout << "Дата рождения: " << birthdate.DD << "." << birthdate.MM << "." << birthdate.YYYY << endl;
            if (sex == 0)
            {
                cout << "Пол: женский" << endl;
            }
            else if (sex == 1)
            {
                cout << "Пол: мужской" << endl;
            }
            else
            {
                cout << "Пол: гендеров всего 2, а в базе данных какая-то ошибка" << endl;
            }
            cout << "Год поступления: " << studyplace.EntranceYear << endl;
            cout << "Факультет (институт): " << studyplace.Faculty << endl;
            cout << "Кафедра: " << studyplace.Department << endl;
            cout << "Группа: " << studyplace.Group << endl;
            cout << "+----- УСПЕВАЕМОСТЬ -----+" << endl;
            for (int i = 0; i < 9; i++)
            {
                *SemestrProgramID = grade.Terms[i].ProgramID;

                if (*SemestrProgramID > 0)
                {
                    for (int i = 0; i < *ClassesAmount; i++)
                    {
                        if (*SemestrProgramID == Classes[i].ProgramID)
                        {
                            *TempID = i;
                        }
                    }
                    cout << "--- СЕМЕСТР " << i + 1 << " ---" << endl;
                    cout << "[Учебный план №" << *SemestrProgramID << "]" << endl;
                    PrintMark(Classes[*TempID].Subject1, grade.Terms[i].Subjects[0]);
                    PrintMark(Classes[*TempID].Subject2, grade.Terms[i].Subjects[1]);
                    PrintMark(Classes[*TempID].Subject3, grade.Terms[i].Subjects[2]);
                    PrintMark(Classes[*TempID].Subject4, grade.Terms[i].Subjects[3]);
                    PrintMark(Classes[*TempID].Subject5, grade.Terms[i].Subjects[4]);
                    PrintMark(Classes[*TempID].Subject6, grade.Terms[i].Subjects[5]);
                    PrintMark(Classes[*TempID].Subject7, grade.Terms[i].Subjects[6]);
                    PrintMark(Classes[*TempID].Subject8, grade.Terms[i].Subjects[7]);
                    PrintMark(Classes[*TempID].Subject9, grade.Terms[i].Subjects[8]);
                    PrintMark(Classes[*TempID].Subject10, grade.Terms[i].Subjects[9]);
                }
                else
                {
                    break;
                }
            }
            delete Mark, SemestrProgramID;
            cout << "+----- КОНЕЦ УСПЕВАЕМОСТИ -----+" << endl;
        }
    }
    short IsHeRealMen(short *TermNumber)
    {
        short* tempShort = (short*) new short;
        *tempShort = 6;
        for (int i = 0; i < 10; i++)
        {
            if ((grade.Terms[*TermNumber-1].Subjects[i] > 0) && (grade.Terms[*TermNumber-1].Subjects[i] < 6))
            {
                *tempShort = min(*tempShort, grade.Terms[*TermNumber-1].Subjects[i]);
            }
        }
        if (*tempShort == 6)
        {
            return 0;
        }
        else
        {
            return *tempShort;
        }
    }
    void SaveStudent() 
    {
        ofstream Output;
        Output.open("Students.bin", ios::binary|ios::app); // app - запись с добавлением, out - перезапись файла
        Output << " " << UniqueID << " " << initials.Surname << " " << initials.Name << " " << initials.Patronymic << " ";
        Output << birthdate.DD << " " << birthdate.MM << " " << birthdate.YYYY << " " << studyplace.EntranceYear << " ";
        Output << studyplace.Faculty << " " << studyplace.Department << " " << studyplace.Group << " " << sex;
        for (int i = 0; i < 9; i++)
        {
            Output << " " << grade.Terms[i].ProgramID;
            for (int z = 0; z < 10; z++)
            {
                Output << " " << grade.Terms[i].Subjects[z];
                // Output << " " << z; // <-- для проверки
            }
        }
    }
    
};

Student* ResizeStudents(Student* OldStudents, int RecordsAmount)
{
    Student* NewStudents = new Student[RecordsAmount];
    memset(NewStudents, 0, sizeof(Student) * RecordsAmount);

    copy(OldStudents, OldStudents+RecordsAmount, NewStudents);

    delete[] OldStudents;

    return NewStudents;
}

StudyProgram* ResizeClasses(StudyProgram* OldClasses, int RecordsAmount)
{
    StudyProgram* NewClasses = new StudyProgram[RecordsAmount];
    memset(NewClasses, 0, sizeof(StudyProgram) * RecordsAmount);

    copy(OldClasses, OldClasses + RecordsAmount, NewClasses);

    delete[] OldClasses;

    return NewClasses;
}

int IsItDate(const char InputDate[11])
{
    for (int i = 0; i < 2; i++)
    {
        if (InputDate[i] != '0' && InputDate[i] != '1' && InputDate[i] != '2' && InputDate[i] != '3' && InputDate[i] != '4' && InputDate[i] != '5' && InputDate[i] != '6' && InputDate[i] != '7' && InputDate[i] != '8' && InputDate[i] != '9')
        {
            return 0;
        }
    }
    if (InputDate[2] != '.' || InputDate[5] != '.')
    {
        return 0;
    }
    for (int i = 3; i < 5; i++)
    {
        if (InputDate[i] != '0' && InputDate[i] != '1' && InputDate[i] != '2' && InputDate[i] != '3' && InputDate[i] != '4' && InputDate[i] != '5' && InputDate[i] != '6' && InputDate[i] != '7' && InputDate[i] != '8' && InputDate[i] != '9')
        {
            return 0;
        }
    }
    for (int i = 6; i < 10; i++)
    {
        if (InputDate[i] != '0' && InputDate[i] != '1' && InputDate[i] != '2' && InputDate[i] != '3' && InputDate[i] != '4' && InputDate[i] != '5' && InputDate[i] != '6' && InputDate[i] != '7' && InputDate[i] != '8' && InputDate[i] != '9')
        {
            return 0;
        }
    }
    return 1;
}

void SaveClasses(StudyProgram* Classes, int* ClassesAmount)
{
    rename("Classes.bin", "Classes_backup.bin");
    ofstream OutputFile;
    OutputFile.open("Classes.bin", ios::binary | ios::app);
    if (OutputFile.is_open())
    {
        for (int i = 0; i < *ClassesAmount; i++)
        {
            OutputFile << " " << Classes[i].ProgramID << " " << Classes[i].Subject1 << " " << Classes[i].Subject2 << " " << Classes[i].Subject3 << " " << Classes[i].Subject4 << " " << Classes[i].Subject5 << " " << Classes[i].Subject6 << " " << Classes[i].Subject7 << " " << Classes[i].Subject8 << " " << Classes[i].Subject9 << " " << Classes[i].Subject10;
        }
        OutputFile.close();
    }
    else
    {
        remove("Classes.bin");
        rename("Classes_backup.bin", "Classes.bin");
    }
}

void SaveStudents(Student* Students, int* StudentsAmount)
{
    rename("Students.bin", "Students_backup.bin");
    ofstream OutputFile;
    OutputFile.open("Students.bin", ios::binary | ios::app);
    if (OutputFile.is_open())
    {
        for (int i = 0; i < *StudentsAmount; i++)
        {
            Students[i].SaveStudent();
        }
        OutputFile.close();
    }
    else
    {
        remove("Students.bin");
        rename("Students_backup.bin", "Students.bin");
    }

}

void MenuStudents(Student* Students, int* StudentsAmount, StudyProgram* Classes, int* ClassesAmount)
{
    string Action;

    system("cls");
    RepeatMenuStudents:
    cout << "========= МЕНЮ - Студенты =========" << endl;
    cout << "Возможные действия:" << endl;
    cout << "1. Все студенты" << endl;
    cout << "2. Подробнее о студенте" << endl;
    cout << "3. Добавить студента" << endl;
    cout << "4. Изменить студента" << endl;
    cout << "5. Изменить успеваемость студента" << endl;
    cout << "6. Удалить студента" << endl;
    cout << "7. Поиск отличников/хорошистов/троечников" << endl;
    cout << "8. Назад" << endl;
    RepeatMenuStudentsChoice:
    cout << "Выберите действие: ";
    cin >> Action;
    if (Action == "1")
    {
        system("cls"); 
        cout << "========= Список всех студентов =========" << endl;
        cout << "Данные выводятся в формате: номер зачётной книжки / Фамилия И.О. / Группа" << endl;
        for (int i = 0; i < *StudentsAmount; i++)
        {
            Students[i].PrintShortInfo();
        }
        goto RepeatMenuStudents;
    }
    else if (Action == "2")
    {
        string* tempStr = (string*) new string;
        cout << "Введите номер зачётной книжки (в формате 12А4567): ";
        cin >> *tempStr;
        if ((*tempStr).size() == 7)
        {
            for (int i = 0; i < *StudentsAmount; i++)
            {
                if (AreIDsEqual(Students[i].UniqueID, (*tempStr).c_str()) == 1)
                {
                    Students[i].PrintInfo(Classes, ClassesAmount);
                    delete tempStr;
                    goto RepeatMenuStudents;
                }
            }
        }
        cout << "[!] Студент с таким номером зачётной книжки не найден!" << endl;
        delete tempStr;
        goto RepeatMenuStudents;
    }
    else if (Action == "3")
    {
        string* tempStr = (string*) new string;
        short* tempShort = (short*) new short;
        Student tempStudent;

        cout << "========= Добавление нового ученика =========" << endl;
        Return2_0:
        cout << "Введите номер зачётной книжки (в формате 12А4567): ";
        cin >> *tempStr;
        if ((*tempStr).size() == 7)
        {
            for (int i = 0; i < *StudentsAmount; i++)
            {
                if (AreIDsEqual(Students[i].UniqueID, (*tempStr).c_str()) == 1)
                {
                    cout << "Студент с таким номером зачётной книжки уже существует!" << endl;
                    goto Return2_0;
                }
            }
            strcpy_s(tempStudent.UniqueID, 8, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Неправильный формат номера зачётной книжки!" << endl;
            goto Return2_0;
        }
        Return2_1:
        cout << "Введите фамилию студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() >= 20)
        {
            cout << "[!] Фамилия слишком длинная!" << endl;
            goto Return2_1;
        }
        strcpy_s(tempStudent.initials.Surname, 20, (*tempStr).c_str());
        Return2_2:
        cout << "Введите имя студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() >= 20)
        {
            cout << "[!] Имя слишком длинное!" << endl;
            goto Return2_2;
        }
        strcpy_s(tempStudent.initials.Name, 20, (*tempStr).c_str());
        Return2_3:
        cout << "Введите отчество студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() >= 20)
        {
            cout << "[!] Отчество слишком длинное!" << endl;
            goto Return2_3;
        }
        strcpy_s(tempStudent.initials.Patronymic, 20, (*tempStr).c_str());
        Return2_4:
        cout << "Введите дату рождения студента (в формате ДД.ММ.ГГГГ): ";
        cin >> *tempStr;
        if (((*tempStr).size() == 10) && (IsItDate((*tempStr).c_str()) == 1))
        {
            int* dd_ = (int*) new int;
            int* mm_ = (int*) new int;
            int* yyyy_ = (int*) new int;
            sscanf_s((*tempStr).c_str(), "%d.%d.%d", dd_, mm_, yyyy_);
            if (*dd_ < 1)
            {
                *dd_ = 1;
            }
            if ((*dd_ > 29 && *mm_ == 2 && *yyyy_ % 4 == 0) || (*dd_ > 28 && *mm_ == 2 && *yyyy_ % 4 != 0))
            {
                *dd_ = 1;
                *mm_ = 3;
            }
            else if (*dd_ > 31 && (*mm_ == 1 || *mm_ == 3 || *mm_ == 5 || *mm_ == 7 || *mm_ == 8 || *mm_ == 10 || *mm_ == 12))
            {
                *dd_ = 1;
                *mm_ = *mm_ + 1;
            }
            else if (*dd_ > 30 && (*mm_ == 4 || *mm_ == 6 || *mm_ == 9 || *mm_ == 11))
            {
                *dd_ = 1;
                *mm_ = *mm_ + 1;
            }
            if (*mm_ > 12) {
                *yyyy_ = *yyyy_ + 1;
                *mm_ = 1;
            }
            tempStudent.birthdate.DD = *dd_;
            tempStudent.birthdate.MM = *mm_;
            tempStudent.birthdate.YYYY = *yyyy_;
            delete dd_, mm_, yyyy_;
        }
        else 
        {
            cout << "[!] Введённое значение не похоже на дату!" << endl;
            goto Return2_4;
        }
        Return2_5:
        cout << "Введите год поступления: ";
        cin >> *tempShort;
        if (*tempShort < (tempStudent.birthdate.YYYY + 7))
        {
            cout << "[!] Навряд ли этот человек такой вундеркинд, что смог поступить в институт до 7 лет!" << endl;
            goto Return2_5;
        }
        tempStudent.studyplace.EntranceYear = *tempShort;
        Return2_6:
        cout << "Введите факультет (институт) (макс. 5 символов): ";
        cin >> *tempStr;
        if ((*tempStr).size() >= 6)
        {
            cout << "[!] Неправильный формат записи факультета!" << endl;
            goto Return2_6;
        }
        strcpy_s(tempStudent.studyplace.Faculty, 6, (*tempStr).c_str());
        Return2_7:
        cout << "Введите кафедру (макс. 10 символов): ";
        cin >> *tempStr;
        if ((*tempStr).size() >= 11)
        {
            cout << "[!] Неправильный формат записи кафедры!" << endl;
            goto Return2_7;
        }
        strcpy_s(tempStudent.studyplace.Department, 11, (*tempStr).c_str());
        Return2_8:
        cout << "Введите группу (в формате БАСО-00-00): ";
        cin >> *tempStr;
        if ((*tempStr).size() != 10)
        {
            cout << "[!] Неправильный формат записи группы!" << endl;
            goto Return2_8;
        }
        strcpy_s(tempStudent.studyplace.Group, 11, (*tempStr).c_str());
        Return2_9:
        cout << "Введите пол студента (м - мужчина, ж - женщина): ";
        cin >> *tempStr;
        if (*tempStr == "М" || *tempStr == "м")
        {
            tempStudent.sex = 1;
        }
        else if (*tempStr == "Ж" || *tempStr == "ж")
        {
            tempStudent.sex = 0;
        }
        else
        {
            cout << "[!] Неправильно введён пол!" << endl;
            goto Return2_9;
        }
        for (int i = 0; i < 9; i++)
        {
            Return2_10:
            cout << "Введите № учебного плана для семестра №" << i + 1 << " (введите 0 для пустого плана): ";
            cin >> *tempShort;
            if (*tempShort == 0)
            {
                for (int z = i; z < 9; z++)
                {
                    tempStudent.grade.Terms[z].ProgramID = 0;
                }
                break;
            }
            else
            {
                int ProgramID_ = IsStudyProgramExists(tempShort, Classes, ClassesAmount);
                if (ProgramID_ > -1)
                {
                    tempStudent.grade.Terms[i].ProgramID = *tempShort;

                    cout << "+----- Выставление оценок -----+" << endl;
                    cout << "Выставьте оценки за семестр:" << endl;
                    cout << "0 - оценки нет, 2 - незачёт," << endl;
                    cout << "3,4 и 5 - зачёт." << endl;
                    
                    Return2_11:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject1 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[0] = *tempShort;
                    }
                    else
                    {
                        goto Return2_11;
                    }
                    Return2_12:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject2 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[1] = *tempShort;
                    }
                    else
                    {
                        goto Return2_12;
                    }
                    Return2_13:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject3 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[2] = *tempShort;
                    }
                    else
                    {
                        goto Return2_13;
                    }
                    Return2_14:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject4 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[3] = *tempShort;
                    }
                    else
                    {
                        goto Return2_14;
                    }
                    Return2_15:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject5 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[4] = *tempShort;
                    }
                    else
                    {
                        goto Return2_15;
                    }
                    Return2_16:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject6 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[5] = *tempShort;
                    }
                    else
                    {
                        goto Return2_16;
                    }
                    Return2_17:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject7 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[6] = *tempShort;
                    }
                    else
                    {
                        goto Return2_17;
                    }
                    Return2_18:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject8 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[7] = *tempShort;
                    }
                    else
                    {
                        goto Return2_18;
                    }
                    Return2_19:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject9 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[8] = *tempShort;
                    }
                    else
                    {
                        goto Return2_19;
                    }
                    Return2_20:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject10 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        tempStudent.grade.Terms[i].Subjects[9] = *tempShort;
                    }
                    else
                    {
                        goto Return2_20;
                    }
                }
                else
                {
                    cout << "[!] Учебный план №" << *tempShort << "не был найден!" << endl;
                    goto Return2_10;
                }
            }
        }
        *StudentsAmount = *StudentsAmount + 1;
        Students = ResizeStudents(Students, *StudentsAmount);
        Students[*StudentsAmount - 1] = tempStudent;
        delete tempStr, tempShort;
        SaveStudents(Students, StudentsAmount);
        goto RepeatMenuStudents;
    }
    else if (Action == "4")
    {
        string* tempStr = (string*) new string;
        int* tempInt = (int*) new int;
        short* tempShort = (short*) new short;

        cout << "========= Изменение данных о студенте =========" << endl;
        Return4_0:
        cout << "Введите номер зачётной книжки студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() != 7)
        {
            cout << "[!] Это не похоже на зачётную книжку!" << endl;
            goto Return4_0;
        }
        for (int i = 0; i < *StudentsAmount; i++)
        {
            if (AreIDsEqual(Students[i].UniqueID, (*tempStr).c_str()) == 1)
            {
                *tempInt = i;
                goto Continue4_0;
            }
        }
        cout << "[!] Студент с номером зачётной книжки " << *tempStr << " не был найден!" << endl;
        goto RepeatMenuStudents;

        Continue4_0:
        cout << "Изменить номер зачётной книжки (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_1;
        }
        if ((*tempStr).size() == 7)
        {
            strcpy_s(Students[*tempInt].UniqueID, 8, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Это не похоже на номер зачётной книжки!" << endl;
            goto Continue4_0;
        }
        Continue4_1:
        cout << "Изменить фамилию студента (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_2;
        }
        if ((*tempStr).size() < 20)
        {
            strcpy_s(Students[*tempInt].initials.Surname, 20, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Слишком длинная фамилия!" << endl;
            goto Continue4_1;
        }
        Continue4_2:
        cout << "Изменить имя студента (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_3;
        }
        if ((*tempStr).size() < 20)
        {
            strcpy_s(Students[*tempInt].initials.Name, 20, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Слишком длинное имя!" << endl;
            goto Continue4_2;
        }
        Continue4_3:
        cout << "Изменить отчество студента (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_4;
        }
        if ((*tempStr).size() < 20)
        {
            strcpy_s(Students[*tempInt].initials.Patronymic, 20, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Слишком длинное отчество!" << endl;
            goto Continue4_3;
        }
        Continue4_4:
        cout << "Изменить дату рождения студента (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_5;
        }
        if (((*tempStr).size() == 10) && (IsItDate((*tempStr).c_str()) == 1))
        {
            int* dd_ = (int*) new int;
            int* mm_ = (int*) new int;
            int* yyyy_ = (int*) new int;
            sscanf_s((*tempStr).c_str(), "%d.%d.%d", dd_, mm_, yyyy_);
            if (*dd_ < 1)
            {
                *dd_ = 1;
            }
            if ((*dd_ > 29 && *mm_ == 2 && *yyyy_ % 4 == 0) || (*dd_ > 28 && *mm_ == 2 && *yyyy_ % 4 != 0))
            {
                *dd_ = 1;
                *mm_ = 3;
            }
            else if (*dd_ > 31 && (*mm_ == 1 || *mm_ == 3 || *mm_ == 5 || *mm_ == 7 || *mm_ == 8 || *mm_ == 10 || *mm_ == 12))
            {
                *dd_ = 1;
                *mm_ = *mm_ + 1;
            }
            else if (*dd_ > 30 && (*mm_ == 4 || *mm_ == 6 || *mm_ == 9 || *mm_ == 11))
            {
                *dd_ = 1;
                *mm_ = *mm_ + 1;
            }
            if (*mm_ > 12) {
                *yyyy_ = *yyyy_ + 1;
                *mm_ = 1;
            }
            Students[*tempInt].birthdate.DD = *dd_;
            Students[*tempInt].birthdate.MM = *mm_;
            Students[*tempInt].birthdate.YYYY = *yyyy_;
            delete dd_, mm_, yyyy_;
        }
        else
        {
            cout << "[!] Введённое значение не похоже на дату!" << endl;
            goto Continue4_4;
        }
        Continue4_5:
        cout << "Изменить год поступления (0 в случае, если не хотите менять): ";
        cin >> *tempShort;
        if (*tempStr == "-")
        {
            goto Continue4_6;
        }
        if (*tempShort < (Students[*tempInt].birthdate.YYYY + 7))
        {
            cout << "[!] Навряд ли этот человек такой вундеркинд, что смог поступить в институт до 7 лет!" << endl;
            goto Continue4_5;
        }
        Students[*tempInt].studyplace.EntranceYear = *tempShort;
        Continue4_6:
        cout << "Изменить институт/факультет (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_7;
        }
        if ((*tempStr).size() < 6)
        {
            strcpy_s(Students[*tempInt].studyplace.Faculty, 6, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Это не похоже на институт/факультет!" << endl;
            goto Continue4_6;
        }
        Continue4_7:
        cout << "Изменить кафедру (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_8;
        }
        if ((*tempStr).size() < 11)
        {
            strcpy_s(Students[*tempInt].studyplace.Department, 11, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Это не похоже на кафедру!" << endl;
            goto Continue4_7;
        }
        Continue4_8:
        cout << "Изменить группу студента (- в случае, если не хотите менять): ";
        cin >> *tempStr;
        if (*tempStr == "-")
        {
            goto Continue4_9;
        }
        if ((*tempStr).size() < 11)
        {
            strcpy_s(Students[*tempInt].studyplace.Group, 11, (*tempStr).c_str());
        }
        else
        {
            cout << "[!] Это не похоже на группу!" << endl;
            goto Continue4_8;
        }
        Continue4_9:
        cout << "[!] Смена пола - хреновая затея. Поэтому смена пола студента невозможна!" << endl;
        SaveStudents(Students, StudentsAmount);
        delete tempStr, tempShort, tempInt;
        goto RepeatMenuStudents;
    }
    else if (Action == "5")
    {
        string* tempStr = (string*) new string;
        int* tempInt = (int*) new int;
        short* tempShort = (short*) new short;

        cout << "========= Изменение успеваемости студента =========" << endl;
        Return5_0:
        cout << "Введите номер зачётной книжки студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() != 7)
        {
            cout << "[!] Это не похоже на зачётную книжку!" << endl;
            goto Return5_0;
        }
        for (int i = 0; i < *StudentsAmount; i++)
        {
            if (AreIDsEqual(Students[i].UniqueID, (*tempStr).c_str()) == 1)
            {
                *tempInt = i;
                goto Continue5_0;
            }
        }
        cout << "[!] Студент с номером зачётной книжки " << *tempStr << " не был найден!" << endl;
        goto RepeatMenuStudents;

        Continue5_0:
        cout << "Семестры студента:" << endl;
        for (int i = 0; i < 9; i++)
        {
            if (Students[*tempInt].grade.Terms[i].ProgramID > 0)
            {
                cout << "Семестр №" << i + 1 << " - учебный план №" << Students[*tempInt].grade.Terms[i].ProgramID << endl;

            }
            else
            {
                cout << "Для семестра №" << i + 1 << " учебный план не выбран!" << endl;
            }
            Return5_00:
            cout << "[?] Желаете выбрать № учебного плана для " << i + 1 << "-го семестра (-1 в случае, если не хотите менять, 0 для пустого плана): ";
            cin >> *tempShort;
            if (*tempShort == -1)
            {
                continue;
            }
            else if (*tempShort == 0)
            {
                Students[*tempInt].grade.Terms[i].ProgramID = 0;
                goto RepeatMenuStudents;
            }
            else
            {
                int ProgramID_ = IsStudyProgramExists(tempShort, Classes, ClassesAmount);
                if (ProgramID_ == -1)
                {
                    cout << "[!] Учебного плана с номером " << *tempInt << " не существует!" << endl;
                    goto Return5_00;
                }
                else
                {
                    Students[*tempInt].grade.Terms[i].ProgramID = *tempShort;
                    Return5_1:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject1 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[0] = *tempShort;
                    }
                    else
                    {
                        goto Return5_1;
                    }
                    Return5_2:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject2 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[1] = *tempShort;
                    }
                    else
                    {
                        goto Return5_2;
                    }
                    Return5_3:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject3 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[2] = *tempShort;
                    }
                    else
                    {
                        goto Return5_3;
                    }
                    Return5_4:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject4 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[3] = *tempShort;
                    }
                    else
                    {
                        goto Return5_4;
                    }
                    Return5_5:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject5 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[4] = *tempShort;
                    }
                    else
                    {
                        goto Return5_5;
                    }
                    Return5_6:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject6 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[5] = *tempShort;
                    }
                    else
                    {
                        goto Return5_6;
                    }
                    Return5_7:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject7 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[6] = *tempShort;
                    }
                    else
                    {
                        goto Return5_7;
                    }
                    Return5_8:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject8 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[7] = *tempShort;
                    }
                    else
                    {
                        goto Return5_8;
                    }
                    Return5_9:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject9 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[8] = *tempShort;
                    }
                    else
                    {
                        goto Return5_9;
                    }
                    Return5_10:
                    cout << "Введите оценку за предмет «" << Classes[ProgramID_].Subject10 << "»: ";
                    cin >> *tempShort;
                    if (*tempShort == 0 || *tempShort == 2 || *tempShort == 3 || *tempShort == 4 || *tempShort == 5)
                    {
                        Students[*tempInt].grade.Terms[i].Subjects[9] = *tempShort;
                    }
                    else
                    {
                        goto Return5_10;
                    }
                }
            }
        }
        SaveStudents(Students, StudentsAmount);
        delete tempStr, tempShort, tempInt;
        goto RepeatMenuStudents;
    }
    else if (Action == "6")
    {
        string* tempStr = (string*) new string;
        int* tempInt = (int*) new int;

        cout << "========= Удаление студента =========" << endl;
        Return6_0:
        cout << "Введите номер зачётной книжки студента: ";
        cin >> *tempStr;
        if ((*tempStr).size() != 7)
        {
            cout << "[!] Это не похоже на зачётную книжку!" << endl;
            goto Return6_0;
        }
        for (int i = 0; i < *StudentsAmount; i++)
        {
            if (AreIDsEqual(Students[i].UniqueID, (*tempStr).c_str()) == 1)
            {
                *tempInt = i;
                for (int z = *tempInt; z < (*StudentsAmount - 1); z++)
                {
                    Students[z] = Students[z + 1];
                }
                *StudentsAmount = *StudentsAmount - 1;
                Students = ResizeStudents(Students, *StudentsAmount);
                cout << "Студент успешно удалён!" << endl;
                SaveStudents(Students, StudentsAmount);
                delete tempStr, tempInt;
                goto RepeatMenuStudents;
            }
        }
        cout << "[!] Студент с номером зачётной книжки " << *tempStr << " не был найден!" << endl;
        delete tempStr, tempInt;
        goto RepeatMenuStudents;
    }
    else if (Action == "7")
    {
        short* tempShort = (short*) new short;
        string* tempStr = (string*) new string;
        short* tempShort2 = (short*) new short;

        system("cls");
        cout << "========= Отличники / Хорошисты / Троечники =========" << endl;
        cout << "Кого вы хотите вывести:\n1) отличников\n2) отличников и хорошистов\n3) хорошистов и троечников?" << endl;
        RepeatShowRealMen_0:
        cout << "Выберите категорию учеников: ";
        cin >> *tempStr;
        if (*tempStr == "1")
        {
            *tempShort = 5;
        }
        else if (*tempStr == "2")
        {
            *tempShort = 4;
        }
        else if (*tempStr == "3")
        {
            *tempShort = 3;
        }
        else
        {
            goto RepeatShowRealMen_0;
        }
        cout << "Выберите семестр (1-9): ";
        cin >> *tempShort2;

        for (int i = 0; i < *StudentsAmount; i++)
        {
            if ((Students[i].IsHeRealMen(tempShort2) == *tempShort) || (Students[i].IsHeRealMen(tempShort2) == (*tempShort + 1)))
            {
                Students[i].PrintShortInfo();
            }
        }
        goto RepeatMenuStudents;
    }
    else if (Action == "8")
    {
        system("cls");
    }
    else
    {
        goto RepeatMenuStudentsChoice;
    }

}

void MenuClasses(StudyProgram* Classes, int* ClassesAmount)
{
    string Action;

    system("cls");
    RepeatMenuClasses:
    cout << "========= МЕНЮ - учебные планы =========" << endl;
    cout << "Возможные действия:" << endl;
    cout << "1. Посмотреть учебные планы (кратко)" << endl;
    cout << "2. Добавить учебный план" << endl;
    cout << "3. Изменить учебный план" << endl;
    cout << "4. Назад" << endl;
    RepeatMenuClassesChoice:
    cout << "Выберите дейсвтие: ";
    cin >> Action;
    if (Action == "1")
    {
        system("cls");
        cout << "========= Список всех учебных планов =========" << endl;
        for (int i = 0; i < *ClassesAmount; i++)
        {
            cout << "[" << Classes[i].ProgramID << "] " << Classes[i].Subject1 << " / " << Classes[i].Subject2 << " / " << Classes[i].Subject3 << " / " << Classes[i].Subject4 << " / " << Classes[i].Subject5 << " /" << endl;
            cout << Classes[i].Subject6 << " / " << Classes[i].Subject7 << " / " << Classes[i].Subject8 << " / " << Classes[i].Subject9 << " / " << Classes[i].Subject10 << endl;
            if (i != *ClassesAmount - 1)
            {
                cout << "+---------+" << endl;
            }
        }
        goto RepeatMenuClasses;
    }
    else if (Action == "2")
    {
        short* tempShort = (short*) new short;
        string* tempString = (string*) new string;
        StudyProgram tempClass;

        cout << "========= Добавление учебного плана =========" << endl;
        RepeatC_0:
        cout << "Введите № учебного плана: ";
        cin >> *tempShort;
        for (int i = 0; i < *ClassesAmount; i++)
        {
            if (Classes[i].ProgramID == *tempShort)
            {
                cout << "[!] Учебный план с таким номером уже существует!" << endl;
                goto RepeatC_0;
            }
        }
        tempClass.ProgramID = *tempShort;
        RepeatC_1:
        cout << "Введите название первого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_1;
        }
        strcpy_s(tempClass.Subject1, 41, (*tempString).c_str());
        RepeatC_2:
        cout << "Введите название второго предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2;
        }
        strcpy_s(tempClass.Subject2, 41, (*tempString).c_str());
        RepeatC_3:
        cout << "Введите название третьего предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_3;
        }
        strcpy_s(tempClass.Subject3, 41, (*tempString).c_str());
        RepeatC_4:
        cout << "Введите название четвёртого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_4;
        }
        strcpy_s(tempClass.Subject4, 41, (*tempString).c_str());
        RepeatC_5:
        cout << "Введите название пятого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_5;
        }
        strcpy_s(tempClass.Subject5, 41, (*tempString).c_str());
        RepeatC_6:
        cout << "Введите название шестого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_6;
        }
        strcpy_s(tempClass.Subject6, 41, (*tempString).c_str());
        RepeatC_7:
        cout << "Введите название седьмого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_7;
        }
        strcpy_s(tempClass.Subject7, 41, (*tempString).c_str());
        RepeatC_8:
        cout << "Введите название восьмого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_8;
        }
        strcpy_s(tempClass.Subject8, 41, (*tempString).c_str());
        RepeatC_9:
        cout << "Введите название девятого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_9;
        }
        strcpy_s(tempClass.Subject9, 41, (*tempString).c_str());
        RepeatC_10:
        cout << "Введите название десятого предмета: ";
        cin >> *tempString;
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_10;
        }
        strcpy_s(tempClass.Subject10, 41, (*tempString).c_str());
        *ClassesAmount = *ClassesAmount + 1;
        Classes = ResizeClasses(Classes, *ClassesAmount);
        Classes[*ClassesAmount - 1] = tempClass;
        SaveClasses(Classes, ClassesAmount);
        cout << "Учебный план успешно добавлен!";
        goto RepeatMenuClasses;
    }
    else if (Action == "3")
    {
        short* tempShort = (short*) new short;
        string* tempString = (string*) new string;
        int* tempInt = (int*) new int;

        cout << "========= Изменение учебного плана =========" << endl;
        RepeatC_00:
        cout << "Введите № учебного плана, который желаете изменить: ";
        cin >> *tempShort;
        for (int i = 0; i < *ClassesAmount; i++)
        {
            if (Classes[i].ProgramID == *tempShort)
            {
                *tempInt = i;
                goto ContinueC_0;
            }
        }
        cout << "[!] Учебный план с номером " << *tempShort << " не был найден!" << endl;
        goto RepeatC_00;

        ContinueC_0:
        Classes[*tempInt].ProgramID = *tempShort;
        RepeatC_2_1:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject1 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_2;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_1;
        }
        strcpy_s(Classes[*tempInt].Subject1, 41, (*tempString).c_str());
        RepeatC_2_2:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject2 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_3;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_2;
        }
        strcpy_s(Classes[*tempInt].Subject2, 41, (*tempString).c_str());
        RepeatC_2_3:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject3 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_4;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_3;
        }
        strcpy_s(Classes[*tempInt].Subject3, 41, (*tempString).c_str());
        RepeatC_2_4:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject4 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_5;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_4;
        }
        strcpy_s(Classes[*tempInt].Subject4, 41, (*tempString).c_str());
        RepeatC_2_5:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject5 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_6;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_5;
        }
        strcpy_s(Classes[*tempInt].Subject5, 41, (*tempString).c_str());
        RepeatC_2_6:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject6 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_7;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_6;
        }
        strcpy_s(Classes[*tempInt].Subject6, 41, (*tempString).c_str());
        RepeatC_2_7:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject7 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_8;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_7;
        }
        strcpy_s(Classes[*tempInt].Subject7, 41, (*tempString).c_str());
        RepeatC_2_8:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject8 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_9;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_8;
        }
        strcpy_s(Classes[*tempInt].Subject8, 41, (*tempString).c_str());
        RepeatC_2_9:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject9 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_10;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_9;
        }
        strcpy_s(Classes[*tempInt].Subject9, 41, (*tempString).c_str());
        RepeatC_2_10:
        cout << "Хотите изменить предмет «" << Classes[*tempInt].Subject10 << "» (- в случае, если не хотите менять): ";
        cin >> *tempString;
        if (*tempString == "-")
        {
            goto RepeatC_2_11;
        }
        if ((*tempString).size() >= 41)
        {
            cout << "[!] Слишком длинное название предмета!" << endl;;
            goto RepeatC_2_10;
        }
        strcpy_s(Classes[*tempInt].Subject10, 41, (*tempString).c_str());
        RepeatC_2_11:
        SaveClasses(Classes, ClassesAmount);
        cout << "Учебный план №" << *tempInt << " успешно изменён!" << endl;
        delete tempString, tempShort, tempInt;
        goto RepeatMenuClasses;
    }
    else if (Action == "4") 
    {
        system("cls");
    }
    else
    {
        goto RepeatMenuClassesChoice;
    }
}

void MainMenu(Student* Students, int* StudentsAmount, StudyProgram* Classes, int* ClassesAmount)
{
    string Action;

    system("cls");
    RepeatMainMenu:
    cout << "========= ГЛАВНОЕ МЕНЮ =========" << endl;
    cout << "Возможные действия:" << endl;
    cout << "1. Студенты" << endl;
    cout << "2. Учебные планы" << endl;
    cout << "3. Выход из программы" << endl;
    RepeatMainMenuChoice:
    cout << "Выберите действие: ";
    cin >> Action;
    if (Action == "1")
    {
        MenuStudents(Students, StudentsAmount, Classes, ClassesAmount);
        goto RepeatMainMenu;
    }
    else if (Action == "2")
    {
        MenuClasses(Classes, ClassesAmount);
        goto RepeatMainMenu;
    }
    else if (Action == "3")
    {
        system("cls");
    }
    else
    {
        goto RepeatMainMenuChoice;
    }
}

void Decrypt()
{
    cout << "========= Загрузка программы =========" << endl;
    cout << "Пожалуйста, подождите..." << endl;
    string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in Password.safin -out Password.bin";
    system(command.c_str());
    if (remove("Password.safin") != 0) {
        cout << "[!] Ошибка удаления зашифрованного пароля для дешифрования базы данных!" << endl;
    }
    char* pass = new char[64];
    ifstream InputFile;
    InputFile.open("Password.bin", ios::binary);
    InputFile.read(pass, 65);
    InputFile.close();
    if (remove("Password.bin") != 0) {
        cout << "[!] Ошибка удаления пароля для дешифрования базы данных!" << endl;
    }
    command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in Students.safin -out Students.bin -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("Students.safin") != 0) {
        cout << "[!] Ошибка удаления зашифрованной базы данных!" << endl;
    }
}

void Crypt()
{
    srand(time(NULL));
    char* pass = new char[64];
    for (int i = 0; i < 64; ++i) {
        switch (rand() % 3) {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
        }
    }
    string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in Students.bin -out Students.safin -pass pass:";
    command += pass;
    system(command.c_str());
    if (remove("Students.bin") != 0)
    {

        cout << "[!] Ошибка удаления НЕзашифрованной базы данных!" << endl;
    }
    ofstream OutputForPSWD;
    OutputForPSWD.open("Password.bin", ios::binary);
    OutputForPSWD << pass;
    OutputForPSWD.close();
    command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in Password.bin -out Password.safin";
    system(command.c_str());
    if (remove("Password.bin") != 0)
    {
        cout << "[!] Ошибка удаление пароля для шифрования базы данных!" << endl;
    }
}

int main()
{
    // Локализация терминала
    // setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    
    // Учебные программы
    StudyProgram* Classes = (StudyProgram*) new StudyProgram[0];

    string tempStr2;
    ifstream InputClasses;
    InputClasses.open("Classes.bin", ios::binary);
    int c = 0;
    while (!InputClasses.eof())
    {
        Classes = ResizeClasses(Classes, c + 1); // Увеличиваем массив

        InputClasses >> Classes[c].ProgramID;
        
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject1, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject2, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject3, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject4, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject5, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject6, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject7, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject8, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject9, tempStr2.c_str());
        InputClasses >> tempStr2;
        if (tempStr2.size() > 40)
        {
            tempStr2 = "Предмет_не_распознан";
        }
        strcpy_s(Classes[c].Subject10, tempStr2.c_str());

        c++;
    }
    InputClasses.close();

    // Дешифровка базы данных
    Decrypt();

    // СТУДЕНТЫ - объявление, считывание из файла
    Student* Students = new Student[0];

    string tempStr;
    short tempShort;
    ifstream InputStudents;
    InputStudents.open("Students.bin", ios::binary);
    int s = 0;
    while (!InputStudents.eof())
    {
        Students = ResizeStudents(Students, s + 1); // Увеличиваем массив

        InputStudents >> tempStr;
        if (tempStr.size() > 7)
        {
            tempStr = "Ошибка";
        }
        strcpy_s(Students[s].UniqueID, tempStr.c_str());

        InputStudents >> tempStr;
        if (tempStr.size() > 19)
        {
            tempStr = "Ошибка_фамилии";
        }
        strcpy_s(Students[s].initials.Surname, tempStr.c_str());
        InputStudents >> tempStr;
        if (tempStr.size() > 19)
        {
            tempStr = "Ошибка_имени";
        }
        strcpy_s(Students[s].initials.Name, tempStr.c_str());
        InputStudents >> tempStr;
        if (tempStr.size() > 19)
        {
            tempStr = "Ошибка_отчества";
        }
        strcpy_s(Students[s].initials.Patronymic, tempStr.c_str());

        InputStudents >> tempShort;
        if ((tempShort < 1) || (tempShort > 31))
        {
            tempShort = 1;
        }
        Students[s].birthdate.DD = tempShort;
        InputStudents >> tempShort;
        if ((tempShort < 1) || (tempShort > 12))
        {
            tempShort = 1;
        }
        Students[s].birthdate.MM = tempShort;
        InputStudents >> tempShort;
        if (tempShort < 1900)
        {
            tempShort = 2000;
        }
        Students[s].birthdate.YYYY = tempShort;


        InputStudents >> tempShort;
        if (tempShort < 1918)
        {
            tempShort = 1918;
        }
        Students[s].studyplace.EntranceYear = tempShort;
        InputStudents >> tempStr;
        if (tempStr.size() > 5)
        {
            tempStr = "ИКБ";
        }
        strcpy_s(Students[s].studyplace.Faculty, tempStr.c_str());
        InputStudents >> tempStr;
        if (tempStr.size() > 10)
        {
            tempStr = "КБ-1";
        }
        strcpy_s(Students[s].studyplace.Department, tempStr.c_str());
        InputStudents >> tempStr;
        if (tempStr.size() != 10)
        {
            tempStr = "БАСО-02-22";
        }
        strcpy_s(Students[s].studyplace.Group, tempStr.c_str());


        InputStudents >> tempShort;
        if ((tempShort < 0) || (tempShort > 1))
        {
            tempShort = 1;
        }
        Students[s].sex = tempShort;

        for (int i = 0; i < 9; i++)
        {
            InputStudents >> Students[s].grade.Terms[i].ProgramID;
            for (int z = 0; z < 10; z++)
            {
                InputStudents >> Students[s].grade.Terms[i].Subjects[z];
            }
        }
        // Students[s].PrintInfo(Classes, &c); <-- проверяем, что всё точно работает)))
        s++;
    }
    InputStudents.close();

    MainMenu(Students, &s, Classes, &c);

    system("cls");
    cout << "========= Завершение программы =========" << endl;

    // Шифруем базу данных от злоумышленников-студентов
    Crypt();
    cout << "[?] На текст на английском языке не обращайте внимание!)" << endl;

    return 0;
}