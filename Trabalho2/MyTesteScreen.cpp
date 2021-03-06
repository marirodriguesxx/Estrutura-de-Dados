#include "Screen.h"
#include <iostream>

using namespace std;

void print(const Screen &s) {
    for (int j = 0; j < s.getWidth() + 2; j++) {
        if(j == 0 || j== s.getWidth() + 1)
            cout << "*";
        else
            cout << "-";
    }
    cout << endl;
    for (int i = 0; i < s.getHeight(); i++) {
        cout << "|";
        for (int j = 0; j < s.getWidth(); j++) {
            if (s.get(s.getHeight() - 1 - i, j) == Screen::EMPTY) cout << " ";
            else if (s.get(s.getHeight() - 1 - i, j) == Screen::SNAKE) cout << "x";
            else cout << "•";
        }
        cout << "|" << "\n";
    }
      for (int j = 0; j < s.getWidth() + 2; j++) {
        if(j == 0 || j== s.getWidth() + 1)
            cout << "*";
        else
            cout << "-";
    }
    cout << "\n\n";
}

int main() {
    int height = 6, width = 5;
     cout<<"Construindo screen\n";
    Screen s(height, width);
    print(s);
    
    cout<<"Screen construída!\n";
    cout<<"Largura da screen: "<<s.getWidth()<<endl;
    cout<<"Altura da screen: "<<s.getHeight()<<endl;
  

    // //print(s);
    // // s.set(0, 9, Screen::FOOD);
    // // print(s);
    // // s.set(0, 9, Screen::SNAKE);
    // // print(s);
    // //Coloca tudo como Comida
    // // s.set(5, 3, Screen::SNAKE);
    // // print(s);
    // // s.set(4, 3, Screen::SNAKE);
    // // // print(s);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            s.set(i, j, Screen::FOOD);
     print(s);

    Screen s2= s;
     print(s2);
    // // cout<<s.get(-10,-100)<<endl;
    // // cout<<s.get(4,4)<<endl;

    //Volta tudo para Empty
    for (int i = (height-1); i >= 0; i--)
        for (int j = (width-1); j >=0; j--)
            s2.set(i, j, Screen::EMPTY);

    print(s2);
    //cout<<s.get(2,6)<<endl;
    for (int i = (width-1); i >=0; i--){
        s2.set(0, i, Screen::SNAKE);
    }
    print(s2);
    return 0;
}