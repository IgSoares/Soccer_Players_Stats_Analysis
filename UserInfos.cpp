#include "UserInfos.h"


UserInfos::UserInfos(){}


UserInfos::~UserInfos(){}


void UserInfos::set_in_f_time(DateTime in_f){
    in_first_t = in_f;
}


void UserInfos::set_fin_f_time(DateTime fin_f){
    fin_first_t = fin_f;
}


void UserInfos::set_in_s_time(DateTime in_s){
    in_sec_t = in_s;
}


void UserInfos::set_fin_s_time(DateTime fin_s){
    fin_sec_t = fin_s;
}


void UserInfos::set_coordenadas(GlobalCoord a, GlobalCoord b, GlobalCoord c, GlobalCoord d){

    p[0].latitude = a.latitude; //Primeiro ponto
    p[0].longitude = a.longitude;

    p[1].latitude = b.latitude; //Segundo ponto
    p[1].longitude = b.longitude;

    p[2].latitude = c.latitude; //Terceiro Ponto
    p[2].longitude = c.longitude;

    p[3].latitude = d.latitude; //Quarto Ponto
    p[3].longitude = d.longitude;

}

DateTime UserInfos::get_in_f_time(){
    return in_first_t;
}

DateTime UserInfos::get_fin_f_time(){
    return fin_first_t;
}


DateTime UserInfos::get_in_s_time(){
    return in_sec_t;
}


DateTime UserInfos::get_fin_s_time(){
    return fin_sec_t;
}


GlobalCoord* UserInfos::get_coordenadas(){
    return p;
}
