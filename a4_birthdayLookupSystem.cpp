#include <stdio.h>
#include "a4_birthdayBST.hpp"
#include "a4_birthdaylib.hpp"
#include <fstream>




int main(){
    //printing out the fancy banner
    cout<<"♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡"<< endl;
    cout<<"Famous Birthdays Lookup System"<<endl;
    cout<<"♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡"<< endl;
    cout<<"Layan Barrieshee"<<endl;
    cout<<"301544289"<<endl;
    cout<<"lab22@sfu.ca" <<endl;
    cout<<"♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡" <<endl;


    //string stores my file name so i can open it and store its info
    string textfile;

    //indicator that the there is textfile and the name has been stored
    int flag = 0;
    string linereading;
    

    //indicator to keep on running the program unil user stops it
    //in that case, the terminator value changes and program ends
    int terminator = 0;

    //create the tree to store info
    BirthdayBST newtree = BirthdayBST();
    
    

    //interface for program
   while (terminator==0){

    //setting the type and number for which the user enters
    int option;

    //showing the options that the user can choose from
    cout<<"Press numbers 1-5 for the following options then enter:"<<endl;
    cout<<"1) to load a birthday file"<<endl;
    cout<<"2) to list birthdays sorted by Month-Day"<<endl;
    cout<<"3) to look up a birthday"<<endl;
    cout<<"4) to add a birthday"<<endl;
    cout<<"5) to save a birthday file"<<endl;
    cout<<"6) to terminate the program." <<endl;
    cout<<"Option:"<<endl;

    //allowing user to enter their choice
    cin>>option;

    //do the following it is option 1
    if (option == 1){
        flag = 1;
        cout<<"Enter the full name of the"; 
        cout<<"birthday file (with extension):"<<endl;

        //getting file name from user
        cin>>textfile;

            //opening file and checking if is empty or not
            ifstream file;
            file.open(textfile);
            if(!file.is_open()){
                cout<<"No Birthday loaded. Load one first."<<endl;
                cout<<"=============================="<<endl;
            
            }
            //checking if a file already exists
            else{
                if (flag == 1){
                    newtree.~BirthdayBST();
                    newtree = BirthdayBST();
                }


                //fill up the info for each line 
                short month;
                short day;
                short year;
                string nameinfo;
                string descripinfo;
                string dashes;


                //reading the file information and storing it inside
                while(getline(file,linereading,'-')){
                    year = stoi(linereading);
                    
                
                    getline(file,linereading,'-');
                    month = stoi(linereading);
                   

                    getline(file,linereading);
                    day = stoi(linereading);
                   


                    getline(file,nameinfo);                  
                    

                    getline(file,descripinfo);                 
                    

                    getline(file,dashes);
                   
                    //storing info into the struct
                    Birthday* newbirthday = create_Birthday(year, month, day, 
                    nameinfo, descripinfo);
                   
                   //inserting a node for each struct
                    newtree.insertNode(newbirthday);
              

                }       //getting the number of entries using size of tree
                        cout<<newtree.getSize()<<" entries read." <<endl;
                        cout<<"=============================="<<endl;

                //closing the file after reading it
                file.close();
              
            }
                    
    }

    //if option 2, do the following  
    else if (option == 2){
    if (flag == 1){
        newtree.inOrderPrint(cout);
    }
    //if the file is not ther or there is a problem tell the user
    else {
        cout<<"No Birthday loaded. Load one first."<<endl;    
        }
    }


    //if option 3, do the following
    else if (option == 3){
        if(flag == 1){
            
            //get user input for month
            short monthy;
            cout<<"What is the month?(Press 1-2 and enter)"<<endl;
            cin>>monthy;

            //get user input for day
            short dayy;
            cout<<"What is the day?(Press 1-31 and enter)"<<endl;
            cin>>dayy;

            //tell the user what they have entered
            cout<<"You have entered:" <<monthy<<"-"<<dayy<<endl;
            cout<<"=============================="<<endl;
            //find the matching md if there is one
            newtree.findNodeByMD(monthy, dayy);
    }
    else {
        cout<<"No Birthday loaded. Load one first."<<endl;    
        }
}
         
    //if option 4, do the following
    else if (option == 4){
        if(flag == 1){

            //get the user input for year
            short yearinput;
            cout<<"What is the year?(input a 4-digit year)"<<endl;
            cin>>yearinput;

            //get the user input for month
            short monthinput;
            cout<<"What is the month?(Press 1-2 and enter)"<<endl;
            cin>>monthinput;

            //get user input for day
            short dayinput;
            cout<<"What is the day?(Press 1-31 and enter)"<<endl;
            cin>>dayinput;

            //get user input for the name of the person
            string nameofperson;
            cout<<"What is the name of this person?"<<endl;
            getline(cin>>ws,nameofperson);
        
            //get user input for what this person is known for
            string kfor;
            cout<<"What is this person known for?"<<endl;
            getline(cin>>ws,kfor);

            //tell the user what they have entered
            cout<<"You have entered:" <<yearinput<<"-"
            <<monthinput<<"-"<<dayinput<<endl
            <<nameofperson<<endl<<kfor<<endl;

            //store the information in a struct 
            Birthday* newbirthday = create_Birthday(yearinput, 
            monthinput, dayinput,nameofperson, kfor);

            //if there is no existing birthday, add it 
            cout<<"=============================="<<endl;
            if (newtree.findNodeByYMDN(yearinput, monthinput, 
            dayinput, nameofperson) == NULL){
                newtree.insertNode(newbirthday);
                cout<<"Birthday added!"<<endl;
            }
           
           //otherwise do not add the birthday
            else {
                cout<<"An entry with the same name and";
                cout<< "birthday already exists.Nothing added."<<endl;
            }
        
        }

    }

    //if user enters 5, do the following
    else if(option == 5){
        if(flag == 1){
    
        //get input from user for the file you want to get the info from
        string filename;
        cout<<"Enter the full name of the"; 
        cout<<"birthday file (with extension):"<<endl;
        cin.ignore();
        getline(cin,filename);

        //open and read the file
        ofstream otherfile;
        otherfile.open(filename);

        //if the file is open, print the information in 
        //the other file created
        if(otherfile.is_open()){
        newtree.inOrderPrint(otherfile);

        //report back the number of entries stored
        cout<<newtree.getSize()<<" entries read." <<endl;
        cout<<"=============================="<<endl;
        otherfile.close();
        }

        
        }

         else {
        cout<<"No Birthday loaded. Load one first."<<endl; 
        cout<<"=============================="<<endl;
   
        }
    }

    else{
        // //thanking the user and end program
        cout<<"Program Ended! Thank You! Good Bye!"<<endl;
        terminator = 1;  
        break;
                 
    }  
   } 
}