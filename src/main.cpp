#include <iostream>
using namespace std;
#include <vector>

enum Status {
    BORROWED,
    AVAILABLE,
    UNAVAILABLE
};

class Item {
public:
    string id;
    string name;
    Status status;
    string responsibleId; // id da pessoa responsável por esse item (pode ser a propria biblioteca id = "0")

    Item(string n, Status s, string ir, string i) {
        name = n;
        id = i;
        status = s;
        responsibleId = ir;
    }
};

class Person {
public:
    string name;
    string id;

    Person(string n, string i) {
        name = n;
        id = i;
    }
};

class LibraryRepository {
public:
    string id = "001";
    vector<Item> items;
    vector<Person> users;

    /*
    virtual void addItem(Item item) = 0;
    virtual void removeItem(Item item) = 0;
    virtual void updateItem(Item item) = 0;
    virtual Item findItemByName(string name) = 0;
    */

    void listItems() {
        cout << "LISTANDO ITEMS \n";
        for (int c = 0; c < items.size(); c++) {
            cout << "NOME: " << items[c].name
                 << ", STATUS: " << items[c].status
                 << ", ID DO RESPONSÁVEL: " << items[c].responsibleId;
            cout << "\n";
        }
        cout << "\n\n";
    }

    void listUsers() {
        cout << "LISTANDO USUÁRIOS: \n";
        for (int c = 0; c < users.size(); c++) {
            cout << "NOME: " << users[c].name
                 << ", ID: " << users[c].id;
            cout << "\n";
        }
    }


    void lendItem(string  idPerson, string idItem , int days) {
        bool userExists = false;
        bool itemExists = false;

        int userIndex = 0;
        int itemIndex = 0;
        
        for(int d = 0 ; d <users.size() ; d++){
            if(users[d].id == idPerson) {
                userExists = true;
                userIndex = d;
                break;
            }
        }

        if(userExists = false){
            cout << "Erro: usuário com ID " << idPerson << " não encontrado no sistema.\n\n";
            return;
        }

        for(int c = 0 ; c < items.size(); c++){
            if(items[c].id == idItem){
                itemIndex = true;
                itemIndex = c;
                break;
            }
        }

        if(itemExists = false){
            cout << "Erro: item com ID " << idItem << " não encontrado no sistema.\n\n";
            return;
        }

        if (items[itemIndex].status != AVAILABLE) {
            cout << "Erro: o item " << items[itemIndex].name 
             << " nao esta disponivel para emprestimo. ";
            if (items[itemIndex].status == BORROWED) {
                cout << "Ja esta emprestado \n\n";
            } else {
                cout << "Status: INDISPONIVEL\n\n";
            }
            return;
        }

        items[itemIndex].responsibleId = users[userIndex].id;
        items[itemIndex].status = BORROWED;
        cout << "Sucesso: item " << items[itemIndex].name << items[itemIndex].id << " emprestado a " << users[userIndex].name << " por " << days << " dias.\n\n";
    }
    
    void returnItem(string idPerson, string idItem, int days) {
        bool userExists  = false; // Ver se existem antes de executar
        bool itemExists = false; // Falta implementar !!!
    
        int userIndex = 0;
        int itemIndex = 0;

        for(int d = 0 ; d < users.size(); d++){
            if(users[d].id == idPerson){
                userExists = true;
                userIndex = d;
                break;
            }
        }

        if(userExists = false){
            cout << "Erro na devolução: usuário com ID " << idPerson << " não cadastrado.\n\n";
            return;
        }

        for(int c = 0 ; c < items.size(); c++){
            if(items[c].id == idItem){
                itemExists = true;
                itemIndex = c;
                break;
            }
        }

        if(itemExists = false){
            cout << "Erro na devolução: item com ID " << idItem << "não cadastrado.\n\n";
            return;
        }

        if(items[itemIndex].status != BORROWED){
            cout << "Erro na devolução: item " << items[itemIndex].name << "não consta como emprestado no sistema.\n\n";
            return;
        }

        if(items[itemIndex].responsibleId != idPerson){
            cout << "Erro na devolução: O usuario " << users[userIndex].name << "tentou devolver o item " << items[itemIndex].name << " que foi pego emprestado por outro usuario \n\n";
            return;
        }
        
        items[itemIndex].responsibleId = "0";
        items[itemIndex].status = AVAILABLE;
        cout << "Sucesso: item " << items[itemIndex].name << "devolvido com sucesso por" << users[userIndex].name << "\n\n";
    }
};

int main() {
    vector<Item> items = {
        Item("Dom Casmurro", AVAILABLE, "0", "100"),
        Item("Dom Casmurro", AVAILABLE, "0", "101"),
        Item("Dom Casmurro", UNAVAILABLE, "0", "102"),
        Item("1984", AVAILABLE, "0", "200"),
        Item("1984", UNAVAILABLE, "0", "201"),
        Item("The Hobbit", AVAILABLE, "0", "300"),
        Item("Clean Code", AVAILABLE, "0", "401"),
        Item("Clean Code", UNAVAILABLE, "0", "402"),
        Item("Clean Code", AVAILABLE, "0", "403"),
        Item("Clean Code", AVAILABLE, "0", "404"),
        Item("Clean Code", AVAILABLE, "0", "405"),
        Item("Animal Farm", UNAVAILABLE, "0", "500")
    };

    vector<Person> users = {
        Person("Ana", "002"),
        Person("João", "003"),
        Person("Maria", "004"),
        Person("Pedro", "005")
    };

    LibraryRepository library;
    library.items = items;
    library.users = users;
    
    library.listUsers();
    cout << "\n\n";
    library.listItems();
    
    library.lendItem("002", "100", 20);
    library.lendItem("003", "100", 20); // Já emprestado
    library.lendItem("003", "101", 20); // Emprestando outra cópia

    library.listUsers();
    cout << "\n\n";
    library.listItems();

    library.returnItem("002", "100", 20);
    library.returnItem("002", "100", 20);


    return 0;
}
