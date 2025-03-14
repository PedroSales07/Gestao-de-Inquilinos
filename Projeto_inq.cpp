/*
//------------// Cr�ditos //----------//
Desenvolvedor:   Pedro Paulo Dias Sales
Data de Cria��o: 14/03/2025 
Contatos: 
Email    -       pedrosalesmcd@gmail.com
WhatsApp -       (21) 96865-6996
Descri��o:
	Este programa foi desenvolvido para auxiliar na gest�o de inquilinos, 
	permitindo o controle de informa��es como CPF, nome, idade, sexo, 
	d�vidas e pagamentos de aluguel. O sistema facilita opera��es como 
	o c�lculo de d�vidas, a verifica��o de inadimpl�ncia, o controle de 
	pagamentos, al�m de gerar relat�rios sobre a situa��o financeira dos 
	inquilinos.
	
	Funcionalidades:
	- Cadastro de inquilinos e controle de informa��es pessoais.
	- Registro de pagamentos e c�lculo de d�vidas.
	- Exibi��o de inquilinos com pend�ncias.
	- Relat�rios financeiros, incluindo totais pagos e devidos.
	- Op��es para editar, remover ou apagar dados de inquilinos.
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

//--------------------------------------------------------//informa��es de login 
string usuarioCorreto = "acesso"; 
string senhaCorreta = "9999";   

//---------------------------------------------------------//Sistema de Login com senha e usu�rio.
bool autenticar(){
	string usuario, senha;
	int tentativas = 3;
	
	while(tentativas > 0){
		system("cls");
        system("color F0");
        cout<<"_________SISTEMA DE LOGIN_________"<<endl;
        cout<<"Usu�rio: "; cin>>usuario;
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

//---------------------------------------------------------//Fun��o para verificar se existe cpf cadastrado.
bool verificarCpf(string cpf){
		for(int i = 0; i < total; i++){
        if(inquilino[i].cpf == cpf){
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------//Fun��o para verificar se o sexo � v�lido.
bool verificarSexo(char sexo){
	if(sexo == 'M' || sexo == 'F'){
		return true; 
	}else{
		return false;
	}
}

//---------------------------------------------------------//Fun��o para verificar se a idade � v�lida.	
bool verificarIdade(int idade){
	if(idade<18){
		return false;
	}else{
		return true;
	}
}

//---------------------------------------------------------//Fun��o para verificar se o m�s � v�lido.
bool verificarMes(int mes){
    if(mes >= 1 && mes <= 12){
    	return true;
	}else{
		return false;
	}
}

//---------------------------------------------------------//Fun��o para zarar os valores para o novo inquilino.
void zerandoContadores(Pessoa &inq){
	inq.deveAluguel = false;  
    inq.divida = 0; 
    for(int i=0;i<12;i++){
    	inq.pagamentos[i] = 0;
	}
}

//---------------------------------------------------------//Fun��o "mensagem".
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

//---------------------------------------------------------//Fun��o para adicionar um novo inquilino.
void adicionarInquilino(){
	system("cls");
	cout<<"_________ADICIONAR INQUILINO__________"<<endl<<endl;
	if(total<100){
		cout<<"INQUILINO "<<total + 1<<endl;
		
		//------------------CPF-------------------//
		cout<<"CPF: "; cin>>inquilino[total].cpf;
		if(verificarCpf(inquilino[total].cpf)==true){
			mensagem("INQUILINO J� CADASTRADO","vermelho");
			return;
		}
		
		//------------------NOME------------------//
		cout<<"NOME: "; cin>>inquilino[total].nome;
		
		//------------------SEXO------------------//
		do{
            cout<<"SEXO (M/F): "; cin>>inquilino[total].sexo;
            inquilino[total].sexo = toupper(inquilino[total].sexo); 
            if(verificarSexo(inquilino[total].sexo)==false){
                mensagem("SEXO INV�LIDO! TENTE NOVAMENTE.", "vermelho");
            }
        } while (verificarSexo(inquilino[total].sexo)==false);
		
		//------------------IDADE-----------------//
		do{
            cout<<"IDADE: "; cin>>inquilino[total].idade;
            if(verificarIdade(inquilino[total].idade)==false){
                mensagem("IDADE INV�LIDA! TENTE NOVAMENTE.", "vermelho");
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

//---------------------------------------------------------//Fun��o para exibir funcion�rio da posi��o [i].
void exibirInquilino(int i){
    cout<<endl<<"INQUILINO "<<i + 1<<endl;
    cout<<"CPF...........: "<<inquilino[i].cpf<<endl;
    cout<<"NOME..........: "<<inquilino[i].nome<<endl;
    cout<<"SEXO..........: "<<inquilino[i].sexo<<endl;
    cout<<"IDADE.........: "<<inquilino[i].idade<<endl;
    cout<<"DEVE ALUGUEL..: "<<(inquilino[i].deveAluguel ? "SIM" : "N�O")<<endl;
    cout<<"_______________________________"<<endl;
}

//---------------------------------------------------------//Fun��o para exibir todos os funcion�rios cadastrados.
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

//---------------------------------------------------------//Fun��o para configurar novo valor do aluguel.
void valorNovoAluguel(){
	system("cls");
	cout<<"_________CONFIGURAR VALOR DO ALUGUEL_________"<<endl;
    cout<<"NOVO VALOR: R$ "; cin>>valorAluguel;
    
    if(valorAluguel < 500){
        mensagem("VALOR INV�LIDO! O VALOR DEVE SER MAIOR QUE 499.", "vermelho");
    }else{
    	ostringstream oss;
		oss<<fixed<<setprecision(2)<<valorAluguel;
		mensagem("VALOR DO ALUGUEL CONFIGURADO PARA R$ " + oss.str(), "verde");

        system("pause");
    }
}

//---------------------------------------------------------//Fun��o para registrar os pagamentos.
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
			cout<<endl<<"M�S (1-12): "; cin>>mes;	
				if(verificarMes(mes)==false){
		                mensagem("M�S INV�LIDO!", "vermelho");
		                return;
		            }	            
				if(inquilino[i].pagamentos[mes - 1] > 0){
		                mensagem("PAGAMENTO J� REGISTRADO PARA ESTE M�S!", "vermelho");
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
	mensagem("INQUILINO N�O ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Fun��o para exibir pagamentos pendentes.
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
            cout<<"D�VIDA TOTAL..: R$ "<<inquilino[i].divida<<endl;
            cout<<"-------------------------------------"<<endl;
            encontrouDivida = true;
        }
    }
    if(encontrouDivida==false){
        mensagem("Todos os inquilinos est�o em dia com os pagamentos!","verde");
    }
    system("pause"); 
}

//---------------------------------------------------------//Fun��o para pesquisar inquilinos.
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
    mensagem("INQUILINO N�O ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Fun��o para exibir o hist�rico de pagamentos.
void mostrarHistorico(){
	system("cls");
    string cpfBusca;
    cout<<"_________HIST�RICO DE PAGAMENTOS_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;

    for(int i = 0; i < total; i++){
        if (inquilino[i].cpf == cpfBusca) {
            exibirInquilino(i);
            cout << "----------------------------------------" << endl;

            cout<<"M�S       VALOR PAGO (R$)"<<endl;
            cout<<"----------------------------------"<<endl;
            for(int mes = 0; mes < 12; mes++){
                cout<<mes + 1 << "         " <<inquilino[i].pagamentos[mes]<<endl;
            }
            cout<<"-----------------------------------------"<<endl;
            cout<<"D�VIDA TOTAL: R$ "<<inquilino[i].divida<<endl;
            system("pause");
            return;
        }
    }
    mensagem("INQUILINO N�O ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Fun��o para quitar d�vida do respectivo inquilino.
void quitarDivida() {
    string cpfBusca;
    float valorPago;

    system("cls");
    cout<<"_________QUITAR D�VIDA_________"<<endl;
    cout<<"CPF: "; cin>>cpfBusca;

    for(int i = 0; i < total; i++){
        if(inquilino[i].cpf == cpfBusca){
            if(inquilino[i].divida <= 0){
                mensagem("ESTE INQUILINO N�O POSSUI D�VIDAS!", "verde");
                return;
            }

            cout<<"D�VIDA ATUAL: R$ "<<inquilino[i].divida<<endl;
            cout<<"VALOR A SER PAGO: R$ "; cin>>valorPago;

            if(valorPago <= 0){
                mensagem("VALOR INV�LIDO! DIGITE UM VALOR MAIOR QUE ZERO.", "vermelho");
                return;
            }

            inquilino[i].divida -= valorPago;

            if(inquilino[i].divida <= 0){
                inquilino[i].divida = 0;
                inquilino[i].deveAluguel = false; 
                mensagem("D�VIDA TOTALMENTE QUITADA! PARAB�NS!", "verde");
            }else{
                mensagem("PAGAMENTO REGISTRADO! D�VIDA RESTANTE: R$ ", "verde");
                cout<<inquilino[i].divida;
            }
            return;
        }
    }
    mensagem("INQUILINO N�O ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Fun��o exibi o relat�rio de pagamentos.
void relatorioPagamentos(){
	system("cls");
	int inquilinosEmDia = 0;
    int inquilinosComDivida = 0;
    float totalRecebido = 0;
    float totalDividas = 0;
	
	cout<<"_________RELAT�RIO DE PAGAMENTOS_________"<<endl;
	
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
    cout<<"Total com d�vida.......: "<<inquilinosComDivida<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"Receita................: R$ "<<totalRecebido<<endl;
    cout<<"D�vidas................: R$ "<<totalDividas<<endl;
    cout<<"_________________________________________"<<endl;
    system("pause");
}

//---------------------------------------------------------//Fun��o para salvar os dados.
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

//---------------------------------------------------------//Fun��o para carregar os dados.
void carregarDados(){
    ifstream arquivo("inquilinos.txt");
    if(!arquivo.is_open()){
        mensagem("Arquivo de dados n�o encontrado. Criando novo arquivo...", "vermelho");
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

//---------------------------------------------------------//Fun��o para remover o respectivo inquilino.
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
                mensagem("OPERA��O CANCELADA!.", "vermelho");
            }
            return;
        }
    }
    mensagem("INQUILINO N�O ENCONTRADO!", "vermelho");
}

//---------------------------------------------------------//Fun��o para apagar todos os dados.
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
        mensagem("OPERA��O CANCELADA!", "vermelho");
    }
}

//---------------------------------------------------------//Fun��o Menu.
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
    cout << " [7]  Quitar D�vida                      " << endl;
    cout << " [8]  Exibir Hist�rico de Pagamentos     " << endl;
    cout << " [9]  Relat�rio de Pagamentos            " << endl;
    cout << " [10] Remover Inquilino                  " << endl;
    cout << " [11] Salvar dados                       " << endl;
    cout << " [12] Apagar dados                       " << endl;
    cout << " [0]  Sair                               " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Escolha uma op��o: ";
}

//---------------------------------------------------------//Fun��o Principal.
int main(){
	//-----------------------------------------------------//Define a localidade para portugu�s brasileiro
	setlocale(LC_ALL, "portuguese");
	
	//-----------------------------------------------------//verifica��o de login
	if (autenticar()==false) {
        return 0; 
    }
	
	//-----------------------------------------------------//Carrega os dados dos inquilinos
    carregarDados();
	
	int op;
	do{
		exibirMenu(); //-----------------------------------// Chama a fun��o "menu"
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
            default: mensagem("OP��O INVALIDA, TENTE NOVAMENTE!", "vermelho");
			                                                      break;
		}
	}while(op != 0);	
	
	return 0;
}
