/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Data-Access.h"

AFEDataAccess::AFEDataAccess() {}

DEVICE AFEDataAccess::getDeviceConfiguration() {
  DEVICE configuration;

  Eeprom.read(9, 16).toCharArray(configuration.name,
                                 sizeof(configuration.name));
  configuration.isLED[0] = Eeprom.read(366);
  configuration.isRelay[0] = Eeprom.read(369);
  configuration.isSwitch[0] = Eeprom.read(395);
  configuration.isSwitch[1] = Eeprom.read(402);
  configuration.httpAPI = Eeprom.read(25);
  configuration.mqttAPI = Eeprom.read(228);

  return configuration;
}

FIRMWARE AFEDataAccess::getFirmwareConfiguration() {
  FIRMWARE configuration;

  Eeprom.read(0, 7).toCharArray(configuration.version,
                                sizeof(configuration.version));
  Eeprom.read(28, 120).toCharArray(configuration.upgradeURL,
                                   sizeof(configuration.upgradeURL));
  configuration.type = Eeprom.readUInt8(7);
  configuration.autoUpgrade = Eeprom.readUInt8(27);
  return configuration;
}

NETWORK AFEDataAccess::getNetworkConfiguration() {
  NETWORK configuration;

  Eeprom.read(148, 32).toCharArray(configuration.ssid,
                                   sizeof(configuration.ssid));
  Eeprom.read(180, 32).toCharArray(configuration.password,
                                   sizeof(configuration.password));

  configuration.isDHCP = Eeprom.read(212);
  configuration.ip = Eeprom.readIP(213);
  configuration.gateway = Eeprom.readIP(217);
  configuration.subnet = Eeprom.readIP(221);
  configuration.noConnectionAttempts = Eeprom.readUInt8(225);
  configuration.waitTimeConnections = Eeprom.readUInt8(226);
  configuration.waitTimeSeries = Eeprom.readUInt8(227);
  return configuration;
}

MQTT AFEDataAccess::getMQTTConfiguration() {
  MQTT configuration;

  Eeprom.read(229, 32).toCharArray(configuration.host,
                                   sizeof(configuration.host));
  configuration.ip = Eeprom.readIP(261);
  configuration.port = Eeprom.read(265, 5).toInt();
  Eeprom.read(270, 32).toCharArray(configuration.user,
                                   sizeof(configuration.user));
  Eeprom.read(302, 32).toCharArray(configuration.password,
                                   sizeof(configuration.password));
  Eeprom.read(334, 32).toCharArray(configuration.topic,
                                   sizeof(configuration.topic));

  return configuration;
}

LED AFEDataAccess::getLEDConfiguration(uint8_t id) {
  LED configuration;
  uint8_t nextLED = 0;
  configuration.gpio = Eeprom.readUInt8(367 + id * nextLED);
  configuration.changeToOppositeValue = Eeprom.read(368 + id * nextLED);

  return configuration;
}

RELAY AFEDataAccess::getRelayConfiguration(uint8_t id) {
  RELAY configuration;
  MQTT configurationMQTT;
  uint8_t nextRelay = 26;
  char mqttTopic[49];
  configuration.gpio = Eeprom.readUInt8(370 + id * nextRelay);
  configuration.timeToOff = Eeprom.read(372 + id * nextRelay, 5).toFloat();
  configuration.statePowerOn = Eeprom.readUInt8(377 + id * nextRelay);

  Eeprom.read(378 + id * nextRelay, 16)
      .toCharArray(configuration.name, sizeof(configuration.name));

  configuration.stateMQTTConnected = Eeprom.readUInt8(394 + id * nextRelay);

  Eeprom.read(334, 32).toCharArray(configurationMQTT.topic,
                                   sizeof(configurationMQTT.topic));

  sprintf(configuration.mqttTopic, "%s%s/", configurationMQTT.topic,
          configuration.name);

  /* @TODO DOMOTICZ
    configuration.idx = Eeprom.read(376 + id * next, 5).toInt();
    configuration.publishToDomoticz = Eeprom.readUInt8(382 + id * next); */

  return configuration;
}

