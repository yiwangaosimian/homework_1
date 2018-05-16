#include<iostream>
#include<string>
#include<fstream>
#include<map>
using namespace std;
map<string, string> BOOK;
string STR[750],UNAME[750];
int i=0,l=0;
//1 在借 0 在库 2 异常
class Book{
public:
    Book(string Name,string Path,string Kind,string Code,string Kind1,string isbn,string Press,string Writer,string Keeper,int Status);
    ~Book(){};
private:
    string name,path,kind,code,kind1,ISBN,press,writer,keeper;
    int status=0;
};

class Account{
public:
    Account(string Name,string Username,string Passcode,string Identity,string Catalogue);
    ~Account(){};
    void Borrow(string borrower);
    void Return(string keeper);
private:
    string name,username,passcode,identity;
    string catalogue;
};

class Paper{
public:
    Paper(string Name,string Path,string Kind,string Code,string Kind1,string Periodical,string Writer[64],string Keeper,string Title,string TIME,int NUM,int Status);
    ~Paper(){};
private:
    string name,path,kind,code,kind1,periodical,press,writer[64],keeper,title,Time;
    int status=0,NumOfWr=0;
};

class Explorer{
public:
    Explorer(string Catalogue);
    ~Explorer(){};
    void Input();
    void Update();
    void Delete();
    void View();
    void Search();
    void OnlineReading();
private:
    string catalogue,name,path,kind,code,kind1,periodical,ISBN,press,writer[64],keeper,title,Time;
    int status=0,NumOfWr=0;
};

class AccountManagement{
public:
    AccountManagement(string Name,string Username,string Passcode,string Identity,string Catalogue);
    ~AccountManagement(){};
    void AddUser();
    //void UpdateUser();
    void DeleteUser();
    //void SetUserRole();
    string Judge();
private:
    string name,username,passcode,identity,catalogue;
};
int main(){
    Book book("","","","","","","","","",0);
    Paper paper("","","","","","",NULL,"","","",0,0);
    Account account("","","","","/Users/linhailan1/Desktop/林海斓/程序设计/程序设计实践/作业1类与对象ddl：3.26/save/");
    Explorer explorer("/Users/linhailan1/Desktop/林海斓/程序设计/程序设计实践/作业1类与对象ddl：3.26/save/");
    string username="",passcode="",identity="",name="",temp="";
    bool flag=false;
    int choice=0;
    cout<<"Please enter your identity,name,username and passcode!"<<endl;
    cin>>identity>>name>>username>>passcode;
    AccountManagement AM(name,username,passcode,identity,"/Users/linhailan1/Desktop/林海斓/程序设计/程序设计实践/作业1类与对象ddl：3.26/record/");
    AM.AddUser();
    identity=AM.Judge();
    cout<<"Please enter your choice~"<<endl<<"1:Search  2:Borrow  3:Return  4:OnlineReading  5:SetUp  6:Input  7:Delete  8:DeleteUser   9:View 10:Update"<<endl;
    cin>>choice;
    if(identity=="user"||identity=="administrator"){
        while(choice){
            if(flag){
                cout<<"Do you want to carry on? Type the choice~ 0 refers to no!"<<endl;
                cin>>choice;
            }
            flag=true;
            switch(choice){
                case 1:{  explorer.Search();  break;  }
                case 2:{  account.Borrow(name);  break;  }
                case 3:{  account.Return(name);  break;  }
                case 4:{  explorer.OnlineReading();  break;  }
                case 5:{
                    cout<<"Please enter your identity,name,username and passcode!"<<endl;
                    cin>>identity>>name>>username>>passcode;
                    AccountManagement AM(name,username,passcode,identity,"/Users/linhailan1/Desktop/林海斓/程序设计/程序设计实践/作业1类与对象ddl：3.26/record/");
                    AM.AddUser();   break;
                }
                case 6: {
                    if(identity=="user"){
                        cout<<"you do not have privilege!"<<endl;
                        continue;
                    }
                    else if(identity=="administrator"){
                        explorer.Input();  break;
                    }
                }
                case 7:{
                    if(identity=="user"){
                        cout<<"you do not have privilege!"<<endl;
                        continue;
                    }
                    else if(identity=="administrator"){
                        explorer.Delete();  break;
                    }
                }
                case 8:{
                    if(identity=="user"){
                        cout<<"you do not have privilege!"<<endl;
                        continue;
                    }
                    else if(identity=="administrator"){
                        AM.DeleteUser();  break;
                    }
                }
                case 9:{
                    if(identity=="user"){
                        cout<<"you do not have privilege!"<<endl;
                        continue;
                    }
                    else if(identity=="administrator"){
                        explorer.View();  break;
                    }
                }
                case 10:{
                    if(identity=="user"){
                        cout<<"you do not have privilege!"<<endl;
                        continue;
                    }
                    else if(identity=="administrator"){
                        explorer.Update();  break;
                    }
                }
            }
        }
    }
    else cout<<"Wrong identity!"<<endl;
    return 0;
}

