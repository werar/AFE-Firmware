#include "AFE-Sites-Generator.h"

AFESitesGenerator::AFESitesGenerator() { language = Data.getLanguage(); }

const String AFESitesGenerator::generateHeader(uint8_t redirect) {

  FIRMWARE configuration;
  configuration = Data.getFirmwareConfiguration();

  String page = "<!doctype html>"
                "<html lang=\"en\">"
                "<head>"
                "<meta charset=\"utf-8\">";

  if (redirect > 0) {
    page += "<meta http-equiv=\"refresh\" content=\"";
    page += String(redirect);
    page += ";URL=/\">";
  }

  page += "<title>AFE Firmware ";
  page += configuration.version;
  page += " [T";
  page += configuration.type;
  page +=
      "]</title>"
      "<style>body{margin:0}#c{display:table;width:100%}#l,#r{display:table-"
      "cell}#l{width:300px;background:#282828;padding:20px;color:#eee}#r{"
      "padding:20px}p,a,input,h1,h3,h4,span,label,button,li{font-family:sans-"
      "serif}a{text-decoration:none}.ltit,.ltag{margin:0}.ltag{font-weight:300;"
      "color:#b0cadb;margin-bottom:20px}.lst{list-style:none;margin:0;padding:"
      "0}.itm "
      "a{display:block;text-decoration:none;white-space:nowrap;padding:.2em "
      "1em;color:#777;font-size:95%}.itm a:hover,.itm "
      "a:focus{background-color:#eee;text-decoration:none;padding:.2em "
      "1.5em;color:#000}.ci{margin-bottom:2em}.ci "
      "h1{color:#aaa;border-bottom:1px solid "
      "#eee;font-size:110%;font-weight:500;letter-spacing:.1em}.ci "
      ".cd{color:#444;line-height:1.8em;font-size:80%;font-style:italic}.cm{"
      "color:#999;font-size:90%;margin:0 0 20px 0}.la{margin:0 "
      ".1em;padding:.3em "
      "1em;color:#fff;background:#999;font-size:80%}.lr{background:#ca3c3c}.lg{"
      "background:#2fb548}fieldset{margin:0;padding:.35em 0 "
      ".75em;border:0}.cf{margin-bottom:.5em}.cc{margin:1em 0 .5em 9.4em}.cf "
      "label{text-align:right;display:inline-block;vertical-align:middle;width:"
      "10em;margin:0 1em 0 0;font-size:.875em}.cc "
      "label{font-size:.875em}input,select{padding:.5em "
      ".6em;display:inline-block;border:1px solid "
      "#ccc;vertical-align:middle;box-sizing:border-box}.hint{display:inline-"
      "block;padding-left:.3em;color:#aaa;vertical-align:middle;font-size:80%}."
      "b{font-size:100%;padding:.5em 1em;border:1px solid #999;border:none "
      "rgba(0,0,0,0);text-decoration:none;color:white}.bs{background:#2fb548}."
      "be{background:#ca3c3c}.bw{background:#df7514}.bc{background:#42b8dd}.b:"
      "hover,.b:focus{filter:alpha(opacity=90);background-image:-webkit-linear-"
      "gradient(transparent,rgba(0,0,0,0.05) "
      "40%,rgba(0,0,0,0.10));background-image:linear-gradient(transparent,rgba("
      "0,0,0,0.05) 40%,rgba(0,0,0,0.10))}</style>"
      "</head>"
      "<body>"
      "<div id=\"c\">"
      "<div id=\"l\">"
      "<h3 class=\"ltit\">AFE FIRMWARE</h3>"
      "<h4 class=\"ltag\">";
  page += language == 0 ? "dla urządzeń zbudowanych o" : "for devices built on";
  page += " ESP8266</h4>"
          "<h4>MENU</h4>"
          "<ul class=\"lst\">";
  if (Device.getMode() != MODE_NORMAL) {
    Device.begin(); // Reading configuration data
    page += "<li class=\"itm\"><a href=\"\\?option=device\">";
    page += language == 0 ? "Urządzenie" : "Device";
    page += "</a></li> "
            "<li class=\"itm\"><a href=\"\\?option=network\">";
    page += language == 0 ? "Sieć WiFi" : "Network";
    page += "</a></li>";
    if (Device.configuration.mqttAPI) {
      page += "<li class=\"itm\"><a "
              "href=\"\\?option=mqtt\">MQTT "
              "Broker</a></li>";
    }
    if (Device.configuration.isLED[0]) {
      page += "<li class=\"itm\"><a href=\"\\?option=led\">LED</a></li>";
    }
    if (Device.configuration.isRelay[0]) {
      page += "<li class=\"itm\"><a href=\"\\?option=relay\">";
      page += language == 0 ? "Przekaźnik" : "Relay";
      page += "</a></li>";
    }
    if (Device.configuration.isSwitch[0] || Device.configuration.isSwitch[1]) {
      page += "<li class=\"itm\"><a href=\"\\?option=switch\">";
      page += language == 0 ? "Przycisk / Włącznik" : "Switch / Button";
      page += "</a></li>";
    }
    page +=
        "<br><br><li class=\"itm\"><a "
        "href=\"\\?option=language\">[PL] Język / "
        "[EN] Language</a></li><br><br><li class=\"itm\"><a href=\"\\update\">";
    page += language == 0 ? "Aktulizacja firmware" : "Firmware upgrade";
    page += "</a></li><li class=\"itm\"><a href=\"\\?option=reset\">";
    page += language == 0 ? "Przywracanie ustawień początkowych"
                          : "Reset to orginal state";
    page += "</a></li><br><br><li class=\"itm\"><a href=\"\\?option=exit\">";
    page += language == 0 ? "Zakończ konfigurację" : "Finish configuration";
  } else {
    page += "<li class=\"itm\"><a href=\"\\?option=help&cmd=1\">";
    page += language == 0 ? "Ustawienia" : "Settings";
    page += "</a></li><li class=\"itm\"><a href=\"\\?option=help&cmd=2\">";
    page += language == 0 ? "Ustawienia (tryb:" : "Settings (mode:";
    page += " Access Point)";
  }
  page += "</a></li></ul><br><br><h4>INFORMA";
  page += language == 0 ? "CJE" : "TION";
  page += "</h4><ul class=\"lst\"><li class=\"itm\"><a "
          "href=\"http://smart-house.adrian.czabanowski.com/afe-firmware-";
  page += language == 0 ? "pl" : "en";
  page += "/\" target=\"_blank\">Do";
  page += language == 0 ? "kumentacja" : "cumentation";
  page += "</a></li><li class=\"itm\"><a "
          "href=\"http://smart-house.adrian.czabanowski.com/forum/"
          "firmware-do-przelacznika-sonoff/\" target=\"_blank\">";
  page += language == 0 ? "Pomoc" : "Help";
  page += "</a></li><li class=\"itm\"><a "
          "href=\"https://github.com/tschaban/AFE-Firmware/blob/master/"
          "LICENSE\" "
          "target=\"_blank\">Licenc";
  page += language == 0 ? "ja" : "e";
  page += "</a></li><li class=\"itm\"><a "
          "href=\"http://smart-house.adrian.czabanowski.com/afe-firmware-";
  page += language == 0 ? "pl" : "en";
  page += "/log\" target=\"_blank\">";
  page += language == 0 ? "Wersja" : "Version";
  page += " ";
  page += configuration.version;
  page += " [T";
  page += configuration.type;
  page += "]</a></li>"
          "</ul>";
  if (Device.getMode() != MODE_ACCESS_POINT) {
    page += "<br><br><h4>";
    page += language == 0 ? "WSPARCIE" : "DONATION";
    page += "</h4><p class=\"cm\">";
    page += language == 0
                ? "Oprogramowanie dostępne jest za darmo w ramach licencji "
                : "Software is available for free within terms of ";
    page += " <a "
            "href=\"https://github.com/tschaban/AFE-Firmware/blob/master/"
            "LICENSE\" "
            "target=\"_blank\"  style=\"color:#fff\">MIT</a>";
    page += language == 1 ? " licence" : "";
    page += "</p><p class=\"cm\">";
    page += language == 0 ? "Jeśli spełnia Twoje oczekiwania to rozważ wsparcie"
                          : "If the firmware meets your expectations then "
                            "consider donation to it's";
    page += " <a href=\"https://adrian.czabanowski.com\" "
            "target=\"_blank\" style=\"color:#fff\">aut";
    page += language == 0 ? "ora" : "hor";
    page += "</a>. ";
    page += language == 0 ? "Z góry dziękuję" : "Thank you";
    page += "</p>";
    page +=
        "<a "
        "href=\"https://www.paypal.com/cgi-bin/"
        "webscr?cmd=_donations&business=VBPLM42PYCTM8&lc=PL&item_name="
        "Wsparcie%20projektu%20AFE%20Firmware&item_number=Firmware%20%5bvT0%"
        "5d&currency_code=PLN&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%"
        "3aNonHosted\" target=\"_blank\"><img "
        "src=\"http://adrian.czabanowski.com/afe/donation/T";
    page += configuration.type;
    page += "/";
    page += configuration.version;
    page += "/\" border=\"0\" alt=\"PayPal\" style=\"width:290px\"></a>";
  }
  page += "</div>"
          "<div id=\"r\">";
  return page;
}

