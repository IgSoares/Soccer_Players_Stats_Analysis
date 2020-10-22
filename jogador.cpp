#include "jogador.h"
#include "UserInfos.h"
#include "sobrecargas_data.h"

#include <cmath>


std::map<int,Player> readPlayerData(std::string name,UserInfos& us){

     std::map<int,Player> m;
     int index,ID;

     std::ifstream file(name); //abrindo arquivo especificado pelo nome recebido como parametro

     if(!file.is_open()) return m; //empty map     }

     std::string trash;

     std::getline(file,trash); //primeira linha -> com informacoes irrelevantes

     while(file){ //le as linhas do arquivo até chegar ao seu final

          file >> index;
          file.ignore();

          file >> ID;
          file.ignore();

          Player& p = m[ID];

          PlayerData pd;

          std::getline(file, trash, ',');

          file >> pd.UTC;
          file.ignore();
          file >> pd.Local;
          file.ignore();
          file >> pd.MS;
          file.ignore();
          file >> pd.position.latitude;
          file.ignore();
          file >> pd.position.dirlat;
          file.ignore();
          file >> pd.position.longitude;
          file.ignore();
          file >> pd.position.dirlong;
          file.ignore();
          file >> pd.altitude;
          file.ignore();
          file >> pd.speed;
          file.ignore();
          file >> pd.heading;
          file.ignore();
          std::getline(file, trash, '\n');

          if((pd.Local >= us.get_in_f_time() && pd.Local <= us.get_fin_f_time()) ||
          (pd.Local >= us.get_in_s_time() && pd.Local <= us.get_fin_s_time())){
               p.data.push_back(pd);
               std::cout << pd.Local << std::endl;
          }
     }

     return m;

}


std::time_t DateTime::toTimestamp() const{

    struct tm *timeinfo;
    std::time_t rt,novo;

    time ( &rt );
    timeinfo = localtime ( &rt );
    timeinfo->tm_year = this->year - 1900;
    timeinfo->tm_mon = this->month - 1;
    timeinfo->tm_mday = this->day;
    timeinfo->tm_hour = this->hour;
    timeinfo->tm_min = this->minute;
    timeinfo->tm_sec = this->second;

    novo = mktime(timeinfo);
    return novo;
}


void DateTime::fromTimestamp(std::time_t time){

    if(time >= 0){
        this->hour = time/3600;
        time = time % 3600;
        this->minute = time / 60;
        time = time % 60;
        this->second = time;
    }

}

// -------------------------------------  Stats Implementação --------------------------------------------- //


Stats::Stats(){}


Stats::~Stats(){}


void Stats::Calculate_first_time(UserInfos& us){
    time_1 = us.get_fin_f_time()-us.get_in_f_time();
}


void Stats::Calculate_sec_time(UserInfos& us){
    time_2 = us.get_fin_s_time()-us.get_in_s_time();
}

void Stats::Calculate_tot_time(UserInfos& us){
    tot_time = time_1 + time_2;
}


void Stats::Calculate_speed_ft_18(Player& p){

    if(p.data.size() == 0){
        return;
    }

    unsigned int i,cont = 0;
    speed_ft_18 = 0;
    DateTime dif,ini,fin;

    faster_th18.day = p.data[0].Local.day;
    faster_th18.month = p.data[0].Local.month;
    faster_th18.year = p.data[0].Local.year;
    faster_th18.hour = 0;
    faster_th18.minute = 0;
    faster_th18.second = 0;

    for(i=0;i < p.data.size();i++){

        if(p.data[i].speed > 18){
            if(cont == 0){
                if(i < p.data.size()-1){
                    ini = p.data[i].Local;
                    fin = p.data[i+1].Local;
                }else{
                    fin = p.data[i].Local;
                }
            }else{
                if(i < p.data.size()-1){
                    fin = p.data[i+1].Local;
                }else{
                    fin = p.data[i].Local;
                }
            }
            speed_ft_18++;
            cont++;
        }else{
            if(cont != 0){
                dif = fin - ini;
                faster_th18 = faster_th18 + dif;
                cont = 0;
            }else{
                continue;
            }
        }

    }
}


void Stats::Calculate_speed_ft_20(Player& p){

    unsigned int i,cont = 0;
    speed_ft_20 = 0;
    DateTime dif,ini,fin;

    faster_th20.day = p.data[0].Local.day;
    faster_th20.month = p.data[0].Local.month;
    faster_th20.year = p.data[0].Local.year;
    faster_th20.hour = 0;
    faster_th20.minute = 0;
    faster_th20.second = 0;

    for(i=0;i < p.data.size();i++){

        if(p.data[i].speed > 20.0){
            if(cont == 0){
                if(i < p.data.size()-1){
                    ini = p.data[i].Local;
                    fin = p.data[i+1].Local;
                }else{
                    fin = p.data[i].Local;
                }
            }else{
                if(i < p.data.size()-1){
                    fin = p.data[i+1].Local;
                }else{
                    fin = p.data[i].Local;
                }
            }
            speed_ft_20++;
            cont++;
        }else{
            if(cont != 0){
                dif = fin - ini;
                faster_th20 = faster_th20 + dif;
                cont = 0;
            }else{
                continue;
            }
        }

    }

}