void Explorer::Input(){
    cout<<"Please enter the book information you want to input!"<<endl;
    cin>>kind>>code;
    if(kind=="图书"){
        cin>>ISBN>>name>>press>>writer[0]>>kind1>>path>>keeper>>status;
        BOOK.insert(pair<string, string>(name,code));
        STR[i++]=name;
    }
    else if(kind=="论文"){
        cin>>title>>NumOfWr;
        for(int j=0;j<NumOfWr;++j){
            cin>>writer[j];
        }
        cin>>periodical>>Time>>kind1>>path>>keeper>>status;
        BOOK.insert(pair<string, string>(title,code));
        STR[i++]=title;
    }
    else cout<<"Donot have this kind!"<<endl;
    fstream out;
    string str;
    str=catalogue+code+".txt";
    out.open(str,ios::in|ios::out|ios::app);
    if(!out.is_open()){
        out<<"Error! cannot set up this file!"<<endl;
    }
    else{
        if(kind=="图书"){
            out<<"图书"<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(kind=="论文"){
            out<<"论文"<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int i=0;i<NumOfWr;++i){
                out<<writer[i]<<endl;
            }
            out<<periodical<<endl<<Time<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
    }
    out.close();
}

void Explorer::Delete(){
    string Name;
    cout<<"Please enter the name of the book or paper you want to delete!"<<endl;
    cin>>Name;
    string str;
    auto iter=BOOK.find(Name);
    str=catalogue+iter->second+".txt";
    const char *s=str.c_str();
    remove(s);
}

void Explorer::Search(){
    string Name;
    cout<<"Please enter the name of the book or paper you want to search!"<<endl;
    cin>>Name;
    bool flag=false;
    for(int j=0;j<i;++j){
        if(STR[j].npos!=STR[j].find(Name)){
            flag=true;
            auto iter=BOOK.find(STR[j]);
            string str;
            str=catalogue+iter->second+".txt";
            fstream read;
            read.open(str,ios::in);
            read>>kind>>code;
            if(kind=="图书"){
            read>>ISBN>>name>>press>>writer[0]>>kind1>>path>>keeper>>status;
            cout<<name<<" "<<press<<" "<<writer[0]<<" "<<path<<" "<<status<<endl;
            }
            else if(kind=="论文"){
                read>>title>>NumOfWr;
                for(int j=0;j<NumOfWr;++j){
                    read>>writer[j];
                }
                read>>periodical>>Time>>kind1>>path;
                cout<<title<<" "<<periodical<<" ";
                for(int j=0;j<NumOfWr;++j){
                    cout<<writer[j]<<" ";
                }
                cout<<path<<" "<<status<<endl;
            }
            read.close();
        }
    }
    if(!flag) cout<<"Not found!"<<endl;
}

void Account::Borrow(string keeper){
    int sta=0;
    ifstream in;
    string name,path,kind,code,kind1,periodical,ISBN,press,writer[64],title,Time,Name,str1;
    int NumOfWr=0;
    cout<<"Please enter the name of the book or paper you want to borrow!"<<endl;
    cin>>Name;
    auto iter1=BOOK.find(Name);
    str1=catalogue+iter1->second+".txt";
    const char *p1=str1.c_str();
    in.open(p1,ios::in);
    if(!in.is_open()) cout<<"Cannot open the book file!"<<endl;
    in.seekg(-1,ios_base::end);
    in>>sta;
    if(!sta){
        in.seekg(0,ios_base::beg);
        in>>kind;
        if(kind=="图书"){
            in>>code>>ISBN>>name>>press>>writer[0]>>kind1>>path;
        }
        else{
            in>>code>>title>>NumOfWr;
            for(int j=0;j<NumOfWr;++j){
                in>>writer[j];
            }
            in>>periodical>>Time>>kind1>>path;
        }
        ofstream bor;
        bor.open(p1,ios::ate|ios::out);
        bor.seekp(0,ios_base::beg);
        if(kind=="图书"){
            bor<<kind<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl;
        }
        else{
            bor<<kind<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                bor<<writer[j]<<endl;
            }
            bor<<periodical<<endl<<Time<<endl<<kind1<<endl<<path<<endl;
        }
        bor<<keeper<<endl<<1;
        bor.close();
    }
    else if(sta==1) cout<<"The book has been borrowed!"<<endl;
    else if(sta==2) cout<<"The book status is abnormal!"<<endl;
    else cout<<"Wrong status!"<<endl;
    in.close();
}

