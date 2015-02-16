/*
created 10.02.2015
modified 16.02.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Nano)
*/

#include "Cyruit.h"

// Конструктор
Cyruit::Cyruit(
  void* ptr, display_type type, byte width, byte height, byte f_width, byte f_height
){
  lcd = ptr;
  lcd_type = type;
  font_width = f_width,
  font_height = f_height,
  scr_width = width / font_width,
  scr_height = height / font_height,
  scr_length = scr_width * scr_height;
  clear();
}

Cyruit::Cyruit(
  Cyruit_PCD8544* ptr,
  byte width, byte height, byte f_width, byte f_height
):Cyruit(ptr, Cyruit_PCD8544_lib, width, height, f_width, f_height){
}

// Ф-ия печати строк переданных с помощью F()
void Cyruit::print(const __FlashStringHelper* str, int8_t position, byte go_ln, byte space){
  word str_len = strlen_P((char*) str) + 1;
  char* tmp = new char[str_len];
  strcpy_P(tmp, (char*) str);
  print(tmp, position, go_ln, space);
  delete[] tmp;
}

// Ф-ия печати целых чисел
void Cyruit::print(int chr, int8_t position, byte go_ln, byte space){
  char str[max_num_length];
  sprintf(str, "%d", chr);
  print(str, position, go_ln, space);
}

// Печать чисел с плавающей точкой
void Cyruit::print(double chr, int8_t position, byte go_ln, byte width, byte prec){
  char str[max_num_length];
  dtostrf(chr, width, prec, str);
  print(str, position, go_ln);
}

// Печать отдельного символа
inline void Cyruit::print(char chr, int8_t position, byte go_ln, byte space){
  char str[2]{chr};
  print(str, position, go_ln, space);
}

// Печать отдельного utf символа по номеру
void Cyruit::print(word utf8_num, int8_t position, byte go_ln, byte space){
  word utf8_chr = (utf8_num & 0x07C0) << 2 | utf8_num & 0x003F | 0xC080;
  char utf8_str[3]{(utf8_chr & 0xff00) >> 8, utf8_chr & 0xff};
  print(utf8_str, position, go_ln, space);
}

// Печать отдельного символа несколько раз
void Cyruit::print(char chr, int count){
  while (count-- > 0){
    print(chr);
  }
}

inline void Cyruit::print(char chr, word count){
  print(chr, (int) count);
}

// Печать массива символов по указателю
void Cyruit::print(char* str, int8_t position, byte go_ln, byte space){
  if (go_ln != def_go_ln && go_ln < scr_height){
    go(0, go_ln);
  }
  word str_size = utf8_strlen(str);
  // Сдвиг относительно текущей позиции
  word free_size = ((space - str_size) / 2) % scr_length;
  word free_size_pp = free_size + (space - str_size) % 2;
  /*Serial.println(str);
  Serial.println(str_size);
  Serial.println(scr_pos);
  Serial.println(scr_pos / scr_width);*/
  byte scr_width_pp = scr_width + 1;
  // Если указана новая позиция
  if (position != def_position && position < scr_width && position > -1 * scr_width_pp){
    // Если позиция от правого края
    if (position < 0){
      // Если нужна центровка
      if (space != def_space){
        go(scr_width_pp - space + position, scr_pos / scr_width);
        // Сдвигаем курсор пробелами
        print(' ', free_size_pp);
        print_lcd(str);
        print(' ', free_size);
        return;
      // Если равнение на право
      }else{
        // Если край экрана - переносим курсор
        word new_pos = scr_width_pp - str_size + position + scr_pos;
        go(new_pos >= 0 ? new_pos : (new_pos % scr_length) + scr_length);
      }
    // Если позиция от левого края
    }else{
      go(position, scr_pos / scr_width);
      // Если нужна центровка
      if (space != def_space){
        // Если сдвиг влево
        if (free_size < 0) {
          // Если край экрана - переносим курсор
          word new_pos = free_size + scr_pos;
          go(new_pos >= 0 ? new_pos : (new_pos % scr_length) + scr_length);
        }else{
          // Сдвигаем курсор пробелами
          print(' ', free_size);
          print_lcd(str);
          print(' ', free_size_pp);
          return;
        }
      }
    }
  }
  // Печатаем строку во внутренней кодировке
  print_lcd(str);
  //Serial.println("--------------");
}

// Ф-ия печати строк без параметров
void Cyruit::print_lcd(char* str){
  switch (lcd_type){
    case Cyruit_PCD8544_lib:
      for (word i = 0; str[i] && i < 65535; i++){
        if ((~str[i]) & 0x80 || (byte) str[i] >> 5 == 6){
          ((Cyruit_PCD8544*) lcd)->fillRect(
            scr_pos % scr_width * font_width,
            scr_pos / scr_width * font_height,
            font_width, font_height,
            WHITE
          );
        }
        ((Cyruit_PCD8544*) lcd)->write(str[i]);
        if ((~str[i]) & 0x80 || (byte) str[i] >> 5 != 6){
          scr_pos++;
          if (scr_pos >= scr_length){
            go(0);
          }
        }
      }
      ((Cyruit_PCD8544*) lcd)->display();
      break;
  }
}

// Очистка экрана и установка курсора на ноль
void Cyruit::clear(){
  switch (lcd_type){
    case Cyruit_PCD8544_lib:
      ((Cyruit_PCD8544*) lcd)->clearDisplay();
      ((Cyruit_PCD8544*) lcd)->display();
      break;
  }
  go(0);
}

// Установка курсора в выбранные столбец-строка
void Cyruit::go(byte col, byte row){
  /*Serial.print(col);
  Serial.print(", ");
  Serial.print(row);
  Serial.print('\n');*/
  if (col < scr_width && row < scr_height){
    switch (lcd_type){
      case Cyruit_PCD8544_lib:
        ((Cyruit_PCD8544*) lcd)->setCursor(col * font_width, row * font_height);
        break;
    }
    scr_pos = row * scr_width + col;
  }
}

// Установка курсора в выбранную позицию справа-налево сверху-вниз
void Cyruit::go(byte col){
  if (col < scr_length){
    go(col % scr_width, col / scr_width);
  }else if (col == 255){
    go(scr_pos);
  }
}

// Возвращает длину строки закодированной в utf-8
word Cyruit::utf8_strlen(char* str){
  word str_len = 0;
  byte chr_len = 1;
  for (word i = 0; str[i] && i < 65535; i += chr_len){
    chr_len = 0;
    for(
      byte mask = 0x80;
      mask && mask & str[i];
      chr_len++, mask >>= 1
    );
    if (!chr_len || chr_len > 6){
      chr_len = 1;
    }
    str_len++;
  }
  return str_len;
}