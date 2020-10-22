#ifndef USERINFOS_H
#define USERINFOS_H

#include "jogador.h"


class UserInfos{

    DateTime in_first_t,fin_first_t; // tempo de início e fim do primeiro tempo
    DateTime in_sec_t,fin_sec_t; // tempo de início e fim do segundo tempo
    GlobalCoord p[4]; //coordenadas limite do campo passadas pelo usuário

public:

    UserInfos();
    ~UserInfos();

    void set_in_f_time(DateTime in_f);
    void set_fin_f_time(DateTime fin_f);
    void set_in_s_time(DateTime in_s);
    void set_fin_s_time(DateTime fin_s);
    void set_coordenadas(GlobalCoord a,GlobalCoord b,GlobalCoord c,GlobalCoord d);//a para primeira,b para segunda posicao...

    DateTime get_in_f_time();
    DateTime get_fin_f_time();
    DateTime get_in_s_time();
    DateTime get_fin_s_time();
    GlobalCoord* get_coordenadas();

};

#endif // USERINFOS_H