void Account::Return(string keeper){
    string name,path,kind,code,kind1,periodical,ISBN,press,writer[64],title,Time;
    int NumOfWr=0;
    cout<<"Please enter the name of the book or paper you want to return!"<<endl;
    cin>>name;
    auto iter2=BOOK.find(name);
    ifstream in;
    string str2;
    str2=catalogue+iter2->second+".txt";
    const char *p2=str2.c_str();
    in.open(p2,ios::in);
    in.seekg(0,ios_base::beg);
        in>>kind;
        if(kind=="图书"){
            in>>code>>ISBN>>name>>press>>writer[0]>>kind1>>path;
        }
        else{
            in>>code>>title>>NumOfWr;
            for(int j=0;j<NumOfWr;++j){
                in>>writer[j];
            }
            in>>periodical>>Time>>kind1>>path;
        }
        ofstream ret;
        ret.open(p2,ios::ate|ios::out);
        ret.seekp(0,ios_base::beg);
        if(kind=="图书"){
            ret<<kind<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl;
        }
        else{
            ret<<kind<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                ret<<writer[j]<<endl;
            }
            ret<<periodical<<endl<<Time<<endl<<kind1<<endl<<path<<endl;
        }
        ret<<"无"<<endl<<0;
        ret.close();
}

void Explorer::OnlineReading(){
    string Name;
    cout<<"Please enter the name of the book or paper you want to Onlineread!"<<endl;
    cin>>Name;
    auto iter3=BOOK.find(Name);
    string str3;
    str3=catalogue+iter3->second+".txt";
    fstream view;
    const char *p3=str3.c_str();
    view.open(p3,ios::in);
    view>>str3;
    if(str3=="论文"){
        view>>code>>name>>NumOfWr;
        for(int j=0;j<NumOfWr;++j){
            view>>writer[j];
        }
        view>>periodical>>Time>>kind1;
    }
    else{
        view>>str3>>str3>>str3>>str3>>str3>>str3;
    }
    if(str3=="实体书")   cout<<"Do not have electronic resourse!"<<endl;
    else {
        view>>str3;
        str3="OPEN "+str3;
        p3=str3.c_str();
        system(p3);
    }
    view.close();
}

void AccountManagement::AddUser(){
    UNAME[l++]=username;
    fstream SU;
    string str4=catalogue+username+".txt";
    const char *p4=str4.c_str();
    SU.open(p4,ios::in|ios::app|ios::out);
    if(!SU.is_open()) cout<<"cannot set up this Account!"<<endl;
    else{
        SU<<identity<<endl<<name<<endl<<username<<endl<<passcode;
    }
    SU.close();
}

void AccountManagement::DeleteUser(){
    string Name,str5;
    bool flag=false;
    cout<<"Please enter the username of the account you want to delete!"<<endl;
    cin>>Name;
    for(int j=0;j<l;++j){
        if(UNAME[j]==Name){
            flag=true;
            break;
        }
    }
    if(flag){
        str5=catalogue+Name+".txt";
        const char *p5=str5.c_str();
        remove(p5);
    }
    else cout<<"Wrong Name!"<<endl;
}

string AccountManagement::Judge(){
    bool flag =false;
    cout<<"Please enter your username!"<<endl;
    cin>>username;
    cout<<"Please enter your passcode!"<<endl;
    cin>>passcode;
    for(int j=0;j<l;++j){
        if(UNAME[j]==username){
            flag=true;
            break;
        }
    }
    string str6=catalogue+username+".txt",s="";
    if(!flag) {
        cout<<"Donot have this username!"<<endl;
        return s;
    }
    fstream Am;
    const char *p6=str6.c_str();
    Am.open(p6,ios::in);
    if(!Am.is_open()) {
        cout<<"cannot open account file!"<<endl;
        return s;
    }
    else{
        string UN,P;
        Am>>identity>>UN>>UN>>P;
        if((UN==username)&&(P==passcode)) cout<<"Correct!"<<endl;
        else{
            cout<<"Wrong! Please try it again!"<<endl;
            Judge();
        }
    }
    return identity;
}

void Explorer::View(){
    cout<<"Please enter the book information you want to View!"<<endl;
    cin>>name;
    auto iter3=BOOK.find(name);
    string str6=catalogue+iter3->second+".txt";
    fstream read;
    read.open(str6,ios::in);
    read>>kind>>code;
    if(kind=="图书"){
        read>>ISBN>>name>>press>>writer[0]>>kind1>>path>>keeper>>status;
        cout<<kind<<" "<<code<<" "<<ISBN<<" "<<name<<" "<<press<<" "<<writer[0]<<" "<<kind1<<" "<<path<<" "<<keeper<<" "<<status<<endl;
    }
    else if(kind=="论文"){
        read>>title>>NumOfWr;
        for(int j=0;j<NumOfWr;++j){
            read>>writer[j];
        }
        read>>periodical>>Time>>kind1>>path>>keeper>>status;
        cout<<kind<<" "<<code<<" "<<title<<" "<<NumOfWr<<" ";
        for(int j=0;j<NumOfWr;++j){
            cout<<writer[j]<<" ";
        }
        cout<<periodical<<" "<<Time<<" "<<kind1<<" "<<path<<" "<<keeper<<" "<<status<<endl;
    }
    read.close();
}

