#include "jogador.h"
#include "UserInfos.h"
#include "sobrecargas_data.h"


int main(){

    std::map<int,Player> ret;

    UserInfos u;
	DateTime ini_1,fin_1;
	DateTime ini_2,fin_2;
	//GlobalCoord g1,g2,g3,g4;

	std::cout << "Entre com os dados de inicio e fim da primeira parte da atividade:(aaaa/mm/dd,hh:mm:ss)\n";
	std::cin >> ini_1 >> fin_1;

	std::cout << "Entre com os dados de inicio e fim da segunda parte da atividade:(aaaa/mm/dd,hh:mm:ss)\n";
	std::cin >> ini_2 >> fin_2;
/*
	std::cout << "Entre com os dados das coordenadas que delimitam o campo(Primeiro latitude,depois longitude);\n";
	std::cout << "Coordenada 1:";
	std::cin >> g1.latitude >> g1.longitude;
	std::cout << "Coordenada 2:";
	std::cin >> g2.latitude >> g2.longitude;
	std::cout << "Coordenada 3:";
	std::cin >> g3.latitude >> g3.longitude;
	std::cout << "Coordenada 4:";
	std::cin >> g4.latitude >> g4.longitude;
*/
    u.set_in_f_time(ini_1);
	u.set_fin_f_time(fin_1);
	u.set_in_s_time(ini_2);
	u.set_fin_s_time(fin_2);
	//u.set_coordenadas(g1,g2,g3,g4);

    ret = readPlayerData("exemplo_atividade1.csv",u);

    unsigned int i = 1,j;

    for(i = 1; i <= ret.size();i++){

        if(ret[i].data.size() == 0){
            std::cout << "Sem atividade no periodo!" << std::endl;
            continue;
        }

        Stats *Teste = new Stats;

        Teste->Calculate_first_time(u);
        Teste->Calculate_sec_time(u);
        Teste->Calculate_tot_time(u);

        Teste->Calculate_max_speed(ret[i]);
        Teste->Calculate_speed_ft_18(ret[i]);
        Teste->Calculate_speed_ft_20(ret[i]);
        Teste->Calculate_total_distance(u,ret[i]);

        ret[i].s = Teste;
        ret[i].s->Calculate_first_time(u);
    }

    for(i = 1;i <= ret.size();i++){

        std::cout << std::endl;
        std::cout << "Jogador" << i << std::endl << std::endl;

        if(ret[i].data.size() == 0){
            std::cout << "Sem atividade no periodo!" << std::endl;
            continue;
        }

        std::cout << ret[i].s->get_first_time() << std::endl;
        std::cout << ret[i].s->get_sec_time() << std::endl;
        std::cout << ret[i].s->get_tot_time() << std::endl;
        std::cout << "V max ms: " << ret[i].s->get_max_speed_ms()<< std::endl;
        std::cout << "V max Kmh: " << ret[i].s->get_max_speed_Kmh() << std::endl;
        std::cout << "Dist total:" << ret[i].s->get_total_distance() << std::endl;
        std::cout << "maior 18:" << ret[i].s->num_times_ft18() << std::endl;
        std::cout << "maior 20:" << ret[i].s->num_times_ft20() << std::endl;
        std::cout << "Tempo a mais de 18: " << ret[i].s->get_time_ft_18() << std::endl;
        std::cout << "Tempo a mais de 20: " << ret[i].s->get_time_ft_20() << std::endl;
    }


    std::list<Player> l = lista_distancia(ret);
    std::list<Player>::iterator it;

    std::cout << std::endl << std::endl;
    for(it = l.begin();it != l.end();it++){
        std::cout << *it << std::endl;
    }

    for(i = 1; i <= ret.size();i++){ // desalocar memoria

        if(ret[i].data.size() == 0){
            continue;
        }
        destroi_stats(&ret[i]);
    }

	return 0;
}
