//
//  Created by Daniel Sodkiewicz on 3/22/14.
//  Copyright (c) 2014 Daniel Sodkiewicz. All rights reserved.
//
// https://www.youtube.com/watch?v=-U7c_y5ks30
// to test http://www.coolmath-games.com/0-pegsolitaire/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <fstream>

using namespace std;

// functions declaration
void legal (int array[], int, int, int);
bool findsolution ();
void isfinal (int array[]);
void showboard ();
void makejumpback(int, int);
int nrpos=0;

stack <int> steps;

// HASH
//http://www.onextrabit.com/view/502c152965e7d250c5000001

template <typename T>
class SimpleHash {
private:
    // data
    T* m_pData;
    // hash table size
    unsigned int m_size;
    
    // djb2 hash function
    unsigned int djb2(const char* key) {
        unsigned int hash = 5381;
        
        for (unsigned int i = 0; i < strlen(key); i++)
            hash = ((hash << 5) + hash) + (unsigned int)key[i];
        
        return hash % m_size;
    }
    
public:
    SimpleHash(unsigned int size): m_size(size) {
        // init hash table data given table size
        m_pData = new T[m_size];
    }
    
    ~SimpleHash() {
        delete[] m_pData;
    }
    
    void set(const char* key, const T& value) {
        unsigned int index = djb2(key);
    //    std::cout << "set " << index << ": " << value  << std::endl;
        m_pData[index] = value;
    }
    
    T get(const char* key) {
        unsigned int index = djb2(key);
  //      std::cout << "get " << index << std::endl;
        return m_pData[index];
    }
};

SimpleHash<int> myhash(999999999);

// board

/*
int board[7][7] = {
    {2,2,1,1,1,2,2},
    {2,2,1,1,1,2,2},
    {1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1},
    {2,2,1,1,1,2,2},
    {2,2,1,1,1,2,2}
};
*/
int board[7][7] = {
    {2,2,1,1,1,2,2},
    {2,2,1,1,1,2,2},
    {1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1},
    {2,2,1,1,1,2,2},
    {2,2,1,1,1,2,2}
};


/*

 int board[7][7] = {
 {2,2,1,1,0,2,2},
 {2,2,0,1,1,2,2},
 {0,0,0,0,0,1,0},
 {0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0},
 {2,2,0,0,0,2,2},
 {2,2,0,0,0,2,2}
 };

 */


void showboard() {
    int n;
    for(int a = 0; a<7; a++) {
        for(int b = 0; b<7;b++) {
            n = board[a][b];
            if (n==2)cout <<" ";
            else cout << n;
        }
        cout<< endl;
    }
    
}

bool legal (int board[7][7], int a, int b, int dir)
{
   
    int ok = 1;
    
    if (dir==1) { if (a==0 || a==1
                      || (a==2 && b ==0) || (a==2 && b ==1)
                      || (a==2 && b ==5) || (a==2 && b ==6)
                      || (a==3 && b ==0) || (a==3 && b ==1)
                      || (a==3 && b ==5) || (a==3 && b ==6) ) ok = 0; }
    
    if (dir==2) { if (a==5 || a==6
                      || (a==4 && b ==0) || (a==4 && b ==1)
                      || (a==4 && b ==5) || (a==4 && b ==6)
                      || (a==3 && b ==0) || (a==3 && b ==1)
                      || (a==3 && b ==5) || (a==3 && b ==6) ) ok = 0; }
    if (dir==3) { if (b==5 || b==6
                      || (a==0 && b ==3) || (a==1 && b ==3)
                      || (a==5 && b ==3) || (a==6 && b ==3)
                      || (a==0 && b ==4) || (a==1 && b ==4)
                      || (a==5 && b ==4) || (a==6 && b ==4) ) ok = 0; }
    if (dir==4) { if (b==0 || b==1
                      || (a==0 && b ==3) || (a==1 && b ==3)
                      || (a==5 && b ==3) || (a==6 && b ==3)
                      || (a==0 && b ==2) || (a==1 && b ==2)
                      || (a==5 && b ==2) || (a==6 && b ==2) ) ok = 0; }
    
   
    if (ok)
    {
    
         //N
         if (dir==1) { if ( board[a][b]==1 && board[a-1][b]==1 && board[a-2][b]==0) return true;
         else return false;
        }
        // S
           if (dir==2) { if (  board[a][b]==1 && board[a+1][b]==1 && board[a+2][b]==0) return true;
            else return false;
           }
         //E
           if (dir==3) { if (  board[a][b]==1 && board[a][b+1]==1 && board[a][b+2]==0) return true;
           else return false;
           }
         //W
           if (dir==4) { if ( board[a][b]==1 && board[a][b-1]==1 && board[a][b-2]==0) return true;
          else return false;
           }
       
    
    }
    return false;
}

void makejump (int a, int b, int dir)
{
    
    
    switch (dir)
    {
        case 1: //N
            board[a][b]=0 ; board[a-1][b]=0; board[a-2][b]=1;
            break;
        case 2: //S
            board[a][b]=0 ; board[a+1][b]=0; board[a+2][b]=1;
            break;
        case 3: //E
            board[a][b]=0 ; board[a][b+1]=0; board[a][b+2]=1;
            break;
        case 4: //W
            board[a][b]=0 ; board[a][b-1]=0; board[a][b-2]=1;
            break;
        default: cout << "qwerty";
            break;
    }
    
}

