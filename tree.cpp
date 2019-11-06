#include <iostream>
#include <list>
using namespace std;
#include "tree.h"
#include "board.h"

tree :: tree(){
  root = new board();//intialize new board
  root->display();
  curr = root;
  curr->prev = 0;
  
}
/*
1)	Uniform Cost Search 
2)	A* with the Misplaced Tile heuristic.
3)	A* with the Manhattan Distance heuristic.

*/
void tree :: createBoard(){
  int userInput;  
  int counter = 1;
  cout<<"Please enter numbers 0-9, with 0 being the blank space, NO REPEATS: " <<endl;
  for(int i =0; i<3; ++i){
    for(int j =0; j<3; ++j){
      cout<<"Enter Number at " <<counter <<": ";
      cin>>userInput;
      if(userInput == 0){
        root->row = i;
        root->col = j;
      }
      root->arr[i][j]=userInput;
      ++counter;
    }
  }
  cout<<endl <<endl;
  cout<<"Enter Heuristic Function"<<endl;
  cout<<"1)	Uniform Cost Search"<<endl;
  cout<<"2)	A* with the Misplaced Tile heuristic"<<endl;
  cout<<"3)	A* with the Manhattan Distance heuristic."<<endl;
}

void tree :: goUp(){//current pos in tree
 if(curr->validMove('w')) {
    board* temp = new board(curr);//create new temp
    board* tempParent = new board(curr);//for previous
    temp->moveUp();//temp move up
    curr->up = temp;//set current up to new moved temp
    //now switch current to the one we just moved too    
    curr = temp;
    curr->prev = tempParent;
    //prevNode = tempParent;
    
    tempParent = NULL;
    // delete tempParent; 
    temp = NULL;//set to null then delete temp
    // delete temp;
 } 
}

void tree :: goDown(){//current pos in tree
  if(curr->validMove('s')) {
    board* temp = new board(curr);//create new temp
    board* tempParent = new board(curr);//for previous
    
    temp->moveDown();//temp move down
    curr->down=temp;//set current down to new moved temp
    //now switch current to the one we just moved too

    curr = temp;
    curr->prev = tempParent;

    tempParent = NULL;
    // delete tempParent; 
    temp = NULL;//set to null then delete temp
    // delete temp; 
  }
}
void tree :: goLeft(){//current pos in tree
  if(curr->validMove('a')) {
    board* temp = new board(curr);//create new temp
    board* tempParent = new board(curr);//for previous
    temp->moveLeft();//temp move left
    curr->left=temp;//set current left to new moved temp
    //now switch current to the one we just moved too

    curr = temp;
    curr->prev = tempParent;
    // cout<<"flag"<<endl;
    
    tempParent = NULL;
    // delete tempParent; 
    temp = NULL;//set to null then delete temp
    // delete temp; 
    
  }
}
void tree :: goRight(){//current pos in tree
  if(curr->validMove('d')) {
    board* temp = new board(curr);//create new temp
    board* tempParent = new board(curr);//for previous
    temp->moveRight();//temp move right
    curr->right=temp;//set current right to new moved temp
    //now switch current to the one we just moved too
    curr = temp;
    curr->prev = tempParent;
    
    tempParent = NULL;
    // delete tempParent; 
    temp = NULL;//set to null then delete temp
    // delete temp; 
  }
}
void tree :: displayBoard(){
  cout<<"Displaying From the Root"<<endl;
  root->display();
  displayBoard(root);
}