void Explorer::Update(){
    cout<<"What book and what attribute you want to update?And update to what?"<<endl;
    string book,Attributes,New;
    cin>>book>>Attributes>>New;
    auto iter4=BOOK.find(book);
    string str7=catalogue+iter4->second+".txt";
    fstream upd;
    upd.open(str7,ios::in);
    upd>>kind>>code;
    if(kind=="图书"){
        upd>>ISBN>>name>>press>>writer[0]>>kind1>>path>>keeper>>status;
    }
    else if(kind=="论文"){
        upd>>title>>NumOfWr;
        for(int j=0;j<NumOfWr;++j){
            upd>>writer[j];
        }
        upd>>periodical>>Time>>kind1>>path>>keeper>>status;
    }
    ofstream updt;
    const char *temp=str7.c_str();
    remove(temp);
    //updt.seekp(0,ios_base::beg);
    if(kind=="图书"){
        if(Attributes=="code"){
            str7=catalogue+New+".txt";
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<New<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="ISBN"){
           updt.open(str7,ios::app|ios::out|ios::in); updt<<kind<<endl<<code<<endl<<New<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="name"){
           updt.open(str7,ios::app|ios::out|ios::in); updt<<kind<<endl<<code<<endl<<ISBN<<endl<<New<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="press"){
           updt.open(str7,ios::app|ios::out|ios::in); updt<<kind<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<New<<endl<<writer[0]<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="writer"){
           updt.open(str7,ios::app|ios::out|ios::in); updt<<kind<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<New<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="path"){
           updt.open(str7,ios::app|ios::out|ios::in); updt<<kind<<endl<<code<<endl<<ISBN<<endl<<name<<endl<<press<<endl<<writer[0]<<endl<<kind1<<endl<<New<<endl<<keeper<<endl<<status;
        }
        else cout<<"This attribute cannot be updated!"<<endl;
    }
    else if(kind=="论文"){
        if(Attributes=="code"){
            str7=catalogue+New+".txt";
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<New<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                updt<<writer[j]<<endl;
            }
            updt<<periodical<<endl<<Time<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="title"){
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<code<<endl<<New<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                updt<<writer[j]<<endl;
            }
            updt<<periodical<<endl<<Time<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="periodical"){
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                updt<<writer[j]<<endl;
            }
            updt<<New<<endl<<Time<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="time"){
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                updt<<writer[j]<<endl;
            }
            updt<<periodical<<endl<<New<<endl<<kind1<<endl<<path<<endl<<keeper<<endl<<status;
        }
        else if(Attributes=="path"){
            updt.open(str7,ios::app|ios::out|ios::in);
            updt<<kind<<endl<<code<<endl<<title<<endl<<NumOfWr<<endl;
            for(int j=0;j<NumOfWr;++j){
                updt<<writer[j]<<endl;
            }            updt<<periodical<<endl<<Time<<endl<<kind1<<endl<<New<<endl<<keeper<<endl<<status;
        }
        else cout<<"This attribute cannot be updated!"<<endl;
    }
}

Book::Book(string Name,string Path,string Kind,string Code,string Kind1,string isbn,string Press,string Writer,string Keeper,int Status){
    name=Name;path=Path;kind=Kind;code=Code;kind1=Kind1;
    ISBN=isbn;press=Press;writer=Writer;keeper=Keeper;status=Status;
}

Account::Account(string Name,string Username,string Passcode,string Identity,string Catalogue){
    name=Name;username=Username;passcode=Passcode;identity=Identity;
    catalogue=Catalogue;
}

AccountManagement::AccountManagement(string Name,string Username,string Passcode,string Identity,string Catalogue){
    name=Name;username=Username;passcode=Passcode;identity=Identity;
    catalogue=Catalogue;
}

Paper::Paper(string Name,string Path,string Kind,string Code,string Kind1,string Periodical,string Writer[64],string Keeper,string Title,string TIME,int NUM,int Status){
    name=Name;path=Path;kind=Kind;code=Code;kind1=Kind1;periodical=Periodical;
    //Writer
    keeper=Keeper;title=Title;Time=TIME;NumOfWr=NUM;status=Status;
}

Explorer::Explorer(string Catalogue){
    catalogue=Catalogue;
}


