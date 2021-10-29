#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
using namespace std;
class Activity{
    public:
    string activityTitle,activityCreator,tb,db,te,de,venueName,exclusive;
    long long unsigned int startepoch;
    long long unsigned int endepoch;
    Activity(string _activityTitle,string _activityCreator,string _tb,string _db, string _te,string _de,string _venueName,string _exclusive,long long unsigned int _startepoch,long long unsigned int _endepoch){
        activityTitle=_activityTitle; 
        activityCreator=_activityCreator;
        tb=_tb;
        db=_db;
        te=_te;
        de=_de;
        venueName=_venueName;
        exclusive=_exclusive;
        startepoch=_startepoch;
        endepoch=_endepoch;
    }
      Activity(){
        activityTitle="null"; 
        activityCreator="null";
        tb="null";
        db="null";
        te="null";
        de="null";
        venueName="null";
        exclusive="null";
    }
};

class User{
    public:
    string firstname,lastname,userId;
    vector<Activity> attending;

    User(string id,string fname,string lname){
        firstname=fname;
        lastname=lname;
        userId=id;
    }
    User(){
        firstname="null";
        lastname="null";
        userId="null";
    }
};



class Venue{
    public:
    string venueName,venueLocation;
    int venueCapacity;
    Venue(string _name,int capacity,string location)
    {
        venueName=_name;
        venueCapacity=capacity;
        venueLocation=location;
    }
     Venue()
    {
        venueName="null";
        venueCapacity=0;
        venueLocation="null";
    }
};

