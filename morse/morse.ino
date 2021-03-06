/*
 * morse.ino
 * Телеграфная азбука
 * Современная телеграфная азбука (система кодировки символов короткими и
 * длинными посылками для передачи их по линиям связи, известная как
 * «код Морзе» или «морзянка»)
 *
 * В среднем 60 знаков в минуту
 * В среднем 3 символа в секунду (350ms на символ), 150 ms точка
 *
 * За единицу времени принимается длительность одной точки. Длительность
 * тире равна трём точкам. Пауза между элементами одного знака — одна точка,
 * между знаками в слове — 3 точки, между словами — 7 точек
 *
 * created 15.01.2015
 * modifid 02.02.2015
 * with Arduino 1.5.8 (tested on Arduino Uno)
 *
 * Copyright 2015 Vitaliy Fust <aslok.zp@gmail.com>
 *
 * This work is licensed under the MIT License (MIT). To view a copy of this
 * license, visit http://opensource.org/licenses/MIT or send a letter to:
 * Open Source Initiative
 * 855 El Camino Real
 * Ste 13A, #270
 * Palo Alto, CA 94301
 * United States.
 *
 *
 */

// Строка для ввода
const String str = "Jah Rastafari!";
// Обработка не происходит если строка ввода длиннее чем 53 символов
// Если строка ввода длиннее 24 символа то строка вывода укорачивается на символ строки ввода (переполнение строки ввода)
// Очевидно используется общая куча для строк String в которой просто заканчивается место
// Пример хорошей строки без переполнения
// qwertyuiopasdfghjklzxcv
// --.- .-- . .-. - -.-- ..- .. --- .--. .- ... -.. ..-. --. .... .--- -.- .-.. --.. -..- -.-. ...-
// Примеры плохих строк с переполнением
// qwertyuiopasdfghjklzxcvb
// --.- .-- . .-. - -.-- ..- .. --- .--. .- ... -.. ..-. --. .... .--- -.- .-.. --.. -..- -.-. ...-
// qwertyuiopasdfghjklzxcvbnm
// --.- .-- . .-. - -.-- ..- .. --- .--. .- ... -.. ..-. --. .... .--- -.- .-.. --.. -..- -.

// Флаг для отладки через порт
const boolean debug = true;

// Продолжительность "точки"
const int ms = 100;
// Служебный пин
const int pin = 13;

// Размер алфавита (Chars Lines)
const int CL = 26;
// Алфавитов (Chars Alphabets)
const int CA = 2;
// Максимальный размер символа (Chars count = X)
const int CX = 8;

// Ожидание после каждой итерации вспышек, ms
// Если -1 то только одна итерация без повторений
const int ew = 3000;

// Строка для вывода
String out;


// Алфавиты - массивы символов для замены (CHars)
char CH[CA][CL] = {
  {
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'z', 'x', 'c', 'v', 'b', 'n', 'm'
  }
  ,
  {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '.', ',', ':', ';', '(', ')', '\'', '`', '@',
    '"', '-', '—', '!', '?', '§', ' '
  }
};

// Алфавиты - массивы строк на которые будет замена (Morse cHars)
String MH[CA][CL] = {
  {
    "--.-", ".--", ".", ".-.", "-", "-.--", "..-", "..", "---", ".--.",
    ".-", "...", "-..", "..-.", "--.", "....", ".---", "-.-", ".-..",
    "--..", "-..-", "-.-.", "...-", "-...", "-.", "--"
  }
  ,
  {
    ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----",
    "......", ".-.-.-", "---...", "-.-.-.", "-.--.-", "-.--.-", ".----.", ".----.", ".--.-.",
    ".-..-.", "-....-", "-....-", "--..--", "..--..", "-...-", "|"
  }
};

// Вывод строки в порт
void dump(const String & msg) {
  if (debug) {
    Serial.println(msg.c_str());
  }
}

// Вывод символа в порт
void dump(char chr) {
  if (debug) {
    Serial.println(chr);
  }
}

// Вывод константы-указателя-на-символы в порт
void dump(const char * chr) {
  if (debug) {
    Serial.println(chr);
  }
}

// Короткая вспышка
void dot() {
  if (debug) {
    Serial.print('.');
  }
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
}

// Длиная (х3) вспышка
void dash() {
  if (debug) {
    Serial.print('-');
  }
  digitalWrite(pin, HIGH);
  delay(ms * 3);
  digitalWrite(pin, LOW);
}

// Отображения символа морзянки вспышками
// Задержки между вспышками - символами " " и "|"
void show_chr(char chr) {
  switch (chr) {
    // Выводим точку
    case '.':
      dot();
      break;
    // Выводим тире
    case '-':
      dash();
      break;
    // Ждем
    case ' ':
    case '|':
      delay(ms * 4);
      break;
    // Очевидно какая-то ошибка
    default:
      break;
  }
  // Ждем после вывода
  delay(ms * 2);
}

// Вывод строки морзянки посимвольно вспышками
void morse(String & morse_str) {
  // Текущий символ для вывода
  char chr;
  // Обходим символы строки
  for (int num = 0; num < morse_str.length(); num++) {
    chr = morse_str.charAt(num);
    // Выводим текущий символ морзянки в порт
    // dump(chr);
    // Выводим текущий символ морзянки вспышками
    show_chr(chr);
  }
}


void setup() {
  // Настраиваем диод для вспышек и порт для отладки
  pinMode(pin, OUTPUT);
  if (debug) {
    Serial.begin(57200);
  }

  // Строка для морзянки пока пустая
  out = "";
  // Делаем копию строки текта
  String str_lr = str;
  // Удаляем пробелы покраям
  str_lr.trim();
  // Переводим строку в нижний регистр
  str_lr.toLowerCase();
  // Текущая позиция конвертера
  int str_pos = 0;
  // Длинна символа для конвертации (очевидно будет = 1)
  int substr_len;
  // Флаг конвертера "символ найден"
  boolean br;
  // Начинается итерация цикла поиска
  do {
    // Символ не найден
    br = false;
    // Обходим словари символов (Chars Alphabets)
    for (int CA_num = 0; CA_num < CA; CA_num++) {
      // Если сивол найден - заканчиваем со словарями
      if (br) {
        break;
      }
      // Обходим символы-строки словаря (Chars Lines)
      for (int CL_num = 0; CL_num < CL; CL_num++) {
        if (str_pos != str_lr.indexOf(CH[CA_num][CL_num], str_pos)) {
          continue;
        }
        // Если длина символа-строки не нулевая и позиция вхождения этой подстроки
        // в строку текста равна текущей позиции конвертера
        // Добавляем соответствующий символ-строку в строку морзянки и ещё в конце пробел
        out += MH[CA_num][CL_num];
        out += " ";
        // Сдвигаем текущую позицию конвертера на длину найденного символа-строки
        str_pos++;
        // Символ найден
        br = true;
        // Заканчиваем с этим словарём
        break;
      }
    }
  }
  // Выполняем цикл до тех пор пока можем что-то найти
  while (br);
}

void loop() {
  // Выводим строку текста в порт
  dump(str);
  // Выводим морзянку в порт
  dump(out);
  // Выводим морзянку вспышками
  morse(out);
  // Если больше ничего не делаем
  if (ew == -1) {
    while(true);
  }
  // Ничего не делаем ew секунды
  delay(ew);
}
