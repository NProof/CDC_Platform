#include "../header/Board.h"

#include <algorithm>
#include <map>

bool Chess::operator==(const Chess &str) const{
    return this->type == str.type;
}

Board::Board(){
    uint8_t itype[] = {1,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,8,8,8,8,8,9,9,10,10,11,11,12,12,13,13,14};
    std::random_shuffle(itype, itype + 32);
    for(int i = 0; i < 32; i++){
        this->chs[i].stat = 1;
        this->chs[i].type = itype[i];
    }
}

Board::Board(std::string str){
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7}, 
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    for(int i = 0; i < 32; i++){
        this->chs[i].stat = 1;
        this->chs[i].type = m.at(str[i]);
    }
}

Board::Board(std::string str, uint32_t dark, uint32_t alive){
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7},
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    uint32_t mask = 0x1;
    for(int i = 0; i < 32; i++){
        this->chs[i].stat = (dark & mask) ? 1 : ((alive & mask) ? 2 : 3);
        this->chs[i].type = m.at(str[i]);
        mask <<= 1;
    }
}

bool Board::neighbor(int x,int y){
    int tem;
    if(y>x){
        tem = y;
        y = x;
        x = tem; 
    }
    if(x-y==1&&x%8!=0){
        return true;
    }
    else if(x-y==8){
        return true;
    }else return false;   
}

bool Board::boom(int x,int y){ // 這裡你把 int chess[] 改成 Board & board
    int tem;

    if(y>x){
        tem = y;
        y = x;
        x = tem; 
    }
    if(x-y==2&&x%8!=0&&(x-1)%8!=0&&this->chs[x-1].stat!=3){
        return true;
    }
    else if(x-y==16&&this->chs[x-8].stat!=3){
        return true;
    }else return false;
}

bool Chess::momentum(int type, int type_opp) // 判斷兩旗子可不可以產生吃的行為
{
    if((type>7&&type_opp>7)||(type<8&&type_opp<8)){
        return false;
    }
    else if((type==8&&type_opp==1)||(type==7&&type_opp==14)){
        return true;
    }
    else if(type<8&&(15-type_opp)>=type){
        return true;
    }
    else if(type>7&&(15-type_opp)<=type){
        return true;
    }
    else return false;
}
