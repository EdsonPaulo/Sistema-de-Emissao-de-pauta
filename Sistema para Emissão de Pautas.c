/*-------------------------------------------------------------------------------------------------------
Objectivo:
Autor: Edson Paulo Gregorio;    ID: 20973        Ultima Edicao: 12/07/2018;
--------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_ALUNO 20
#define MAX_AVAL 7
#define MAX_NOME 30

#define PROVA 1
#define TRABALHO 2
/*-------------------------------------------------------------------------------------------------------
	Prototipo de funcoes
--------------------------------------------------------------------------------------------------------*/
int lerTotalDeAlunos();
int lerNumeroDeProvas();
int lerNumeroAluno();
void lerNomeAluno(char nomeAluno[]);
int lerPeso();
int verificarMenorNota(int tipoDeProva, int numProvas, float notas[], int pesos[]);
float lerNota(int i);
float calcularMedia(int numProvas,  float notas[], int pesos[]);
float provaRecuperacao(int tipoDeProva, int numProvas, float notas[], int pesos[]);
void carregarNotas(int numProvas, float notas[], int pesos[]);
void ordenarPauta(int TAlunos, float mediaFinal[], int numeroDosAlunos[], char avaliacao[MAX_ALUNO][MAX_NOME], char nomeDosAlunos[MAX_ALUNO][MAX_NOME]);
void imprimirPauta(int TAlunos, float mediaFinal[], int numeroDosAlunos[], char avaliacao[MAX_ALUNO][MAX_NOME], char nomeDosAlunos[MAX_ALUNO][MAX_NOME]);

