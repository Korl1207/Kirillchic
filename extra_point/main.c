#include <stdio.h>

#define MAX_EXPENSES 1000 // Максимальное количество расходов, которые можем сохранить

// Структура для одного расхода
struct Expense
{
    char date[11];
    char category[30];
    float amount;
};

// Глобальный массив для хранения всех расходов
struct Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// --- Функция для загрузки расходов из файла ---
void loadExpenses(const char *filename)
{
    FILE *input = fopen(filename, "r");

    if (!input)
    {
        return;
    }

    while (fscanf(input, "%11s %30s %f", expenses[expenseCount].date, expenses[expenseCount].category, &expenses[expenseCount].amount) == 3)
    {
        ++expenseCount;
    }
    fclose(input);
}

// --- Функция для сохранения одного расхода в файл ---
void saveExpenseToFile(const char *filename, struct Expense e)
{
    FILE *output = fopen(filename, "r");

    if (!output)
    {
        printf("Ошибка при сохранении файла!\n");
    }
    fprintf(output, "%s %s %.2f", e.date, e.category, e.amount);

    fclose(output);
}

// --- Функция для добавления нового расхода ---
void addExpence()
{
    if (expenseCount >= MAX_EXPENSES)
    {
        printf("Превышен лимит расходов!\n");
    }

    struct Expense e;

    printf("Введите дату (дд.мм.гггг): ");
    scanf("%11s", e.date);

    printf("Введите категорию: ");
    scanf("%30s", e.category);

    printf("Введите сумму: ");
    scanf("%f", &e.amount);

    expenses[expenseCount++] = e;

    printf("Расход добавлен!\n");
}

// --- Функция для отображения всех расходов ---
void showAllExpenses()
{
    if (expenseCount == 0)
    {
        printf("Нет данных о расходах.\n");
        return;
    }

    // Заголовок таблицы
    printf("\n--- Все расходы ---\n");
    printf("Дата        Категория      Сумма\n");
    printf("------------------------------\n");

    // Выводим каждую запись
    int i;
    for (i = 0; i < expenseCount; ++i)
    {
        printf("%-12s%-15s%.2f руб.\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}

// --- Функция для вывода статистики ---
void showStats()
{
    if (expenseCount == 0)
    {
        printf("Нет данных для анализа.\n");
        return;
    }

    float total = 0;                // Общая сумма
    float max = expenses[0].amount; // Самая большая трата

    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;

        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount; // Среднее значение

    // Вывод
    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата: %.2f руб.\n", average);
    printf("Максимальная трата: %.2f руб\n", max);
}

// --- Функция для отображения меню пользователя ---
void showMenu()
{
    printf("\n=== Трекер расходов ===\n");
    printf("1. Добавить расход\n");
    printf("2. Показать все расходы\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт: ");
}

// --- Главная функция программы ---
int main()
{
    loadExpenses("expenses.txt"); // Загрузка данных из файла

    int choice;

    // Основной цикл
    printf("ok");
    do
    {
        showMenu(); // Показываем меню
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addExpence();
            break;
        case 2:
            showAllExpenses();
            break;
        case 3:
            showStats();
            break;
        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор.\n");
        }
    } while (choice != 4);

    return 0;
}