//---------------------------------------------------------------------------------------------------------------------------
//linked list stuff
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node()
    {
        data = T();
        next = NULL;
    }
    Node(T data)
    {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
class LinkedList {
    Node<T>* head;
public:
    LinkedList() { head = NULL; }
    ~LinkedList(){}
    void insertNode(T);
    void printListUser();
    void deleteNode(int);
    bool searchUserList(string);
    bool searchActivityList(string);
    bool isFree(long long unsigned int,long long unsigned int,string);
    Activity searchActivitySender(string );
    bool updater(string,Activity,LinkedList<Venue>);
    bool isSeatsAvailable(Activity act);

};
template <typename T>
void LinkedList<T>::deleteNode(int NodeOffset)
{
    Node<T> *temp1 = head, *temp2 = NULL;
    int ListLen = 0;
  
    if (head == NULL) {
        cout << "List empty." << endl;
        return;
    }
      while (temp1 != NULL) {
        temp1 = temp1->next;
        ListLen++;
    }

    if (ListLen < NodeOffset) {
        cout << "Index out of range"
             << endl;
        return;
    }
  
    temp1 = head;
  
    if (NodeOffset == 1) {
  
        head = head->next;
        delete temp1;
        return;
    }

    while (NodeOffset-- > 1) {
          temp2 = temp1;
          temp1 = temp1->next;
    }

    temp2->next = temp1->next;
  
    delete temp1;
}
template <typename T>
void LinkedList<T>::insertNode(T data)
{
    Node<T>* newNode = new Node<T>(data);
      if (head == NULL) {
        head = newNode;
        return;
    }
  
    Node<T>* temp = head;
    while (temp->next != NULL) {
          temp = temp->next;
    }
      temp->next = newNode;
}
template <typename T>
void LinkedList<T>::printListUser()
{
    Node<T>* temp = head;
  
    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }
  
    while (temp != NULL) {
        cout << temp->data.userId << " "<< temp->data.firstname<<" "<< temp->data.lastname <<endl;
        temp = temp->next;
    }
    
   
  
}
template<typename T>
bool LinkedList<T>::searchUserList(string item) //function to search element in the linked list 
{  
     Node<T>* temp = head;
  
    if (head == NULL) {
        cout << "User List empty" << endl;
        return false;
    }
  
    while (temp != NULL) {
        if(temp->data.userId == item)
        {
            // cout<<"\n\nFOUND "<<item;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::searchActivityList(string item) //function to search element in the linked list 
{  
     Node<T>* temp = head;
  
    if (head == NULL) {
        cout << "Activity List empty" << endl;
        return false;
    }
  
    while (temp != NULL) {
        if(temp->data.activityTitle==item){
            return true;
        }
        
        temp = temp->next;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::isFree(long long unsigned int start ,long long unsigned int end,string userId) //function to search element in the linked list 
{  
     Node<T>* temp = head;
    int flag=0;
    if (head == NULL) {
        cout << "Activity List empty" << endl;
        return true;
    }
       
     while (temp != NULL) 
     {
        //  cout<<temp->data.userId<<endl;
        if(temp->data.userId == userId)
        {   
            // cout<<"found him! "<<temp->data.userId;
            flag=1;
            for( Activity i : temp->data.attending)
            {
                // cout<<"debug:"<<i.activityTitle<<endl;
                flag=2;
                // if(start<i.endepoch)cout<<"endepoch is bigger by"<<i.endepoch-start<<endl;
                // else cout<<"start is bigger by"<<start-i.endepoch<<endl;
                // if(start<i.startepoch)cout<<"startepoch is bigger by"<<i.startepoch-start<<endl; 
                // else cout<<"start is bigger by"<<start-i.startepoch<<endl;

                if(start > i.endepoch)
                {
                    // cout<<"\nstart is greater\n";
                    return true;
                }
                else if(start < i.startepoch && end > i.endepoch){
                    // cout<<"\nstart is lesser\n";
                    return true;
                }
                return false;
            } 
        }
           
        if(flag==1)
        {
            //he is fully free
            return true;
        } 
        temp = temp->next;
    }
    cout<<"user not even found\n";
    return false;
}

template<typename T>
Activity LinkedList<T>::searchActivitySender(string item) //function to search element in the linked list 
{  
     Node<T>* temp = head;
  
    if (head == NULL) {
        cout << "Activity List empty" << endl;
    }
  
    while (temp != NULL) {
         if(temp->data.activityTitle==item){
            return temp->data;
        }
        temp = temp->next;
    }
    return Activity(); //null
}

template<typename T>
bool LinkedList<T>::updater(string name,Activity act,LinkedList<Venue> ValueLinkedList) //function to search element in the linked list 
{  
     Node<T>* temp = head;
    // LinkedList<Value> ValueLinkedList;
    if (head == NULL) {
        cout << "user List empty" << endl;
    }
  
    while (temp != NULL) {
         if(temp->data.userId == name)
        {
            // cout<<"userid:"<<temp->data.userId;
            if(ValueLinkedList.isSeatsAvailable(act))
                temp->data.attending.push_back(act);
                cout<<"\nattendance updated \n-------------------------------------------------------------\n";
                return true;
        }
        temp = temp->next;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::isSeatsAvailable(Activity act) //function to search element in the linked list 
{ 
    // cout<<"seats\n\n\n";
     Node<T>* temp = head;
  
    if (head == NULL) {
        cout << "user List empty" << endl;
    }
  
    while (temp != NULL) {
            // cout<<"\n\nwhile\n\n\n";

         if(act.venueName == temp->data.venueName)
        {
            int capacity=temp->data.venueCapacity;
            if(capacity-1>=0)
            {
                capacity--;
                temp->data.venueCapacity=capacity;
                cout<<"\nSEATS ARE THERE\n";
                return true;
            }
            else{
                cout<<"\nNO SEATS AVAILABLE\n";
                return false;
            }
        }
        temp = temp->next;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------


long long unsigned int getepoch(string time,string date){
    int b_dd,b_mm,b_yyyy;
    //==================================================date
      string date_dd="",date_mm="",date_yyyy="";
            string intermediate;
            stringstream check1(date);
            int i=0;
            bool check=false;
            while(getline(check1, intermediate, '-'))
            {
                if(i==0)
                 date_dd.append(intermediate); 
                else if(i==1)
                  date_mm.append(intermediate);
                else if(i==2)
                {
                  date_yyyy.append(intermediate);
                  check=true;
                }
                else
                {
                  cout<<"XXXXXXXX Wrong date 1 XXXXXXXX\n";
                  return false;
                  check=false;
                }
              
              i++;
            }
            if(check!=true)
            {
              cout<<"XXXXXXXX Wrong date 2 XXXXXXXX\n";
              return false; 

            }
            // cout<<"Debug: "<<"dd="<<date_dd<<endl;
            // cout<<"Debug: "<<"mm="<<date_mm<<endl;
            // cout<<"Debug: "<<"yyyy="<<date_yyyy<<endl;
            if((stoi(date_dd)>31 && stoi(date_dd)>0) || (stoi(date_mm)>12 && stoi(date_mm)>0 )||( (stoi(date_yyyy)<1970 && stoi(date_yyyy)>5000 )))
            {
                cout<<"XXXXXXXX Wrong date 3 XXXXXXXX\n";
                return false; 
            }
            else
            {
                b_dd=stoi(date_dd);
                b_mm=stoi(date_mm);
                b_yyyy=stoi(date_yyyy);
                // cout<<"yay";
            }

            //===================================================time
            int thh,tmm,tss;

            string time_hh="",time_mm="",time_ss="";
            intermediate="";
            stringstream check2(time);
            i=0;
            check=false;
            while(getline(check2, intermediate, ':'))
            {
                if(i==0)
                  time_hh.append(intermediate); 
                else if(i==1)
                  time_mm.append(intermediate);
                else if(i==2)
                {
                  time_ss.append(intermediate);
                  check=true;
                }
                else
                {
                  cout<<"XXXXXXXX Wrong date 4 XXXXXXXX\n";
                  check=false;
                }
              
              i++;
            }
            if(check!=true)
            {
              cout<<"XXXXXXXX Wrong date 5 XXXXXXXX\n";
              return false; 
            }
            // cout<<"Debug: "<<"hh="<<time_hh<<endl;
            // cout<<"Debug: "<<"mm="<<time_mm<<endl;
            // cout<<"Debug: "<<"ss="<<time_ss<<endl;
              i++;
            

            // if(check!=true)
            //   return false;

            if(( (stoi(time_hh)>24 && stoi(time_hh)>=0 ) || (stoi(time_mm)>59 && stoi(time_mm)>=0) || (stoi(time_ss)>59) && stoi(time_ss)>=0)  )
            {
                cout<<"XXXXXXXX Wrong Time XXXXXXXX\n";
            }
            else
            {
                   thh=stoi(time_hh);
                tmm=stoi(time_mm);
                tss=stoi(time_ss);
                // cout<<"wohoo";
            } 
long long unsigned int begin_timestamp=0,end_timestamp=0,difference=0;
begin_timestamp += b_yyyy * 31536000 ;
// cout<<begin_timestamp<<endl;
begin_timestamp += b_mm * 2592000 ;
// cout<<begin_timestamp<<endl;

begin_timestamp += (b_dd - 1) * 86400;
// cout<<begin_timestamp<<endl;

begin_timestamp += thh * 3600;
// cout<<begin_timestamp<<endl;

begin_timestamp += tmm * 60;
// cout<<begin_timestamp<<endl;

begin_timestamp += tss;

return begin_timestamp;
// return 1;
}

int main (){
LinkedList<User> UserLinkedList;
LinkedList<Activity> ActivityLinkedList;
LinkedList<Venue> VenueLinkedList;

ifstream _venueFile,_userFile,_activityFile,_attendanceFile;
_venueFile.open("_venueFile.txt");
_userFile.open("_userFile.txt");
_activityFile.open("_activityFile.txt");
_attendanceFile.open("_attendanceFile.txt");
//----------------------------------------------------------------------------------------------------------------------------
//VenueFile Parser
string venueLine="";
if ( _venueFile.is_open() )  
{
while ( getline (_venueFile, venueLine) )
{ 
// cout << userLine << '\n';
vector <string> tokens;
stringstream check1(venueLine);
string intermediate;
 while(getline(check1, intermediate, '>') )  //Tokenizing by space " "
    {   
        stringstream check1(intermediate);
        string intermediate2;
        while(getline(check1, intermediate2, '<') )
            cout<<"";
        
        if(intermediate2!=" ")
            tokens.push_back(intermediate2);
    }
    string venueName,venueLocation;
    int venueCapacity;
    int temp=0;
    for(int i = 0; i < tokens.size(); i++)
        {
            temp++;
            string strNew = tokens[i];
            if(temp==1)
                venueName=strNew;
            else if(temp==2)
             venueCapacity=stoi(strNew);
            else if(temp==3)
                venueLocation=strNew;
        }
        VenueLinkedList.insertNode(Venue(venueName,venueCapacity,venueLocation));
}
// VenueLinkedList.printListUser();
}
else {
cout << "Couldn't open _venueFile \n";
}

//-----------------------------------------------------------------------------------------------------------------------------
//UserFile Parser
string userLine="";
if ( _userFile.is_open() )  
{
while ( getline (_userFile, userLine) )
{ 
// cout << userLine << '\n';
vector <string> tokens;
stringstream check1(userLine);
string intermediate;
 while(getline(check1, intermediate, '>') )  //Tokenizing by space " "
    {   
        stringstream check1(intermediate);
        string intermediate2;
        while(getline(check1, intermediate2, '<') )
            cout<<"";
        
        if(intermediate2!=" ")
            tokens.push_back(intermediate2);
    }
    string firstname,lastname,id;
    int temp=0;
    for(int i = 0; i < tokens.size(); i++)
        {
            temp++;
            string strNew = tokens[i];
            if(temp==1)
                id=strNew;
            else if(temp==2)
             firstname=strNew;
            else if(temp==3)
                lastname=strNew;
        }
        UserLinkedList.insertNode(User(id,firstname,lastname));
}
// UserLinkedList.printListUser();
}
else {
cout << "Couldn't open _userFile \n";
}

//-----------------------------------------------------------------------------------------------------------------------------
//ActivityFile Parser
string activityLine="";
int number_of_lines=0;
if ( _activityFile.is_open() )  
{
while ( getline (_activityFile, activityLine) )
{ 
vector <string> tokens;
stringstream check1(activityLine);
string intermediate;
 while(getline(check1, intermediate, '>') )  //Tokenizing by space " "
    {   
        stringstream check1(intermediate);
        string intermediate2;
        while(getline(check1, intermediate2, '<') )
            cout<<"";
        
        if(intermediate2!=" ")
            tokens.push_back(intermediate2);
    }
    string activityTitle,activityCreator,tb,db,te,de,venuename,exclusive;
    int temp=0;
    for(int i = 0; i < tokens.size(); i++)
        {
            temp++;
            string strNew = tokens[i];
            if(temp==1)
                activityTitle=strNew;
            else if(temp==2)
             activityCreator=strNew;
            else if(temp==3)
                tb=strNew;
            else if(temp==4)
                db=strNew;
            else if(temp==5)
                te=strNew;
            else if(temp==6)
                de=strNew;
            else if(temp==7)
                venuename=strNew;
            else if(temp==8)
                exclusive=strNew;
        }
        // cout<<activityTitle<<" "<<activityCreator<<" "<<venuename<<" etc... "<<endl;

        ActivityLinkedList.insertNode(Activity(activityTitle,activityCreator,tb,db, te,de,venuename,exclusive,getepoch(tb,db),getepoch(te,de)));
        // ActivityLinkedList.insertNode(Activity(activityTitle,activityCreator,tb,db, te,de,venuename,exclusive,1,2));

}
// ActivityLinkedList.printListActivity();
}
else {
cout << "Couldn't open _activityFile \n";
}

//-----------------------------------------------------------------------------------------------------------------------------
//attendance Parser
string attendanceLine="";
if ( _attendanceFile.is_open() )  
{
while ( getline (_attendanceFile, attendanceLine) )
{ 
vector <string> tokens;
stringstream check1(attendanceLine);
string intermediate;
int temp1=1;
 while(getline(check1, intermediate, '>'))  //Tokenizing by space " "
    {   
        int len=intermediate.length();
        if(temp1==1){
            intermediate=intermediate.substr(1,len);
            tokens.push_back(intermediate);
            // cout<<"test 1 :"<<intermediate<<endl;
        }
        else if(temp1==2)
        {
            intermediate=intermediate.substr(2,len);
            tokens.push_back(intermediate);
            // cout<<"test 2 :"<<intermediate<<endl;
        }
        temp1++;
    }
    string activityTitle,userid;
    int temp=0;
    for(int i = 0; i < tokens.size(); i++)
        {
            temp++;
            string str = tokens[i];
            unsigned first = str.find("<");
            unsigned last = str.find_last_of(">");
            string strNew = str.substr (first+1,last-first-1);
            if(temp==1)
                activityTitle=strNew;
            else if(temp==2)
                userid=strNew;
        }
        // cout<<activityTitle<<endl;
        //start the process

        if(UserLinkedList.searchUserList(userid)){
            cout<<"\nUser "<<userid<<" Found\n";
            if(ActivityLinkedList.searchActivityList(activityTitle))
            {
                cout<<"\nActivity Found\n";
                Activity localAct=ActivityLinkedList.searchActivitySender(activityTitle);
                if(UserLinkedList.isFree(localAct.startepoch,localAct.endepoch,userid))
                {
                    cout<<"\nUser IS FREE\n";
                    UserLinkedList.updater(userid,localAct,VenueLinkedList);
                }
                else{
                    cout<<"\nUser is not free// SO REJECTING \n-------------------------------------------------------------"<<endl;
                }
                //if user is free, try to add activity else reject
            }
            else{
                cout<<"\nActivity Not Found// SO REJECTING  \n-------------------------------------------------------------\n";
            }
        }
        else{
            cout<<"\nUser Not found// SO REJECTING \n-------------------------------------------------------------\n";
        }

        //check if the user id is present in LinkedList
            //NO == Quit
            //YES == check if the activity title is present in activityLinkedList
                        //NO == Quit
                        //YES == check the venue of activity and get the capacity for the venue from venueLinkedList
                                

}
}
else {
cout << "Couldn't open _activityFile \n";
}


return 0;      
}