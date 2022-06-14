01. 타이머 / 카운터


* 타이머 / 카운터 란?

- 카운터 : 입력된 펄스를 세는 장치 (외부 클럭)

- 타이머 : 카운트한 펄스의 개수로 시간 측정 (내부 클럭)

- 프리스케일러 : 타이머에 공급하는 입력 클록의 속도 조절 분주기, 각 타이머/카운터가 가지고 있음

- ATmega128은 8비트 카운터 / 타이머 2개와 16비트 카운터 / 타이머 2개를 제공

   : 8비트 타이머 / 카운터 : 0, 2

   : 16비트 타이머 / 카운터 : 1, 3


02. PWM 신호

1) PWM (Pulse Width Modulation, 펄스 폭 변조)

: 효율적인 스위칭 제어의 기본이 되는, 디지털 출력으로 아날로그 회로를 제어하는 기술

: 일정한 주기 내에서 듀티비 (일률) 를 변화 시켜서 평균 전압을 제어하는 방법

<img width="206" alt="image" src="https://user-images.githubusercontent.com/87634136/173609318-52d83352-71b2-4157-82a5-08efc00b7642.png">


2) PWM 신호의 장점 

: ON-OFF 신호만으로 신호의 크기를 조절할 수 있음

: 전력 소모가 작아짐


3) PWM 신호

<img width="424" alt="image" src="https://user-images.githubusercontent.com/87634136/173609411-470a5966-a88c-45ff-8254-30f2ef8a4d2e.png">


03. 관련 레지스터

( 8비트 관련 레지스터 )

<img width="422" alt="image" src="https://user-images.githubusercontent.com/87634136/173609553-363744fe-d97e-49b3-98b9-a7844bc5c2b4.png">

<img width="428" alt="image" src="https://user-images.githubusercontent.com/87634136/173609609-b6d6fea9-4afb-4cdf-b48e-de09dc09f19a.png">

<img width="427" alt="image" src="https://user-images.githubusercontent.com/87634136/173609651-655f858e-69d9-4a01-bd73-5b7245820f4d.png">

<img width="429" alt="image" src="https://user-images.githubusercontent.com/87634136/173609698-a7434d24-088f-40c0-8b3f-09551fb82f26.png">

<img width="430" alt="image" src="https://user-images.githubusercontent.com/87634136/173609756-84382811-ab14-46dd-8973-b5e98c434a68.png">

<img width="427" alt="image" src="https://user-images.githubusercontent.com/87634136/173609814-e0a7a81d-2b3a-4e38-9a85-82dd134a9a37.png">

<img width="428" alt="image" src="https://user-images.githubusercontent.com/87634136/173609857-513a54bc-0cdc-41f6-a552-cb940bfaa6f7.png">

<img width="428" alt="image" src="https://user-images.githubusercontent.com/87634136/173609908-49991fec-b578-4fda-b0e1-1a93a9519cb4.png">

<img width="433" alt="image" src="https://user-images.githubusercontent.com/87634136/173609956-b5fc87b9-c7d3-4281-8e51-36cd535f4bb8.png">


( 16 비트 관련 레지스터 )

<img width="413" alt="image" src="https://user-images.githubusercontent.com/87634136/173610041-d3f47275-c3a5-4f9d-b8f6-1a38800cb31e.png">

<img width="420" alt="image" src="https://user-images.githubusercontent.com/87634136/173610089-82d83073-0e28-4387-8a7b-212e11b6b56c.png">


( 8비트 타이머 카운터 동작 모드 )

- 타이머 카운터 용어 

<img width="428" alt="image" src="https://user-images.githubusercontent.com/87634136/173610188-d26deb51-794f-41f0-bd7e-154dccc8c5ca.png">

- 표준 모드 ( Nomal Mode )

<img width="418" alt="image" src="https://user-images.githubusercontent.com/87634136/173610240-d438a3f7-fdbe-465d-9272-659e3237f44c.png">

- CTC 모드 ( Clear Timer on Compare Mode )

<img width="418" alt="image" src="https://user-images.githubusercontent.com/87634136/173610297-52235603-c9fd-4534-926f-0c0579e4d00f.png">

- Fast PWM 모드

<img width="421" alt="image" src="https://user-images.githubusercontent.com/87634136/173610349-10354bf4-59c9-470b-adc8-c1f4beba4632.png">

- Phase Correct PWM 모드

<img width="416" alt="image" src="https://user-images.githubusercontent.com/87634136/173610414-c7bc6b3e-cf1b-4615-baf7-c2befa285ebd.png">

