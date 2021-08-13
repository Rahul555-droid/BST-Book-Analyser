/*
A BST based book Analyser's driver file.
*/

#include<iostream>
#include "bst.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include<fstream>

using namespace std;

//WordEntry Class 
class WordEntry{

public:
    string word="";
    int frequency=0;

    //cunstroctors.
    WordEntry(){
        this->word = "";
    }

    WordEntry(string str){
        this->word = str;
        this->frequency = 1;
    }

    //overloaded operators.
    //for deciding equality we care about string values only.
    bool operator == (WordEntry const &w){
        return (this->word == w.word);
    }

    bool operator == (WordEntry* const w){
        return (this->word == w->word);
    }

    //>= of frequency means ">" in wordEntry

    bool operator > (WordEntry const &w){
        return (this->frequency >= w.frequency);
    }

    bool operator > (WordEntry* const w){
        return (this->frequency >= w->frequency);
    }

    bool operator < (WordEntry const &w){
        return (this->frequency < w.frequency);
    }

    bool operator < (WordEntry* const w){
        return (this->frequency < w->frequency);
    }

    friend ostream & operator << (ostream &out,WordEntry w);
};
//overloaded << operator for output.
ostream & operator << (ostream &out,WordEntry w ){
        out<<" ["<<w.word<<", "<<w.frequency<<"] ";        
        return out;
    }

//comparator for albphabetical sorting #xtra credit.
bool comparatorAlpha(WordEntry w1, WordEntry w2)
{
    return (w1.word < w2.word);
}

int main(){

unordered_map<string, WordEntry> umap; //using unordered map for start.

cout<<"\nWelcome to Abdalla's CSE 240 BST word Counter!\n\n";
cout<<"Enter the Name of your file : ";
string fileName;
cin>>fileName;
cout<<"Analysing the file for you...........\n";

ifstream file(fileName);

string line;
while (getline(file, line)) {
    // line contains the current line
    string word;
    for (size_t i=0;i<line.size();i++){
        char c=line[i];
        
    if (c=='\'') //for handling apostrophe. //for some files this apostrophe part was not working as character sets were different.
            word+=c;
    
    if(c>=97 && c<=122)
                word+=c;
            
    else if(c>=65 && c<=90)
            {  
                c+=32; //converting Capital letter char into small.
                word+=c;
            }
        
    else{
			if (word=="")
				continue;
			
            if(umap.find(word)==umap.end())
                umap[word] = *(new WordEntry(word));
            else
                umap[word].frequency=umap[word].frequency+1;
            
            word.clear();
            }
        }
    }



    BST<WordEntry>* bstree = new BST<WordEntry>();

    for (auto x : umap)
        bstree->Insert(x.second);
    
WordEntry* wArr = bstree->toArray();

/* //to print the BST array with WordClass just in case .

for(int i=0;i<bstree->Length();i++)
    cout<<wArr[i]<<"\n";
*/

//Printing summary.
int total_words = 0;
for(int i=0;i<bstree->Length();i++)
    total_words+=wArr[i].frequency;

cout<<"total words in file : "<<total_words<<"\n";
cout<<"unique words in file : "<<bstree->Length()<<"\n";

//I have the inorder traversal array "wArr" from previous part so will reuse that. in next parts.
string word2find,input;

my_label: //I know gotos are bad practice but cse230 gave me a different outlook.
    cout<<"\nSUMMARY:\n";
    cout<<"Top 5 most frequent words:\n";

for(int i=1;i<6;i++)
    cout<<to_string(i)+". "<<wArr[bstree->Length() - i].word<<"\n";

cout<<"Top 5 least frequent words:\n";
for(int i=0;i<5;i++)
    cout<<to_string(i+1)+". "<<wArr[i].word<<"\n";

cout<<"\nEnter the word that you want to find : ";
//I overloaded "==" WordEntry , so this works.
cin>>word2find;

//This is to find a word's frequency from BST It works for most of the time
//but I used hashmap method below
//for finding frequency of a word as it gives me O(1) time complexity for searching. 

/*
WordEntry w_obj = *(new WordEntry(word2find));
BSTNode<WordEntry>* node = bstree->Find(w_obj);

if(node==nullptr || node ==NULL)
{
cout<<"here3"<<endl;
cout<<"\nCouldn't find the word "<<word2find<<" in the BST\n";
cout<<"here4"<<endl;
}
else{
//cout<<"\n"<<"Frequency of the word: "<<node->item.word<<" is "<<node->item.frequency<<"\n";
cout<<"\n"<<node->item<<"\n";
}
*/

//hashmap based frequency getter.
if(umap.find(word2find)==umap.end())
    cout<<"\nCouldn't find the word "<<word2find<<"\n";
else
    cout<<"\n"<<"Frequency of the word: "<<word2find<<" is "<<umap[word2find].frequency<<"\n";
    

my_label1:
    cout<<"Do you want to output this analysis to a file ?(Y/N)\n";
    cin>>input;

//did extra credit for sorting by alphabetical and frequency..
if(input=="Y" || input=="y")
    { 
        cout<<"You selected option Y---Yes.\nWriting it to a file \"analysis.txt\" \n";
        cout<<"Enter the option for each of the case below:\n";
        cout<<"Sort words in file by : \n1.Frequency \n2.Alphabetically "<<"\n";
        int inp;
        cin>>inp;

        if(inp==1)
         {
        ofstream writeFile("analysis.txt");   
        cout<<"The file is Sorted in Ascending order by Frequency \n";

        writeFile<<"total words in file : "<<total_words<<"\n";
        writeFile<<"unique words in file : "<<bstree->Length()<<"\n";
        writeFile <<"The file is Sorted in Ascending order by Frequency \n";
        writeFile <<"\n[word , frequency] ---- Format\n\n";
        wArr = bstree->toArray();
        for(int i=0;i<bstree->Length();i++){
            writeFile<<to_string(i+1)+". "<<wArr[i]<<"\n";
         }
        writeFile.close();
         }
        else if (inp == 2)
        {
            ofstream writeFile("analysis.txt");
            cout<<"The file is Sorted in Ascending order by Alphabetics\n";
            writeFile<<"total words in file : "<<total_words<<"\n";
            writeFile<<"unique words in file : "<<bstree->Length()<<"\n";
            writeFile<<"The file is Sorted in Ascending order by Alphabetics\n";
            sort(wArr, wArr + bstree->Length(),comparatorAlpha);
        for(int i=0;i<bstree->Length();i++)
            writeFile<<to_string(i+1)+". "<<wArr[i]<<"\n";
        
        writeFile.close();
		wArr = bstree->toArray();
         }  
        else{
            cout<<"Invalid input\n";
        }
    }
else if(input=="N" || input=="n")     
    cout<<"You selected option N---No.\n";
else{
    cout<<"Invalid option\n try again.";
    goto my_label1;
    }

cout<<"Do you want to Exit the program?(Y/N)\n";
cin>>input;
if(input=="N" || input=="n")
{
    cout<<"Do you want to check summary for another word?"<<"(Y / N or other for exit.):";
    cin>>input;
    if(input=="Y" || input=="y")
        goto my_label;
}


file.close();
delete bstree; //deleting bstree.

return 0;

}