// Вариант 24, Соваренко Максим Васильевич
/*
В отличие от 4ой лабы, здесь я не стал отдельно объявлять копирование и
перемещение (так как это не сказано в условии 5ой лабы), а также
уже объяснил в ней (4ой лабе), что их отдельная реализация не нужна
*/

#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <functional>
#include <unordered_set>
using namespace std;

// Объявление класса кредит
class Credit{
    private:
        string name;
        double amount;
        string currency;
        double rate;

    public:
    Credit() {
        name = "Пусто";
        amount = 0;
        currency = "Никакой";
        rate = 0;
    };
    Credit(string n, double a, string c, double r)
    : name(n), amount(a), currency(c), rate(r){};

    double getRate() const {
        return rate;
    }

    // Перегрузки операторов сравнения, вывода и равенства
    friend bool operator<(const Credit& c1, const Credit& c2) {
        return c1.rate < c2.rate;
    }
    friend ostream& operator<<(ostream& out, const Credit& c) {
        out << c.name << " ";
        out << c.amount << " ";
        out << c.currency << " ";
        out << c.rate << " ";
        return out;
    }
    friend bool operator==(const Credit& c1, const Credit& c2) {
        return c1.rate == c2.rate;
    }
};

// Хеширование по процентной ставке при помощи std::hash<double>
struct CreditHash {
    size_t operator()(const Credit& c) const {
        double rate = c.getRate();
        hash<double> h;
        return h(rate);
    }
};

int main() {
    set<Credit> credits;
    unordered_set<Credit, CreditHash> unordered_credits;

    ifstream in("input.txt");
    if (!in.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 1;
    }

    string n,c;
    double a,r;

    while (in >> n >> a >> c >> r) {
        credits.insert(Credit(n,a,c,r));
        unordered_credits.insert(Credit(n,a,c,r));
    }
    in.close();

    cout << "Кредиты по процентной ставке:" << endl;
    for (const Credit& c : credits) {
        cout << c << endl;
    }

    cout << "Кредиты в unordered_set:" << endl;
    for (const Credit& c : unordered_credits) {
        cout << c << endl;
    }

    return 0;
}
