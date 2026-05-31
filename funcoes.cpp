#include <iostream>
#include <fstream>
#include "funcoes.h"
#include <string>

using namespace std;

//Variáveis globais para gerenciamento do programa

//Variaveis constantes com o tamanho dos arrays

const int pacientes=10;
const int dias=7;
const int vezesDia=3;
const int tiposPressao=2;

//Variáveis não-constantes

int totalPacientes=0; //controla a quantidade de pacientes na sala
int pacienteEscolhido=0; //variável para a função de gerar gráfico e CSV

//Arrays para registro dos dados

int medicao[pacientes][dias][vezesDia][tiposPressao]; //array para registro da pressão
string listaPacientes[pacientes]; //array para lista de pacientes

// == Funções ==
void registrarPaciente(){ //Registra os pacientes no array listapacientes

	string nome;
	int controleMenu;
	 
	do{
	if(totalPacientes>=pacientes)
	{
		cout<<"Sala cheia! \nRetornando ao menu principal. \n";
		return;
	}
		cout<<"Digite o nome do paciente: ";
		cin.ignore(1000,'\n');
		getline(cin,nome);
		
		listaPacientes[totalPacientes] = nome;
		totalPacientes++;
		
		cout<<"Paciente cadastrado com sucesso! \n"<<endl;
		
		if(totalPacientes==pacientes){
			cout<<"\n Sala lotada. Retornando ao menu principal. \n"<<endl;
			return;
		}
		
		
		do {
			
			cout<<"Deseja cadastrar outro paciente?"<<endl;
			cout<<"1 - Sim | 0 - Voltar ao menu principal "<<endl;
			cin>>controleMenu;
			
		if(controleMenu != 0 && controleMenu != 1)
			cout<<"Digite uma opção válida!";
		}while(controleMenu!=0 && controleMenu!=1);
		
	}while(controleMenu==1);
	
}

void listarPacientes(){ //Imprime os pacientes do array
	
	if(totalPacientes==0){
		cout<<"Nenhum paciente cadastrado. Retornando ao menu principal."<<endl;
		return;
	}
		for(int i=0;i<totalPacientes;i++)
		{
			cout<<"\n";
			cout<<"Leito "<< i+1 <<": "<<listaPacientes[i]<<endl;
		}
	
	
}

void registroPressao() {

	
if (totalPacientes == 0) {
    cout << "Nenhum paciente cadastrado! Retornando ao menu.\n";
    return;
}

	listarPacientes();

    int pacienteEscolhido=0;

    cout << "Escolha o paciente: ";
    cin >> pacienteEscolhido;

    if (pacienteEscolhido < 1 || pacienteEscolhido > totalPacientes) {
        cout << "Paciente invalido!\n";
        return;
    }
    pacienteEscolhido--;

    int continuar;

    do {

        int dia = -1, turno = -1;
        bool controladorPressao = false;

        // Busca a posição vazia no array
        for (int d = 0; d < dias && !controladorPressao; d++) {
            for (int v = 0; v < vezesDia && !controladorPressao; v++) {

                if (medicao[pacienteEscolhido][d][v][0] == 0) {
                    dia = d;
                    turno = v;
                    controladorPressao = true;
                }
            }
        }

        //  Se não encontrou espaço livre
        if (!controladorPressao) {
            cout << "Todas as medições deste paciente ja foram registradas!\n";
            return;
        }

        int sistolica, diastolica;
        int controleInsercao;

        // Loop de confirmação
        do {
        	
            cout << "Pressao sistolica: ";
            cin >> sistolica;

            cout << "Pressao diastolica: ";
            cin >> diastolica;
            
            do{
            	cout << "\n Confirmar a inserção?\n";
            cout << "1 - Sim | 0 - Nao\n";
            cin >> controleInsercao;
            
            if(controleInsercao!=0  &&  controleInsercao!=1)
            	cout<<"Opção inválida!";
			}while (controleInsercao != 0 && controleInsercao != 1);

        } while (controleInsercao != 1);

        // Guarda o valor na matriz
        medicao[pacienteEscolhido][dia][turno][0] = sistolica;
        medicao[pacienteEscolhido][dia][turno][1] = diastolica;

        // Retorna valores inseridos
        cout << "Pressão registrada no dia " << dia + 1;

        if (turno == 0) cout << " (Manhã)\n";
        else if (turno == 1) cout << " (Tarde)\n";
        else cout << " (Noite)\n";

        // Controle de vezes
        cout << "\n Deseja registrar outra pressao? \n";
        cout << "1 - Sim | 0 - Voltar ao menu principal \n";
        cin >> continuar;

    } while (continuar == 1);
}

void gerarGrafico() {

    listarPacientes();

    cout << "Escolha o leito em que o paciente está: ";
    cin >> pacienteEscolhido;

    if (pacienteEscolhido < 1 || pacienteEscolhido > totalPacientes) {
        cout << "Paciente invalido!\n";
        return;
    }

    pacienteEscolhido--;

    gerarCSV(pacienteEscolhido);
    system("python grafico.py");
}

void gerarCSV(int pacienteEscolhido) {

    ofstream arquivo("dados_paciente.csv");

    arquivo << "dia,sistolica,diastolica\n";

    for (int d = 0; d < dias; d++) {

        int somaSis = 0;
        int somaDia = 0;

        for (int v = 0; v < vezesDia; v++) {
            somaSis += medicao[pacienteEscolhido][d][v][0];
            somaDia += medicao[pacienteEscolhido][d][v][1];
        }

        arquivo << d+1 << ","
                << somaSis / vezesDia << ","
                << somaDia / vezesDia << "\n";
    }

    arquivo.close();

    cout << "Gerando CSV para criar o gráfico...\n";
}


