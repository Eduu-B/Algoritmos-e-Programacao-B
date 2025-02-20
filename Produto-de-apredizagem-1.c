#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>                             //NOME: EDUARDO OSMARI BORTOLOTTO

#define qtdepacientes 300

// OBS: como não consegui usar "fgets", nomes e prescrição devem ser recebidos sem espaço e as datas no formato dd/mm/aaaa
typedef struct{
    char data[11];
    float peso; 
    float altura;                             // Estrura para "Última consulta"
    char prescricao[500];
    float valor_pago; 
}dados_consulta;

typedef struct{
    char codigo[10]; 
    char nome_paciente[50];
    char data_nascimento[11];                 // Estrutura para "Dados paciente"
    char nome_mae[50];
    char nome_pai[50];
    dados_consulta consulta; // Variável do tipo dados_consulta
}dados_paciente;

int cadastrados = 0; // Variável global para guardar quantidade de pacientes cadastrados
dados_paciente pacientes[qtdepacientes]; // variável global do tipo dados_paciente

void cadastrar_paciente(){     
    
    char continuar;
    
    // Cadastrar pacientes enquanto o usuário desejar
    while(cadastrados<qtdepacientes) {       
        printf("\nCadastro do paciente %d\n", cadastrados+1);
        printf("Digite o código do paciente: ");
        scanf("%s", pacientes[cadastrados].codigo);
        printf("Nome do paciente: ");
        scanf("%s", pacientes[cadastrados].nome_paciente);
        //fgets(pacientes[cadastrados].nome_paciente, 50, stdin);
        printf("Data de nascimento no formato DD/MM/AAAA: ");
        scanf("%s", pacientes[cadastrados].data_nascimento);
        printf("Nome da Mãe: ");
        scanf("%s", pacientes[cadastrados].nome_mae);
        //fgets(pacientes[cadastrados].nome_mae, 50, stdin);
        printf("Nome do Pai: ");
        scanf("%s", pacientes[cadastrados].nome_pai);
        //fgets(pacientes[cadastrados].nome_pai, 50, stdin);
        cadastrados++;

        printf("\nDeseja continuar o cadastro?\nSe sim digite \"S\"\nse não digite qualquer outra letra\n: ");
        scanf(" %c", &continuar);

        if(toupper(continuar) != 'S') // Verificar se deseja continuar
            return;
    }
}

void registrar_consulta(){
    
    char acesso[50]; 
    
    // Registrar consulta
    printf("\nInforme o código ou nome do paciente(conforme foi cadastrado) para registrar consulta\n: ");
    scanf("%s", acesso); // variável de entrada

    for(int i=0;i<cadastrados;i++) {     
        if(strcmp(acesso, pacientes[i].codigo) == 0 || strcmp(acesso, pacientes[i].nome_paciente) == 0){    // Comparando a entrada com o código e o nome do paciente
            printf("\nData da última consulta no formato DD/MM/AAAA: ");
            scanf("%s", pacientes[i].consulta.data);
            printf("Peso em KG: ");
            scanf("%f", &pacientes[i].consulta.peso);
            printf("Altura em CM: ");
            scanf("%f", &pacientes[i].consulta.altura);
            printf("Prescrição: ");
            //fgets(pacientes[i].consulta.prescricao, 500, stdin);
            scanf("%s", pacientes[i].consulta.prescricao);
            printf("Valor pago em R$: ");
            scanf("%f", &pacientes[i].consulta.valor_pago);
            return;
        }
    }
    
    printf("\nCódigo ou nome do paciente não encontrado!\n"); // Retorna ao menu caso o código ou nome não seja encontrado
    
}

int converte_dia(char data[11]) {
    char aux[5];
    // Covertendo dia para inteiro
    aux[0] = data[0];
    aux[1] = data[1];
    aux[2] = '\0';

    return atoi(aux);
}

