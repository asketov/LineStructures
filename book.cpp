#include <iostream>
 
struct DataType
{
    double coef, degree;
};
 
class IBaseClass //абстрактный базовый класс:интерфейс
{
public:
    bool virtual EnQueue(DataType info) = 0;
    DataType virtual DeQueue(void) = 0;
};
 
class Connected : public IBaseClass //связная структура хранения
{
private:
    struct element
    {
        DataType data;
        element* next;
    } *front, * rear; //индексы головы и хвоста
public:
    Connected() { front = rear = NULL; } //конструктор
    ~Connected() //деструктор
    {
        element* temp;
        while (front)
        {
            temp = front;
            front = front->next;
            delete temp;
        }
    }
    bool EnQueue(DataType info) override /*перераспределение виртуальной функции добавления элемента в структуру хранения*/
    {
        element* temp = new element;
        if (temp == NULL) return 1;
        temp->data = info;
        temp->next = NULL;
        if (front == NULL)
            front = rear = temp;
        else
        {
            rear->next = temp;
            rear = rear->next;
        }
        return 1;
    }
 
    DataType DeQueue(void) override /*перераспределение виртуальной функции чтения элемента из структуры хранения*/
    {
        DataType temp = front->data;
        element* tmp = front;
        front = front->next;
        delete tmp;
        return temp;
    }
 
 
};
 
class vector : public IBaseClass //векторная структура хранения
{
private:
    int front, rear; //индексы головы и хвоста
    int maxlength;  //размер массива
    DataType* data; //массив для хранения элементов
public:
    vector(int n) : maxlength(n) //конструктор
    {
        data = new DataType[maxlength];
        front = 0;
        rear = maxlength - 1;
    }
    ~vector() //деструктор
    {
        delete[] data;
    }
    bool EnQueue(DataType info) override /*перераспределение виртуальной функции добавления элемента в структуру хранения*/
    {
        rear = (rear + 1) % maxlength;
        data[rear] = info;
        return 1;
    }
    DataType DeQueue(void) override /*перераспределение виртуальной функции чтения элемента из структуры хранения*/
    {
        int temp = front;
        front = (front + 1) % maxlength;
        return data[temp];
    }
};
 
using namespace std;
void create_mnogochlen(int n, IBaseClass& structure);
void difference_of_polynomials(IBaseClass& structure1, IBaseClass& structure2, int n1, int n2);
 
int main()
{
    setlocale(LC_ALL, "Russian");
    char choise;
    int n1, n2, i = 1;
    cout << "Выберите структуру хранения:" << endl << "1. Векторная" << endl << "2. Связная" << endl;
    choise = getchar();
    system("cls");
    if (choise == '1')
    {
        cout << "Введите количество членов первого многочлена:";
        cin >> n1;
        class vector Vector(n1);
        create_mnogochlen(n1, Vector);
        cout << "Введите количество членов второго многочлена:";
        cin >> n2;
        class vector Vector1(n2);
        create_mnogochlen(n2, Vector1);
        difference_of_polynomials(Vector, Vector1, n1, n2);
       
    }
    else if (choise == '2')
    {
        class Connected first, second;
        cout << "Введите количество членов первого многочлена:";
        cin >> n1;
        create_mnogochlen(n1, first);
        cout << "Введите количество членов второго многочлена:";
        cin >> n2;
        create_mnogochlen(n2, second);
        difference_of_polynomials(first, second, n1, n2);
        
 
    }
    else { cout << "Цифра введена неверно, повторите попытку"; }
    return 0;
}
 
void create_mnogochlen(int n, IBaseClass& structure) //функция создания многочлена
{
    int i = 1;
    while (i <= n)
    {
        DataType Info;
        cout << "Введите с" << i << ":";
        cin >> Info.coef;
        cout << "Введите e" << i << ":";
        cin >> Info.degree;
        structure.EnQueue(Info);
        i++;
    }
}
void difference_of_polynomials(IBaseClass& structure1, IBaseClass& structure2, int n1, int n2) //функция разности многочленов
{
    DataType first_p, second_p;
    if (n1 > n2)
    {
        while (n1 != n2)
        {
            first_p = structure1.DeQueue();
            cout << first_p.coef << "*x^" << first_p.degree << "+";
            n1--;
        }
        while (n1 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n1 != 1) 
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree << "+";
            }
            else
            {
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n1--;
        }
    }
    else if (n2 > n1)
    {
        while (n2 != n1)
        {
            second_p = structure2.DeQueue();
            cout << -second_p.coef << "*x^" << second_p.degree;
            n2--;
        }
        cout << "+";
        while (n2 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n2 != 1)
            {
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree << "+";
            }
            else
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n2--;
        }
    }
    else if (n1 == n2)
    {
        while (n1 != 0)
        {
            first_p = structure1.DeQueue();
            second_p = structure2.DeQueue();
            if (n1 != 1)
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree << "+";
                }
                else cout << first_p.coef - second_p.coef  << "*x^" << first_p.degree << "+";
            }
            else 
            { 
                if ((first_p.coef - second_p.coef) < 0)
                {
                    cout << "(" << first_p.coef - second_p.coef << ")" << "*x^" << first_p.degree;
                }
                else cout << first_p.coef - second_p.coef << "*x^" << first_p.degree;
            }
            n1--;
        }
    }
}
