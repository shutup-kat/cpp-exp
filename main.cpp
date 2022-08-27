#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct kitten{
    string name;
    string color;
    int score;
    
};

struct roster{
    kitten kittens[10];
    int size=0;
    int total=0;
};



// kitten.name
// roster.kitten[1].color


void printMenu(){
    cout << "MENU" << endl;
    cout << "a - Add kitten" << endl;
    cout << "d - Delete kitten" << endl;
    cout << "u - Update kitten color and cuteness score" << endl;
    cout << "f - Find kitten" << endl;
    cout << "l - Load kitten info from file" << endl;
    cout << "s - Save kitten info to file" << endl;
    cout << "o - Output roster" << endl;
    cout << "q - Quit" << endl << endl;

    cout << "Choose an option:" << endl;
    
    
};

int findKitten(string name, roster x){
    int index = -1;
    for(int k=0; k< 10; k++){
        if (x.kittens[k].name == name){
            index = k;
            return index;
        }
    }
    return index;
};

void addKitten(kitten kit, roster& ros){
    
    if(ros.size >= 10){
        cout << "Impossible to add new kitten: roster is full." << endl;
    }
    else{
        cout <<"Enter a new kitten's name:" << endl;
        cin >> kit.name;
        ros.kittens[ros.size].name = kit.name;
        cout << "Enter the kittens's color:" << endl;
        cin >> kit.color;
        ros.kittens[ros.size].color = kit.color;
        cout << "Enter the kittens's cuteness score:" << endl;
        cin >> kit.score;
        ros.kittens[ros.size].score = kit.score;
        
        ros.size += 1;
        cout << "Successfully added new kitten to roster." << endl <<endl;
    };
    
};

bool deleteKitten(string name, roster& ros){
    bool flag = false;
    cin >> name;
    if( findKitten(name, ros) != -1){
            ros.size -= 1;
            for(int j = 0; j < ros.size; j++){
                ros.kittens[j].name = ros.kittens[j+1].name;
                ros.kittens[j].color = ros.kittens[j+1].color;
                ros.kittens[j].score = ros.kittens[j+1].score;
                flag = true;
            }
        }
        else{

            cout <<"kitten was not found. " << endl;
            flag = false;
        };
    return flag;
    };

void getKittenFromFile(string fileName, roster& ros)
{
    ifstream inFS;
    inFS.open(fileName);
    if(!inFS.is_open()){
        cout << "Error! File not found." << endl;
    }
    else{
        if(ros.size <10){
        while (getline(inFS, ros.kittens[ros.size].name)){
            //inFS.ignore();
            getline(inFS, ros.kittens[ros.size].color);
            //.ignore();
            inFS >> ros.kittens[ros.size].score;
            inFS.ignore(256, '\n');
            ros.size +=1;
            if(ros.size > 10){
            cout << "Impossible to add new kitten: roster is full." << endl;
        }
        }
        }
        inFS.close();
        }
    }
bool updateKitten(kitten kit, roster& ros){
    int index = findKitten(kit.name, ros);
    if(index == -1){
       cout << "Cannot find kitten." << endl;
       return false;
    }
    else{
        ros.kittens[index].color = kit.color;
        ros.kittens[index].score = kit.score;
        cout << "Successfuly updated kitten info." << endl;
        return true;
        }
};


void printRoster(roster ros){
    cout << "ROSTER:" << endl;
    for(int i = 0; i< ros.size; i++){
        cout << "Kitten " << i+1 << " -- Name: " << ros.kittens[i].name;
        cout << ", Color: " << ros.kittens[i].color;
        cout << ", Score: " << ros.kittens[i].score << endl;
    };
    cout << endl;
};


void printToFile(string fileName, roster& ros){
    ofstream fiName;
    int k;
    fiName.open(fileName);
    if(!fiName.is_open()){
        return;
    }
    else{
        fiName << "ROSTER:" << endl;
        for(k = 0; k < ros.size; k++){
        fiName << "Kitten " << k+1 << " -- Name: " << ros.kittens[k].name << ", Color: " << ros.kittens[k].color << ", Score: " << ros.kittens[k].score << endl;
        }
    }
    fiName.close();
};

int main()
        {
    string name;
    string fileName;
    ifstream infile;
    //ifstream infile(fileName);
    roster kittenRoster;
    kitten kitten;
    char y;
            do{
                printMenu();
               // cin .ignore();
                cin >> y;
                cin .ignore();
                
                switch(y){
                        
                    case 'a': {
                        addKitten(kitten, kittenRoster);
                        
                        break;
                    };
                        
                    case 'd': {
                        deleteKitten(name, kittenRoster);
                        
                        break;
                    };
                        
                    case 'u': {
                         
                    cout << "Enter a kitten name:" << endl;
                    cin >> kitten.name;
                    cout << "Enter a new color for the kitten:" << endl;
                    getline(cin, kitten.color);
                    cout << "Enter a new score for the kitten:"<< endl;
                    infile >> kitten.score;
                    updateKitten(kitten, kittenRoster);
                    cout << endl;
                                               
                        break;
                    };
                        
                    case 'f': {
                        cout << "Enter a kitten name: " << endl;
                        cin >> name;
                        if(findKitten(name, kittenRoster) == -1){
                            cout << "Kitten not found." << endl;
                        }
                        else{
                            for(int k=0; k< kittenRoster.size; k++){
                                if (kittenRoster.kittens[k].name == name){
                                    cout <<kittenRoster.kittens[k].name <<" info: " << kittenRoster.kittens[k].color << ", " << kittenRoster.kittens[k].score << endl;
                                }
                            };
                        };
                        cout << endl;
                        break;
                    };
                        
                    case 'l': {
                        cin >> fileName;
                getKittenFromFile(fileName, kittenRoster);
                        break;
                    };
                        
                    case 's': {
                        cout << "Enter file name: " << endl;
                        cin >> fileName;
                        
                        printToFile(fileName, kittenRoster);
                        cout << endl;
                        
                        break;
                    };
                        
                    case 'o': {
                        
                        printRoster(kittenRoster);
                        
                        break;
                    };
                        
                    case 'q' : {
                        break;
                    };
                        
                    default:{
                        cout << "Invalid option. Please try again." << endl;
                        break;}
                        
                }
                
                
            }while(y != 'q');
        
        
        
        }
   