String AFESitesGenerator::addDeviceConfiguration() {
  DEVICE configuration;
  configuration = Data.getDeviceConfiguration();

  String body = "<fieldset><div class=\"cf\"><label>";
  body += language == 0 ? "Nazwa urządzenia" : "Device name";
  body += "*</label><input name=\"deviceName\" type=\"text\" maxlength=\"16\" "
          "value=\"";
  body += configuration.name;
  body += "\"><span class=\"hint\">Max 16 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span></div></fieldset>";

  String page = addConfigurationBlock(
      language == 0 ? "Nazwa urządzenia" : "Device name",
      language == 0
          ? "Nazwa jest wykorzystywana jako nazwa urządzenia w Twojej "
            "lokalnej sieci WiFi "
            "oraz jako nazwa punktu dostępowego WiFi do "
            "konfiguracji urządzenia"
          : "Device name is used within your LAN as the device's device "
            "and device's Access Point name which allows to connect to "
            "Configuration Panel",
      body);

  body = "<fieldset>";

  body += generateLEDItem(0, configuration.isLED[0]);
  body += generateRelayItem(0, configuration.isRelay[0]);
  body += generateSwitchItem(0, configuration.isSwitch[0]);
  body += generateSwitchItem(1, configuration.isSwitch[1]);

  body += "</fieldset>";

  page += addConfigurationBlock(
      language == 0 ? "Sprzęt" : "Hardware",
      language == 0 ? "Konfiguracja urządzenia" : "Device configuration", body);

  body = "<fieldset>";
  body += "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"mqttAPI\" type=\"checkbox\" value=\"1\"";
  body += configuration.mqttAPI ? " checked=\"checked\"" : "";
  body += ">MQTT API ";
  body += language == 0 ? "włączone" : "enabled";
  body += "?";
  body += "</label>";
  body += "</div>";

  body += "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"httpAPI\" type=\"checkbox\" value=\"1\"";
  body += configuration.httpAPI ? " checked=\"checked\"" : "";
  body += ">HTTP API ";
  body += language == 0 ? "włączone" : "enabled";
  body += "?";
  body += "</label>";
  body += "</div>";

  body += "</fieldset>";

  page += addConfigurationBlock(
      language == 0 ? "Sterowanie urządzeniem" : "Device controlling mechanism",
      language == 0
          ? "Włączanie / Wyłączanie mechanizmów sterowania urządzeniem"
          : "Enable / Disable APIs",
      body);

  return page;
}

