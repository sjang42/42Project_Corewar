# Corewar - sjang@student.42.us.org

## 목차
* [개요](#개요)
* [개발 환경](#개발-환경)
* [사용 함수 제한](#사용-함수-제한)
* [챔피언](#챔피언)
* [빌드 방법](#빌드-방법)
* [사용 방법](#사용-방법)
* [참고](#참고)

## 개요

[42Project_Corewar][1] 는 고전 게임[Corewar][2]를 재구성하여 만드는 [42 Silicon Valley][3]의 팀 프로젝트입니다.
Corewar는 Redcode(어셈블리어)를 이용해 만들어진 프로그램(챔피언)들이 가상 머신에서 경쟁하여 한 챔피언이 살아남을 때까지 시뮬레이션으로 진행되는 게임입니다.
각각의 챔피언은 독립된 프로그램으로 registry와 processor(실행자)를 가지며 이를 이용해 실행자 복제, 가상 머신 내 코드 재생산, live외침 등의 명령을 사용할 수 있습니다.
가상머신은 각각의 챔피언(프로그램)을 동시에 실행하고 한 번의 실행은 한 번의 cycle을 의미합니다.
CYCLE_TO_DIE 의 실행 횟수 동안 코드 삭제, 실행자 부재 등으로 live 외침을 한 번 이상 실행하지 않은 프로그램은 죽게되어 가상머신에서 작동하지 않습니다.

해당 소스에서는 Redcode를 해석하여 가상머신에서 동작하는 바이너리파일(.cor)을 만드는 `asm` 실행파일과 복수의 챔피언파일(.cor)들이 게임하는 가상머신 `corewar`를 빌드합니다.

## 개발 환경
* OS
	* Ubuntu 16.04
* Language
	* C
* Compiler
	* gcc
* builder
	* MAKE
* 사용 라이브러리
	* [42Project_Libft][4]
	* [42Project_ftprintf][5]
	* ncurses

## 사용 함수 제한

* 입출력 관련 함수
	* open
	* close
	* read
	* lseek
	* write

* 메모리 관련 함수
	* malloc
	* realloc
	* free
* 가변인자 관련 함수
	* va_start
	* va_arg
	* va_end

* 에러 관련 함수
	* perror
	* strerror
	* exit

* CUI(Console User Interface)관련 라이브러리
	* ncurses

* 나머지 ft_printf, ft_memset 등의 함수는 위의 함수제한 내에서 직접 구현한 함수입니다.
	* [42Project_Libft][4], [42Project_ftprintf][4] 참고

## 챔피언

* 명령
	* **live** : 프로세서는 이 명령을 이용하여 살아있음을 가상머신에게 알릴 수 있습니다.
	* **fork** : 새로운 실행자를 생성합니다. (PC + (1st parameter % IDX_MOD))의 위치에 실행자를 복재합니다.
	* **lfork** : long-fork를 의미합니다. (PC + 1st parameter)의 위치에 실행자를 복재합니다.
	* **st** : 하나의 레지스터와 레지스터 또는 간접주소의 값을 입력받습니다. 처음 레지스터의 값을 (두번째 인자 % IDX_MOD)주소에 복사합니다.
	* **sti** : 하나의 레지스터와 두개의 인덱스를 입력받습니다. 두 인덱스를 합친 값을 주소로 하여 레지스터값을 복재합니다.
	* **ld** : 하나의 인자와 하나의 레지스터를 입력받습니다. 첫번째 인자를 IDX_MOD로 나눈 값을 레지스터에 등록합니다.
	* **lld** : long-ld를 의미합니다. 첫번째 인자를 레지스터에 등록합니다.
	* **ldi** : 두개의 인자와 하나의 레지스터를 입력받습니다. 두 개의 인자의 값의 합을 주소로 취하여 해당 주소값에 있는 값을 레지스터에 등록합니다.
	* **add** : 세 개의 레지스터를 입력받습니다. 처음 두 레지스터의 값을 합하여 세번째 레지스터에 등록합니다.
	* **sub** : 세 개의 레지스터를 입력받습니다. 첫 레지스터와 두번째 레지스터의 차를 세번째 레지스터에 등록합니다.
	* **or** : 세 개의 레지스터를 입력받습니다. 처 레지스터와 두번째 레지스터의 논리합의 값을 세번째 레지스터에 등록합니다.
	* **zjmp** : 하나의 인자를 입력받아 프로세서의 위치를 해당 인자의 주소로 이동시킵니다.
	* **aff** : 하나의 바이트를 입력받아 해당 값을 읽어 콘솔창으로 출력합니다. ASCII 코드를 이용합니다.

## 빌드 방법

우분투(16.04v) 터미널 환경을 사용한다고 가정하겠습니다.

### 사전 설치
make 프로그램이 설치되어있어야 합니다.

	sudo apt-get install make

ncurses 라이브러리가 설치되어있어야 합니다.

	sudo apt-get install ncurses-dev

터미널에서 라이브러리를 저장할 폴더로 이동합니다.

### 빌드

해당 깃을 클론한 뒤 서브 깃을 업데이트합니다.

	git clone https://github.com/sjang42/42Project_Corewar.git
	git submodule init
	git submodule update

루트 디렉터리에 `Makefile` 이 포함되어있으므로 이를 이용해 빌드할 수 있습니다.
해당 Makefile은 `ASM`, `VM`, `libft`, `ft_printf`폴더의 Makefile에 의존합니다.

	cd 42Project_Corewar
	make

루트 디렉터리에 챔피언 코드를 해석하는 `asm`파일과 가상머신 `corewar`가 생성되었습니다.

## 사용 방법

### asm

`asm` 파일은 Redcode로 작성된 챔피언 파일(.s)을 입력으로 받아 바이너리파일(.cor / .jex)을 만들어냅니다.
샘플로 주어지는 bee_gees.s 파일을 입력해 bee_gees.jex 파일을 생성합니다.

	./asm bee_gees.s

문법에 오류가 있으면 `ams` 프로그램이 오류에 대하여 피드백을 합니다.

### corewar

아래 명령을 이용하면 옵션에 대한 사용법이 출력됩니다.

	./corewar

`corewar`는 하나 이상의 챔피언을 입력으로 받습니다.
하나 이상의 챔피언이 입력되면 시뮬레이션 후 승자를 출력합니다.
시뮬레이션을 콘솔 그래픽으로 보기 위해 실행시 -v 옵션을 추가합니다.

	./corewar -v bee_gees.jex bee_gees.jex

## 참고

[1]: https://github.com/sjang42/42Project_Corewar/blob/master/corewar.en.pdf
[2]: https://en.wikipedia.org/wiki/Core_War
[3]: http://42.us.org "42 USA"
[4]: https://github.com/sjang42/42Project_Libft.git
[5]: https://github.com/sjang42/42Project_Printf.git