int converte_mes(char data[11]) {
    char aux[5];
    // Convertendo mês para inteiro
    aux[0] = data[3];
    aux[1] = data[4];
    aux[2] = '\0';

    return atoi(aux);
}

int converte_ano(char data[11]) {
    char aux[5];
    // Convertendo ano para inteiro
    aux[0] = data[6];
    aux[1] = data[7];
    aux[2] = data[8];
    aux[3] = data[9];
    aux[4] = '\0';

    return atoi(aux);
}

void calcula_idade(int dia_nasc, int mes_nasc, int ano_nasc, int dia_con, int mes_con, int ano_con) {
    
    // Calculo da idade com base na data de nascimento e data da última consulta
    //Calculo ano
    int idade_anos, idade_meses, idade_dias;
    if (mes_nasc > mes_con) {
        idade_anos = ano_con - ano_nasc - 1; // Ajuste para quando não fez aniversário ainda
    } else if (mes_nasc == mes_con) {
        if (dia_nasc > dia_con) {
            idade_anos = ano_con - ano_nasc - 1; // Ajuste para quando não fez aniversário ainda
        } else {
            idade_anos = ano_con - ano_nasc;
        }
    } else {
        idade_anos = ano_con - ano_nasc;
    }

    //Calculo mês
    if (mes_nasc > mes_con) {
        idade_meses = 12 - (mes_nasc - mes_con);
    } else if (mes_nasc == mes_con) {
        if (dia_nasc > dia_con) {
            idade_meses = 11; // O mês é sempre igual a 11, quando os meses são iguais, mas o dia de consulta é menor que o de nascimento
        } else {
            idade_meses = mes_con - mes_nasc;
        }
    }
    else {
        if (dia_nasc > dia_con) {
            idade_meses = mes_con - mes_nasc - 1; // Ajuste para quando não fez aniversário ainda
        } else {
            idade_meses = mes_con - mes_nasc;
        }
    }

    //Calculo dia
    if (dia_nasc > dia_con) {
        idade_dias = 30 - (dia_nasc - dia_con); // Diferença do menor para o maior
    } else {
        idade_dias = dia_con - dia_nasc;
    }

    printf("Idade em dias,meses e ano: %d anos, %d meses, %d dias\n", idade_anos, idade_meses, idade_dias);
}

void visualizar_prescricao() {
    
    char acesso[50];
    int dia_nascimento, mes_nascimento, ano_nascimento;
    int dia_consulta, mes_consulta, ano_consulta;
    
    // Visualizar prescrição
    printf("\nInforme o código ou nome do paciente (conforme foi cadastrado) para visualizar prescrição\n: ");
    scanf("%s", acesso); // variável de entrada

    for(int i=0;i<cadastrados;i++){ 
        if(strcmp(acesso, pacientes[i].codigo) == 0 || strcmp(acesso, pacientes[i].nome_paciente) == 0){   // Comparando a entrada com o código e o nome do paciente
            printf("\nCódigo do paciente: %s\nNome do paciente: %s\n", pacientes[i].codigo, pacientes[i].nome_paciente);

            if (pacientes[i].consulta.altura != 0) { // Verificar se foi registrada alguma consulta

                printf("Data da última consulta: %s\n", pacientes[i].consulta.data);
                
                // Convertendo datas dd/mm/aaaa(string) em valores inteiros com funções
                dia_nascimento = converte_dia(pacientes[i].data_nascimento);
                mes_nascimento = converte_mes(pacientes[i].data_nascimento);
                ano_nascimento = converte_ano(pacientes[i].data_nascimento);
    
                dia_consulta = converte_dia(pacientes[i].consulta.data);
                mes_consulta = converte_mes(pacientes[i].consulta.data);
                ano_consulta = converte_ano(pacientes[i].consulta.data);
                
                // Chamando calcula_idade para fazer o cálculo
                calcula_idade(dia_nascimento, mes_nascimento, ano_nascimento, dia_consulta, mes_consulta, ano_consulta);
                
                printf("Peso: %.2f\nAltura: %.2f\n", pacientes[i].consulta.peso, pacientes[i].consulta.altura);
                printf("Prescrição: %s\n", pacientes[i].consulta.prescricao);
            } else {
                printf("Paciência sem nenhuma consulta registrada\n"); // Caso não tenha sido registrada consulta alguns dados não poderão ser mostrados
            }
            
            return;
        }
    }
                
    printf("\nCódigo ou nome do paciente não encontrado!\n"); // Retorna ao menu caso o código ou nome não seja encontrado
    return;

}

