/*
//------------// Créditos //----------//
Desenvolvedor:   Pedro Paulo Dias Sales
Data de Criação: 14/03/2025 
Contatos: 
Email    -       pedrosalesmcd@gmail.com
WhatsApp -       (21) 96865-6996
Descrição:
	Este programa foi desenvolvido para auxiliar na gestão de inquilinos, 
	permitindo o controle de informações como CPF, nome, idade, sexo, 
	dívidas e pagamentos de aluguel. O sistema facilita operações como 
	o cálculo de dívidas, a verificação de inadimplência, o controle de 
	pagamentos, além de gerar relatórios sobre a situação financeira dos 
	inquilinos.
	
	Funcionalidades:
	- Cadastro de inquilinos e controle de informações pessoais.
	- Registro de pagamentos e cálculo de dívidas.
	- Exibição de inquilinos com pendências.
	- Relatórios financeiros, incluindo totais pagos e devidos.
	- Opções para editar, remover ou apagar dados de inquilinos.
	- Sistema de login para acesso seguro ao sistema.

    */

//---------------------------------------------------------//Bibliotecas.
#include<stdlib.h>
#include<iostream>
#include<locale.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

//---------------------------------------------------------//Struct.
typedef struct{
	string cpf;
	string nome;
	char sexo;
	int idade;             //------------------------------//Campos.
	bool deveAluguel;
	float pagamentos[12];
	float divida;	
}Pessoa;

Pessoa inquilino[100];
int total = 0;
float valorAluguel = 500;

//--------------------------------------------------------//informações de login 
string usuarioCorreto = "acesso"; 
string senhaCorreta = "9999";   

//---------------------------------------------------------//Sistema de Login com senha e usuário.
bool autenticar(){
	string usuario, senha;
	int tentativas = 3;
	
	while(tentativas > 0){
		system("cls");
        system("color F0");
        cout<<"_________SISTEMA DE LOGIN_________"<<endl;
        cout<<"Usuário: "; cin>>usuario;
        cout<<"Senha: "; cin>>senha;
        if(usuario==usuarioCorreto && senha==senhaCorreta){
        	cout<<"Login bem-sucedido!"<<endl;
            system("pause");
            return true;
		}else{
			tentativas--;
			cout<<"Credenciais incorretas! Tentativas restantes: "<<tentativas<<"\n";
            system("pause");
		}
	}
	cout<<"Acesso negado!"<<endl;
    return false;
}

