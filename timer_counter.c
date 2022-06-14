// 방법1)

#define F_CPU 7372800UL

#include <avr/io.h>

#include <stdio.h>

#include <util/delay.h>

​

unsigned char flag = 0;

char mess[100] = { 0 };

​

void serial_init(unsigned long baud) {

	unsigned short ubrr;

	//보레이트 설정

	ubrr = (unsigned short)(F_CPU / (16 * baud) - 1);

	UBRR0H = (unsigned char)(ubrr >> 8); //상위 비트

	UBRR0L = (unsigned char)(ubrr & 0xff); //하위 비트

	UCSR0B = 0b00011000; //인터럽트 불가능하게 함,수신부 가능, 송신부 가능

	UCSR0C = 0b00000110; //비동기모드, 패리티비트 사용안함, 정지비트 1비트, 문자크기 8비트

}

​

void tx_data(unsigned char data) { //데이터 송신함수

	while ((UCSR0A & 0x20) == 0x00); //data가 비었는지 확인(UDR0에 데이터가 있으면 while문에 멈춰있음)

	UDR0 = data; //tx와 rx 값을 저장하는 레지스터 UDR

}

​

void tx_string(char* str) { //UART 문자열 전달 함수, *string 포인터가 문자열 첫 글자 주소를 가리킴 

	while (*str != '\0') { // 문자열 끝(null)이 올때까지 이하 내용 수행

		tx_data(*str++); // *str 배열에 저장된 문자 송신하여 값 1증가시켜 다음 문자열 가리킴

	}

}

​

void set_servo_motor() { //서보모터 설정(16비트)

	TCCR1A = 0x82; // Fast PWM 모드 설정

	TCCR1B = 0x1a; // Fast PWM, 분주비 8, TOP값 ICRn (WGMn3:0=1110)

	ICR1 = 18432; // (7372800/8) * 0.02s(20ms)(20ms->반송주기)

	OCR1A = 1843; //초기 각도 설정(18432 * 2.0ms(0.002s)=1843.2)

}

​

int main(void) {

	DDRD = 0x00; //입력포트 설정(스위치)

	DDRB = 0xff; //출력포트 설정(서보모터,PB5)

	unsigned int angle = 0;

	serial_init(115200);

	set_servo_motor();

	​

		while (1) {

			if ((~PIND & 0x0f) == 0x01) { //0번째 스위치를 눌렀을 때

				_delay_ms(20);

				flag++; //flag 증가

				while (~PIND & 0x01); //스위치를 떼면 while이 거짓이 되면서 다음 문장 실행

			}

			if (flag == 1) {

				OCR1A = 1382; //각도 0도 설정(921600 * 1.5ms(0.0015s)=1382.4)

				_delay_ms(20);

			}

			else if (flag == 2) {

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(20);

			}

			else if (flag == 3) {

				OCR1A = 2119; //각도 180도 설정(921600 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(20);

			}

			else if (flag > 3) {

				flag = 1;

			}

			​

			else if ((~PIND & 0x0f) == 0x02) { //1번째 스위치를 눌렀을 때

				OCR1A = 2119; //각도 180도 설정(921600 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(80);

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(80);

				while (~PIND & 0x02);

			}

			​

			else if ((~PIND & 0x0f) == 0x04) { //2번째 스위치를 눌렀을 때

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(80);

				OCR1A = 2119; //각도 180도 설정(921600 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(80);

			}

			​

			else if ((~PIND & 0x0f) == 0x08) { //3번째 스위치를 눌렀을 때

				while ((~PIND & 0x0f) == 0x08) { //3번째 스위치를 누르는 동안에

					OCR1A = OCR1A + 8; //1도에 8씩 움직이므로 8씩 더함

					_delay_ms(10);

					if (OCR1A > 2119) OCR1A = 645;

				}

				angle = (OCR1A - 645) / 8; //8(0도, 90도, 180도 차이 각이 737-> 737/90도=약8-> 1도에 8씩)

				if (angle > 180) angle = 180;

				sprintf(mess, "%d\r", angle);

				tx_string(mess);

				_delay_ms(30);

			}

		}

	​

}

​

// 방법2)

#define F_CPU 7372800UL

