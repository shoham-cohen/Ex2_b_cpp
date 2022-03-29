#include <iostream>
#include "Direction.hpp"
#include "Notebook.hpp"

const int max_row_length = 100;

using namespace std;
using namespace ariel;

void Notebook::write(int page, int row, int column, Direction direction, string const& sentence){
    if((unsigned(column) + sentence.length() > max_row_length && direction == Direction::Horizontal) || column >= max_row_length){
        throw("cant write in more than 100 colums in one row");
    }
    if(page < 0 || row < 0 || column < 0){
        throw runtime_error("page, row and column has to be non negative");
    }
    if(direction == Direction::Vertical){
        for(int i = 0; i < sentence.length(); i++){
            if(the_notebook.find(page) == the_notebook.end()){ //if the page does not exists
                build_page(page, row + i);
            } 
            else if(the_notebook.at(page).find(row + i) == the_notebook.at(page).end()){ //if the row does not exist
                build_row(page, row + i);
            }
        }
        for(int i = 0; i < sentence.length(); i++){ //checking that we wont write on written/erased or write illegal char
            if(the_notebook.at(page).at(row + i).at(unsigned(column)) != '_'){
                throw runtime_error("you cant write on written or erased");
            }
            if((sentence.at(unsigned(i)) < ' ') || sentence.at(unsigned(i)) >= '~'){
                throw runtime_error("there is an illegal char in the string");
            }
        }
        for(int i = 0; i < sentence.length(); i++){ //if everything ok write in the notebook as wanted
            the_notebook.at(page).at(row + i).at(unsigned(column)) = sentence.at(unsigned(i));
        }
    }
    else{
        if(the_notebook.find(page) == the_notebook.end()){  //if the page does not exists
            build_page(page, row);
        } 
        else if(the_notebook.at(page).find(row) == the_notebook.at(page).end()){ //if the row does not exist
            build_row(page, row);
        }
        for(unsigned int i = 0; i < sentence.length(); i++){ 
            if(the_notebook.at(page).at(row).at(unsigned(column) + i) != '_'){ //checking that we wont write on written/erased or write illegal char
                throw runtime_error("you cant write on written or erased");
            }
            if((sentence.at(unsigned(i)) < ' ') || sentence.at(unsigned(i)) >= '~'){
                throw runtime_error("there is an illegal char in the string");
            }
        }
        for(int i = 0; i < sentence.length(); i++){ //if everything ok write in the notebook as wanted
            the_notebook.at(page).at(row).at(unsigned(column + i)) = sentence.at(unsigned(i));
        }
    } 
}     

string Notebook::read(int page, int row, int column, Direction direction, int chars_to_read){
    string final_res; 
    if((unsigned(column) + unsigned(chars_to_read) > max_row_length && direction == Direction::Horizontal) || column >= max_row_length){
        throw("cant read more than 100 colums in one row");
    }
    if(page < 0 || row < 0 || column < 0 || chars_to_read < 0){
        throw runtime_error("page, row, column and chars_to_read has to be non negative");
    }
    if(direction == Direction::Vertical){
        for(int i = 0; i < chars_to_read; i++){ // check if the wanted place exists. if so append the char that in that place' otherwise append the char _.
            if(the_notebook.find(page) == the_notebook.end() || the_notebook.at(page).find(row + i) == the_notebook.at(page).end()){
                final_res += "_";
            }
            else{
                final_res.append(1, the_notebook.at(page).at(row + i).at(unsigned(column)));
            }
        }
    }
    else{ // direction == Horizontal
    // check if the wanted place exists. if so append the char that in that place' otherwise append the char _.
        if(the_notebook.find(page) == the_notebook.end() || the_notebook.at(page).find(row) == the_notebook.at(page).end()){
            for(int i = 0; i < chars_to_read; i++){
                final_res += '_';
            }
        }
        else{
            for(int i = 0; i< chars_to_read; i++){
                final_res.append(1, the_notebook.at(page).at(row).at(unsigned(column+i)));
            }
        } 
    }
    return(final_res);
}

void Notebook::erase(int page, int row, int column, Direction direction, int chars_to_erase){
    if((unsigned(column) + unsigned(chars_to_erase) > max_row_length && direction == Direction::Horizontal) || column >= max_row_length){
        throw("cant erase more than 100 colums in one row");
    }
    if(page < 0 || row < 0 || column < 0 || chars_to_erase < 0){
        throw runtime_error("page, row, column and chars_to_erase has to be non negative");
    } 
    if(direction == Direction::Vertical){
        for(int i = 0; i < chars_to_erase; i++){
            if(the_notebook.find(page) == the_notebook.end()){ //if the page does not exists
                build_page(page, row + i);
            } 
            else if(the_notebook.at(page).find(row + i) == the_notebook.at(page).end()){ //if the row does not exist
                build_row(page, row + i);
            }
        }
        for(int i = 0; i < chars_to_erase; i++){ //if everything ok erase the wanted chars
            the_notebook.at(page).at(row + i).at(unsigned(column)) = '~';
        }
    }
    else{  // direction == Horizontal
        if(the_notebook.find(page) == the_notebook.end()){ //if the page does not exist
            build_page(page, row);
        } 
        else if(the_notebook.at(page).find(row) == the_notebook.at(page).end()){ //if the row does not exist
            build_row(page, row);
        } 
        for(int i = 0; i < chars_to_erase; i++){ //if everything ok erase the wanted chars
            the_notebook.at(page).at(row).at(unsigned(column + i)) = '~';
        }
    } 
}

void Notebook::show(int page){
    if(page < 0){
        throw("page has to be non-negative");
    }
    if(the_notebook.find(page) == the_notebook.end()){
        cout<<"this page is empty"<<endl;
    }
    else{
        int min_row = the_notebook.at(page).begin()->first;
        int max_row = the_notebook.at(page).rbegin()->first;
        for(int i = min_row; i <= max_row; i++){
            cout << read(page, i, 0, Direction::Horizontal, max_row_length) << endl;
        }
    }
}

void Notebook::build_page(int page, int row){
    vector <char> temp_line(max_row_length, '_');
    map<int, vector<char>> temp_page;
    temp_page[row] = temp_line;
    the_notebook[page] = temp_page;
}

void Notebook::build_row(int page, int row){
    vector <char> temp_line(max_row_length, '_');
    the_notebook.at(page)[row] = temp_line;
}