String AFESitesGenerator::addNetworkConfiguration() {

  NETWORK configuration;
  configuration = Data.getNetworkConfiguration();

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Nazwa sieci WiFI" : "Wireless network name";
  body += "*</label>";
  body += "<input name=\"wifi_ssid\" type=\"text\" maxlength=\"32\" value=\"";
  body += configuration.ssid;
  body += "\">";
  body += "<span class=\"hint\">Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Hasło" : "Password";
  body += "*</label>";
  body += "<input type=\"password\" name=\"wifi_password\" maxlength=\"32\" "
          "value=\"";
  body += configuration.password;
  body += "\">";
  body += "<span class=\"hint\">Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "</fieldset>";

  String page = addConfigurationBlock(
      language == 0 ? "Konfiguracja dostępu do sieci WiFi" : "WiFi network",
      language == 0 ? "Urządzenie bez dostępu do sieci WiFi będzie "
                      "działać tylko w trybie sterowania ręcznego"
                    : "Device without access to WiFi network will only work in "
                      "manual mode",
      body);

  body = "<fieldset>";
  body += "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"dhcp_config\" type=\"checkbox\" value=\"1\"";
  body += (configuration.isDHCP ? " checked=\"checked\"" : "");
  body += "> ";
  body += language == 0 ? "Automatyczna konfiguracja przez DHCP?"
                        : "Automatic configuration over DHCP";
  body += "</label>";
  body += "</div>";

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Adres IP" : "IP Addess";
  body += "</label>";
  body += "<input name=\"device_ip1\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[0];
  body += "\">.";
  body += "<input name=\"device_ip2\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[1];
  body += "\">.";
  body += "<input name=\"device_ip3\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[2];
  body += "\">.";
  body += "<input name=\"device_ip4\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[3];
  body += "\">";
  body += "</div>";

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Bramka" : "Gateway";
  body += "</label>";
  body += "<input name=\"gateway_ip1\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.gateway[0];
  body += "\">.";
  body += "<input name=\"gateway_ip2\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.gateway[1];
  body += "\">.";
  body += "<input name=\"gateway_ip3\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.gateway[2];
  body += "\">.";
  body += "<input name=\"gateway_ip4\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.gateway[3];
  body += "\">";
  body += "</div>";

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Maska sieci" : "Subnet";
  body += "</label>";
  body += "<input name=\"subnet_ip1\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.subnet[0];
  body += "\">.";
  body += "<input name=\"subnet_ip2\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.subnet[1];
  body += "\">.";
  body += "<input name=\"subnet_ip3\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.subnet[2];
  body += "\">.";
  body += "<input name=\"subnet_ip4\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.subnet[3];
  body += "\">";
  body += "</div>";

  body += "</fieldset>";

  page += addConfigurationBlock(
      language == 0 ? "Adres IP urządzenia" : "Device's IP address",
      language == 0 ? "Możesz skonfigurować adres IP urządzenia ręcznie lub "
                      "automatycznie za pośrednictwem DHCP"
                    : "You can set up device's IP address manually or "
                      "automatically by DHCP",
      body);

  body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Ilość prób łączenia się"
                        : "Number of connection attempts";
  body += "*</label>";
  body += "<input name=\"no_connection_attempts\" type=\"number\" "
          "maxlength=\"3\" value=\"";
  body += configuration.noConnectionAttempts;
  body += "\">";
  body += "<span class=\"hint\">1-255</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Czas między próbami łączenia się"
                        : "Time between connections' attempts";
  body += "*</label>";
  body += "<input type=\"number\" name=\"wait_time_connections\" "
          "maxlength=\"3\" value=\"";
  body += configuration.waitTimeConnections;
  body += "\">";
  body += "<span class=\"hint\">1-255 (";
  body += language == 0 ? "sekundy" : "seconds";
  body += ")</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Czas po jakim powtórzyć próby łączenia się"
                        : "Sleep time before next connection attempts";
  body += "*</label>";
  body += "<input type=\"number\" name=\"wait_time_series\" maxlength=\"3\" "
          "value=\"";
  body += configuration.waitTimeSeries;
  body += "\">";
  body += "<span class=\"hint\">1-255 (";
  body += language == 0 ? "sekundy" : "seconds";
  body += ")</span>";
  body += "</div>";
  body += "</fieldset>";

  page += addConfigurationBlock(
      language == 0 ? "Konfiguracja nawiązywania połączeń z siecią WiFi"
                    : "Network connection's configuration",
      language == 0
          ? "Zaawansowane ustawienia dotyczące łączenia "
            "się do sieci WiFi oraz MQTT Brokera"
          : "Advanced configuration of the network connections process",
      body);

  return page;
}