SWITCH AFEDataAccess::getSwitchConfiguration(uint8_t id) {
  SWITCH configuration;
  uint8_t nextSwitch = 7;
  configuration.gpio = Eeprom.readUInt8(396 + id * nextSwitch);
  configuration.type = Eeprom.readUInt8(397 + id * nextSwitch);
  configuration.sensitiveness = Eeprom.read(398 + id * nextSwitch, 3).toInt();
  configuration.functionality = Eeprom.readUInt8(401 + id * nextSwitch);

  return configuration;
}

void AFEDataAccess::saveConfiguration(DEVICE configuration) {
  Eeprom.write(9, 16, configuration.name);
  Eeprom.write(369, configuration.isRelay[0]);
  Eeprom.write(395, configuration.isSwitch[0]);
  Eeprom.write(402, configuration.isSwitch[1]);
  Eeprom.write(366, configuration.isLED[0]);
  Eeprom.write(25, configuration.httpAPI);
  Eeprom.write(228, configuration.mqttAPI);
  // Eeprom.write(413, configuration.isDS18B20);
}

void AFEDataAccess::saveConfiguration(FIRMWARE configuration) {
  Eeprom.write(0, 7, configuration.version);
  Eeprom.writeUInt8(7, configuration.type);
  Eeprom.writeUInt8(27, configuration.autoUpgrade);
  Eeprom.write(28, 120, configuration.upgradeURL);
}

void AFEDataAccess::saveConfiguration(NETWORK configuration) {
  Eeprom.write(148, 32, configuration.ssid);
  Eeprom.write(180, 32, configuration.password);
  Eeprom.write(212, configuration.isDHCP);
  Eeprom.writeIP(213, configuration.ip);
  Eeprom.writeIP(217, configuration.gateway);
  Eeprom.writeIP(221, configuration.subnet);
  Eeprom.writeUInt8(225, configuration.noConnectionAttempts);
  Eeprom.writeUInt8(226, configuration.waitTimeConnections);
  Eeprom.writeUInt8(227, configuration.waitTimeSeries);
}

void AFEDataAccess::saveConfiguration(MQTT configuration) {
  Eeprom.write(229, 32, configuration.host);
  Eeprom.writeIP(261, configuration.ip);
  Eeprom.write(265, 5, (long)configuration.port);
  Eeprom.write(270, 32, configuration.user);
  Eeprom.write(302, 32, configuration.password);
  Eeprom.write(334, 32, configuration.topic);
}

void AFEDataAccess::saveConfiguration(uint8_t id, RELAY configuration) {
  uint8_t nextRelay = 26;

  Eeprom.writeUInt8(370 + id * nextRelay, configuration.gpio);
  Eeprom.write(372 + id * nextRelay, 5, configuration.timeToOff);
  Eeprom.writeUInt8(377 + id * nextRelay, configuration.statePowerOn);
  /* @TODO For MQTT only */
  Eeprom.write(378 + id * nextRelay, 16, configuration.name);
  Eeprom.writeUInt8(394 + id * nextRelay, configuration.stateMQTTConnected);
  /* @TODO DOMOTICZ
    Eeprom.write(376 + id * nextRelay, 5, (long)configuration.idx);
    Eeprom.writeUInt8(382 + id * nextRelay, configuration.publishToDomoticz);
    */
}

void AFEDataAccess::saveConfiguration(uint8_t id, LED configuration) {
  uint8_t nextLED = 2;
  Eeprom.writeUInt8(367 + id * nextLED, configuration.gpio);
  Eeprom.write(368 + id * nextLED, configuration.changeToOppositeValue);
}