//---------------------------------------------------------//Função para verificar se existe cpf cadastrado.
bool verificarCpf(string cpf){
		for(int i = 0; i < total; i++){
        if(inquilino[i].cpf == cpf){
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------//Função para verificar se o sexo é válido.
bool verificarSexo(char sexo){
	if(sexo == 'M' || sexo == 'F'){
		return true; 
	}else{
		return false;
	}
}

//---------------------------------------------------------//Função para verificar se a idade é válida.	
bool verificarIdade(int idade){
	if(idade<18){
		return false;
	}else{
		return true;
	}
}

//---------------------------------------------------------//Função para verificar se o mês é válido.
bool verificarMes(int mes){
    if(mes >= 1 && mes <= 12){
    	return true;
	}else{
		return false;
	}
}

//---------------------------------------------------------//Função para zarar os valores para o novo inquilino.
void zerandoContadores(Pessoa &inq){
	inq.deveAluguel = false;  
    inq.divida = 0; 
    for(int i=0;i<12;i++){
    	inq.pagamentos[i] = 0;
	}
}

//---------------------------------------------------------//Função "mensagem".
void mensagem(const string &texto, const string &cor){
	system("cls");
	if(cor == "vermelho"){
        system("color 4F");
    }else if (cor == "verde"){
        system("color 2F");
    }else if (cor == "azul"){
        system("color 1F");
    }else{
        system("color 7F"); 
    }
	
	cout<<texto<<endl; 
	system("pause"); 
}

//---------------------------------------------------------//Função para adicionar um novo inquilino.
void adicionarInquilino(){
	system("cls");
	cout<<"_________ADICIONAR INQUILINO__________"<<endl<<endl;
	if(total<100){
		cout<<"INQUILINO "<<total + 1<<endl;
		
		//------------------CPF-------------------//
		cout<<"CPF: "; cin>>inquilino[total].cpf;
		if(verificarCpf(inquilino[total].cpf)==true){
			mensagem("INQUILINO JÁ CADASTRADO","vermelho");
			return;
		}
		
		//------------------NOME------------------//
		cout<<"NOME: "; cin>>inquilino[total].nome;
		
		//------------------SEXO------------------//
		do{
            cout<<"SEXO (M/F): "; cin>>inquilino[total].sexo;
            inquilino[total].sexo = toupper(inquilino[total].sexo); 
            if(verificarSexo(inquilino[total].sexo)==false){
                mensagem("SEXO INVÁLIDO! TENTE NOVAMENTE.", "vermelho");
            }
        } while (verificarSexo(inquilino[total].sexo)==false);
		
		//------------------IDADE-----------------//
		do{
            cout<<"IDADE: "; cin>>inquilino[total].idade;
            if(verificarIdade(inquilino[total].idade)==false){
                mensagem("IDADE INVÁLIDA! TENTE NOVAMENTE.", "vermelho");
            }
        }while(verificarIdade(inquilino[total].idade)==false);
		
		//-----------ZERANDO-CONTADORES-----------//
		zerandoContadores(inquilino[total]);
		
		//----------------------------------------//
		mensagem("INQUILINO CADASTRADO!","verde");
		
		total++; 
		
	}else{
		mensagem("SISTEMA LOTADO!", "vermelho");
	}
}

//---------------------------------------------------------//Função para exibir funcionário da posição [i].
void exibirInquilino(int i){
    cout<<endl<<"INQUILINO "<<i + 1<<endl;
    cout<<"CPF...........: "<<inquilino[i].cpf<<endl;
    cout<<"NOME..........: "<<inquilino[i].nome<<endl;
    cout<<"SEXO..........: "<<inquilino[i].sexo<<endl;
    cout<<"IDADE.........: "<<inquilino[i].idade<<endl;
    cout<<"DEVE ALUGUEL..: "<<(inquilino[i].deveAluguel ? "SIM" : "NÃO")<<endl;
    cout<<"_______________________________"<<endl;
}

//---------------------------------------------------------//Função para exibir todos os funcionários cadastrados.
void exibirTodosInq(){
	system("cls");
	
    if(total <= 0){
        mensagem("SISTEMA VAZIO!", "vermelho");
        return;
    }
    cout<<"_________EXIBIR TODOS INQUILINOS_________"<<endl;
    cout<<"TOTAL DE INQUILINOS: "<<total<<endl<<endl;  
    for(int i = 0; i < total; i++){
        exibirInquilino(i);
    }
    system("pause");
}

//---------------------------------------------------------//Função para configurar novo valor do aluguel.
void valorNovoAluguel(){
	system("cls");
	cout<<"_________CONFIGURAR VALOR DO ALUGUEL_________"<<endl;
    cout<<"NOVO VALOR: R$ "; cin>>valorAluguel;
    
    if(valorAluguel < 500){
        mensagem("VALOR INVÁLIDO! O VALOR DEVE SER MAIOR QUE 499.", "vermelho");
    }else{
    	ostringstream oss;
		oss<<fixed<<setprecision(2)<<valorAluguel;
		mensagem("VALOR DO ALUGUEL CONFIGURADO PARA R$ " + oss.str(), "verde");

        system("pause");
    }
}

//---------------------------------------------------------//Função para registrar os pagamentos.
void registrarPagamento(){
	system("cls");
	string cpfBusca;
	int mes;
	float valorPago;

	cout<<"_________REGISTRAR PAGAMENTO_________"<<endl;
	cout<<"CPF: "; cin>>cpfBusca;
	for(int i=0; i < total;i++){
		if(inquilino[i].cpf == cpfBusca){		
			exibirInquilino(i);		
			cout<<endl<<"MÊS (1-12): "; cin>>mes;	
				if(verificarMes(mes)==false){
		                mensagem("MÊS INVÁLIDO!", "vermelho");
		                return;
		            }	            
				if(inquilino[i].pagamentos[mes - 1] > 0){
		                mensagem("PAGAMENTO JÁ REGISTRADO PARA ESTE MÊS!", "vermelho");
		                return;
		            }        
            cout<<"VALOR PAGO: R$ "; cin>>valorPago;       
				if(valorPago < valorAluguel){
	            inquilino[i].divida += (valorAluguel - valorPago);
	            inquilino[i].deveAluguel = true; 
				}else{
		            inquilino[i].deveAluguel = false; 
				} 			
				inquilino[i].pagamentos[mes - 1] = valorPago;
	            mensagem("PAGAMENTO REGISTRADO!", "verde");
	            return;
        }
	}
	mensagem("INQUILINO NÃO ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Função para exibir pagamentos pendentes.
void pagamentosPendentes(){
    system("cls");
    cout<<"_________PAGAMENTOS PENDENTES_________"<<endl<<endl;
	cout<<"TOTAL DE INQUILINOS: "<<total<<endl<<endl;  
	
    bool encontrouDivida = false; 

    for(int i = 0; i < total; i++){
        if(inquilino[i].deveAluguel==true){
            cout<<"INQUILINO: "<<i + 1<<endl;
            cout<<"CPF...........: "<<inquilino[i].cpf<<endl;
            cout<<"NOME..........: "<<inquilino[i].nome<<endl;
            cout<<"SEXO..........: "<<inquilino[i].sexo<<endl;
            cout<<"IDADE.........: "<<inquilino[i].idade<<endl;
            cout<<"DÍVIDA TOTAL..: R$ "<<inquilino[i].divida<<endl;
            cout<<"-------------------------------------"<<endl;
            encontrouDivida = true;
        }
    }
    if(encontrouDivida==false){
        mensagem("Todos os inquilinos estão em dia com os pagamentos!","verde");
    }
    system("pause"); 
}

//---------------------------------------------------------//Função para pesquisar inquilinos.
void pesquisarInquilino(){
	system("cls");
    string cpfBusca;
    cout<<"_________PESQUISAR INQUILINO_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;
    for(int i = 0; i < total; i++){
        if(inquilino[i].cpf == cpfBusca){
            exibirInquilino(i);
            system("pause");
            return;
        }
    }
    mensagem("INQUILINO NÃO ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Função para exibir o histórico de pagamentos.
void mostrarHistorico(){
	system("cls");
    string cpfBusca;
    cout<<"_________HISTÓRICO DE PAGAMENTOS_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;

    for(int i = 0; i < total; i++){
        if (inquilino[i].cpf == cpfBusca) {
            exibirInquilino(i);
            cout << "----------------------------------------" << endl;

            cout<<"MÊS       VALOR PAGO (R$)"<<endl;
            cout<<"----------------------------------"<<endl;
            for(int mes = 0; mes < 12; mes++){
                cout<<mes + 1 << "         " <<inquilino[i].pagamentos[mes]<<endl;
            }
            cout<<"-----------------------------------------"<<endl;
            cout<<"DÍVIDA TOTAL: R$ "<<inquilino[i].divida<<endl;
            system("pause");
            return;
        }
    }
    mensagem("INQUILINO NÃO ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Função para quitar dívida do respectivo inquilino.
void quitarDivida() {
    string cpfBusca;
    float valorPago;

    system("cls");
    cout<<"_________QUITAR DÍVIDA_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;

    for(int i = 0; i < total; i++){
        if(inquilino[i].cpf == cpfBusca){
            if(inquilino[i].divida <= 0){
                mensagem("ESTE INQUILINO NÃO POSSUI DÍVIDAS!", "verde");
                return;
            }

            cout<<"DÍVIDA ATUAL: R$ "<<inquilino[i].divida<<endl;
            cout<<"VALOR A SER PAGO: R$ "; cin>>valorPago;

            if(valorPago <= 0){
                mensagem("VALOR INVÁLIDO! DIGITE UM VALOR MAIOR QUE ZERO.", "vermelho");
                return;
            }

            inquilino[i].divida -= valorPago;

            if(inquilino[i].divida <= 0){
                inquilino[i].divida = 0;
                inquilino[i].deveAluguel = false; 
                mensagem("DÍVIDA TOTALMENTE QUITADA! PARABÉNS!", "verde");
            }else{
                mensagem("PAGAMENTO REGISTRADO! DÍVIDA RESTANTE: R$ ", "verde");
                cout<<inquilino[i].divida;
            }
            return;
        }
    }
    mensagem("INQUILINO NÃO ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Função exibi o relatório de pagamentos.
void relatorioPagamentos(){
	system("cls");
	int inquilinosEmDia = 0;
    int inquilinosComDivida = 0;
    float totalRecebido = 0;
    float totalDividas = 0;
	
	cout<<"_________RELATÓRIO DE PAGAMENTOS_________"<<endl;
	
	for(int i = 0; i < total; i++){
		bool temPagamento = false;
        for(int mes = 0; mes < 12; mes++){
            if(inquilino[i].pagamentos[mes] > 0){
                totalRecebido += inquilino[i].pagamentos[mes];
                temPagamento = true;
            }
        }
        totalDividas += inquilino[i].divida;
        if(inquilino[i].deveAluguel){
            inquilinosComDivida++;
        }else if(temPagamento){
            inquilinosEmDia++;
        }
    }
	cout<<"Total em dia...........: "<<inquilinosEmDia<<endl;
    cout<<"Total com dívida.......: "<<inquilinosComDivida<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"Receita................: R$ "<<totalRecebido<<endl;
    cout<<"Dívidas................: R$ "<<totalDividas<<endl;
    cout<<"_________________________________________"<<endl;
    system("pause");
}

//---------------------------------------------------------//Função para salvar os dados.
void salvarDados() {
    ofstream arquivo("inquilinos.txt");
    if(!arquivo.is_open()){
        mensagem("Erro ao abrir o arquivo para salvar os dados!", "vermelho");
        return;
    }
    arquivo<<valorAluguel<<endl;
    arquivo<<total<<endl;
    for (int i = 0; i < total; i++) {
        arquivo<<inquilino[i].cpf<<endl;
        arquivo<<inquilino[i].nome<<endl;
        arquivo<<inquilino[i].sexo<<endl;
        arquivo<<inquilino[i].idade<<endl;
        arquivo<<inquilino[i].deveAluguel<<endl;
        arquivo<<inquilino[i].divida<<endl;
        for (int j = 0; j < 12; j++) {
            arquivo<<inquilino[i].pagamentos[j]<<" ";
        }
        arquivo<<endl;
    }

    arquivo.close();
    mensagem("DADOS SALVOS!", "verde");
}

//---------------------------------------------------------//Função para carregar os dados.
void carregarDados(){
    ifstream arquivo("inquilinos.txt");
    if(!arquivo.is_open()){
        mensagem("Arquivo de dados não encontrado. Criando novo arquivo...", "vermelho");
        return;
    }
    arquivo>>valorAluguel;
    arquivo>>total;
    for(int i = 0; i < total; i++){
        arquivo>>inquilino[i].cpf;
        arquivo.ignore();
        getline(arquivo, inquilino[i].nome);
        arquivo>>inquilino[i].sexo;
        arquivo>>inquilino[i].idade;
        arquivo>>inquilino[i].deveAluguel;
        arquivo>>inquilino[i].divida;
        for(int j = 0; j < 12; j++){
            arquivo >> inquilino[i].pagamentos[j];
        }
    }
    arquivo.close();
    mensagem("Dados carregados com sucesso!", "verde");
}

//---------------------------------------------------------//Função para remover o respectivo inquilino.
void removerInquilino(){
    string cpfBusca;
    system("cls");
    cout<<"_________REMOVER INQUILINO_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;

    for (int i = 0; i < total; i++) {
        if (inquilino[i].cpf == cpfBusca) {
            exibirInquilino(i);

            char confirmacao;
            cout<<"Tem certeza que deseja remover este inquilino? (S/N): "; cin>>confirmacao;
            confirmacao = toupper(confirmacao);

            if(confirmacao == 'S'){
                for (int j = i; j < total - 1; j++){
                    inquilino[j] = inquilino[j + 1];
                }
                total--; 
                mensagem("INQUILINO REMOVIDO COM SUCESSO!", "verde");
            } else {
                mensagem("OPERAÇÃO CANCELADA!.", "vermelho");
            }
            return;
        }
    }
    mensagem("INQUILINO NÃO ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Função para apagar todos os dados.
void apagarDados() {
    char confirmacao;
    system("cls");
    cout<<"_________APAGAR TODOS OS DADOS_________"<<endl;
    cout<<"Tem certeza que deseja apagar todos os dados? (S/N): "; cin>>confirmacao;
    confirmacao = toupper(confirmacao);

    if(confirmacao == 'S'){
        total = 0; 
        valorAluguel = 500;
        mensagem("DADOS APAGADOS COM SUCESSO!", "verde");
    }else{
        mensagem("OPERAÇÃO CANCELADA!", "vermelho");
    }
}

//---------------------------------------------------------//Função Menu.
void exibirMenu() {
    system("cls");
    system("color 1F"); 

    cout << "=========================================" << endl;
    cout << "       CONTROLE DE INQUILINOS            " << endl;
    cout << "=========================================" << endl;
    cout << "           MENU PRINCIPAL                " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " [1]  Adicionar Inquilino                " << endl;
    cout << " [2]  Pesquisar Inquilino                " << endl;
    cout << " [3]  Exibir Todos os Inquilinos         " << endl;
    cout << " [4]  Registrar Pagamento                " << endl;
    cout << " [5]  Exibir Pagamentos Pendentes        " << endl;
    cout << " [6]  Configurar Valor do Aluguel        " << endl;
    cout << " [7]  Quitar Dívida                      " << endl;
    cout << " [8]  Exibir Histórico de Pagamentos     " << endl;
    cout << " [9]  Relatório de Pagamentos            " << endl;
    cout << " [10] Remover Inquilino                  " << endl;
    cout << " [11] Salvar dados                       " << endl;
    cout << " [12] Apagar dados                       " << endl;
    cout << " [0]  Sair                               " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Escolha uma opção: ";
}

//---------------------------------------------------------//Função Principal.
int main(){
	//-----------------------------------------------------//Define a localidade para português brasileiro
	setlocale(LC_ALL, "portuguese");
	
	//-----------------------------------------------------//verificação de login
	if (autenticar()==false) {
        return 0; 
    }
	
	//-----------------------------------------------------//Carrega os dados dos inquilinos
    carregarDados();
	
	int op;
	do{
		exibirMenu(); //-----------------------------------// Chama a função "menu"
        cin>>op;
		
		switch(op){
		    case 1:  adicionarInquilino();                        break;
            case 2:  pesquisarInquilino();                        break;
            case 3:  exibirTodosInq();                            break;
            case 4:  registrarPagamento();                        break;
            case 5:  pagamentosPendentes();                       break;
            case 6:  valorNovoAluguel();                          break;
            case 7:  quitarDivida();                              break;
            case 8:  mostrarHistorico();                          break; 
            case 9:  relatorioPagamentos();                       break;
            case 10: removerInquilino();                          break;
            case 11: salvarDados();                               break; 
            case 12: apagarDados();                               break;
            case 0:                                               break;
            default: mensagem("OPÇÃO INVALIDA, TENTE NOVAMENTE!", "vermelho");
			                                                      break;
		}
	}while(op != 0);	
	
	return 0;
}