void listar_pacientes(){
    
    // Listando todos os pacientes 
    for(int i=0;i<cadastrados;i++){
        printf("\nPaciente %d\n", i+1);
        printf("Código do paciente: %s\n", pacientes[i].codigo);
        printf("Nome do paciente: %s\n", pacientes[i].nome_paciente);
        printf("Data de nascimento: %s\n", pacientes[i].data_nascimento);
        printf("Nome da Mãe: %s\n", pacientes[i].nome_mae);
        printf("Nome do Pai: %s\n", pacientes[i].nome_pai);
        if (pacientes[i].consulta.altura != 0)  // Verificar se foi registrada alguma consulta
            printf("Data da última consulta: %s\n", pacientes[i].consulta.data);
        else
            printf("Nenhuma consulta registrada\n");
    }
    
    return;
}

void valor_total_recebido_mes() {

    char mes[3], ano[5], mes_temp[3], ano_temp[5];
    float soma = 0;
    //valor total recebido no mês
    printf("\nInforme o número do mês de interesse: "); // Exemplo mês "02","03","08"
    scanf("%s", mes);
    printf("\nInforme o ano de interesse: ");
    scanf("%s", ano);

    for (int i=0;i<cadastrados;i++) {
        // Guardando o mês e o ano da data formato dd/mm/aaaa em variável temporária
        mes_temp[0] = pacientes[i].consulta.data[3];
        mes_temp[1] = pacientes[i].consulta.data[4];
        mes_temp[2] = '\0';

        ano_temp[0] = pacientes[i].consulta.data[6];
        ano_temp[1] = pacientes[i].consulta.data[7];
        ano_temp[2] = pacientes[i].consulta.data[8];
        ano_temp[3] = pacientes[i].consulta.data[9];
        ano_temp[4] = '\0';

        if (strcmp(ano, ano_temp) == 0 && strcmp(mes, mes_temp) == 0) { // Comparando o mês e ano informados com o mês e ano da última consulta
            soma += pacientes[i].consulta.valor_pago; // Soma do valor total recebido no mês
        }
    }

    if(soma != 0) 
        printf("\nValor total recebido no mês: %.2fR$\n", soma); // Mostra o valor total recebido no mês desejado, caso tenha recebido algum valor
    else
        printf("\nNenhum valor recebido no mês\n");
          
    return;
}

int main(){

    char opcao;

    while(1){
        // Menu de opções
        printf("\nMenu de opções\nA) Cadastrar Paciente\nB) Registrar Consulta\nC) Visualizar Prescrição\nD) Listar Pacientes\nE) Valor total recebido no mês\nF) Finalizar\n: ");
        scanf(" %c", &opcao);
        opcao = toupper(opcao);

        switch (opcao) {
            // Escolher a opção para chamar a função
            case 'A':
                cadastrar_paciente();
                break;
            case 'B':
                if(cadastrados == 0){ // Verificar se tem pacientes cadastrados
                    printf("\nNenhum paciente cadastrado!\n");
                }
                else{
                    registrar_consulta();
                }
                break;
            case 'C':
                visualizar_prescricao();
                break;
            case 'D':
                listar_pacientes();
                break;
            case 'E':
                valor_total_recebido_mes();
                break;
            case 'F': 
                printf("\nPrograma finalizado"); // Finaliza o programa
                return 0;

            default:
                printf("\nEscolha uma opção válida!\n");
        }

    }

}