String AFESitesGenerator::addMQTTBrokerConfiguration() {

  MQTT configuration;
  configuration = Data.getMQTTConfiguration();

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>Hostname</label>";
  body += "<input name=\"mqtt_host\" type=\"text\" maxlength=\"32\" value=\"";
  body += configuration.host;
  body += "\">";
  body += "<span class=\"hint\">Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Adres IP" : "IP address";
  body += "</label>";
  body += "<input name=\"mqtt_ip1\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[0];
  body += "\">.";
  body += "<input name=\"mqtt_ip2\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[1];
  body += "\">.";
  body += "<input name=\"mqtt_ip3\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[2];
  body += "\">.";
  body += "<input name=\"mqtt_ip4\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[3];
  body += "\">";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Port*</label>";
  body += "<input name=\"mqtt_port\" type=\"number\""
          "maxlength=\"5\" value=\"";
  body += configuration.port;
  body += "\">";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Użytkownik" : "User";
  body += "</label>";
  body += "<input name=\"mqtt_user\" type=\"text\"  maxlength=\"32\" value=\"";
  body += configuration.user;
  body += "\">";
  body += "<span class=\"hint\">Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Hasło" : "Password";
  body += "</label>";
  body += "<input name=\"mqtt_password\" type=\"password\"  maxlength=\"32\" "
          "value=\"";
  body += configuration.password;
  body += "\">";
  body += "<span class=\"hint\">Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Temat wiadomości" : "MQTT Topic";
  body += "*</label>";
  body += "<input name=\"mqtt_topic\" type=\"text\""
          "maxlength=\"32\" value=\"";
  body += configuration.topic;
  body += "\">";
  body += "<span class=\"hint\">Format <strong>/abc/def/</strong>. Max 32 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";
  body += "</fieldset>";

  return addConfigurationBlock(
      "MQTT Broker",
      language == 0 ? "Urządzenie bez skonfigurowanego MQTT Brokera "
                      "może być sterowane tylko ręcznie. Wprowadź "
                      "adres hosta np. localhost lub adres IP"
                    : "Device without MQTT Broker configured can only be "
                      "controled manually. Enter MQTT Broker hostname or its "
                      "IP address",
      body);
}

String AFESitesGenerator::addLEDConfiguration(uint8_t id) {
  LED configuration;
  configuration = Data.getLEDConfiguration(id);

  String body = "<fieldset>";

  char filed[13];
  sprintf(filed, "led%d_gpio", id);

  body += generateConfigParameter_GPIO(filed, configuration.gpio);

  body += "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"led";
  body += id;
  body += "_opposite\" type=\"checkbox\" value=\"1\"";
  body += configuration.changeToOppositeValue ? " checked=\"checked\"" : "";
  body += ">";
  body += language == 0 ? "Zmień świecenie diody LED na odwrotne"
                        : "Change LED ligtning to opposite";
  body += "</label>";
  body += "</div>";

  body += "</fieldset>";

  return addConfigurationBlock(
      "LED",
      language == 0 ? "LED wykorzystywany jest do identyfikowania w jakim "
                      "stanie jest urządzenie"
                    : "LED helps to identify the state of the device",
      body);
}

