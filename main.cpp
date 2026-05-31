#include<iostream>
#include <string>
#include <fstream>
#include "funcoes.h"
#include <cstdlib>  // rand()
#include <ctime>    // time()

using namespace std;
main(){ //Programa principal


	system("chcp 65001>nul");
	int opcao;
	srand(time(0));
	
	cout<<"======================================="<<endl;
	cout<<"PROGRAMA DE MONITORAMENTO DE PACIENTES"<<endl;
	cout<<"======================================="<<endl;
	
	do
	{
		
		cout<<"\n\n Selecione uma opção:"<<endl;
	cout<<"1 - Registrar paciente"<<endl;
	cout<<"2 - Listar Pacientes"<<endl;
	cout<<"3 - Registrar pressão"<<endl;
	cout<<"4 - Gerar gráfico"<<endl;
	cout<<"0 - Sair \n"<<endl;
			
	cin>>opcao;
			switch(opcao){
		case 1:{
			registrarPaciente(); //Função de registro de pacientes
			break;
		}
		case 2:{
			listarPacientes(); //Função para listar os pacientes
			break;
		}
		case 3:{
			escolherRegistroPressao(); // Função de registro de pressão
			break;
		}
		
		case 4:{ 
			gerarGrafico(); //Função para gerar o gráfico
    break;
}
		
		case 0:{
			cout<<"Encerrando o programa."<<endl;
			break;
		}
		
		default:
			cout<<"Opção inválida"<<endl;
			
	}
	} while (opcao !=0);

	


}