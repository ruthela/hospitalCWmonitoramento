#include <iostream>
#include <fstream>
#include "funcoes.h"
#include <string>
#include <cstdlib>  // rand()
#include <ctime>    // time()

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


int lerInteiro() { // Função de validação de entrada que garante que as escolhas dos menus aceitem apenas números. Se o usuário inserir um texto no lugar do número, a função irá barrar e solicitar uma entrada válida.
    int valor;
    while (!(cin >> valor)) {
        cin.clear();            
        cin.ignore(1000, '\n'); 
        cout << "Entrada inválida! Digite apenas o número: ";
    }
    return valor;
}

void registrarPaciente(){ //Registra os pacientes no array listapacientes

	string nome;
	int controleMenu;
	 
	do{
	if(totalPacientes>=pacientes) 
	// Verifica se o array está preenchido
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
		//Identifica se todos os leitos já foram preenchidos		
		
			cout<<"\n Sala lotada. Retornando ao menu principal. \n"<<endl;
			return;
		}
		
		
		do {
			
			cout<<"Deseja cadastrar outro paciente?"<<endl;
			cout<<"1 - Sim | 0 - Voltar ao menu principal "<<endl;
			controleMenu=lerInteiro();
			
			
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

void escolherRegistroPressao(){
	
	int escolha=0;
	
	if (totalPacientes == 0) {
    cout << "Nenhum paciente cadastrado! Retornando ao menu.\n";
    return;
}

	listarPacientes();

    cout << "Escolha o leito do paciente desejado: ";
    pacienteEscolhido=lerInteiro();

    if (pacienteEscolhido < 1 || pacienteEscolhido > totalPacientes) {
        cout << "Paciente invalido!\n";
        return;
    }
    pacienteEscolhido--;
	
	do{
		cout<<"Escolha como quer inserir as pressões do paciente: \n \n 1 - Gerar aleatoriamente \n 2 - Inserir manualmente \n ";
		escolha=lerInteiro();
		
		if(escolha==1)
		gerarPressaoAleatoria(pacienteEscolhido);
		
		else if (escolha==2)
		registroPressao(pacienteEscolhido);
		
		else
		cout<<"Opção inválida!";
		
		
	}while(escolha!=1 && escolha!=2);
}

		void gerarPressaoAleatoria(int paciente) {
		        bool controladorPressao = false; //busca valores vazios no array
		        bool temValor = false;
		
		        // Busca a posição vazia no array
		        for (int d = 0; d < dias; d++) {
		            for (int v = 0; v < vezesDia; v++) {
		
		                if (medicao[paciente][d][v][0] != 0) 
						{	
							temValor = true;
						}
						else{
							
							medicao[paciente][d][v][0] = rand() % 91 + 90; // sistolica
		            		medicao[paciente][d][v][1] = rand() % 31 + 60; // diastolica
		                    controladorPressao = true;
							
							} 
		                }
		            }
		
		        //  Se não encontrou espaço livre
		        if (!controladorPressao) {
		        cout << "Todas as medicoes deste paciente ja foram registradas!\n";
		    } else {
		    		
		    		if(temValor)
		        cout << "Foram encontrados valores já preenchidos manualmente. \n Completando o restante da matriz com valores aleatórios. \n \n";
		    cout << "Pressões aleatórias geradas com sucesso!\n";
			}   
		}

void registroPressao(int pacienteEscolhido) {

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
            sistolica=lerInteiro();

            cout << "Pressao diastolica: ";
            diastolica=lerInteiro();
            
            do{
            	cout << "\n Confirmar a inserção?\n";
            cout << "1 - Sim | 0 - Nao\n";
            controleInsercao=lerInteiro();
            
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

        // Controla opção de continuar preenchendo
        cout << "\n Deseja registrar outra pressao? \n";
        cout << "1 - Sim | 0 - Voltar ao menu principal \n";
        continuar=lerInteiro();

    } while (continuar == 1);
}

void gerarGrafico() {

    listarPacientes();

    cout << "Escolha o leito em que o paciente está: ";
   	pacienteEscolhido=lerInteiro();

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
    int contador = 0;

    for (int v = 0; v < vezesDia; v++) {
        if (medicao[pacienteEscolhido][d][v][0] != 0) {
            somaSis += medicao[pacienteEscolhido][d][v][0];
            somaDia += medicao[pacienteEscolhido][d][v][1];
            contador++;
        }
    }

    if (contador > 0) {
        arquivo << d+1 << ","
                << somaSis / contador << ","
                << somaDia / contador << "\n";
    } else {
        arquivo << d+1 << ",0,0\n";
    }
}


    arquivo.close();

    cout << "Gerando CSV para criar o gráfico...\n";
}


