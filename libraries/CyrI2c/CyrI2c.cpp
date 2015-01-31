/*
created 19.01.2015
modified 23.01.2015
by Fust Vitaliy
with Arduino 1.5.8 (tested on Arduino Uno)
*/

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "CyrI2c.h"

/*
Кодировка использует для хранения символа один беззнаковый байт
192	А
193	Б
194	В
195	Г
196	Д
197	Е
198	Ё
199	Ж
200	З
201	И
202	Й
203	К
204	Л
205	М
206	Н
207	О
208	П
209	Р
210	С
211	Т
212	У
213	Ф
214	Х
215	Ц
216	Ч
217	Ш
218	Щ
219	Ъ
220	Ы
221	Ь
222	Э
223	Ю
224	Я
225	Ґ
226	Є
227	І
228	Ї
*/

CyrI2c::CyrI2c(uint8_t address, uint8_t width, uint8_t height) {
  const uint8_t ru_chars_count = 25;
  const uint8_t en_chars_count = 28;

	abc    = (char*) F("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяҐЄІЇґєії");
  ru     = new uint8_t*[ru_chars_count];
  ru_num = new uint8_t[ru_chars_count];
  ru_cnt = ru_chars_count;
  en     = new uint8_t[en_chars_count];
  en_num = new uint8_t[en_chars_count];
  en_cnt = en_chars_count;

  ru_num[0]  = 193; // Б
  ru[0]  = new uint8_t[8]{ 0x1e,0x10,0x10,0x1e,0x11,0x11,0x1e,0x0 };
  ru_num[1]  = 195; // Г
  ru[1]  = new uint8_t[8]{ 0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru_num[2]  = 196; // Д
  ru[2]  = new uint8_t[8]{ 0xe, 0xa, 0xa, 0xa, 0xa, 0x1f,0x11,0x0 };
  ru_num[3]  = 220; // Ы
  ru[3]  = new uint8_t[8]{ 0x11,0x11,0x11,0x1d,0x13,0x13,0x1d,0x0 };
  ru_num[4]  = 223; // Ю
  ru[4]  = new uint8_t[8]{ 0x17,0x15,0x15,0x1d,0x15,0x15,0x17,0x0 };
  ru_num[5]  = 224; // Я
  ru[5]  = new uint8_t[8]{ 0xf, 0x11,0x11,0xf, 0x5, 0x9, 0x11,0x0 };
  ru_num[6]  = 199; // Ж
  ru[6]  = new uint8_t[8]{ 0x15,0x15,0xe, 0xe, 0xe, 0x15,0x15,0x0 };
  ru_num[7]  = 208; // П
  ru[7]  = new uint8_t[8]{ 0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x0 };
  ru_num[8]  = 225; // Ґ
  ru[8]  = new uint8_t[8]{ 0x1, 0x1f,0x10,0x10,0x10,0x10,0x10,0x0 };
  ru_num[9]  = 216; // Ч
  ru[9]  = new uint8_t[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0x1, 0x0 };
  ru_num[10] = 226; // Є
  ru[10] = new uint8_t[8]{ 0xf, 0x10,0x10,0x1e,0x10,0x10,0xf, 0x0 };
  ru_num[11] = 204; // Л
  ru[11] = new uint8_t[8]{ 0x3, 0x5, 0x9, 0x9, 0x9, 0x9, 0x19,0x0 };
  ru_num[12] = 212; // У
  ru[12] = new uint8_t[8]{ 0x11,0x11,0x11,0xf, 0x1, 0x1, 0xe, 0x0 };
  ru_num[13] = 213; // Ф
  ru[13] = new uint8_t[8]{ 0xe, 0x15,0x15,0x15,0xe, 0x4, 0x4, 0x0 };
  ru_num[14] = 215; // Ц
  ru[14] = new uint8_t[8]{ 0x12,0x12,0x12,0x12,0x12,0x12,0x1f,0x1 };
  ru_num[15] = 222; // Э
  ru[15] = new uint8_t[8]{ 0x1e,0x1, 0x1, 0xf, 0x1, 0x1, 0x1e,0x0 };
  ru_num[16] = 219; // Ъ
  ru[16] = new uint8_t[8]{ 0x18,0x8, 0x8, 0xe, 0x9, 0x9, 0xe, 0x0 };
  ru_num[17] = 218; // Щ
  ru[17] = new uint8_t[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1e,0x1 };
  ru_num[18] = 228; // Ї
  ru[18] = new uint8_t[8]{ 0xa, 0x4, 0x4, 0x4, 0x4, 0x4, 0xe, 0x0 };
  ru_num[19] = 217; // Ш
  ru[19] = new uint8_t[8]{ 0x15,0x15,0x15,0x15,0x15,0x15,0x1f,0x0 };
  ru_num[20] = 202; // Й
  ru[20] = new uint8_t[8]{ 0x15,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru_num[21] = 201; // И
  ru[21] = new uint8_t[8]{ 0x11,0x11,0x11,0x13,0x15,0x19,0x11,0x0 };
  ru_num[22] = 198; // Ё
  ru[22] = new uint8_t[8]{ 0xa, 0x1f,0x10,0x1e,0x10,0x10,0x1f,0x0 };
  ru_num[23] = 200; // З
  ru[23] = new uint8_t[8]{ 0xe, 0x11,0x1, 0xe, 0x1, 0x11,0xe, 0x0 };
  ru_num[24] = 221; // Ь
  ru[24] = new uint8_t[8]{ 0x10,0x10,0x10,0x1c,0x12,0x12,0x1c,0x0 };

  en_num[0]  = 192; // А
  en[0]  = 'A';
  en_num[1]  = 194; // В
  en[1]  = 'B';
  en_num[2]  = 197; // Е
  en[2]  = 'E';
  en_num[3]  = 198; // Ё
  en[3]  = 'E';
  en_num[4]  = 200; // З
  en[4]  = '3';
  en_num[5]  = 201; // И
  en[5]  = 'U';
  en_num[6]  = 202; // Й
  en[6]  = 'U';
  en_num[7]  = 203; // К
  en[7]  = 'K';
  en_num[8]  = 205; // М
  en[8]  = 'M';
  en_num[9]  = 206; // Н
  en[9]  = 'H';
  en_num[10] = 207; // О
  en[10] = 'O';
  en_num[11] = 209; // Р
  en[11] = 'P';
  en_num[12] = 210; // С
  en[12] = 'C';
  en_num[13] = 211; // Т
  en[13] = 'T';
  en_num[14] = 214; // Х
  en[14] = 'X';
  en_num[15] = 217; // Ш
  en[15] = 'W';
  en_num[16] = 218; // Щ
  en[16] = 'W';
  en_num[17] = 221; // Ь
  en[17] = 'b';
  en_num[18] = 219; // Ъ
  en[18] = 'b';
  en_num[19] = 204; // Л
  en[19] = 202;
  en_num[20] = 212; // У
  en[20] = 191;
  en_num[21] = 213; // Ф
  en[21] = 236;
  en_num[22] = 216; // Ч
  en[22] = 209;
  en_num[23] = 215; // Ц
  en[23] = 249;
  en_num[24] = 222; // Э
  en[24] = 214;
  en_num[25] = 226; // Є
  en[25] = 211;
  en_num[26] = 227; // І
  en[26] = 'I';
  en_num[27] = 228; // Ї
  en[27] = 'I';

  s      = NULL;
	p_s    = NULL;
	f      = 0;
  bl     = false;
  for (uint8_t i = 0; i < 8; i++){
    char_map[i] = 0;
  }

  lcd = new LiquidCrystal_I2C(address, width, height);
  lcd->init();
  clear();
}

void CyrI2c::print(const __FlashStringHelper* str, int8_t position, uint8_t go_ln){
  char* ptr = (char*) str;
  char* tmp = new char[256];
	char chr;
	uint8_t cur_chr;
  for (cur_chr = 0; cur_chr < 255 && (chr = (char) pgm_read_byte_near(ptr + cur_chr)); cur_chr++){
		tmp[cur_chr] = chr;
	}
	tmp[cur_chr] = 0;
	print(tmp, position, go_ln);
	delete[] tmp;
}

void CyrI2c::print(char chr, int8_t position, uint8_t go_ln){
	char* str = new char[2]{chr, 0};
  print(str, position, go_ln);
	delete[] str;
}

void CyrI2c::print(char* str, int8_t position, uint8_t go_ln){
	uint8_t cur_chr;
  for (cur_chr = 0; cur_chr < 255 && str[cur_chr]; cur_chr++);
	char* tmp = new char[cur_chr + 1];
	get_str_enc(str, tmp);
  print_enc(tmp, position, go_ln);
	delete[] tmp;
}

void CyrI2c::print_enc(char* str, int8_t position, uint8_t go_ln){
  uint8_t cur, old_cur, cur_chr, i, cur_pos, pos;
	if (go_ln != 255 && go_ln < 2){
    setCursor(0, go_ln);
  }
  if (position != 127 && position < 16 && position > -17){
    if (position < 0){
      // Выясняем длину строки
      for (cur_chr = 0; str[cur_chr] && str[cur_chr] != '\n'; cur_chr++);
      setCursor(17 - cur_chr + position, scr_pos / 16);
    }else{
      setCursor(position, scr_pos / 16);
    }
  }
  // Массив символов которые будут отображаться после вывода
  // Порядок соответствует порядку отображения
  char* next_scr = new char[33];
	//Serial.println(str);
  get_next_scr(str, next_scr);
	//Serial.println(next_scr);
  // Массив символов, на которые нужно будет заменить соответствующие
  // символы кирилицы при выводе
  char lcd_replace[32];
  // Обходим next_scr
  boolean found;
  for (cur_chr = 0; cur_chr < 32; cur_chr++){
    found = false;
    // Обходим основной набор символов для замены
    for (cur = 0; cur < en_cnt; cur++){
      if (en_num[cur] == (unsigned char) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = en[cur];
        found = true;
        break;
      }
    }
    if (found){
      continue;
    }
    // Обходим набор использованных самодельных символов для замены
    for (i = 0; i < 8; i++){
      if (char_map[i] && char_map[i] == (unsigned char) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = i;
        found = true;
        break;
      }
    }
    // Ничего не нашли, не заменяем символ - будет тот же
    lcd_replace[cur_chr] = next_scr[cur_chr];
  }

  // Выполнена предварительная замена, lcd_replace почти во внутренней кодировке
  // Ищем символы которые нужно и можно заменить, их коды в области 192-255
  for (cur_chr = 0; cur_chr < 32; cur_chr++){
    if ((unsigned char) lcd_replace[cur_chr] < 192 || (unsigned char) lcd_replace[cur_chr] > 255){
      continue;
    }
    /*Serial.println("(unsigned char) lcd_replace[cur_chr]");
    Serial.println(cur_chr);
    Serial.println((unsigned char) lcd_replace[cur_chr]);
    Serial.println("----------------------------");*/
    found = false;
    // Обходим набор использованных самодельных символов для замены
    for (i = 0; i < 8; i++){
      if (char_map[i] && char_map[i] == (unsigned char) next_scr[cur_chr]){
        // Символ для замены найден, запоминаем по позиции в next_scr
        lcd_replace[cur_chr] = i;
        found = true;
        break;
      }
    }
    if (found){
	    //Serial.println("Replaced");
      continue;
    }
    found = false;
    // Обходим набор самодельных символов для замены
    for (cur = 0; cur < 9; cur++){
      // Если мы можем заменить его одним из восьми первых
      if (ru_num[cur] == (unsigned char) lcd_replace[cur_chr]){
        found = true;
        // Переменная cur хранит номер самодельного символа
        break;
      }
    }

    // Нечем заменить, наверно не нужно
    if (!found){
      continue;
    }

    // Символ найден, ищем свободную ячейку
    found = false;
    for (i = 0; i < 8; i++){
			// Ячейка занята
      if (char_map[i]){
        continue;
      }
      found = true;
      // Сохраняем в ячейку номер символа который заменяем
      char_map[i] = ru_num[cur];
      /*Serial.println("lcd->createChar(i, ru[cur]);");
      Serial.println(i);
      Serial.println(cur);
      Serial.println("----------------------------");*/
      lcd->createChar(i, ru[cur]);
      // Бага lcd->createChar - приходится обновлять курсор
      setCursor();
      // Будем заменять его при выводе на номер ячейки
      for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
        if ((unsigned char) lcd_replace[cur_pos] == ru_num[cur]){
          /*Serial.println("lcd_replace[cur_chr] = i");
          Serial.println(cur_chr);
          Serial.println(i);
          Serial.println("----------------------------");*/
          lcd_replace[cur_chr] = i;
        }
      }
			// Прекращаем поиск свободных ячеек
      break;
    }

		// Переходим к следующему символу
    if (found){
      continue;
    }

    // Закончились ячейки для хранения символов :(
    // Ищем что заменить
    // Обходим набор самодельных символов для замены с конца
    // Никогда не выселяем символы 0-8 потому что заменить нечем :(
    for (cur_pos = ru_cnt; cur_pos-- > 8; ){
      // Ищем ячейку занятую этим символом
      for (i = 0; i < 8; i++){
        // Если есть кандидат на выселение
        if (ru_num[cur_pos] == char_map[i]){
          found = false;
          // Обходим основной набор символов для замены
          // После выселения будет отображаться оттуда
          for (pos = 0; pos < en_cnt; pos++){
            if (en_num[pos] == char_map[i]){
              found = true;
              old_cur = pos;
              break;
            }
          }
          if (!found){
            // Если так случится - будет глюк
            // Выход один - добавить этот символ в en
            // Второй выход - переместить в начало ru
            // Этот выход невозможен:
            // 1. Количество невыселяемых символов ограничено драйвером 8 штук
            // 2. Набор одновременно отображаемых символов ограничен алфавитом
            // Одновременный вывод частей украинского и русского алфавитов
            // может привести к глюкам
            continue;
          }
          // Сохраняем в ячейку номер символа который заменяем
          char_map[i] = ru_num[cur];
          // Будем заменять его при выводе на номер ячейки
          for (pos = 0; pos < 32; pos++){
            if ((unsigned char) lcd_replace[pos] == ru_num[cur]){
              /*Serial.println("lcd_replace[pos] = i");
              Serial.println(pos);
              Serial.println(i);
              Serial.println("----------------------------");*/
              lcd_replace[pos] = i;
            }
            // Динамическое обновление символов
            // Перетираем отображающееся предыдущее содержимое ячейки
            if ((unsigned char) next_scr[pos] == ru_num[cur_pos]){
              lcd->setCursor(pos - pos / 16 * 16, pos / 16);
              lcd_replace[pos] = en[old_cur];
              lcd->write(en[old_cur]);
            }
          }
          // Отображающееся предыдущее содержимое перетерто, можем подменять
          lcd->createChar(i, ru[cur]);
          // Бага lcd->createChar - приходится обновлять курсор
          setCursor();
          break;
        }
      }
      if (found){
        break;
      }
    }
  }

  // Обходим набор использованных самодельных символов char_map
  for (cur = 0; cur < 8; cur++){
    // Если ячейка используется
    // Проверяем, если уже не нужна - освобобождаем
    if (char_map[cur]) {
      found = false;
      // Обходим массив который получился для замены
      for (cur_chr = 0; cur_chr < 32; cur_chr++){
        // Если был использован один из самодельных символов
        if ((unsigned char) lcd_replace[cur_chr] == cur){
          found = true;
          break;
        }
      }
      // Мы используем этот символ
      if (found){
        continue;
      }

      // Символ не используется - очищаем
      /*Serial.println("char_map[cur]");
      Serial.println(cur);
      Serial.println(char_map[cur]);
      Serial.println("char_map[cur] = 0");
      Serial.println("----------------------------");*/
      char_map[cur] = 0;
    }

    // Обходим дополнительные символы самодельного набора, ищем что бы ещё заменить
    for (uint8_t ru_cur = 9; ru_cur < ru_cnt; ru_cur++){
      found = false;
      // Обходим уже использованные дополнительные символы
      for (i = 0; i < 8; i++){
        if (char_map[i] && char_map[i] == ru_num[ru_cur]){
          // Уже заменили раньше
          found = true;
          break;
        }
      }
      if (found){
				// Переходим к следующему самодельному символу
        continue;
      }
      // Обходим массив символов, которые будут отображаться после вывода
      for (cur_chr = 0; cur_chr < 32; cur_chr++){
				// Ищем текущий дополнительный самодельный символ
        if ((unsigned char) next_scr[cur_chr] != ru_num[ru_cur]){
          continue;
        }
        // Найден текущий дополнительный самодельный символ
        // Сохраняем в ячейку номер символа
        char_map[cur] = ru_num[ru_cur];
        /*Serial.println("lcd->createChar(cur, ru[ru_cur]);");
        Serial.println(cur);
        Serial.println(ru_cur);
        Serial.println("----------------------------");*/
        lcd->createChar(cur, ru[ru_cur]);
        // Будем заменять его при выводе на номер ячейки
				// Обходим начиная с текущего, предыдущие заменили бы раньше
        for (cur_pos = cur_chr; cur_pos < 32; cur_pos++){
          if ((unsigned char) next_scr[cur_pos] == ru_num[ru_cur]){
            /*Serial.println("lcd_replace[cur_chr] = cur");
            Serial.println(cur_chr);
            Serial.println(cur);
            Serial.println("----------------------------");*/
            lcd_replace[cur_chr] = cur;
            // Динамическое обновление символов
            lcd->setCursor(cur_chr - cur_chr / 16 * 16, cur_chr / 16);
            lcd->write(cur);
          }
        }
        // Бага lcd->createChar - приходится обновлять курсор
        setCursor();
      }
      if (found){
        // Переходим к следующей ячейке
        break;
      }
    }
  }

  write_str_enc(str, lcd_replace);
	delete[] next_scr;
}

void CyrI2c::get_next_scr(char* str, char* next_scr){
  uint8_t next_scr_pos = scr_pos;
	// Копируем текущий экран
  for (uint8_t i = 0; i < 33; i++){
    next_scr[i] = scr[i];
  }
	// Обходим строку и эмулируем вывод
  for (uint8_t cur_chr = 0; str[cur_chr] && cur_chr < 255; cur_chr++){
    if (str[cur_chr] == '\n'){
      if (next_scr_pos < 16){
        next_scr_pos = 16;
      }else{
        next_scr_pos = 0;
      }
    }
    if (next_scr_pos > 31){
      next_scr_pos = 0;
    }
    if (str[cur_chr] != '\n'){
      next_scr[next_scr_pos++] = str[cur_chr];
    }
    if (next_scr_pos > 31){
      next_scr_pos = 0;
    }
  }
}

void CyrI2c::write_str_enc(char* str, char* lcd_chars){
  char out;
  for (uint8_t cur_chr = 0; str[cur_chr] && cur_chr < 255; cur_chr++){
    out = str[cur_chr];
    if (out == '\n'){
      if (scr_pos < 16){
        scr_pos = 16;
      }else{
        scr_pos = 0;
      }
      setCursor();
      continue;
    }
    if (scr_pos > 31){
      scr_pos = 0;
    }
    if (scr_pos == 0 || scr_pos == 16){
      setCursor();
    }
    if ((unsigned char) out >= 192 && (unsigned char) out <= 255){
      out = lcd_chars[scr_pos];
    }
    scr[scr_pos++] = str[cur_chr];

    //Serial.println((unsigned char) out);
    lcd->write(out);
    if (scr_pos > 31){
      scr_pos = 0;
    }
  }
  //Serial.println("--------------------------------------------------------");
}

void CyrI2c::get_str_enc(char* str, char* result){
  boolean found = false;
  uint8_t res_pos = 0;
  // Обходим символы строки
  for (uint8_t str_pos = 0; str[str_pos]; str_pos++){
    // Совпадений ещё небыло
    found = false;
    // Обходим подстроки для поиска (74 символа, 33+33 русских и 4+4 украинских)
    for (uint8_t abc_num = 0; abc_num < 148; abc_num += 2){
      // Обходим символы подстрок для поиска
      for (uint8_t abc_chr_pos = 0, cur_pos = str_pos; abc_chr_pos < 2; abc_chr_pos++, cur_pos++){
        // Если текущий символ подстроки не равен текущему символу строки
        if (str[cur_pos] != (char) pgm_read_byte_near(abc + abc_num + abc_chr_pos)){
          // Прерываем обход символов подстроки
          found = false;
          // Переходим к следующей подстроке
          break;
        }
        // Эти символы строк совпадают
        found = true;
      }
      // Проверяем результаты сравнения строк
      if (found){
        // Русский алфавит верхний регистр
        if (abc_num < 66){
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 192;
        // Русский алфавит нижний регистр
        // И символы из украинского алфавита верхний регистр
        }else if (abc_num < 140){
          // Пишем в результат символ для замены найденной строки
          result[res_pos++] = (abc_num / 2) + 159;
        // Символы из украинского алфавита нижний регистр
        }else{
          result[res_pos++] = (abc_num / 2) + 155;
        }
        // Сдвигаем текущую позицию строки на один символ (потому что всего надо на два)
        str_pos++;
        // Заканчиваем цикл обхода подстрок - подстрока найдена
        break;
      }
    }
    if (!found){
      // Подстрока не была найдена - копируем текущий символ как он есть
      result[res_pos++] = str[str_pos];
    }
  }
  result[res_pos] = 0;
}

void CyrI2c::clear_screen(){
  uint8_t i;
  for (i = 0; i < 32; i++){
    scr[i] = ' ';
  }
  scr[32] = 0;
  scr_pos = 0;
}

void CyrI2c::backlight(boolean state){
  if (bl = state){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

void CyrI2c::backlight(){
  if (bl = !bl){
    lcd->backlight();
  }else{
    lcd->noBacklight();
  }
}

void CyrI2c::power(boolean state){
  if (pwr = state){
    lcd->display();
  }else{
    lcd->noDisplay();
  }
}

void CyrI2c::power(){
  if (pwr = !pwr){
    lcd->display();
  }else{
    lcd->noDisplay();
  }
}

void CyrI2c::cursor(boolean state){
  if (crsr = state){
    lcd->cursor();
  }else{
    lcd->noCursor();
  }
}

void CyrI2c::cursor(){
  if (crsr = !crsr){
    lcd->cursor();
  }else{
    lcd->noCursor();
  }
}

void CyrI2c::blink(boolean state){
  if (blnk = state){
    lcd->blink();
  }else{
    lcd->noBlink();
  }
}

void CyrI2c::blink(){
  if (blnk = !blnk){
    lcd->blink();
  }else{
    lcd->noBlink();
  }
}

void CyrI2c::clear(){
  lcd->clear();
  clear_screen();
}

void CyrI2c::home(){
  lcd->home();
  scr_pos = 0;
}

void CyrI2c::setCursor(uint8_t col, uint8_t row){
  //Serial.println("setCursor");
  //Serial.println(col);
  //Serial.println(row);
  if (col < 16 && row < 2){
    lcd->setCursor(col, row);
    scr_pos = row * 16 + col;
  }
}

void CyrI2c::setCursor(uint8_t col){
  if (col < 32){
    setCursor(col - col / 16 * 16, col / 16);
  }
  if (col == 32){
    setCursor(scr_pos);
  }
}

void CyrI2c::init(const __FlashStringHelper* str){
	delete p_s;
  p_s = (char*) str;
	f = 1;
}

void CyrI2c::init(const char* str){
	delete s;
  s = str;
	f = 2;
}

void CyrI2c::printn(uint8_t num, int8_t position, uint8_t go_ln){
  if (f == 1){
    printn_flash(num, position, go_ln);
		return;
  }
  if (f == 2){
    printn_str(num, position, go_ln);
		return;
  }
}

void CyrI2c::printn_str(uint8_t num, int8_t position, uint8_t go_ln){
  char str[255];
	uint8_t count = 0, str_pos;
	unsigned int pos = 0;
  while (count < num && pos < 65000 && s[pos]){
		if (s[pos++] == '\r'){
      count++;
      continue;
		}
  }
	if (count != num){
		return;
	}
	for (str_pos = 0; pos < 255 && str_pos < 255 && pos < 65000 && s[pos]; pos++){
		if (s[pos] == '\r'){
			break;
	  }
    str[str_pos++] = s[pos];
	}
	str[str_pos] = 0;
	print(str, position, go_ln);
}

void CyrI2c::printn_flash(uint8_t num, int8_t position, uint8_t go_ln){
  char str[255];
	uint8_t count = 0, str_pos;
	unsigned int pos = 0;
	char chr;
  while (count < num && pos < 65000 && (chr = (char) pgm_read_byte_near(p_s + pos++))){
		if (chr == '\r'){
      count++;
      continue;
		}
  }
	if (count != num){
		return;
	}
	for (str_pos = 0; (chr = (char) pgm_read_byte_near(p_s + pos)) && pos < 65000; pos++){
		if (chr == '\r'){
			break;
	  }
    str[str_pos++] = chr;
	}
	str[str_pos] = 0;
	print(str, position, go_ln);
}
