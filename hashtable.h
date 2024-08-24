#include <iostream>
#include <list>
#include <string>
#include <vector>

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

//Cada elemento da lista encadeada – a palavra, e sua contagem.
class Node
{
    public:
        string word;
        int count;
        //Construtor padrão
        Node()
        {
            word = "\0";
            count = 0;
        }
        //Construtor parametrizado
        Node(string x, int y)
        {
            word = x;
            count = y;
        }
        //Destrutor
        ~Node()
        {

        }
};

//Classe da tabela de dispersão
class HashTable
{
    public:
        //Vetor de "texto", para ler as entradas
        vector<string> words;
        //Quantidade de "baldes" na tabela
        int n;
        //Tabela de dispersão em si – um vetor de listas encadeadas.
        vector<list<Node>> hashmap;
        
        //Construtor padrão
        HashTable()
        {

        }
        //Construtor parametrizado
        HashTable(int x)
        {
            n = x;
            for (int i = 0; i < x; i++)
            {
                hashmap.push_back({Node()});
            }
        }
        //Destrutor  
        ~HashTable()
        {

        }
        //Adicionar textos
        void addText(string text)
        {
            int i = 0;
            //Laço para separação dos termos do texto
            //A string é quebrada e suas palavras são inseridas no vetor de texto
            while (i < static_cast<int>(text.length()))
            {
                if (text[i] != ' ' && text[i] != '\n')
                {
                    int len = 0;
                    while (text[i + len] != ' ' && text[i + len] != '\n' && text[i + len] != '\0')
                    {
                        len++;
                    }
                    words.push_back(text.substr(i, len));
                    i = i + len;
                }
                else
                {
                    i++;
                }
            }
            //O método de atualização da tabela hash é chamado.
            updateHash();
            cout << "Texto adicionado. Contagem de palavras atualizada.\n";
        }
        //Contar palavras
        int countWord(string cword)
        {
            //"Balde" em que está a palavra
            int bucket = hashFunction(cword);
            //Percorre a lista encadeada
            for (list<Node>::iterator it = hashmap[bucket].begin(); it != hashmap[bucket].end(); it++)
            {
                //Acha a contagem da palavra
                if (it->word == cword)
                {
                    return it->count;
                }
            }
            //Se a palavra não foi achada, retorna 0
            return 0;
        }
        //Atualizar palavras
        void updateWord(string uword, int newq)
        {
            //"Balde" em que está a palavra
            int bucket = hashFunction(uword);
            //Laço que percorre a lista encadeada
            for (list<Node>::iterator it = hashmap[bucket].begin(); it != hashmap[bucket].end(); it++)
            {
                //Se a palavra for encontrada...
                if (it->word == uword)
                {
                    //As duas condições a seguir atualizam a quantidade da palavra no "texto" (vetor words).
                    //Se há elementos a adicionar...
                    if (newq > it->count)
                    {
                        for (int i = 0; i < newq - it->count; i++)
                        {
                            words.push_back(uword);
                        }
                    }
                    //Se há elementos a retirar...
                    else if (newq < it->count)
                    {
                        //Iterador para percorrer o vetor
                        vector<string>::iterator itv = words.begin();
                        //Quantidade de elementos já removidos
                        int removed_qt = 0;
                        while (itv != words.end())
                        {
                            if (*itv == uword && removed_qt < it->count - newq)
                            {
                                itv = words.erase(itv);
                                removed_qt++;
                            }
                            else
                            {
                                itv++;
                            }
                        }
                    }
                    //Atualiza o contador do hashmap
                    it->count = newq;
                    cout << "Palavra atualizada.\n";
                    return;
                }
            }
            cout << "Palavra não encontrada!\n";
        }
        //Remover palavras
        void removeWord(string rword)
        {
            //"Balde" em que está a palavra
            int bucket = hashFunction(rword);
            //Laço que percorre a lista encadeada
            for (list<Node>::iterator it = hashmap[bucket].begin(); it != hashmap[bucket].end(); it++)
            {
                //Se a palavra for achada...
                if (it->word == rword)
                {
                    //Iterador para percorrer o vetor
                    vector<string>::iterator itv = words.begin();
                    //O laço a seguir remove todas as instâncias da palavra no "texto" (vetor words).
                    while (itv != words.end())
                    {
                        if (*itv == rword)
                        {
                            itv = words.erase(itv);
                        }
                        else
                        {
                            itv++;
                        }
                    }
                    //Apaga o elemento do hashmap.
                    hashmap[bucket].erase(it);
                    return;
                }
            }
            //Caso em que a palavra não foi encontrada.
            cout << "Elemento não está na lista.\n";
        }
        //Verificar palavras
        bool containsWord(string coword)
        {
            //"Balde" em que está a palavra
            int bucket = hashFunction(coword);
            //Laço que percorre a lista encadeada
            for (list<Node>::iterator it = hashmap[bucket].begin(); it != hashmap[bucket].end(); it++)
            {
                //Se a palavra é achada...
                if (it->word == coword)
                {
                    return true;
                }
            }
            return false;
        }
        //Imprimir conteúdo
        void printTable()
        {
            //Laço para percorrer as n linhas do vetor
            for (int i = 0; i < n; i++)
            {
                cout << "indice " << i << ": ";
                //Laço para percorrer a lista encadeada
                for (list<Node>::iterator it = hashmap[i].begin(); it != hashmap[i].end(); it++)
                {
                    if (it->word != "\0")
                    {
                        cout << "(\"" << it->word << "\", " << it->count << ") -> ";
                    }
                }
                cout << "NULL\n";
            }
        }
        //Função Hash
        int hashFunction(const string& word)
        {
            unsigned long hash = 5381;
            for (char c : word)
            {
                hash = ((hash << 5) + hash) + static_cast<unsigned long>(c);
            }
            return (hash % n);
        }
        //Atualizar tabela
        void updateHash()
        {
            //wordcount = quantidade de vezes em que a palavra aparece no texto
            //bucket = "balde" em que será inserida aquela palavra, baseado na função hash
            //search = palavra que é procurada no texto em dado momento
            //found = indica se a palavra já foi achada no mapa ("true") ou não ("false")  
            int wordcount, bucket;
            string search;
            bool found;

            //Laço percorre todas as palavras do texto, da maneira como ele está;
            for (long unsigned int i = 0; i < words.size(); i++)
            {
                wordcount = 0;
                search = words[i];
                bucket = hashFunction(words[i]);
                found = false;

                //Percorre todo o texto, checando quantas vezes a palavra aparece
                //Armazena em wordcount
                for (long unsigned int j = 0; j < words.size(); j++)
                {
                    if (words[j] == search)
                    {
                        wordcount++;
                    }
                }
                //Checa se o "balde" em que será armazenada a palavra está vazio
                //Se sim, armazena no primeiro elemento
                if (hashmap[bucket].front().word == "\0")
                {
                    hashmap[bucket].front().word = words[i];
                    hashmap[bucket].front().count = wordcount;
                }
                //Se o balde não está vazio...
                else
                {
                    //Percorre todo o balde, para verificar se a palavra já está nele.
                    for (list<Node>::iterator it = hashmap[bucket].begin(); it != hashmap[bucket].end(); it++)
                    {
                        //Se a palavra for encontrada, seu contador é atualizado.
                        if (it->word == words[i])
                        {
                            it->count = wordcount;
                            found = true;
                            break;
                        }
                    }
                    //Senão, é incluído um novo elemento na lista encadeada.
                    if (!found)
                    {
                        hashmap[bucket].push_back(Node(words[i], wordcount));
                    }
                }
            }
        }
        //Mostra texto, com as palavras separadas por linha
        void showWords()
        {
            for (int i = 0; i < static_cast<int>(words.size()); i++)
            {
                cout << words[i] << "\n";
            }
        }
};

#endif