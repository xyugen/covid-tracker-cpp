#include <iostream>
#include <curl/curl.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sstream>
#include "json.hpp" // nlohmann
#include "colormod.hpp" // joel sjogren
/*  
 *  COVID-19 TRACKER  
 *  INPIRED BY: joshxfi's covid-tracker
 *  API: https://disease.sh/
 *  AUTHOR: xyugen
 *  LICENCE: MIT-LICENSE
 */ 

#define URL "https://disease.sh/v3/covid-19/"

// color modifiers
Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier magenta(Color::FG_MAGENTA);
Color::Modifier cyan(Color::FG_CYAN);
Color::Modifier white(Color::FG_WHITE);

Color::Modifier def(Color::FG_DEFAULT);

static size_t WriteCallback(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    ((std::string*)buffer)->append((char*)data, size * nmemb);
    return size * nmemb;
}

void toCapital(std::string &str) {
    if (str.length() == 0) {
        return;
    }
 
    str[0] = std::toupper(str[0]);
}

void printData(std::string params)
{
    CURL *curl;
    CURLcode res;
    std::string buffer;

    char url_buffer[256];
    std::ostringstream out;
    //snprintf(url_buffer, sizeof(url_buffer), "%s%s", URL, params);
    out << URL << params;

    std::string url_str = out.str();
    url_str.copy(url_buffer, url_str.size());
    url_buffer[url_str.size()] = '\0';

    // init curl session
    curl = curl_easy_init();
    if(curl) {
        // url
        curl_easy_setopt(curl, CURLOPT_URL, url_buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // send data to function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer); // save res -> buffer

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;

        // cleanup
        curl_easy_cleanup(curl);
    }

    if (!buffer.empty()) {
        nlohmann::json j = nlohmann::json::parse(buffer);
        int updated = j["updated"],
            cases = j["cases"],
            tCases = j["todayCases"],
            deaths = j["deaths"],
            tDeaths = j["todayDeaths"],
            recovered = j["recovered"],
            tRecovered = j["todayRecovered"],
            active = j["active"],
            critical = j["critical"];

        std::cout << blue <<
            "\tUpdated:\t\t" << updated << std::endl;
        
        putchar('\n');

        std::cout << blue <<
            "\tCases:\t\t\t" << cases << std::endl << red <<
            "\tDeaths:\t\t\t" << deaths << std::endl << green <<
            "\tRecovered:\t\t" << recovered << std::endl;

        putchar('\n');

        std::cout << blue <<
            "\tCases Today:\t\t" << tCases << std::endl << red <<
            "\tDeaths Today:\t\t" << tDeaths << std::endl << green <<
            "\tRecovered Today:\t" << tRecovered << std::endl;

        putchar('\n');

        std::cout << blue <<
            "\tActive:\t\t\t" << active << std::endl << red <<
            "\tCritical:\t\t" << critical << def << std::endl;

    } else {
        std::cerr << "Error: buffer is empty" << std::endl;
    } 
}


void title()
{
    std::cout << cyan << 
        "  ___ _____ _  _ ____ ____     ____ ____   __   ___ _  _ ____ ____ \n" << 
        " / __(  _  ( \\/ (_  _(  _ \\   (_  _(  _ \\ /__\\ / __( )/ ( ___(  _ \\\n" << 
        "( (__ )(_)( \\  / _)(_ )(_) )    )(  )   //(__)( (__ )  ( )__) )   /\n" << 
        " \\___(_____) \\/ (____(____/    (__)(_)\\_(__)(__\\___(_)\\_(____(_)\\_)\n" << magenta <<
        "\t\t   PROGRAMMED BY: YUGEN" << def << std::endl;
}

void menu()
{
    std::cout << white <<
        "\t[1] GLOBAL\n" <<
        "\t[2] CONTINENT\n" <<
        "\t[3] COUNTRY\n\n" << red <<
        "\t[0] EXIT" << def << std:: endl;
}

int main()
{
    int c;
    
    system("clear");
    std::string name;
    do {
        title();
        menu();

        std::cout << "\tChoice: ";
        std::cin >> c;

        switch (c)
        {
            case 1:
                system("clear");
                title();

                std::cout << "\t\tGLOBAL" << std::endl;
                printData("all");

                break;
            case 2:
                system("clear");
                title();

                std::cout << "Enter continent name: ";
                std::cin >> name;
                toCapital(name);
                std::cout << "\t\t" << name << std::endl;
                printData("continents/" + name);

                break;
            case 3:
                system("clear");
                title();

                std::cout << "Enter country name/iso2/iso3/code: ";
                std::cin >> name;
                if (name.length() > 5)
                    toCapital(name);
                std::cout << "\t\t" << name << std::endl;
                printData("countries/" + name);

                break;
            case 0:
                system("clear");
                title();
                std::cout << "\tExiting..." << std::endl;
                break;
            default:
                system("clear");
                std::cout << "\tInvalid input..." << std::endl;
                break;
        }
    } while (c != 0);

    return 0;
}

