#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

int main()
{
    //Criando a tabela de dispersao
    HashTable hashTable(100); //Tamanho da tabela de dispersao e 100

    //Adicionando 20 palavras à tabela de dispersao
    hashTable.addText("apple");
    hashTable.addText("orange");
    hashTable.addText("banana");
    hashTable.addText("grape");
    hashTable.addText("cherry");
    hashTable.addText("peach");
    hashTable.addText("mango");
    hashTable.addText("apricot");
    hashTable.addText("plum");
    hashTable.addText("date");
    hashTable.addText("fig");
    hashTable.addText("kiwi");
    hashTable.addText("melon");
    hashTable.addText("lime");
    hashTable.addText("nectarine");
    hashTable.addText("tangerine");
    hashTable.addText("pear");
    hashTable.addText("quince");
    hashTable.addText("raspberry");
    hashTable.addText("coconut");

    //Contando a quantidade de ocorrencias das palavras
    cout << "Quantidade de 'apple': " << hashTable.countWord("apple") << endl;
    cout << "Quantidade de 'orange': " << hashTable.countWord("orange") << endl;
    cout << "Quantidade de 'banana': " << hashTable.countWord("banana") << endl;
    cout << "Quantidade de 'grape': " << hashTable.countWord("grape") << endl;
    cout << "Quantidade de 'cherry': " << hashTable.countWord("cherry") << endl;

    //Verificando se uma palavra esta na tabela
    if (hashTable.containsWord("peach"))
    {
        cout << "'peach' esta presente na tabela." << endl;
    }
    else
    {
        cout << "'peach' nao esta presente na tabela." << endl;
    }

    //Removendo uma palavra da tabela
    hashTable.removeWord("date");
    if (!hashTable.containsWord("date"))
    {
        cout << "'date' foi removida da tabela." << endl;
    }

    //Imprimindo todo o conteúdo da tabela
    hashTable.printTable();

    return 0;

    //O MAIN ABAIXO HAVIA SIDO FEITO POR MIM, ANTERIORMENTE.
    //NÃO QUIS PERDÊ-LO, ENTÃO DEIXEI-O AQUI EMBAIXO. O PROFESSOR PODE USÁ-LO TAMBÉM, SE QUISER.
    
    /*
    HashTable hashTable(100);

    int op = 0;
    while (op != 7)
    {
        //Demanda-se a opção desejada ao usuário
        cout << "Digite a opção desejada.\n";
        cout << "1 - Adicionar Texto\n";
        cout << "2 - Contar Palavra\n";
        cout << "3 - Atualizar Palavra\n";
        cout << "4 - Remover Palavra\n";
        cout << "5 - Verificar Palavra\n";
        cout << "6 - Imprimir Conteúdo\n";
        cout << "7 - Sair\n";
        cin >> op;
        cin.ignore();

        if (op == 1)
        {
            string txt_ad;
            cout << "Digite o texto a ser adicionado.\n";
            getline(cin, txt_ad);
            hashTable.addText(txt_ad);
        }
        else if (op == 2)
        {
            string word;
            cout << "Digite palavra a ser contada.\n";
            getline(cin, word);
            cout << "A palavra tem " << hashTable.countWord(word) << " ocorrências.\n";
        }
        else if (op == 3)
        {
            string word;
            int qt;
            cout << "Digite palavra a ser atualizada.\n";
            getline(cin, word);
            cout << "Digite seu novo número.\n";
            cin >> qt;
            hashTable.updateWord(word, qt);
        }
        else if (op == 4)
        {
            string word;
            cout << "Digite palavra a ser removida.\n";
            getline(cin, word);
            hashTable.removeWord(word);           
        }
        else if (op == 5)
        {
            string word;
            cout << "Digite palavra a ser verificada.\n";
            getline(cin, word);
            if (hashTable.containsWord(word))
            {
                cout << "A palavra está na lista.\n";
            }
            else
            {
                cout << "A palavra não está na lista.\n";
            }
        }
        else if (op == 6)
        {
            hashTable.printTable();
        }
        else if (op == 7)
        {
            break;
        }
    }
    return 0;
    */
}