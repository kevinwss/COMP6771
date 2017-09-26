#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <deque>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void solve(stack<string> &mystack,string &s,int &repeat_times,bool &is_repeat,vector<string> &record){
    if(isdigit(s[0])){
            if(is_repeat==true){record.push_back(s);return;}
            mystack.push(s);
        }
        else if (s=="add"){ //"add" case:b+a
            if(is_repeat==true){record.push_back(s);return;}
            string b = mystack.top();
            mystack.pop();
            string a = mystack.top();
            mystack.pop();
            bool aDouble = false;
            bool bDouble = false;
            if(a.find('.') != string::npos)aDouble=true;
            if(b.find('.') != string::npos)bDouble=true;

            double num1 = stod(b);
            double num2 = stod(a);

            if(aDouble==true or bDouble==true){ //The case that any input is double
                double ans = num1+num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str+".");
                if(aDouble==false and bDouble==true){cout<<num1<<" + "<<a<<" = "<<ans<<endl;}
                else if(aDouble==true and bDouble==false){cout<<b<<" + "<<num2<<" = "<<ans<<endl;}
                else {cout<<num1<<" + "<<num2<<" = "<<ans<<endl;}

            }else{ //The case that no input is double
                int ans = num1+num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str);
                cout<<b<<" + "<<a<<" = "<<ans<<endl;

            }
        }
       else if (s=="sub"){//"sub" case:b-a
            if(is_repeat==true){record.push_back(s);return;}
            string b = mystack.top();
            mystack.pop();
            string a = mystack.top();
            mystack.pop();
            bool aDouble = false;
            bool bDouble = false;
            if(a.find('.') != string::npos)aDouble=true;
            if(b.find('.') != string::npos)bDouble=true;

            double num1 = stod(b);
            double num2 = stod(a);

            if(aDouble==true or bDouble==true){//The case that any input is double
                double ans = num1-num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str+".");
                if(aDouble==false and bDouble==true){cout<<num1<<" - "<<a<<" = "<<ans<<endl;}
                else if(aDouble==true and bDouble==false){cout<<b<<" - "<<num2<<" = "<<ans<<endl;}
                else {cout<<num1<<" - "<<num2<<" = "<<ans<<endl;}

            }else{ //The case that no input is double
                int ans = num1-num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str);
                cout<<b<<" - "<<a<<" = "<<ans<<endl;

            }
        }
        else if (s=="mult"){//"mult" case b*a
            if(is_repeat==true){record.push_back(s);return;}
            string b = mystack.top();
            mystack.pop();
            string a = mystack.top();
            mystack.pop();
            bool aDouble = false;
            bool bDouble = false;
            if(a.find('.') != string::npos)aDouble=true;
            if(b.find('.') != string::npos)bDouble=true;

            double num1 = stod(b);
            double num2 = stod(a);

            if(aDouble==true or bDouble==true){//The case that any input is double
                double ans = num1*num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str+".");
                if(aDouble==false and bDouble==true){cout<<num1<<" * "<<a<<" = "<<ans<<endl;}
                else if(aDouble==true and bDouble==false){cout<<b<<" * "<<num2<<" = "<<ans<<endl;}
                else {cout<<num1<<" * "<<num2<<" = "<<ans<<endl;}

            }else{//The case that no input is double
                int ans = num1*num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str);
                cout<<b<<" * "<<a<<" = "<<ans<<endl;

            }
        }
        else if (s=="div"){//"div" case b/a
            if(is_repeat==true){record.push_back(s);return;}
            string b = mystack.top();
            mystack.pop();
            string a = mystack.top();
            mystack.pop();

            bool aDouble = false;
            bool bDouble = false;
            if(a.find('.') != string::npos)aDouble=true;
            if(b.find('.') != string::npos)bDouble=true;

            double num1 = stod(b);
            double num2 = stod(a);

            if(aDouble==true or bDouble==true){
                double ans = num1/num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str+".");

                if(aDouble==false and bDouble==true){cout<<num1<<" / "<<a<<" = "<<ans<<endl;}
                else if(aDouble==true and bDouble==false){cout<<b<<" / "<<num2<<" = "<<ans<<endl;}
                else {cout<<num1<<" / "<<num2<<" = "<<ans<<endl;}

            }else{
                int ans = num1/num2;
                ostringstream oss;
                oss<<ans;
                string str = oss.str();
                mystack.push(str);
                cout<<b<<" / "<<a<<" = "<<ans<<endl;

            }
        }
    else if (s=="sqrt"){
            if(is_repeat==true){record.push_back(s);return;}

            bool bDouble = false;
            string b = mystack.top();
            mystack.pop();
            if(b.find('.') != string::npos)bDouble=true;

            double num1 = stod(b);
            double ans = sqrt(num1);

            if(bDouble==true){//The case that input is double
            ostringstream oss;
            oss<<ans;
            string str = oss.str();
            mystack.push(str+".");
            cout<<"sqrt "<<num1<<" = "<<ans<<endl;}
            else{//The case that input is not double
            ostringstream oss;
            oss<<int(ans);
            string str = oss.str();
            mystack.push(str);
            cout<<"sqrt "<<b<<" = "<<int(ans)<<endl;
            }
        }

    else if (s=="pop"){
    if(is_repeat==true){record.push_back(s);return;}
    mystack.pop();}

    else if (s=="reverse"){
        if(is_repeat==true){record.push_back(s);return;}
        int reverse_n = stoi(mystack.top());
        mystack.pop();
        deque<string> reverse_deque;
        for (int i=0;i<reverse_n;i++){
            reverse_deque.push_front(mystack.top());
            mystack.pop();

        }
        for (int i=0;i<reverse_n;i++){

            mystack.push(reverse_deque.back());
            reverse_deque.pop_back();

        }
    }
    else if (s=="repeat"){//Use a recording stack to store the steps between "repeat" and "endrepeat"
        repeat_times =stoi(mystack.top());
        mystack.pop();
        is_repeat = true;

    }
    else if (s=="endrepeat"){//Dealing with the steps between "repeat" and "endrepeat"
        is_repeat = false;

        for(int i=0;i<repeat_times;i++){// In each repeat time, do the process recorded in stack
            for(unsigned int iter=0;iter<record.size();iter++)solve(mystack,record[iter],repeat_times,is_repeat,record);
        }
        record.clear();

            }
}

int main(int argc, char* argv[]) {
	// setup the print out format for the precision required.
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
	// open the file for reading
	ifstream in;
	in.open(argv[1]);
	// string to be read into
	string s;
    stack<string> mystack;
    vector<string> record;
    int repeat_times = 0;
    bool is_repeat = false;
	// read the file while we have input.
	while (in >> s) {
        solve(mystack,s,repeat_times,is_repeat,record);
	}
	in.close();
}