/*-------------------------------------------------------------------------------------------------------
Objectivo: Ler o numero de alunos a processar   Retorna: numero de alunos
--------------------------------------------------------------------------------------------------------*/
int lerTotalDeAlunos()
{
	int TAlunos;
	printf("\n\t>> Entre com o numero de estudantes a processar: ");
	scanf("%d", &TAlunos);
	while(TAlunos <= 0 || TAlunos > MAX_ALUNO)
	{
		printf("\n\tERRO: Numero de estudantes invalido. \n\t Re-introduza: ");
		scanf("%d", &TAlunos);
	}
	return TAlunos;
}
/*------------------------------------------------------------------------------------------------------------
Objectivo: Ler o numero de provas ou trabalhos que os estudantes realizaram        Retorna: numero de provas
--------------------------------------------------------------------------------------------------------------*/
int lerNumeroDeProvas()
{
	int numProvas;
	printf("\n\t>> Informe o numero de provas e trabalhos feitos: ");
	scanf("%d", &numProvas);
	while(numProvas <= 0 || numProvas > MAX_AVAL-2)
	{
		printf("\n\tERRO: Numero de provas invalido. \n\t Re-introduza: ");
		scanf("%d", &numProvas);
	}
	return numProvas;
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: Ler a idententificacao de um aluno                   Retorna: ID do aluno
--------------------------------------------------------------------------------------------------------*/
int lerNumeroAluno()
{
	int numeroAluno;
	printf("\n\tEntre com o numero do estudante: ");
	scanf("%d", &numeroAluno);
	while(numeroAluno <= 0)
	{
		printf("\n\tERRO: Numero do estudante invalido. \n\t Re-introduza: ");
		scanf("%d", &numeroAluno);
	}
	return numeroAluno;
}

/*-----------------------------------------------------------------------------------------------------------------
Objectivo: Ler nome de um aluno         Recebe: vertor nomesAlunos    Devolve: vetor com mais um nome de aluno
-------------------------------------------------------------------------------------------------------------------*/
void lerNomeAluno(char nomeAluno[])
{
	int i = 0;
	printf("\n\tInforme o nome do estudante: ");
	fflush(stdin);
	gets(nomeAluno);
	while(nomeAluno[i] != '\0')
	{  
		if (!(nomeAluno[i] >= 'A' && nomeAluno[i] <= 'a' || nomeAluno[i] >= 'Z' && nomeAluno[i] <= 'z' || nomeAluno[i] == ' '))	
		{
			printf("\n\tERRO: Nome invalido. \n\t Informe o nome do estudante: ");
			fflush(stdin);
			gets(nomeAluno);
			i = 0;
		} 
		i++;
	}
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: Ler uma nota            Retorna: Nota lida    
--------------------------------------------------------------------------------------------------------*/
float lerNota(int numDaProva)
{
	float nota;
	if (numDaProva > 0)
		printf("\n\tDigite a nota %d: ", numDaProva);
	else
		printf("\tDigite a nota da prova de Recuperacao: ");
	scanf("%f", &nota);
	while(nota < 0.0 || nota > 20.0)
	{
		printf("\n\tERRO: Nota invalida. \n\t Redigite-a: ");
		scanf("%f", &nota);
	}
	return nota;
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: Ler o peso de cada avaliacao              retorna: o peso de lido se for valido
--------------------------------------------------------------------------------------------------------*/
int lerPeso()
{
	int peso;
	printf("\tO Peso da prova: ");
	scanf("%d", &peso);
	while(peso < 1 || peso > 6)
	{
		printf("\n\tERRO: O Peso vai de 1 a 6.  \n\t Redigite-o: ");
		scanf("%d", &peso);
	}
	return peso;
}
/*--------------------------------------------------------------------------------------------------------------------------------
Objectivo: Carregar um vetor com as notas e um com os pesos /  Recebe: vetor notas e vetor pesos  /  Devolve: os vectores carregados
----------------------------------------------------------------------------------------------------------------------------------*/
void carregarNotas(int numProvas, float notas[], int pesos[])
{
	int i;
	for(i = 0; i < numProvas; i++)
	{
		notas[i] = lerNota(i+1);
		pesos[i] = lerPeso();
	}
	notas[numProvas] = 0.0;
	pesos[numProvas] = 0;
}

/*-------------------------------------------------------------------------------------------------------
Objectivo: Calcular media das provas    Recebe: numero de provas, vetor com notas e vetor com pesos
--------------------------------------------------------------------------------------------------------*/
float mediaDasProvas(int numProvas, float notasDasProvas[], int pesoDasProvas[], float Mp)
{	
	if(Mp >= 6.0 && Mp <= 10.0)
		return provaRecuperacao(PROVA, numProvas, notasDasProvas, pesoDasProvas);
	else
		return Mp;
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: Calcular media dos trabalhos    Recebe: numero de trabalhos, vetor com notas e vetor com pesos
--------------------------------------------------------------------------------------------------------*/
float mediaDosTrabalhos(int numTrabalhos, float notasDosTrabalhos[], int pesoDosTrabalhos[], float Mt)
{
	if(Mt >= 4.0 && Mt < 9.0)
		return provaRecuperacao(TRABALHO, numTrabalhos, notasDosTrabalhos, pesoDosTrabalhos);
	else
		return Mt;
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: calcular notafinal    Retorna: a nota final
--------------------------------------------------------------------------------------------------------*/
float NotaFinal(float Mp, float Mt, float MTR, float MPR)
{
	float Nf, NFR;
	if(Mp > 14.0 && Mt > 12.0)
		Nf = Mp * 0.6 + Mt * 0.4;   
	else{
		if(Mp < Mt)
			Nf = Mp;
		else
			Nf = Mt;
	}

	if(MPR == Mp && MTR == Mt)
		NFR = Nf;
	else{
		float MPRR = (Mp + 2*MPR)/3;
		if(MPRR > Nf)
			NFR = MPRR;
		else
			NFR = Nf;
	}
	printf("\n\t\t Medias Mp:%.1f  Mt:%.1f  MPR:%.1f  MTR:%.1f  Nf:%.1f  NFR:%.1f\n", Mp, Mt, MPR, MTR, Nf, NFR);
	return NFR;
}
/*-----------------------------------------------------------------------------------------------------------------
Objectivo: Calcular media das provas e/ou dos trabalhos                         Retorna: a media ponderada das notas
Recebe: o numero de provas, vector com os pesos e vector com asnotas           
--------------------------------------------------------------------------------------------------------------------*/
float calcularMedia(int numProvas,  float notas[], int pesos[])
{
	float numerador = 0.0;
	int i, denominador = 0;
	for(i = 0; i <= numProvas-1; i++)
	{
		numerador += pesos[i] * notas[i];
		denominador += pesos[i];
	}
	return numerador/denominador;
}

/*----------------------------------------------------------------------------------------------------------------
Objectivo: verificar a menor nota do vetor com as notas      Retorna: posicao da menor nota
Recebe: vetor com notas, numProvas e vetor com os pesos
-------------------------------------------------------------------------------------------------------------*/
int verificarMenorNota(int tipoDeProva, int numProvas, float notas[], int pesos[])
{
	int i, posMenorNota = 0, menosPeso = pesos[0];
	float menorNota = notas[0];
	for(i = 1; i < numProvas; i++)
	{
		if(menorNota > notas[i])
		{
			menorNota = notas[i];
			menosPeso = pesos[i];
			posMenorNota = i;
		}
		else if(menorNota == notas[i])
			{
				if(tipoDeProva == PROVA) //se for prova a menor nota eh a  de menos peso, se for trabalho eh a de mais peso
				{                    
					if(menosPeso > pesos[i])
					{
						menosPeso = pesos[i];
						posMenorNota = i;
					}
				}
				else if(menosPeso < pesos[i])
					{
						menosPeso = pesos[i];
						posMenorNota = i;
					}	
			}
	}
	return 	posMenorNota;
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: substituir a menor nota das provas pela nota de recuperacao se esta for maior que a menor nota
Recebe: numProvas, vetor com notas, e pesos..      Retorna: a nova MEDIA
--------------------------------------------------------------------------------------------------------*/
float provaRecuperacao(int tipoDeProva, int numProvas, float notas[], int pesos[])
{
	int posMenorNota = verificarMenorNota(tipoDeProva, numProvas, notas, pesos);
	printf("\n\n\t\tOBS: Estudante em recuperacao!\n");
	float NPR = lerNota(0);
	if(NPR > notas[posMenorNota])
	{
		notas[posMenorNota] = 0.0; //remove a menor nota atribuindo zero. para substituir pela nota de recuperacao
		notas[numProvas] = NPR; //armazena a nota do recurso na ultima pos.
		pesos[numProvas] = pesos[posMenorNota];
		pesos[posMenorNota] = 0;
	}
	return calcularMedia(numProvas, notas, pesos);
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: Ordenar a pauta na forma decrescente em funcao da media final
--------------------------------------------------------------------------------------------------------*/
void ordenarPauta(int TAlunos, float mediaFinal[], int numeroDosAlunos[], char avaliacao[MAX_ALUNO][MAX_NOME], char nomeDosAlunos[MAX_ALUNO][MAX_NOME])
{
	int  j, i;
	for (i = 0; i < TAlunos; i++)
		for(j = i + 1; j < TAlunos; j++)
		{
			float auxMed;
			int auxNum;
			char auxNome[MAX_NOME], auxAval[MAX_NOME];
			if (mediaFinal[i] < mediaFinal[j])
			{
				auxMed = mediaFinal[i];
				auxNum = numeroDosAlunos[i];
				strcpy(auxAval, avaliacao[i]);
				strcpy(auxNome, nomeDosAlunos[i]);
				
				mediaFinal[i] = mediaFinal[j];
				numeroDosAlunos[i] = numeroDosAlunos[j];
				strcpy(avaliacao[i], avaliacao[j]);
				strcpy(nomeDosAlunos[i] , nomeDosAlunos[j]);
				
				mediaFinal[j] = auxMed;
				numeroDosAlunos[j] = auxNum;
				strcpy(avaliacao[j], auxAval);
				strcpy(nomeDosAlunos[j] , auxNome);
			}
		}
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: imprimir a pauta na forma decrescente da media final
--------------------------------------------------------------------------------------------------------*/
void imprimirPauta(int TAlunos, float mediaFinal[], int numeroDosAlunos[], char avaliacao[MAX_ALUNO][MAX_NOME], char nomeDosAlunos[MAX_ALUNO][MAX_NOME])
{
	printf("\n\n\t===================================================================");
	printf("\n\t|-----------------------| PAUTA FINAL |---------------------------|");
	printf("\n\t===================================================================\n");
	printf("\n\tID\t|\tNome\t|  Nota Final  |\t  Avaliacao \n");
	int i;
	for(i=0; i < TAlunos; i++)
		printf("\n\t%d \t %s\t\t%.1f \t\t%s", numeroDosAlunos[i], nomeDosAlunos[i], mediaFinal[i], avaliacao[i]);
}
/*-------------------------------------------------------------------------------------------------------
Objectivo: imprimir as estatisticas dos alunos por conceito    Recebe: total de alunos e alunos por conceito
--------------------------------------------------------------------------------------------------------*/
void imprimirClassificacao(int TAlunos, int excelente, int muitoBom, int suficiente, int mediocre, int mau)
{
	float factor = 100/TAlunos;
	printf("\n\n\t------------------------------------------------------------------\n");
	printf("\t\t\tEstudantes por Conceito: \n");
	printf("\n\t\t EXCELENTE \t %d estudantes \t[%.1f%%]", excelente, excelente*factor);
	printf("\n\t\t MUITO BOM \t %d estudantes \t[%.1f%%]", muitoBom, muitoBom*factor);
	printf("\n\t\t SUFICIENTE\t %d estudantes \t[%.1f%%]", suficiente, suficiente*factor);
	printf("\n\t\t MEDIOCRE  \t %d estudantes \t[%.1f%%]", mediocre, mediocre*factor);
	printf("\n\t\t MAU       \t %d estudantes \t[%.1f%%]", mau, mau*factor);
	printf("\n\n\t------------------------------------------------------------------\n");
}
/*-------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------*/
int main()
{
	int TAlunos, i, numProvas;
	int pesoDasProvas[MAX_AVAL], pesoDosTrabalhos[MAX_AVAL], numeroDosAlunos[MAX_ALUNO];
	float notasDasProvas[MAX_AVAL], notasDosTrabalhos[MAX_AVAL], mediaFinal[MAX_ALUNO];
	float Mp, Mt, MPR, MTR, NFR;
	char nomeDosAlunos[MAX_ALUNO][MAX_NOME], avaliacao[MAX_ALUNO][MAX_NOME];
	int excelente = 0, muitoBom = 0, suficiente = 0, mediocre = 0, mau = 0;

	printf("\n\t====================================================================================");
	printf("\n\t|========================| SISTEMA PARA EMISSAO DE PAUTAS |========================|");
	printf("\n\t====================================================================================\n");

	TAlunos = lerTotalDeAlunos();
	numProvas = lerNumeroDeProvas();

   //Processar Alunos do primeiro ao total de alunos
	for(i = 0; i < TAlunos; i++)
	{
		printf("\n\n\t-------------------------------------------------------");
		printf("\n\t\tEstudante %d", i+1);

		numeroDosAlunos[i] = lerNumeroAluno();
		lerNomeAluno(nomeDosAlunos[i]);
		
		printf("\n\n\t==== Notas das %d provas ====\n", numProvas);
		carregarNotas(numProvas, notasDasProvas, pesoDasProvas);
		Mp = calcularMedia(numProvas, notasDasProvas,  pesoDasProvas); //media das provas
		MPR = mediaDasProvas(numProvas, notasDasProvas, pesoDasProvas, Mp); //media das provas com recurso
		
		printf("\n\n\t==== Notas dos %d trabalhos ====\n", numProvas);
		carregarNotas(numProvas, notasDosTrabalhos, pesoDosTrabalhos);
		Mt = calcularMedia(numProvas, notasDosTrabalhos, pesoDosTrabalhos); //media dos trabalhos
		MTR = mediaDosTrabalhos(numProvas, notasDosTrabalhos, pesoDosTrabalhos, Mt); //media das provas com recurso

		NFR = NotaFinal(Mp, Mt, MTR, MPR);

		if(NFR > 18.0){
			strcpy(avaliacao[i], "EXCELENTE");
			excelente++;
		}
		else if(NFR > 14.0){
				strcpy(avaliacao[i], "MUITO BOM");
				muitoBom++;
			}
			else if(NFR > 9.0){
					strcpy(avaliacao[i], "SUFICIENTE");
					suficiente++;
				}
				else if(NFR > 4.0){
						strcpy(avaliacao[i], "MEDIOCRE");
						mediocre++;
					}
					else{
						strcpy(avaliacao[i], "MAU");
						mau++;
					}
		mediaFinal[i] = NFR;
	}

	ordenarPauta(TAlunos, mediaFinal, numeroDosAlunos, avaliacao, nomeDosAlunos);

	imprimirPauta(TAlunos, mediaFinal, numeroDosAlunos, avaliacao, nomeDosAlunos);

	imprimirClassificacao(TAlunos, excelente, muitoBom, suficiente, mediocre, mau);

	printf("\n\n");
	system ("PAUSE");
	return 0;
}
