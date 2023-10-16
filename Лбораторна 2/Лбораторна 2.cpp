#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <locale>



using namespace std;

class Ingredient {
private:
    string name;
    double quantity;
    double pricePerUnit;

public:
    Ingredient(string n, double q, double price) : name(n), quantity(q), pricePerUnit(price) {}

    string getName() {
        return name;
    }

    double getQuantity() {
        return quantity;
    }

    double getPricePerUnit() {
        return pricePerUnit;
    }

    void show() {
        cout << "Інгредієнт: " << name << endl;
        cout << "Дозування: " << quantity << endl;
        cout << "Ціна за одиницю: " << pricePerUnit << endl;
    }

    double getCost() {
        return quantity * pricePerUnit;
    }
};

class Recipe {
private:
    string name;
    vector<Ingredient> ingredients;

public:
    Recipe(string n) : name(n) {}

    void set(string n) {
        name = n;
        ingredients.clear();
    }

    void addIngredient(Ingredient ingredient) {
        ingredients.push_back(ingredient);
    }

    string getName() {
        return name;
    }

    void show() {
        cout << "Рецепт: " << name << endl;
        cout << "Інгредієнти:" << endl;
        for (Ingredient ingredient : ingredients) {
            ingredient.show();
        }
    }

    double getCost() {
        double totalCost = 0.0;
        for (Ingredient ingredient : ingredients) {
            totalCost += ingredient.getCost();
        }
        return totalCost;
    }

    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Помилка відкриття файлу для запису" << endl;
            return;
        }
        outFile << "Рецепт: " << name << endl;
        outFile << "Інгредієнти:" << endl;
        for (Ingredient ingredient : ingredients) {
            outFile << "Інгредієнт: " << ingredient.getName() << endl;
            outFile << "Дозування: " << ingredient.getQuantity() << endl;
            outFile << "Ціна за одиницю: " << ingredient.getPricePerUnit() << endl;
        }
        outFile.close();
    }



    void loadFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Помилка відкриття файлу для читання" << endl;
            return;
        }

        set("");

        string line;
        while (getline(inFile, line)) {
            if (line.find("Рецепт: ") == 0) {
                set(line.substr(8));
            }
            else if (line.find("Інгредієнт: ") == 0) {
                string name = line.substr(12);
                getline(inFile, line);
                if (line.find("Дозування: ") == 0) {
                    double quantity = stod(line.substr(12));
                    getline(inFile, line);
                    if (line.find("Ціна за одиницю: ") == 0) {
                        double price = stod(line.substr(19));
                        Ingredient ingredient(name, quantity, price);
                        addIngredient(ingredient);
                    }
                }
            }
        }

        inFile.close();
    }



};

int main() {
    setlocale(LC_ALL, "Ukrainian");
    Ingredient ingredient1("Спагеті", 250, 1.5);
    Ingredient ingredient2("Томатний соус", 300, 2.0);
    Ingredient ingredient3("М'ясні кульки", 12, 5.0);

    Recipe spaghetti("Спагеті");
    spaghetti.addIngredient(ingredient1);
    spaghetti.addIngredient(ingredient2);
    spaghetti.addIngredient(ingredient3);

    spaghetti.show();
    cout << "Загальна вартість спагеті: " << spaghetti.getCost() << endl;

    spaghetti.saveToFile("recipe.txt");
    Recipe loadedRecipe("Новий рецепт");
    loadedRecipe.loadFromFile("recipe.txt");
    loadedRecipe.show();

    return 0;
}