void Stats::Calculate_max_speed(Player &p){

    unsigned int i;
    max_speed_Kmh = p.data[0].speed;

    for(i=0;i < p.data.size();i++){
        if(p.data[i].speed > max_speed_Kmh){
            max_speed_Kmh = p.data[i].speed;
        }
    }

}


void Stats::Calculate_total_distance(UserInfos& us,Player& p){ //verificar se esta correta

    unsigned int i;
    distance = 0.0;
    double dist_coord_1 = 0.0,dist_coord_2 = 0.0;
    double dist_1t=0.0,dist_2t=0.0;
    double dla = 0.0,dlo =0.0;

    for(i = 0; i < p.data.size()-1;i++){

        if(p.data[i].position.dirlat != p.data[i+1].position.dirlat){
                if(p.data[i].position.dirlat == 'S'){
                    p.data[i].position.latitude *= -1;
                }else{
                    p.data[i+1].position.latitude *= -1;
                }
        }

        if(p.data[i].position.dirlong != p.data[i+1].position.dirlong){
                 if(p.data[i].position.dirlong == 'W'){
                    p.data[i].position.longitude *= -1;
                }else{
                    p.data[i+1].position.longitude *= -1;
                }
        }

        if(p.data[i].Local >= us.get_in_f_time() && p.data[i].Local < us.get_fin_f_time()
           && p.data[i+1].Local > us.get_in_f_time() && p.data[i+1].Local <= us.get_fin_f_time()){

            dla = p.data[i+1].position.latitude - p.data[i].position.latitude;
            dlo = p.data[i+1].position.longitude - p.data[i].position.longitude;

            dist_coord_1 = sqrt(pow(dla*60*1852,2) + pow(dlo*60*1852,2)); //conversao de diferenca de latitudes e longitudes para distancias
            dist_1t += dist_coord_1;

        }else if(p.data[i].Local >= us.get_in_s_time() && p.data[i].Local < us.get_fin_s_time()
           && p.data[i+1].Local > us.get_in_s_time() && p.data[i+1].Local <= us.get_fin_s_time()){

            dla = p.data[i+1].position.latitude - p.data[i].position.latitude;
            dlo = p.data[i+1].position.longitude - p.data[i].position.longitude;

            dist_coord_2 = sqrt(pow(dla*60*1852,2) + pow(dlo*60*1852,2)); //conversao de diferenca de latitudes e longitudes para distancias
            dist_2t += dist_coord_2;
        }

    }

    distance = dist_1t + dist_2t;
}


DateTime Stats::get_first_time(){
    return time_1;
}


DateTime Stats::get_sec_time(){
    return time_2;
}


DateTime Stats::get_tot_time(){
    return tot_time;
}


DateTime Stats::get_time_ft_18(){
    return faster_th18;
}


DateTime Stats::get_time_ft_20(){
    return faster_th20;
}


int Stats::num_times_ft18(){
    return speed_ft_18;
}


int Stats::num_times_ft20(){
    return speed_ft_20;
}


double Stats::get_max_speed_Kmh(){
    return max_speed_Kmh;
}


double Stats::get_max_speed_ms(){
    return (max_speed_Kmh/3.6);
}


double Stats::get_total_distance(){
    return distance;
}



bool dist_percor(const Player &a,const Player &b){

   return (a.s->get_total_distance() < b.s->get_total_distance());
}


std::list<Player> lista_distancia(std::map<int,Player> m){

    std::list<Player> l;
    unsigned int i;

    // map inicializado a partir da key = 1
    for(i=1; i <= m.size();i++){
        if(m[i].data.size() > 0){
            l.push_back(m[i]);
        }else{
            std::cout << "Sem dados do jogador!" << std::endl;
            continue;
        }
    }

    for(i=1;i <= m.size() - 1;i++){
        if(m[i].data.size() > 0){
            l.sort(dist_percor); // ordenando
        }else{
            std::cout << "Sem dados do jogador!" << std::endl;
            continue;
        }
    }

    return l;
}

std::ostream& operator<<(std::ostream& out,const Player& p){

    out << p.s->get_total_distance();
    return out;
}


void destroi_stats(Player *p){

    if(p == nullptr){
        return;
    }

    delete p->s;
}
