#define tacogerador 4 //pode ser substituido por um potenciometro, ou qualqer outro sensor analógico

#define n 20 //número de iterações do filtro, quanto maior melhor o resultado, porem gera maior atraso....

long moving_average(); //declaração do protótipo da função do filtro

unsigned long timeold; //armazena o tempo de inicialização do sistema
void atraso(); // declaração do protótipo da função do delay

int       original,      //armazena aquisição original   
          filtrado;       //armazena a aquisição depois do filtro 

int       numbers[n];  //vetor volátil para o armazenamento dos dados das iterações

void setup() {
  Serial.begin(9600);    
  pinMode(tacogerador, INPUT);   

  timeold = 0;

}

void atraso(){
if (micros() - timeold >= 100000)
	{
		timeold = micros();
    original = analogRead(tacogerador);
    filtrado = moving_average(); //armazena o valor retornado pela função do filtro

		Serial.println("filtrado = ");
		Serial.println(filtrado, DEC);
    Serial.println("original = ");
		Serial.println(original, DEC);
    
	}
    
}

void loop() {

  atraso();//

}
long moving_average()
{

  
   for(int i= n-1; i>0; i--) numbers[i] = numbers[i-1]; //armazena os dados no vetor de n posições consecutivamente

   numbers[0] = original; //inicia o calculo no vetor de posição zero

   long acc = 0;  //inicializa a variável de acumulação em 0       

   for(int i=0; i<n; i++) acc += numbers[i]; // move a posição dos vetores, adquirindo um novo na ultima posição e removendo o da primeira posição


   return acc/n; // realiza o retorna da operação de média, em que a soma acumulada dos vetores é dividida pelo número dos vetores

 
} 