void tree :: displayBoard(board* cur){
  if(cur->up != 0){
    cout<<"went up"<<endl;
    cur->up->display();
    displayBoard(cur->up); 
  }
  else if(cur->down != 0){
    cout<<"went down"<<endl;
    cur->down->display();
    displayBoard(cur->down); 
  }
  else if(cur->left != 0){
    cout<<"went left"<<endl;
    cur->left->display();
    displayBoard(cur->left); 
  }
  else if(cur->right != 0){
    cout<<"went right"<<endl;
    cur->right->display();
    displayBoard(cur->right); 
  }
}
/*
b.push_back(curr);
*/
bool tree:: expand(board* r, vector <board*> &b, int heuristic){
  vector <char> c = r->legalMoves();//store all the legal moves

  for(int i =0 ; i<c.size();++i){//shows legal moves
    cout<<c.at(i)<<endl;
  }
  
  cout<<endl <<"current board"<<endl;
  r->display();

  board* check = new board(r);
  string checkTemp = check->getHash();

  if(r->getHashGoal() == checkTemp){//if its goal state is now then return
    cout<<"at goal state"<<endl;
    check->display();
    return true;
  }

  for(int i=0; i<c.size(); ++i){//goes through all actions
    
    if(c.at(i)=='w'){//check up
      
      board* temp = new board(r);//set temp val of current node
      temp->moveUp();//do the action of moving up
      string sTemp = temp->getHash();//get the hash of the node
      // cout <<sTemp<<endl;
      
      if(r->getHashGoal() == sTemp){//if that is the goal state then return
        cout<<"at goal state"<<endl;
        temp->display();
        return true;
      }
      
      if(blacklist->find(sTemp) == blacklist->end()){//did not find hash of up
        cout<<"up SUCC"<<endl;
        this->goUp();//do moving action
        curr->addScore(heuristic, curr->depth);
        b.push_back(curr);//push it back into problems
        curr = curr->prev;
        cout<<"Mapping this Hash: " <<sTemp<<endl;
        blacklist->insert(pair<string,bool>(sTemp,true));
      
        if(blacklist->find(sTemp) != blacklist->end()){
          cout<<endl<<endl <<"Black List is accepted"<<endl<<endl;
        }
        cout<<"blacklist size: "<<blacklist->size() <<endl;;
      }


    }
    if(c.at(i)=='s'){
      board* temp = new board(r);//set temp val;
      temp->moveDown();
      string sTemp = temp->getHash();
      // cout <<sTemp<<endl;
      if(r->getHashGoal() == sTemp){//checking the hash
        temp->display();
        return true;
      }
      if(blacklist->find(sTemp) == blacklist->end()){
        cout<<"down SUCC"<<endl;
        this->goDown();
        curr->addScore(heuristic, curr->depth);
        b.push_back(curr);
        
        curr = curr->prev;
        cout<<"Mapping this Hash: " <<sTemp<<endl;
        blacklist->insert(pair<string,bool>(sTemp,true));
        if(blacklist->find(sTemp) != blacklist->end()){
          cout<<endl<<endl <<"Black List is accepted"<<endl<<endl;
        }
        cout<<"blacklist size: "<<blacklist->size() <<endl;;
      }
    }
    if(c.at(i)=='a'){
      board* temp = new board(r);//set temp val;
      temp->moveLeft();
      string sTemp = temp->getHash();
      // cout <<sTemp<<endl;
      if(r->getHashGoal() == sTemp){//checking the hash
        temp->display();
        return true;
      }
      if(blacklist->find(sTemp) == blacklist->end()){
        // cout<<"whattt"<<endl;
        cout<<"left SUCC"<<endl;
        this->goLeft();
        curr->addScore(heuristic, curr->depth);
        // curr->display();
        cout<<b.size()<<endl;
        // cout<<"whattt"<<endl;
        
        b.push_back(curr);//this line of code is messed up
        
        curr = curr->prev;
        cout<<"Mapping this Hash: " <<sTemp<<endl;
        blacklist->insert(pair<string,bool>(sTemp,true));
        if(blacklist->find(sTemp) != blacklist->end()){
          cout<<endl<<endl <<"Black List is accepted"<<endl<<endl;
        }
        cout<<"blacklist size: "<<blacklist->size() <<endl;;
        // cout<<"NO"<<endl;
        
        
      }
    }
    if(c.at(i)=='d'){
      
      board* temp = new board(r);//set temp val;
      temp->moveRight();
      string sTemp = temp->getHash();
      // cout <<sTemp<<endl;
      if(r->getHashGoal() == sTemp){//checking the hash
        temp->display();
        return true;
      }
      if(blacklist->find(sTemp) == blacklist->end()){
        cout<<"right SUCC"<<endl;
        this->goRight();
        curr->addScore(heuristic, curr->depth);
        b.push_back(curr);
        curr = curr->prev;
        cout<<"Mapping this Hash: " <<sTemp<<endl;
        blacklist->insert(pair<string,bool>(sTemp,true));
        if(blacklist->find(sTemp) != blacklist->end()){
          cout<<endl<<endl <<"Black List is accepted"<<endl<<endl;
        }
        cout<<"blacklist size: "<<blacklist->size() <<endl;
      }
    }
  }

  for(int i = 0; i<b.size(); ++i){
    b.at(i)->display();
  }

  
  return false;
  
}
/*
function general-search(problem, QUEUEING-FUNCTION)  
nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE)) 
loop do
 if EMPTY(nodes) then return "failure" 
   node = REMOVE-FRONT(nodes) 
 if problem.GOAL-TEST(node.STATE) succeeds then return node
    nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))  
 end
*/