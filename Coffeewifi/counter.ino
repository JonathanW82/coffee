

void count_down_timer(int min, int sec) {
  static unsigned long previous_time = 0;
  
    if (!initialized_count_down) {
        delta_min_cd = min;
        delta_sec_cd = sec;
        initialized_count_down = true;
    }

  if (millis() - previous_time < 1000) {
    return;
  }
    previous_time = millis();

    delta_sec_cd--;

    if (delta_sec_cd < 0) {
      if (delta_min_cd > 0) {
        delta_min_cd--;
        delta_sec_cd = 59;
      } else {
        delta_min_cd = 0;
        delta_sec_cd = 0;
      }
    }

    minutes = delta_min_cd;
    seconds = delta_sec_cd;
  
  if (delta_min_cd == 0 && delta_sec_cd == 0) {
    return;
  }
}

void reset_count_down(){
    minutes = 0;
    seconds = 0;
    delta_min_cd = 0;
    delta_sec_cd = 0;
    initialized_count_down = false;
}


void count_up_timer() {
  static unsigned long previous_time = 0;

  if (millis() - previous_time < 1000) {
    return;
  }
    previous_time = millis();

    current_sec_cu++;

    if (current_sec_cu >= 60) {
      current_min_cu++;
      current_sec_cu = 0;
    }

    minutes = current_min_cu;
    seconds = current_sec_cu;

}

void reset_count_up_timer(){
      current_min_cu = 0;
      current_sec_cu = 0;
      minutes = 0;
      seconds = 0;
}