String AFESitesGenerator::addRelayConfiguration(uint8_t id) {

  RELAY configuration;
  configuration = Data.getRelayConfiguration(id);

  String body = "<fieldset>";

  char filed[13];
  sprintf(filed, "relay%d_gpio", id);

  body += generateConfigParameter_GPIO(filed, configuration.gpio);

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Nazwa" : "Name";
  body += "*</label>";
  body += "<input name=\"relay" + String(id) +
          "_name\" type=\"text\" maxlength=\"16\" value=\"";
  body += configuration.name;
  body += "\">";
  body += "<span class=\"hint\">Max 16 ";
  body += language == 0 ? "znaków" : "chars";
  body += "</span>";
  body += "</div>";

  body += "<p class=\"cm\">";
  body +=
      language == 0
          ? "Konfiguracja zachowania się przekaźnika po przywróceniu zasilania "
            "lub nawiązaniu połączenia do brokera MQTT"
          : "Setting relay state after power is restored "
            "or the device connected to MQTT Broker";
  body += "</p>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Po przywróceniu zasilania"
                        : "When power is restored set it to";
  body += "</label>";
  body += "<select name=\"relay" + String(id) + "_power_restored\">";
  body += "<option value=\"0\"";
  body += (configuration.statePowerOn == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Brak akcji" : "No action";
  body += "</option>";
  body += "<option value=\"1\"";
  body += (configuration.statePowerOn == 1 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Wyłączony" : "Off";
  body += "</option>";
  body += "<option value=\"2\"";
  body += (configuration.statePowerOn == 2 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Włączony" : "On";
  body += "</option>";
  body += "<option value=\"3\"";
  body += (configuration.statePowerOn == 3 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Ostatnia zapamiętana wartość" : "Last known state";
  body += "</option>";
  body += "<option value=\"4\"";
  body += (configuration.statePowerOn == 4 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Przeciwna do ostatniej zapamiętanej wartości"
                        : "Oposite to the last known state";
  body += "</option>";
  body += "</select>";
  body += "</div>";

  /* @TODO MQTT */
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Po podłączeniu do brokera MQTT"
                        : "After establishing connection to MQTT Broker";
  body += "</label>";
  body += "<select  name=\"relay" + String(id) + "_mqtt_connected\">";
  body += "<option value=\"0\"";
  body +=
      (configuration.stateMQTTConnected == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Brak akcji" : "No action";
  body += "</option>";
  body += "<option value=\"1\"";
  body +=
      (configuration.stateMQTTConnected == 1 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Wyłączony" : "Off";
  body += "</option>";
  body += "<option value=\"2\"";
  body +=
      (configuration.stateMQTTConnected == 2 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Włączony" : "On";
  body += "</option>";
  body += "<option value=\"3\"";
  body +=
      (configuration.stateMQTTConnected == 3 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Ostatnia zapamiętana wartość" : "Last known state";
  body += "</option>";
  body += "<option value=\"4\"";
  body +=
      (configuration.stateMQTTConnected == 4 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Przeciwna do ostatniej zapamiętanej wartości"
                        : "Oposite to the last known state";
  body += "</option>";
  body += "<option value=\"5\"";
  body +=
      (configuration.stateMQTTConnected == 5 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0
              ? "Wartość z systemu sterowania przekaźnikiem (przez MQTT)"
              : "Get state from a relay's controlling system (over MQTT)";
  body += "</option>";
  body += "</select>";
  body += "</div>";

  body += "<br><p class=\"cm\">";
  body += language == 0 ? "Funkcjonalność automaycznego wyłączenie przekaźnika "
                        : "Automatic relay switching off functionality";
  body += "</p>";

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Wyłącz po" : "Turn relay OFF after";
  body += "*</label>";
  body += "<input name=\"relay" + String(id) +
          "_off_time\" type=\"number\" step=\"0.01\" maxlength=\"5\" value=\"";
  body += configuration.timeToOff;
  body += "\">";
  body += "<span class=\"hint\">0.01 - 99999 (";
  body += language == 0 ? "sekund). Brak akcji jeśli jest ustawione na 0"
                        : "seconds). No action if it's set to 0";
  body += "</span>";
  body += "</div>";

  body += "</fieldset>";

  char title[23];
  language == 0 ? sprintf(title, "Przekaźnik #%d", id + 1)
                : sprintf(title, "Relay #%d", id + 1);

  return addConfigurationBlock(
      title,
      language == 0
          ? "Przekaźnik musi posiadać unikalną nazwę np. "
            "<strong>lampa</strong>. "
            "Nazwa przekaźnika jest używana przez MQTT API"
          : "Relay must have unique name, for example: <strong>lamp</strong>. "
            "Relay name is used by MQTT API",
      body);
}

String AFESitesGenerator::addSwitchConfiguration(uint8_t id) {

  SWITCH configuration;
  configuration = Data.getSwitchConfiguration(id);

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Funkcja" : "Functionality";
  body += "</label>";
  body += "<select name=\"switch" + String(id) + "_functionality\">";
  body += "<option value=\"11\"";
  body += (configuration.functionality == 11 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Sterowanie przekaźnikiem" : "Relay control";
  body += "</option>";
  body += "<option value=\"0\"";
  body += (configuration.functionality == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Multifunkcyjny" : "Multifunction";
  body += "</option>";
  /*  body += "<option value=\"3\"";
  body += (configuration.functionality == 3 ? " selected=\"selected\"" : "");
  body += ">Reboot</option>";
  body += "<option value=\"4\"";
  body += (configuration.functionality == 4 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Uruchamianie tryb konfiguracji"
                        : "Launching configuration mode";
  body += "</option>";
  body += "<option value=\"5\"";
  body += (configuration.functionality == 5 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Aktualizacja oprogramowania" : "Firmware upgrade";
  body += "</option>"; */
  body += "</select>";
  body += "</div>";
  char filed[13];
  sprintf(filed, "switch%d_gpio", id);
  body += generateConfigParameter_GPIO(filed, configuration.gpio);

  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Typ" : "Type";
  body += "*</label>";
  body += "<select name=\"switch" + String(id) + "_type\">";
  body += "<option value=\"0\"";
  body += (configuration.type == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Monostabilny" : "Monostable";
  body += "</option>";
  body += "<option value=\"1\"";
  body += (configuration.type == 1 ? " selected=\"selected\"" : "");
  body += ">";
  body += language == 0 ? "Bistabilny" : "Bistable";
  body += "</option>";
  body += "</select>";
  body += "</div>";
  body += "<br><p class=\"cm\">";
  body += language == 0
              ? "Czułość włącznika należy ustawić metodą prób, aż uzyska się "
                "porządane jego działanie "
              : "Button's sensitiveness should be adjusted if it didn't behave "
                "as expected";

  body += "</p><div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Czułość" : "Sensitiveness";
  body += "*</label>";
  body += "<input name=\"switch" + String(id) +
          "_sensitivity\" type=\"number\" maxlength=\"3\" "
          "value=\"";
  body += configuration.sensitiveness;
  body += "\">";
  body += "<span class=\"hint\">0 - 999 (milise";
  body += language == 0 ? "kund" : "conds";
  body += ")</span>";
  body += "</div>";
  body += "</fieldset>";

  char title[23];
  language == 0 ? sprintf(title, "Przycisk / Włącznik #%d", id + 1)
                : sprintf(title, "Switch / Button #%d", id + 1);

  return addConfigurationBlock(title, "", body);
}

String AFESitesGenerator::addUpgradeSection() {
  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Wybierz" : "Select";
  body += " firmware</label>";
  body += "<input class=\"bs\" name=\"update\" type=\"file\" accept=\".bin\">";
  body += "</div>";
  body += "<p class=\"cm\">";
  body += language == 0
              ? "Po zakończeniu aktualizacji urządzenie zostanie "
                "automatycznie zresetowane"
              : "Device will be automatically rebooted after an upgrade";
  body += "</p>";
  body += "<button type=\"submit\" class=\"b be\">";
  body += language == 0 ? "Aktualizuj" : "Upgrade";
  body += "</button>";
  body += "</fieldset>";
  return addConfigurationBlock(
      language == 0 ? "Aktualizacja firmware" : "Firmware upgrade",
      language == 0 ? "<strong>UWAGA</strong>: nie odłączaj "
                      "urządzenia od źródła zasilania podczas aktualizacji"
                    : "<strong>Warning</strong>: don't plug off the device "
                      "from a power source while upgrading",
      body);
}

String AFESitesGenerator::addPostUpgradeSection(boolean status) {

  String body = "<fieldset><ul>";
  if (status) {
    body += "<li style=\"color:red\">";
    body += language == 0 ? "Aktualizacja nie powiodła się" : "Upgrade failed";
  } else {
    body += "<li class=\"cm\">";
    body += language == 0 ? "Aktualizacja zakończona pomyślnie"
                          : "Upgrade finished succesfully";
  }
  body += "</li><li class=\"cm\">";
  body +=
      language == 0
          ? "Po 10 "
            "sekundach przełącznik zostanie przeładowany z wgranym "
            "oprogramowaniem. Proszę czekać"
          : "After 10s device will be rebooted and the new firmware will be "
            "loaded. Please wait";
  body += "....</li>";
  body += "</fieldset>";
  return addConfigurationBlock(
      language == 0 ? "Aktualizacja firmware" : "Firmware upgrade", "", body);
}

String AFESitesGenerator::addResetSection(uint8_t command) {
  String body = "<fieldset>";
  String subtitle;
  if (command == 0) {
    body += "<a href=\"\\?option=reset&cmd=1\" class=\"b be\">";
    body += language == 0 ? "Przywróć ustawienia początkowe"
                          : "Restore default settings";
    body += "</a>";
    subtitle = "<strong>";
    subtitle += language == 0 ? "Uwaga" : "Warning";
    subtitle += "</strong>: ";
    subtitle +=
        language == 0
            ? "przywrócenie ustawień "
              "początkowych usuwa wszystkie ustawienia "
              "urządzenia, włącznie z konfiguracją sieci WiFi"
            : "restoring to default settings will remove all configuration's "
              "information, incl. WiFi configuration";
  } else {
    subtitle += "";
    body += language == 0 ? "Trwa przywracanie ustawień początkowych"
                          : "Restoring configuration is in progress";
    body += "</strong>";
    body += "<p class=\"cm\">";
    body += language == 0 ? "Po 20 sekundach połącz się z siecią WiFi o "
                            "nazwie: <strong>AFE-Device</strong>, a następnie "
                            "połącz się z "
                            "panelem konfiguracyjnym pod adresem"
                          : "After 20 seconds connect to WiFi network called "
                            "<strong>AFE-Device</strong> and open "
                            "configuration panel";
    body += ": </p>";
    body += "<a href=\"http://192.168.5.1\">http://192.168.5.1</a>";
  }
  body += "</fieldset>";
  return addConfigurationBlock(language == 0
                                   ? "Przywracanie ustawień początkowych"
                                   : "Restoring to default settings",
                               subtitle, body);
}

String AFESitesGenerator::addExitSection() {
  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<p class=\"cm\">";
  body += language == 0 ? "Trwa restart urządzenia" : "Reboot in progress";
  body += ".....</p>";
  body += "<p class=\"cm\">";
  body += language == 0 ? "Strona zostanie przeładowana automatycznie... czekaj"
                        : "Site will be automatically reloaded... wait";
  body += "</p>";
  body += "</div>";
  body += "</fieldset>";
  return addConfigurationBlock(
      language == 0 ? "Restart urządzenia" : "Device reboot", "", body);
}

String AFESitesGenerator::addHelpSection() {
  DEVICE configuration;
  configuration = Data.getDeviceConfiguration();

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += language == 0 ? "Nazwa urządzenia" : "Device name";
  body += "</label>";
  body += "<span>";
  body += configuration.name;
  body += "</span>";
  body += "</div>";
  body += "</fieldset>";
  return addConfigurationBlock(language == 0
                                   ? "Urządzenie jest w trybie operacyjnym"
                                   : "Device is in working mode",
                               "", body);
}

String AFESitesGenerator::addLanguageConfiguration() {

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>Language / Język";
  body += ": </label>";
  body += "<select name=\"language\">";
  body += "<option value=\"0\"";
  body += language == 0 ? " selected=\"selected\"" : "";
  body += ">Polski</option>";
  body += "<option value=\"1\"";
  body += language == 1 ? " selected=\"selected\"" : "";
  body += ">English</option>";
  body += "</select>";
  body += "</div>";

  String page = addConfigurationBlock("Language / Język",
                                      "Choose language / "
                                      "Wybierz język",
                                      body);
  return page;
}

const char *AFESitesGenerator::generateFooter() {
  return "</div></div></body></html>";
}

String AFESitesGenerator::addConfigurationBlock(const String title,
                                                const String description,
                                                const String body) {
  String page = "<div class=\"ci\">";
  page += "<h1>" + title + "</h1>";
  page += "<p class=\"cd\">" + description + "</p>";
  page += body;
  page += "</div>";

  return page;
}

const String AFESitesGenerator::generateConfigParameter_GPIO(const char *field,
                                                             uint8_t selected) {
  String page = "<div class=\"cf\"><label>GPIO</label><select name=\"";
  page += field;
  page += "\">";
  for (uint8_t i = 0; i <= 16; i++) {
    page += "<option value=\"" + String(i) + "\"" +
            (selected == i ? "selected=\"selected\"" : "") + ">" + String(i) +
            "</option>";
  }
  page += "</select></div>";
  return page;
}

const String AFESitesGenerator::generateSwitchItem(uint8_t id,
                                                   boolean checked) {
  String body = "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"switch";
  body += id;
  body += "\" type =\"checkbox\" value=\"1\"";
  body += checked ? " checked=\"checked\"" : "";
  body += ">";
  body += language == 0 ? "Przycisk / włącznik #" : "Is button / switch #";
  body += id + 1;
  body += language == 0 ? " jest podłączony" : " present";
  body += "?";
  body += "</label>";
  body += "</div>";

  return body;
}

const String AFESitesGenerator::generateRelayItem(uint8_t id, boolean checked) {
  String body = "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"relay";
  body += id;
  body += "\" type =\"checkbox\" value=\"1\"";
  body += checked ? " checked=\"checked\"" : "";
  body += ">";
  body += language == 0 ? "Czy przekaźnik jest podłączony" : "Is Relay present";
  body += "?";
  body += "</label>";
  body += "</div>";

  return body;
}

const String AFESitesGenerator::generateLEDItem(uint8_t id, boolean checked) {
  String body = "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"led";
  body += id;
  body += "\" type =\"checkbox\" value=\"1\"";
  body += checked ? " checked=\"checked\"" : "";
  body += ">";
  body += language == 0 ? "Czy LED jest podłączony" : "Is LED present";
  body += "?";
  body += "</label>";
  body += "</div>";

  return body;
}

/* @TODO DOMOTICZ
body += "<div class=\"cf\">";
body += "<label>IDX urządzenia</label>";
body += "<input name=\"relay" + String(id) +
        "_idx\" type=\"number\" maxlength=\"3\" value=\"";
body += configuration.idx;
body += "\">";
body += "<span class=\"hint\">Informacja wymagana. Do odczytania z "
        "konfiguracji Domoticz</span>";
body += "</div>";

body += "<div class=\"cc\">";
body += "<label>";
body += "<input name=\"relay" + String(id) +
        "_publish_to_domoticz\" type=\"checkbox\" value=\"1\"";
body += (configuration.publishToDomoticz ? " checked=\"checked\"" : "");
body += "> Publikowac stan przekaźnika do Domoticz?";
body += "</label>";
body += "</div>";

*/

/* @TODO DOMOTICZ
String AFESitesGenerator::addDomoticzConfiguration() {

  DOMOTICZ configuration;
  configuration = Data.getDomoticzConfiguration();

  String body = "<fieldset>";
  body += "<div class=\"cf\">";
  body += "<label>IP serwera</label>";
  body += "<input name=\"domoticz_ip1\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[0];
  body += "\">.";
  body += "<input name=\"domoticz_ip2\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[1];
  body += "\">.";
  body += "<input name=\"domoticz_ip3\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[2];
  body += "\">.";
  body += "<input name=\"domoticz_ip4\" type=\"number\" maxlength=\"3\" "
          "style=\"width:70px\" value=\"";
  body += configuration.ip[3];
  body += "\">";
  body += "<span class=\"hint\">Informacja wymagana</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Port</label>";
  body += "<input name=\"domoticz_port\" type=\"number\" "
          "maxlength=\"5\" value=\"";
  body += configuration.port;
  body += "\">";
  body += "<span class=\"hint\">Informacja wymagana</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Użytkownik</label>";
  body +=
      "<input name=\"domoticz_user\" type=\"text\"  maxlength=\"32\" value=\"";
  body += configuration.user;
  body += "\">";
  body += "<span class=\"hint\">Max 32 znaki</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Hasło</label>";
  body += "<input name=\"domoticz_password\" type=\"password\"  "
          "maxlength=\"32\" value=\"";
  body += configuration.password;
  body += "\">";
  body += "<span class=\"hint\">Max 32 znaki</span>";
  body += "</div>";

  body += "</fieldset>";

  return addConfigurationBlock("Serwer Domoticz",
                               "Konfiguracja wymagana jest jedynie kiedy jest "
                               "potrzeba wysyłania stanu przekaźnika do "
                               "serwera Domoticz",
                               body);
}
*/

/* @TODO DS18B20
String AFESitesGenerator::addDS18B20Configuration() {

  DS18B20 configuration;
  configuration = Data.getDS18B20Configuration();

  String body = "<fieldset>";
  body += "<div class=\"cc\">";
  body += "<label>";
  body += "<input name=\"ds18b20_present\" type=\"checkbox\" value=\"1\"";
  body += (configuration.present ? " checked=\"checked\"" : "");
  body += "> Włączony?";
  body += "</label>";
  body += "</div>";
  body += generateConfigParameter_GPIO("ds18b20_gpio", configuration.gpio);
  body += "<div class=\"cf\">";
  body += "<label>Odczyty co</label>";
  body += "<input name=\"ds18b20_interval\" type=\"number\" maxlength=\"5\" "
          "value=\"";
  body += configuration.interval;
  body += "\">";
  body += "<span class=\"hint\">sekund. Zakres 10sek do 99999sek</span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Korekta wartości o</label>";
  body += "<input name=\"ds18b20_correction\" type=\"number\" maxlength=\"6\" "
          "value=\"";
  body += configuration.correction;
  body += "\">";
  body += "<span class=\"hint\">stopni. Zakres -9.99 do 9.99, </span>";
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>Jednostka</label>";
  body += "<select  name=\"ds18b20_unit\">";
  body += "<option value=\"0\"";
  body += (configuration.unit == 0 ? " selected=\"selected\"" : "");
  body += ">celsjusz</option>";
  body += "<option value=\"1\"";
  body += (configuration.unit == 1 ? " selected=\"selected\"" : "");
  body += ">fahrenheit</option>";
  body += "</select>";
  body += "</div>";

  body += "</fieldset>";

  return addConfigurationBlock("Czujnik temperatury DS18B20",
                               "DS18B20 jest obsługiwanym czujnikiem "
                               "temperatury. Możliwe jest podłaczenie tylko "
                               "jednego czujnika temperatury",
                               body);
}
*/
