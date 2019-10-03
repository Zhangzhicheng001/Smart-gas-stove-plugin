    /*
  unsigned long varW_Temperature = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_Temperature, varW_Temperature);
  unsigned long varW_humidity = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_humidity, varW_humidity);
  unsigned long varW_time_left = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_time_left, varW_time_left);
  unsigned long varW_yanwu = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_yanwu, varW_yanwu);
  unsigned long varW_huoyan = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_huoyan, varW_huoyan);


  bool varR_submit = 0;
  if(myGizwits.hasBeenSet(EVENT_submit))
  {
    myGizwits.read(EVENT_submit,&varR_submit);//Address for storing data
    mySerial.println(F("EVENT_submit"));
    mySerial.println(varR_submit,DEC);

  }
  bool varR_ignition = 0;
  if(myGizwits.hasBeenSet(EVENT_ignition))
  {
    myGizwits.read(EVENT_ignition,&varR_ignition);//Address for storing data
    mySerial.println(F("EVENT_ignition"));
    mySerial.println(varR_ignition,DEC);

  }
  bool varR_mode_Slow_fire_old_soup = 0;
  if(myGizwits.hasBeenSet(EVENT_mode_Slow_fire_old_soup))
  {
    myGizwits.read(EVENT_mode_Slow_fire_old_soup,&varR_mode_Slow_fire_old_soup);//Address for storing data
    mySerial.println(F("EVENT_mode_Slow_fire_old_soup"));
    mySerial.println(varR_mode_Slow_fire_old_soup,DEC);

  }
  bool varR_mode_Firewood = 0;
  if(myGizwits.hasBeenSet(EVENT_mode_Firewood))
  {
    myGizwits.read(EVENT_mode_Firewood,&varR_mode_Firewood);//Address for storing data
    mySerial.println(F("EVENT_mode_Firewood"));
    mySerial.println(varR_mode_Firewood,DEC);

  }
  bool varR_mode_Steamed_bag = 0;
  if(myGizwits.hasBeenSet(EVENT_mode_Steamed_bag))
  {
    myGizwits.read(EVENT_mode_Steamed_bag,&varR_mode_Steamed_bag);//Address for storing data
    mySerial.println(F("EVENT_mode_Steamed_bag"));
    mySerial.println(varR_mode_Steamed_bag,DEC);

  }
  unsigned long varR_dianji_one = 0;
  if(myGizwits.hasBeenSet(EVENT_dianji_one))
  {
    myGizwits.read(EVENT_dianji_one,&varR_dianji_one);//Address for storing data
    mySerial.println(F("EVENT_dianji_one"));
    mySerial.println(varR_dianji_one,DEC);

  }
  unsigned long varR_set_the_time = 0;
  if(myGizwits.hasBeenSet(EVENT_set_the_time))
  {
    myGizwits.read(EVENT_set_the_time,&varR_set_the_time);//Address for storing data
    mySerial.println(F("EVENT_set_the_time"));
    mySerial.println(varR_set_the_time,DEC);

  }