void AFEDataAccess::saveConfiguration(uint8_t id, SWITCH configuration) {
  uint8_t nextSwitch = 7;
  Eeprom.writeUInt8(396 + id * nextSwitch, configuration.gpio);
  Eeprom.writeUInt8(397 + id * nextSwitch, configuration.type);
  Eeprom.write(398 + id * nextSwitch, 3, (long)configuration.sensitiveness);
  Eeprom.writeUInt8(401 + id * nextSwitch, configuration.functionality);
}

const char AFEDataAccess::getVersion() {
  char version[7];
  Eeprom.read(0, 7).toCharArray(version, sizeof(version));
  return *version;
}

void AFEDataAccess::saveVersion(String version) { Eeprom.write(0, 7, version); }

boolean AFEDataAccess::getRelayState(uint8_t id) {
  uint8_t nextRelay = 26;
  return Eeprom.read(371 + id * nextRelay);
}

void AFEDataAccess::saveRelayState(uint8_t id, boolean state) {
  uint8_t nextRelay = 26;
  Eeprom.write(371 + id * nextRelay, state);
}

uint8_t AFEDataAccess::getDeviceMode() { return Eeprom.readUInt8(26); }

void AFEDataAccess::saveDeviceMode(uint8_t mode) {
  Eeprom.writeUInt8(26, mode);
}

uint8_t AFEDataAccess::getLanguage() { return Eeprom.readUInt8(8); }

void AFEDataAccess::saveLanguage(uint8_t language) {
  Eeprom.writeUInt8(8, language);
}

/* @TODO DOMOTICZ
DOMOTICZ AFEDataAccess::getDomoticzConfiguration() {
  DOMOTICZ configuration;

  Eeprom.read(228, 32).toCharArray(configuration.host,
                                   sizeof(configuration.host));
  configuration.ip = Eeprom.readIP(260);
  configuration.port = Eeprom.read(264, 5).toInt();
  Eeprom.read(269, 32).toCharArray(configuration.user,
                                   sizeof(configuration.user));
  Eeprom.read(301, 32).toCharArray(configuration.password,
                                   sizeof(configuration.password));

  Serial << endl << "INFO: Requested : Domoticz";
  Serial << endl << "    - Host : " << configuration.host;
  Serial << endl << "    - IP : " << configuration.ip;
  Serial << endl << "    - Port : " << configuration.port;
  Serial << endl << "    - User : " << configuration.user;
  Serial << endl << "    - Password : " << configuration.password;

  return configuration;
}
*/
/* @TODO DS18B20
DS18B20 AFEDataAccess::getDS18B20Configuration() {
  DS18B20 configuration;

  configuration.present = Eeprom.read(400);
  configuration.gpio = Eeprom.readUInt8(401);
  configuration.correction = Eeprom.read(402, 5).toFloat();
  configuration.interval = Eeprom.read(407, 5).toInt();
  configuration.unit = Eeprom.readUInt8(412);
  Serial << endl << "INFO: Requested : DS18B20 : ";
  Serial << endl << "    - Present : " << configuration.present;
  Serial << endl << "    - GPIO : " << configuration.gpio;
  Serial << endl << "    - Correction by : " << configuration.correction;
  Serial << endl << "    - Read interval : " << configuration.interval;
  Serial << endl << "    - Unit : " << configuration.unit;
  return configuration;
}

*/
/* @TODO DOMOTICZ
void AFEDataAccess::saveConfiguration(DOMOTICZ configuration) {
  Eeprom.write(228, 32, configuration.host);
  Eeprom.writeIP(260, configuration.ip);
  Eeprom.write(264, 5, (long)configuration.port);
  Eeprom.write(269, 32, configuration.user);
  Eeprom.write(301, 32, configuration.password);
}
*/
/* @TODO DS18B20
void AFEDataAccess::saveConfiguration(DS18B20 configuration) {
  Eeprom.writeUInt8(401, configuration.gpio);
  Eeprom.write(402, 5, (float)configuration.correction);
  Eeprom.write(407, 5, (long)configuration.interval);
  Eeprom.writeUInt8(412, configuration.unit);
} */