#include <avr/io.h>

#include <stdio.h>

#include <util/delay.h>

​

unsigned char flag = 0;

char mess[100] = { 0 };

​

void serial_init(unsigned long baud) {

	unsigned short ubrr;

	//보레이트 설정

	ubrr = (unsigned short)(F_CPU / (16 * baud) - 1);

	UBRR0H = (unsigned char)(ubrr >> 8); //상위 비트

	UBRR0L = (unsigned char)(ubrr & 0xff); //하위 비트

	UCSR0B = 0b00011000; //인터럽트 불가능하게 함,수신부 가능, 송신부 가능

	UCSR0C = 0b00000110; //비동기모드, 패리티비트 사용안함, 정지비트 1비트, 문자크기 8비트

}

​

void tx_data(unsigned char data) { //데이터 송신함수

	while ((UCSR0A & 0x20) == 0x00); //data가 비었는지 확인(UDR0에 데이터가 있으면 while문에 멈춰있음)

	UDR0 = data; //tx와 rx 값을 저장하는 레지스터 UDR

}

​

void tx_string(char* str) { //UART 문자열 전달 함수, *string 포인터가 문자열 첫 글자 주소를 가리킴 

	while (*str != '\0') { // 문자열 끝(null)이 올때까지 이하 내용 수행

		tx_data(*str++); // *str 배열에 저장된 문자 송신하여 값 1증가시켜 다음 문자열 가리킴

	}

}

​

void set_servo_motor() { //서보모터 설정(16비트)

	TCCR1A = 0x82; // Fast PWM 모드 설정

	TCCR1B = 0x1a; // Fast PWM, 분주비 8, TOP값 ICRn (WGMn3:0=1110)

	ICR1 = 18432; // (7372800/8) * 0.02s(20ms)

	OCR1A = 1843; //초기 각도 설정(18432 * 2.0ms(0.002s)=1843.2)

}

​

int main(void) {

	DDRD = 0x00; //입력포트 설정(스위치)

	DDRB = 0xff; //출력포트 설정(서보모터,PB5)

	unsigned int angle = 0;

	serial_init(115200);

	set_servo_motor();

	​

		while (1) {

			if ((~PIND & 0x0f) == 0x01) { //0번째 스위치를 눌렀을 때

				_delay_ms(20);

				flag++; //flag 증가

				while (~PIND & 0x01); //스위치를 떼면 while이 거짓이 되면서 다음 문장 실행

			}

			if (flag == 1) {

				OCR1A = 1382; //각도 0도 설정(921600 * 1.5ms(0.0015s)=27.648)

				_delay_ms(20);

			}

			else if (flag == 2) {

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(20);

			}

			else if (flag == 3) {

				OCR1A = 2119; //각도 180도 설정(18432 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(20);

			}

			else if (flag > 3) {

				flag = 1;

			}

			​

			else if ((~PIND & 0x0f) == 0x02) { //1번째 스위치를 눌렀을 때

				OCR1A = 2119; //각도 180도 설정(18432 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(80);

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(80);

				while (~PIND & 0x02);

			}

			​

			else if ((~PIND & 0x0f) == 0x04) { //2번째 스위치를 눌렀을 때

				OCR1A = 645; //각도 90도 설정(921600 * 0.7ms(0.0007s)=645.12)

				_delay_ms(80);

				OCR1A = 2119; //각도 180도 설정(18432 * 2.3ms(0.0023s)=2119.68)

				_delay_ms(80);

			}

			​

			else if ((~PIND & 0x0f) == 0x08) { //3번째 스위치를 눌렀을 때

				while ((~PIND & 0x0f) == 0x08) { //3번째 스위치를 누르는 동안에

					OCR1A = OCR1A + 8; //1도에 8씩 움직이므로 8씩 더함

					_delay_ms(10);

					if (OCR1A > 2119) OCR1A = 645;

				}

				angle = (OCR1A - 645) / 8; //8(0도, 90도, 180도 차이 각이 737-> 737/90도=약8-> 1도에 8씩)

				if (angle > 180) angle = 180;

				sprintf(mess, "%d\r", angle);

				tx_string(mess);

				_delay_ms(30);

			}

		}

	​

}