  // SEL0433/SEL0614/SEL0336 - Aplic. de Microprocessadores
  // Exemplo: Uso do conversor AD para leituras analógicas com bilbiotecas
  
// Uso do conversor ADC para realizar uma leitura analógica (sinal de tensão)
// com número float e 2 casas decimais, usando o TRIMPOT "ADC Input" do kit EasyPIC v7

  // será usado o canal analógico AN4/RA5 - para ler o sinal de tensão analógico
  //o qual irá variar conforme o ajuste do TRIMPOT (simulando uma variação analógica
  // de um sensor, por exemplo)

  // Device:  PIC18F4550 - Clock  = 8 MHz
  // tensãoo de ref. interna do ADC 0 - 5V
  
  // ***necessário add bibliotecas LCD e conversão de dados em "Libray Manager"***

  // Configurações necessárias: Jumper no "trimpot ADC input" RA5 (PORT A - 1 trimpot)
  // habilitar o display LCD em SW4 e se necessário ajsutar o contraste no trimpot
  // correspondente

//------------------------------------------------------------------------------
// Config. de pinos do LCD  (PORTB)

/*Include*/

/*Diretivas de pré-compilação*/
 #define TRUE  1  // assim: while(TRUE) = while(1)

// config. dos pinos para o LCD

// pinos utilizados para comunicação com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "
// dire��o do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // direção do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

/*Programa Principal*/

void main(){

  unsigned int Valor_ADC = 0;  // var. para leitura
  unsigned char Tensao[10];    // arranjo textual para exibir no display

    //lembrando que os pinos agora devem ser configurados como analógicos
  TRISA.RA5 = 1;
  ADCON1 = 0B00000000; //Configura todos os canais como ADC no PIC18F4450


 // Configuração do módulo LCD
  Lcd_Init();                 // Inicializa a lib. Lcd
  Lcd_Cmd(_LCD_CLEAR);       // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);  // Cursor off
  Lcd_Out(1,1,"ADC0:");   //Escreve na Linha x Coluna do LCD o texto(valor do ADC)

  ADC_Init();  // uso da função da biblioteca ADC do próprio compilador
  //- incializa o módulo ADC

 while(TRUE)
  {
    Valor_ADC = ADC_Read(4); // função da biblioteca ADC do compilador para
    //leitura dos valores de 0 a 1023 (10 bits)  - ex.:  valor_ADC = 1023;
    // onde: 4 é o número do canal analógico usado, no caso AN4, no pino RA5

    // Ajustes de escala dos valores de conversão para colocar no formato float
    // de 2 casas após a virgula. Tomando como exemplo valores de 0 a 12.34 para
    // a escala de 0 a 1023 do conversor:

    Valor_ADC = Valor_ADC * (1234/1023.); // formata o valor de entrada (neste caso o valor de exemplo '1234')
    // para 0 a 1023 -> com ponto no final para nº float,i.e.,o display mostrará: '12.34'

    // Formatando cada valor a ser exibido no display como "12.34"
    Tensao[0] = (Valor_ADC/1000) + '0';// div. de 2 nº inteiros - em programação
    // resulta na parte inteira do primeiro nº (ex.: 1234/1000 = 1)
    // E '1' + '0'  = 1; ou seja,  converte o valor para ASCI  para exibir no display

    Tensao[1] = (Valor_ADC/100)%10 + '0'; // div. de nº inteiros => 1234/100 = 12
    // '%' em ling. C a operação "mod"  c/ resto da divisão, ou seja, 12%10 = 2
    // portanto, formata o segundo nº no display no padrão ASCI ( '2' + '0' = 2)

    Tensao[2] = '.';    //3º valor corresponde ao ponto - ex. 12.34

    Tensao[3] = (Valor_ADC/10)%10 + '0'; // 4º valor é a 1ª casa decimal, portanto:
    // 1234/10 = 123%10 = 3  - formata no padrão ASCI
    Tensao[4] = (Valor_ADC/1)%10 + '0';  // formata o valor da 2� casa decimal

    Tensao[5] = 0; //terminador NULL (ultima posição da matriz - zero indica o
    //final operção e limita a exibição dos 5 valores anteriores: 12.34), ou seja
    // a partir daqui, não serão mais exibidos valores, os quais poderão ser
    //adicionados caso se deseja exibir, por ex., mais casas decimais

    //floatToStr(Valor_ADC , Tensao);
    //Tensao[5] = 0;


     // Exibir os valores na config. acima no display LCD:
    Lcd_Out(1,6,Tensao); // Mostra os valores no display
    Delay_ms(20);   // atualizar display
  }
}