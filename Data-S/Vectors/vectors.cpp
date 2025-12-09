//I've made this program which helped me understand the basics of vector Data Structure in cpp

#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n,b;
    cout<<"\nEnter number of task you wanna add (initial): ";
    cin>>b;
    cin.ignore();
    vector<string> a(b);
    for(int i=0;i<a.size();i++){
        cout<<i<<". ";
        getline(cin, a.at(i));
        cout<<endl;
    }

    cout<<"\nYour list: \n";
        for(int i=0;i<a.size();i++){
            cout<<i<<". "<<a.at(i)<<endl;
        }
    
while(true){
// from here the loops starts
    cout<<"\n\n===Features===";
    cout<<"\n1. Add Tasks";
    cout<<"\n2. Remove Task";
    cout<<"\n3. Edit a specific task";
    cout<<"\n4. Preview Task";
    cout<<"\n5. Exit";
    cout<<"\nChoose (1,2,3): ";
    cin>>n;
    cin.ignore();   

    if(n==1){
        string temp;
        cout<<"\n\nEnter the new element: ";
        getline(cin, temp);
        a.push_back(temp);
        cout<<"\nNew list: \n";
        for(int i=0;i<a.size();i++){
            cout<<i<<". "<<a.at(i)<<endl;
        }
    }
    else if(n==2){
        cout<<"\n\nEnter the no. of the elements you wanna remove (1,2,...): ";
        int m;cin>>m;
        a.erase(a.begin()+m);
        cout<<"\nNew list: \n";
        for(int i=0;i<a.size();i++){
            cout<<i<<". "<<a.at(i)<<endl;
        }

    }
    else if(n==3){
        cout<<"\nWhich task you wanna edit (1,2,...): ";
        int g;cin>>g;
        string edit;
        cin.ignore();
        cout<<"\nEdit your "<<g<<"no. task: ";
        getline(cin, edit);
        a.at(g) = edit;
        cout<<"\nNew list: \n";
        for(int i=0;i<a.size();i++){
            cout<<i<<". "<<a.at(i)<<endl;
        }

    }
    else if(n==4){
        cout<<"\nYour list: \n";
        for(int i=0;i<a.size();i++){
            cout<<i<<". "<<a.at(i)<<endl;
        }
    }
    else if(n==5) break;
}


    return 0;
}