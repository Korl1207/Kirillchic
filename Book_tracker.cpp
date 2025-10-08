#include <iostream>

using namespace std;

#define NAMEL 100
#define AUTHORL 50
#define BD "books.txt"

// Кортеж книги
struct Book
{
    char name[NAMEL];
    char author[AUTHORL];
    int yread;
    float grade;
};

// Массив из книг
Book books[1000];
int s = 0;
int s_prev = 0;

// Прочтение строки из потока
void read_str(FILE *file, char *str, int lim)
{
    char c;
    int ind = 0;
    c = getc(file);
    while (c != ';' && c != '\n' && c != EOF && ind < lim)
    {
        str[ind] = c;
        ++ind;
        c = getc(file);
    }
}

// Прочтение числа из потока
void read_int(FILE *file, int *n)
{
    *n = 0;
    char c;
    c = getc(file);
    while (c != ';' && c != '\n' && c != EOF)
    {
        *n = (*n) * 10;
        *n = (*n) + (c - '0');
        c = getc(file);
    }
}

// Прочтение дробного числа через точку из потока
void read_float(FILE *file, float *f)
{
    char c;
    c = getc(file);
    bool dot = false;
    float k = 1;
    while (c != ';' && c != '\n' && c != EOF)
    {
        if (c == '.')
        {
            dot = true;
        }
        else
        {
            if (!dot)
            {
                *f *= 10;
                *f += (c - '0');
            }
            else
            {
                k *= 0.1;
                *f += (c - '0') * k;
            }
        }
        c = getc(file);
    }
}

// Считывание файла BD
int read_txt()
{
    FILE *file = fopen(BD, "r");
    if (!file)
    {
        return 1;
    }
    char c;
    while ((c = getc(file)) != EOF)
    {
        ungetc(c, file);
        read_str(file, books[s].name, NAMEL);
        read_str(file, books[s].author, AUTHORL);
        read_int(file, &books[s].yread);
        read_float(file, &books[s].grade);
        ++s;
    }
    fclose(file);
    s_prev = s;
    return 0;
}

// Запись изменений в файл
int write_txt()
{
    FILE *file = fopen(BD, "a");
    if (!file)
    {
        return 1;
    }

    for (int i = s_prev; i < s; i++)
    {
        fprintf(file, "%s;%s;%d%f\n", books[i].name, books[i].author, books[i].yread, books[i].grade);
    }
    fclose(file);
    return 0;
}
// Вывод книг по команде 1
void print_all()
{
    if (s == 0)
    {
        cout << "Список пуст" << endl;
        return;
    }
    cout << "Название : Автор : Год прочтения : Оценка" << endl;
    for (int i = 0; i < s; i++)
    {
        cout << books[i].name << '\t' << books[i].author << '\t' << books[i].yread << '\t' << books[i].grade << endl;
    }
}

// Добавить книгу по команде 2
void add_book()
{
    cout << "Введите название книги: ";
    cin >> books[s].name;
    cout << "Введите автора: ";
    cin >> books[s].author;
    cout << "Введите год прочтения: ";
    cin >> books[s].yread;
    cout << "Введите оценку (0-10): ";
    cin >> books[s].grade;
    ++s;
}

// Вывести статистику по команде 3
void show_stat()
{
    printf("Прочитано книг: %d\n", s);
    float sum = 0;
    int max_ind = 0;
    for (int i = 0; i < s; i++)
    {
        sum += books[i].grade;
        if (books[max_ind].grade < books[i].grade)
        {
            max_ind = i;
        }
    }
    printf("Средняя оценка: %f\n", sum / s);
    printf("Самая высоко оцененная книга: %s\n Автор: %s\n Год прочтения: %d\n Оценка: %.1f\n", books[max_ind].name, books[max_ind].author, books[max_ind].yread, books[max_ind].grade);
}

// Редактор книг
void run()
{
    cout << "====== Трекер книг =====" << endl;
    cout << "1. Вывести книги" << endl;
    cout << "2. Добавить книгу" << endl;
    cout << "3. Показать статистику" << endl;
    cout << "4. Выход" << endl;
    int c;
    while (true)
    {
        cout << "Введите номер команды: ";
        cin >> c;
        switch (c)
        {
        case 1:
            print_all();
            break;
        case 2:
            add_book();
            break;
        case 3:
            show_stat();
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}

int main()
{
    // Обработка открытия файла
    if (read_txt())
    {
        cerr << "Не удалось открыть файл для чтения" << endl;
        return 1;
    }
    run();
    // Обработка закрытия файла
    if (write_txt())
    {
        cerr << "Не удалось открыть файл для записи, изменения не сохранены" << endl;
    }
}