bool isfinal (int boardw[7][7])
{
 
    
    if (
        
        boardw[0][2]==0 &&
        boardw[0][3]==0 &&
        boardw[0][4]==0 &&
        
        boardw[1][2]==0 &&
        boardw[1][3]==0 &&
        boardw[1][4]==0 &&
        
        boardw[2][0]==0 &&
        boardw[2][1]==0 &&
        boardw[2][2]==0 &&
        boardw[2][3]==0 &&
        boardw[2][4]==0 &&
        boardw[2][5]==0 &&
        boardw[2][6]==0 &&
        
        boardw[3][0]==0 &&
        boardw[3][1]==0 &&
        boardw[3][2]==0 &&
        boardw[3][3]==1 &&
        boardw[3][4]==0 &&
        boardw[3][5]==0 &&
        boardw[3][6]==0 &&
        
        boardw[4][0]==0 &&
        boardw[4][1]==0 &&
        boardw[4][2]==0 &&
        boardw[4][3]==0 &&
        boardw[4][4]==0 &&
        boardw[4][5]==0 &&
        boardw[4][6]==0 &&
        
        boardw[5][2]==0 &&
        boardw[5][3]==0 &&
        boardw[5][4]==0 &&
        
        boardw[6][2]==0 &&
        boardw[6][3]==0 &&
        boardw[6][4]==0
        ) {
        return true; }
    else {
   
        return false;
    }
    
}

bool findsolution ()
{
    
  
    if (isfinal(board))
        return true;
    else {
     
        // try next possibility
    
        for (int a =0; a <= 6; a++)
        {
            for (int b=0; b <= 6; b++)
            {
                for (int c=1; c <= 4; c++)
                {
                    
                if (legal(board,a,b,c))
                {
                    
                    // create local copy array to go back here
                    int locatArray[7][7];
                    
                    copy(&board[0][0], &board[6][6], &locatArray[0][0]);
                    
                    makejump(a,b,c);
                    steps.push(a);
                    steps.push(b);
                    steps.push(c);
                    cout<< "Making move:" <<endl;
                    showboard();
                    cout<< "----------" <<endl;
                    
                    
                    int Number=0;
                    string Result ="";          // string which will contain the result
                    
                    for(int x = 0; x<7; x++) {
                        for(int y = 0; y<7;y++) {
                    
                            Number = board[x][y];
             
                            
                              Result +=  to_string(Number);
              
                            }
                        
                        }
                    
                    Result+=to_string(a);
                    Result+=to_string(b);
                    Result+=to_string(c);
       
                    const char *cstr = Result.c_str();
                    
                   
                    int wasnotbefore=1;
                    
                    if(myhash.get(cstr)) {
                        wasnotbefore=0;
                        cout<< "This state was before:"<<endl;
                        showboard();
                        cout<< "----------" <<endl;
                    }
                    
                    
                    nrpos++;
                    
        
                         if (wasnotbefore && (steps.size()<=93) )
                    {
               
                        myhash.set(cstr, nrpos);
                        
               
                    if (findsolution()) return true;
                    else {
                
                        copy(&locatArray[0][0], &locatArray[6][6], &board[0][0]);
                        steps.pop();steps.pop();steps.pop();
       
                        cout<< "Move step back:" <<endl;
                        showboard();
                        cout<< "----------" <<endl;
                    }
                        
                    } else
                        {
                        copy(&locatArray[0][0], &locatArray[6][6], &board[0][0]);
                        steps.pop();steps.pop();steps.pop();
                            cout<< "Move step back:" <<endl;
                            showboard();
                            cout<< "----------" <<endl;
                        }
                   
                    
                }
                }
           
            }
           
        }
    
          
        
        return false;
    }
    
}


int main(int argc, const char * argv[])
{

    cout << "Initial board:" <<endl;
    showboard();
    

    findsolution();
    cout << "Final board:" <<endl;
    showboard();
    
    
    int i=0;
    int a, b ,c;
    string cc="";
    cout<< "------------------"<<endl;
    cout<< "SOLUTION"<<endl;
    cout<< "------------------"<<endl<<endl;
    cout<< "BOARD:"<<endl;
    cout<< " ----------x--------"<<endl;
    cout<< "|     1 2 3 4 5 6 7 "<<endl;
    cout<< "|    ---------------"<<endl;
    cout<< "| 1 |     _ _ _    "<<endl;
    cout<< "| 2 |     _ _ _    "<<endl;
    cout<< "| 3 | _ _ _ _ _ _ _"<<endl;
    cout<< "y 4 | _ _ _ _ _ _ _"<<endl;
    cout<< "| 5 | _ _ _ _ _ _ _"<<endl;
    cout<< "| 6 |     _ _ _    "<<endl;
    cout<< "| 7 |     _ _ _    "<<endl<<endl<<endl;
    cout<< "DIRECTION:"<<endl;
    cout<< "    N    "<<endl;
    cout<< "    ^    "<<endl;
    cout<< "    |    "<<endl;
    cout<< " W ---> E"<<endl;
    cout<< "    |    "<<endl;
    cout<< "    S    "<<endl<<endl;
    
    cout<< "------------------"<<endl<<endl;
    cout<< "STEPS:"<<endl<<"Read from bottom to top"<<endl<<endl;
    cout<< "------------------"<<endl;
    cout<< "YX Direction"<<endl;
    cout<< "------------------"<<endl;
    while (!steps.empty()) {
        c = steps.top();
        steps.pop();
        
        b= steps.top();
        steps.pop();
        
        a = steps.top();
        steps.pop();
        if (c==1) cc = "N";
        if (c==2) cc = "S";
        if (c==3) cc = "E";
        if (c==4) cc = "W";
            cout<< a+1<< b+1<<" "<< cc<< endl;
     
        i++;
    }
   
                                 
    return 0;
}

