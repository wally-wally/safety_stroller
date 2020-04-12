# :page_with_curl: README - 안전 유모차

---

:heavy_check_mark: <b>발표자료(keynote) 보러가기</b> : <a href="https://github.com/wally-wally/safety_carriage/tree/master/keynote.pdf" target="_blank">(바로 이동)</a>

:heavy_check_mark: <b>프로젝트 논문 보러가기</b> : <a href="https://github.com/wally-wally/safety_carriage/tree/master/IT융합프로젝트_논문.pdf" target="_blank">(바로 이동)</a>

---

<br>

## 1️⃣ Overview

- 전자공학과 IT융합프로젝트(졸업작품)
  - 2017.09 ~ 2018.02 : 아이디어 구상 및 설계
  - 2018.03 ~ 2018.12 : 작품 제작
- 주제 선정 이유 및 구현 목표
  - 한국소비자원에서 발표한 <소비자 유해 정보>에 따르면, 2017년까지 유아용 가구에서 가장 큰 사고를 차지하고 있는 것은 유모차이다.
  - 그 중에서 유모차 안전벨트 미착용에 의한 사고가 대부분을 차지한다. 이러한 안전사고를 예방하기 위해 움직이고 있는 유모차에 `잠금 설정 기능`, `브레이크 기능`, `분실 방지 기능`을 구현하여 `안전 유모차`를 만들었다.

<br>

## 2️⃣ Tech Stack

📍 **Hardware(Mr. Yeom)** : `ATmega328`, `Arduino`, `Servo Motor`, `GY-521`, `HC-SR04`, `HC-06` etc

📍 **Software(my part)** : `Arduino`, `Bluetooth`, `App Inventor`, `Proteus`, `PADS` etc

<br>

## 3️⃣ Function Diagram

![전체 기능 구성도](https://user-images.githubusercontent.com/52685250/79074912-2de06300-7d2a-11ea-8da1-9c56edd73a6b.png)

| 기능           | 설명                                                         |
| -------------- | ------------------------------------------------------------ |
| 잠금 설정 기능 | 유아가 유모차에 탑승 중일 때 안전벨트를 착용했을 경우에만 잠금 장치 해제 가능 |
| 브레이크 기능  | 탑승 후 이동 중일 때 스마트폰 어플에서 '운전 모드'를 선택한 경우 기울기 센서(GY-521)에 의해 일정 각도 이상 기울어지면 자동 브레이크 장치에 작동 |
| 분실 방지 기능 | 유모차와 보호자가 일정 거리 이상 멀어지면 부저를 울려 유모차 분실사고를 막을 수 있음 |

<br>

## :four: Hardware

- 안전 유모차의 외관 모습(좌: 전면, 우: 후면)

  ![그림1](https://user-images.githubusercontent.com/52685250/79074941-5f592e80-7d2a-11ea-8656-498da6fe3cea.png)

- 메인 박스(좌) & 각 기능별 하드웨어 설계(우)

  ![그림2](https://user-images.githubusercontent.com/52685250/79074942-6122f200-7d2a-11ea-8ec5-4d6e1a22dcfc.png)

- 기능 회로도(Proteus로 구성)

  ![그림3](https://user-images.githubusercontent.com/52685250/79074943-61bb8880-7d2a-11ea-96fd-d073cde4a9a8.jpg)

<br>

## :five: Software

- Arduino 코드 일부 (코드 전체를 보시려면 <a href="https://github.com/wally-wally/safety_carriage/tree/master/code.ino" target="_blank">(여기)</a>를 클릭하세요.)

  ![그림5](https://user-images.githubusercontent.com/52685250/79075118-b7446500-7d2b-11ea-9a58-deef78a4f42a.png)

- App Inventor로 제작한 스마트폰 어플리케이션 스크린샷 및 코드 블록

  ![그림41](https://user-images.githubusercontent.com/52685250/79074944-61bb8880-7d2a-11ea-969e-a778b7119224.png)

<br>

## :six: Copyright

All copyrights on the code of this project and the homepage are in [wally-wally](https://github.com/wally-wally) and my project partner(Mr. Yeom).

If you use the project contents without permission, authorization, you may be subject to legal punishment.